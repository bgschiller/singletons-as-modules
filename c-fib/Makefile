CC=gcc
CFLAGS=-I.

fib_example: fib_example.o fib.o vector.o print_fibs.o determine_fib.o
	$(CC) -o fib_example fib_example.o fib.o vector.o print_fibs.o determine_fib.o

clean:
	rm -f *.o fib_example