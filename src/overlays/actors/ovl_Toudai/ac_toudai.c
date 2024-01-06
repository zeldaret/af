#include "ac_toudai.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "c_keyframe.h"
#include "m_field_info.h"
#include "m_collision_bg.h"
#include "m_rcp.h"
#include "m_lib.h"
#include "macros.h"
#include "code_variables.h"

#define THIS ((Toudai*)thisx)

void aTOU_actor_ct(Actor* thisx, Game_Play* game_play);
void aTOU_actor_dt(Actor* thisx, Game_Play* game_play);
void aTOU_actor_init(Actor* thisx, Game_Play* game_play);
void aTOU_actor_draw(Actor* thisx, Game_Play* game_play);
void aTOU_set_bgOffset(Toudai* this, s32 heightTableIndex);
void aTOU_init(Toudai* this, struct Game_Play* game_play);
void aTOU_wait(Toudai* this, struct Game_Play* game_play);
void aTOU_lighting(Toudai* this, struct Game_Play* game_play);
void aTOU_lightout(Toudai* this, struct Game_Play* game_play);
void aTOU_setup_action(Toudai* this, s32 processIndex);

ActorProfile Toudai_Profile = {
    /* */ ACTOR_TOUDAI,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x5843,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Toudai),
    /* */ aTOU_actor_ct,
    /* */ aTOU_actor_dt,
    /* */ aTOU_actor_init,
    /* */ aTOU_actor_draw,
    /* */ NULL,
};

u8 aTOU_shadow_vtx_fix_flg_table[] = { 0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x01, 0x00,
                                       0x00, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x00 };

extern Vtx obj_s_toudai_shadow_v[];
extern Gfx obj_s_toudai_shadow_1_model[];
ShadowData aTOU_shadow_data = { 20, aTOU_shadow_vtx_fix_flg_table, 60.0f, obj_s_toudai_shadow_v,
                                obj_s_toudai_shadow_1_model };

extern BaseSkeletonR cKF_bs_r_obj_s_toudai;
extern BaseSkeletonR cKF_bs_r_obj_w_toudai;
BaseSkeletonR* skl_324[] = { &cKF_bs_r_obj_s_toudai, &cKF_bs_r_obj_w_toudai };

void aTOU_actor_ct(Actor* thisx, Game_Play* game_play UNUSED) {
    Toudai* this = THIS;
    s32 type = (common_data.time.season == WINTER);

    gSegments[6] = OS_K0_TO_PHYSICAL(common_data.unk_10098->unk_AC(45));
    cKF_SkeletonInfo_R_ct(&this->skeletonInfo, skl_324[type], NULL, this->jointTable, this->morphTable);
    aTOU_set_bgOffset(this, 1);
    aTOU_setup_action(this, 0);
    cKF_SkeletonInfo_R_play(&this->skeletonInfo);
    this->actor.world.pos.x -= 20.0f;
    this->actor.world.pos.z -= 20.0f;
}

void aTOU_actor_dt(Actor* thisx, Game_Play* game_play UNUSED) {
    Toudai* this = THIS;

    common_data.unk_10098->unk_A8(&common_data.unk_10098->unk_B0, 8, 45, thisx);
    common_data.unk_10098->unk_A8(&common_data.unk_10098->unk_454, 9, 90, thisx);
    common_data.unk_10098->unk_A8(&common_data.unk_10098->unk_86C, 8, 45, thisx);
    cKF_SkeletonInfo_R_dt(&this->skeletonInfo);
    thisx->world.pos.x += 20.0f;
    thisx->world.pos.z += 20.0f;
}

mCoBG_unkStruct2 height_table_ct_360[] = { { 0x64, 16, 16, 16, 16, 16, 0 },
                                           { 0x64, 16, 16, 16, 16, 16, 0 },
                                           { 0x64, 16, 16, 16, 16, 16, 0 },
                                           { 0x64, 16, 16, 16, 16, 16, 0 } };
mCoBG_unkStruct2* height_table_361[] = { height_table_ct_360, height_table_ct_360 };
f32 addX_362[] = { -40.0f, 0.0f };
f32 addZ_363[] = { -40.0f, 0.0f };

void aTOU_set_bgOffset(Toudai* this, s32 heightTableIndex) {
    s32 i;
    xyz_t pos;
    mCoBG_unkStruct2* offsetTable = height_table_361[heightTableIndex];

    for (i = 0; i < 2; i++) {
        pos.z = addZ_363[i] + this->actor.home.pos.z;
        pos.x = addX_362[0] + this->actor.home.pos.x;
        mCoBG_SetPluss5PointOffset_file(pos, *offsetTable, "../ac_toudai_move.c_inc", 76);
        offsetTable++;
        pos.x = addX_362[1] + this->actor.home.pos.x;
        mCoBG_SetPluss5PointOffset_file(pos, *offsetTable, "../ac_toudai_move.c_inc", 80);
        offsetTable++;
    }
}

