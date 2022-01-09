#include "stack_n_array.h"
#include "load.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>

// TEST FUNCTIONS TO DEBUG
//
// char path_to_test_automaton[] = "LR1/word_bis.aut"
//
// void testStack(){
//     printf("> TESTS STACK :\n");
//     stack a = createEmptyStack();
//     printf("    -test createEmptyStack(): ");
//     printStack(a);
//     push(&a,4);
//     push(&a,5);
//     printf("    -test push : ");
//     printStack(a);
//     printf("    -test pop: %i, %i\n",pop(&a),pop(&a));
//     printf("\n");
// }

// void testArray(){
//     value* tab = createEmptyArray(10);
//     tab[2]=2;
//     printArray("> TESTS ARRAY :",tab,2,5);
//     printf("\n");
// }

// void testAutomaton(char* path_to_automaton){
//     automaton aut = createEmptyAutomaton();
//     loadAutomaton(&aut, path_to_automaton);
//     printf("> TESTS AUTOMATON :\n\n");
//     printAutomaton(aut);
// }

// void test(char* path_to_automaton){
//     testStack();
//     testArray();
//     testAutomaton(path_to_automaton);
// }
// void dispUserInput(char buf[]){
//     printf("= [");
//     for(int i=0;i<256;i+=1){
//         if(buf[i]==0){
//             i=256;
//             printf(" \\n]\n");
//         } else {
//             printf("%4i,", buf[i]);
//         }
//     }
// }

/*
@requires an array of 256 characters
@assigns this array
@ensures the store of the user input in this array
*/
void getUserInput(char buf[]){
    fgets(buf, 256, stdin);
    sscanf(buf, "%s", buf);
}

/*
@requires user input ends with EOF (character 0)
@assigns the stack
@ensures the convertion of the input into a stack
*/
int fillStackLineFromUserInput(stack* line, char* user_input){
    int cursor = 0;
    int result = 0;
    /*
    Either terminates when cursor reaches 256 or when user_input[cursor]==0
    */
    while(cursor<256 && !result){
        if(user_input[cursor]==0){
            result = 1;
        }
        cursor+=1;
    }

    if(!result){
        perror("user input too long (max 256 characters including \\n)");
        return 1;
    }

    push(line,0);//push end of char array into the stack
    push(line, 10);//push line break into the stack
    //push user input into the stack
    for(int i = (cursor-2); i>=0; i--){
        push(line,user_input[i]);
    }
    return 0;
}


int main(int argc, char** argv){
    char user_input[256];//variable to store the user input line
    if(argc != 2){
        //wrong usage
        fprintf(stderr,"Error usage: %s path_to_aut_file\n",argv[0]);
        return 1;
    } else {
        //create empty automaton and stack
        automaton aut = createEmptyAutomaton();
        stack line;

        //load informations of the *.aut file into the automaton
        loadAutomaton(&aut, argv[1]);
        printf("File \"%s\" correctly read, please enter your inputs [^C to escape] :\n",argv[1]);
        
        /*
        infinite loop until SIGINT signal is catched
        each loop corresponds to the recognition of a line entered by the user
        */
        while(1){
            getUserInput(user_input);
            line = createEmptyStack();
            int res = fillStackLineFromUserInput(&line, user_input);
            if(res!=0){
                //wrong input detected
                return res;
            }
            
            recognize(&aut,line);//display result of the recognition
            // deleteStack(&line);
        }
        return 0;
    }
}