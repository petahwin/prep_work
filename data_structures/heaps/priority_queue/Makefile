CC=gcc
CFLAGS = -Wall -pedantic -std=c99

main: main.o PriorityQueue.o
	$(CC) -o $@ $(CFLAGS) $^

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean: 
	rm -f *.o main

