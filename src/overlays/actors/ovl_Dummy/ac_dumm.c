#include "ac_dumm.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Dummy_Actor_ct(Actor* thisx, Game_Play* game_play);
void Dummy_Actor_dt(Actor* thisx, Game_Play* game_play);
void Dummy_Actor_move(Actor* thisx, Game_Play* game_play);
void Dummy_Actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Dummy_Profile = {
    /* */ ACTOR_DUMMY,
    /* */ ACTOR_PART_7,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Dummy),
    /* */ Dummy_Actor_ct,
    /* */ Dummy_Actor_dt,
    /* */ Dummy_Actor_move,
    /* */ Dummy_Actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Dummy/ac_dumm/Dummy_Actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Dummy/ac_dumm/Dummy_Actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Dummy/ac_dumm/Dummy_Actor_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Dummy/ac_dumm/Dummy_Actor_move.s")
