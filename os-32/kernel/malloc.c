#include <malloc.h>
#include <system.h>
#include <screen.h>
static union Header base;
static union Header *freep = NULL;

void *malloc(size_t nBytes)
{
    union Header *p, *prevp;
    unsigned int nUnits;
    union Header *moreCore(unsigned int nUnits);
    unsigned int toAlignmentUnits(unsigned int nBytes);

    nUnits = toAlignmentUnits(nBytes);

    if ((prevp = freep) == NULL ) {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }

    for (p = prevp->s.ptr ;; prevp = p, p = p->s.ptr) {
        kprintf("p->s.size A: %u\n",p->s.size);
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
        {
            if ((p = moreCore(nUnits)) == NULL)
                return NULL;
        }
    }
}

union Header *moreCore(unsigned int nUnits) {
    char *cp;
    union Header *up;
    unsigned int alignmentUnitsToFrames(unsigned int nUnits);
    unsigned int framesToAlignmentUnits(unsigned int frames);

    unsigned int nFrames = alignmentUnitsToFrames(nUnits);
    cp = mm_alloc_frames(nFrames);
    if (cp == (char *) -1)
        return NULL;
    up = (union Header *) cp;
    up->s.size = framesToAlignmentUnits(nFrames);

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

/*nUnits to frames*/
unsigned int alignmentUnitsToFrames(size_t nUnits) {
    return (nUnits * sizeof(union Header))/MALLOC_BLOCK_SIZE + 1;
}

unsigned int toAlignmentUnits(unsigned int nBytes) {
    return (nBytes + sizeof(union Header) - 1)/sizeof(union Header) + 1;
}

unsigned int framesToAlignmentUnits(unsigned int frames) {
    return frames * MALLOC_BLOCK_SIZE / sizeof(Align);
}
