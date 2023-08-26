#include "ac_arrange_ftr.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Arrange_Furniture_Actor_ct(Actor* thisx, Game_Play* gamePlay);
void Arrange_Furniture_Actor_dt(Actor* thisx, Game_Play* gamePlay);
void Arrange_Furniture_Actor_move(Actor* thisx, Game_Play* gamePlay);
void Arrange_Furniture_Actor_draw(Actor* thisx, Game_Play* gamePlay);

#if 0
ActorProfile Arrange_Furniture_Profile = {
    /* */ ACTOR_ARRANGE_FURNITURE,
    /* */ ACTOR_PART_4,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x8007,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Arrange_Furniture),
    /* */ Arrange_Furniture_Actor_ct,
    /* */ Arrange_Furniture_Actor_dt,
    /* */ Arrange_Furniture_Actor_move,
    /* */ Arrange_Furniture_Actor_draw,
    /* */ NULL,
};
#endif

// clang-format off
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Arrange_Furniture/ac_arrange_ftr/Arrange_Furniture_Actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Arrange_Furniture/ac_arrange_ftr/Arrange_Furniture_Actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Arrange_Furniture/ac_arrange_ftr/Arrange_Furniture_Actor_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Arrange_Furniture/ac_arrange_ftr/Arrange_Furniture_Actor_move.s")
// clang-format on
