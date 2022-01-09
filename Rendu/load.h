#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "stack_n_array.h"

typedef struct automaton_abs* automaton;

/*
@requires nothing
@assigns nothing
@returns an empty automaton
*/
automaton createEmptyAutomaton();

/*
@requires a path corresponding to an *.aut file correctly written
@assigns automaton parameters
@ensures a loaded automaton with the parameters corresponding to the *.aut file
*/
void loadAutomaton(automaton*, char*);


/*
@requires a non-empty automaton
@assigns nothing
@ensures the display of the automaton
*/
void printAutomaton(automaton aut);

/*
@requires a non-empty automaton
@assigns free all memory corresponding to this automaton
@returns nothing
*/
void deleteAutomaton(automaton*);

/*
@requires a non-empty automaton
@assigns user_input
@ensures display of "Accepted" if the input is recognized by the automaton, 
display of "Rejected: (position where it is rejected" otherwise
*/
int recognize(automaton*, stack);