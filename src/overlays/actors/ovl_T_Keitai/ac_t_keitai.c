#include "ac_t_keitai.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTKT_actor_ct(Actor* thisx, PlayState* play);
void aTKT_actor_move(Actor* thisx, PlayState* play);
void aTKT_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile T_Keitai_Profile = {
    /* */ 20,
    /* */ ACTOR_PART_4,
    /* */ 48,
    /* */ 0,
    /* */ 45,
    /* */ sizeof(T_Keitai),
    /* */ aTKT_actor_ct,
    /* */ (ActorFunc)none_proc1,
    /* */ aTKT_actor_move,
    /* */ aTKT_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Keitai/ac_t_keitai/aTKT_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Keitai/ac_t_keitai/func_80A1F58C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Keitai/ac_t_keitai/func_80A1F634_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Keitai/ac_t_keitai/func_80A1F6C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Keitai/ac_t_keitai/func_80A1F6E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Keitai/ac_t_keitai/func_80A1F700_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Keitai/ac_t_keitai/func_80A1F720_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Keitai/ac_t_keitai/aTKT_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Keitai/ac_t_keitai/aTKT_actor_draw.s")
