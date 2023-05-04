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

///////////////////////////////////////////////////////////////////////////////
//z64animation.h

typedef struct {
    /* 0x00 */ f32 unk_0;
    /* 0x04 */ f32 unk_4;
    /* 0x08 */ f32 unk_8;
    /* 0x0C */ f32 unk_C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ s32 unk_14;
} FrameControl; // size = 0x18

typedef struct {
    /* 0x0 */ Gfx* dList;
    /* 0x4 */ u8 unk_4;
    /* 0x5 */ u8 flags;
    /* 0x6 */ Vec3s root;
} limb_type1; // size = 0xC

typedef struct {
    /* 0x0 */ Gfx* dList;
    /* 0x4 */ u8 unk_4;
    /* 0x5 */ u8 flags;
    /* 0x6 */ u8 unk_6;         // transform limb draw index
} limb_type2; // size = 0x8

//cKF_je_r
typedef struct {
    /* 0x00 */ char pad[0x14];
    //u8 limb count
    //u8
    //limb struct pointer (array of them, number based on how many limbs?) (also it's a segmented address) (can be type 1 or type 2)
    //s16*
    //s16*
    //?? 2 bytes
    //s16
} placeholderStruct1; // size = 0x14

//cKF_ba_r
//- cKF_ckcb_r
//- cKF_kn
//- cKF_c
//- cKF_ds
typedef struct {
    /* 0x00 */ u16* unk_0;
    /* 0x04 */ s16* unk_4;
    /* 0x08 */ s16* unk_8;
    /* 0x0C */ s16* unk_C;
    /* 0x10 */ char unk_10[0x2];
    /* 0x12 */ s16 unk_12;
} placeholderStruct2; // size = 0x14

typedef struct {
    /* 0x00 */ FrameControl frameCtrl;
    /* 0x18 */ placeholderStruct1* unk_18;
    /* 0x1C */ placeholderStruct2* unk_1C;
    /* 0x20 */ void* unk_20;
    /* 0x24 */ Vec3s* frameData;
    /* 0x28 */ s32* unk_28;
    /* 0x2C */ s16* unk_2C;
} SkeletonInfo; // size = 0x30

///////////////////////////////////////////////////////////////////////////////

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80051A80_jp.s")
// cKF_FrameControl_zeroClear
// void func_80051A80_jp(FrameControl* frameCtrl)
// {
//     if ((frameCtrl && frameCtrl) && frameCtrl)
//     {

