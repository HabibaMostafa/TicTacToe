CC = gcc
CFLAGS = -Wall -ansi

all: gameCLI.o
	$(CC) gameCLI.o -g -o gameCLI

a4.o: gameCLI.c gameCLI.h
	$(CC) $(CFLAGS) gameCLI.c -g -c -o gameCLI.o

run: all
	./gameCLI
    
clean: 
	rm gameCLI *.o *.bin