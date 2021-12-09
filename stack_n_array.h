typedef int value;
typedef struct stack_abs* stack;

stack createEmptyStack();

int stackIsEmpty(stack);

void push(stack*, value);

value pop(stack*);

value head(stack);

void printStack(stack);

value* createEmptyArray(int);

void printArray(char*, value*, int, int);