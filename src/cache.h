#ifndef CACHE_H
#define CACHE_H

#include <stdint.h>
#include "config.h"

typedef struct Cache Cache;

typedef enum {
    CACHE_READ,
    CACHE_WRITE
} CacheOperation;

typedef struct {
    unsigned long long hits;
    unsigned long long misses;
    unsigned long long evictions;
    unsigned long long writebacks;
} CacheStats;

Cache *cache_create(const Config *config);

void cache_access(
    Cache *cache,
    uint64_t address,
    CacheOperation operation
);

CacheStats cache_get_stats(const Cache *cache);

void cache_destroy(Cache *cache);

#endif