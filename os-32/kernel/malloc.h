#ifndef MALLOC_H_INCLUDED
#define MALLOC_H_INCLUDED
#include <types.h>
#define NALLOC 1024
#define MALLOC_BLOCK_SIZE	4096
typedef long long Align;

union Header {
    struct {
        union Header *ptr;
        unsigned int size;
    } s;
    Align x;
};


void free(void *ap);
void *malloc(size_t nBytes);
#endif // MALLOC_H_INCLUDED
