#include "global.h"
#include "ac_toudai.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "c_keyframe.h"
#include "m_field_info.h"
#include "m_collision_bg.h"
#include "m_rcp.h"
#include "m_lib.h"
#include "overlays/actors/ovl_Structure/ac_structure.h"

#define THIS ((Toudai*)thisx)

void aTOU_actor_ct(Actor* thisx, PlayState* play);
void aTOU_actor_dt(Actor* thisx, PlayState* play);
void aTOU_actor_init(Actor* thisx, PlayState* play);
void aTOU_actor_draw(Actor* thisx, PlayState* play);

void aTOU_set_bgOffset(Toudai* this, s32 /*arg1*/);
void aTOU_init(Toudai* this, PlayState* play UNUSED);
void aTOU_wait(Toudai* this, PlayState* play UNUSED);
void aTOU_lighting(Toudai* this, PlayState* play UNUSED);
void aTOU_lightout(Toudai* this, PlayState* play UNUSED);
void aTOU_setup_action(Toudai* this, s32 processIndex);

s32 aTOU_actor_draw_after(PlayState* play, SkeletonInfoR* skeletonInfo, s32 jointIndex, Gfx** dlist,
                          u8* displayBufferFlag, void*, Vec3s* rotation, Vec3f* translation);

ActorProfile Toudai_Profile = {
    /* */ 175, // ACTOR_TOUDAI
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x5843,
    /* */ 3, // GAMEPLAY_KEEP
    /* */ sizeof(Toudai),
    /* */ aTOU_actor_ct,
    /* */ aTOU_actor_dt,
    /* */ aTOU_actor_init,
    /* */ aTOU_actor_draw,
    /* */ NULL,
};

// todo: remove somewhere else
typedef struct ShadowData {
    /* 0x00 */ u32 numberOfVertices;
    /* 0x04 */ u8* vertexFixFlagTable;
    /* 0x08 */ f32 size;
    /* 0x0C */ Vtx* vertices;
    /* 0x10 */ Gfx* model;
} ShadowData; // size = 0x10

UNK_TYPE aTOU_shadow_vtx_fix_flg_table[] = { 0x01000100, 0x00010100, 0x01000000, 0x01010001, 0x01000100 };
ShadowData aTOU_shadow_data[] = { 20, aTOU_shadow_vtx_fix_flg_table, 60.0f, 0x060089C8, 0x06008B08 };
// obj_s_toudai_shadow_v
// obj_s_toudai_shadow_1_model

// TODO move somewhere else
typedef enum Season {
    /* 0 */ SPRING,
    /* 1 */ SUMMER,
    /* 2 */ FALL,
    /* 3 */ WINTER
} Season;

static BaseSkeletonR* skl[] = { 0x0607EE1C, 0x06080A24 }; // cKF_bs_r_obj_s_toudai, cKF_bs_r_obj_w_toudai

void aTOU_actor_ct(Actor* thisx, PlayState* play UNUSED) {
    Toudai* this = THIS;
    s32 type = (common_data.season == WINTER);

    gSegments[6] = OS_K0_TO_PHYSICAL(common_data.structureClip->unk_AC(STRUCTURE_TOUDAI));
    cKF_SkeletonInfo_R_ct(&this->skeletonInfo, skl[type], NULL, this->jointTable, this->morphTable);
    aTOU_set_bgOffset(this, 1);
    aTOU_setup_action(this, 0);
    cKF_SkeletonInfo_R_play(&this->skeletonInfo);
    this->actor.world.pos.x -= 20.0f;
    this->actor.world.pos.z -= 20.0f;
}

void aTOU_actor_dt(Actor* thisx, PlayState* play UNUSED) {
    Toudai* this = THIS;

    // TODO remove the structure cast when the structure base struct gets put in
    common_data.structureClip->unk_A8(&common_data.structureClip->unk_B0, 8, STRUCTURE_TOUDAI, (Structure*)this);
    common_data.structureClip->unk_A8(&common_data.structureClip->unk_454, 9, STRUCTURE_TOUDAI_PAL, (Structure*)this);
    common_data.structureClip->unk_A8(&common_data.structureClip->unk_86C, 8, STRUCTURE_TOUDAI, (Structure*)this);
    cKF_SkeletonInfo_R_dt(&this->skeletonInfo);
    thisx->world.pos.x += 20.0f;
    thisx->world.pos.z += 20.0f;
}

mCoBG_OffsetTable height_table_ct[] = { { 0x64, 16, 16, 16, 16, 16, 0 },
                                        { 0x64, 16, 16, 16, 16, 16, 0 },
                                        { 0x64, 16, 16, 16, 16, 16, 0 },
                                        { 0x64, 16, 16, 16, 16, 16, 0 } };
static mCoBG_OffsetTable* height_table[] = { height_table_ct, height_table_ct };
static f32 addX[] = { -40.0f, 0.0f };
static f32 addZ[] = { -40.0f, 0.0f };


