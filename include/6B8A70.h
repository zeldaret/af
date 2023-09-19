#ifndef C_6B8A70_H
#define C_6B8A70_H

#include "ultra64.h"
#include "unk.h"

typedef struct LandName {
    /* 0x0 */ UNK_TYPE1 unk_0[0x6];
} LandName; // size = 0x6

// void func_80094DD0_jp();
// void func_80094E10_jp();
// void func_80094E38_jp();
// void func_80094E90_jp();
// void func_80094EE0_jp();
void mLd_CopyLandName(LandName* arg0, LandName* arg1);
// void func_80094F24_jp();
// void func_80094F84_jp();
// void func_8009504C_jp();
// void func_800950D8_jp();
// void func_800950E8_jp();
// void func_8009519C_jp();
// void mLd_PlayerManKindCheck();
// void func_800951E4_jp();
// void func_80095218_jp();
void mLd_LandDataInit(void);

#endif
