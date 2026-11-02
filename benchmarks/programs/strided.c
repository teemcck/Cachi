
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define N (1024 * 1024)

int main(int argc, char **argv) {
    size_t stride = argc > 1
                  ? (size_t)strtoull(argv[1], NULL, 10)
                  : 1;

    if (stride == 0) return 1;

    uint64_t *data = malloc(N * sizeof(*data));
    if (!data) return 1;

    for (size_t i = 0; i < N; i++)
        data[i] = i;

    uint64_t sum = 0;

    for (size_t repeat = 0; repeat < 10; repeat++) {
        for (size_t i = 0; i < N; i += stride)
            sum += data[i];
    }

    printf("Sum: %llu\n", (unsigned long long)sum);

    free(data);
    return 0;
}
