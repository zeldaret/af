#include "ac_boxManager.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void BoxManager_Actor_ct(Actor* thisx, Game_Play* play);
void BoxManager_Actor_dt(Actor* thisx, Game_Play* play);
void BoxManager_Actor_move(Actor* thisx, Game_Play* play);
void BoxManager_Actor_draw(Actor* thisx, Game_Play* play);

#if 0
ActorProfile BoxManager_Profile = {
    /* */ ACTOR_BOX_MANAGER,
    /* */ ACTOR_PART_4,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x8005,
    /* */ OBJECT_20,
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
