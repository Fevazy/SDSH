#include <assert.h>
#include <sdsh.h>
#include <stdint.h>

typedef struct {
    float x, y;
} position_t;
typedef struct {
    float x, y;
} velocity_t;

void system_callback(sdsh_range_t *r, void *user) {
    (void)user;
    position_t      *p = (position_t *)sdsh_component_get_base(r, 0); // pos
    velocity_t      *v = (velocity_t *)sdsh_component_get_base(r, 1); // vel
    sdsh_entity_id_t count = sdsh_range_get_count(r);
    for (sdsh_entity_id_t i = 0; i < count; i++) {
        p[i].x += v[i].x;
        p[i].y += v[i].y;
    }
    return;
}

int main() {
    sdsh_world_t *w = sdsh_world_create();

    sdsh_component_desc_t comps[2] = {
        {.id = 0, .size = sizeof(position_t), .align = _Alignof(position_t)},
        {.id = 1, .size = sizeof(velocity_t), .align = _Alignof(velocity_t)},
    };

    sdsh_register_components(w, comps, 2);
    sdsh_archetype_id_t a = sdsh_archetype_register(w, comps, 2);

    sdsh_component_id_t reads[] = {0, 1}; // pos, vel
    sdsh_component_id_t writes[] = {0};   // pos
    sdsh_system_register(w, system_callback, reads, 2, writes, 1, NULL);

    sdsh_entity_id_t e = sdsh_entity_spawn(w, a);
    *(position_t *)sdsh_comp_get(w, e, 0) = (position_t){.x = 0, .y = 0}; // pos
    *(velocity_t *)sdsh_comp_get(w, e, 1) =
        (velocity_t){.x = 1, .y = 15}; // vel

    sdsh_world_deploy(w);
    sdsh_world_tick(w);

    position_t p = *(position_t *)sdsh_comp_get(w, e, 0);
    assert(p.x == 1.0f && p.y == 15.0f);

    sdsh_world_delete(w);

    return 0;
}
