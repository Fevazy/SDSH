#pragma once
#ifndef SDSH_PUB_SDSH_H
#define SDSH_PUB_SDSH_H

#include <stdint.h>

typedef uint64_t sdsh_type_id_t;
typedef struct sdsh_state_t sdsh_state_t;

// Returns new type id.
// 0 is an error.
sdsh_type_id_t sdsh_register_type(sdsh_state_t *state, uint64_t size);



#endif // SDSH_PUB_SDSH_H
