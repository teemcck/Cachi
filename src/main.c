#include <stdio.h>
#include "hierarchy.h"

// Cachi: a Multilevel Processor Cache Simulator.
// Author: Tristan McCaskill
// Date (M/D/Y): 11/1/26
// References: https://www.cs.cornell.edu/courses/cs3410/2026sp/notes/caches

int main(int argc, char* argv[])
{
    // Format ./exe config trace
    // Trace is not yet implemented.

    char path[] = argv[1];
    create_cache_hierarchy(path);
    return 0;
}
