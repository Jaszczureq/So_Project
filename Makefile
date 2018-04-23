CC=gcc
CFLAGS=-Wall
main: main.o bst.o read.o functions.o

clean:
	rm -f main main.o bst.o read.o functions.o