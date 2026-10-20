#ifndef CONFIG_H
#define CONFIG_H

enum ReplacementType {
    LRU,
    FIFO,
    MRU,
    RR
    // Optionally add more types later.
};

typedef struct {
    int capacity;
    int block_size;
    int associativity;
    ReplacementType replacement;
} Config;

#endif
