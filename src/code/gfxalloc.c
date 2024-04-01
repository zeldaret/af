#include "gfxalloc.h"
#include "alignment.h"

Gfx* gfxopen(Gfx* gfx) {
    return gfx + 1;
}

Gfx* gfxclose(Gfx* gfx, Gfx* gfxNew) {
    if (gfx + 1 != gfxNew) {
        gSPBranchList(gfx, gfxNew);
        return gfxNew;
    } else {
        gSPNoOp(gfx);
        return gfx;
    }
}

void* gfxalloc(Gfx** gfxp, size_t size) {
    u8* ptr;
    Gfx* dst;

    size = ALIGN8(size);
    ptr = (u8*)(*gfxp + 1);
    dst = (Gfx*)(ptr + size);
    gSPBranchList(*gfxp, dst);

    *gfxp = dst;
    return ptr;
}
