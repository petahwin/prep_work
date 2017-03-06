CC=g++
CFLAGS = -Wall -pedantic

main: main.o Graph.o
	$(CC) -o $@ $(CFLAGS) $^

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean: 
	rm -f *.o main

