#include "ac_arrange_ftr.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Arrange_Furniture_Actor_ct(Actor* thisx, PlayState* play);
void Arrange_Furniture_Actor_dt(Actor* thisx, PlayState* play);
void Arrange_Furniture_Actor_move(Actor* thisx, PlayState* play);
void Arrange_Furniture_Actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Arrange_Furniture_Profile = {
    /* */ 18,
    /* */ ACTOR_PART_4,
    /* */ 48,
    /* */ 32775,
    /* */ 3,
    /* */ sizeof(Arrange_Furniture),
    /* */ Arrange_Furniture_Actor_ct,
    /* */ Arrange_Furniture_Actor_dt,
    /* */ Arrange_Furniture_Actor_move,
    /* */ Arrange_Furniture_Actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Arrange_Furniture/ac_arrange_ftr/Arrange_Furniture_Actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Arrange_Furniture/ac_arrange_ftr/Arrange_Furniture_Actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Arrange_Furniture/ac_arrange_ftr/Arrange_Furniture_Actor_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Arrange_Furniture/ac_arrange_ftr/Arrange_Furniture_Actor_move.s")
