#include "stack_n_array.h"
#include "load.h"
#include <stdlib.h>
#include <stdio.h>

void testStack(){
    printf("> TESTS STACK :\n");
    stack a = createEmptyStack();
    printf("    -test createEmptyStack(): ");
    printStack(a);
    push(&a,4);
    push(&a,5);
    printf("    -test push : ");
    printStack(a);
    printf("    -test pop: %i, %i\n",pop(&a),pop(&a));
    printf("\n");
}

void testArray(){
    value* tab = createEmptyArray(10);
    tab[2]=2;
    printArray("> TESTS ARRAY :",tab,2,5);
    printf("\n");
}

void testAutomaton(){
    automaton aut = createEmptyAutomaton();
    loadAutomaton(&aut, "LR1/word_bis.aut");
    printf("> TESTS AUTOMATON :\n\n");
    printAutomaton(aut);
}

void test(){
    testStack();
    testArray();
    testAutomaton();
}

void getUserInput(char buf[]){
    fgets(buf, 256, stdin);
    sscanf(buf, "%s", buf);
}

void dispUserInput(char buf[]){
    printf("= [");
    for(int i=0;i<256;i+=1){
        if(buf[i]==0){
            i=256;
            printf(" \\n]\n");
        } else {
            printf("%4i,", buf[i]);
        }
    }
}

int fillStackLineFromUserInput(stack* line, char* user_input){
    int cursor = 0;
    int result = 0;
    while(cursor<256 && !result){
        if(user_input[cursor]==0){
            result = 1;
        }
        cursor+=1;
    }
    if(!result){
        perror("user input too long (max 256 characters including \\n)");
        return 2;
    }
    push(line,0);
    push(line, 10);
    for(int i = (cursor-2); i>=0; i--){
        push(line,user_input[i]);
    }
    return 0;
}

int main(int argc, char** argv){
    char user_input[256];
    if(argc != 2){
        fprintf(stderr,"Error usage: %s path_to_file\n",argv[0]);
        return 1;
    } else {
        automaton aut = createEmptyAutomaton();
        stack line;
        loadAutomaton(&aut, argv[1]);
        printf("File \"%s\" correctly read, please enter your inputs [^C to escape] :\n",argv[1]);
        while(1){    
            getUserInput(user_input);
            line = createEmptyStack();
            int res = fillStackLineFromUserInput(&line, user_input);
            if(res!=0){
                return res;
            }
            printf("%s\n", recognize(&aut,line));
        }
        return 0;
    }
}