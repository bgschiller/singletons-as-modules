#include "print_fibs.hpp"

#include <stdio.h>

#include "fib.hpp"

void print_fibs_to(unsigned char limit) {
  for (unsigned char ix = 0; ix < limit; ix++) {
    printf("fib(%d) is %d\n", ix, Fib::get(ix));
  }
}
