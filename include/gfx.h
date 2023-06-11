#ifndef GFX_H
#define GFX_H

#include "ultra64.h"
#include "THA_GA.h"

typedef struct GraphicsContext {
    /* 0x000 */ char pad[0x290];
    /* 0x298 */ TwoHeadGfxArena polyOpa;
    /* 0x2A8 */ TwoHeadGfxArena polyXlu;
} GraphicsContext; // size = ??

#define WORK_DISP __gfxCtx->work.p
#define POLY_OPA_DISP __gfxCtx->polyOpa.p
#define POLY_XLU_DISP __gfxCtx->polyXlu.p
#define OVERLAY_DISP __gfxCtx->overlay.p
#define DEBUG_DISP __gfxCtx->debug.p

// __gfxCtx shouldn't be used directly.
// Use the DISP macros defined above when writing to display buffers.
#define OPEN_DISPS(gfxCtx)                  \
    {                                       \
        GraphicsContext* __gfxCtx = gfxCtx; \
        s32 __dispPad

#define CLOSE_DISPS(gfxCtx) \
    (void)0;                \
    }                       \
    (void)0

#endif