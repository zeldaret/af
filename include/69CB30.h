#ifndef C_69CB30_H
#define C_69CB30_H

#include "ultra64.h"

struct Animal_c;
struct PrivateInfo;

s32 mCPk_PakOpen(void* arg0, s32 arg1);
// void func_80078EB4_jp();
// void func_80078EE0_jp();
// void func_80078F08_jp();
// void func_80078F34_jp();
// void func_80078FE8_jp();
// void func_80079030_jp();
// void func_80079080_jp();
// void mCPk_InitPak();
// void func_8007919C_jp();
// void func_8007920C_jp();
// void func_800792FC_jp();
// void func_80079378_jp();
// void func_800793A8_jp();
s32 mCPk_SavePak(struct PrivateInfo*, struct Animal_c*, void*);
s32 func_8007942C_jp(struct PrivateInfo*, struct Animal_c*, void*);
// void func_800794E4_jp();
// void func_8007967C_jp();
// void func_80079708_jp();
// void func_80079760_jp();
// void func_80079838_jp();
// void func_800798DC_jp();
// void func_80079A24_jp();
// void func_80079AAC_jp();
// void func_80079B28_jp();
// void func_80079BF8_jp();
// void func_80079D00_jp();
// void func_80079D50_jp();
// void func_80079E14_jp();
// void func_80079E54_jp();
// void func_80079EA4_jp();
// void func_80079EDC_jp();
// void func_80079F44_jp();
// void func_8007A008_jp();
void* mCPk_get_pkinfo(void);
// void func_8007A080_jp();

#endif
