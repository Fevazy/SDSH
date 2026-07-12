#pragma once
#ifndef SDSH_ALLOC_H
#define SDSH_ALLOC_H

#include <stdint.h>
void *sdsh_alloc(uint64_t size);
void  sdsh_free(void *p);

#endif // SDSH_ALLOC_H
