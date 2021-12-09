#include "stack_n_array.h"
#include "automaton.h"
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


int main(int argc, char** argv){
    if(argc==1){
        test();
        return 0;
    } else if(argc != 2){
        fprintf(stderr,"Error usage: %s path_to_file\n",argv[0]);
        return 1;
    } else {
        automaton aut = createEmptyAutomaton();
        loadAutomaton(&aut, argv[1]);
        printAutomaton(aut);
        return 0;
    }
}