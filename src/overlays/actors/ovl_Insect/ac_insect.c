#include "ac_insect.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aINS_actor_ct(Actor* thisx, PlayState* play);
void aINS_actor_dt(Actor* thisx, PlayState* play);
void aINS_actor_move(Actor* thisx, PlayState* play);
void aINS_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Insect_Profile = {
    /* */ ACTOR_INSECT,
    /* */ ACTOR_PART_7,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Insect),
    /* */ aINS_actor_ct,
    /* */ aINS_actor_dt,
    /* */ aINS_actor_move,
    /* */ aINS_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Insect/ac_insect/aINS_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Insect/ac_insect/aINS_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Insect/ac_insect/func_80A102B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Insect/ac_insect/func_80A10314_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Insect/ac_insect/func_80A1035C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Insect/ac_insect/func_80A103F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Insect/ac_insect/func_80A10494_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Insect/ac_insect/func_80A104F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Insect/ac_insect/func_80A10558_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Insect/ac_insect/func_80A108AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Insect/ac_insect/func_80A109A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Insect/ac_insect/func_80A10A10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Insect/ac_insect/func_80A10A20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Insect/ac_insect/func_80A10ADC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Insect/ac_insect/func_80A10B88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Insect/ac_insect/func_80A10D88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Insect/ac_insect/func_80A10E54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Insect/ac_insect/func_80A10EF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Insect/ac_insect/aINS_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Insect/ac_insect/func_80A11264_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Insect/ac_insect/aINS_actor_draw.s")
