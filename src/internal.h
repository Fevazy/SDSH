#pragma once
#ifndef SDSH_INTERNAL_H
#define SDSH_INTERNAL_H

#include "alloc.h" // IWYU pragma: export
#include "sdsh.h"  // IWYU pragma: export
#include <stdint.h>
#include <stdio.h>  // IWYU pragma: export
#include <stdlib.h> // IWYU pragma: export

#define SDSH_NOT_IMPLEMENTED()                                                 \
    do {                                                                       \
        fprintf(stderr, "%s: %d: %s: SDSH: Not implemented!\n", __FILE__,      \
                __LINE__, __func__);                                           \
        abort();                                                               \
    } while (0)

typedef struct sdsh_archetype_t sdsh_archetype_t;
typedef struct sdsh_component_t sdsh_component_t;

struct sdsh_world_t {
    sdsh_archetype_t **archetypes;
    uint64_t           archetype_count;
    uint64_t           archetype_capacity;
};

struct sdsh_component_t {
    uint64_t size;
    uint64_t align;
};

struct sdsh_archetype_t {
    uint64_t         component_count;
    sdsh_component_t components[];
};

struct sdsh_range_t {};

#endif // SDSH_INTERNAL_H
