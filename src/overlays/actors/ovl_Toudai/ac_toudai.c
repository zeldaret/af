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

void aTOU_actor_ct(Actor* thisx, Game_Play* game_play UNUSED) {
    Toudai* this = THIS;
    static BaseSkeletonR* skl[] = { &cKF_bs_r_obj_s_toudai, &cKF_bs_r_obj_w_toudai };
    s32 type = (common_data.time.season == WINTER);

    gSegments[6] = OS_K0_TO_PHYSICAL(common_data.clip.structureClip->getObjectSegment(STRUCTURE_TYPE_TOUDAI));
    cKF_SkeletonInfo_R_ct(&this->structureActor.skeletonInfo, skl[type], NULL, this->structureActor.jointTable,
                          this->structureActor.morphTable);
    aTOU_set_bgOffset(this, 1);
    aTOU_setup_action(this, 0);
    cKF_SkeletonInfo_R_play(&this->structureActor.skeletonInfo);
    this->structureActor.actor.world.pos.x -= 20.0f;
    this->structureActor.actor.world.pos.z -= 20.0f;
}

void aTOU_actor_dt(Actor* thisx, Game_Play* game_play UNUSED) {
    Toudai* this = THIS;

    common_data.clip.structureClip->removeInstanceProc(common_data.clip.structureClip->objectSegmentTable,
                                                       ARRAY_COUNT(common_data.clip.structureClip->objectSegmentTable),
                                                       STRUCTURE_TYPE_TOUDAI, thisx);
    common_data.clip.structureClip->removeInstanceProc(common_data.clip.structureClip->paletteSegmentTable,
                                                       ARRAY_COUNT(common_data.clip.structureClip->paletteSegmentTable),
                                                       STRUCTURE_PALETTE_TOUDAI, thisx);
    common_data.clip.structureClip->removeInstanceProc(common_data.clip.structureClip->shadowSegmentTable,
                                                       ARRAY_COUNT(common_data.clip.structureClip->shadowSegmentTable),
                                                       STRUCTURE_TYPE_TOUDAI, thisx);
    cKF_SkeletonInfo_R_dt(&this->structureActor.skeletonInfo);
    thisx->world.pos.x += 20.0f;
    thisx->world.pos.z += 20.0f;
}

void aTOU_set_bgOffset(Toudai* this, s32 heightTableIndex) {
    static mCoBG_unkStruct2 height_table_ct[] = { { 0x64, 16, 16, 16, 16, 16, 0 },
                                                  { 0x64, 16, 16, 16, 16, 16, 0 },
                                                  { 0x64, 16, 16, 16, 16, 16, 0 },
                                                  { 0x64, 16, 16, 16, 16, 16, 0 } };
    static mCoBG_unkStruct2* height_table[] = { height_table_ct, height_table_ct };
    static f32 addX[] = { -40.0f, 0.0f };
    static f32 addZ[] = { -40.0f, 0.0f };
    s32 i;
    xyz_t pos;
    mCoBG_unkStruct2* offsetTable = height_table[heightTableIndex];

    for (i = 0; i < 2; i++) {
        pos.z = addZ[i] + this->structureActor.actor.home.pos.z;
        pos.x = addX[0] + this->structureActor.actor.home.pos.x;
        mCoBG_SetPluss5PointOffset_file(pos, *offsetTable, "../ac_toudai_move.c_inc", 76);
        offsetTable++;
        pos.x = addX[1] + this->structureActor.actor.home.pos.x;
        mCoBG_SetPluss5PointOffset_file(pos, *offsetTable, "../ac_toudai_move.c_inc", 80);
        offsetTable++;
    }
}

