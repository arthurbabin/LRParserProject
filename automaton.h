#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "stack_n_array.h"

typedef struct automaton_abs* automaton;

automaton createEmptyAutomaton();

void getGroupMarkers(automaton* aut, unsigned char buffer[]);

automaton createEmptyAutomaton();

void loadAutomaton(automaton*, char*);

void printAutomaton(automaton aut);