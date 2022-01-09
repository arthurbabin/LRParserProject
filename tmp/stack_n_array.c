#include "stack_n_array.h"
#include <stdlib.h>
#include <stdio.h>

//STACK

struct stack_abs{
    value v;
    struct stack_abs* next;
};

/*
@requires nothing
@assigns nothing
@returns an empty stack
*/
stack createEmptyStack(){
    return NULL;
};

/*
@requires nothing
@assigns nothing
@returns if the stack is empty
*/
int stackIsEmpty(stack s){
    return s==NULL;
};

/*
@requires nothing
@assigns stack
@ensures the insertion of value e at the top of the stack s
*/
void push(stack* s, value e){
    stack new = malloc(sizeof(struct stack_abs));
    new->v = e;
    new->next = *s;
    *s = new;
};

/*
@requires nothing
@assigns stack
@returns the value of the first element of the stack
*/
value pop(stack* s){
    if(stackIsEmpty(*s)){
        perror("pop on empty stack");
        exit(1);
    }
    value res = (*s)->v;
    stack tmp = *s;
    *s = (*s)->next;
    free(tmp);
    return res;
};

/*
@requires non empty stack
@assigns nothing
@returns the value of the element at the top of the stack
*/
value head(stack s){
    return s->v;
}

/*
@requires non cyclic stack
@assigns nothing
@ensures deletion of the memory allocated for the stack
*/
void deleteStack(stack *s){
    while(!stackIsEmpty(*s)){
        stack tmp =(*s)->next;
        free(*s);
        *s = tmp;
    }
}

/*
@requires non cyclic stack
@assigns nothing
@ensures the display of the stack
*/
void printStack(stack s){
    stack rec = s;

    //read through the elements of the non cyclic stack until the stack is empty
    while(!stackIsEmpty(rec)){
        printf("[%i]->",rec->v);
        rec = rec->next;
    }
    printf("[]\n");
}

//ARRAY
/*
@requires size>0
@assigns nothing
@returns an empty array of size size
*/
value* createEmptyArray(int size){
    value *tab;
    tab = (value *) malloc(size * sizeof(value));
    return tab;
}

/*
@requires nothing
@assigns tab
@ensures the deletion of memory allocated to the tab
*/
void deleteArray(value* tab){
    free(tab);
}

/*
@requires array tab of size=h*w
@assigns nothing
@ensures the display of the array as a matrix h*w
*/
void printArray(char* header, value* tab, int h, int w){
    int i = 0;
    int size = h*w;
    printf("%s\n",header);
    //read through the elements of tab size times, while terminates
    while(i<size){
        if(i%w==0){
            printf("\n\t|%3i|",tab[i]);
        } else {
            printf("%3i|",tab[i]);
        }
        i+=1;
    }
    printf("\n\n");
}