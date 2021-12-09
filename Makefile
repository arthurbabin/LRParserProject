CC = gcc -Wall

%.o:%.c
	$(CC) -c $<

all: main.o stack_n_array.o load.o
	$(CC) -o automaton main.o stack_n_array.o load.o

main.o: main.c stack_n_array.h load.h

stack_n_array.o: stack_n_array.c stack_n_array.h

load.o: load.c load.h stack_n_array.h