#include <stdio.h>
#include "hierarchy.h"

// Currently: caches can be loaded from a config with blank stats.
// To implement: 
// Creating access requests to the cache.
// Storing the active blocks for each cache.
// - each block should have a tag and associated data.
//   - remember that the tag is found 
// - keep track of data needed for replacement policy.

// When cpu requests data, memory address is split into three distinct fields:
// - Block offset, Set index, and tag.

int main(int argc, char* argv[])
{
    // Format ./exe config trace
    // Trace is not yet implemented.

    char path[] = argv[1];
    create_cache_hierarchy(path);
    return 0;
}
