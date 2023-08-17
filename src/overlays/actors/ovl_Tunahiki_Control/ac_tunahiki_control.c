#include "ac_tunahiki_control.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTNC_actor_ct(Actor* thisx, Game_Play* play);
void aTNC_actor_dt(Actor* thisx, Game_Play* play);
void aTNC_actor_move(Actor* thisx, Game_Play* play);

#if 0
ActorProfile Tunahiki_Control_Profile = {
    /* */ ACTOR_TUNAHIKI,
    /* */ ACTOR_PART_7,
    /* */ ACTOR_FLAG_10,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Tunahiki_Control),
    /* */ aTNC_actor_ct,
    /* */ aTNC_actor_dt,
    /* */ aTNC_actor_move,
    /* */ (ActorFunc)none_proc1,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Control/ac_tunahiki_control/aTNC_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Control/ac_tunahiki_control/aTNC_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Control/ac_tunahiki_control/aTNC_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Control/ac_tunahiki_control/func_80A918C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Control/ac_tunahiki_control/func_80A919E8_jp.s")