void aTOU_color_ctrl(Toudai* this) {
    f32 var_fv0;
    s32 frameTemp;

    if (this->structureActor.unk_2BC == 0) {
        add_calc(&this->structureActor.unk_2C8, 0.0f, 0.3f, 100.0f, 1.0f);
        add_calc(&this->structureActor.unk_2CC, 0.0f, 0.3f, 100.0f, 1.0f);
        add_calc(&this->structureActor.unk_2D0, 0.0f, 0.1f, 100.0f, 1.0f);
        return;
    }

    frameTemp = this->structureActor.unk_1E8 - 51;
    var_fv0 = (frameTemp < 0) ? 1.0f : -1.0f;
    frameTemp = ABS(frameTemp);

    if (frameTemp == 0) {
        this->structureActor.unk_2C8 = 220.0f;
        this->structureActor.unk_2CC = 240.0f;

    } else if (frameTemp >= 40) {
        add_calc(&this->structureActor.unk_2C8, 0.0f, 0.3f, 100.0f, 1.0f);
        add_calc(&this->structureActor.unk_2CC, 0.0f, 0.3f, 100.0f, 1.0f);

    } else if (frameTemp < 10) {
        this->structureActor.unk_2C8 = this->structureActor.unk_2C8 + (9.0f * var_fv0);
        this->structureActor.unk_2CC = this->structureActor.unk_2CC + (14.0f * var_fv0);

    } else if (frameTemp < 30) {
        this->structureActor.unk_2C8 = this->structureActor.unk_2C8 + (2.5f * var_fv0);
        this->structureActor.unk_2CC = this->structureActor.unk_2CC + (4.5f * var_fv0);

    } else {
        this->structureActor.unk_2C8 = this->structureActor.unk_2C8 + (8.0f * var_fv0);
        this->structureActor.unk_2CC = this->structureActor.unk_2CC + var_fv0;
    }

    add_calc(&this->structureActor.unk_2D0, 255.0f, 0.1f, 100.0f, 1.0f);
}

void aTOU_init(Toudai* this, Game_Play* game_play UNUSED) {
    aTOU_setup_action(this, 1);
}

void aTOU_wait(Toudai* this, Game_Play* game_play UNUSED) {
    if ((common_data.time.nowSec >= 0xFD20) || (common_data.time.nowSec < 0x4650)) {
        this->structureActor.unk_2BC = 1;
        this->structureActor.skeletonInfo.frameControl.speed = 1.0f;
        aTOU_setup_action(this, 2);
    }
}

void aTOU_lighting(Toudai* this, Game_Play* game_play UNUSED) {
    if ((common_data.time.nowSec < 64800) && (common_data.time.nowSec >= 18000)) {
        aTOU_setup_action(this, 3);
    }
}

void aTOU_lightout(Toudai* this, Game_Play* game_play UNUSED) {
    if (this->structureActor.unk_1E8 == 0x33) {
        this->structureActor.unk_2BC = 0;
        this->structureActor.skeletonInfo.frameControl.speed = 0.0f;
        aTOU_setup_action(this, 1);
    }
}

extern BaseAnimationR cKF_ba_r_obj_s_toudai;
extern BaseAnimationR cKF_ba_r_obj_w_toudai;

void aTOU_setup_action(Toudai* this, s32 processIndex) {
    static BaseAnimationR* ani[] = { &cKF_ba_r_obj_s_toudai, &cKF_ba_r_obj_w_toudai };
    static ToudaiActionFunc process[] = { aTOU_init, aTOU_wait, aTOU_lighting, aTOU_lightout };
    s32 type;

    if (processIndex == 0) {
        type = (common_data.time.season == WINTER);
        cKF_SkeletonInfo_R_init(&this->structureActor.skeletonInfo, this->structureActor.skeletonInfo.skeleton,
                                ani[type], 1.0f, 100.0f, 51.0f, 0.0f, 0.0f, ANIMATION_REPEAT, NULL);
    }

    this->structureActor.process = process[processIndex];
    this->structureActor.unk_2B4 = processIndex;
}

void aTOU_actor_move(Actor* thisx, Game_Play* game_play) {
    Toudai* this = THIS;

    gSegments[6] = OS_K0_TO_PHYSICAL(common_data.clip.structureClip->getObjectSegment(STRUCTURE_TYPE_TOUDAI));
    this->structureActor.unk_174 = cKF_SkeletonInfo_R_play(&this->structureActor.skeletonInfo);
    this->structureActor.unk_1E8 = this->structureActor.skeletonInfo.frameControl.currentFrame;
    ((ToudaiActionFunc)this->structureActor.process)(this, game_play);
    aTOU_color_ctrl(this);
}

void aTOU_actor_init(Actor* thisx, Game_Play* game_play) {
    Toudai* this = THIS;

    mFI_SetFG_common(61706, this->structureActor.actor.home.pos, 0);
    aTOU_actor_move(thisx, game_play);
    this->structureActor.actor.update = aTOU_actor_move;
}

s32 aTOU_actor_draw_before(Game_Play* game_play UNUSED, SkeletonInfoR* skeletonInfo UNUSED, s32 jointIndex, Gfx** dlist,
                           u8* displayBufferFlag UNUSED, void* thisx UNUSED, s_xyz* rotation UNUSED,
                           xyz_t* translation UNUSED) {
    // LIGHTHOUSE_JOINT_LIGHT
    if (jointIndex == 4) {
        *dlist = NULL;
    }
    return 1;
}

