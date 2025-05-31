#ifndef CFBINFO_H
#define CFBINFO_H

#include "ultra64.h"
#include "unk.h"

typedef struct CfbInfo {
    /* 0x00 */ void* unk_00;
    /* 0x04 */ UNK_PTR swapBuffer;
    /* 0x08 */ u8 state;
    /* 0x09 */ s8 unk_09;
    /* 0x0A */ u8 unk_0A;
    /* 0x0B */ s8 unk_0B;
    /* 0x0C */ OSViMode* viMode;
    /* 0x10 */ s32 viFeatures;
    /* 0x14 */ f32 xScale;
    /* 0x18 */ f32 yScale;
} CfbInfo; // size = 0x1C


CfbInfo* func_800D2C10_jp(void);
void func_800D2CB4_jp(CfbInfo* cfb);
void func_800D2CDC_jp(CfbInfo* cfb);

#endif
