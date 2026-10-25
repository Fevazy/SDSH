#include "alloc.h"
#include <stdint.h>
#include <stdlib.h>

void *sdsh_alloc(uint64_t size) {
    if (size == 0)
        return NULL;
    return malloc(size);
}

void *sdsh_realloc(void *p, uint64_t size) {
    return realloc(p, size);
}

void sdsh_free(void *p) {
    free(p);
}
