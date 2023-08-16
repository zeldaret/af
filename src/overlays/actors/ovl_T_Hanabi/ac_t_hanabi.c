#include "ac_t_hanabi.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTHB_actor_ct(Actor* thisx, PlayState* play);
void aTHB_actor_dt(Actor* thisx, PlayState* play);
void aTHB_actor_move(Actor* thisx, PlayState* play);
void aTHB_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile T_Hanabi_Profile = {
    /* */ ACTOR_T_HANABI,
    /* */ ACTOR_PART_4,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ OBJECT_53,
    /* */ sizeof(T_Hanabi),
    /* */ aTHB_actor_ct,
    /* */ aTHB_actor_dt,
    /* */ aTHB_actor_move,
    /* */ aTHB_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Hanabi/ac_t_hanabi/aTHB_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Hanabi/ac_t_hanabi/aTHB_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Hanabi/ac_t_hanabi/func_80A1FE14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Hanabi/ac_t_hanabi/func_80A1FE7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Hanabi/ac_t_hanabi/func_80A1FE9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Hanabi/ac_t_hanabi/func_80A1FEBC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Hanabi/ac_t_hanabi/func_80A1FEDC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Hanabi/ac_t_hanabi/aTHB_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Hanabi/ac_t_hanabi/aTHB_actor_draw.s")
