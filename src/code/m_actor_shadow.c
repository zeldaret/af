#include "m_actor_shadow.h"
#include "m_rcp.h"
#include "m_collision_obj.h"
#include "macros.h"
#include "sys_math3d.h"
#include "m_field_info.h"

extern Gfx ef_shadow_out_modelT[];
extern Gfx ef_shadow_in_modelT[];

s32 mActorShadow_OperateScrollLimit(s32 value, s32 step, s32 limit) {
    if (step != 0) {
        if (step > 0) {
            value += step;
            if (value > limit) {
                value = limit;
            }
        } else if (step < 0) {
            value += step;
            if (value < limit) {
                value = limit;
            }
        }
    }
    return value;
}

Gfx* mActorShadow_TileScroll2(u32* x1, u32* y1, s32 step1, s32 step2, s32 limit1, s32 limit2, s32 width1, s32 height1,
                              u32* x2, u32* y2, s32 step3, s32 step4, s32 limit3, s32 limit4, s32 width2, s32 height2,
                              Game* game) {
    *x1 = mActorShadow_OperateScrollLimit(*x1, step1, limit1);
    *y1 = mActorShadow_OperateScrollLimit(*y1, step2, limit2);
    *x2 = mActorShadow_OperateScrollLimit(*x2, step3, limit3);
    *y2 = mActorShadow_OperateScrollLimit(*y2, step4, limit4);

    return two_tex_scroll(game->gfxCtx, 0, *x1, *y1, width1, height1, 1, *x2, *y2, width2, height2);
}

void mActorShadow_AdjustRate(f32* rate) {
    if (*rate < 0.0f) {
        *rate = 0.0f;
    } else if (*rate > 1.0f) {
        *rate = 1.0f;
    }
}

void mActorShadow_GetTimeAngleY_TimeAlpha(ShadowInfo* shadow, Game_Play* play) {
    f32 timef;
    s32 timesec = common_data.time.nowSec;
    f32 angle;
    shadow->unk1C = play->kankyo.shadowAlpha;

    // Between 4 a.m and 8 p.m
    if ((timesec >= 14400) && (timesec < 72000)) {
        UNUSED f32 scopedTemp;
        timef = (timesec - 14400) / 57600.0f;
        angle = 16384;
    } // Between 12 a.m and 4 a.m
    else if (timesec < 14400) {
        UNUSED f32 scopedTemp;
        timef = 0.5f + timesec / 28800.0f;
        angle = 16384;
    } // Between 8 p.m and 12 a.m
    else {
        timef = (timesec - 72000) / 28800.0f;
        angle = 16384;
    }

    shadow->unk26 = 0x8000 - ((s16)(angle * timef) + 0x6000);
}

void mActorShadow_GetGroundAverageAngle(ShadowInfo* shadow) {
    static xyz_t angle_range_table[4] = {
        { 10.0f, 0.0f, 10.0f },
        { 10.0f, 0.0f, -10.0f },
        { -10.0f, 0.0f, 10.0f },
        { -10.0f, 0.0f, -10.0f },
    };

    s32 x = 0;
    s32 y = 0;
    s32 z = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        xyz_t pos = shadow->position;
        s_xyz sangle = { 0, 0, 0 };

        pos.x += angle_range_table[i].x;
        pos.y += angle_range_table[i].y;
        pos.z += angle_range_table[i].z;

        mCoBG_GetBgY_AngleS_FromWpos(&sangle, pos, 0.0f);

        x += sangle.x;
        y += sangle.y;
        z += sangle.z;
    }

    shadow->unk20 = x >> 2;
    shadow->unk22 = y >> 2;
    shadow->unk24 = z >> 2;
}