extern Gfx obj_s_toudai_light_model[];
extern Gfx obj_w_toudai_light_model[];

s32 aTOU_actor_draw_after(Game_Play* game_play, SkeletonInfoR* skeletonInfo UNUSED, s32 jointIndex, Gfx** dlist UNUSED,
                          u8* displayBufferFlag UNUSED, void* thisx, s_xyz* rotation UNUSED,
                          xyz_t* translation UNUSED) {
    static Gfx* mdl[] = { obj_s_toudai_light_model, obj_w_toudai_light_model };
    static Color_RGBA8 prmcol = { 255, 255, 150, 120 };
    GraphicsContext* gfxCtx = game_play->state.gfxCtx;
    Toudai* this = (Toudai*)thisx;
    s32 type;
    s32 object;
    u16* palette;
    Mtx* mtx;

    // LIGHTHOUSE_JOINT_LIGHT
    if ((jointIndex == 4) && ((s32)this->structureActor.unk_2CC)) {
        mtx = _Matrix_to_Mtx_new(gfxCtx);
        if (mtx != NULL) {
            type = common_data.time.season == WINTER;
            object = common_data.clip.structureClip->getObjectSegment(STRUCTURE_TYPE_TOUDAI);
            palette = common_data.clip.structureClip->getPalSegment(STRUCTURE_PALETTE_TOUDAI);
            _texture_z_light_fog_prim_light(gfxCtx);
            OPEN_LIGHT_DISP(gfxCtx);
            gSPSegment(__light++, 8, palette);
            gSPSegment(__light++, 6, object);
            prmcol.b = this->structureActor.unk_2C8;
            prmcol.a = this->structureActor.unk_2CC;
            if ((u8)this->structureActor.unk_2D0 < prmcol.a) {
                prmcol.a = this->structureActor.unk_2D0;
            }
            gDPPipeSync(__light++);
            gDPSetPrimColor(__light++, 0, (u8)this->structureActor.unk_2D0, prmcol.r, prmcol.g, prmcol.b, prmcol.a);
            gSPMatrix(__light++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(__light++, mdl[type]);
            CLOSE_LIGHT_DISP(gfxCtx);
        }
    }
    return 1;
}

void aTOU_actor_draw(Actor* thisx, Game_Play* game_play) {
    UNUSED s32 pad;
    GraphicsContext* gfxCtx = game_play->state.gfxCtx;
    Toudai* this = THIS;
    SkeletonInfoR* skeletonInfo = &this->structureActor.skeletonInfo;
    Mtx* mtx;
    s32 object;
    u16* palette;
    u8 numberOfDisplayLists = skeletonInfo->skeleton->unk01;
    xyz_t* worldPosition = &this->structureActor.actor.world.pos;

    mtx = GRAPH_ALLOC_NO_ALIGN(gfxCtx, numberOfDisplayLists * sizeof(Mtx));

    if (mtx != NULL) {
        object = common_data.clip.structureClip->getObjectSegment(STRUCTURE_TYPE_TOUDAI);
        palette = common_data.clip.structureClip->getPalSegment(STRUCTURE_PALETTE_TOUDAI);

        _texture_z_light_fog_prim_npc(gfxCtx);
        OPEN_POLY_OPA_DISP(gfxCtx);
        gSPSegment(__polyOpa++, 0x8, palette);
        gSegments[6] = OS_K0_TO_PHYSICAL(object);
        gSPSegment(__polyOpa++, 0x6, object);
        CLOSE_POLY_OPA_DISP(gfxCtx);

        _texture_z_light_fog_prim_xlu(gfxCtx);
        OPEN_POLY_XLU_DISP(gfxCtx);
        gSPSegment(__polyXlu++, 0x8, palette);
        gSPSegment(__polyXlu++, 0x6, object);
        CLOSE_POLY_XLU_DISP(gfxCtx);

        Setpos_HiliteReflect_init(worldPosition, game_play);
        Setpos_HiliteReflect_xlu_init(worldPosition, game_play);
        cKF_Si3_draw_R_SV(game_play, skeletonInfo, mtx, aTOU_actor_draw_before, aTOU_actor_draw_after, this);
        common_data.clip.unk_074->unk_04(game_play, &aTOU_shadow_data, 0x2D);
    }
}
