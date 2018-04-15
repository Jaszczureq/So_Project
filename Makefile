CC=gcc
CFLAGS=-Wall
main: main.o bst.o read.o

clean:
	rm -f main main.o bst.o read.o