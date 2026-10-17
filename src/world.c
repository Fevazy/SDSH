#include "internal.h"

sdsh_world_t *sdsh_world_create() {
    sdsh_world_t *w = sdsh_alloc(sizeof(sdsh_world_t));
    // TODO: initialize world
    return w;
};

void sdsh_world_deploy(sdsh_world_t *w) {
    SDSH_NOT_IMPLEMENTED();
    return;
};

void sdsh_world_tick(sdsh_world_t *w) {
    SDSH_NOT_IMPLEMENTED();
    return;
};

void sdsh_world_delete(sdsh_world_t *w) {
    sdsh_free(w);
    return;
};
