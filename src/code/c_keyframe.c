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
    /* 0x00 */ char pad[0x14];
} placeholderStruct1; // size = 0x14

typedef struct {
    /* 0x00 */ char pad[0x14];
} placeholderStruct2; // size = 0x14

typedef struct {
    /* 0x00 */ FrameControl frameCtrl;
    /* 0x18 */ placeholderStruct1* unk_18;
    /* 0x1C */ placeholderStruct2* unk_1C;
    /* 0x20 */ char pad20[0x4];
    /* 0x24 */ Vec3s* frameData;
    /* 0x28 */ s32* unk_28;
    /* 0x2C */ char unk_0[0x70];
} SkeletonInfo; // size = 0x70

///////////////////////////////////////////////////////////////////////////////

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80051A80_jp.s")
void func_80051A80_jp(FrameControl* frameCtrl);
//cKF_FrameControl_zeroClear
// void func_80051A80_jp(FrameControl* frameCtrl) {
//     bzero(frameCtrl, 0x18);
//     frameCtrl->unk_14 = 0;
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
void func_800521A8_jp(s16 arg0[3], s16 arg1[3], f32 t)
{
    s32 i;

    for (i = 0; i < 3; i++)
    {
        if (*arg0 != *arg1)
        {
            f32 f1 = *arg0;
            f32 f2 = *arg1;
            *arg0 = f1 + (f2 - f1) * t;
        }
        arg0++;
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
//cKF_SkeletonInfo_R_ct   
// void func_80052228_jp(SkeletonInfo* skeleton, placeholderStruct1* arg1, placeholderStruct2* arg2, Vec3s* frameData, s32* arg4)
// {
//     func_80052208_jp(skeleton);
//     func_80051AC4_jp(&skeleton->frameCtrl);
//     skeleton->unk_18 = (placeholderStruct1*)func_8009ADA8_jp(arg1);
//     skeleton->unk_1C = (placeholderStruct2*)func_8009ADA8_jp(arg2);
//     // skeleton->frameData = frameData;
//     // skeleton->unk_28 = arg4;
// }


#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/cKF_SkeletonInfo_R_dt.s")
//cKF_SkeletonInfo_R_dt
// void cKF_SkeletonInfo_R_dt(SkeletonInfo* skeleton)
// {

// }

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80052298_jp.s")
//cKF_SkeletonInfo_R_init_standard_stop

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

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80052610_jp.s")
//cKF_SkeletonInfo_R_setAnim

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_8005264C_jp.s")
//cKF_SkeletonInfo_R_morphJoint

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/cKF_SkeletonInfo_R_play.s")
//cKF_SkeletonInfo_R_play

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
