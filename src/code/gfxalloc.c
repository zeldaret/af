#include "gfxalloc.h"
#include "alignment.h"

Gfx* gfxopen(Gfx* gfxHead) {
    return gfxHead + 1;
}

Gfx* gfxclose(Gfx* gfxHead, Gfx* gfx) {
    if (gfxHead + 1 != gfx) {
        gSPBranchList(gfxHead, gfx);
        return gfx;
    } else {
        gSPNoOp(gfxHead);
        return gfxHead;
    }
}

void* gfxalloc(Gfx** gfxP, size_t size) {
    u8* ptr;
    Gfx* dst;

    size = ALIGN8(size);
    ptr = (u8*)(*gfxP + 1);
    dst = (Gfx*)(ptr + size);
    gSPBranchList(*gfxP, dst);

    *gfxP = dst;
    return ptr;
}
