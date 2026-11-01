#ifndef CONFIG_H
#define CONFIG_H

typedef enum {
    LRU,
    FIFO,
    MRU,
    RR
    // Optionally add more types later.
} ReplacementType;

typedef struct { // Measured in:
    int capacity; // Bytes
    int block_size; // Bytes per block
    int associativity; // Blocks (ways) per set
    ReplacementType replacement;
} Config;

#endif
