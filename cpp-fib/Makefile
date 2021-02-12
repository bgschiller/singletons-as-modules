fib_example: *.cpp *.hpp
	g++ -o fib_example *.cpp

clean:
	rm -f *.o fib_example

check_leaks: fib_example
	# pipe in a number, as fib_example expects a single line of stdin
	echo 8 | valgrind --track-origins=yes --leak-check=full ./fib_example
