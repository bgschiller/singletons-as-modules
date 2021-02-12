#pragma once
#include "vector.h"

extern Vector fibs;

// Initialize memory for the module. To be called exactly once, before any calls to fib_get
void fib_init();
// Clean up memory for the module. To be called exactly once, after any calls to fib_get
void fib_fini();

// retrieve the ix'th fibonacci number
unsigned int fib_get(unsigned char ix);
