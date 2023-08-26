#ifndef C_6B8A70_H
#define C_6B8A70_H

#include "ultra64.h"

struct AnmPersonalId;
struct LandInfo;

// void func_80094DD0_jp();
// void func_80094E10_jp();
s32 func_80094E38_jp(u8* dst, u8* src);
s32 func_80094E90_jp(u8* dstName, u16 dstId, u8* srcName, u16 srcId);
void func_80094EE0_jp(u8* landName);
void mLd_CopyLandName(u8* dst, u8* src);
// void func_80094F24_jp();
// void func_80094F84_jp();
// void func_8009504C_jp();
struct LandInfo* func_800950D8_jp(void);
// void func_800950E8_jp();
// void func_8009519C_jp();
s32 mLd_PlayerManKindCheck(void);
s32 func_800951E4_jp(u8* landName, u16 landId);
// void func_80095218_jp();
void mLd_LandDataInit(void);

#endif
