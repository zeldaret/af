#ifndef GFX_H
#define GFX_H

#include "ultra64.h"
#include "PR/sched.h"
#include "attributes.h"
#include "alignment.h"
#include "THA_GA.h"
#include "unk.h"

#define GRAPH_ALLOC(gfxCtx, size) ((void*)((gfxCtx)->polyOpa.d = (Gfx*)((u8*)(gfxCtx)->polyOpa.d - ALIGN16(size))))
#define GRAPH_ALLOC_NO_ALIGN(gfxCtx,size) ((void*)((gfxCtx)->polyOpa.d = (Gfx*)((u8*)(gfxCtx)->polyOpa.d - size)))

#define TMEM_SIZE 0x1000

#define GFXPOOL_HEAD_MAGIC 0x1234
#define GFXPOOL_TAIL_MAGIC 0x5678

typedef struct GfxPool {
    /* 0x00000 */ u16 headMagic;
    /* 0x00004 */ UNK_TYPE1 unk00004[0x4];
    /* 0x00008 */ Gfx polyOpaBuffer[0x29E0];
    /* 0x14F08 */ Gfx polyXluBuffer[0x800];
    /* 0x18F08 */ Gfx overlayBuffer[0x400];
    /* 0x1AF08 */ Gfx workBuffer[0x80];
    /* 0x1B308 */ UNK_TYPE1 unk1B308[0x100];
    /* 0x1B408 */ Gfx fontBuffer[0x700];
    /* 0x1EC08 */ Gfx shadowBuffer[0x200];
    /* 0x1FC08 */ Gfx lightBuffer[0x100];
    /* 0x20408 */ u16 tailMagic;
} GfxPool; // size = 0x20410

typedef struct GraphicsContext {
    /* 0x000 */ Gfx* polyOpaBuffer;
    /* 0x004 */ Gfx* polyXluBuffer;
    /* 0x008 */ UNK_PTR unk_008;
    /* 0x00C */ UNK_TYPE1 unk_00C[0x4];
    /* 0x010 */ Gfx* overlayBuffer;
    /* 0x014 */ Gfx* fontBuffer;
    /* 0x018 */ Gfx* shadowBuffer;
    /* 0x01C */ Gfx* lightBuffer;
    /* 0x020 */ s32 unk_20;
    /* 0x024 */ UNK_TYPE1 unk_024[0x20];
    /* 0x044 */ OSMesg msgBuff[8];
    /* 0x064 */ OSMesgQueue* unk_064;
    /* 0x068 */ OSMesgQueue queue;
    /* 0x080 */ OSScTask task;
    /* 0x0D8 */ UNK_TYPE1 unk_0E8[0x188 - 0xD8];
    /* 0x188 */ Gfx* workBuffer;
    /* 0x18C */ TwoHeadGfxArena work;
    /* 0x19C */ UNK_TYPE1 unk_19C[0xC0];
    /* 0x25C */ OSViMode* unk_25C;
    /* 0x260 */ UNK_TYPE1 unk_260[0x20];
    /* 0x280 */ TwoHeadGfxArena overlay;
    /* 0x290 */ TwoHeadGfxArena polyOpa;
    /* 0x2A0 */ TwoHeadGfxArena polyXlu;
    /* 0x2B0 */ TwoHeadGfxArena font;
    /* 0x2C0 */ TwoHeadGfxArena shadow;
    /* 0x2D0 */ TwoHeadGfxArena light;
    /* 0x2E0 */ u32 unk_2E0;
    /* 0x2E4 */ UNK_PTR unk_2E4;
    /* 0x2E8 */ UNK_TYPE1 unk_2E8[0x4];
    /* 0x2EC */ s32 unk_2EC;
    /* 0x2F0 */ u8 unk_2F0;
    /* 0x2F1 */ UNK_TYPE1 unk_2F1[0x1];
    /* 0x2F2 */ u8 unk_2F2;
    /* 0x2F3 */ u8 unk_2F3;
    /* 0x2F4 */ void (*callback)(struct GraphicsContext*, void*);
    /* 0x2F8 */ void* callbackArg;
    /* 0x2FC */ f32 unk_2FC;
    /* 0x300 */ f32 unk_300;
    /* 0x304 */ Gfx* unk_304;
} GraphicsContext; // size = 0x308

#define OVERLAY_DISP __gfxCtx->overlay.p
#define POLY_OPA_DISP __gfxCtx->polyOpa.p
#define POLY_XLU_DISP __gfxCtx->polyXlu.p
#define FONT_DISP __gfxCtx->font.p
#define SHADOW_DISP __gfxCtx->shadow.p
#define LIGHT_DISP __gfxCtx->light.p
#define WORK_DISP __gfxCtx->work.p

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
