CC=gcc
CFLAGS=-Wall -Wextra -fno-stack-protector # special constant that adds compiler flags to gcc command automatically

SRCS := $(wildcard *.c) # all files with .c extension is stored in the SRCS variable
BINS := $(SRCS:%.c=%) # all binary files will have their filenames match their .c counterparts

# Inspired by http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

all: one two three

one: one.o
	$(CC) -o one one.o -lm

two: two.o
	$(CC) -o two two.o

three: three.o
	$(CC) -o three three.o

clean:
	rm -rvf *.o ${BINS}
