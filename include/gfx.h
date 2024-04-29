#ifndef GFX_H
#define GFX_H

#include "ultra64.h"
#include "attributes.h"
#include "alignment.h"
#include "THA_GA.h"
#include "unk.h"

#define GRAPH_ALLOC(gfxCtx, size) ((void*)((gfxCtx)->polyOpa.d = (Gfx*)((u8*)(gfxCtx)->polyOpa.d - ALIGN16(size))))
#define GRAPH_ALLOC_NO_ALIGN(gfxCtx,size) ((void*)((gfxCtx)->polyOpa.d = (Gfx*)((u8*)(gfxCtx)->polyOpa.d - size)))

typedef struct GraphicsContext {
    /* 0x000 */ UNK_TYPE1 unk_000[0x8];
    /* 0x008 */ UNK_PTR unk_008;
    /* 0x00C */ UNK_TYPE1 unk_00C[0x250];
    /* 0x25C */ OSViMode* unk_25C;
    /* 0x260 */ UNK_TYPE1 unk_260[0x20];
    /* 0x280 */ TwoHeadGfxArena overlay;
    /* 0x290 */ TwoHeadGfxArena polyOpa;
    /* 0x2A0 */ TwoHeadGfxArena polyXlu;
    /* 0x2B0 */ TwoHeadGfxArena font;
    /* 0x2C0 */ TwoHeadGfxArena shadow;
    /* 0x2D0 */ TwoHeadGfxArena light;
    /* 0x2E0 */ UNK_TYPE1 unk_2E0[0x4];
    /* 0x2E4 */ UNK_PTR unk_2E4;
    /* 0x2E8 */ UNK_TYPE1 unk_2E8[0x4];
    /* 0x2EC */ s32 unk_2EC;
    /* 0x2F0 */ u8 unk_2F0;
    /* 0x2F1 */ UNK_TYPE1 unk_2F1[0x1];
    /* 0x2F2 */ u8 unk_2F2;
    /* 0x2F3 */ UNK_TYPE1 unk_2F3[0x1];
    /* 0x2F4 */ s32 unk_2F4;
    /* 0x2F8 */ s32 unk_2F8;
    /* 0x2FC */ f32 unk_2FC;
    /* 0x300 */ f32 unk_300;
} GraphicsContext; // size >= 0x304

#define OVERLAY_DISP __gfxCtx->overlay.p
#define POLY_OPA_DISP __gfxCtx->polyOpa.p
#define POLY_XLU_DISP __gfxCtx->polyXlu.p
#define FONT_DISP __gfxCtx->font.p
#define SHADOW_DISP __gfxCtx->shadow.p
#define LIGHT_DISP __gfxCtx->light.p

// __gfxCtx shouldn't be used directly.
// Use the DISP macros defined above when writing to display buffers.
#define OPEN_DISPS(gfxCtx)                  \
    do {} while (0);                        \
    {                                       \
        GraphicsContext* __gfxCtx = gfxCtx; \
        s32 __dispPad = 0;                  \
        do {} while (0)

#define CLOSE_DISPS(gfxCtx) \
        do {} while (0);    \
        (void)__dispPad;    \
    }                       \
    do {} while (0)

#define OPEN_POLY_OPA_DISP(g)                     \
    do {} while (0);                              \
    OPEN_DISPS(g);                                \
    {                                             \
        Gfx* __polyOpa = __gfxCtx->polyOpa.p;     \
        s32 __poly_opa_gfx = 0;                   \
    do {} while (0)

#define CLOSE_POLY_OPA_DISP(g)                     \
    do {} while (0);                               \
        (void)__poly_opa_gfx;                      \
        __gfxCtx->polyOpa.p = __polyOpa;           \
    }                                              \
    CLOSE_DISPS(g);                                \
    do {} while (0)

#define OPEN_POLY_XLU_DISP(g)                     \
    do {} while (0);                              \
    OPEN_DISPS(g);                                \
    {                                             \
        Gfx* __polyXlu = __gfxCtx->polyXlu.p;     \
        s32 __poly_xlu_gfx = 0;                   \
    do {} while (0)

#define CLOSE_POLY_XLU_DISP(g)                     \
    do {} while (0);                               \
        (void)__poly_xlu_gfx;                      \
        __gfxCtx->polyXlu.p = __polyXlu;           \
    }                                              \
    CLOSE_DISPS(g);                                \
    do {} while (0)

#define OPEN_LIGHT_DISP(g)                    \
    do {} while (0);                          \
    OPEN_DISPS(g);                            \
    {                                         \
        Gfx* __light = __gfxCtx->light.p;     \
        s32 __light_gfx = 0;                  \
        do {} while (0)

#define CLOSE_LIGHT_DISP(g)              \
       do {} while (0);                  \
        __gfxCtx->light.p = __light;     \
        (void)__light_gfx;               \
    }                                    \
    CLOSE_DISPS(g);                      \
    do {} while (0)

#define OPEN_SHADOW_DISP(g)                     \
    do {} while (0);                            \
    OPEN_DISPS(g);                              \
    {                                           \
        Gfx* __shadow_gfx = __gfxCtx->shadow.p; \
        s32 __shadow_opened = 0;                \
        do {} while (0)

#define CLOSE_SHADOW_DISP(g)                \
       do {} while (0);                     \
        (void)__shadow_opened;              \
        __gfxCtx->shadow.p = __shadow_gfx;  \
    }                                       \
    CLOSE_DISPS(g);                         \
    do {} while (0)

#define qs1616(e) ((s32)((e)*0x00010000))

#define IPART(x) ((qs1616(x) >> 16) & 0xFFFF)
#define FPART(x) (qs1616(x) & 0xFFFF)

// clang-format off

#define gdSPDefMtx(     \
        xx, yx, zx, wx, \
        xy, yy, zy, wy, \
        xz, yz, zz, wz, \
        xw, yw, zw, ww) \
    {{                                    \
        (IPART(xx) << 0x10) | IPART(xy),  \
        (IPART(xz) << 0x10) | IPART(xw),  \
        (IPART(yx) << 0x10) | IPART(yy),  \
        (IPART(yz) << 0x10) | IPART(yw),  \
        (IPART(zx) << 0x10) | IPART(zy),  \
        (IPART(zz) << 0x10) | IPART(zw),  \
        (IPART(wx) << 0x10) | IPART(wy),  \
        (IPART(wz) << 0x10) | IPART(ww),  \
        (FPART(xx) << 0x10) | FPART(xy),  \
        (FPART(xz) << 0x10) | FPART(xw),  \
        (FPART(yx) << 0x10) | FPART(yy),  \
        (FPART(yz) << 0x10) | FPART(yw),  \
        (FPART(zx) << 0x10) | FPART(zy),  \
        (FPART(zz) << 0x10) | FPART(zw),  \
        (FPART(wx) << 0x10) | FPART(wy),  \
        (FPART(wz) << 0x10) | FPART(ww),  \
    }}

// clang-format on

#endif
