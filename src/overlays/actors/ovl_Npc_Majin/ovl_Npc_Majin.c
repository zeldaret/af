#include "ovl_Npc_Majin.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aMJN_actor_ct(Actor* thisx, Game_Play* game_play);
void aMJN_actor_dt(Actor* thisx, Game_Play* game_play);
void aMJN_actor_init(Actor* thisx, Game_Play* game_play);
void aMJN_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Npc_Majin_Profile = {
    /* */ ACTOR_NPC_MAJIN,
    /* */ ACTOR_PART_NPC,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0xD03E,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Npc_Majin),
    /* */ aMJN_actor_ct,
    /* */ aMJN_actor_dt,
    /* */ aMJN_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aMJN_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin/ovl_Npc_Majin/aMJN_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin/ovl_Npc_Majin/aMJN_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin/ovl_Npc_Majin/aMJN_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin/ovl_Npc_Majin/aMJN_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin/ovl_Npc_Majin/func_809B3350_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin/ovl_Npc_Majin/func_809B3388_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin/ovl_Npc_Majin/func_809B33C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin/ovl_Npc_Majin/func_809B3430_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin/ovl_Npc_Majin/func_809B3464_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin/ovl_Npc_Majin/func_809B34C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin/ovl_Npc_Majin/func_809B3530_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin/ovl_Npc_Majin/func_809B3550_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin/ovl_Npc_Majin/func_809B3560_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin/ovl_Npc_Majin/func_809B3590_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin/ovl_Npc_Majin/func_809B3630_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin/ovl_Npc_Majin/func_809B36E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin/ovl_Npc_Majin/func_809B371C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin/ovl_Npc_Majin/func_809B3770_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin/ovl_Npc_Majin/func_809B3884_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin/ovl_Npc_Majin/func_809B38A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin/ovl_Npc_Majin/func_809B3918_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin/ovl_Npc_Majin/func_809B3948_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin/ovl_Npc_Majin/func_809B3988_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin/ovl_Npc_Majin/func_809B39F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin/ovl_Npc_Majin/func_809B3A24_jp.s")