void aTOU_color_ctrl(Toudai* this) {
    f32 var_fv0;
    s32 frameTemp;

    if (this->unk2BC == 0) {
        add_calc(&this->unk2C8, 0.0f, 0.3f, 100.0f, 1.0f);
        add_calc(&this->unk2CC, 0.0f, 0.3f, 100.0f, 1.0f);
        add_calc(&this->unk2D0, 0.0f, 0.1f, 100.0f, 1.0f);
        return;
    }

    frameTemp = this->unk1E8 - 51;
    var_fv0 = (frameTemp < 0) ? 1.0f : -1.0f;
    frameTemp = ABS(frameTemp);

    if (frameTemp == 0) {
        this->unk2C8 = 220.0f;
        this->unk2CC = 240.0f;

    } else if (frameTemp >= 40) {
        add_calc(&this->unk2C8, 0.0f, 0.3f, 100.0f, 1.0f);
        add_calc(&this->unk2CC, 0.0f, 0.3f, 100.0f, 1.0f);

    } else if (frameTemp < 10) {
        this->unk2C8 = this->unk2C8 + (9.0f * var_fv0);
        this->unk2CC = this->unk2CC + (14.0f * var_fv0);

    } else if (frameTemp < 30) {
        this->unk2C8 = this->unk2C8 + (2.5f * var_fv0);
        this->unk2CC = this->unk2CC + (4.5f * var_fv0);

    } else {
        this->unk2C8 = this->unk2C8 + (8.0f * var_fv0);
        this->unk2CC = this->unk2CC + var_fv0;
    }

    add_calc(&this->unk2D0, 255.0f, 0.1f, 100.0f, 1.0f);
}

void aTOU_init(Toudai* this, Game_Play* game_play UNUSED) {
    aTOU_setup_action(this, 1);
}

void aTOU_wait(Toudai* this, Game_Play* game_play UNUSED) {
    if ((common_data.time.nowSec >= 0xFD20) || (common_data.time.nowSec < 0x4650)) {
        this->unk2BC = 1;
        this->skeletonInfo.frameControl.speed = 1.0f;
        aTOU_setup_action(this, 2);
    }
}

void aTOU_lighting(Toudai* this, Game_Play* game_play UNUSED) {
    if ((common_data.time.nowSec < 64800) && (common_data.time.nowSec >= 18000)) {
        aTOU_setup_action(this, 3);
    }
}

void aTOU_lightout(Toudai* this, Game_Play* game_play UNUSED) {
    if (this->unk1E8 == 0x33) {
        this->unk2BC = 0;
        this->skeletonInfo.frameControl.speed = 0.0f;
        aTOU_setup_action(this, 1);
    }
}

extern BaseAnimationR cKF_ba_r_obj_s_toudai;
extern BaseAnimationR cKF_ba_r_obj_w_toudai;
BaseAnimationR* ani_484[] = { &cKF_ba_r_obj_s_toudai, &cKF_ba_r_obj_w_toudai };
ToudaiActionFunc process_485[] = { aTOU_init, aTOU_wait, aTOU_lighting, aTOU_lightout };

void aTOU_setup_action(Toudai* this, s32 processIndex) {
    s32 type;

    if (processIndex == 0) {
        type = (common_data.time.season == WINTER);
        cKF_SkeletonInfo_R_init(&this->skeletonInfo, this->skeletonInfo.skeleton, ani_484[type], 1.0f, 100.0f, 51.0f,
                                0.0f, 0.0f, ANIMATION_REPEAT, NULL);
    }

    this->unk2A0 = process_485[processIndex];
    this->unk2B4 = processIndex;
}

void aTOU_actor_move(Actor* thisx, Game_Play* game_play) {
    Toudai* this = THIS;

    gSegments[6] = OS_K0_TO_PHYSICAL(common_data.unk_10098->unk_AC(45));
    this->unk174 = cKF_SkeletonInfo_R_play(&this->skeletonInfo);
    this->unk1E8 = this->skeletonInfo.frameControl.currentFrame;
    this->unk2A0(this, game_play);
    aTOU_color_ctrl(this);
}

void aTOU_actor_init(Actor* thisx, Game_Play* game_play) {
    Toudai* this = THIS;

    mFI_SetFG_common(61706, this->actor.home.pos, 0);
    aTOU_actor_move(thisx, game_play);
    this->actor.update = aTOU_actor_move;
}

