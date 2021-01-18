#include "determine_fib.h"
#include "fib.h"

void determine_fib_init() {
    fib_init();
}
void determine_fib_fini() {
    fib_fini();
}

bool determine_fib(unsigned int x) {
    unsigned int f = 0;
    unsigned char ix = 0;
    while ((f = fib_get(ix++)) < x);
    return f == x;
}