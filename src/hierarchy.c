#include <stdlib.h>
#include <hierarchy.h>
#include "parse_config.h"

static inline void append_cache(CacheHierarchy* hierarchy, Cache* cache) {
    // Add a cache the the end of the hierarchy and update the number of levels.
    hierarchy->levels[(hierarchy->num_levels)++] = cache;
}

CacheHierarchy* create_cache_hierarchy(const char* input) {
    size_t num_entries;
    Config* configs = parse_config_file(input, &num_entries);
    if (configs == NULL) {
        return NULL;
    }

    // Allocate cache hierarchy.
    CacheHierarchy* hierarchy = (CacheHierarchy*)malloc(sizeof(CacheHierarchy));
    hierarchy->levels = (Cache**)malloc(sizeof(Cache*) * num_entries);
    hierarchy->num_levels = 0;

    // Build caches for each level from config.
    for (size_t i = 0; i < num_entries; ++i) {
        Cache* cache = create_cache(&configs[i]);
        if (cache == NULL) {
            hierarchy = NULL;
            continue;
        }
        append_cache(hierarchy, cache);
    }
    free(configs);
    return hierarchy;
}

void free_cache_hierarchy(CacheHierarchy* hierarchy) {
    for (size_t i = 0; i < hierarchy->num_levels; ++i) {
        // Free individual caches stored in hierarchy.
        cache_destroy(hierarchy->levels[i]);
    }
    // Free hierarchy data structure.
    free(hierarchy);
}