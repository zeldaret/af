#ifndef PRE_RENDER_H
#define PRE_RENDER_H

#include "ultra64.h"

#include "listalloc.h"
#include "unk.h"

typedef struct PreRender {
    /* 0x00 */ u16 width;
    /* 0x02 */ u16 height;
    /* 0x04 */ u16 unk_04;
    /* 0x04 */ u16 unk_06;
    /* 0x08 */ UNK_TYPE1 unk_08[0x8];
    /* 0x10 */ UNK_PTR unk_10;
    /* 0x14 */ UNK_PTR unk_14;
    /* 0x18 */ UNK_PTR unk_18;
    /* 0x1C */ UNK_PTR unk_1C;
    /* 0x20 */ UNK_PTR unk_20;
    /* 0x24 */ u16 unk_24;
    /* 0x26 */ u16 unk_26;
    /* 0x28 */ u16 unk_28;
    /* 0x2A */ u16 unk_2A;
    /* 0x2C */ u16 unk_2C;
    /* 0x2E */ u16 unk_2E;
    /* 0x30 */ u16 unk_30;
    /* 0x32 */ u16 unk_32;
    /* 0x34 */ UNK_TYPE1 UNK_34[0x10];
    /* 0x44 */ ListAlloc alloc;
    /* 0x4C */ UNK_TYPE1 unk_4C[0x4];
} PreRender; // size = 0x50

#define WALLPAPER_FLAGS_1 (1 << 0)
#define WALLPAPER_FLAGS_2 (1 << 1)
#define WALLPAPER_FLAGS_AC_THRESHOLD (1 << 2)
#define WALLPAPER_FLAGS_LOAD_S2DEX2 (1 << 3)
#define WALLPAPER_FLAGS_COPY (1 << 4)

void wallpaper_draw(Gfx** gfxp, void* timg, void* tlut, u16 width, u16 height, u8 fmt, u8 siz, u16 tt, u16 tlutCount, f32 x, f32 y, f32 xScale, f32 yScale, u32 flags);
void PreRender_setup_savebuf(PreRender* render, s32 arg1, s32 arg2, void* arg3, void* arg4, void* arg5);
void PreRender_init(PreRender* render);
void PreRender_setup_renderbuf(PreRender* render, s32 width, s32 height, void* arg3, void* arg4);
void PreRender_cleanup(PreRender* render);
void PreRender_TransBufferCopy(PreRender* render, Gfx** gfxP, void* img, void* imgDst, u32 useThresholdAlphaCompare);
void PreRender_TransBuffer(PreRender* render, Gfx** gfxP, void* arg2, void* arg3);
void PreRender_TransBuffer1(PreRender* render, Gfx** gfxP, void* arg2, void* arg3);
void PreRender_TransBuffer2(PreRender* render, Gfx** gfxP, void* arg2, void* arg3);
void PreRender_ShowCoveredge(Gfx** gfxP, s32 ulx, s32 uly, s32 lrx, s32 lry);
void PreRender_CopyRGBC(PreRender* render, Gfx** gfxP, s32 arg2, s32 arg3);
void PreRender_saveZBuffer(PreRender* render, Gfx** gfxP);
void PreRender_saveFrameBuffer(PreRender* render, Gfx** gfxP);
void PreRender_saveCVG(PreRender* render, Gfx** gfxP);
// void PreRender_loadZBuffer();
// void PreRender_loadFrameBuffer();
// void PreRender_loadFrameBufferAlpha();
void PreRender_loadFrameBufferCopy(PreRender* render, Gfx** gfx);
// void ASAlgorithm();
// void AntiAliasFilter();
void PreRender_ConvertFrameBuffer_fg(PreRender* render);
// void PreRender_ConvertFrameBuffer();

#endif