//     }
//     bzero(frameCtrl, 0x18);
//     frameCtrl->unk_14 = false;
//     frameCtrl->unk_8 = 1.0f;
//     frameCtrl->unk_10 = 1.0f;
//     frameCtrl->unk_C = 1.0f;
//     frameCtrl->unk_4 = 1.0f;
//     frameCtrl->unk_0 = 1.0f;
// }

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80051AC4_jp.s")
//cKF_FrameControl_ct
void func_80051AC4_jp(FrameControl* frameCtrl) {
    func_80051A80_jp(frameCtrl);
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80051AE4_jp.s")
//cKF_FrameControl_setFrame
// void func_80051AE4_jp(FrameControl* frameCtrl, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6)
// {
//     frameCtrl->unk_0 = arg1;
//     frameCtrl->unk_4 = (arg2 < 1.0f) ? arg3 : arg2;
//     frameCtrl->unk_8 = arg3;
//     frameCtrl->unk_C = arg5;
//     frameCtrl->unk_10 = arg4;
//     frameCtrl->unk_14 = arg6;
// }


// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80051B44_jp.s")
//cKF_FrameControl_passCheck
s32 func_80051B44_jp(FrameControl* frameCtrl, f32 arg1, f32* arg2)
{
    f32 temp_fv0;
    f32 var_fv1;
    //TODO fix this fake match
    if ((frameCtrl && frameCtrl) && frameCtrl)
    {
    }
    *arg2 = 0.0f;
    temp_fv0 = frameCtrl->unk_10;
    if (arg1 == temp_fv0)
    {
        return 0;
    }
    var_fv1 = (frameCtrl->unk_0 < frameCtrl->unk_4) ? frameCtrl->unk_C : -frameCtrl->unk_C;

    if ((var_fv1 >= 0.0f && temp_fv0 < arg1 && arg1 <= temp_fv0 + var_fv1) ||
        (var_fv1 < 0.0f && arg1 < temp_fv0 && temp_fv0 + var_fv1 <= arg1))
    {
        *arg2 = temp_fv0 + var_fv1 - arg1;
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80051C18_jp.s")
//cKF_FrameControl_passCheck_now
// s32 func_80051C18_jp(FrameControl* frameCtrl, f32 arg1)
// {
//     s32 var_v1;
//     f32 var_fv1;

//     var_v1 = 0;
//     if (arg1 = frameCtrl->unk_10)
//     {
//         var_fv1 = (frameCtrl->unk_0 < frameCtrl->unk_4) ? frameCtrl->unk_C : -frameCtrl->unk_C;
//         if ((var_fv1 >= 0.0f && arg1 <= frameCtrl->unk_10 && (frameCtrl->unk_10 - var_fv1) < arg1) ||
//             (var_fv1 < 0.0f && frameCtrl->unk_10 <= arg1 && arg1 < (frameCtrl->unk_10 - var_fv1)))
//         {
//             var_v1 = 1;
//         }
//     }
//     else
//     {
//         var_v1 = 1;
//     }
//     return var_v1;
// }

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80051CE8_jp.s")
//cKF_FrameControl_stop_proc
s32 func_80051CE8_jp(FrameControl* frameCtrl)
{
    //TODO better match
    f32 sp1C;
    if (frameCtrl->unk_4)
    {
    }

    if (frameCtrl->unk_10 == frameCtrl->unk_4)
    {
        return 1;
    }
    if (func_80051B44_jp(frameCtrl, frameCtrl->unk_4, &sp1C))
    {
        frameCtrl->unk_10 = frameCtrl->unk_4;
        return 1;
    }
    if (func_80051B44_jp(frameCtrl, frameCtrl->unk_0, &sp1C))
    {
        frameCtrl->unk_10 = frameCtrl->unk_4;
        return 1;
    }
    return 0;
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80051D74_jp.s")
//cKF_FrameControl_repeat_proc
s32 func_80051D74_jp(FrameControl* frameCtrl)
{
    f32 sp1C;

    if (func_80051B44_jp(frameCtrl, frameCtrl->unk_4, &sp1C))
    {
        frameCtrl->unk_10 = (f32) (frameCtrl->unk_0 + sp1C);
        return 2;
    }
    if (func_80051B44_jp(frameCtrl, frameCtrl->unk_0, &sp1C) != 0)
    {
        frameCtrl->unk_10 = frameCtrl->unk_4 + sp1C;
        return 2;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80051DF0_jp.s")
//cKF_FrameControl_play
// s32 func_80051DF0_jp(FrameControl* frameCtrl)
// {
//     f32 var_fv0;
//     s32 var_v0;

//     if (!frameCtrl->unk_14)
//     {
//         var_v0 = func_80051CE8_jp(frameCtrl);
//     }
//     else
//     {
//         var_v0 = func_80051D74_jp(frameCtrl);
//     }
//     if (!var_v0)
//     {
//         var_fv0 = (frameCtrl->unk_0 < frameCtrl->unk_4) ? frameCtrl->unk_C : -frameCtrl->unk_C;
//         frameCtrl->unk_10 = frameCtrl->unk_10 + var_fv0;
//     }
//     if (frameCtrl->unk_10 < 1.0f)
//     {
//         frameCtrl->unk_10 = frameCtrl->unk_10 - 1.0f + frameCtrl->unk_8;
//         return var_v0;
//     }
//     else if (frameCtrl->unk_8 < frameCtrl->unk_10)
//     {
//         frameCtrl->unk_10 = frameCtrl->unk_10 - frameCtrl->unk_8 + 1.0f;
//     }
//     return var_v0;
// }

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80051EC4_jp.s")
//cKF_HermitCalc
// hermite interpolation
// #define SQ(x) ((x) * (x))
// #define CB(x) ((x) * (x) * (x))
// f32 func_80051EC4_jp(f32 t, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5)
// {
//     f32 p = 3.0f * SQ(t) - 2.0f * CB(t);

//     return (1.0f - p) * arg2 + p * arg3 + ((CB(t) - 2.0f * SQ(t) + t) * arg4 + (CB(t) - SQ(t)) * arg5) * arg1;
// }


#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80051F3C_jp.s")
//cKF_KeyCalc

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_800520DC_jp.s")
//cKF_SkeletonInfo_subRotInterpolation
// void func_800520DC_jp(f32 t, s16* out, s16 rot1, s16 rot2)
// {
//     u16 urot1 = rot1;
//     s32 pad;
//     u16 urot2 = rot2;
//     f32 f1 = rot1;
//     f32 signedDiff = rot2 - f1;
//     f32 f2 = rot1;
//     f32 unsignedDiff = urot2 - f2;

//     if (fabsf(signedDiff) < fabsf(unsignedDiff))
//     {
//         *out = f1 + signedDiff * t;
//     }
//     else
//     {
//         *out = f2 + unsignedDiff * t;
//     }
// }


// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_800521A8_jp.s")
//cKF_SkeletonInfo_morphST
void func_800521A8_jp(s16 skeleton[3], s16 arg1[3], f32 t)
{
    s32 i;

    for (i = 0; i < 3; i++)
    {
        if (*skeleton != *arg1)
        {
            f32 f1 = *skeleton;
            f32 f2 = *arg1;
            *skeleton = f1 + (f2 - f1) * t;
        }
        skeleton++;
        arg1++;
    }
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80052208_jp.s")
//cKF_SkeletonInfo_R_zeroClear
void func_80052208_jp(SkeletonInfo* skeleton)
{
    bzero(skeleton, 0x70);
}


//Lib_SegmentedToVirtual
void* func_8009ADA8_jp(void* ptr);

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80052228_jp.s")
// cKF_SkeletonInfo_R_ct   
// void func_80052228_jp(SkeletonInfo* skeleton, placeholderStruct1* arg1, placeholderStruct2* arg2, Vec3s* frameData, s32* arg4)
// {
//     func_80052208_jp(skeleton);
//     func_80051AC4_jp(&skeleton->frameCtrl);
//     skeleton->unk_18 = (placeholderStruct1*)func_8009ADA8_jp(arg1);
//     skeleton->unk_1C = (placeholderStruct2*)func_8009ADA8_jp(arg2);
//     skeleton->frameData = frameData;
//     skeleton->unk_28 = arg4;
// }


#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/cKF_SkeletonInfo_R_dt.s")
//cKF_SkeletonInfo_R_dt
// void cKF_SkeletonInfo_R_dt(SkeletonInfo* skeleton)
// {

// }

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80052298_jp.s")
//cKF_SkeletonInfo_R_init_standard_stop
// void func_80052584_jp(void *, s32, void *, f32, f32, f32, f32, f32, s32, s32); /* extern */

// void func_80052298_jp(SkeletonInfo* skeleton, placeholderStruct1* arg1, s32 arg2)
// {
//     func_80052584_jp(skeleton, skeleton->unk_18, arg1, 1.0f, ((placeholderStruct2*)func_8009ADA8_jp(arg1))->unk_12, 1.0f, 1.0f, 0.0f, 0, arg2);
// }


#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80052310_jp.s")
//cKF_SkeletonInfo_R_init_standard_stop_speedset

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_8005238C_jp.s")
//cKF_SkeletonInfo_R_init_standard_stop_morph

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80052408_jp.s")
//cKF_SkeletonInfo_R_init_standard_repeat

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80052484_jp.s")
//cKF_SkeletonInfo_R_init_standard_repeat_speedset

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80052504_jp.s")
//cKF_SkeletonInfo_R_init_standard_repeat_morph

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80052584_jp.s")
//cKF_SkeletonInfo_R_init
// void func_80051AE4_jp(void *, s32, s32, f32, f32, f32, s32); /* extern */

// void func_80052584_jp(SkeletonInfo* skeleton, placeholderStruct1* arg1, placeholderStruct2* arg2, s32 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7, s32 arg8, s32 arg9)
// {
//     void *temp_v0;

//     skeleton->unk_20 = arg7;
//     skeleton->unk_18 = func_8009ADA8_jp(arg1);
//     temp_v0 = func_8009ADA8_jp(arg2);
//     skeleton->unk_1C = (placeholderStruct1*)func_8009ADA8_jp(arg2);
//     func_80051AE4_jp(skeleton, arg3, arg4, ((placeholderStruct1*)skeleton->unk_1C)->unk_12, arg5, arg6, arg8);
//     skeleton->unk_2C = arg9;
// }


#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80052610_jp.s")
//cKF_SkeletonInfo_R_setAnim

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_8005264C_jp.s")
//cKF_SkeletonInfo_R_morphJoint

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/cKF_SkeletonInfo_R_play.s")
//cKF_SkeletonInfo_R_play
// s32 func_80051DF0_jp(void *);                       /* extern */
// s16 func_80051F3C_jp(s16, s16, void *, s32);        /* extern */
// ? func_8005264C_jp(void *);                         /* extern */
// extern f32 RO_FLT_8011611C_jp;
// extern f32 RO_FLT_80116120_jp;
// extern f32 RO_FLT_80116124_jp;
// extern f32 RO_FLT_80116128_jp;
// extern f32 RO_FLT_8011612C_jp;
// extern f32 RO_FLT_80116130_jp;

// s32 cKF_SkeletonInfo_R_play(SkeletonInfo* skeleton)
// {
//     s32 sp84;
//     u8 *sp7C;
//     void *sp68;
//     void *sp64;
//     void *sp60;
//     f32 temp_fs0;
//     f32 temp_fs1;
//     f32 temp_fs3;
//     f32 temp_fv0;
//     f32 temp_fv0_2;
//     f32 temp_fv1;
//     s16 *temp_s0;
//     s16 *temp_s0_2;
//     s16 *var_s1;
//     s16 *var_v0;
//     s16 *var_v0_2;
//     s16 temp_ft1;
//     s16 temp_t4;
//     s16 temp_t7;
//     s16 temp_t7_2;
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
//     if (!(fabsf(skeleton->unk_20) < RO_FLT_8011611C_jp))
//     {
//         var_s1 = skeleton->unk_28;
//     }
//     else
//     {
//         var_s1 = skeleton->unk24;
//     }
//     sp68 = func_8009ADA8_jp(skeleton->unk1C->unkC);
//     sp60 = func_8009ADA8_jp(skeleton->unk1C->unk8);
//     sp64 = func_8009ADA8_jp(skeleton->unk1C->unk4);
//     var_t0 = func_8009ADA8_jp(*skeleton->unk1C);
//     var_s2 = 0x20;
//     var_s3 = 0;
//     do
//     {
//         if (*var_t0 & var_s2)
//         {
//             temp_s0 = sp60 + (var_s4 * 2);
//             sp7C = var_t0;
//             *var_s1 = func_80051F3C_jp(var_s6, *temp_s0, sp64, skeleton->unk10);
//             var_s4 += 1;
//             var_s6 += *temp_s0;
//         }
//         else
//         {
//             temp_t4 = *(sp68 + (var_s5 * 2));
//             var_s5 += 1;
//             *var_s1 = temp_t4;
//         }
//         var_s3 += 1;
//         var_s2 = var_s2 >> 1;
//         var_s1 += 2;
//     } while (var_s3 != 3);
//     sp84 = 0;
//     var_s7 = var_t0;
//     var_v1 = *skeleton->unk18;
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
//                 *var_s1 = func_80051F3C_jp(var_s6, *temp_s0_2, sp64, skeleton->unk10);
//                 var_s4 += 1;
//                 var_s6 += *temp_s0_2;
//             }
//             else
//             {
//                 temp_t7 = *(sp68 + (var_s5 * 2));
//                 var_s5 += 1;
//                 *var_s1 = temp_t7;
//             }
//             var_s3_2 += 1;
//             var_s2_2 = var_s2_2 >> 1;
//             temp_ft1 = *var_s1;
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
//             var_v1 = *skeleton->unk18;
//         } while (temp_t5 < (s32) var_v1);
//     }
//     if (skeleton->unk2C != 0)
//     {
//         temp_fv0_2 = fabsf(skeleton->unk20);
//         sp84 = 0;
//         if (!(temp_fv0_2 < RO_FLT_8011612C_jp))
//         {
//             var_v0 = skeleton->unk28;
//         }
//         else
//         {
//             var_v0 = skeleton->unk24;
//         }
//         var_v0_2 = var_v0 + 6;
//         if ((s32) var_v1 > 0)
//         {
//             var_v1_2 = 0;
//             do
//             {
//                 temp_t7_2 = *var_v0_2;
//                 var_v0_2 += 6;
//                 var_v0_2->unk-6 = (s16) (*(skeleton->unk2C + var_v1_2) + temp_t7_2);
//                 var_v0_2->unk-4 = (s16) ((skeleton->unk2C + var_v1_2)->unk2 + var_v0_2->unk-4);
//                 temp_t9 = (skeleton->unk2C + var_v1_2)->unk4;
//                 var_v1_2 += 6;
//                 var_v0_2->unk-2 = (s16) (temp_t9 + var_v0_2->unk-2);
//                 temp_t3 = sp84 + 1;
//                 sp84 = temp_t3;
//             } while (temp_t3 < (s32) *skeleton->unk18);
//         }
//     }
//     temp_fv1 = skeleton->unk20;
//     if (fabsf(temp_fv1) < RO_FLT_80116130_jp)
//     {
//         return func_80051DF0_jp(skeleton);
//     }
//     if (temp_fv1 > 0.0f)
//     {
//         func_8005264C_jp(skeleton);
//         skeleton->unk20 = (f32) (skeleton->unk20 - 1.0f);
//         if (skeleton->unk20 <= 0.0f)
//         {
//             skeleton->unk20 = 0.0f;
//         }
//         return 0;
//     }
//     func_8005264C_jp(skeleton);
//     skeleton->unk20 = (f32) (skeleton->unk20 + 1.0f);
//     if (skeleton->unk20 >= 0.0f)
//     {
//         skeleton->unk20 = 0.0f;
//     }
//     return func_80051DF0_jp(skeleton);
// }

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80052D20_jp.s")


#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_800530D8_jp.s")


#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80053170_jp.s")


#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_800531F0_jp.s")


#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_8005326C_jp.s")


#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_800532E8_jp.s")


#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80053384_jp.s")


#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_800533F4_jp.s")


#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80053470_jp.s")


#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_8005376C_jp.s")


#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80053B54_jp.s")


#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80053EF8_jp.s")


#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_800542CC_jp.s")


#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80054320_jp.s")


#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80054474_jp.s")


#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80054504_jp.s")


#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80054884_jp.s")
