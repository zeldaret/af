#include "ac_t_tumbler.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTTB_actor_ct(Actor* thisx, Game_Play* game_play);
void aTTB_actor_move(Actor* thisx, Game_Play* game_play);
void aTTB_actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile T_Tumbler_Profile = {
    /* */ ACTOR_T_TUMBLER,
    /* */ ACTOR_PART_4,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ OBJECT_371,
    /* */ sizeof(T_Tumbler),
    /* */ aTTB_actor_ct,
    /* */ (ActorFunc)none_proc1,
    /* */ aTTB_actor_move,
    /* */ aTTB_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Tumbler/ac_t_tumbler/aTTB_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Tumbler/ac_t_tumbler/func_80A20C84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Tumbler/ac_t_tumbler/func_80A20CEC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Tumbler/ac_t_tumbler/func_80A20D0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Tumbler/ac_t_tumbler/func_80A20D2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Tumbler/ac_t_tumbler/func_80A20D4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Tumbler/ac_t_tumbler/aTTB_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Tumbler/ac_t_tumbler/aTTB_actor_draw.s")
