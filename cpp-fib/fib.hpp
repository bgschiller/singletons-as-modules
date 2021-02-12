#pragma once
#include <vector>

class Fib
{
public:
    static unsigned int get(unsigned char ix);
private:
    Fib();
    static Fib& instance();
    std::vector<unsigned int> fibs;
};
