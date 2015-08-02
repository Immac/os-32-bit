#include <malloc.h>
#include <system.h>
#include <screen.h>
static union Header base;
static union Header *freep = NULL;

void *malloc(size_t nBytes)
{
    union Header *p, *prevp;
    uint32_t nUnits;
    kprintf("size: %x\n",nBytes);
    nUnits = (nBytes + sizeof(union Header) - 1)/sizeof(union Header) + 1;

    if ((prevp = freep) == NULL ) {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }

    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nUnits) {
            if (p->s.size == nUnits)
                prevp->s.ptr = p->s.ptr;
            else {
                p->s.size -= nUnits;
                p += p->s.size;
                p->s.size = nUnits;
            }
            freep = prevp;
            kprintf("p: %p\n",p);
            kprintf("freep: %p\n",freep);
            return (void*)(p + 1);
        }
        if (p == freep)
            if ((p = moreCore(nUnits)) == NULL)
                return NULL;
    }
}

static union Header *moreCore(uint32_t nUnits) {
    char *cp;
    union Header *up;

    if(nUnits < NALLOC)
        nUnits = NALLOC;
    cp = (char *)mm_alloc_frames(nUnits * sizeof(union Header));
    if (cp == (char *) -1)
        return NULL;
    up = (union Header *) cp;
    up->s.size = nUnits;
    free( (void *) (up + 1) );
    return freep;
}

void free(void *ap) {
    union Header *bp, *p;

    bp = (union Header* )ap - 1;
    for (p = freep; !(bp > p && bp < p->s.ptr ); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;

    if (bp + bp->s.size == p->s.ptr) {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else
        bp->s.ptr = p->s.ptr;
    if (p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else
        p->s.ptr = bp;
    freep = p;
}
