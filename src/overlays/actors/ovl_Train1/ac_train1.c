#include "ac_train1.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTR1_actor_ct(Actor* thisx, PlayState* play);
void aTR1_actor_dt(Actor* thisx, PlayState* play);
void aTR1_actor_move(Actor* thisx, PlayState* play);
void aTR1_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Train1_Profile = {
    /* */ ACTOR_TRAIN1,
    /* */ ACTOR_PART_0,
    /* */ 536870928,
    /* */ 0x580B,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Train1),
    /* */ aTR1_actor_ct,
    /* */ aTR1_actor_dt,
    /* */ aTR1_actor_move,
    /* */ aTR1_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train1/ac_train1/aTR1_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train1/ac_train1/aTR1_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train1/ac_train1/func_80A0D3A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train1/ac_train1/func_80A0D3D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train1/ac_train1/func_80A0D444_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train1/ac_train1/func_80A0D480_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train1/ac_train1/func_80A0D558_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train1/ac_train1/func_80A0D5F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train1/ac_train1/func_80A0D708_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train1/ac_train1/aTR1_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train1/ac_train1/aTR1_actor_draw.s")
