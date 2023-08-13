#ifndef PRE_RENDER_H
#define PRE_RENDER_H

#include "ultra64.h"

typedef struct ListAlloc {
    /* 0x0 */ struct ListAlloc* prev;
    /* 0x4 */ struct ListAlloc* next;
} ListAlloc; // size = 0x8

typedef struct {
    /* 0x00 */ u16 width;
    /* 0x02 */ u16 height;
    /* 0x04 */ u16 widthSave;
    /* 0x06 */ u16 heightSave;
    /* 0x08 */ char unk_8[8];
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
    /* 0x34 */ char unk_34[16];
    /* 0x44 */ ListAlloc alloc;
    /* 0x4C */ u8 unk_4C;
    /* 0x4D */ u8 unk_4D;
    /* 0x4E */ char unk_4E[2];
} PreRender; // size = 0x50

// void wallpaper_draw1();
// void wallpaper_draw();
// void gfx_SetUpCFB();
void PreRender_setup_savebuf(PreRender* render, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void PreRender_init(PreRender* render);
void PreRender_setup_renderbuf(PreRender* render, s32 arg1, s32 arg2, s32 arg3, void* arg4);
void PreRender_cleanup(PreRender* render);
// void PreRender_TransBufferCopy();
// void PreRender_TransBuffer();
// void PreRender_TransBuffer1_env();
// void PreRender_TransBuffer1();
// void PreRender_TransBuffer2();
// void PreRender_ShowCoveredge();
// void PreRender_CopyRGBC();
// void PreRender_saveZBuffer();
void PreRender_saveFrameBuffer(PreRender* render, Gfx** gfx);
void PreRender_saveCVG(PreRender* render, Gfx** gfx);
// void PreRender_loadZBuffer();
// void PreRender_loadFrameBuffer();
// void PreRender_loadFrameBufferAlpha();
void PreRender_loadFrameBufferCopy(PreRender* render, Gfx** gfx);
// void ASAlgorithm();
// void AntiAliasFilter();
void PreRender_ConvertFrameBuffer_fg(PreRender* render);
// void PreRender_ConvertFrameBuffer();

#endif
