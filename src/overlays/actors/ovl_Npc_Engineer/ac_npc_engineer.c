#include "ac_npc_engineer.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aNEG_actor_ct(Actor* thisx, Game_Play* game_play);
void aNEG_actor_dt(Actor* thisx, Game_Play* game_play);
void aNEG_actor_init(Actor* thisx, Game_Play* game_play);
void aNEG_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Npc_Engineer_Profile = {
    /* */ ACTOR_NPC_ENGINEER,
    /* */ ACTOR_PART_NPC,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20000000,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Npc_Engineer),
    /* */ aNEG_actor_ct,
    /* */ aNEG_actor_dt,
    /* */ aNEG_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aNEG_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Engineer/ac_npc_engineer/aNEG_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Engineer/ac_npc_engineer/aNEG_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Engineer/ac_npc_engineer/aNEG_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Engineer/ac_npc_engineer/aNEG_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Engineer/ac_npc_engineer/func_809AEF28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Engineer/ac_npc_engineer/func_809AEF54_jp.s")
