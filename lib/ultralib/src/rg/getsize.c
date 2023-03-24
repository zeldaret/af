#include "PR/region.h"

// TODO: this comes from a header
#ident "$Revision: 1.17 $"

s32 osGetRegionBufSize(void *region) {
    register OSRegion *rp = region;
    return rp->r_bufferSize;
}
