#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <stdint.h>
#include "cache.h"

typedef struct {
    Cache *levels;
    uint8_t num_levels;
} CacheHierarchy;

#endif