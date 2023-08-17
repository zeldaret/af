#include "ac_t_cracker.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTCR_actor_ct(Actor* thisx, Game_Play* game_play);
void aTCR_actor_move(Actor* thisx, Game_Play* game_play);
void aTCR_actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile T_Cracker_Profile = {
    /* */ ACTOR_T_CRACKER,
    /* */ ACTOR_PART_4,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ OBJECT_395,
    /* */ sizeof(T_Cracker),
    /* */ aTCR_actor_ct,
    /* */ (ActorFunc)none_proc1,
    /* */ aTCR_actor_move,
    /* */ aTCR_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Cracker/ac_t_cracker/aTCR_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Cracker/ac_t_cracker/func_80A20154_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Cracker/ac_t_cracker/func_80A201BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Cracker/ac_t_cracker/func_80A201DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Cracker/ac_t_cracker/func_80A201FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Cracker/ac_t_cracker/func_80A2021C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Cracker/ac_t_cracker/aTCR_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Cracker/ac_t_cracker/aTCR_actor_draw.s")
