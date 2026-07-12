#include <stdint.h>
#include <include/SDSH.h>
#include <src/alloc.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

typedef struct sdsh_type_registry_t sdsh_type_registry_t;
typedef struct sdsh_dynarray_t      sdsh_dynarray_t;
typedef struct sdsh_type_t          sdsh_type_t;

struct sdsh_type_t {
    uint64_t id;
    uint64_t size;
};

struct sdsh_dynarray_t {
    void *data;
    uint64_t cap;
    uint64_t el_sz;
    uint64_t used;
};

bool sdsh_dynarray_append(sdsh_dynarray_t *arr, const void *data){
    if(arr->cap<=arr->used || arr->data==NULL){
        uint64_t newcap = arr->cap*2;
        newcap = (newcap >= 2) ? newcap : 2;
        void *newp = sdsh_alloc(newcap*arr->el_sz);
        if(newp==NULL) return false;
        if(arr->data!=NULL){
            memcpy(newp, arr->data, arr->used*arr->el_sz);
            sdsh_free(arr->data);
        }
        arr->data=newp;
        arr->cap=newcap;
    }
    uint64_t index = arr->used++;
    void *dest = (uint8_t*)(arr->data)+index*arr->el_sz;
    memcpy(dest, data, arr->el_sz);
    return true;
};

struct sdsh_state_t{
    sdsh_type_registry_t *typereg;
};

struct sdsh_type_registry_t {
    sdsh_dynarray_t types;
    uint64_t next_id;
};

void sdsh_type_registry_t_init(sdsh_type_registry_t *arrp){
    *arrp = (sdsh_type_registry_t){
        .types.el_sz=sizeof(sdsh_type_t),
        .next_id=1 //0 is an error
    };
}

uint64_t sdsh_register_type(sdsh_state_t *state, uint64_t size){
    if(!state || !state->typereg || !size) return 0;
    sdsh_type_registry_t *typereg = state->typereg;
    sdsh_type_t newtype = (sdsh_type_t){
        .size=size,
        .id=typereg->next_id++
    };
    sdsh_dynarray_t *typearr = &typereg->types;
    if (!sdsh_dynarray_append(typearr, &newtype)) return 0;
    return newtype.id;
};
