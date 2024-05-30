#ifndef PRE_RENDER_H
#define PRE_RENDER_H

#include "ultra64.h"

#include "listalloc.h"
#include "unk.h"

typedef struct PreRender {
    /* 0x00 */ u16 width;
    /* 0x02 */ u16 height;
    /* 0x04 */ u16 width_save;
    /* 0x04 */ u16 height_save;
    /* 0x08 */ UNK_TYPE1 unk_08[0x8];
    /* 0x10 */ u16* fbuf;
    /* 0x14 */ u16* fbuf_save;
    /* 0x18 */ u8* cvg_save;
    /* 0x1C */ u16* zbuf;
    /* 0x20 */ u16* zbuf_save;
    /* 0x24 */ u16 ulx_save;
    /* 0x26 */ u16 uly_save;
    /* 0x28 */ u16 lrx_save;
    /* 0x2A */ u16 lry_save;
    /* 0x2C */ u16 ulx;
    /* 0x2E */ u16 uly;
    /* 0x30 */ u16 lrx;
    /* 0x32 */ u16 lry;
    /* 0x34 */ UNK_TYPE1 UNK_34[0x10];
    /* 0x44 */ ListAlloc alloc;
    /* 0x4C */ u8 unk_4C;
    /* 0x4D */ u8 filterState;
} PreRender; // size = 0x50

#define WALLPAPER_FLAGS_1 (1 << 0)
#define WALLPAPER_FLAGS_2 (1 << 1)
#define WALLPAPER_FLAGS_AC_THRESHOLD (1 << 2)
#define WALLPAPER_FLAGS_LOAD_S2DEX2 (1 << 3)
#define WALLPAPER_FLAGS_COPY (1 << 4)

void PreRender_setup_savebuf(PreRender* this, s32 width, s32 height, void* fbuf, void* zbuf, void* cvg);
void PreRender_init(PreRender* this);
void PreRender_setup_renderbuf(PreRender* this, s32 width, s32 height, void* fbuf, void* zbuf);
void PreRender_cleanup(PreRender* this);
void PreRender_TransBufferCopy(PreRender* this, Gfx** glistpp, void* arg2, void* arg3, u32 useThresholdAlphaCompare);
void PreRender_TransBuffer(PreRender* this, Gfx** glistpp, void* arg2, void* arg3);
void PreRender_TransBuffer1(PreRender* this, Gfx** glistpp, void* arg2, void* arg3);
void PreRender_TransBuffer2(PreRender* this, Gfx** glistpp, void* arg2, void* arg3);
void PreRender_CopyRGBC(PreRender* this, Gfx** gfxp, s32 width, s32 height);
void PreRender_saveZBuffer(PreRender* this, Gfx** glistpp);
void PreRender_saveFrameBuffer(PreRender* this, Gfx** glistpp);
void PreRender_saveCVG(PreRender* this, Gfx** glistpp);
void PreRender_loadZBuffer(PreRender* this, Gfx** glistpp);
void PreRender_loadFrameBuffer(PreRender* this, Gfx** glistpp);
void PreRender_loadFrameBufferAlpha(PreRender* this, Gfx** glistpp, s32 alpha);
void PreRender_loadFrameBufferCopy(PreRender* this, Gfx** glistpp);
void PreRender_ConvertFrameBuffer_fg(PreRender* this);
void PreRender_ConvertFrameBuffer(PreRender* this);

#endif
