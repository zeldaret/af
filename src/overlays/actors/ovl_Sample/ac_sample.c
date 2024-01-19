#include "ac_sample.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "m_rcp.h"
#include "69E2C0.h"
#include "m_msg_main.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Ac_Sample_Actor_ct(Actor* thisx, Game_Play* play);
void Ac_Sample_Actor_dt(Actor* thisx, Game_Play* play);
void Ac_Sample_Actor_main(Actor* thisx, Game_Play* play);
void Ac_Sample_Actor_draw(Actor* thisx, Game_Play* play);

// TODO: extract assets

extern BaseSkeletonR cKF_bs_r_hnw;
extern BaseAnimationR cKF_ba_r_hnw_move;

extern u8 hnw_tmem_txt[];
extern u16 hnw_face[];

ClObjPipe_Init Ac_Sample_OcInfoData_forStand = {
    { OC1_1 | OC1_TYPE_8 | OC1_TYPE_10 | OC1_TYPE_20, OC2_TYPE_20, COLSHAPE_PIPE },
    { ELEM_FLAG_1 },
    { { 0x1E, 0x3C, 0, { 0, 0, 0 } } },
};

void Ac_Sample_ct_forCorect(Actor* thisx, Game_Play* play) {

    Sample* this = (Sample*)thisx;

    ClObjPipe_ct(play, &this->stand);
    ClObjPipe_set5(play, &this->stand, thisx, &Ac_Sample_OcInfoData_forStand);
}

void Ac_Sample_Excute_Corect(Actor* thisx, Game_Play* play) {
    UNUSED s32 pad[3];
    Sample* this = (Sample*)thisx;
    ClObjPipe* stand = &this->stand;

    CollisionCheck_Uty_ActorWorldPosSetPipeC(thisx, stand);
    CollisionCheck_setOC(play, &play->unk_2138, &stand->base);
}

void Ac_Sample_Actor_dt(Actor* thisx, Game_Play* play) {
    Sample* this = (Sample*)thisx;
    SkeletonInfoR* info = &this->skeletonInfo;

    if (thisx->child != NULL) {
        Actor_delete(thisx->child);
    }

    cKF_SkeletonInfo_R_dt(info);
    ClObjPipe_dt(play, &this->stand);
}

void Ac_Sample_Animation_Base(Sample* this) {
    cKF_SkeletonInfo_R_play(&this->skeletonInfo);
}

char Ac_Sample_str_mail[64];

void Ac_Sample_Actor_wait_demo_ct(UNUSED Actor* thisx) {
    static char str0[] = {
        0xDC, 0xB8, 0x97, 0x8C, 0x9D, 0x20, 0x20, 0x20, 0x20, 0x20,
    };
    static char str9[] = {
        0xE4, 0xBA, 0x9D, 0xA3, 0x32,
    };

    mDemo_Set_msg_num(9);

    mMsg_Set_item_str(mMsg_Get_base_window_p(), 0, str0, 6);

    mMsg_Set_item_str(mMsg_Get_base_window_p(), 4, str9, sizeof(str9));
    mMsg_Set_free_str(mMsg_Get_base_window_p(), 0, str0, sizeof(str0));
    mMsg_Set_free_str(mMsg_Get_base_window_p(), 9, str9, sizeof(str9));
    mMsg_Set_mail_str(mMsg_Get_base_window_p(), 0, Ac_Sample_str_mail, sizeof(Ac_Sample_str_mail));
}

void func_80934104_jp(Actor* thisx, Game_Play* play) {
    Sample* this = (Sample*)thisx;
    void* segment = play->objectExchangeBank.status[thisx->unk_026].segment;
    SkeletonInfoR* info = &this->skeletonInfo;

    if (segment != this->segment) {
        info->skeleton = Lib_SegmentedToVirtual(&cKF_bs_r_hnw);
        info->animation = Lib_SegmentedToVirtual(&cKF_ba_r_hnw_move);
        this->segment = segment;
    }
}

void Ac_Sample_Actor_main_wait(Sample* this, Game_Play* play) {
    Ac_Sample_Animation_Base(this);
    Actor_world_to_eye(&this->actor, 48.0f);
    Ac_Sample_Excute_Corect(&this->actor, play);

    if (mDemo_Check(7, &this->actor) == 0) {
        mDemo_Request(7, &this->actor, &Ac_Sample_Actor_wait_demo_ct);
    } else {
        this->mainAction = 1;
    }
}

