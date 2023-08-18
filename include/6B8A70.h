#ifndef C_6B8A70_H
#define C_6B8A70_H

#include "ultra64.h"

struct AnmPersonalID_c;
struct mLd_land_info_c;
union memuni_u;

// void func_80094DD0_jp();
// void func_80094E10_jp();
s32 func_80094E38_jp(u8* dst, u8* src);
s32 func_80094E90_jp(union memuni_u* dst, u16 dst_id, union memuni_u* src, u16 src_id);
void func_80094EE0_jp(u8* land_name);
void mLd_CopyLandName(u8* dst, u8* src);
// void func_80094F24_jp();
// void func_80094F84_jp();
// void func_8009504C_jp();
struct mLd_land_info_c* func_800950D8_jp(void);
// void func_800950E8_jp();
// void func_8009519C_jp();
s32 mLd_PlayerManKindCheck(void);
s32 func_800951E4_jp(u8* land_name, u16 land_id);
// void func_80095218_jp();
void mLd_LandDataInit(void);

#endif
