#include "fib.hpp"

Fib::Fib() {
  fibs.push_back(0);
  fibs.push_back(1);
}

Fib &Fib::instance() {
    static Fib f;
    return f;
}

unsigned int Fib::get(unsigned char ix) {
  Fib& f = instance();
  while (f.fibs.size() <= ix) {
    f.fibs.push_back(f.fibs[f.fibs.size() - 1] + f.fibs[f.fibs.size() - 2]);
  }
  return f.fibs[ix];
}
