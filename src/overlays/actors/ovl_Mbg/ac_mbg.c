#include "ac_mbg.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Mbg_Actor_ct(Actor* thisx, Game_Play* gamePlay);
void Mbg_Actor_dt(Actor* thisx, Game_Play* gamePlay);
void Mbg_Actor_move(Actor* thisx, Game_Play* gamePlay);
void Mbg_Actor_draw(Actor* thisx, Game_Play* gamePlay);

#if 0
ActorProfile Mbg_Profile = {
    /* */ ACTOR_MBG,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x8003,
    /* */ GAMEPLAY_KEEP,
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
