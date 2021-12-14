#include "stack_n_array.h"
#include <stdlib.h>
#include <stdio.h>

//STACK

struct stack_abs{
    value v;
    struct stack_abs* next;
};

stack createEmptyStack(){
    return NULL;
};

int stackIsEmpty(stack s){
    return s==NULL;
};

void push(stack* s, value e){
    stack new = malloc(sizeof(struct stack_abs));
    new->v = e;
    new->next = *s;
    *s = new;
};

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

value head(stack s){
    return s->v;
}

void printStack(stack s){
    stack rec = s;
    while(!stackIsEmpty(rec)){
        printf("[%i]->",rec->v);
        rec = rec->next;
    }
    printf("[]\n");
}

//ARRAY
value* createEmptyArray(int size){
    value *tab;
    tab = (value *) malloc(size * sizeof(value));
    return tab;
}

void printArray(char* header, value* tab, int h, int w){
    int i = 0;
    int size = h*w;
    printf("%s\n",header);
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

