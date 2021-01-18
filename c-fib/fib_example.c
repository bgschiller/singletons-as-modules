#include "print_fibs.h"
#include "determine_fib.h"
#include <stdio.h>

int main() {
    determine_fib_init();
    print_fibs_init();

    print_fibs_to(10);
    printf("tell me a number and I'll tell you if it's fibonacci: ");
    unsigned int num;
    scanf("%u", &num);
    if (determine_fib(num)) {
        printf("yup, that's a fibonacci number\n");
    } else {
        printf("nope, that's not\n");
    }
    print_fibs_fini();
    determine_fib_fini();
    return 0;
}