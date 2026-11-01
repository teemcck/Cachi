#include "replacement.h"

#include <stdlib.h>

static size_t choose_lru_line(const Cache* cache, size_t start, size_t end) {
    size_t victim = start;
    for (size_t i = start + 1; i < end; ++i) {
        if (cache->cache_lines[i].last_access <
            cache->cache_lines[victim].last_access) {
            victim = i;
        }
    }
    return victim;
}

static size_t choose_fifo_line(const Cache* cache, size_t start, size_t end) {
    size_t victim = start;
    for (size_t i = start + 1; i < end; ++i) {
        if (cache->cache_lines[i].insertion_time <
            cache->cache_lines[victim].insertion_time) {
            victim = i;
        }
    }
    return victim;
}

static size_t choose_mru_line(const Cache* cache, size_t start, size_t end) {
    size_t victim = start;
    for (size_t i = start + 1; i < end; ++i) {
        if (cache->cache_lines[i].last_access >
            cache->cache_lines[victim].last_access) {
            victim = i;
        }
    }
    return victim;
}

static size_t choose_random_line(size_t start, size_t end) {
    return start + (size_t)rand() % (end - start);
}

size_t replacement_choose_victim(const Cache* cache, size_t start, size_t end) {
    switch (cache->config.replacement) {
        case LRU: return choose_lru_line(cache, start, end);
        case FIFO: return choose_fifo_line(cache, start, end);
        case MRU: return choose_mru_line(cache, start, end);
        case RR: return choose_random_line(start, end);
    }
    // An unknown policy defaults to the first line in the set.
    return start;
}
