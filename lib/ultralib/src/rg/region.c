#include "PR/region.h"
#include "PR/ultraerror.h"
#include "os_internal_error.h"
#include "assert.h"

















































































































































































// TODO: this comes from a header
#ident "$Revision: 1.17 $"

void* osCreateRegion(void* startAddress, u32 length, u32 bufferSize, u32 alignSize) {
    register OSRegion* rp;
    register int i;
    register char* addr;

    assert(startAddress != NULL);

#ifdef _DEBUG
    if ((alignSize != 0) && (alignSize != OS_RG_ALIGN_2B) && (alignSize != OS_RG_ALIGN_4B) &&
        (alignSize != OS_RG_ALIGN_8B) && (alignSize != OS_RG_ALIGN_16B)) {
        __osError(ERR_OSCREATEREGION_ALIGN, 1, alignSize);
        return 0;
    }
#endif

    if (alignSize == 0) {
        alignSize = OS_RG_ALIGN_DEFAULT;
    }

    rp = (OSRegion*)ALIGN(startAddress, alignSize);
    length = length - ((s32)rp - (s32)startAddress);
    rp->r_bufferSize = ALIGN(bufferSize, alignSize);
    rp->r_bufferCount = (s32)(length - ALIGN(sizeof(OSRegion), alignSize)) / rp->r_bufferSize;

#ifdef _DEBUG
    if (rp->r_bufferCount <= 0) {
        __osError(ERR_OSCREATEREGION_SIZE, 2, length, bufferSize);
        return 0;
    }
#endif

    if (rp->r_bufferCount > MAX_BUFCOUNT) {
        rp->r_bufferCount = MAX_BUFCOUNT;
    }

    rp->r_startBufferAddress = (u8*)rp + ALIGN(sizeof(OSRegion), alignSize);
    rp->r_endAddress = (u8*)rp + length;
    addr = rp->r_startBufferAddress;

    for (i = 0; i < rp->r_bufferCount - 1; i++) {
        *((s16*)(&addr[i * rp->r_bufferSize])) = i + 1;
    }

    *((u16*)(&addr[i * rp->r_bufferSize])) = BUF_FREE_WO_NEXT;
    rp->r_alignSize = alignSize;
    rp->r_freeList = 0;
    return rp;
}
