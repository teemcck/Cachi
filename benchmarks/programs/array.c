#include <stdint.h>
#include <stdio.h>

#define N 10000

int main(void) {
    // Volatile keyword prevents compiler optimizations here.
    volatile uint64_t data[N] = {0};

    for (int i = 0; i < N; i++) {
        data[i] = i;
    }

    for (int i = 0; i < N; i++) {
        data[i] += 1;
    }

    printf("%llu\n", (unsigned long long)data[0]);
    return 0;
}