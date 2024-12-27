#ifndef CFBINFO_H
#define CFBINFO_H

#include "ultra64.h"
#include "unk.h"

typedef struct cfbStruct {
    /* 0x00 */ void* unk_00;
    /* 0x04 */ UNK_PTR unk_04;
    /* 0x08 */ UNK_TYPE1 unk_08[0x1];
    /* 0x09 */ u8 unk_09;
    /* 0x0A */ u8 unk_0A;
    /* 0x0B */ u8 unk_0B;
    /* 0x0C */ OSViMode* unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
} cfbStruct; // size >= 0x1C

cfbStruct* func_800D2C10_jp(void);
// void func_800D2CB4_jp();
// void func_800D2CDC_jp();

#endif
