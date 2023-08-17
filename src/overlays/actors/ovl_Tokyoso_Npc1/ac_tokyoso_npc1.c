#include "ac_tokyoso_npc1.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTKN1_actor_ct(Actor* thisx, Game_Play* game_play);
void aTKN1_actor_dt(Actor* thisx, Game_Play* game_play);
void aTKN1_actor_init(Actor* thisx, Game_Play* game_play);
void aTKN1_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Tokyoso_Npc1_Profile = {
    /* */ ACTOR_TOKYOSO_NPC1,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0xD02E,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Tokyoso_Npc1),
    /* */ aTKN1_actor_ct,
    /* */ aTKN1_actor_dt,
    /* */ aTKN1_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aTKN1_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/aTKN1_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/aTKN1_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/aTKN1_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/aTKN1_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A74BDC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A74C78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A74D0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A74D50_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A74D9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A74DDC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A74EEC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A74F84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A75050_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A750E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A75184_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A751F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A75234_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A75300_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A75494_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A75580_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A755FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A75648_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A75714_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A75744_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A75840_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A758C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A7594C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A759EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A75AF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A75C94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A75CDC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A75D84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A75DCC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A75E0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A75EC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc1/ac_tokyoso_npc1/func_80A75F0C_jp.s")
