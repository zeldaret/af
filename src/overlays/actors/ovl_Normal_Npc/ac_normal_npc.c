#include "ac_normal_npc.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aNOR_actor_ct(Actor* thisx, Game_Play* game_play);
void aNOR_actor_dt(Actor* thisx, Game_Play* game_play);
void aNOR_actor_init(Actor* thisx, Game_Play* game_play);
void aNOR_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Normal_Npc_Profile = {
    /* */ ACTOR_NORMAL_NPC,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Normal_Npc),
    /* */ aNOR_actor_ct,
    /* */ aNOR_actor_dt,
    /* */ aNOR_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aNOR_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Normal_Npc/ac_normal_npc/aNOR_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Normal_Npc/ac_normal_npc/aNOR_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Normal_Npc/ac_normal_npc/aNOR_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Normal_Npc/ac_normal_npc/aNOR_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Normal_Npc/ac_normal_npc/func_809A5B4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Normal_Npc/ac_normal_npc/func_809A5B78_jp.s")
