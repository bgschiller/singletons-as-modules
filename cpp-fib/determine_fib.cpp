#include "determine_fib.hpp"

#include "fib.hpp"

bool determine_fib(unsigned int x) {
  unsigned int f = 0;
  unsigned char ix = 0;
  while ((f = Fib::get(ix++)) < x);
  return f == x;
}
