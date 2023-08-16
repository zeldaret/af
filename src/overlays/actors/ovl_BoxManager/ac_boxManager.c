#include "ac_boxManager.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void BoxManager_Actor_ct(Actor* thisx, PlayState* play);
void BoxManager_Actor_dt(Actor* thisx, PlayState* play);
void BoxManager_Actor_move(Actor* thisx, PlayState* play);
void BoxManager_Actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile BoxManager_Profile = {
    /* */ 14,
    /* */ ACTOR_PART_4,
    /* */ 48,
    /* */ 32773,
    /* */ 20,
    /* */ sizeof(BoxManager),
    /* */ BoxManager_Actor_ct,
    /* */ BoxManager_Actor_dt,
    /* */ BoxManager_Actor_move,
    /* */ BoxManager_Actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BoxManager/ac_boxManager/BoxManager_Actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BoxManager/ac_boxManager/BoxManager_Actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BoxManager/ac_boxManager/BoxManager_Actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BoxManager/ac_boxManager/BoxManager_Actor_draw.s")