void aTOU_set_bgOffset(Toudai* this, s32 heightTableIndex) {
    s32 i;
    Vec3f pos;
    mCoBG_OffsetTable* offsetTable = height_table[heightTableIndex];

    for (i = 0; i < 2; i++) {
        pos.z = addZ[i] + this->actor.home.pos.z;
        pos.x = addX[0] + this->actor.home.pos.x;
        mCoBG_SetPluss5PointOffset_file(pos, *offsetTable, "../ac_toudai_move.c_inc", 76);
        offsetTable++;
        pos.x = addX[1] + this->actor.home.pos.x;
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

void aTOU_init(Toudai* this, PlayState* play UNUSED) {
    aTOU_setup_action(this, 1);
}

void aTOU_wait(Toudai* this, PlayState* play UNUSED) {
    if ((common_data.now_sec >= 0xFD20) || (common_data.now_sec < 0x4650)) {
        this->unk2BC = 1;
        this->skeletonInfo.frameControl.speed = 1.0f;
        aTOU_setup_action(this, 2);
    }
}

void aTOU_lighting(Toudai* this, PlayState* play UNUSED) {
    if ((common_data.now_sec < 64800) && (common_data.now_sec >= 18000)) {
        aTOU_setup_action(this, 3);
    }
}

void aTOU_lightout(Toudai* this, PlayState* play UNUSED) {
    if (this->unk1E8 == 0x33) {
        this->unk2BC = 0;
        this->skeletonInfo.frameControl.speed = 0.0f;
        aTOU_setup_action(this, 1);
    }
}

static BaseAnimationR* ani[] = { 0x0607EE6C, 0x06080A74 }; // cKF_ba_r_obj_s_toudai, cKF_ba_r_obj_w_toudai
static ToudaiActionFunc process[] = { aTOU_init, aTOU_wait, aTOU_lighting, aTOU_lightout };

void aTOU_setup_action(Toudai* this, s32 processIndex) {
    s32 type;

    if (processIndex == 0) {
        type = (common_data.season == WINTER);
        cKF_SkeletonInfo_R_init(&this->skeletonInfo, this->skeletonInfo.skeleton, ani[type], 1.0f, 100.0f, 51.0f, 0.0f,
                                0.0f, ANIMATION_REPEAT, NULL);
    }

    this->unk2A0 = process[processIndex];
    this->unk2B4 = processIndex;
}

void aTOU_actor_move(Toudai* this, PlayState* play) {
    gSegments[6] = OS_K0_TO_PHYSICAL(common_data.structureClip->unk_AC(STRUCTURE_TOUDAI));
    this->unk174 = cKF_SkeletonInfo_R_play(&this->skeletonInfo);
    this->unk1E8 = this->skeletonInfo.frameControl.currentFrame;
    this->unk2A0(this, play);
    aTOU_color_ctrl(this);
}

void aTOU_actor_init(Actor* thisx, PlayState* play) {
    Toudai* this = THIS;

    mFI_SetFG_common(61706, this->actor.home.pos, 0);
    aTOU_actor_move(this, play);
    this->actor.update = (ActorFunc)aTOU_actor_move;
}

s32 aTOU_actor_draw_before(PlayState* play UNUSED, SkeletonInfoR* skeletonInfo UNUSED, s32 jointIndex, Gfx** dlist) {
    //LIGHTHOUSE_JOINT_LIGHT
    if (jointIndex == 4) {
        *dlist = NULL;
    }
    return 1;
}

static Gfx* mdl[] = { 0x0607E188, 0x0607FD90 }; // obj_s_toudai_light_model, obj_w_toudai_light_model
static Color_RGBA8 prmcol = { 255, 255, 150, 120 };

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/aTOU_actor_draw_after.s")
// s32 aTOU_actor_draw_after(PlayState* play, SkeletonInfoR* skeletonInfo, s32 jointIndex, Gfx** dlist,
//                           u8* displayBufferFlag, Toudai* arg5, Vec3s* rotation, Vec3f* translation) {
//     // GraphicsContext* sp2C;
//     s32 type; //sp24
//     s32 object; //sp20
//     s32 palette; //sp1C
//     GraphicsContext* temp_a3;
//     // Mtx* temp_v0;
//     // s8 temp_a2;
//     u8 var_a0;
//     Mtx* mtx; //sp18
//     u32 temp_v1;
//     u32 temp;
//     // void* temp_v0_2;
//     // void* temp_v0_3;
//     // void* temp_v0_4;
//     // void* temp_v0_5;
//     // void* temp_v0_6;
//     // void* temp_v0_7;
//     Gfx* gfx;

//     // temp_a3 = play->state.gfxCtx;
//     //LIGHTHOUSE_JOINT_LIGHT
//     if ((jointIndex == 4) && (arg5->unk2CC)) {
//         OPEN_DISPS(temp_a3);
//         // sp2C = temp_a3;
//         mtx = _Matrix_to_Mtx_new(temp_a3);
//         // mtx = temp_v0;
//         if (mtx != NULL) {
//             type = (common_data.season == 3);
//             object = common_data.structureClip->unk_AC(STRUCTURE_TOUDAI);
//             palette = common_data.structureClip->getPalSegment(STRUCTURE_TOUDAI_PAL);
//             func_800BD5C0_jp(play->state.gfxCtx);
//             gfx = LIGHT_DISP;
//             gSPSegment(gfx++, 0x08, palette);
//             gSPSegment(gfx++, 0x06, object);

//             temp = arg5->unk2C8;
//             var_a0 = arg5->unk2CC;
//             temp_v1 = arg5->unk2D0;
//             if (arg5->unk2D0 < arg5->unk2CC) {
//                 arg5->unk2CC = temp_v1;
//             }
//             gDPPipeSync(gfx++);
//             gDPSetPrimColor(gfx++, 0, arg5->unk2D0, prmcol.r, prmcol.g, temp, var_a0);
//             gSPMatrix(gfx++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
//             gSPDisplayList(gfx++, mdl[type]);
//             if (!temp_a3)
//             {
//             }
//         }
//         CLOSE_DISPS(temp_a3);
//     }
//     return 1;
// }

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/aTOU_actor_draw.s")
// TODO look at the m_rcp function prototypes again, they might be wrong
// void aTOU_actor_draw(Actor *thisx, PlayState *play)
// {
//     Toudai* this = THIS;
//     GraphicsContext *gfxCtx = play->state.gfxCtx;
//     UNK_PTR sp68; //object file i guess?
//     u16* sp64; //palette
//     // Mtx *sp28;
//     // PosRot *sp24;
//     GraphicsContext *temp_a2;
//     Mtx *mtx; //temp_v1
//     // PosRot *temp_a0;
//     // void *temp_v1_2;
//     // void *temp_v1_3;
//     // void *temp_v1_4;
//     // void *temp_v1_5;
//     Gfx* gfx;
//     StructureClip* ptr;
//     u8 t = this->skeletonInfo.skeleton->unk01;
//     // if ((!common_data.unk_10080) && (!common_data.unk_10080))
//     // {
//     // }
//     OPEN_DISPS(gfxCtx);
//     ptr = common_data.structureClip;
//     mtx = GRAPH_ALLOC(gfxCtx, t * sizeof(Mtx));
//     // temp_a2 = play->state.gfxCtx;
//     // temp_v1 = temp_a2->polyOpa.tha.tail - (thisx->unk190->unk1 << 6);
//     // temp_a2->polyOpa.tha.tail = temp_v1;
//     if (mtx != NULL)
//     {
//         // sp28 = temp_v1;
//         // sp78 = temp_a2;
//         sp68 = ptr->unk_AC(STRUCTURE_TOUDAI);
//         sp64 = ptr->getPalSegment(STRUCTURE_TOUDAI_PAL);
//         func_800BD5E8_jp(gfx);
//         gfx = POLY_OPA_DISP;
//         // temp_v1_2 = temp_a2->polyOpa.tha.head;
//         // temp_v1_2->unk0 = 0xDB060020;
//         // temp_v1_3 = temp_v1_2 + 8;
//         // temp_v1_2->unk4 = sp64;
//         gSPSegment(gfx++, 0x08, sp64);
//         gSegments[6] = OS_K0_TO_PHYSICAL(sp68);
//         // temp_v1_3->unk0 = 0xDB060018;
//         // temp_v1_3->unk4 = sp68;
//         // temp_a2->polyOpa.tha.head = temp_v1_3 + 8;
//         gSPSegment(gfx++, 0x06, sp68);
//         POLY_OPA_DISP = gfx;
//         // sp78 = temp_a2;
//         func_800BD598_jp(gfx);

//     gfx = POLY_XLU_DISP;
//     // temp_v1_4 = temp_a2->polyXlu.tha.head;
//     // temp_v1_4->unk0 = 0xDB060020;
//     // temp_v1_5 = temp_v1_4 + 8;
//     // temp_v1_4->unk4 = sp64;
//     gSPSegment(gfx++, 0x08, sp64);
//     // temp_v1_5->unk0 = 0xDB060018;
//     // temp_v1_5->unk4 = sp68;
//     // temp_a2->polyXlu.tha.head = temp_v1_5 + 8;
//     gSPSegment(gfx++, 0x06, sp68);
//     POLY_XLU_DISP = gfx;
//     // temp_a0 = &thisx->world;
//     // sp24 = temp_a0;
//     Setpos_HiliteReflect_init(&this->actor.world.pos, play);
//     Setpos_HiliteReflect_xlu_init(&this->actor.world.pos, play);
//     cKF_Si3_draw_R_SV(play, &this->skeletonInfo, mtx, aTOU_actor_draw_before, aTOU_actor_draw_after, this);
//     common_data.unk_10080->unk_4(play, &aTOU_shadow_data, STRUCTURE_TOUDAI);
// }
// CLOSE_DISPS(gfxCtx);
// if (gfxCtx) {}
// }
