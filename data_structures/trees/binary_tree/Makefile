CC=gcc
CFLAGS = -Wall -pedantic -std=c99

main: main.o BinaryTree.o
	$(CC) -o $@ $(CFLAGS) $^

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean: 
	rm -f *.o main

