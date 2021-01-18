# Singletons just wanna be modules

The Devetry book club has been reading through Bob Nystrom's Game Programming Patterns, and we spent a while talking about Singletons. Here's what the Gang of Four book says about them:

> Ensure a class has one instance, and provide a global point of access to it.

Singletons seem to be pretty common in C++ codebases I've used (even if folks are ashamed of them). But I've never reached for one in a Python or Javascript codebase. Why is that?

Let's look at what problem singletons solve for us. We'll look at a small C program to calculate fibonacci numbers. It's broken down into a silly number of separate libraries because it helps us demonstrate the problem. The relevant players are, to wit:

1. `vector.h` defines an automatically growing container. It has `vector_init` and `vector_free` functions to create and release vector values.
2. `fib.h` defines a `fib_get` function that returns the `n`th fibonacci number. It stores all the values it's computed in a vector to speed up subsequent calls. Because the vector is stored on the heap, this modules also includes `fib_init` and `fib_fini` initialization and finalization functions that allocate and clean up the vector.
3. `print_fibs.h` defines a function to print the first `n` fibonacci numbers. It depends on `fib.h`, so it exposes `init` and `fini` functions that wrap the ones in `fib.h`.
4. `determine_fib.h` defines a function that takes a number and tells you whether its fibonacci or not. It also depends on `fib.h`, so it _also_ exposes `init` and `fini` functions that wrap the ones in `fib.h`.
5. _Finally_, `fib_example.c` uses `print_fibs` and `determine_fibs` to
    - print the first 10 fibonacci numbers
    - prompt for a number
    - tell you whether that number is fibonacci or not.

Here's the contents of `fib_example.c`

```c
#include "print_fibs.h"
#include "determine_fib.h"
#include <stdio.h>

int main() {
    /* initialize our dependencies */
    determine_fib_init();
    print_fibs_init();

    print_fibs_to(10);
    printf(
        "tell me a number and I'll "
        "tell you if it's fibonacci: ");
    unsigned int num;
    scanf("%u", &num);
    if (determine_fib(num)) {
        printf("yup, that's a fibonacci number\n");
    } else {
        printf("nope, that's not\n");
    }

    /* finalize the dependencies */ 
    print_fibs_fini();
    determine_fib_fini();
    return 0;
}
```

It's kinda contrived, and a bit silly to spread out the dependencies across so many tiny libraries. If you like, imagine `fib` defines a database connection, and `determine_fib` and `print_fibs` both use that connection in some way.




Not "ensure a class has one instance", but "initialize data once at the start of your program"