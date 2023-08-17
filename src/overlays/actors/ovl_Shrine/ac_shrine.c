#include "ac_shrine.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aSHR_actor_ct(Actor* thisx, Game_Play* game_play);
void aSHR_actor_dt(Actor* thisx, Game_Play* game_play);
void aSHR_actor_init(Actor* thisx, Game_Play* game_play);
void aSHR_actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Shrine_Profile = {
    /* */ ACTOR_SHRINE,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x5825,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Shrine),
    /* */ aSHR_actor_ct,
    /* */ aSHR_actor_dt,
    /* */ aSHR_actor_init,
    /* */ aSHR_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shrine/ac_shrine/func_80A0A1F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shrine/ac_shrine/aSHR_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shrine/ac_shrine/aSHR_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shrine/ac_shrine/func_80A0A3F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shrine/ac_shrine/func_80A0A410_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shrine/ac_shrine/func_80A0A448_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shrine/ac_shrine/func_80A0A468_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shrine/ac_shrine/func_80A0A498_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shrine/ac_shrine/func_80A0A61C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shrine/ac_shrine/func_80A0A6CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shrine/ac_shrine/func_80A0A730_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shrine/ac_shrine/func_80A0A7A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shrine/ac_shrine/func_80A0A928_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shrine/ac_shrine/func_80A0AB08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shrine/ac_shrine/func_80A0AB44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shrine/ac_shrine/func_80A0AB64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shrine/ac_shrine/func_80A0ABE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shrine/ac_shrine/aSHR_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shrine/ac_shrine/func_80A0AD14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shrine/ac_shrine/func_80A0AED8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shrine/ac_shrine/func_80A0AF98_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shrine/ac_shrine/aSHR_actor_draw.s")
