#include "PR/region.h"
#include "PR/R4300.h"
#include "PR/ultraerror.h"
#include "PR/os_internal.h"
#include "assert.h"





































// TODO: this comes from a header
#ident "$Revision: 1.17 $"

void osFree(void* region, void* addr) {
    register OSRegion* rp = region;
    int i;

#ifdef _DEBUG
    assert((region != NULL) && (addr != NULL));
    if (((char*)rp + ALIGN(sizeof(OSRegion), rp->r_alignSize)) != rp->r_startBufferAddress) {
        __osError(ERR_OSFREE_REGION, 1, region);
        return;
    }
#endif

    i = ((u8*)addr - rp->r_startBufferAddress) / rp->r_bufferSize;

#ifdef _DEBUG
    if ((i < 0) || (i >= rp->r_bufferCount)) {
        __osError(ERR_OSFREE_ADDR, 2, addr, region);
        return;
    }

    if (((unsigned char*)addr - rp->r_startBufferAddress) % (rp->r_bufferSize) != 0) {
        __osError(ERR_OSFREE_ADDR, 2, addr, region);
        return;
    }
#endif
    *(u16*)(&rp->r_startBufferAddress[i * rp->r_bufferSize]) = rp->r_freeList;
    rp->r_freeList = i;
}
