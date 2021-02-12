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

It's kinda contrived, and a bit silly to spread out the dependencies across so many tiny libraries. If you like, imagine `fib` defines a database connection, and `determine_fib` and `print_fibs` both use that connection in some way. Let's visualize part of the dependency tree (skipping vector.h): `fib_example` depends on both `print_fibs` and `determine_fibs`. Both of _those_ libraries depend on `fib`.

```
         fib
        /    \
       /      \
print_fibs  determine_fib
       \      /
        \    /
      fib_example
```

This dependency structure isn't usually a problem. But in this case, `fib` has initialize and finalize functions that should be called exactly once each, at the start and end of the program. That's the contract `fib` has with any code that wants to use it. `print_fibs` and `determine_fib` honor this request by delegating responsibility to their own callers. In the spirit of hiding their implementation details, each of those libraries exposes their own init and fini functions.

Now the problem appears: `fib_example` dutifully invokes _both_ `print_fibs_init` and `determine_fib_init`. That means we have two calls to `fib_init` and a memory leak. Check out what valgrind has to say about this program:

```
HEAP SUMMARY:
    in use at exit: 400 bytes in 1 blocks
  total heap usage: 4 allocs, 3 frees, 5,920 bytes allocated

400 bytes in 1 blocks are definitely lost in loss record 1 of 1
   at 0x4839809: malloc (vg_replace_malloc.c:307)
   by 0x4012DD: vector_init (vector.c:4)
   by 0x401212: fib_init (fib.c:7)
   by 0x40144F: determine_fib_init (determine_fib.c:5)
   by 0x401187: main (fib_example.c:6)
```

A memory leak! The second time we call fib_init, we lose the only reference the memory we got from the first call. Even though fib_fini also gets called twice, we can't clean up a vector when we've lost the only pointer to it.

Whose fault is this? Certainly not `fib`, whose contract we broke by invoking `fib_init` more than once. (Although, a better library design would make `fib_init` safe to call multiple times, checking if a vector was already allocated before asking for a new one). You could make an argument that the fault lies with `print_fibs` and `determine_fib`, since they tried to encapsulate the `fib` library without fully insulating us from the contract that library makes. The C ethos would argue that `fib_example.c` is responsible for its dependencies.

The problem is "I want to run some initialization code before anyone can call these functions". A library exposing functions for retrieving items from a database might wish to initialize its connection first. A package that interfaces with some other daemon process might want to ensure the other process is running. When you consider threading, it's not necessarily trivial to ensure the initialization code runs at the right time and exactly once. How do other compiled languages solve this?
- Go allows defining `init` functions in each package, which are invoked exactly once before `main`.
- Rust has a `lazy_static` macro (in a crate, not built-in) that invokes init code on the first use of a value.
- C# has static constructors that run before the first instance of a class is created. It looks like the runtime tracks when these are running to avoid issues with threads (I think. I don't know a lot about C#.)
- C++ uses the singleton pattern and puts initialization code in the private constructor.

This article being (ostensibly) about the singleton pattern, let's examine the C++ solution to this problem. Take a look at the cpp-fib code. The `determine_fib` and `print_fibs` headers are far simpler—no initialization or finalization code! We were able to get rid of those functions because fibs.hpp is self-sufficient.

Not "ensure a class has one instance", but "initialize data once at the start of your program"
