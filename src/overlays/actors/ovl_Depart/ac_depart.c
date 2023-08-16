#include "ac_depart.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aDPT_actor_ct(Actor* thisx, PlayState* play);
void aDPT_actor_dt(Actor* thisx, PlayState* play);
void aDPT_actor_init(Actor* thisx, PlayState* play);
void aDPT_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Depart_Profile = {
    /* */ ACTOR_DEPART,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x5807,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Depart),
    /* */ aDPT_actor_ct,
    /* */ aDPT_actor_dt,
    /* */ aDPT_actor_init,
    /* */ aDPT_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Depart/ac_depart/aDPT_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Depart/ac_depart/aDPT_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Depart/ac_depart/func_80A0226C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Depart/ac_depart/func_80A0229C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Depart/ac_depart/func_80A023A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Depart/ac_depart/func_80A023FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Depart/ac_depart/func_80A024D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Depart/ac_depart/func_80A025EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Depart/ac_depart/func_80A0262C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Depart/ac_depart/func_80A02738_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Depart/ac_depart/func_80A027D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Depart/ac_depart/func_80A02918_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Depart/ac_depart/func_80A0294C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Depart/ac_depart/func_80A02980_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Depart/ac_depart/func_80A02A88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Depart/ac_depart/aDPT_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Depart/ac_depart/func_80A02B78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Depart/ac_depart/func_80A02C0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Depart/ac_depart/aDPT_actor_draw.s")
