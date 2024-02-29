#include "ac_train_door.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "m_rcp.h"
#include "audio.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTRD_actor_ct(Actor* thisx, Game_Play* game_play);
void aTRD_actor_dt(Actor* thisx, Game_Play* game_play);
void aTRD_actor_move(Actor* thisx, Game_Play* game_play);
void aTRD_actor_draw(Actor* thisx, Game_Play* game_play);

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

void aTRD_actor_ct(Actor* thisx, UNUSED Game_Play* game_play) {
    TrainDoor* this = (TrainDoor*)thisx;

    cKF_SkeletonInfo_R_ct(&this->skeletonInfo, &cKF_bs_r_obj_romtrain_door, NULL, this->work, this->target);
    cKF_SkeletonInfo_R_init(&this->skeletonInfo, this->skeletonInfo.skeleton, &cKF_ba_r_obj_romtrain_door, 1.0f, 51.0f,
                            1.0f, 0.0f, 0.0f, 0, NULL);
    this->skeletonInfo.morphCounter = 0.0f;
    cKF_SkeletonInfo_R_play(&this->skeletonInfo);
}

void aTRD_actor_dt(Actor* thisx, UNUSED Game_Play* game_play) {
    TrainDoor* this = (TrainDoor*)thisx;

    cKF_SkeletonInfo_R_dt(&this->skeletonInfo);
}

void aTRD_set_door_SE(Actor* thisx) {
    static s32 chk_pat[] = { 2, 27 };
    static u16 se_no[] = { 1042, 1043 };
    TrainDoor* this = (TrainDoor*)thisx;
    s32 i;

    for (i = 0; i < 2; i++) {
        if ((s32)this->skeletonInfo.frameControl.currentFrame == chk_pat[i]) {
            sAdo_OngenTrgStart(se_no[i], &this->actor.world.pos);
            return;
        }
    }
}

void aTRD_actor_move(Actor* thisx, UNUSED Game_Play* game_play) {
    TrainDoor* this = (TrainDoor*)thisx;
    SkeletonInfoR* skeletonInfo = &this->skeletonInfo;

    if (this->idle == 1) {
        this->idle = 0;
        this->skeletonInfo.frameControl.speed = 1.0f;
    }

    if (cKF_SkeletonInfo_R_play(&this->skeletonInfo) == 1) {
        skeletonInfo->frameControl.currentFrame = skeletonInfo->frameControl.start;
        skeletonInfo->frameControl.speed = 0.0f;
    }
    aTRD_set_door_SE(thisx);
}

void aTRD_actor_draw(Actor* thisx, Game_Play* game_play) {
    TrainDoor* this = (TrainDoor*)thisx;
    Gfx* mtx;
    Mtx* mtxp;

    mtx = GRAPH_ALLOC_NO_ALIGN(game_play->state.gfxCtx, this->skeletonInfo.skeleton->unk01 * sizeof(Mtx));

    mtxp = (Mtx*)mtx;
    if (mtxp != NULL) {
        _texture_z_light_fog_prim(game_play->state.gfxCtx);
        cKF_Si3_draw_R_SV(game_play, &this->skeletonInfo, mtxp, NULL, NULL, NULL);
    }
}
