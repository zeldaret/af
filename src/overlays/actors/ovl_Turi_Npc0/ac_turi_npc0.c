#include "ac_turi_npc0.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void func_805900b0(Actor* thisx, PlayState* play);
void func_805901d8(Actor* thisx, PlayState* play);
void aTR0_actor_init(Actor* thisx, PlayState* play);
void aTR0_actor_save(Actor* thisx, PlayState* play);

#if 0
ActorProfile Turi_Npc0_Profile = {
    /* */ ACTOR_TURI_NPC0,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Turi_Npc0),
    /* */ func_805900b0,
    /* */ func_805901d8,
    /* */ aTR0_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aTR0_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi_Npc0/ac_turi_npc0/func_805900b0.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi_Npc0/ac_turi_npc0/aTR0_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi_Npc0/ac_turi_npc0/func_805901d8.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi_Npc0/ac_turi_npc0/aTR0_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi_Npc0/ac_turi_npc0/func_809E2D40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi_Npc0/ac_turi_npc0/func_809E2D80_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi_Npc0/ac_turi_npc0/func_809E2DAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi_Npc0/ac_turi_npc0/func_809E2DCC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi_Npc0/ac_turi_npc0/func_809E2E30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi_Npc0/ac_turi_npc0/func_809E2E64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi_Npc0/ac_turi_npc0/func_809E2EE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi_Npc0/ac_turi_npc0/func_809E2EFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi_Npc0/ac_turi_npc0/func_809E2F20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi_Npc0/ac_turi_npc0/func_809E2F48_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi_Npc0/ac_turi_npc0/func_809E2F78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi_Npc0/ac_turi_npc0/func_809E2FD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi_Npc0/ac_turi_npc0/func_809E3000_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi_Npc0/ac_turi_npc0/func_809E3030_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi_Npc0/ac_turi_npc0/func_809E311C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi_Npc0/ac_turi_npc0/func_809E3194_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi_Npc0/ac_turi_npc0/func_809E31C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi_Npc0/ac_turi_npc0/func_809E32C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi_Npc0/ac_turi_npc0/func_809E32F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi_Npc0/ac_turi_npc0/func_809E3324_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Turi_Npc0/ac_turi_npc0/func_809E3364_jp.s")
