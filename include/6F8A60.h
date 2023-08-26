#ifndef C_6F8A60_H
#define C_6F8A60_H

#include "ultra64.h"

struct LBRTCTime;

// void func_800D4DC0_jp();
// void func_800D4E20_jp();
// void func_800D4E94_jp();
// void func_800D4F18_jp();
// void func_800D4F6C_jp();
// void func_800D4FB8_jp();
// void func_800D5004_jp();
void lbRTC_GetTime(struct LBRTCTime* time);
// void func_800D5104_jp();
// void func_800D5164_jp();
s32 func_800D51E0_jp(struct LBRTCTime* time1, struct LBRTCTime* time2, s32 arg2);
s32 func_800D52C0_jp(struct LBRTCTime* arg0, struct LBRTCTime* arg1);
// void func_800D53A4_jp();
// void func_800D53DC_jp();
// void func_800D5414_jp();
u32 func_800D5480_jp(struct LBRTCTime* time1, struct LBRTCTime* time2);
// void func_800D54DC_jp();
// void func_800D56B8_jp();
// void func_800D56CC_jp();
// void func_800D572C_jp();
// void func_800D579C_jp();
// void func_800D57FC_jp();
// void func_800D585C_jp();
// void func_800D58BC_jp();
// void func_800D5930_jp();
// void func_800D5944_jp();
// void func_800D59E8_jp();
// void func_800D5A8C_jp();
// void func_800D5B34_jp();
// void func_800D5BDC_jp();
// void func_800D5C84_jp();
// void func_800D5CF8_jp();
void lbRTC_TimeCopy(struct LBRTCTime* dst, struct LBRTCTime* src);
// void func_800D5D94_jp();

#endif
