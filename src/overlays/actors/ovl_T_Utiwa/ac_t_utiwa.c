#include "ac_t_utiwa.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTUT_actor_ct(Actor* thisx, PlayState* play);
void aTUT_actor_move(Actor* thisx, PlayState* play);
void aTUT_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile T_Utiwa_Profile = {
    /* */ 87,
    /* */ ACTOR_PART_4,
    /* */ 48,
    /* */ 0,
    /* */ 53,
    /* */ sizeof(T_Utiwa),
    /* */ aTUT_actor_ct,
    /* */ (ActorFunc)none_proc1,
    /* */ aTUT_actor_move,
    /* */ aTUT_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Utiwa/ac_t_utiwa/aTUT_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Utiwa/ac_t_utiwa/func_80A1FAC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Utiwa/ac_t_utiwa/func_80A1FB2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Utiwa/ac_t_utiwa/func_80A1FB4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Utiwa/ac_t_utiwa/func_80A1FB6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Utiwa/ac_t_utiwa/func_80A1FB8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Utiwa/ac_t_utiwa/aTUT_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Utiwa/ac_t_utiwa/aTUT_actor_draw.s")
