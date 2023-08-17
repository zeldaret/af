#include "ac_turi.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTUR_actor_ct(Actor* thisx, PlayState* play);
void aTUR_actor_dt(Actor* thisx, PlayState* play);
void aTUR_actor_init(Actor* thisx, PlayState* play);
void aTUR_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Turi_Profile = {
    /* */ ACTOR_TURI,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x5837,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Turi),
    /* */ aTUR_actor_ct,
    /* */ aTUR_actor_dt,
    /* */ aTUR_actor_init,
    /* */ aTUR_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi/ac_turi/aTUR_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi/ac_turi/aTUR_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi/ac_turi/func_80A8FDE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi/ac_turi/func_80A8FE28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi/ac_turi/func_80A8FE38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi/ac_turi/func_80A8FEA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi/ac_turi/func_80A8FECC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi/ac_turi/func_80A8FF08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi/ac_turi/func_80A8FF2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi/ac_turi/func_80A8FFEC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi/ac_turi/func_80A90124_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi/ac_turi/func_80A902CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi/ac_turi/func_80A90334_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi/ac_turi/func_80A90530_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi/ac_turi/func_80A90540_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi/ac_turi/func_80A90560_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi/ac_turi/aTUR_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi/ac_turi/aTUR_actor_draw.s")
