#ifndef PRE_RENDER_H
#define PRE_RENDER_H

#include "ultra64.h"

typedef struct ListAlloc {
    /* 0x0 */ struct ListAlloc* prev;
    /* 0x4 */ struct ListAlloc* next;
} ListAlloc; // size = 0x8

typedef struct {
    /* 0x00 */ char unk00[0x10];
    /* 0x10 */ UNK_PTR unk_10;
    /* 0x14 */ UNK_PTR unk_14;
    /* 0x18 */ UNK_PTR unk_18;
    /* 0x1C */ char unk1C[0x34];
} PreRender; // size = 0x50

// void wallpaper_draw1();
// void wallpaper_draw();
// void gfx_SetUpCFB();
void PreRender_setup_savebuf(PreRender* render, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void PreRender_init(PreRender* render);
void PreRender_setup_renderbuf(PreRender* render, s32 arg1, s32 arg2, void* arg3, void* arg4);
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
