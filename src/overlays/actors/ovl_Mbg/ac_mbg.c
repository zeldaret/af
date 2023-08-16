#include "ac_mbg.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Mbg_Actor_ct(Actor* thisx, PlayState* play);
void Mbg_Actor_dt(Actor* thisx, PlayState* play);
void Mbg_Actor_move(Actor* thisx, PlayState* play);
void Mbg_Actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Mbg_Profile = {
    /* */ 12,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 32771,
    /* */ 3,
    /* */ sizeof(Mbg),
    /* */ Mbg_Actor_ct,
    /* */ Mbg_Actor_dt,
    /* */ Mbg_Actor_move,
    /* */ Mbg_Actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mbg/ac_mbg/Mbg_Actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mbg/ac_mbg/Mbg_Actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mbg/ac_mbg/Mbg_Actor_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mbg/ac_mbg/Mbg_Actor_move.s")