void mActorShadow_GetDistanceRate(ShadowInfo* shadow, f32 rate) {
    f32 xcalc;
    f32 disty;
    f32 calcRate;

    disty = shadow->groundY <= shadow->position.y ? shadow->position.y - shadow->groundY
                                                  : -(shadow->position.y - shadow->groundY);
    xcalc = 100.0f + rate;

    if (xcalc < disty) {
        shadow->unk14 = 0.6f;
        shadow->unk18 = 0;
        return;
    }

    calcRate = (xcalc - disty) / xcalc;
    shadow->unk14 = (((0.04f * 10.0f) * calcRate) + 0.6f);
    shadow->unk18 = 1 * calcRate;
}

f32 mActorShadow_GetAbsBigger(f32 a, f32 b) {
    f32 absA;
    f32 absB;
    absA = ABS(a);
    absB = ABS(b);

    if (absA > absB) {
        return absA;
    }
    return absB;
}

void mActorShadow_RadiusScaleRate(Actor* actor, ShadowInfo* shadow) {
    f32 abs = mActorShadow_GetAbsBigger(actor->shape.shadowSizeX, actor->shape.shadowSizeZ);
    shadow->unk10 = (abs / 19.0f) * 0.018f;
}

void mActorShadow_GetShadowTopPos_GetSlideS(ShadowInfo* shadow) {
    xyz_t wpos;
    xyz_t base;
    f32 bgY;

    if (shadow->kind == 0) {
        base.x = 0.0f;
        base.y = 0.0f;
        base.z = -40.0f;
        sMath_RotateY(&base, BINANG_TO_RAD(shadow->unk26));
        wpos.x = shadow->position.x + base.x;
        wpos.y = shadow->position.y + base.y;
        wpos.z = shadow->position.z + base.z;
        bgY = mCoBG_GetShadowBgY_AngleS_FromWpos(NULL, wpos, 0.0f);
        if ((shadow->position.y - bgY) > 20.0f) {
            shadow->unk34 = 28;
            return;
        }
    }
    shadow->unk34 = 0;
}

Gfx* mActorShadow_SetTexScroll(Actor* actor, ShadowInfo* shadow, Game* game) {
    s32 tempShapex2;
    u32 y1 = 0;
    u32 x1 = 0;
    u32 y2 = 0;
    s32 step;

    tempShapex2 = actor->shape.unk_20;
    if (tempShapex2 < shadow->unk34) {
        step = 13;
    } else if (tempShapex2 > shadow->unk34) {
        step = -13;
    } else {
        step = 0;
    }

    mActorShadow_TileScroll2(&x1, &y1, 0, 0, 0, 0, 32, 16, &actor->shape.unk_20, &y2, step, 0, shadow->unk34, 0, 32, 16,
                             game);
}

