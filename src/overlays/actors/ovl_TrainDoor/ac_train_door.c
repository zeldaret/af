#include "ac_train_door.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTRD_actor_ct(Actor* thisx, Game_Play* play);
void aTRD_actor_dt(Actor* thisx, Game_Play* play);
void aTRD_actor_move(Actor* thisx, Game_Play* play);
void aTRD_actor_draw(Actor* thisx, Game_Play* play);

#if 0
ActorProfile TrainDoor_Profile = {
    /* */ ACTOR_TRAIN_DOOR,
    /* */ ACTOR_PART_4,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0xA011,
    /* */ OBJECT_11,
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
