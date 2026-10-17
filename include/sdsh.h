#pragma once
#ifndef SDSH_PUB_SDSH_H
#define SDSH_PUB_SDSH_H

#include <stddef.h>
#include <stdint.h>

#define SDSH_MAX_COMPONENTS 256 // per archetype

typedef uint8_t  sdsh_component_id_t; // must store up to N =
// = SDSH_MAX_COMPONENTS-1. keep as short as possible, wastes memory a lot
typedef uint64_t sdsh_archetype_id_t; // must store. keep.
typedef uint64_t sdsh_entity_id_t;

typedef struct sdsh_world_t          sdsh_world_t;
typedef struct sdsh_component_desc_t sdsh_component_desc_t;
typedef struct sdsh_component_set_t  sdsh_component_set_t;
typedef struct sdsh_range_t          sdsh_range_t;

struct sdsh_component_desc_t {
    uint64_t size;
    uint8_t  align;
};

struct sdsh_component_set_t {
    uint64_t            count;
    sdsh_component_id_t indexes[SDSH_MAX_COMPONENTS];
};

sdsh_world_t *sdsh_world_create();
void          sdsh_world_deploy(sdsh_world_t *w);
void          sdsh_world_tick(sdsh_world_t *w);
void          sdsh_world_delete(sdsh_world_t *w);

sdsh_archetype_id_t sdsh_archetype_register(sdsh_world_t          *w,
                                            sdsh_component_desc_t *comps,
                                            sdsh_component_id_t    count);

sdsh_entity_id_t sdsh_entity_spawn(sdsh_world_t *r, sdsh_archetype_id_t a);

void *sdsh_component_get_base(sdsh_range_t *r, sdsh_component_id_t c);
void *sdsh_comp_get(sdsh_world_t *w, sdsh_entity_id_t e, sdsh_component_id_t c);

uint64_t sdsh_range_get_count(sdsh_range_t *r);

void sdsh_system_register(sdsh_world_t *w,
                          void (*cb)(sdsh_range_t *r, void *user),
                          sdsh_component_set_t *reads,
                          sdsh_component_set_t *writes, void *user);

#endif // SDSH_PUB_SDSH_H
