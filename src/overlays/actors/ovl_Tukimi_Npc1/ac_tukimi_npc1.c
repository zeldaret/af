#include "ac_tukimi_npc1.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTM1_actor_ct(Actor* thisx, Game_Play* game_play);
void aTM1_actor_dt(Actor* thisx, Game_Play* game_play);
void aTM1_actor_init(Actor* thisx, Game_Play* game_play);
void aTM1_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Tukimi_Npc1_Profile = {
    /* */ ACTOR_TUKIMI_NPC1,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Tukimi_Npc1),
    /* */ aTM1_actor_ct,
    /* */ aTM1_actor_dt,
    /* */ aTM1_actor_init,
    /* */ (void*)none_proc1,
    /* */ aTM1_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc1/ac_tukimi_npc1/aTM1_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc1/ac_tukimi_npc1/aTM1_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc1/ac_tukimi_npc1/aTM1_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc1/ac_tukimi_npc1/aTM1_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc1/ac_tukimi_npc1/func_809E0304_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc1/ac_tukimi_npc1/func_809E0344_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc1/ac_tukimi_npc1/func_809E0370_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc1/ac_tukimi_npc1/func_809E0390_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc1/ac_tukimi_npc1/func_809E03A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc1/ac_tukimi_npc1/func_809E03E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc1/ac_tukimi_npc1/func_809E0414_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc1/ac_tukimi_npc1/func_809E0488_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc1/ac_tukimi_npc1/func_809E04B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc1/ac_tukimi_npc1/func_809E04E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc1/ac_tukimi_npc1/func_809E05CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc1/ac_tukimi_npc1/func_809E06D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc1/ac_tukimi_npc1/func_809E0704_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc1/ac_tukimi_npc1/func_809E0820_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc1/ac_tukimi_npc1/func_809E0878_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc1/ac_tukimi_npc1/func_809E08C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc1/ac_tukimi_npc1/func_809E08F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc1/ac_tukimi_npc1/func_809E0930_jp.s")
