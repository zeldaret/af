#include "ac_normal_npc.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aNOR_actor_ct(Actor* thisx, PlayState* play);
void aNOR_actor_dt(Actor* thisx, PlayState* play);
void aNOR_actor_init(Actor* thisx, PlayState* play);
void aNOR_actor_save(Actor* thisx, PlayState* play);

#if 0
ActorProfile Normal_Npc_Profile = {
    /* */ 113,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0,
    /* */ 3,
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