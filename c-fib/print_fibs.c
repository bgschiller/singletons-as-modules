#include "print_fibs.h"
#include "fib.h"
#include <stdio.h>

void print_fibs_init() {
    fib_init();
}
void print_fibs_fini() {
    fib_fini();
}

void print_fibs_to(unsigned char limit) {
    for (unsigned char ix = 0; ix < limit; ix ++) {
        printf("fib(%d) is %d\n", ix, fib_get(ix));
    }
}
