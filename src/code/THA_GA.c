/**
 * @file THA_GA.c
 *
 * This file implements a particular use of the double-ended stack allocator from TwoHeadArena.c for graphics data.
 *
 * Display list commands are allocated from the head while other graphics data such as matrices and vertices are
 * allocated from the tail end.
 *
 * @see TwoHeadArena.c
 */

#include "global.h"
#include "THA_GA.h"

void THA_GA_ct(TwoHeadGfxArena* thga, void* start, size_t size) {
    THA_ct(&thga->tha, start, size);
}

void THGA_dt(TwoHeadGfxArena* thga) {
    THA_dt(&thga->tha);
}

u32 THA_GA_isCrash(TwoHeadGfxArena* thga) {
    return THA_isCrash(&thga->tha);
}

void THA_GA_init(TwoHeadGfxArena* thga) {
    THA_init(&thga->tha);
}

s32 THA_GA_getFreeBytes(TwoHeadGfxArena* thga) {
    return THA_getFreeBytes(&thga->tha);
}

Gfx* THA_GA_getHeadPtr(TwoHeadGfxArena* thga) {
    return THA_getHeadPtr(&thga->tha);
}

void THA_GA_setHeadPtr(TwoHeadGfxArena* thga, Gfx* newHead) {
    THA_setHeadPtr(&thga->tha, newHead);
}

void* THA_GA_getTailPtr(TwoHeadGfxArena* thga) {
    return THA_getTailPtr(&thga->tha);
}

/**
 * Allocates a display list of `num` Gfx commands to the head of the Two Head Gfx Arena.
 */
Gfx* THA_GA_nextPtrN(TwoHeadGfxArena* thga, size_t num) {
    THA_nextPtrN(&thga->tha, num * sizeof(Gfx));
}

/**
 * Allocates a single Gfx command to the head of the Two Head Gfx Arena.
 */
Gfx* THA_GA_nextPtr1(TwoHeadGfxArena* thga) {
    return THA_GA_nextPtrN(thga, 1);
}

/**
 * Allocates a single Gfx command to the head of the Two Head Gfx Arena.
 */
Gfx* THA_GA_NEXT_DISP(TwoHeadGfxArena* thga) {
    return THA_GA_nextPtr1(thga);
}

/**
 * Allocates to the end of the Two Head Gfx Arena. Intended for data complementary to the display lists such as
 * matrices and vertices that are only needed for a single graphics task.
 */
void* THA_GA_alloc(TwoHeadGfxArena* thga, size_t size) {
    return THA_alloc(&thga->tha, size);
}

/**
 * Allocates `num` matrices to the tail end of the Two Head Gfx Arena.
 */
Mtx* THA_GA_allocMtxN(TwoHeadGfxArena* thga, size_t num) {
    return THA_GA_alloc(thga, num * sizeof(Mtx));
}

/**
 * Allocates a matrix to the tail end of the Two Head Gfx Arena.
 */
Mtx* THA_GA_allocMtx1(TwoHeadGfxArena* thga) {
    return THA_GA_alloc(thga, sizeof(Mtx));
}

/**
 * Allocates `num` vertices to the tail end of the Two Head Gfx Arena.
 */
Vtx* THA_GA_allocVtxN(TwoHeadGfxArena* thga, u32 num) {
    return THA_GA_alloc(thga, num * sizeof(Vtx));
}

/**
 * Allocates a vertex to the tail end of the Two Head Gfx Arena.
 */
Vtx* THA_GA_allocVtx1(TwoHeadGfxArena* thga) {
    return THA_GA_alloc(thga, sizeof(Vtx));
}
