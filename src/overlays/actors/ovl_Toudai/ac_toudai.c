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

void func_80AAB488_jp(Toudai* this, s32);
void func_80AAB81C_jp(Toudai *this, PlayState* play UNUSED);
void func_80AAB840_jp(Toudai *this, PlayState* play UNUSED);
void func_80AAB894_jp(Toudai *this, PlayState* play UNUSED);
void func_80AAB8D8_jp(Toudai *this, PlayState* play UNUSED);
void func_80AAB918_jp(Toudai *this, s32 arg1);

ActorProfile Toudai_Profile = {
    /* */ 175, //ACTOR_TOUDAI
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x5843,
    /* */ 3, //GAMEPLAY_KEEP
    /* */ sizeof(Toudai),
    /* */ aTOU_actor_ct,
    /* */ aTOU_actor_dt,
    /* */ aTOU_actor_init,
    /* */ aTOU_actor_draw,
    /* */ NULL,
};

UNK_TYPE D_80AAC084_jp[] = {0x01000100, 0x00010100, 0x01000000, 0x01010001, 0x01000100};
UNK_TYPE D_80AAC098_jp[] = {0x00000014, D_80AAC084_jp, 0x42700000, 0x060089C8, 0x06008B08};
//skl
extern BaseSkeletonR* D_80AAC0AC_jp[] = {0x0607EE1C, 0x06080A24}; //cKF_bs_r_obj_s_toudai, cKF_bs_r_obj_w_toudai
//height_table_ct
UNK_TYPE D_80AAC0B4_jp[] = {0x64101010, 0x10100064, 0x10101010, 0x10006410, 0x10101010, 0x00641010, 0x10101000};
//height_table
mCoBG_OffsetTable* D_80AAC0D0_jp[] = {D_80AAC0B4_jp, D_80AAC0B4_jp};
//addX
f32 D_FLT_80AAC0D8_jp[] = {-40.0f, 0.0f};
//addZ
f32 D_FLT_80AAC0E0_jp[] = {-40.0f, 0.0f};
//ani
BaseAnimationR* D_80AAC0E8_jp[] = {0x0607EE6C, 0x06080A74}; //cKF_ba_r_obj_s_toudai, cKF_ba_r_obj_w_toudai
//process
ToudaiActionFunc D_80AAC0F0_jp[] = {func_80AAB81C_jp, func_80AAB840_jp, func_80AAB894_jp, func_80AAB8D8_jp};
//mdl
Gfx* D_80AAC100_jp[] = {0x0607E188, 0x0607FD90}; //obj_s_toudai_light_model, obj_w_toudai_light_model
Color_RGBA8 D_80AAC108_jp = {0xFF, 0xFF, 0x96, 0x78};

// aTOU_fgunit_on
// aTOU_fgunit_off
// aTOU_actor_ct
// aTOU_actor_dt
// aTOU_rewrite_door
// aTOU_set_bgOffset
// aTOU_color_ctrl
// aTOU_init
// aTOU_waitf
// aTOU_lighting
// aTOU_lightout
// aTOU_setup_action
// aTOU_actor_move
// aTOU_actor_init
// aTOU_actor_draw_before
// aTOU_actor_draw_after
// aTOU_actor_draw

// aTOU_shadow_data
// aTOU_shadow_vtx_fix_flg_table
// height_table

