#include "malloc.h"

void Osapi_Malloc(regs_t *r)
{
    unsigned int nBytes = r->ebx;
    void* output = malloc(nBytes);
    r->eax = (int)output;
}

void Osapi_Free(regs_t *r)
{
    void *ap = (void *)r->ebx;
    free(ap);
}
