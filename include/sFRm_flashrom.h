#ifndef SFRM_FLASHROM_H
#define SFRM_FLASHROM_H

#include "ultra64.h"
#include "unk.h"

typedef struct FlashromRequest {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ UNK_TYPE1 unk_04[0x4];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
} FlashromRequest; // size >= 0x14

// void func_800CDB10_jp();
// void func_800CDBE0_jp();
// void func_800CDBF0_jp();
// void func_800CDC10_jp();
// void func_800CDC30_jp();
// void func_800CDCC0_jp();
// void func_800CDDE0_jp();
// void func_800CDE54_jp();
// void func_800CDECC_jp();
// void func_800CDEDC_jp();
// void func_800CDF78_jp();
// void func_800CE04C_jp();
// void func_800CE090_jp();
// void func_800CE0E8_jp();
// void func_800CE110_jp();
// void func_800CE120_jp();
// void func_800CE1CC_jp();
// void func_800CE328_jp();

#endif
