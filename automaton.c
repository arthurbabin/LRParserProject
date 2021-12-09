#include "automaton.h"
#include "stack_n_array.h"

struct automaton_abs {
    int nb_states;
    int length_shift;
    int length_connect;
    value* action;
    value* reduce;
    value* shift;
    value* connect;
};

automaton createEmptyAutomaton(){
    automaton new = malloc(sizeof(struct automaton_abs));
    return new;
}

void getGroupMarkers(automaton* aut, unsigned char buffer[]){
    int reader = 2;
    int nb_states = 0;
    while(buffer[reader]!=10){
        nb_states = nb_states*10 + ( (int)buffer[reader] -48);
        reader+=1;
    }
    (*aut)->nb_states = nb_states;

    reader+=1;
    int length_action = 128 * ((*aut)->nb_states);
    (*aut)->action = createEmptyArray(length_action);
    for(int j=0;j<length_action;j+=1){
        ((*aut)->action)[j] = buffer[reader+j];
    }

    reader += length_action + 1;
    (*aut)->reduce = createEmptyArray((*aut)->nb_states * 2);
    for(int j=0;j<((*aut)->nb_states);j+=1){
        ((*aut)->reduce)[j] = buffer[reader+j];
    }
    reader += (*aut)->nb_states + 1;
    for(int j=0;j<((*aut)->nb_states);j+=1){
        ((*aut)->reduce)[ (*aut)->nb_states + j ] = buffer[reader+j];
    }

    reader += (*aut)->nb_states + 1;
    (*aut)->length_shift = 0;
    while(
    buffer[ reader + ((*aut)->length_shift) ]!=173 && 
    buffer[ reader + ((*aut)->length_shift) + 1 ]!=173 && 
    buffer[ reader + ((*aut)->length_shift) + 2 ]!=173){
        ((*aut)->length_shift)+=3;
    }
    (*aut)->shift = createEmptyArray((*aut)->length_shift);
    for(int j=0;j<((*aut)->length_shift);j+=1){
        ((*aut)->shift)[j] = buffer[reader+j];
    }
    reader += (*aut)->length_shift + 3;
    (*aut)->length_connect = 0;
    while(
    buffer[ reader + ((*aut)->length_connect) ]!=173 && 
    buffer[ reader + ((*aut)->length_connect) + 1 ]!=173 && 
    buffer[ reader + ((*aut)->length_connect) + 2 ]!=173){
        ((*aut)->length_connect)+=3;
    }
    (*aut)->connect = createEmptyArray((*aut)->length_connect);
    for(int j=0;j<((*aut)->length_connect);j+=1){
        ((*aut)->connect)[j] = buffer[reader+j];
    }
}

void printAutomaton(automaton aut){
    printArray("    > ACTION", aut->action,128,aut->nb_states);
    printArray("    > REDUCE", aut->reduce,2,aut->nb_states);
    printArray("    > SHIFT", aut->shift,aut->length_shift/3,3);
    printArray("    > CONNECT", aut->connect,aut->length_connect/3,3);
}

void loadAutomaton(automaton *aut, char* path_to_automaton){
    struct stat properties;
    int verif = lstat(path_to_automaton,&properties);
    if(verif==-1){
        perror("lstat");
        return;
    }
    off_t size = properties.st_size;
    if (size > 0){
        FILE *fin; 
        fin=fopen(path_to_automaton, "rb");
        unsigned char buffer[size];
        if (buffer==NULL){
            perror("malloc");
            return;
        }
        fread(buffer,sizeof(buffer),1,fin);
        // int nb_states, length_shift, length_connect;
        // value* action, *reduce, *shift, *connect;
        // getGroupMarkers(&nb_states, &length_shift, &length_connect, &action, &reduce, &shift, &connect, buffer);
        getGroupMarkers(aut,buffer);
    }
}