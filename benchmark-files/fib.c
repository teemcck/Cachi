
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

static uint64_t fibonacci_recursive(int n) {
    if (n <= 1) return (uint64_t)n;

    return fibonacci_recursive(n - 1)
         + fibonacci_recursive(n - 2);
}

static uint64_t fibonacci_iterative(int n) {
    uint64_t a = 0, b = 1;

    for (int i = 0; i < n; i++) {
        uint64_t next = a + b;
        a = b;
        b = next;
    }

    return a;
}

int main(int argc, char **argv) {
    int n = argc > 1 ? atoi(argv[1]) : 30;

    if (n < 0 || n > 40) return 1;

    printf("Recursive: %llu\n",
           (unsigned long long)fibonacci_recursive(n));

    printf("Iterative: %llu\n",
           (unsigned long long)fibonacci_iterative(n));

    return 0;
}
