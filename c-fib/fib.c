#include "fib.h"
#include <stdio.h>

Vector fibs;

void fib_init() {
    vector_init(&fibs, 100);
    vector_insert(&fibs, 0);
    vector_insert(&fibs, 1);
}

void fib_fini() {
    vector_free(&fibs);
}

unsigned int fib_get(unsigned char ix) {
    while (fibs.used <= ix) {
        vector_insert(&fibs, fibs.array[fibs.used - 1] + fibs.array[fibs.used - 2]);
    }
    return fibs.array[ix];
}