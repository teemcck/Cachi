#ifndef PARSE_CONFIG_H
#define PARSE_CONFIG_H

#include <stddef.h>
#include "config.h"

/*
 * Returns a heap-allocated array; the caller frees it.
 */
Config* parse_config_file(const char *path, size_t *count);

#endif
