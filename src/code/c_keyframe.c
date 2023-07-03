#include "global.h"
#include "c_keyframe.h"
#include "z64math.h"
#include "m_lib.h"
#include "gfx.h"
#include "m_play.h"

#define IS_ZERO(f) (fabsf(f) < 0.008f)


float fabsf(float f);
#pragma intrinsic(fabsf)

f64 nearbyint(f64 x);

#define FMOD(x, mod) ((x) - ((s32)((x) * (1.0f / (mod))) * (f32)(mod)))

void *Lib_SegmentedToVirtual(void *ptr);

// SkeletonInfo_R_combine_work* combineStructPtr[3];

void cKF_FrameControl_zeroClear(FrameControl *frameCtrl) {
    bzero(frameCtrl, 0x18);
    frameCtrl->mode = cKF_FC_STOP;
    frameCtrl->max = 1.0f;
    frameCtrl->current = 1.0f;
    frameCtrl->speed = 1.0f;
    frameCtrl->end = 1.0f;
    frameCtrl->start = 1.0f;
}

void cKF_FrameControl_ct(FrameControl *frameCtrl) {
    cKF_FrameControl_zeroClear(frameCtrl);
}

void cKF_FrameControl_setFrame(FrameControl *frameCtrl, f32 start, f32 end, f32 max, f32 current, f32 speed, s32 mode) {
    frameCtrl->start = start;
    frameCtrl->end = (end < 1.0f) ? max : end;
    frameCtrl->max = max;
    frameCtrl->speed = speed;
    frameCtrl->current = current;
    frameCtrl->mode = mode;
}

s32 cKF_FrameControl_passCheck(FrameControl *frameCtrl, f32 arg1, f32 *out) {
    f32 var_fv1;
    *out = 0.0f;

    if (arg1 == frameCtrl->current) {
        return 0;
    }
    var_fv1 = (frameCtrl->start < frameCtrl->end) ? frameCtrl->speed : -frameCtrl->speed;

    if ((var_fv1 >= 0.0f && frameCtrl->current < arg1 && arg1 <= frameCtrl->current + var_fv1) ||
        (var_fv1 < 0.0f && arg1 < frameCtrl->current && frameCtrl->current + var_fv1 <= arg1)) {
        *out = frameCtrl->current + var_fv1 - arg1;
        return 1;
    }
    return 0;
}

s32 cKF_FrameControl_passCheck_now(FrameControl *frameCtrl, f32 arg1) {
    s32 var_v1;

    var_v1 = 0;
    if (arg1 != frameCtrl->current) {
        f32 var_fv1;
        var_fv1 = (frameCtrl->start < frameCtrl->end) ? frameCtrl->speed : -frameCtrl->speed;

        if ((var_fv1 >= 0.0f && arg1 <= frameCtrl->current && frameCtrl->current - var_fv1 < arg1) ||
            (var_fv1 < 0.0f && frameCtrl->current <= arg1 && arg1 < frameCtrl->current - var_fv1)) {
            var_v1 = 1;
        }
    } else {
        var_v1 = 1;
    }
    return var_v1;
}

s32 cKF_FrameControl_stop_proc(FrameControl *frameCtrl) {
    f32 sp1C;

    if (frameCtrl->current == frameCtrl->end) {
        return 1;
    }
    if (cKF_FrameControl_passCheck(frameCtrl, frameCtrl->end, &sp1C)) {
        frameCtrl->current = frameCtrl->end;
        return 1;
    }
    if (cKF_FrameControl_passCheck(frameCtrl, frameCtrl->start, &sp1C)) {
        frameCtrl->current = frameCtrl->end;
        return 1;
    }
    return 0;
}

s32 cKF_FrameControl_repeat_proc(FrameControl *frameCtrl) {
    f32 sp1C;

    if (cKF_FrameControl_passCheck(frameCtrl, frameCtrl->end, &sp1C)) {
        frameCtrl->current = (f32)(frameCtrl->start + sp1C);
        return 2;
    }
    if (cKF_FrameControl_passCheck(frameCtrl, frameCtrl->start, &sp1C) != 0) {
        frameCtrl->current = frameCtrl->end + sp1C;
        return 2;
    }
    return 0;
}

s32 cKF_FrameControl_play(FrameControl *frameCtrl) {
    f32 var_fv0;
    s32 var_v0;

    if (frameCtrl->mode == cKF_FC_STOP) {
        var_v0 = cKF_FrameControl_stop_proc(frameCtrl);
    } else {
        var_v0 = cKF_FrameControl_repeat_proc(frameCtrl);
    }
    if (var_v0 == 0) {
        var_fv0 = (frameCtrl->start < frameCtrl->end) ? frameCtrl->speed : -frameCtrl->speed;
        frameCtrl->current += var_fv0;
    }
    if (frameCtrl->current < 1.0f) {
        frameCtrl->current = (frameCtrl->current - 1.0f) + frameCtrl->max;
    } else if (frameCtrl->max < frameCtrl->current) {
        frameCtrl->current = (frameCtrl->current - frameCtrl->max) + 1.0f;
    }
    return var_v0;
}

// cubic hermite interpolation
f32 cKF_HermitCalc(f32 t, f32 arg1, f32 p0, f32 p1, f32 v0, f32 v1) {
    f32 h3 = 3.0f * SQ(t) - 2.0f * CB(t);
    f32 h2 = -SQ(t) + CB(t);
    f32 h1 = CB(t) - 2.0f * SQ(t) + t;
    f32 h0 = 1.0f - h3;

    return h0 * p0 + h3 * p1 + (h1 * v0 + h2 * v1) * arg1;
}