s32 aTOU_actor_draw_before(Game_Play* game_play UNUSED, SkeletonInfoR* skeletonInfo UNUSED, s32 jointIndex,
                           Gfx** dlist) {
    // LIGHTHOUSE_JOINT_LIGHT
    if (jointIndex == 4) {
        *dlist = NULL;
    }
    return 1;
}

extern Gfx obj_s_toudai_light_model[];
extern Gfx obj_w_toudai_light_model[];
Gfx* mdl_519[] = { obj_s_toudai_light_model, obj_w_toudai_light_model };
Color_RGBA8 prmcol_520 = { 255, 255, 150, 120 };

#ifdef NON_EQUIVALENT
s32 aTOU_actor_draw_after(Game_Play* game_play, SkeletonInfoR* skeletonInfo, s32 jointIndex, Gfx** dlist,
                          u8* displayBufferFlag, Toudai* arg5, s_xyz* rotation, xyz_t* translation) {
    s32 type;    // sp24
    s32 object;  // sp20
    s32 palette; // sp1C
    GraphicsContext* temp_a3;
    u8 var_a0;
    Mtx* mtx; // sp18
    u32 temp_v1;
    u32 temp;
    Gfx* gfx;

    // LIGHTHOUSE_JOINT_LIGHT
    if ((jointIndex == 4) && (arg5->unk2CC)) {
        OPEN_DISPS(temp_a3);
        mtx = _Matrix_to_Mtx_new(temp_a3);
        if (mtx != NULL) {
            type = (common_data.time.season == 3);
            object = common_data.unk_10098->unk_AC(45);
            palette = common_data.unk_10098->unk_450(90);
            func_800BD5C0_jp(game_play->state.gfxCtx);
            gfx = LIGHT_DISP;
            gSPSegment(gfx++, 0x08, palette);
            gSPSegment(gfx++, 0x06, object);

            temp = arg5->unk2C8;
            var_a0 = arg5->unk2CC;
            temp_v1 = arg5->unk2D0;
            if (arg5->unk2D0 < arg5->unk2CC) {
                arg5->unk2CC = temp_v1;
            }
            gDPPipeSync(gfx++);
            gDPSetPrimColor(gfx++, 0, arg5->unk2D0, prmcol_520.r, prmcol_520.g, temp, var_a0);
            gSPMatrix(gfx++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfx++, mdl_519[type]);
            if (!temp_a3) {}
        }
        CLOSE_DISPS(temp_a3);
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/aTOU_actor_draw_after.s")
#endif

#ifdef NON_EQUIVALENT
void aTOU_actor_draw(Actor* thisx, Game_Play* game_play) {
    Toudai* this = THIS;
    GraphicsContext* gfxCtx = game_play->state.gfxCtx;
    UNK_PTR sp68; // object
    u16* sp64;    // palette
    GraphicsContext* temp_a2;
    Mtx* mtx; // temp_v1
    Gfx* gfx;
    CommonData_unk_10098* ptr;
    u8 t = this->skeletonInfo.skeleton->unk01;
    OPEN_DISPS(gfxCtx);
    ptr = common_data.unk_10098;
    mtx = GRAPH_ALLOC(gfxCtx, t * sizeof(Mtx));
    if (mtx != NULL) {
        sp68 = ptr->unk_AC(45);
        sp64 = ptr->unk_450(90);
        func_800BD5E8_jp(gfx);
        gfx = POLY_OPA_DISP;
        gSPSegment(gfx++, 0x08, sp64);
        gSegments[6] = OS_K0_TO_PHYSICAL(sp68);
        gSPSegment(gfx++, 0x06, sp68);
        POLY_OPA_DISP = gfx;
        _texture_z_light_fog_prim_xlu(gfx);

        gfx = POLY_XLU_DISP;
        gSPSegment(gfx++, 0x08, sp64);
        gSPSegment(gfx++, 0x06, sp68);
        POLY_XLU_DISP = gfx;
        Setpos_HiliteReflect_init(&this->actor.world.pos, game_play);
        Setpos_HiliteReflect_xlu_init(&this->actor.world.pos, game_play);
        cKF_Si3_draw_R_SV(game_play, &this->skeletonInfo, mtx, aTOU_actor_draw_before, aTOU_actor_draw_after, this);
        common_data.unk_10080->unk_4(game_play, &aTOU_shadow_data, 45);
    }
    CLOSE_DISPS(gfxCtx);
    if (gfxCtx) {}
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/aTOU_actor_draw.s")
#endif
