#ifndef REPLACEMENT_H
#define REPLACEMENT_H

#include "cache.h"

/* Selects a victim line from the half-open range [start, end). */
size_t replacement_choose_victim(const Cache* cache, size_t start, size_t end);

#endif
