CC=gcc
CFLAGS=-I. -g

fib_example: fib_example.o fib.o vector.o print_fibs.o determine_fib.o
	$(CC) -o fib_example fib_example.o fib.o vector.o print_fibs.o determine_fib.o

clean:
	rm -f *.o fib_example

check_leaks: fib_example
	# pipe in a number, as fib_example expects a single line of stdin
	echo 8 | valgrind --track-origins=yes --leak-check=full ./fib_example
