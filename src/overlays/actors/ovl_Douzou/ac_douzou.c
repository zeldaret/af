#include "ac_douzou.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aDOU_actor_ct(Actor* thisx, PlayState* play);
void aDOU_actor_dt(Actor* thisx, PlayState* play);
void aDOU_actor_init(Actor* thisx, PlayState* play);
void aDOU_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Douzou_Profile = {
    /* */ ACTOR_DOUZOU,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x5842,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Douzou),
    /* */ aDOU_actor_ct,
    /* */ aDOU_actor_dt,
    /* */ aDOU_actor_init,
    /* */ aDOU_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Douzou/ac_douzou/aDOU_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Douzou/ac_douzou/aDOU_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Douzou/ac_douzou/func_80AA5C30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Douzou/ac_douzou/func_80AA5D54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Douzou/ac_douzou/func_80AA5D94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Douzou/ac_douzou/func_80AA5E28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Douzou/ac_douzou/func_80AA5ED8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Douzou/ac_douzou/func_80AA5FAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Douzou/ac_douzou/func_80AA6164_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Douzou/ac_douzou/func_80AA6304_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Douzou/ac_douzou/func_80AA63E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Douzou/ac_douzou/func_80AA64A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Douzou/ac_douzou/func_80AA6744_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Douzou/ac_douzou/func_80AA67DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Douzou/ac_douzou/aDOU_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Douzou/ac_douzou/func_80AA68D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Douzou/ac_douzou/aDOU_actor_draw.s")