typedef enum Season {
    /* 0 */ SPRING,
    /* 1 */ SUMMER,
    /* 2 */ FALL,
    /* 3 */ WINTER
} Season;

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/aTOU_actor_ct.s")
void aTOU_actor_ct(Actor *thisx, PlayState *play UNUSED)
{
    Toudai* this = THIS;
    s32 sp30 = (common_data.season == WINTER);
    
    gSegments[6] = OS_K0_TO_PHYSICAL(common_data.structureClip->unk_AC(STRUCTURE_TOUDAI));
    cKF_SkeletonInfo_R_ct(&this->skeletonInfo, D_80AAC0AC_jp[sp30], NULL, this->jointTable, this->morphTable);
    func_80AAB488_jp(this, 1);
    func_80AAB918_jp(this, 0);
    cKF_SkeletonInfo_R_play(&this->skeletonInfo);
    this->actor.world.pos.x -= 20.0f;
    this->actor.world.pos.z -= 20.0f;
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/aTOU_actor_dt.s")
void aTOU_actor_dt(Actor *thisx, PlayState *play UNUSED)
{
    Toudai* this = THIS;

    common_data.structureClip->unk_A8(&common_data.structureClip->unk_B0, 8, STRUCTURE_TOUDAI, (Structure*)this);
    common_data.structureClip->unk_A8(&common_data.structureClip->unk_454, 9, STRUCTURE_TOUDAI_PAL, (Structure*)this);
    common_data.structureClip->unk_A8(&common_data.structureClip->unk_86C, 8, STRUCTURE_TOUDAI, (Structure*)this);
    cKF_SkeletonInfo_R_dt(&this->skeletonInfo);
    thisx->world.pos.x += 20.0f;
    thisx->world.pos.z += 20.0f;
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/func_80AAB488_jp.s")
//aTOU_set_bgOffset
void func_80AAB488_jp(Toudai *this, s32 arg1)
{
    s32 iVar2 = 0;
    Vec3f sp50;
    mCoBG_OffsetTable* offsetTable = D_80AAC0D0_jp[arg1];

    do
    {
        sp50.z = D_FLT_80AAC0E0_jp[iVar2] + this->actor.home.pos.z;
        sp50.x = D_FLT_80AAC0D8_jp[0] + this->actor.home.pos.x;
        mCoBG_SetPluss5PointOffset_file(sp50, *offsetTable, "../ac_toudai_move.c_inc", 76);
        offsetTable++;
        sp50.x = D_FLT_80AAC0D8_jp[1] + this->actor.home.pos.x;
        mCoBG_SetPluss5PointOffset_file(sp50, *offsetTable, "../ac_toudai_move.c_inc", 80);
        offsetTable++;
        iVar2++;
    } while (iVar2 < 2);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/func_80AAB60C_jp.s")
void func_80AAB60C_jp(Toudai *this)
{
    f32 var_fv0;
    s32 var_v0;

    if (this->unk2BC == 0)
    {
        add_calc(&this->unk2C8, 0.0f, 0.3f, 100.0f, 1.0f);
        add_calc(&this->unk2CC, 0.0f, 0.3f, 100.0f, 1.0f);
        add_calc(&this->unk2D0, 0.0f, 0.1f, 100.0f, 1.0f);
        return;
    }
    var_v0 = this->unk1E8 - 0x33;
    if (var_v0 < 0)
    {
        var_fv0 = 1.0f;
    }
    else
    {
        var_fv0 = -1.0f;
    }
    if (var_v0 < 0)
    {
        var_v0 = -var_v0;
    }
    if (var_v0 == 0)
    {
        this->unk2C8 = 220.0f;
        this->unk2CC = 240.0f;
    }
    else if (var_v0 >= 0x28)
    {
        add_calc(&this->unk2C8, 0.0f, 0.3f, 100.0f, 1.0f);
        add_calc(&this->unk2CC, 0.0f, 0.3f, 100.0f, 1.0f);
    }
    else if (var_v0 < 0xA)
    {
        this->unk2C8 = this->unk2C8 + (9.0f * var_fv0);
        this->unk2CC = this->unk2CC + (14.0f * var_fv0);
    }
    else if (var_v0 < 0x1E)
    {
        this->unk2C8 = this->unk2C8 + (2.5f * var_fv0);
        this->unk2CC = this->unk2CC + (4.5f * var_fv0);
    }
    else
    {
        this->unk2C8 = this->unk2C8 + (8.0f * var_fv0);
        this->unk2CC = this->unk2CC + var_fv0;
    }
    add_calc(&this->unk2D0, 255.0f, 0.1f, 100.0f, 1.0f);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/func_80AAB81C_jp.s")
//aTOU_init
void func_80AAB81C_jp(Toudai *this, PlayState* play UNUSED)
{
    func_80AAB918_jp(this, 1);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/func_80AAB840_jp.s")
//aTOU_wait
void func_80AAB840_jp(Toudai *this, PlayState* play UNUSED)
{
    if ((common_data.unk10118 >= 0xFD20) || (common_data.unk10118 < 0x4650))
    {
        this->unk2BC = 1;
        this->skeletonInfo.frameControl.speed = 1.0f;
        func_80AAB918_jp(this, 2);
    }
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/func_80AAB894_jp.s")
//aTOU_lighting
void func_80AAB894_jp(Toudai *this, PlayState* play UNUSED)
{
    if ((common_data.unk10118 < 0xFD20) && (common_data.unk10118 >= 0x4650))
    {
        func_80AAB918_jp(this, 3);
    }
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/func_80AAB8D8_jp.s")
//aTOU_lightout
void func_80AAB8D8_jp(Toudai *this, PlayState* play UNUSED)
{
    if (this->unk1E8 == 0x33)
    {
        this->unk2BC = 0;
        this->skeletonInfo.frameControl.speed = 0.0f;
        func_80AAB918_jp(this, 1);
    }
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/func_80AAB918_jp.s")
void func_80AAB918_jp(Toudai *this, s32 arg1)
{
    s32 temp;

    if (arg1 == 0)
    {
        temp = common_data.season == WINTER;
        cKF_SkeletonInfo_R_init(&this->skeletonInfo, this->skeletonInfo.skeleton, D_80AAC0E8_jp[temp], 1.0f, 100.0f, 51.0f, 0.0f, 0.0f, ANIMATION_REPEAT, NULL);
    }
    this->unk2A0 = D_80AAC0F0_jp[arg1];
    this->unk2B4 = arg1;
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/func_80AAB9C8_jp.s")
void func_80AAB9C8_jp(Toudai *this, PlayState *play)
{
    gSegments[6] = OS_K0_TO_PHYSICAL(common_data.structureClip->unk_AC(STRUCTURE_TOUDAI));
    this->unk174 = cKF_SkeletonInfo_R_play(&this->skeletonInfo);
    this->unk1E8 = this->skeletonInfo.frameControl.currentFrame;
    this->unk2A0(this, play);
    func_80AAB60C_jp(this);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/aTOU_actor_init.s")
void aTOU_actor_init(Actor *thisx, PlayState *play)
{
    Toudai* this = THIS;

    mFI_SetFG_common(0xF10A, this->actor.home.pos, 0);
    func_80AAB9C8_jp(this, play);
    this->actor.update = (ActorFunc)func_80AAB9C8_jp;
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/func_80AABAB8_jp.s")
//aTOU_actor_draw_before
s32 func_80AABAB8_jp(PlayState* play UNUSED, SkeletonInfoR* skeletonInfo UNUSED, s32 jointIndex, Gfx** dlist)
{
    if (jointIndex == 4)
    {
        *dlist = NULL;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/func_80AABAD8_jp.s")
s32 func_80AABAD8_jp(PlayState *play, SkeletonInfoR *skeletonInfo, s32 jointIndex, Gfx **dlist, u8 *displayBufferFlag, void *, Vec3s *rotation, Vec3f *translation); /* extern */

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/aTOU_actor_draw.s")
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
//     CommonData_unk_10098* ptr;
//     u8 t = this->skeletonInfo.skeleton->unk01;

//     OPEN_DISPS(gfxCtx);
//     mtx = GRAPH_ALLOC(gfxCtx, t * sizeof(Mtx));
//     // temp_a2 = play->state.gfxCtx;
//     // temp_v1 = temp_a2->polyOpa.tha.tail - (thisx->unk190->unk1 << 6);
//     // temp_a2->polyOpa.tha.tail = temp_v1;
//     if (mtx != NULL)
//     {
//         // sp28 = temp_v1;
//         // sp78 = temp_a2;
//         sp68 = common_data.structureClip->unk_AC(STRUCTURE_TOUDAI);
//         sp64 = common_data.structureClip->unk_450(STRUCTURE_TOUDAI_PAL);
//         func_800BD5E8_jp(gfxCtx);
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
//         func_800BD598_jp(gfxCtx);

//         gfx = POLY_XLU_DISP;
//         // temp_v1_4 = temp_a2->polyXlu.tha.head;
//         // temp_v1_4->unk0 = 0xDB060020;
//         // temp_v1_5 = temp_v1_4 + 8;
//         // temp_v1_4->unk4 = sp64;
//         gSPSegment(gfx++, 0x08, sp64);
//         // temp_v1_5->unk0 = 0xDB060018;
//         // temp_v1_5->unk4 = sp68;
//         // temp_a2->polyXlu.tha.head = temp_v1_5 + 8;
//         gSPSegment(gfx++, 0x06, sp68);
//         POLY_XLU_DISP = gfx;
//         // temp_a0 = &thisx->world;
//         // sp24 = temp_a0;
//         Setpos_HiliteReflect_init(&this->actor.world.pos, play);
//         Setpos_HiliteReflect_xlu_init(&this->actor.world.pos, play);
//         cKF_Si3_draw_R_SV(play, &this->skeletonInfo, mtx, func_80AABAB8_jp, func_80AABAD8_jp, this);
//         common_data.unk_10080->unk_4(play, &D_80AAC098_jp, STRUCTURE_TOUDAI);
//     }
//     CLOSE_DISPS(gfxCtx);
//     if (gfxCtx) {}
// }
