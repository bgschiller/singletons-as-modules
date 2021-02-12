#include "print_fibs.hpp"
#include "determine_fib.hpp"
#include <stdio.h>

int main() {
    print_fibs_to(10);
    printf("tell me a number and I'll tell you if it's fibonacci: ");
    unsigned int num;
    scanf("%u", &num);
    if (determine_fib(num)) {
        printf("yup, that's a fibonacci number\n");
    } else {
        printf("nope, that's not\n");
    }
    return 0;
}