// startIndex: which keyframe in datasource to start with
// sequenceLength: how many keyframes are in the sequence
// dataSource: Array where all the keyframes are stored
// currentFrame: current frame of the animation
s16 cKF_KeyCalc(s16 startIndex, s16 sequenceLength, Keyframe *dataSource, f32 currentFrame) {
    Keyframe *ds = &dataSource[startIndex];
    f32 frameDelta;
    s32 kf2;
    s32 kf1;

    // if currentFrame is before the starting keyframe
    if (currentFrame <= ds[0].frame) {
        return ds[0].point;
    }
    // if currentFrame is after the ending frame
    if (ds[sequenceLength - 1].frame <= currentFrame) {
        return ds[sequenceLength - 1].point;
    }
    // iterate over all the keyframes to find the correct keyframes to interpolate between
    for (kf2 = 1, kf1 = 0; true; kf1++, kf2++) {
        if (currentFrame < ds[kf2].frame) {
            frameDelta = ds[kf2].frame - ds[kf1].frame;
            if (!IS_ZERO(frameDelta)) {
                return nearbyint(cKF_HermitCalc((currentFrame - ds[kf1].frame) / frameDelta, frameDelta * (1.0f / 30),
                                                ds[kf1].point, ds[kf2].point, ds[kf1].velocity, ds[kf2].velocity));
            } else {
                return ds[kf1].point;
            }
        }
    }
}

void cKF_SkeletonInfo_subRotInterpolation(f32 t, s16 *out, s16 rot1, s16 rot2) {
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

void cKF_SkeletonInfo_morphST(s16 arg0[3], s16 arg1[3], f32 arg3) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (*arg0 != *arg1) {
            f32 f1 = *arg0;
            f32 f2 = *arg1;
            *arg0 = f1 + (f2 - f1) * arg3;
        }
        arg0++;
        arg1++;
    }
}

void cKF_SkeletonInfo_R_zeroClear(SkeletonInfo_R *skeletonInfo) {
    bzero(skeletonInfo, 0x70);
}

void cKF_SkeletonInfo_R_ct(SkeletonInfo_R *skeletonInfo, BaseSkeleton_R *skeleton, BaseAnimation_R *animation,
                           Vec3s *arg3, Vec3s *arg4) {
    cKF_SkeletonInfo_R_zeroClear(skeletonInfo);
    cKF_FrameControl_ct(&skeletonInfo->frameCtrl);
    skeletonInfo->skeleton = Lib_SegmentedToVirtual(skeleton);
    skeletonInfo->animation = Lib_SegmentedToVirtual(animation);
    skeletonInfo->now_joint = arg3;
    skeletonInfo->morph_joint = arg4;
}

