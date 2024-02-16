#ifndef PRE_RENDER_H
#define PRE_RENDER_H

#include "ultra64.h"

#include "listalloc.h"
#include "unk.h"

typedef struct PreRender {
    /* 0x00 */ u16 width;
    /* 0x02 */ u16 height;
    /* 0x04 */ u16 widthSave;
    /* 0x04 */ u16 heightSave;
    /* 0x08 */ UNK_TYPE1 unk_08[0x8];
    /* 0x10 */ u16* fbuf;
    /* 0x14 */ u16* fbufSave;
    /* 0x18 */ u8* cvgSave;
    /* 0x1C */ u16* zbuf;
    /* 0x20 */ u16* zbufSave;
    /* 0x24 */ u16 ulxSave;
    /* 0x26 */ u16 ulySave;
    /* 0x28 */ u16 lrxSave;
    /* 0x2A */ u16 lrySave;
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

void PreRender_setup_savebuf(PreRender* render, s32 arg1, s32 arg2, void* arg3, void* arg4, void* arg5);
void PreRender_init(PreRender* render);
void PreRender_setup_renderbuf(PreRender* render, s32 width, s32 height, void* arg3, void* arg4);
void PreRender_cleanup(PreRender* render);
void PreRender_TransBufferCopy(PreRender* render, Gfx** gfxP, void* arg2, void* arg3, u32 useThresholdAlphaCompare);
void PreRender_TransBuffer(PreRender* render, Gfx** gfxP, void* arg2, void* arg3);
void PreRender_TransBuffer1(PreRender* render, Gfx** gfxP, void* arg2, void* arg3);
void PreRender_TransBuffer2(PreRender* render, Gfx** gfxP, void* arg2, void* arg3);
void PreRender_CopyRGBC(PreRender* render, Gfx** gfxP, s32 arg2, s32 arg3);
void PreRender_saveZBuffer(PreRender* render, Gfx** gfxP);
void PreRender_saveFrameBuffer(PreRender* render, Gfx** gfxP);
void PreRender_saveCVG(PreRender* render, Gfx** gfxP);
void PreRender_loadZBuffer(PreRender* render, Gfx** gfxP);
void PreRender_loadFrameBuffer(PreRender* render, Gfx** gfxP);
void PreRender_loadFrameBufferAlpha(PreRender* render, Gfx** gfxP, s32 alpha);
void PreRender_loadFrameBufferCopy(PreRender* render, Gfx** gfxP);
void PreRender_ConvertFrameBuffer_fg(PreRender* render);
void PreRender_ConvertFrameBuffer(PreRender* render);

#endif
