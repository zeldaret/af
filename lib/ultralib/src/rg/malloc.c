#include "PR/region.h"

// TODO: this comes from a header
#ident "$Revision: 1.17 $"

void *osMalloc(void *region) {
    register OSRegion *rp = region;
    unsigned char *addr;

    if (rp->r_freeList == MAX_BUFCOUNT) {
        return NULL;
    }
    
    addr = &rp->r_startBufferAddress[rp->r_freeList * rp->r_bufferSize];
    rp->r_freeList = *(u16 *)addr;
    return addr;
}