void cKF_SkeletonInfo_R_dt(SkeletonInfo_R *skeletonInfo) {
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/cKF_SkeletonInfo_R_init_standard_stop.s")
// cKF_SkeletonInfo_R_init_standard_stop
void cKF_SkeletonInfo_R_init_standard_stop(SkeletonInfo_R *skeletonInfo, BaseAnimation_R *animation, Vec3s *arg2) {
    cKF_SkeletonInfo_R_init(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f,
                            ((BaseAnimation_R *)Lib_SegmentedToVirtual(animation))->frames, 1.0f, 1.0, 0.0f,
                            cKF_FC_STOP, arg2);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/cKF_SkeletonInfo_R_init_standard_stop_speedset.s")
// cKF_SkeletonInfo_R_init_standard_stop_speedset
void cKF_SkeletonInfo_R_init_standard_stop_speedset(SkeletonInfo_R *skeletonInfo, BaseAnimation_R *animation,
                                                    Vec3s *arg2, f32 arg3) {
    cKF_SkeletonInfo_R_init(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f,
                            ((BaseAnimation_R *)Lib_SegmentedToVirtual(animation))->frames, 1.0f, arg3, 0.0f,
                            cKF_FC_STOP, arg2);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/cKF_SkeletonInfo_R_init_standard_stop_morph.s")
// cKF_SkeletonInfo_R_init_standard_stop_morph
void cKF_SkeletonInfo_R_init_standard_stop_morph(SkeletonInfo_R *skeletonInfo, BaseAnimation_R *animation, Vec3s *arg2,
                                                 f32 arg3) {
    cKF_SkeletonInfo_R_init(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f,
                            ((BaseAnimation_R *)Lib_SegmentedToVirtual(animation))->frames, 1.0f, 1.0, arg3,
                            cKF_FC_STOP, arg2);
}

void cKF_SkeletonInfo_R_init_standard_repeat(SkeletonInfo_R *skeletonInfo, BaseAnimation_R *animation, Vec3s *arg2) {
    cKF_SkeletonInfo_R_init(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f,
                            ((BaseAnimation_R *)Lib_SegmentedToVirtual(animation))->frames, 1.0f, 1.0, 0.0f,
                            cKF_FC_REPEAT, arg2);
}

void cKF_SkeletonInfo_R_init_standard_repeat_speedset(SkeletonInfo_R *skeletonInfo, BaseAnimation_R *animation,
                                                      Vec3s *arg2, f32 arg3) {
    cKF_SkeletonInfo_R_init(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f,
                            ((BaseAnimation_R *)Lib_SegmentedToVirtual(animation))->frames, 1.0f, arg3, 0.0f,
                            cKF_FC_REPEAT, arg2);
}

void cKF_SkeletonInfo_R_init_standard_repeat_morph(SkeletonInfo_R *skeletonInfo, BaseAnimation_R *animation,
                                                   Vec3s *arg2, f32 arg3) {
    cKF_SkeletonInfo_R_init(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f,
                            ((BaseAnimation_R *)Lib_SegmentedToVirtual(animation))->frames, 1.0f, 1.0, arg3,
                            cKF_FC_REPEAT, arg2);
}

void cKF_SkeletonInfo_R_init(SkeletonInfo_R *skeletonInfo, BaseSkeleton_R *skeleton, BaseAnimation_R *animation,
                             f32 startFrame, f32 endFrame, f32 frameCurrent, f32 frameSpeed, f32 morphCounter,
                             s32 frameMode, Vec3s *diff_rot_tbl) {
    skeletonInfo->morphCounter = morphCounter;
    skeletonInfo->skeleton = Lib_SegmentedToVirtual(skeleton);
    skeletonInfo->animation = Lib_SegmentedToVirtual(animation);
    cKF_FrameControl_setFrame(&skeletonInfo->frameCtrl, startFrame, endFrame, skeletonInfo->animation->frames,
                              frameCurrent, frameSpeed, frameMode);
    skeletonInfo->diff_rot_tbl = diff_rot_tbl;
}

void cKF_SkeletonInfo_R_setAnim(SkeletonInfo_R *skeletonInfo, BaseAnimation_R *animation) {
    BaseAnimation_R *temp_v0;

    temp_v0 = (BaseAnimation_R *)Lib_SegmentedToVirtual(animation);
    skeletonInfo->animation = temp_v0;
    skeletonInfo->frameCtrl.max = temp_v0->frames;
}

void cKF_SkeletonInfo_R_morphJoint(SkeletonInfo_R *skeletonInfo) {
    Vec3s *now_joint = skeletonInfo->now_joint;
    Vec3s *morph_joint = skeletonInfo->morph_joint;
    f32 step;
    Vec3s next_joint;
    Vec3s next_morph;
    Vec3s temp_vec;
    s32 i;
    f32 new_var;
    f32 new_var2;

    if (!(fabsf(skeletonInfo->morphCounter) < 0.008f)) {
        step = 1.0f / fabsf(skeletonInfo->morphCounter);
    } else {
        step = 0.0f;
    }
    cKF_SkeletonInfo_morphST(&now_joint->x, &morph_joint->x, step);
    now_joint++;
    morph_joint++;
    for (i = 0; i < skeletonInfo->skeleton->joint_num; i++) {
        // TODO next_joint and next_morph should probably be renamed
        // these temps seem to be used because cKF_SkeletonInfo_subRotInterpolation needs the original joint as an
        // output, and 2 other rotations as arguments
        next_joint.x = now_joint->x;
        next_joint.y = now_joint->y;
        next_joint.z = now_joint->z;

        next_morph.x = morph_joint->x;
        next_morph.y = morph_joint->y;
        next_morph.z = morph_joint->z;
        if (next_joint.x != next_morph.x || next_joint.y != next_morph.y || next_joint.z != next_morph.z) {
            temp_vec.x = 0x7FFF + next_joint.x;
            temp_vec.y = 0x7FFF - next_joint.y;
            temp_vec.z = 0x7FFF + next_joint.z;

            new_var = (fabsf(((f32)next_morph.x) - next_joint.x) + fabsf(((f32)next_morph.y) - next_joint.y)) +
                      fabsf(((f32)next_morph.z) - next_joint.z);
            new_var2 = (fabsf(((f32)next_morph.x) - temp_vec.x) + fabsf(((f32)next_morph.y) - temp_vec.y)) +
                       fabsf(((f32)next_morph.z) - temp_vec.z);

            if (new_var < new_var2) {
                cKF_SkeletonInfo_subRotInterpolation(step, &now_joint->x, next_joint.x, next_morph.x);
                cKF_SkeletonInfo_subRotInterpolation(step, &now_joint->y, next_joint.y, next_morph.y);
                cKF_SkeletonInfo_subRotInterpolation(step, &now_joint->z, next_joint.z, next_morph.z);
            } else {
                cKF_SkeletonInfo_subRotInterpolation(step, &now_joint->x, temp_vec.x, next_morph.x);
                cKF_SkeletonInfo_subRotInterpolation(step, &now_joint->y, temp_vec.y, next_morph.y);
                cKF_SkeletonInfo_subRotInterpolation(step, &now_joint->z, temp_vec.z, next_morph.z);
            }
        }
        morph_joint++;
        now_joint++;
    }
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/cKF_SkeletonInfo_R_play.s")
// s32 cKF_SkeletonInfo_R_play(SkeletonInfo_R* skeletonInfo)
// {
//     s32 threeIndex;
//     u32 bitflag_index;
//     s32 jointIndex;
//     s32 kn_index = 0;
//     u8* ckcb_table;
//     s32 const_value_index = 0;
//     s32 key_calc_index = 0;
//     s16* joint1;
//     Vec3s* joint2;
//     s16* const_value_table;
//     Vec3s* data_source;
//     s16* key_num;

//     if (!IS_ZERO(skeletonInfo->morphCounter))
//     {
//         joint1 = &skeletonInfo->morph_joint->x;
//     }
//     else
//     {
//         joint1 = &skeletonInfo->now_joint->x;
//     }

//     const_value_table = func_8009ADA8_jp(skeletonInfo->animation->const_value_tbl);
//     key_num = func_8009ADA8_jp(skeletonInfo->animation->key_num);
//     data_source = func_8009ADA8_jp(skeletonInfo->animation->data_source);
//     ckcb_table = func_8009ADA8_jp(skeletonInfo->animation->ConstKeyCheckBitTbl);

//     // bitflag_index = 0x20;
//     for (bitflag_index = 0x20, threeIndex = 0; threeIndex < 3; threeIndex++)
//     {
//         if (*ckcb_table & bitflag_index)
//         {
//             *joint1 = func_80051F3C_jp(key_calc_index, key_num[kn_index], data_source,
//             skeletonInfo->frameCtrl.current); key_calc_index += key_num[kn_index]; kn_index += 1;
//         }
//         else
//         {
//             *joint1 = const_value_table[const_value_index];
//             const_value_index += 1;
//         }
//         bitflag_index >>= 1;
//         joint1++;
//     }
//     for (jointIndex = 0; jointIndex < skeletonInfo->skeleton->joint_num; jointIndex++)
//     {
//         // bitflag_index = 0x4;
//         for (bitflag_index = 0x4, threeIndex = 0; threeIndex < 3; threeIndex++)
//         {

//             if (ckcb_table[jointIndex] & bitflag_index)
//             {
//                 *joint1 = func_80051F3C_jp(key_calc_index, key_num[kn_index], data_source,
//                 skeletonInfo->frameCtrl.current); key_calc_index += key_num[kn_index]; kn_index += 1;
//             }
//             else
//             {
//                 *joint1 = const_value_table[const_value_index];
//                 const_value_index += 1;
//             }
//             bitflag_index >>= 1;
//             *joint1 = FMOD(*joint1 * 0.1f, 360.0f) * 182.04445f;
//             joint1++;
//         }
//     }
//     if (skeletonInfo->diff_rot_tbl != NULL)
//     {
//         if (!IS_ZERO(skeletonInfo->morphCounter))
//         {
//             joint2 = skeletonInfo->morph_joint;
//         }
//         else
//         {
//             joint2 = skeletonInfo->now_joint;
//         }
//         joint2++;
//         for (jointIndex = 0; jointIndex < skeletonInfo->skeleton->joint_num; jointIndex++)
//         {
//             joint2->x = joint2->x + skeletonInfo->diff_rot_tbl[jointIndex].x;
//             joint2->y = joint2->y + skeletonInfo->diff_rot_tbl[jointIndex].y;
//             joint2->z = joint2->z + skeletonInfo->diff_rot_tbl[jointIndex].z;
//             joint2++;
//         }
//     }
//     if (IS_ZERO(skeletonInfo->morphCounter))
//     {
//         return func_80051DF0_jp(&skeletonInfo->frameCtrl);
//     }
//     if (skeletonInfo->morphCounter > 0.0f)
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

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/cKF_Si3_draw_SV_R_child.s")
// cKF_Si3_draw_SV_R_child
//  void cKF_Si3_draw_SV_R_child(PlayState *play, SkeletonInfo_R *skeletonInfo, s32 *joint_num, cKF_draw_callback
//  prerender_callback, cKF_draw_callback postrender_callback, void *arg, Mtx **mtxpp)
//  {
//      s32 sp88;
//      Gfx *sp84;
//      u8 sp7F;
//      // s16 sp7C;
//      // s16 sp7A;
//      Vec3s rot;
//      // f32 sp70;
//      // f32 sp6C;
//      Vec3f pos;
//      GraphicsContext *sp58;
//      Gfx *temp_s0;
//      GraphicsContext *temp_t0;
//      Vec3f *temp_v0;
//      Vec3s *temp_a0;
//      s32 temp_v1;
//      s32 temp_v1_2;
//      s32 var_v0;
//      JointElem_R *temp_s2;
//      void *temp_v0_2;
//      void *temp_v0_3;
//      void *temp_v0_4;
//      void *temp_v1_3;
//      void *temp_v1_4;

//     if (1) { } if (1) { } if (1) { } if (1) { }
//     temp_s2 = Lib_SegmentedToVirtual(skeletonInfo->skeleton->joint_tbl);
//     temp_s2 += *joint_num;
//     temp_a0 = &skeletonInfo->now_joint[*joint_num];
//     if (*joint_num != 0)
//     {
//         pos.x = temp_s2->trs.x;
//         pos.y = temp_s2->trs.y;
//         pos.z = temp_s2->trs.z;
//     }
//     else
//     {
//         temp_v1_2 = skeletonInfo->move_flag;
//         temp_v0 = &skeletonInfo->base_shape_trs;
//         if (temp_v1_2 & 1)
//         {
//             pos.x = temp_v0->x;
//             pos.z = temp_v0->z;
//         }
//         else
//         {
//             pos.x = temp_a0->x;
//             pos.z = temp_a0->z;
//         }
//         if (temp_v1_2 & 2)
//         {
//             pos.y = temp_v0->y;
//         }
//         else
//         {
//             pos.y = temp_a0->y;
//         }
//     }
//     rot = temp_a0[1];
//     if ((*joint_num == 0) && (skeletonInfo->move_flag & 4))
//     {
//         rot.x = skeletonInfo->base_data_angle.x;
//         rot.y = skeletonInfo->renew_base_data_angle.y;
//         rot.z = skeletonInfo->renew_base_data_angle.z;
//     }
//     // temp_t0 = play->state.gfxCtx;
//     // sp58 = temp_t0;
//     OPEN_DISPS(play->state.gfxCtx);
//     Matrix_push();
//     temp_s0 = temp_s2->shape;
//     sp84 = temp_s0;
//     sp7F = temp_s2->work_flag;

//     if ((prerender_callback == NULL) ||
//         (prerender_callback != NULL && prerender_callback(play, skeletonInfo, *joint_num, &sp84, &sp7F, arg, &rot,
//         &pos) != NULL))
//     {
//         Matrix_softcv3_mult(&pos, &rot);
//         if (sp84 != NULL)
//         {
//             _Matrix_to_Mtx(*mtxpp);
//             if (sp7F & 1)
//             {
//                 gSPMatrix(POLY_XLU_DISP++, *mtxpp, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
//                 gSPDisplayList(POLY_XLU_DISP++, sp84);
//             }
//             else
//             {
//                 gSPMatrix(POLY_OPA_DISP++, *mtxpp, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
//                 gSPDisplayList(POLY_OPA_DISP++, sp84);
//             }
//             (*mtxpp)++;
//         }
//         else if (temp_s0 != NULL)
//         {
//             _Matrix_to_Mtx(*mtxpp);
//             if(1){}
//             gSPMatrix(POLY_OPA_DISP++, *mtxpp, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
//             (*mtxpp)++;
//         }
//     }
//     if (postrender_callback != NULL)
//     {
//         postrender_callback(play, skeletonInfo, *joint_num, &sp84, &sp7F, arg, &rot, &pos);
//     }
//     (*joint_num)++;
//     for (var_v0 = 0; var_v0 < temp_s2->child; var_v0++)
//     {
//         cKF_Si3_draw_SV_R_child(play, skeletonInfo, joint_num, prerender_callback, postrender_callback, arg, mtxpp);
//     }
//     Matrix_pull();
//     CLOSE_DISPS(play->state.gfx);
// }

void cKF_Si3_draw_R_SV(PlayState *play, SkeletonInfo_R *skeletonInfo, Mtx *mtxp, cKF_draw_callback prerender_callback,
                       cKF_draw_callback postrender_callback, void *arg) {
    s32 joint_num;
    // Mtx* mtx_p = mtxp;

    if (mtxp != NULL) {
        OPEN_DISPS(play->state.gfxCtx);
        do {
            gSPSegment(POLY_OPA_DISP++, 0x0D, mtxp);
            do {
                gSPSegment(POLY_XLU_DISP++, 0x0D, mtxp);
            } while (0);
        } while (0);
        // gSPSegment(POLY_OPA_DISP++, 0x0D, mtxp);
        // gSPSegment(POLY_XLU_DISP++, 0x0D, mtxp);
        CLOSE_DISPS(play->state.gfxCtx);
        joint_num = 0;
        cKF_Si3_draw_SV_R_child(play, skeletonInfo, &joint_num, prerender_callback, postrender_callback, arg, &mtxp);
    }
}

void cKF_SkeletonInfo_R_init_standard_repeat_speedsetandmorph(SkeletonInfo_R *skeletonInfo, BaseAnimation_R *animation,
                                                              Vec3s *arg2, f32 arg3, f32 arg4) {
    cKF_SkeletonInfo_R_init(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f,
                            ((BaseAnimation_R *)Lib_SegmentedToVirtual(animation))->frames, 1.0f, arg3, arg4,
                            cKF_FC_REPEAT, arg2);
}

void cKF_SkeletonInfo_R_init_standard_repeat_setframeandspeedandmorph(SkeletonInfo_R *skeletonInfo,
                                                                      BaseAnimation_R *animation, Vec3s *arg2, f32 arg3,
                                                                      f32 arg4, f32 arg5) {
    cKF_SkeletonInfo_R_init(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f,
                            ((BaseAnimation_R *)Lib_SegmentedToVirtual(animation))->frames, arg3, arg4, arg5,
                            cKF_FC_REPEAT, arg2);
}

void cKF_SkeletonInfo_R_init_standard_setframeandspeedandmorphandmode(SkeletonInfo_R *skeletonInfo,
                                                                      BaseAnimation_R *animation, Vec3s *arg2, f32 arg3,
                                                                      f32 arg4, f32 arg5, s32 arg6) {
    cKF_SkeletonInfo_R_init(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f,
                            ((BaseAnimation_R *)Lib_SegmentedToVirtual(animation))->frames, arg3, arg4, arg5, arg6,
                            arg2);
}

void cKF_SkeletonInfo_R_init_reverse_setspeedandmorphandmode(SkeletonInfo_R *skeletonInfo, BaseAnimation_R *animation,
                                                             Vec3s *arg2, f32 arg3, f32 arg4, s32 arg5) {
    cKF_SkeletonInfo_R_init(skeletonInfo, skeletonInfo->skeleton, animation,
                            ((BaseAnimation_R *)Lib_SegmentedToVirtual(animation))->frames, 1.0f,
                            ((BaseAnimation_R *)Lib_SegmentedToVirtual(animation))->frames, arg3, arg4, arg5, arg2);
}

extern SkeletonInfo_R_combine_work *B_801458A0_jp;

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80053384_jp.s")
void func_80053384_jp(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    if (arg3 != 0) {
        *(&B_801458A0_jp + arg0) = (SkeletonInfo_R_combine_work *)(arg6 + 0x80000000);
    }
    if (arg4 != 0) {
        *(&B_801458A0_jp + arg1) = (SkeletonInfo_R_combine_work *)(arg7 + 0x80000000);
    }
    if (arg5 != 0) {
        *(&B_801458A0_jp + arg2) = (SkeletonInfo_R_combine_work *)(arg8 + 0x80000000);
    }
}

void cKF_SkeletonInfo_R_combine_work_set(SkeletonInfo_R_combine_work *combine, SkeletonInfo_R *skeleton) {
    combine->skeletonInfo = skeleton;
    combine->anm_const_val_tbl = Lib_SegmentedToVirtual(skeleton->animation->const_value_tbl);
    combine->anm_key_num = Lib_SegmentedToVirtual(skeleton->animation->key_num);
    combine->anm_data_src = Lib_SegmentedToVirtual(skeleton->animation->data_source);
    combine->anm_check_bit_tbl = Lib_SegmentedToVirtual(skeleton->animation->ConstKeyCheckBitTbl);
    combine->anm_key_num_idx = 0;
    combine->anm_const_val_tbl_idx = 0;
    combine->anm_data_src_idx = 0;
}

void cKF_SkeletonInfo_R_combine_translation(s16 **joint, u32 *flag, SkeletonInfo_R_combine_work *combine, s8 *arg3) {
    SkeletonInfo_R_combine_work *temp_s1;
    SkeletonInfo_R_combine_work *temp_s2;
    s32 i;

    temp_s1 = &combine[1];
    temp_s2 = &combine[2];
    for (i = 0; i < 3; i++) {
        switch (*arg3) {
            case 0:
                if (*combine[0].anm_check_bit_tbl & *flag) {
                    **joint = cKF_KeyCalc(combine[0].anm_data_src_idx, combine[0].anm_key_num[combine->anm_key_num_idx],
                                          combine[0].anm_data_src, combine[0].skeletonInfo->frameCtrl.current);
                } else {
                    **joint = combine->anm_const_val_tbl[combine->anm_const_val_tbl_idx];
                }
                break;
            case 1:
                if (*temp_s1->anm_check_bit_tbl & *flag) {
                    **joint = cKF_KeyCalc(temp_s1->anm_data_src_idx, temp_s1->anm_key_num[temp_s1->anm_key_num_idx],
                                          temp_s1->anm_data_src, temp_s1->skeletonInfo->frameCtrl.current);
                } else {
                    **joint = temp_s1->anm_const_val_tbl[temp_s1->anm_const_val_tbl_idx];
                }
                break;
            case 2:
                if (*temp_s2->anm_check_bit_tbl & *flag) {
                    **joint = cKF_KeyCalc(temp_s2->anm_data_src_idx, temp_s2->anm_key_num[temp_s2->anm_key_num_idx],
                                          temp_s2->anm_data_src, temp_s2->skeletonInfo->frameCtrl.current);
                } else {
                    **joint = temp_s2->anm_const_val_tbl[temp_s2->anm_const_val_tbl_idx];
                }
                break;
        }
        if (*combine[0].anm_check_bit_tbl & *flag) {
            combine->anm_data_src_idx += combine[0].anm_key_num[combine->anm_key_num_idx++];
        } else {
            combine->anm_const_val_tbl_idx += 1;
        }
        if (*temp_s1->anm_check_bit_tbl & *flag) {
            temp_s1->anm_data_src_idx += temp_s1->anm_key_num[temp_s1->anm_key_num_idx++];
        } else {
            temp_s1->anm_const_val_tbl_idx++;
        }
        if (*temp_s2->anm_check_bit_tbl & *flag) {
            temp_s2->anm_data_src_idx += temp_s2->anm_key_num[temp_s2->anm_key_num_idx++];
        } else {
            temp_s2->anm_const_val_tbl_idx += 1;
        }
        *flag >>= 1;
        *joint += 1;
    }
}

void cKF_SkeletonInfo_R_combine_rotation(s16 **joint, u32 *flag, SkeletonInfo_R_combine_work *combine, s8 *arg3) {
    SkeletonInfo_R_combine_work *sp64;
    SkeletonInfo_R_combine_work *temp_s0;
    SkeletonInfo_R_combine_work *temp_s1;
    s32 i;
    s32 j;
    s16 *temp_v0_5;
    f32 temp_fv0;

    sp64 = combine;
    temp_s0 = &combine[1];
    temp_s1 = &combine[2];
    for (i = 0; i < sp64->skeletonInfo->skeleton->joint_num; i++) {
        *flag = 4;
        for (j = 0; j < 3; j++) {
            switch (arg3[i + 1]) {
                case 0:
                    if (combine->anm_check_bit_tbl[i] & *flag) {
                        **joint =
                            cKF_KeyCalc(combine[0].anm_data_src_idx, combine->anm_key_num[combine->anm_key_num_idx],
                                        combine->anm_data_src, combine->skeletonInfo->frameCtrl.current);
                    } else {
                        **joint = combine->anm_const_val_tbl[combine->anm_const_val_tbl_idx];
                    }
                    break;
                case 1:
                    if (temp_s0->anm_check_bit_tbl[i] & *flag) {
                        **joint = cKF_KeyCalc(temp_s0->anm_data_src_idx, temp_s0->anm_key_num[temp_s0->anm_key_num_idx],
                                              temp_s0->anm_data_src, temp_s0->skeletonInfo->frameCtrl.current);
                    } else {
                        **joint = temp_s0->anm_const_val_tbl[temp_s0->anm_const_val_tbl_idx];
                    }
                    break;
                case 2:
                    if (temp_s1->anm_check_bit_tbl[i] & *flag) {
                        **joint = cKF_KeyCalc(temp_s1->anm_data_src_idx, temp_s1->anm_key_num[temp_s1->anm_key_num_idx],
                                              temp_s1->anm_data_src, temp_s1->skeletonInfo->frameCtrl.current);
                    } else {
                        **joint = temp_s1->anm_const_val_tbl[temp_s1->anm_const_val_tbl_idx];
                    }
                    break;
            }
            if (combine->anm_check_bit_tbl[i] & *flag) {
                combine->anm_data_src_idx += combine->anm_key_num[combine->anm_key_num_idx++];
            } else {
                combine->anm_const_val_tbl_idx++;
            }
            if (temp_s0->anm_check_bit_tbl[i] & *flag) {
                temp_s0->anm_data_src_idx += temp_s0->anm_key_num[temp_s0->anm_key_num_idx++];
            } else {
                temp_s0->anm_const_val_tbl_idx++;
            }
            if (temp_s1->anm_check_bit_tbl[i] & *flag) {
                temp_s1->anm_data_src_idx += temp_s1->anm_key_num[temp_s1->anm_key_num_idx++];
            } else {
                temp_s1->anm_const_val_tbl_idx++;
            }
            temp_v0_5 = *joint;
            temp_fv0 = *temp_v0_5 * 0.1f;
            *temp_v0_5 = (s16)(s32)((temp_fv0 - ((f32)(s32)(temp_fv0 * 0.0027777778f) * 360.0f)) * 182.04445f);
            *flag >>= 1;
            *joint += 1;
        }
    }
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/cKF_SkeletonInfo_R_combine_play.s")
// s32 cKF_SkeletonInfo_R_combine_play(SkeletonInfo_R* arg0, SkeletonInfo_R* arg1, s32 arg2, s32 arg3, s32 arg4, s32
// arg5, s8* arg6)
// {
//     u32 spB0; //bitflag
//     s16 *spAC;
//     SkeletonInfo_R_combine_work sp8C;
//     SkeletonInfo_R_combine_work sp6C;
//     SkeletonInfo_R_combine_work sp4C;
//     SkeletonInfo_R_combine_work *sp44;
//     SkeletonInfo_R_combine_work *sp40;
//     SkeletonInfo_R_combine_work **temp_v0;
//     SkeletonInfo_R_combine_work **temp_v0_2;
//     SkeletonInfo_R_combine_work *temp_t6;
//     Vec3s *var_v0;
//     Vec3s *var_v0_2;
//     // f32 temp_fv1;
//     s16 temp_t4;
//     s16 temp_t5;
//     s16 temp_t8;
//     s32 var_a0;
//     s32 var_s0;
//     s32 var_v1;

//     sp44 = 0;
//     sp40 = 0;
//     if ((arg0 == NULL) || (arg1 == NULL) || (arg2 < 0) || (arg2 >= 0x10) || (arg3 < 0) || (arg3 >= 0x10) || (arg6 ==
//     NULL)) {
//         return 0;
//     }
//     if (!IS_ZERO(arg0->morphCounter)) {
//         spAC = arg0->morph_joint->x;
//     } else {
//         spAC = arg0->now_joint->x;
//     }
//     if (arg4 != 0)
//     {
//         temp_v0 = &(&B_801458A0_jp)[arg2];
//         temp_t6 = *temp_v0;
//         *temp_v0 = arg4 + 0x80000000;
//         sp44 = temp_t6 + 0x80000000;
//         //cKF_SkeletonInfo_R_combine_work_set
//         cKF_SkeletonInfo_R_combine_work_set(&sp4C, arg0);
//     }
//     if (arg5 != 0)
//     {
//         temp_v0_2 = &(&B_801458A0_jp)[arg3];
//         sp40 = *temp_v0_2 + 0x80000000;
//         *temp_v0_2 = arg5 + 0x80000000;
//         //cKF_SkeletonInfo_R_combine_work_set
//         cKF_SkeletonInfo_R_combine_work_set(&sp6C, arg1);
//         cKF_SkeletonInfo_R_combine_work_set(&sp8C, arg1);
//     }
//     spB0 = 0x20;
//     //cKF_SkeletonInfo_R_combine_translation
//     cKF_SkeletonInfo_R_combine_translation(&spAC, &spB0, &sp4C, arg6);
//     //cKF_SkeletonInfo_R_combine_rotation
//     cKF_SkeletonInfo_R_combine_rotation(&spAC, &spB0, &sp4C, arg6);
//     if (arg0->diff_rot_tbl != NULL)
//     {
//         if (!IS_ZERO(arg0->morphCounter))
//         {
//             var_v0 = arg0->morph_joint;
//         }
//         else
//         {
//             var_v0 = arg0->now_joint;
//         }

//         var_v0++;

//         for (var_v1 = 0; var_v1 < arg0->skeleton->joint_num; var_v1++)
//         {
//             var_v0->x = var_v0->x + arg0->diff_rot_tbl[var_v1].x;
//             var_v0->y = var_v0->y + arg0->diff_rot_tbl[var_v1].y;
//             var_v0->z = var_v0->z + arg0->diff_rot_tbl[var_v1].z;
//             var_v0++;
//         }
//     }
//     // temp_fv1 = arg0->morphCounter;
//     if (IS_ZERO(arg0->morphCounter))
//     {
//         cKF_FrameControl_play(&arg1->frameCtrl);
//         var_s0 = cKF_FrameControl_play(&arg0->frameCtrl);
//         func_80053384_jp(arg2, arg3, 0, arg4, arg5, 0, sp44, sp40, 0);
//         return var_s0;
//     }
//     if (arg0->morphCounter > 0.0f)
//     {
//         cKF_SkeletonInfo_R_morphJoint(arg0);
//         arg0->morphCounter -= 1.0f;
//         if (arg0->morphCounter <= 0.0f)
//         {
//             arg0->morphCounter = 0.0f;
//         }
//         func_80053384_jp(arg2, arg3, 0, arg4, arg5, 0, sp44, sp40, 0);
//         return 0;
//     }
//     cKF_SkeletonInfo_R_morphJoint(arg0);
//     arg0->morphCounter += 1.0f;
//     if (arg0->morphCounter >= 0.0f)
//     {
//         arg0->morphCounter = 0.0f;
//     }
//     cKF_FrameControl_play(&arg1->frameCtrl);
//     var_s0 = cKF_FrameControl_play(&arg0->frameCtrl);
//     func_80053384_jp(arg2, arg3, 0, arg4, arg5, 0, sp44, sp40, 0);
//     return var_s0;
// }

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/cKF_SkeletonInfo_R_T_combine_play.s")

void cKF_SkeletonInfo_R_Animation_Set_base_shape_trs(SkeletonInfo_R *skeletonInfo, f32 arg1, f32 arg2, f32 arg3,
                                                     s16 arg4, s16 arg5, s16 arg6) {
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

extern Vec3f D_8010F4A0_jp; // todo: import this

void cKF_SkeletonInfo_R_AnimationMove_ct_base(Vec3f *arg0, Vec3f *arg1, s16 arg2, s16 arg3, f32 arg4,
                                              SkeletonInfo_R *skeletonInfo, s32 arg6) {
    s32 var_v0;

    skeletonInfo->move_flag = arg6;
    skeletonInfo->correct_counter = (arg4 >= 0.0f) ? arg4 : -arg4;
    skeletonInfo->idle_world_pos = D_8010F4A0_jp;
    skeletonInfo->d_correct_base_world_pos = D_8010F4A0_jp;

    if (arg0 != NULL) {
        if (arg1 == NULL) {
            arg1 = arg0;
        }
        if (arg6 & 1) {
            skeletonInfo->idle_world_pos.x = arg1->x;
            skeletonInfo->idle_world_pos.z = arg1->z;
            skeletonInfo->d_correct_base_world_pos.x = arg0->x - arg1->x;
            skeletonInfo->d_correct_base_world_pos.z = arg0->z - arg1->z;
        }
        if (arg6 & 2) {
            skeletonInfo->idle_world_pos.y = arg1->y;
            skeletonInfo->d_correct_base_world_pos.y = (f32)(arg0->y - arg1->y);
        }
    }
    skeletonInfo->idle_set_angleY = arg3;
    skeletonInfo->d_correct_base_set_angleY = 0;
    if (arg6 & 4) {
        var_v0 = arg2 - arg3;
        if (var_v0 >= 0x8001) {
            var_v0 = -(0x10000 - var_v0);
        } else if (var_v0 < -0x8000) {
            var_v0 = var_v0 + 0x10000;
        }
        skeletonInfo->d_correct_base_set_angleY = var_v0;
    }
}

void cKF_SkeletonInfo_R_AnimationMove_dt(SkeletonInfo_R *skeletonInfo) {
    s32 temp_v0;
    Vec3f *temp_a1;
    Vec3s *temp_v0_2;
    Vec3s *temp_v1;

    temp_v0 = skeletonInfo->move_flag;
    temp_v1 = &skeletonInfo->now_joint[0];
    temp_a1 = &skeletonInfo->base_shape_trs;
    if (temp_v0 & 1) {
        temp_v1->x = temp_a1->x;
        temp_v1->z = temp_a1->z;
    }
    if (temp_v0 & 2) {
        temp_v1->y = temp_a1->y;
    }
    if (temp_v0 & 4) {
        temp_v0_2 = &skeletonInfo->now_joint[1];
        temp_v0_2->x = skeletonInfo->base_data_angle.x;
        temp_v0_2->y = skeletonInfo->base_data_angle.y;
        temp_v0_2->z = skeletonInfo->base_data_angle.z;
    }
    skeletonInfo->move_flag = 0;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/cKF_SkeletonInfo_R_AnimationMove_base.s")
// void cKF_SkeletonInfo_R_AnimationMove_base(Vec3f *arg0, s16 *arg1, Vec3f *arg2, s16 arg3, SkeletonInfo_R
// *skeletonInfo)
// {
//     // s32 spAC;
//     f32 spA8;
//     s32 temp_v1;
//     f32 temp_fv1;
//     f32 var_ft4;
//     // s32 pad;
//     s32 sp8C;
//     s32 sp88;
//     s32 sp80;
//     Vec3s *sp78;
//     // s16 sp76;
//     f32 sp70;
//     f32 sp6C;
//     f32 sp68;
//     f32 sp58;
//     f32 sp54;
//     f32 sp50;
//     Vec3s *sp28;
//     // s32 sp24;
//     // MtxF *temp_v0_3;
//     // Vec3s *temp_a1;
//     // Vec3s *temp_v0_2;
//     // f32 temp_fa0;
//     // f32 temp_fa1;
//     // f32 temp_ft0;
//     f32 temp_fv0;
//     f32 temp_fv0_2;
//     // f32 temp_fv1_2;

//     s16 temp_v0;
//     s16 var_a0;
//     s16 temp5;
//     s32 temp_a0;

//     temp_v1 = skeletonInfo->move_flag;
//     spA8 = skeletonInfo->correct_counter;
//     temp_fv1 = spA8 + 1.0f;
//     // temp_a0 = temp_v1 & 4;
//     if (temp_fv1 > 1.0f)
//     {
//         var_ft4 = 1.0f / temp_fv1;
//     }
//     else
//     {
//         var_ft4 = 0.0f;
//     }

//     if (temp_v1 & 4)
//     {
//         f32 temp6 = skeletonInfo->d_correct_base_set_angleY;
//         if (temp_fv1 > 1.0f)
//         {
//             temp6 *= var_ft4;
//             skeletonInfo->d_correct_base_set_angleY -= (s32)temp6;
//         }
//         else
//         {
//             skeletonInfo->d_correct_base_set_angleY = 0;
//         }
//     }
//     if (temp_fv1 > 1.0f)
//     {
//         if (temp_v1 & 1)
//         {
//             f32 temp8;
//             f32 temp9;

//             temp8 = skeletonInfo->d_correct_base_world_pos.x;
//             temp8 *= var_ft4;

//             temp9 = skeletonInfo->d_correct_base_world_pos.z;
//             temp9 *= var_ft4;

//             skeletonInfo->d_correct_base_world_pos.x -= temp8;
//             skeletonInfo->d_correct_base_world_pos.z -= temp9;
//         }
//         if (temp_v1 & 2)
//         {
//             f32 temp7;
//             temp7 = skeletonInfo->d_correct_base_world_pos.y;
//             temp7 *= var_ft4;

//             skeletonInfo->d_correct_base_world_pos.y -= temp7;
//         }
//     }
//     else
//     {
//         skeletonInfo->d_correct_base_world_pos.x = 0.0f;
//         skeletonInfo->d_correct_base_world_pos.y = 0.0f;
//         skeletonInfo->d_correct_base_world_pos.z = 0.0f;
//     }
//     if ((arg1 != NULL) && (temp_v1 & 4))
//     {
//         sp8C = skeletonInfo->idle_set_angleY;
//         sp88 = skeletonInfo->d_correct_base_set_angleY;
//         sp80 = skeletonInfo->base_data_angle.x;
//         sp28 = &skeletonInfo->renew_base_data_angle;
//         Matrix_push();
//         Matrix_rotateXYZ(skeletonInfo->now_joint[1].x, skeletonInfo->now_joint[1].y, skeletonInfo->now_joint[1].z,
//         0); Matrix_to_rotate2_new(get_Matrix_now(), sp28, 0); Matrix_pull(); *arg1 = sp8C + sp88 + (sp28->x - sp80);
//     }
//     var_a0 = 0;
//     if (arg0 != NULL)
//     {
//         // sp24 = temp_v1 & 2;
//         sp78 = skeletonInfo->now_joint;
//         if (arg1 != NULL)
//         {
//             var_a0 = *arg1 - arg3;
//         }
//         if (temp_v1 & 1)
//         {
//             f32 temp_x;
//             f32 temp_z;
//             f32 temp2;
//             f32 temp1;

//             sp70 = skeletonInfo->base_shape_trs.x;
//             sp6C = skeletonInfo->base_shape_trs.z;
//             // sp76 = var_a0;
//             sp68 = sin_s(var_a0);
//             temp_fv0 = cos_s(var_a0);

//             temp1 = (sp70 * temp_fv0) + (sp6C * sp68);
//             sp58 = arg2->x * (sp78->x - temp1);
//             temp1 = (-sp70 * sp68) + (sp6C * temp_fv0);
//             sp54 = arg2->z * (sp78->z - temp1);

//             sp50 = sin_s(arg3);
//             temp_fv0_2 = cos_s(arg3);

//             // arg0->x = skeletonInfo->idle_world_pos.x + skeletonInfo->d_correct_base_world_pos.x + ((sp58 *
//             temp_fv0_2) + (sp54 * sp50));
//             // arg0->z = skeletonInfo->idle_world_pos.z + skeletonInfo->d_correct_base_world_pos.z + ((-sp58 * sp50)
//             + (sp54 * temp_fv0_2)); temp_x = skeletonInfo->d_correct_base_world_pos.x; temp_z =
//             skeletonInfo->d_correct_base_world_pos.z; temp2 = (sp58 * temp_fv0_2) + (sp54 * sp50); arg0->x = temp2 +
//             (skeletonInfo->idle_world_pos.x + temp_x); temp2 = (-sp58 * sp50) + (sp54 * temp_fv0_2); arg0->z = temp2
//             + (skeletonInfo->idle_world_pos.z + temp_z);
//         }
//         if (temp_v1 & 2)
//         {
//             f32 temp3 = sp78->y - skeletonInfo->base_shape_trs.y;
//             arg0->y = skeletonInfo->idle_world_pos.y + skeletonInfo->d_correct_base_world_pos.y + (arg2->y * temp3);
//         }
//     }
//     // temp_ft0 = spA8 - 1.0f;
//     spA8 -= 1.0f;
//     if (spA8 < 0.0f)
//     {
//         spA8 = 0.0f;
//     }
//     skeletonInfo->correct_counter = spA8;
// }

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/cKF_SkeletonInfo_R_AnimationMove_CulcTransToWorld.s")
void cKF_SkeletonInfo_R_AnimationMove_CulcTransToWorld(Vec3f *arg0, Vec3f *arg1, f32 arg2, f32 arg3, f32 arg4, s16 arg5,
                                                       Vec3f *arg6, SkeletonInfo_R *skeleton, s32 arg8) {
    Vec3s *temp_v0;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    f32 temp_fv0;

    temp_v0 = &skeleton->now_joint[0];
    if (arg8 & 1) {
        sp20 = temp_v0->x - arg2;
        sp1C = temp_v0->z - arg4;
        sp18 = sin_s(arg5);
        temp_fv0 = cos_s(arg5);
        arg0->x = (arg1->x + (arg6->x * ((sp20 * temp_fv0) + (sp1C * sp18))));
        arg0->z = (arg1->z + (arg6->z * ((-sp20 * sp18) + (sp1C * temp_fv0))));
    }
    if (arg8 & 2) {
        arg0->y = arg1->y + (arg6->y * (temp_v0->y - arg3));
    }
}
