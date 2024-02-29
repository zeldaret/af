#include "ac_t_keitai.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "m_rcp.h"
#include "objects/tol_keitai_1/tol_keitai_1.h"
#include "overlays/gamestates/ovl_play/m_play.h"

#define THIS ((T_Keitai*)thisx)

void aTKT_actor_ct(Actor* thisx, Game_Play* game_play);
void aTKT_actor_move(Actor* thisx, Game_Play* game_play);
void aTKT_actor_draw(Actor* thisx, Game_Play* game_play);

void aTKT_setupAction(T_Keitai* this, s32 processIndex);

typedef struct TKeitaiAnimationData {
    /* 0x0 */ BaseAnimationR* animation;
    /* 0x4 */ f32 startFrame;
    /* 0x8 */ f32 endFrame;
} TKeitaiAnimationData; // size = 0xC

TKeitaiAnimationData aTKT_anm_dt[] = {
    { &cKF_ba_r_tol_keitai_1_keitai_on1, 1.0f, 68.0f },
    { &cKF_ba_r_tol_keitai_1_keitai_off1, 1.0f, 61.0f },
    { &cKF_ba_r_tol_keitai_1_keitai_off1, 1.0f, 61.0f },
    { &cKF_ba_r_tol_keitai_1_keitai_on1, 1.0f, 68.0f },
    { NULL, 0.0f, 0.0f },
};

ActorProfile T_Keitai_Profile = {
    /* */ ACTOR_T_KEITAI,
    /* */ ACTOR_PART_4,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ OBJECT_TOL_KEITAI_1,
    /* */ sizeof(T_Keitai),
    /* */ aTKT_actor_ct,
    /* */ (void*)none_proc1,
    /* */ aTKT_actor_move,
    /* */ aTKT_actor_draw,
    /* */ NULL,
};

void aTKT_actor_ct(Actor* thisx, Game_Play* game_play) {
    T_Keitai* this = THIS;

    cKF_SkeletonInfo_R_ct(&this->skeletonInfo, &cKF_bs_r_tol_keitai_1, NULL, this->jointTable, this->morphTable);
    this->segment = game_play->objectExchangeBank.status[this->toolActor.actor.unk_026].segment;
    aTKT_setupAction(this, 0);
}

void func_80A1F58C_jp(T_Keitai* this, Game_Play* game_play) {
    UNUSED s32 pad;
    void* segment = game_play->objectExchangeBank.status[this->toolActor.actor.unk_026].segment;
    SkeletonInfoR* skeletonInfo;
    TKeitaiAnimationData* animData;

    if (this->segment != segment) {
        animData = &aTKT_anm_dt[this->processIndex];
        skeletonInfo = &this->skeletonInfo;
        skeletonInfo->skeleton = Lib_SegmentedToVirtual(&cKF_bs_r_tol_keitai_1);
        skeletonInfo->animation = Lib_SegmentedToVirtual(animData->animation);
        this->segment = segment;
    }
}

void aTKT_calc_scale(T_Keitai* this, s32 index) {
    static f32 start_scale[] = { 0.0f, 1.0f };
    static f32 end_scale[] = { 1.0f, 0.0f };
    static f32 start_chno[] = { 10.0f, 33.0f };
    static f32 end_chno[] = { 20.0f, 41.0f };
    f32 currentFrame = this->skeletonInfo.frameControl.currentFrame;
    f32 startingChno = start_chno[index];
    f32 endingChno = end_chno[index];
    f32 startingScale = start_scale[index];
    f32 endingScale = end_scale[index];
    f32 scale;

    if (currentFrame < startingChno) {
        scale = startingScale;
    } else if (endingChno < currentFrame) {
        scale = endingScale;
    } else {
        scale = (((currentFrame - startingChno) / (endingChno - startingChno)) * (endingScale - startingScale)) +
                startingScale;
    }

    this->toolActor.actor.scale.x = scale;
    this->toolActor.actor.scale.y = scale;
    this->toolActor.actor.scale.z = scale;
}

