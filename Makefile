CC=gcc
CFLAGS=-Wall
minicron: minicron.o libs/bst.o libs/read.o libs/functions.o 

clean:
	rm -f minicron minicron.o libs/bst.o libs/read.o libs/functions.o
