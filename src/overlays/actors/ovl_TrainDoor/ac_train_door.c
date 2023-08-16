#include "ac_train_door.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTRD_actor_ct(Actor* thisx, PlayState* play);
void aTRD_actor_dt(Actor* thisx, PlayState* play);
void aTRD_actor_move(Actor* thisx, PlayState* play);
void aTRD_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile TrainDoor_Profile = {
    /* */ 19,
    /* */ ACTOR_PART_4,
    /* */ 48,
    /* */ 40977,
    /* */ 11,
    /* */ sizeof(TrainDoor),
    /* */ aTRD_actor_ct,
    /* */ aTRD_actor_dt,
    /* */ aTRD_actor_move,
    /* */ aTRD_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_TrainDoor/ac_train_door/aTRD_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_TrainDoor/ac_train_door/aTRD_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_TrainDoor/ac_train_door/func_80972AB0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_TrainDoor/ac_train_door/aTRD_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_TrainDoor/ac_train_door/aTRD_actor_draw.s")