void aTKT_takeout(T_Keitai* this) {
    aTKT_calc_scale(this, 0);
}

void aTKT_putaway(T_Keitai* this) {
    aTKT_calc_scale(this, 1);
}

void aTKT_destruct(T_Keitai* this) {
    Actor_delete(&this->toolActor.actor);
}

void aTKT_setupAction(T_Keitai* this, s32 processIndex) {
    static T_KeitaiActionFunc process[] = {
        aTKT_takeout, aTKT_putaway, aTKT_destruct, (T_KeitaiActionFunc)(void*)none_proc1, NULL,
    };
    this->process = process[processIndex];
    this->processIndex = processIndex;

    {
        TKeitaiAnimationData* animData = &aTKT_anm_dt[processIndex];

        cKF_SkeletonInfo_R_init(&this->skeletonInfo, this->skeletonInfo.skeleton, animData->animation,
                                animData->startFrame, animData->endFrame, animData->startFrame, 1.0f, 0.0f,
                                ANIMATION_STOP, NULL);
    }
}

void aTKT_actor_move(Actor* thisx, Game_Play* game_play) {
    T_Keitai* this = THIS;

    func_80A1F58C_jp(this, game_play);

    if (this->toolActor.unk1BC != this->processIndex) {
        aTKT_setupAction(this, this->toolActor.unk1BC);
    }

    cKF_SkeletonInfo_R_play(&this->skeletonInfo);
    this->process(this);
}

#define OPEN_POLY_OPA_DISPS()                 \
    {                                         \
        Gfx* __polyOpa = __gfxCtx->polyOpa.p; \
        int __opa_opened = 0;                 \
        do {                                  \
        } while (0)

#define CLOSE_POLY_OPA_DISPS()       \
    __gfxCtx->polyOpa.p = __polyOpa; \
    (void)__opa_opened;              \
    }                                \
    do {                             \
    } while (0)

void aTKT_actor_draw(Actor* thisx, Game_Play* game_play) {
    static xyz_t D_80A1F9F4_jp = { 0.0f, 0.0f, 0.0f };
    T_Keitai* this = THIS;
    SkeletonInfoR* skeletonInfo = &this->skeletonInfo;
    GraphicsContext* gfxCtx = game_play->state.gfxCtx;
    Mtx* mtx;

    func_80A1F58C_jp(this, game_play);

    mtx = GRAPH_ALLOC_NO_ALIGN(gfxCtx, sizeof(Mtx) * skeletonInfo->skeleton->unk01);

    if (mtx != NULL) {
        if (this->toolActor.unk1B8 == 1) {
            Matrix_put(&this->toolActor.unk178);
            Matrix_Position(&D_80A1F9F4_jp, &this->toolActor.actor.world.pos);
            this->toolActor.unk1B8 = 0;
        } else {
            Matrix_translate(this->toolActor.actor.world.pos.x, this->toolActor.actor.world.pos.y,
                             this->toolActor.actor.world.pos.z, MTXMODE_NEW);
            Matrix_scale(0.01f, 0.01f, 0.01f, MTXMODE_APPLY);
        }

        _texture_z_light_fog_prim_npc(gfxCtx);

        OPEN_DISPS(gfxCtx);
        OPEN_POLY_OPA_DISPS();

        Matrix_scale(this->toolActor.actor.scale.x, this->toolActor.actor.scale.y, this->toolActor.actor.scale.z,
                     MTXMODE_APPLY);
        gSPMatrix(__polyOpa++, _Matrix_to_Mtx_new(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        CLOSE_POLY_OPA_DISPS();
        CLOSE_DISPS(gfxCtx);

        cKF_Si3_draw_R_SV(game_play, skeletonInfo, mtx, NULL, NULL, NULL);
    }
}
