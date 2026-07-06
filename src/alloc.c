#include <stdint.h>
#include <stdlib.h>
void *SDSH_alloc(uint64_t size){
    if(size==0) return NULL;
    return malloc(size);
}
void SDSH_free(void* p){
    free(p);
}
