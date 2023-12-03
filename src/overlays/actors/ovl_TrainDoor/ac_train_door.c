#include "ac_train_door.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "m_rcp.h"
#include "6F5550.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTRD_actor_ct(Actor* actor, Game_Play* game_play);
void aTRD_actor_dt(Actor* actor, Game_Play* game_play);
void aTRD_actor_move(Actor* actor, Game_Play* game_play);
void aTRD_actor_draw(Actor* actor, Game_Play* game_play);

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

extern BaseSkeletonR cKF_bs_r_obj_romtrain_door;
extern BaseAnimationR cKF_ba_r_obj_romtrain_door;

void aTRD_actor_ct(Actor* actor, UNUSED Game_Play* game_play) {
    TrainDoor* traindoor = (TrainDoor*)actor;

    cKF_SkeletonInfo_R_ct(&traindoor->keyframe, &cKF_bs_r_obj_romtrain_door, NULL, traindoor->work, traindoor->target);
    cKF_SkeletonInfo_R_init(&traindoor->keyframe, traindoor->keyframe.skeleton, &cKF_ba_r_obj_romtrain_door, 1.0f,
                            51.0f, 1.0f, 0.0f, 0.0f, 0, NULL);
    traindoor->keyframe.morphCounter = 0.0f;
    cKF_SkeletonInfo_R_play(&traindoor->keyframe);
}

void aTRD_actor_dt(Actor* actor, UNUSED Game_Play* game_play) {
    TrainDoor* traindoor = (TrainDoor*)actor;

    cKF_SkeletonInfo_R_dt(&traindoor->keyframe);
}

void aTRD_set_door_SE(Actor* actor) {
    static s32 chk_pat[] = { 2, 27 };
    static u16 se_no[] = { 1042, 1043 };
    TrainDoor* traindoor = (TrainDoor*)actor;
    s32 i;

    for (i = 0; i < 2; i++) {
        if ((s32)traindoor->keyframe.frameControl.currentFrame == chk_pat[i]) {
            sAdo_OngenTrgStart(se_no[i], &traindoor->actor.world.pos);
            return;
        }
    }
}

void aTRD_actor_move(Actor* actor, UNUSED Game_Play* game_play) {
    TrainDoor* traindoor = (TrainDoor*)actor;
    SkeletonInfoR* keyframe = &traindoor->keyframe;

    if (traindoor->idle == 1) {
        traindoor->idle = 0;
        traindoor->keyframe.frameControl.speed = 1.0f;
    }

    if (cKF_SkeletonInfo_R_play(&traindoor->keyframe) == 1) {
        keyframe->frameControl.currentFrame = keyframe->frameControl.start;
        keyframe->frameControl.speed = 0.0f;
    }
    aTRD_set_door_SE(actor);
}

void aTRD_actor_draw(Actor* actor, Game_Play* game_play) {
    TrainDoor* traindoor = (TrainDoor*)actor;
    Gfx* mtx;
    Mtx* mtxp;

    mtx = GRAPH_ALLOC_NO_ALIGN(game_play->state.gfxCtx, traindoor->keyframe.skeleton->unk01 * sizeof(Mtx));

    mtxp = (Mtx*)mtx;
    if (mtxp != NULL) {
        _texture_z_light_fog_prim(game_play->state.gfxCtx);
        cKF_Si3_draw_R_SV(game_play, &traindoor->keyframe, mtxp, NULL, NULL, NULL);
    }
}
