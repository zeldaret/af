#include "ac_lotus.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aLOT_actor_ct(Actor* thisx, PlayState* play);
void aLOT_actor_dt(Actor* thisx, PlayState* play);
void aLOT_actor_init(Actor* thisx, PlayState* play);
void aLOT_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Lotus_Profile = {
    /* */ ACTOR_LOTUS,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x5840,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Lotus),
    /* */ aLOT_actor_ct,
    /* */ aLOT_actor_dt,
    /* */ aLOT_actor_init,
    /* */ aLOT_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Lotus/ac_lotus/aLOT_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Lotus/ac_lotus/aLOT_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Lotus/ac_lotus/func_80A9EE40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Lotus/ac_lotus/func_80A9EE60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Lotus/ac_lotus/func_80A9EF04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Lotus/ac_lotus/func_80A9EF6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Lotus/ac_lotus/func_80A9F004_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Lotus/ac_lotus/aLOT_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Lotus/ac_lotus/func_80A9F0F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Lotus/ac_lotus/aLOT_actor_draw.s")
