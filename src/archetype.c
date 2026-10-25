#include "alloc.h"
#include "internal.h"
#include "sdsh.h"
#include <stdint.h>
#include <stdlib.h>

sdsh_archetype_id_t sdsh_archetype_register(sdsh_world_t          *w,
                                            sdsh_component_desc_t *comps,
                                            sdsh_component_id_t    comp_count) {
    if (w->archetypes == NULL) {
        w->archetypes = sdsh_alloc(16 * sizeof(sdsh_archetype_t *));
        w->archetype_capacity = 16;
        w->archetype_count = 0;
    }
    if (w->archetype_capacity - w->archetype_count < 1) {
        void *mem = realloc(w->archetypes, (w->archetype_capacity * 2) *
                                               sizeof(sdsh_archetype_t *));
        if (!mem)    // TODO: substitute with careful handler
            abort(); // OoM, DDR4/5 is expensive nowdays
        w->archetypes = mem;
        w->archetype_capacity *= 2;
    }

    sdsh_archetype_t *a = sdsh_alloc(sizeof(sdsh_archetype_t) +
                                     comp_count * sizeof(sdsh_component_t));
    if (!a)      // TODO: substitute with careful handler
        abort(); // OoM, DDR4/5 is still expensive there

    a->component_count = comp_count;
    for (sdsh_component_id_t i = 0; i < comp_count; i++) {
        a->components[i].size = comps->size;
        a->components[i].align = comps->align;
    };
    w->archetypes[++w->archetype_count] = a;
    return w->archetype_count;
};