void Ac_Sample_Actor_main_talk(Sample* this, Game_Play* play) {
    s32 check;
    s16 angle;
    s16 temp;

    Ac_Sample_Animation_Base(this);
    Actor_world_to_eye(&this->actor, 48.0f);
    Ac_Sample_Excute_Corect(&this->actor, play);

    check = mDemo_Check(7, &this->actor);
    if (check != 0) {

        angle = add_calc_short_angle2(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0.5f, 5000, 100);
        temp = angle;
        this->actor.world.rot.y = this->actor.shape.rot.y;
        if (mDemo_Check_ListenAble() == FALSE && mDemo_Check_DiffAngle_forTalk(temp)) {
            mDemo_Set_ListenAble();
        }
    } else {
        this->mainAction = 0;
    }
}

void Ac_Sample_Actor_main(Actor* thisx, Game_Play* play) {
    static SampleActionFunc proc[] = { &Ac_Sample_Actor_main_wait, &Ac_Sample_Actor_main_talk };
    Sample* this = (Sample*)thisx;
    s32 action = this->mainAction;

    func_80934104_jp(thisx, play);
    if (action < 0 || action >= 2 || proc[action] == NULL) {
        return;
    }

    proc[action](this, play);
}

void Ac_Sample_Actor_ct(Actor* thisx, Game_Play* play) {
    SkeletonInfoR* info;
    UNUSED s32 pad[2];
    Sample* this = (Sample*)thisx;

    info = &this->skeletonInfo;
    cKF_SkeletonInfo_R_ct(info, &cKF_bs_r_hnw, &cKF_ba_r_hnw_move, this->jointTable, this->morphTable);
    cKF_SkeletonInfo_R_init_standard_stop(info, &cKF_ba_r_hnw_move, NULL);
    Ac_Sample_ct_forCorect(thisx, play);

    this->drawAction = 1;
    this->segment = play->objectExchangeBank.status[thisx->unk_026].segment;
}

#define AC_GCN_OPEN_DISP(gfxCtx)            \
    {                                       \
        GraphicsContext* __gfxCtx = gfxCtx; \
        int __gfx_opened = 0;               \
        do {                                \
        } while (0)

#define AC_GCN_CLOSE_DISP(gfxCtx) \
    (void)__gfx_opened;           \
    }                             \
    do {                          \
    } while (0)

#define OPEN_CUSTOM_POLY_OPA()                \
    {                                         \
        Gfx* __polyOpa = __gfxCtx->polyOpa.p; \
        int __opa_opened = 0;                 \
        do {                                  \
        } while (0)

#define CLOSE_CUSTOM_POLY_OPA()      \
    __gfxCtx->polyOpa.p = __polyOpa; \
    (void)__opa_opened;              \
    }                                \
    do {                             \
    } while (0)

void Ac_Sample_Actor_draw_normal(Sample* this, Game_Play* play) {
    UNUSED s32 pad;
    SkeletonInfoR* info = &this->skeletonInfo;
    Mtx* mtx = GRAPH_ALLOC_NO_ALIGN(play->state.gfxCtx, sizeof(Mtx) * info->skeleton->unk01);

    if (mtx != NULL) {

        _texture_z_light_fog_prim(play->state.gfxCtx);

        AC_GCN_OPEN_DISP(play->state.gfxCtx);
        OPEN_CUSTOM_POLY_OPA();
        gDPLoadTextureBlockS(__polyOpa++, hnw_tmem_txt, G_IM_FMT_I, G_IM_SIZ_8b, 64, 64, 0, G_TX_MIRROR | G_TX_WRAP,
                             G_TX_MIRROR | G_TX_WRAP, 7, 7, G_TX_NOLOD, G_TX_NOLOD);

        gDPLoadTLUT_pal16(__polyOpa++, 15, hnw_face);
        gDPSetTextureLUT(__polyOpa++, G_TT_RGBA16);

        CLOSE_CUSTOM_POLY_OPA();

        AC_GCN_CLOSE_DISP(play->state.gfxCtx);

        cKF_Si3_draw_R_SV(play, info, mtx, NULL, NULL, NULL);
    }
}

void Ac_Sample_Actor_draw(Actor* thisx, Game_Play* play) {
    static SampleActionFunc proc[] = { (SampleActionFunc)none_proc2, Ac_Sample_Actor_draw_normal };
    Sample* this = (Sample*)thisx;

    s32 action = this->drawAction;

    func_80934104_jp(&this->actor, play);
    if (action < 0 || action >= 2 || proc[action] == NULL) {
        return;
    }

    proc[action](this, play);
}

ActorProfile Sample_Profile = {
    /* */ ACTOR_SAMPLE,
    /* */ ACTOR_PART_4,
    /* */ 0,
    /* */ 0x9000,
    /* */ OBJECT_12,
    /* */ sizeof(Sample),
    /* */ Ac_Sample_Actor_ct,
    /* */ Ac_Sample_Actor_dt,
    /* */ Ac_Sample_Actor_main,
    /* */ Ac_Sample_Actor_draw,
    /* */ NULL,
};
