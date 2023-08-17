#include "ac_uki.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aUKI_actor_ct(Actor* thisx, Game_Play* play);
void aUKI_actor_dt(Actor* thisx, Game_Play* play);
void aUKI_actor_move(Actor* thisx, Game_Play* play);
void func_80A66978_jp(Actor* thisx, Game_Play* play);

#if 0
ActorProfile Uki_Profile = {
    /* */ ACTOR_UKI,
    /* */ ACTOR_PART_4,
    /* */ ACTOR_FLAG_10,
    /* */ 0x8012,
    /* */ OBJECT_48,
    /* */ sizeof(Uki),
    /* */ aUKI_actor_ct,
    /* */ aUKI_actor_dt,
    /* */ aUKI_actor_move,
    /* */ func_80A66978_jp,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/aUKI_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/aUKI_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/func_80A64B20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/func_80A64B68_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/func_80A64BAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/func_80A64BDC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/func_80A64C34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/func_80A64EB4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/func_80A64EF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/func_80A64FD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/func_80A650B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/func_80A65234_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/func_80A65464_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/func_80A655F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/func_80A65714_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/func_80A65754_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/func_80A65BA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/func_80A65C84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/func_80A65D48_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/func_80A65E78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/func_80A65F4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/func_80A65FC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/func_80A66048_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/func_80A661D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/func_80A66288_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/func_80A66434_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/func_80A66624_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/func_80A666AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/func_80A66714_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/aUKI_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/func_80A668AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Uki/ac_uki/func_80A66978_jp.s")
