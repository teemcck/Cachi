#include "cache.h"
#include "replacement.h"
#include <stdlib.h>
#include <stdint.h>

static inline int is_power_of_two(size_t value) {
    return value != 0 && (value & (value - 1)) == 0;
}

static inline uint8_t log2_power_of_two(size_t value) {
    uint8_t bits = 0;
    while (value > 1) {
        value >>= 1;
        ++bits;
    }
    return bits;
}

static size_t find_invalid_line(const Cache* cache, size_t start, size_t end) {
    for (size_t i = start; i < end; ++i) {
        if (!cache->cache_lines[i].valid) return i;
    }
    return SIZE_MAX;
}

/**
 * @brief Allocates and initializes a cache.
 *
 * @return Cache pointer, or NULL if configuration is invalid
 *         or allocation fails.
 */
Cache* create_cache(const Config* config) {
    if (config == NULL || config->capacity <= 0 ||
        config->block_size <= 0 || config->associativity <= 0) {
        return NULL;
    }

    const size_t capacity = (size_t)config->capacity;
    const size_t block_size = (size_t)config->block_size;
    const size_t associativity = (size_t)config->associativity;
    // Block size must be byte representable and evenly divide capacity.
    if (!is_power_of_two(block_size) || capacity % block_size != 0) return NULL;

    const size_t num_blocks = capacity / block_size;
    // Associativity must evenly divide the number of blocks.
    if (num_blocks % associativity != 0) return NULL;

    const size_t num_sets = num_blocks / associativity;
    // Number of sets must be byte representable.
    if (!is_power_of_two(num_sets)) return NULL;

    const uint8_t index_bits = log2_power_of_two(num_sets);
    const uint8_t offset_bits = log2_power_of_two(block_size);
    if ((size_t)index_bits + offset_bits > ADDRESS_BITS) return NULL;

    // Allocate cache structure.
    Cache* cache = calloc(1, sizeof *cache);
    if (cache == NULL) return NULL;

    // Assign useful cache properties.
    cache->config = *config;
    cache->num_blocks = num_blocks;
    cache->num_sets = num_sets;
    cache->set_index_bits = index_bits;
    cache->offset_bits = offset_bits;
    cache->tag_bits = (uint8_t)(ADDRESS_BITS - index_bits - offset_bits);

    // Allocate cache blocks.
    cache->cache_lines = calloc(num_blocks, sizeof *cache->cache_lines);
    if (cache->cache_lines == NULL) {
        free(cache);
        return NULL;
    }

    return cache;
}

void cache_access(    
    Cache *cache,
    uint64_t address,
    CacheOperation operation
) {
    if (cache == NULL) return;

    // From address, find the set index, tag, offset.
    const uint64_t set_mask = (uint64_t)(cache->num_sets - 1);

    const uint64_t set_index =
        (address >> cache->offset_bits) & set_mask;
    const uint64_t tag =
        address >> (cache->offset_bits + cache->set_index_bits);

    const size_t ways = (size_t)cache->config.associativity;
    const size_t start = (size_t)set_index * ways;
    const size_t end = start + ways;
    const uint64_t now = ++cache->access_time;

    // Search the whole set before deciding this is a miss.
    for (size_t i = start; i < end; ++i) {
        CacheLine* line = &cache->cache_lines[i];
        if (line->valid && line->tag == tag) {
            ++cache->stats.hits;
            line->last_access = now;
            if (operation == CACHE_WRITE) line->dirty = true;
            return;
        }
    }

    ++cache->stats.misses;
    size_t victim_index = find_invalid_line(cache, start, end);
    if (victim_index == SIZE_MAX) {
        victim_index = replacement_choose_victim(cache, start, end);
        CacheLine* victim = &cache->cache_lines[victim_index];
        ++cache->stats.evictions;
        if (victim->dirty) ++cache->stats.writebacks;
    }

    CacheLine* line = &cache->cache_lines[victim_index];
    line->tag = tag;
    line->valid = true;
    line->dirty = operation == CACHE_WRITE;
    line->insertion_time = now;
    line->last_access = now;
}

void cache_destroy(Cache* cache) {
    if (cache == NULL) return;
    free(cache->cache_lines);
    free(cache);
}
