CC=gcc
CFLAGS=-Wall -Wextra -I. # special constant that adds compiler flags to gcc command automatically

# Inspired by http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

all: one two three

one: program1.o 
	$(CC) -o program1 program1.c

two: program2.o
	$(CC) -o program2 program2.c

three: program3.o
	$(CC) -o program3 program3.c

clean:
	rm -f *.o program1 program2 program3 
