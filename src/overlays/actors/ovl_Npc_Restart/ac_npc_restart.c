#include "ac_npc_restart.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aNRST_actor_ct(Actor* thisx, Game_Play* game_play);
void aNRST_actor_dt(Actor* thisx, Game_Play* game_play);
void aNRST_actor_init(Actor* thisx, Game_Play* game_play);
void aNRST_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Npc_Restart_Profile = {
    /* */ ACTOR_NPC_RESTART,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0xD06A,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Npc_Restart),
    /* */ aNRST_actor_ct,
    /* */ aNRST_actor_dt,
    /* */ aNRST_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aNRST_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Restart/ac_npc_restart/aNRST_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Restart/ac_npc_restart/aNRST_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Restart/ac_npc_restart/aNRST_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Restart/ac_npc_restart/aNRST_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Restart/ac_npc_restart/func_80AAC42C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Restart/ac_npc_restart/func_80AAC458_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Restart/ac_npc_restart/func_80AAC470_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Restart/ac_npc_restart/func_80AAC4B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Restart/ac_npc_restart/func_80AAC574_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Restart/ac_npc_restart/func_80AAC5B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Restart/ac_npc_restart/func_80AAC5D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Restart/ac_npc_restart/func_80AAC604_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Restart/ac_npc_restart/func_80AAC648_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Restart/ac_npc_restart/func_80AAC6B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Restart/ac_npc_restart/func_80AAC6E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Restart/ac_npc_restart/func_80AAC76C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Restart/ac_npc_restart/func_80AAC7EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Restart/ac_npc_restart/func_80AAC860_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Restart/ac_npc_restart/func_80AAC880_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Restart/ac_npc_restart/func_80AAC8BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Restart/ac_npc_restart/func_80AAC8F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Restart/ac_npc_restart/func_80AAC938_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Restart/ac_npc_restart/func_80AAC9A8_jp.s")
