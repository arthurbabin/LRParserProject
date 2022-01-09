#include "load.h"
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

/*
@requires nothing
@assigns nothing
@returns an empty automaton
*/
automaton createEmptyAutomaton(){
    automaton new = malloc(sizeof(struct automaton_abs));
    return new;
}

/*
@requires an empty automaton and a buffer corresponding to an *.aut file
@assigns automaton parameters (nb_states, length_shift, length_connect, action, reduce, shift, connect)
@returns a loaded
*/
void loadInfosFromBuffer(automaton* aut, unsigned char buffer[]){
    //use of an int to save the position in the file while loading all the parameters of the automaton
    int reader = 2; //number of states starts at buffer[2]
    int nb_states = 0;

    //reads the first line of the buffer and the while terminates when the character 10 (line break)
    while(buffer[reader]!=10){
        nb_states = nb_states*10 + ( (int)buffer[reader] -48);
        reader+=1;
    }

    //load number of states
    (*aut)->nb_states = nb_states;

    //load action array
    reader+=1;
    int length_action = 128 * ((*aut)->nb_states);
    (*aut)->action = createEmptyArray(length_action);
    for(int j=0;j<length_action;j+=1){
        ((*aut)->action)[j] = buffer[reader+j];
    }

    reader += length_action + 1;

    //load reduce array
    (*aut)->reduce = createEmptyArray((*aut)->nb_states * 2);
    for(int j=0;j<((*aut)->nb_states);j+=1){
        ((*aut)->reduce)[j] = buffer[reader+j];
    }
    reader += (*aut)->nb_states + 1;
    for(int j=0;j<((*aut)->nb_states);j+=1){
        ((*aut)->reduce)[ (*aut)->nb_states + j ] = buffer[reader+j];
    }

    reader += (*aut)->nb_states + 1;

    //load length_shift 
    (*aut)->length_shift = 0;
    /*
    in the buffer the first apparition of 173,173,173 corresponds to the end of shift
    increment length_shift by 3 until 173,173,173 is found (while terminates because the buffer corresponds to the *.aut file)
    */
    while(
    buffer[ reader + ((*aut)->length_shift) ]!=173 && 
    buffer[ reader + ((*aut)->length_shift) + 1 ]!=173 && 
    buffer[ reader + ((*aut)->length_shift) + 2 ]!=173){
        ((*aut)->length_shift)+=3;
    }

    //load shift
    (*aut)->shift = createEmptyArray((*aut)->length_shift);
    for(int j=0;j<((*aut)->length_shift);j+=1){
        ((*aut)->shift)[j] = buffer[reader+j];
    }
    reader += (*aut)->length_shift + 3;

    //load length_connect
    (*aut)->length_connect = 0;
    /*
    in the buffer the second apparition of 173,173,173 corresponds to the end of connect
    increment length_connect by 3 until 173,173,173 is found (while terminates because the buffer corresponds to the *.aut file)
    */
    while(
    buffer[ reader + ((*aut)->length_connect) ]!=173 && 
    buffer[ reader + ((*aut)->length_connect) + 1 ]!=173 && 
    buffer[ reader + ((*aut)->length_connect) + 2 ]!=173){
        ((*aut)->length_connect)+=3;
    }
    //load connect
    (*aut)->connect = createEmptyArray((*aut)->length_connect);
    for(int j=0;j<((*aut)->length_connect);j+=1){
        ((*aut)->connect)[j] = buffer[reader+j];
    }
}

/*
@requires a non-empty automaton
@assigns free all memory corresponding to this automaton
@returns nothing
*/
void deleteAutomaton(automaton* aut){
    deleteArray((*aut)->action);
    deleteArray((*aut)->reduce);
    deleteArray((*aut)->shift);
    deleteArray((*aut)->connect);
    free(*aut);
}

/*
@requires a non-empty automaton
@assigns nothing
@ensures the display of the automaton
*/
void printAutomaton(automaton aut){
    printArray("    > ACTION", aut->action,128,aut->nb_states);
    printArray("    > REDUCE", aut->reduce,2,aut->nb_states);
    printArray("    > SHIFT", aut->shift,aut->length_shift/3,3);
    printArray("    > CONNECT", aut->connect,aut->length_connect/3,3);
}

/*
@requires a path corresponding to an *.aut file correctly written
@assigns automaton parameters
@ensures a loaded automaton with the parameters corresponding to the *.aut file
*/
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
            perror("buffer init");
            return;
        }
        fread(buffer,sizeof(buffer),1,fin);
        loadInfosFromBuffer(aut,buffer);
    }
}

/*
@requires an array corresponding to the shift or the connect function
@assigns nothing
@returns the value of fn(state,character) where fn is shift or connect
*/
int findShiftOrConnectNumber(value* array, int length_shift, value state, value character){
    for(int i=0;i<length_shift;i++){
        if(array[i]==state && array[i+1]==character){
            return array[i+2];
        }
    }
    perror("shift or connect number not found");
    return -1;
}

/*
@requires a non-empty automaton
@assigns user_input
@ensures display of "Accepted" if the input is recognized by the automaton, 
display of "Rejected: (position where it is rejected" otherwise
*/
int recognize(automaton* aut, stack user_input){
    stack sta = createEmptyStack(); //stack for the states
    char* rejected = (char*) malloc(25 * sizeof(char));; //string to store the possible rejected informations
    value curr_char,curr_state; //values to store current character and state
    int position = 0;
    push(&sta,0); //push state 0 to begin
    /*
    *.aut file is correctly written so there is no infinite loop if we follow the given recognize algorithm 
    */
    while(!stackIsEmpty(user_input) && !stackIsEmpty(sta)){
        curr_char = pop(&user_input);
        position += 1;
        curr_state = head(sta);
        //collect action_number from the action array of the loaded automaton
        int action_number = ((*aut)->action)[curr_state * 128 + curr_char];
        //switch case corresponding to the possible actions
        switch (action_number) {

            case 1:{
                //if it is 1 the input is accepted
                printf("Accepted\n");
                return 1;
                break;
            }

            case 2: {
                // shift
                int shift_number = findShiftOrConnectNumber((*aut)->shift,(*aut)->length_shift, curr_state,curr_char);
                push(&sta,shift_number);
                break;
            }
            case 3: {
                // reduce
                int reduce_number = (*aut)->reduce[curr_state];
                int reduce_char = (*aut)->reduce[curr_state +(*aut)->nb_states];
                for(int i=0;i<reduce_number;i+=1){
                    pop(&sta);
                }
                // connect
                int connect_state = head(sta);
                int connect_number = findShiftOrConnectNumber((*aut)->connect,(*aut)->length_connect,connect_state,reduce_char);
                push(&sta, connect_number);
                push(&user_input, curr_char);
                position -= 1;
                break;
            }
            default: {
                // reject
                switch(position){
                    case 1:
                        sprintf(rejected, curr_char==10?"Rejected: empty":"Rejected: 1st character");
                        break;
                    case 2:
                        sprintf(rejected, "Rejected: 2nd character");
                        break;
                    case 3:
                        sprintf(rejected, "Rejected: 3rd character");
                        break;
                    default:
                        sprintf(rejected, "Rejected: %ith character",position);
                        break;
                }
                printf("%s\n",rejected);
                free(rejected);
                return 0;
            }
        }
    }
    sprintf(rejected, "Rejected:  empty");
    printf("%s\n",rejected);
    free(rejected);
    return 0;
}