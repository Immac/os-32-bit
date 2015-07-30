#ifndef MALLOC_H_INCLUDED
#define MALLOC_H_INCLUDED
#include <types.h>
#define NALLOC 1024
typedef long Align;

union Header {
    struct {
        union Header *ptr;
        unsigned size;
    } s;
    Align x;
};

static union Header *moreCore(uint32_t nUnits);
void free(void *ap);
void *malloc(uint32_t nBytes);
#endif // MALLOC_H_INCLUDED
