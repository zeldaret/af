#include "global.h"

///////////////////////////////////////////////////////////////////////////////
//z64math.h

typedef struct {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
} Vec3s; // size = 0x06

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
} Vec3f; // size = 0x0C


float fabsf(float f);
#pragma intrinsic(fabsf)

#define IS_ZERO(f) (fabsf(f) < 0.008f)

///////////////////////////////////////////////////////////////////////////////
//z64animation.h

typedef enum cKF_FC_Mode {
    cKF_FC_STOP = 0,
    cKF_FC_REPEAT = 1,
    cKF_FC_LAST_INDEX = 2
} cKF_FC_Mode;

typedef struct {
    /* 0x00 */ f32 start;
    /* 0x04 */ f32 end;
    /* 0x08 */ f32 max;
    /* 0x0C */ f32 speed;
    /* 0x10 */ f32 current;
    /* 0x14 */ s32 mode;
} FrameControl; // size = 0x18

typedef struct {
    /* 0x0 */ Gfx* shape;
    /* 0x4 */ u8 child;
    /* 0x5 */ u8 work_flag;
    /* 0x6 */ u8 func_index;
    /* 0x7 */ char pad; //TODO can i remove this?
} JointElem; // size = 0x8

typedef struct {
    /* 0x0 */ Gfx* shape;
    /* 0x4 */ u8 child;
    /* 0x5 */ u8 work_flag;
    /* 0x6 */ Vec3s trs;
} JointElem_R; // size = 0xC

typedef struct {
    /* 0x00 */ u8 joint_num;
    /* 0x01 */ u8 display_joint_num;
    /* 0x02 */ char pad[0x2]; //TODO can i remove this?
    /* 0x04 */ JointElem* joint_tbl;
} BaseSkeleton; // size = 0x8

typedef struct {
    /* 0x00 */ u8 joint_num;
    /* 0x01 */ u8 display_joint_num;
    /* 0x02 */ char pad[0x2]; //TODO can i remove this?
    /* 0x04 */ JointElem_R* joint_tbl;
} BaseSkeleton_R; // size = 0x14

typedef struct {
    /* 0x00 */ u16* ConstKeyCheckBitTbl;
    /* 0x04 */ s16* data_source;
    /* 0x08 */ s16* key_num;
    /* 0x0C */ s16* const_value_tbl;
    /* 0x10 */ s16 ext;
    /* 0x12 */ s16 frames;
} BaseAnimation; // size = 0x14

typedef struct {
    /* 0x00 */ u16* ConstKeyCheckBitTbl;
    /* 0x04 */ s16* data_source;
    /* 0x08 */ s16* key_num;
    /* 0x0C */ s16* const_value_tbl;
    /* 0x10 */ s16 ext;
    /* 0x12 */ s16 frames;
} BaseAnimation_R; // size = 0x14

typedef struct {
    /* 0x00 */ FrameControl frameCtrl;
    /* 0x18 */ BaseSkeleton* skeleton;
    /* 0x1C */ BaseAnimation* animation;
    /* 0x20 */ void* unk_20; //BEFORE_FUNC_TBL before_func_tbl
    /* 0x24 */ f32 morphCounter;
    /* 0x28 */ Vec3s* now_joint;
    /* 0x2C */ Vec3s* morph_joint;
} SkeletonInfo; // size = 0x30

typedef struct {
    /* 0x00 */ FrameControl frameCtrl;
    /* 0x18 */ BaseSkeleton_R* skeleton;
    /* 0x1C */ BaseAnimation_R* animation;
    /* 0x20 */ f32 morphCounter;
    /* 0x24 */ Vec3s* now_joint; //array of Vec3s
    /* 0x28 */ Vec3s* morph_joint;
    /* 0x2C */ Vec3s* diff_rot_tbl;
    /* 0x30 */ s32 move_flag;
    /* 0x34 */ Vec3f idle_world_pos;
    /* 0x40 */ s16 idle_set_angleY;
    /* 0x42 */ char pad[0x2]; //TODO can i remove this?
    /* 0x44 */ Vec3f base_shape_trs;
    /* 0x50 */ Vec3s base_data_angle;
    /* 0x56 */ Vec3s renew_base_data_angle;
    /* 0x5C */ f32 correct_counter;
    /* 0x60 */ Vec3f d_correct_base_world_pos;
    /* 0x6C */ s16 d_correct_base_set_angleY;
} SkeletonInfo_R; // size = 0x70