void mActorShadow_GetLastAlphaScale(f32* scale, u8* alpha, Actor* actor, ShadowInfo* shadow) {
    f32 alphaCalc = shadow->unk1C * shadow->unk18 * actor->shape.shadowAlphaRate * 0.75f;

    *scale = shadow->unk10 * shadow->unk14 * actor->shape.shadowSizeRate;

    if (shadow->kind == 1) {
        alphaCalc *= 0.7f;
    }
    *alpha = alphaCalc;
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

void mActorShadow_DrawActorShadow(Actor* actor, ShadowInfo* shadow, Game* game, f32 rad, s32 id, xyz_t ofs) {
    Game_Play* play = (Game_Play*)game;
    u8 alpha;
    f32 scale;
    u8 r;
    u8 g;
    u8 b;
    f32 yAdjust;
    s32 scene = common_data.sceneNo;

    mActorShadow_GetLastAlphaScale(&scale, &alpha, actor, shadow);

    AC_GCN_OPEN_DISP(play->state.gfxCtx);

    _texture_z_light_fog_prim_shadow(play->state.gfxCtx);

    yAdjust = (scene == 19 || scene == 27 || scene == 28 || scene == 34) ? 0.5f
                                                                         : ((scene == 15 || scene == 16) ? 0.6f : 2.0f);

    switch (actor->shape.forceShadow) {
        f32 x;
        f32 y;
        f32 z;
        case 1:
            x = actor->shape.shadowPosition->x + ofs.x;
            y = actor->shape.shadowPosition->y + yAdjust + ofs.y;
            z = actor->shape.shadowPosition->z + ofs.z;
            Matrix_translate(x, y, z, 0);
            break;
        default:
            x = shadow->position.x + ofs.x;
            y = shadow->groundY + yAdjust + ofs.y;
            z = shadow->position.z + ofs.z;
            Matrix_translate(x, y, z, 0);
            break;
    }

    switch (actor->shape.forceShadow) {
        case 1:
            Matrix_RotateZ(0, 1);
            Matrix_RotateX(0, 1);
            break;
        default:
            Matrix_RotateZ(shadow->unk24, 1);
            Matrix_RotateX(shadow->unk20, 1);
            break;
    }

    if ((shadow->kind == 0) && (id == 0)) {
        Matrix_RotateY(shadow->unk26, 1);
    }

    switch (id) {
        case 1:
            Matrix_scale(shadow->unk10, shadow->unk10, rad, 1);
            break;
        default:
            switch (actor->shape.forceShadow) {
                case 1:
                    Matrix_scale(shadow->unk10, shadow->unk10, shadow->unk10, 1);
                    break;
                default:
                    Matrix_scale(scale, scale, scale, 1);
                    break;
            }
            break;
    }

    gSPMatrix(SHADOW_DISP++, _Matrix_to_Mtx_new(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    mEnv_GetShadowPrimColor_Light(&r, &g, &b, &play->state);
    gDPSetPrimColor(SHADOW_DISP++, 0, 0xFF, r, g, b, (u8)alpha);

    if ((shadow->kind == 0) && (id == 0)) {
        Gfx* texscroll = mActorShadow_SetTexScroll(actor, shadow, &play->state);
        if (texscroll != NULL) {
            gSPSegment(SHADOW_DISP++, 0x08, texscroll);
            gSPDisplayList(SHADOW_DISP++, ef_shadow_out_modelT);
        }
    } else {
        gSPDisplayList(SHADOW_DISP++, ef_shadow_in_modelT);
    }

    AC_GCN_CLOSE_DISP(play->state.gfxCtx);
}

void mActorShadow_GetShadowPosition(Actor* actor, xyz_t* position) {
    if (actor->shape.shadowPosition != NULL) {
        *position = *actor->shape.shadowPosition;
    } else {
        *position = actor->world.pos;
    }
}

s32 mActorShadow_GetShadowKind(void) {
    if (!(FI_GET_TYPE(mFI_GetFieldId()))) {
        return 0;
    } else {
        return 1;
    }
}

f32 mAc_GetShadowGroundY_NoneForce(ShadowInfo* shadow) {
    f32 res = mCoBG_GetShadowBgY_AngleS_FromWpos(NULL, shadow->position, 0.0f);
    return res;
}

f32 mAc_GetShadowGroundY_Force(ShadowInfo* shadow) {
    return mCoBG_GetBgY_OnlyCenter_FromWpos2(shadow->position, 0.0f);
}

void mAc_DecideShadowRadius_IamNotFish(ShadowInfo* shadow, Actor* actor, f32* radius) {
    mActorShadow_RadiusScaleRate(actor, shadow);
    *radius = 0.01f;
}

void mAc_DecideShadowRadius_IamFish(ShadowInfo* shadow, Actor* actor, f32* radius) {
    shadow->unk10 = (actor->shape.shadowSizeX / 19.0f) * 0.018f;
    *radius = (actor->shape.shadowSizeZ / 19.0f) * 0.018f;
}

void mAc_ActorShadowDraw_ShadowDrawFlagOff(UNUSED Actor* actor, UNUSED Game_Play* play, UNUSED s32 arg2,
                                           UNUSED xyz_t arg3, UNUSED f32 arg6) {
}

typedef f32 (*GetGroundYProc)(ShadowInfo*);
typedef void (*RadiusProc)(ShadowInfo*, Actor*, f32*);
typedef void (*ShadowProc)(Actor* actor, Game_Play* play, s32 arg2, xyz_t arg3, f32 arg6);

void mAc_ActorShadowDraw_ShadowDrawFlagOn(Actor* actor, Game_Play* play, s32 proc, xyz_t pos, f32 rate) {
    static RadiusProc set_raius_proc[] = {
        mAc_DecideShadowRadius_IamNotFish,
        mAc_DecideShadowRadius_IamFish,
    };

    static GetGroundYProc get_ground_y_proc[] = {
        mAc_GetShadowGroundY_NoneForce,
        mAc_GetShadowGroundY_Force,
    };

    ShadowInfo shadow;
    UNUSED s32 pad;
    f32 rad = 0.01f;

    bzero(&shadow, sizeof(ShadowInfo));

    shadow.kind = mActorShadow_GetShadowKind();
    mActorShadow_GetShadowPosition(actor, &shadow.position);
    mActorShadow_AdjustRate(&actor->shape.shadowSizeRate);
    mActorShadow_AdjustRate(&actor->shape.shadowAlphaRate);

    shadow.groundY = get_ground_y_proc[actor->shape.forceShadow & 1](&shadow);

    mActorShadow_GetTimeAngleY_TimeAlpha(&shadow, play);
    mActorShadow_GetGroundAverageAngle(&shadow);
    mActorShadow_GetDistanceRate(&shadow, rate);
    set_raius_proc[proc & 1](&shadow, actor, &rad);
    mActorShadow_GetShadowTopPos_GetSlideS(&shadow);
    mActorShadow_DrawActorShadow(actor, &shadow, &play->state, rad, proc, pos);
    actor->shape.forceShadow = FALSE;
}

void mAc_ActorShadowDraw(Actor* actor, Game_Play* play, s32 arg2, xyz_t arg3, f32 arg6) {
    static ShadowProc shadwo_draw_proc[] = {
        mAc_ActorShadowDraw_ShadowDrawFlagOff,
        mAc_ActorShadowDraw_ShadowDrawFlagOn,
    };

    if (actor->name == 0x4A) {
        mActorShadow_UnSetForceShadowPos(actor);
        actor->shape.shadowPosition = &actor->world.pos;
    }

    shadwo_draw_proc[actor->shape.drawShadow & 1](actor, play, arg2, arg3, arg6);
    actor->shape.shadowPosition = &actor->world.pos;
}

xyz_t mActorShadow_offset0 = {
    0.0f,
    0.0f,
    0.0f,
};

void mActorShadow_SetForceShadowPos(Actor* actor, xyz_t* pos) {
    actor->shape.forceShadow = TRUE;
    actor->shape.shadowPosition = pos;
}

void mActorShadow_UnSetForceShadowPos(Actor* actor) {
    actor->shape.forceShadow = FALSE;
    actor->shape.shadowPosition = &actor->world.pos;
}

void mAc_NormalActorShadow(Actor* actor, Game_Play* play, f32 rad) {
    mAc_ActorShadowDraw(actor, play, 0, mActorShadow_offset0, rad);
}

void mAc_UnagiActorShadow(Actor* actor, Game_Play* play, xyz_t pos) {
    mAc_ActorShadowDraw(actor, play, 1, pos, 1.0f);
}

void mAc_ActorShadowCircle(Actor* actor, UNUSED LightsN* lights, Game_Play* play) {
    mAc_ActorShadowDraw(actor, play, 0, mActorShadow_offset0, 1.0f);
}

void mAc_ActorShadowEllipse(Actor* actor, UNUSED LightsN* lights, Game_Play* play) {
    mAc_ActorShadowDraw(actor, play, 0, mActorShadow_offset0, 1.0f);
}
