#include "ac_t_npc_sao.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTNS_actor_ct(Actor* thisx, PlayState* play);
void aTNS_actor_move(Actor* thisx, PlayState* play);
void aTNS_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile T_NpcSao_Profile = {
    /* */ 109,
    /* */ ACTOR_PART_4,
    /* */ 48,
    /* */ 0,
    /* */ 370,
    /* */ sizeof(T_NpcSao),
    /* */ aTNS_actor_ct,
    /* */ (ActorFunc)none_proc1,
    /* */ aTNS_actor_move,
    /* */ aTNS_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_NpcSao/ac_t_npc_sao/aTNS_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_NpcSao/ac_t_npc_sao/func_80A20FC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_NpcSao/ac_t_npc_sao/func_80A20FE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_NpcSao/ac_t_npc_sao/aTNS_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_NpcSao/ac_t_npc_sao/aTNS_actor_draw.s")