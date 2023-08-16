#include "ac_npc_engineer.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aNEG_actor_ct(Actor* thisx, PlayState* play);
void aNEG_actor_dt(Actor* thisx, PlayState* play);
void aNEG_actor_init(Actor* thisx, PlayState* play);
void aNEG_actor_save(Actor* thisx, PlayState* play);

#if 0
ActorProfile Npc_Engineer_Profile = {
    /* */ 29,
    /* */ ACTOR_PART_NPC,
    /* */ 536870928,
    /* */ 0,
    /* */ 3,
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
