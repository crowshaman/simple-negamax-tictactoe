# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
CC=gcc
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
CFLAGS=-std=c99 -c

all: ttt

ttt: ttt.o
	$(CC) ttt.o -o ttt -lncurses

ttt.o: ttt.c
	$(CC) $(CFLAGS) ttt.c

clean:
	rm -rf *o *.out ttt