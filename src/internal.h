#pragma once
#ifndef SDSH_INTERNAL_H
#define SDSH_INTERNAL_H

#include <stdio.h>  // IWYU pragma: export
#include <stdlib.h> // IWYU pragma: export
#include "sdsh.h"   // IWYU pragma: export
#include "alloc.h"  // IWYU pragma: export


#define SDSH_NOT_IMPLEMENTED()                                 \
    do {                                                       \
        fprintf(stderr, "%s: %d: %s: SDSH: Not implemented!\n",\
                __FILE__, __LINE__, __func__);                 \
        abort();                                               \
    } while(0)



typedef struct sdsh_archetype_t sdsh_archetype_t;



struct sdsh_world_t{
    sdsh_archetype_t *archetypes;
    uint64_t archetype_c;
};



struct sdsh_range_t{
    
};



#endif //SDSH_INTERNAL_H
