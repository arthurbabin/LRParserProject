typedef int value;
typedef struct stack_abs* stack;

/*
@requires nothing
@assigns nothing
@returns an empty stack
*/
stack createEmptyStack();

/*
@requires nothing
@assigns nothing
@returns if the stack is empty
*/
int stackIsEmpty(stack);

/*
@requires nothing
@assigns stack
@ensures the insertion of value e at the top of the stack s
*/
void push(stack*, value);

/*
@requires nothing
@assigns stack
@returns the value of the first element of the stack and pop it out
*/
value pop(stack*);

/*
@requires non empty stack
@assigns nothing
@returns the value of the element at the top of the stack
*/
value head(stack);

/*
@requires non cyclic stack
@assigns nothing
@ensures deletion of the memory allocated for the stack
*/
void deleteStack(stack*);

/*
@requires non cyclic stack
@assigns nothing
@ensures the display of the stack
*/
void printStack(stack);

/*
@requires size>0
@assigns nothing
@returns an empty array of size size
*/
value* createEmptyArray(int);

/*
@requires nothing
@assigns tab
@ensures the deletion of memory allocated to the tab
*/
void deleteArray(value*);

/*
@requires array tab of size=h*w
@assigns nothing
@ensures the display of the array as a matrix h*w
*/
void printArray(char*, value*, int, int);