///////////////////////////////////////////////////////////////////////////////
//prototypes

void func_80052584_jp(SkeletonInfo_R* skeletonInfo, BaseSkeleton_R* skeleton, BaseAnimation_R* animation, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, s32 arg8, Vec3s* arg9);

s32 cKF_SkeletonInfo_R_play(SkeletonInfo_R* skeletonInfo); //todo remove

//Lib_SegmentedToVirtual
void* func_8009ADA8_jp(void* ptr);

///////////////////////////////////////////////////////////////////////////////

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80051A80_jp.s")
// cKF_FrameControl_zeroClear
void func_80051A80_jp(FrameControl* frameCtrl)
{
    bzero(frameCtrl, 0x18);
    frameCtrl->mode = cKF_FC_STOP;
    frameCtrl->max = 1.0f;
    frameCtrl->current = 1.0f;
    frameCtrl->speed = 1.0f;
    frameCtrl->end = 1.0f;
    frameCtrl->start = 1.0f;
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80051AC4_jp.s")
//cKF_FrameControl_ct
void func_80051AC4_jp(FrameControl* frameCtrl) {
    func_80051A80_jp(frameCtrl);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80051AE4_jp.s")
//cKF_FrameControl_setFrame
void func_80051AE4_jp(FrameControl *frameCtrl, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6)
{
    frameCtrl->start = arg1;
    frameCtrl->end = (arg2 < 1.0f) ? arg3 : arg2;
    frameCtrl->max = arg3;
    frameCtrl->speed = arg5;
    frameCtrl->current = arg4;
    frameCtrl->mode = arg6;
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80051B44_jp.s")
//cKF_FrameControl_passCheck
s32 func_80051B44_jp(FrameControl* frameCtrl, f32 arg1, f32* arg2)
{
    f32 var_fv1;
    *arg2 = 0.0f;

    if (arg1 == frameCtrl->current)
    {
        return 0;
    }
    var_fv1 = (frameCtrl->start < frameCtrl->end) ? frameCtrl->speed : -frameCtrl->speed;

    if ((var_fv1 >= 0.0f && frameCtrl->current < arg1 && arg1 <= frameCtrl->current + var_fv1) ||
        (var_fv1 < 0.0f && arg1 < frameCtrl->current && frameCtrl->current + var_fv1 <= arg1))
    {
        *arg2 = frameCtrl->current + var_fv1 - arg1;
        return 1;
    }
    return 0;
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80051C18_jp.s")
//cKF_FrameControl_passCheck_now
s32 func_80051C18_jp(FrameControl *frameCtrl, f32 arg1)
{
    s32 var_v1;

    var_v1 = 0;
    if (arg1 != frameCtrl->current)
    {
        f32 var_fv1;
        var_fv1 = (frameCtrl->start < frameCtrl->end) ? frameCtrl->speed : -frameCtrl->speed;

        if (var_fv1 >= 0.0f && arg1 <= frameCtrl->current && frameCtrl->current - var_fv1 < arg1 ||
          var_fv1 < 0.0f && frameCtrl->current <= arg1 && arg1 < frameCtrl->current - var_fv1)
        {
            var_v1 = 1;
        }
    }
    else
    {
        var_v1 = 1;
    }
    return var_v1;
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80051CE8_jp.s")
//cKF_FrameControl_stop_proc
s32 func_80051CE8_jp(FrameControl* frameCtrl)
{
    f32 sp1C;

    if (frameCtrl->current == frameCtrl->end)
    {
        return 1;
    }
    if (func_80051B44_jp(frameCtrl, frameCtrl->end, &sp1C))
    {
        frameCtrl->current = frameCtrl->end;
        return 1;
    }
    if (func_80051B44_jp(frameCtrl, frameCtrl->start, &sp1C))
    {
        frameCtrl->current = frameCtrl->end;
        return 1;
    }
    return 0;
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80051D74_jp.s")
//cKF_FrameControl_repeat_proc
s32 func_80051D74_jp(FrameControl* frameCtrl)
{
    f32 sp1C;

    if (func_80051B44_jp(frameCtrl, frameCtrl->end, &sp1C))
    {
        frameCtrl->current = (f32) (frameCtrl->start + sp1C);
        return 2;
    }
    if (func_80051B44_jp(frameCtrl, frameCtrl->start, &sp1C) != 0)
    {
        frameCtrl->current = frameCtrl->end + sp1C;
        return 2;
    }
    return 0;
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80051DF0_jp.s")
//cKF_FrameControl_play
s32 func_80051DF0_jp(FrameControl *frameCtrl)
{
    f32 var_fv0;
    s32 var_v0;

    if (frameCtrl->mode == cKF_FC_STOP)
    {
        var_v0 = func_80051CE8_jp(frameCtrl);
    }
    else
    {
        var_v0 = func_80051D74_jp(frameCtrl);
    }
    if (var_v0 == 0)
    {
        var_fv0 = (frameCtrl->start < frameCtrl->end) ? frameCtrl->speed : -frameCtrl->speed;
        frameCtrl->current += var_fv0;
    }
    if (frameCtrl->current < 1.0f)
    {
        frameCtrl->current = (frameCtrl->current - 1.0f) + frameCtrl->max;
    }
    else if (frameCtrl->max < frameCtrl->current)
    {
        frameCtrl->current = (frameCtrl->current - frameCtrl->max) + 1.0f;
    }
    return var_v0;
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80051EC4_jp.s")
//cKF_HermitCalc
// hermite interpolation
#define SQ(x) ((x) * (x))
#define CB(x) ((x) * (x) * (x))
f32 func_80051EC4_jp(f32 t, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5)
{
    f32 p = 3.0f * SQ(t) - 2.0f * CB(t);

    return (1.0f - p) * arg2 + p * arg3 + ((CB(t) - 2.0f * SQ(t) + t) * arg4 + (CB(t) - SQ(t)) * arg5) * arg1;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80051F3C_jp.s")
//cKF_KeyCalc
// s16 func_80051F3C_jp(s16 arg0, s16 arg1, Vec3s* arg2, f32 arg3)
// {
//     Vec3s* temp_a3 = &arg2[arg0];
//     Vec3s* temp_v1 = &temp_a3[arg1];
//     f32 temp_fv1;
//     s16 var_v0;
//     s16 var_v1;

//     if (arg3 <= temp_a3->x)
//     {
//         return temp_a3->y;
//     }
//     if (temp_a3[arg1 - 1].x <= arg3)
//     {
//         return temp_a3[arg1 - 1].y;
//     }

//     for (var_v0 = 1, var_v1 = 0; true; var_v0++, var_v1++)
//     {
//         if (arg3 < temp_a3[var_v0].x)
//         {
//             temp_fv1 = temp_a3[var_v0].x - temp_a3[var_v1].x;
//             if (!IS_ZERO(temp_fv1)) {
//                 return nearbyint(func_80183808((arg3 - temp_a3[var_v1].x) / temp_fv1, temp_fv1 * (1.0f / 30),
//                                                temp_a3[var_v1].y, temp_a3[var_v0].y, temp_a3[var_v1].z,
//                                                temp_a3[var_v0].z));
//             }
//             return temp_a3[var_v1].y;
//         }
//     }
// }

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_800520DC_jp.s")
//cKF_SkeletonInfo_subRotInterpolation
void func_800520DC_jp(f32 t, s16* out, s16 rot1, s16 rot2)
{
    u16 urot1 = rot1;
    s32 pad;
    u16 urot2 = rot2;
    f32 f1 = rot1;
    f32 signedDiff = rot2 - f1;
    f32 f2 = urot1;
    f32 unsignedDiff = urot2 - f2;

    if (fabsf(signedDiff) < fabsf(unsignedDiff)) {
        *out = f1 + signedDiff * t;
    } else {
        *out = f2 + unsignedDiff * t;
    }
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_800521A8_jp.s")
//cKF_SkeletonInfo_morphST
void func_800521A8_jp(s16 arg0[3], s16 arg1[3], f32 arg3)
{
    s32 i;

    for (i = 0; i < 3; i++)
    {
        if (*arg0 != *arg1)
        {
            f32 f1 = *arg0;
            f32 f2 = *arg1;
            *arg0 = f1 + (f2 - f1) * arg3;
        }
        arg0++;
        arg1++;
    }
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80052208_jp.s")
//cKF_SkeletonInfo_R_zeroClear
void func_80052208_jp(SkeletonInfo_R* skeletonInfo)
{
    bzero(skeletonInfo, 0x70);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80052228_jp.s")
// cKF_SkeletonInfo_R_ct   
void func_80052228_jp(SkeletonInfo_R* skeletonInfo, BaseSkeleton_R* skeleton, BaseAnimation_R* animation, Vec3s *arg3, Vec3s *arg4)
{
    func_80052208_jp(skeletonInfo);
    func_80051AC4_jp(&skeletonInfo->frameCtrl);
    skeletonInfo->skeleton = func_8009ADA8_jp(skeleton);
    skeletonInfo->animation = func_8009ADA8_jp(animation);
    skeletonInfo->now_joint = arg3;
    skeletonInfo->morph_joint = arg4;
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/cKF_SkeletonInfo_R_dt.s")
//cKF_SkeletonInfo_R_dt
void cKF_SkeletonInfo_R_dt(SkeletonInfo_R* skeletonInfo)
{

}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80052298_jp.s")
// cKF_SkeletonInfo_R_init_standard_stop
void func_80052298_jp(SkeletonInfo_R* skeletonInfo, BaseAnimation_R* animation, Vec3s* arg2)
{
    func_80052584_jp(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f, ((BaseAnimation_R*)func_8009ADA8_jp(animation))->frames, 1.0f, 1.0, 0.0f, cKF_FC_STOP, arg2);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80052310_jp.s")
//cKF_SkeletonInfo_R_init_standard_stop_speedset
void func_80052310_jp(SkeletonInfo_R* skeletonInfo, BaseAnimation_R* animation, Vec3s* arg2, f32 arg3)
{
    func_80052584_jp(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f, ((BaseAnimation_R*)func_8009ADA8_jp(animation))->frames, 1.0f, arg3, 0.0f, cKF_FC_STOP, arg2);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_8005238C_jp.s")
//cKF_SkeletonInfo_R_init_standard_stop_morph
void func_8005238C_jp(SkeletonInfo_R* skeletonInfo, BaseAnimation_R* animation, Vec3s *arg2, f32 arg3)
{
    func_80052584_jp(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f, ((BaseAnimation_R*)func_8009ADA8_jp(animation))->frames, 1.0f, 1.0, arg3, cKF_FC_STOP, arg2);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80052408_jp.s")
//cKF_SkeletonInfo_R_init_standard_repeat
void func_80052408_jp(SkeletonInfo_R *skeletonInfo, BaseAnimation_R* animation, Vec3s* arg2)
{
    func_80052584_jp(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f, ((BaseAnimation_R*)func_8009ADA8_jp(animation))->frames, 1.0f, 1.0, 0.0f, cKF_FC_REPEAT, arg2);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80052484_jp.s")
//cKF_SkeletonInfo_R_init_standard_repeat_speedset
void func_80052484_jp(SkeletonInfo_R *skeletonInfo, BaseAnimation_R* animation, Vec3s* arg2, f32 arg3)
{
    func_80052584_jp(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f, ((BaseAnimation_R*)func_8009ADA8_jp(animation))->frames, 1.0f, arg3, 0.0f, cKF_FC_REPEAT, arg2);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80052504_jp.s")
//cKF_SkeletonInfo_R_init_standard_repeat_morph
void func_80052504_jp(SkeletonInfo_R *skeletonInfo, BaseAnimation_R* animation, Vec3s *arg2, f32 arg3)
{
    func_80052584_jp(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f, ((BaseAnimation_R*)func_8009ADA8_jp(animation))->frames, 1.0f, 1.0, arg3, cKF_FC_REPEAT, arg2);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80052584_jp.s")
//cKF_SkeletonInfo_R_init
void func_80052584_jp(SkeletonInfo_R* skeletonInfo, BaseSkeleton_R* skeleton, BaseAnimation_R* animation, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, s32 arg8, Vec3s* arg9)
{
    skeletonInfo->morphCounter = arg7;
    skeletonInfo->skeleton = func_8009ADA8_jp(skeleton);
    skeletonInfo->animation = func_8009ADA8_jp(animation);
    func_80051AE4_jp(&skeletonInfo->frameCtrl, arg3, arg4, skeletonInfo->animation->frames, arg5, arg6, arg8);
    skeletonInfo->diff_rot_tbl = arg9;
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80052610_jp.s")
//cKF_SkeletonInfo_R_setAnim
void func_80052610_jp(SkeletonInfo_R* skeletonInfo, BaseAnimation_R* animation)
{
    BaseAnimation_R* temp_v0;

    temp_v0 = (BaseAnimation_R*)func_8009ADA8_jp(animation);
    skeletonInfo->animation = temp_v0;
    skeletonInfo->frameCtrl.max = temp_v0->frames;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_8005264C_jp.s")
//cKF_SkeletonInfo_R_morphJoint

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/cKF_SkeletonInfo_R_play.s")
//cKF_SkeletonInfo_R_play
// s32 cKF_SkeletonInfo_R_play(SkeletonInfo_R *skeletonInfo)
// {
//     s32 sp84;
//     u8 *sp7C;
//     void *sp68;
//     void *sp64;
//     void *sp60;
//     Vec3s *var_s1;
//     Vec3s *var_v0;
//     Vec3s *var_v0_2;
//     f32 temp_fs0;
//     f32 temp_fs1;
//     f32 temp_fs3;
//     f32 temp_fv0;
//     f32 temp_fv0_2;
//     f32 temp_fv1;
//     s16 *temp_s0;
//     s16 *temp_s0_2;
//     s16 temp_ft1;
//     s16 temp_t4;
//     s16 temp_t7;
//     // s16 temp_t7_2;
//     s16 temp_t9;
//     s16 var_s6;
//     s32 temp_t3;
//     s32 temp_t5;
//     s32 var_s3;
//     s32 var_s3_2;
//     s32 var_s4;
//     s32 var_s5;
//     s32 var_v1_2;
//     u32 var_s2;
//     u32 var_s2_2;
//     u8 *var_s7;
//     u8 *var_t0;
//     u8 var_v1;

//     var_s4 = 0;
//     var_s5 = 0;
//     var_s6 = 0;
//     if (!(fabsf(skeletonInfo->morphCounter) < RO_FLT_8011611C_jp))
//     {
//         var_s1 = skeletonInfo->morph_joint;
//     }
//     else
//     {
//         var_s1 = skeletonInfo->now_joint;
//     }
//     sp68 = func_8009ADA8_jp(skeletonInfo->animation->const_value_tbl);
//     sp60 = func_8009ADA8_jp(skeletonInfo->animation->key_num);
//     sp64 = func_8009ADA8_jp(skeletonInfo->animation->data_source);
//     var_t0 = func_8009ADA8_jp(skeletonInfo->animation->ConstKeyCheckBitTbl);
//     var_s2 = 0x20;
//     var_s3 = 0;
//     do
//     {
//         if (*var_t0 & var_s2)
//         {
//             temp_s0 = sp60 + (var_s4 * 2);
//             sp7C = var_t0;
//             var_s1->x = func_80051F3C_jp(var_s6, *temp_s0, sp64, skeletonInfo->frameCtrl.current);
//             var_s4 += 1;
//             var_s6 += *temp_s0;
//         }
//         else
//         {
//             temp_t4 = *(sp68 + (var_s5 * 2));
//             var_s5 += 1;
//             var_s1->x = temp_t4;
//         }
//         var_s3 += 1;
//         var_s2 = var_s2 >> 1;
//         var_s1 += 2;
//     } while (var_s3 != 3);
//     sp84 = 0;
//     var_s7 = var_t0;
//     var_v1 = skeletonInfo->skeleton->joint_num;
//     if ((s32) var_v1 > 0)
//     {
//         temp_fs3 = RO_FLT_80116120_jp;
//         temp_fs1 = RO_FLT_80116124_jp;
//         temp_fs0 = RO_FLT_80116128_jp;
//         do
//         {
//             var_s2_2 = 4;
//             var_s3_2 = 0;
// loop_11:
//             if (*var_s7 & var_s2_2)
//             {
//                 temp_s0_2 = sp60 + (var_s4 * 2);
//                 var_s1->x = func_80051F3C_jp(var_s6, *temp_s0_2, sp64, skeletonInfo->frameCtrl.current);
//                 var_s4 += 1;
//                 var_s6 += *temp_s0_2;
//             }
//             else
//             {
//                 temp_t7 = *(sp68 + (var_s5 * 2));
//                 var_s5 += 1;
//                 var_s1->x = temp_t7;
//             }
//             var_s3_2 += 1;
//             var_s2_2 = var_s2_2 >> 1;
//             temp_ft1 = var_s1->x;
//             var_s1 += 2;
//             temp_fv0 = (f32) temp_ft1 * temp_fs0;
//             var_s1->unk-2 = (s16) (s32) ((temp_fv0 - ((f32) (s32) (temp_fv0 * temp_fs1) * 360.0f)) * temp_fs3);
//             if (var_s3_2 != 3)
//             {
//                 goto loop_11;
//             }
//             var_s7 += 1;
//             temp_t5 = sp84 + 1;
//             sp84 = temp_t5;
//             var_v1 = skeletonInfo->skeleton->joint_num;
//         } while (temp_t5 < (s32) var_v1);
//     }
//     if (skeletonInfo->diff_rot_tbl != NULL)
//     {
//         sp84 = 0;
//         if (!(fabsf(skeletonInfo->morphCounter) < RO_FLT_8011612C_jp))
//         {
//             var_v0 = skeletonInfo->morph_joint;
//         }
//         else
//         {
//             var_v0 = skeletonInfo->now_joint;
//         }
//         var_v0_2 = &var_v0[1];
//         if (skeletonInfo->skeleton->joint_num)
//         {
//             for (var_v1_2 = 0; var_v1_2 < skeletonInfo->skeleton->joint_num; var_v1_2++)
//             {
//                 var_v0_2[var_v1_2].x = skeletonInfo->diff_rot_tbl[var_v1_2].x + var_v0_2[var_v1_2].x;
//                 var_v0_2[var_v1_2].y = skeletonInfo->diff_rot_tbl[var_v1_2].y + var_v0_2[var_v1_2].y;
//                 var_v0_2[var_v1_2].z = skeletonInfo->diff_rot_tbl[var_v1_2].y + var_v0_2[var_v1_2].z;
//             }
//         }
//     }
//     temp_fv1 = skeletonInfo->morphCounter;
//     if (fabsf(temp_fv1) < RO_FLT_80116130_jp)
//     {
//         return func_80051DF0_jp(&skeletonInfo->frameCtrl);
//     }
//     if (temp_fv1 > 0.0f)
//     {
//         func_8005264C_jp(skeletonInfo);
//         skeletonInfo->morphCounter -= 1.0f;
//         if (skeletonInfo->morphCounter <= 0.0f)
//         {
//             skeletonInfo->morphCounter = 0.0f;
//         }
//         return 0;
//     }
//     func_8005264C_jp(skeletonInfo);
//     skeletonInfo->morphCounter += 1.0f;
//     if (skeletonInfo->morphCounter >= 0.0f)
//     {
//         skeletonInfo->morphCounter = 0.0f;
//     }
//     return func_80051DF0_jp(&skeletonInfo->frameCtrl);
// }

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80052D20_jp.s")
//cKF_Si3_draw_SV_R_child

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_800530D8_jp.s")
//cKF_Si3_draw_R_SV

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80053170_jp.s")
//cKF_SkeletonInfo_R_init_standard_repeat_speedsetandmorph
void func_80053170_jp(SkeletonInfo_R* skeletonInfo, BaseAnimation_R* animation, Vec3s *arg2, f32 arg3, f32 arg4)
{
    func_80052584_jp(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f, ((BaseAnimation_R*)func_8009ADA8_jp(animation))->frames, 1.0f, arg3, arg4, cKF_FC_REPEAT, arg2);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_800531F0_jp.s")
//cKF_SkeletonInfo_R_init_standard_repeat_setframeandspeedandmorph
void func_800531F0_jp(SkeletonInfo_R* skeletonInfo, BaseAnimation_R* animation, Vec3s *arg2, f32 arg3, f32 arg4, f32 arg5)
{
    func_80052584_jp(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f, ((BaseAnimation_R*)func_8009ADA8_jp(animation))->frames, arg3, arg4, arg5, cKF_FC_REPEAT, arg2);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_8005326C_jp.s")
//cKF_SkeletonInfo_R_init_standard_setframeandspeedandmorphandmode
void func_8005326C_jp(SkeletonInfo_R* skeletonInfo, BaseAnimation_R* animation, Vec3s *arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6)
{
    func_80052584_jp(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f, ((BaseAnimation_R*)func_8009ADA8_jp(animation))->frames, arg3, arg4, arg5, arg6, arg2);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_800532E8_jp.s")
//cKF_SkeletonInfo_R_init_reverse_setspeedandmorphandmode
void func_800532E8_jp(SkeletonInfo_R* skeletonInfo, BaseAnimation_R* animation, Vec3s *arg2, f32 arg3, f32 arg4, s32 arg5)
{
    func_80052584_jp(skeletonInfo, skeletonInfo->skeleton, animation, ((BaseAnimation_R*)func_8009ADA8_jp(animation))->frames, 1.0f, ((BaseAnimation_R*)func_8009ADA8_jp(animation))->frames, arg3, arg4, arg5, arg2);
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80053384_jp.s")
// extern s32* B_801458A0_jp;

// void func_80053384_jp(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8)
// {
//     if (arg3)
//     {
//          *(&B_801458A0_jp + (arg0 * 4)) = arg6 + 0x80000000;
//     }
//     if (arg4)
//     {
//         *(&B_801458A0_jp + (arg1 * 4)) = arg7 + 0x80000000;
//     }
//     if (arg5)
//     {
//         *(&B_801458A0_jp + (arg2 * 4)) = arg8 + 0x80000000;
//     }
// }

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_800533F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80053470_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_8005376C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80053B54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80053EF8_jp.s")

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_800542CC_jp.s")
void func_800542CC_jp(SkeletonInfo_R* skeletonInfo, f32 arg1, f32 arg2, f32 arg3, s16 arg4, s16 arg5, s16 arg6)
{
    skeletonInfo->base_shape_trs.x = arg1;
    skeletonInfo->base_shape_trs.y = arg2;
    skeletonInfo->base_shape_trs.z = arg3;
    skeletonInfo->base_data_angle.x = arg4;
    skeletonInfo->renew_base_data_angle.x = skeletonInfo->base_data_angle.x;
    skeletonInfo->base_data_angle.y = arg5;
    skeletonInfo->renew_base_data_angle.y = skeletonInfo->base_data_angle.y;
    skeletonInfo->base_data_angle.z = arg6;
    skeletonInfo->renew_base_data_angle.z = skeletonInfo->base_data_angle.z;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80054320_jp.s")

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80054474_jp.s")
//cKF_SkeletonInfo_R_AnimationMove_base (i think?)
void func_80054474_jp(SkeletonInfo_R* skeletonInfo)
{
    s32 temp_v0;
    Vec3f* temp_a1;
    Vec3s* temp_v0_2;
    Vec3s* temp_v1;

    temp_v0 = skeletonInfo->move_flag;
    temp_v1 = &skeletonInfo->now_joint[0];
    temp_a1 = &skeletonInfo->base_shape_trs;
    if (temp_v0 & 1)
    {
        temp_v1->x = temp_a1->x;
        temp_v1->z = temp_a1->z;
    }
    if (temp_v0 & 2)
    {
        temp_v1->y = temp_a1->y;
    }
    if (temp_v0 & 4)
    {
        temp_v0_2 = &skeletonInfo->now_joint[1];
        temp_v0_2->x = skeletonInfo->base_data_angle.x;
        temp_v0_2->y = skeletonInfo->base_data_angle.y;
        temp_v0_2->z = skeletonInfo->base_data_angle.z;
    }
    skeletonInfo->move_flag = 0;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80054504_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80054884_jp.s")
