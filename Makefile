CC = gcc -Wall

%.o:%.c
	$(CC) -c $<

all: main.o stack_n_array.o automaton.o
	$(CC) -o automaton main.o stack_n_array.o automaton.o

main.o: main.c stack_n_array.h automaton.h

stack_n_array.o: stack_n_array.c stack_n_array.h

automaton.o: automaton.c automaton.h stack_n_array.h