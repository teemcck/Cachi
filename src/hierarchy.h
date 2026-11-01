#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <stdint.h>
#include "config.h"
#include "cache.h"

/**
 * @brief Chain Cache Hierarchy structure.
 * 
 * Stores caches in levels, formatted as L[index+1].
 * Ex: L[0] relates to L1 cache.
 */
typedef struct {
    Cache** levels;
    size_t num_levels;
} CacheHierarchy;

/**
 * @brief Dynamically alocates cache hierarchy structure.
 * 
 * Accepts path to hierarchy config file.
 */
CacheHierarchy* create_cache_hierarchy(const char* input);

/**
 * @brief Deallocates cache hierarchy structure and associated caches.
 */
void free_cache_hierarchy(CacheHierarchy* hierarchy);

/**
 * @brief Creates a request to cache hierarchy.
 * 
 * Requests provide referenced memory address and Read/Write.
 */
void hierarchy_access(CacheHierarchy* hierarchy, CacheOperation operation) {
    // Make a request to the L1 cache, then L2, etc.
    
}

#endif