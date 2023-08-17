#include "ac_tukimi_npc0.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTM0_actor_ct(Actor* thisx, Game_Play* game_play);
void aTM0_actor_dt(Actor* thisx, Game_Play* game_play);
void aTM0_actor_init(Actor* thisx, Game_Play* game_play);
void aTM0_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Tukimi_Npc0_Profile = {
    /* */ ACTOR_TUKIMI_NPC0,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Tukimi_Npc0),
    /* */ aTM0_actor_ct,
    /* */ aTM0_actor_dt,
    /* */ aTM0_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aTM0_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc0/ac_tukimi_npc0/aTM0_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc0/ac_tukimi_npc0/aTM0_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc0/ac_tukimi_npc0/aTM0_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc0/ac_tukimi_npc0/aTM0_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc0/ac_tukimi_npc0/func_809DFB14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc0/ac_tukimi_npc0/func_809DFB48_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc0/ac_tukimi_npc0/func_809DFB74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc0/ac_tukimi_npc0/func_809DFB94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc0/ac_tukimi_npc0/func_809DFBA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc0/ac_tukimi_npc0/func_809DFBCC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc0/ac_tukimi_npc0/func_809DFBFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc0/ac_tukimi_npc0/func_809DFC54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc0/ac_tukimi_npc0/func_809DFC84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc0/ac_tukimi_npc0/func_809DFCB4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc0/ac_tukimi_npc0/func_809DFD88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc0/ac_tukimi_npc0/func_809DFE80_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc0/ac_tukimi_npc0/func_809DFEB0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc0/ac_tukimi_npc0/func_809DFFB0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc0/ac_tukimi_npc0/func_809DFFE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc0/ac_tukimi_npc0/func_809E0010_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi_Npc0/ac_tukimi_npc0/func_809E0050_jp.s")
