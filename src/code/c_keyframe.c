#include "global.h"
#include "c_keyframe.h"
#include "z64math.h"
#include "m_lib.h"
#include "gfx.h"
#include "m_play.h"
#include "fp.h"
#include "sys_matrix.h"
#include "sys_math3d.h"

float fabsf(float f);
#pragma intrinsic(fabsf)

#define IS_ZERO(f) (fabsf(f) < 0.008f)
#define FMOD(x, mod) ((x) - ((s32)((x) * (1.0f / (mod))) * (f32)(mod)))

UNK_TYPE *B_801458A0_jp[4];

void cKF_FrameControl_zeroClear(cKF_FrameControl_c *frameCtrl) {
    bzero(frameCtrl, 0x18);
    frameCtrl->mode = cKF_FC_STOP;
    frameCtrl->duration = 1.0f;
    frameCtrl->current = 1.0f;
    frameCtrl->speed = 1.0f;
    frameCtrl->end = 1.0f;
    frameCtrl->start = 1.0f;
}

/**
 * Initialize a FrameControl struct with default values.
 */
void cKF_FrameControl_ct(cKF_FrameControl_c *frameCtrl) {
    cKF_FrameControl_zeroClear(frameCtrl);
}

/**
 * Initialize a FrameControl struct with manually specified parameters.
 */
void cKF_FrameControl_setFrame(cKF_FrameControl_c *frameCtrl, f32 start, f32 end, f32 duration, f32 current, f32 speed,
                               s32 mode) {
    frameCtrl->start = start;
    frameCtrl->end = (end < 1.0f) ? duration : end;
    frameCtrl->duration = duration;
    frameCtrl->speed = speed;
    frameCtrl->current = current;
    frameCtrl->mode = mode;
}

/**
 * Check if the next frame will pass the specified frame number.
 *
 * @param[in] frameCtrl The FrameControl struct to check.
 * @param[in] compareFrame The frame number to compare against.
 * @param[out] remainder The amount of frames past compareFrame.
 * @return Boolean. True if the next frame passes compareFrame.
 */
s32 cKF_FrameControl_passCheck(cKF_FrameControl_c *frameCtrl, f32 compareFrame, f32 *remainder) {
    f32 speed;

    *remainder = 0.0f;

    if (compareFrame == frameCtrl->current) {
        return false;
    }

    speed = (frameCtrl->start < frameCtrl->end) ? frameCtrl->speed : -frameCtrl->speed;

    if ((speed >= 0.0f && frameCtrl->current < compareFrame && frameCtrl->current + speed >= compareFrame) ||
        (speed < 0.0f && compareFrame < frameCtrl->current && frameCtrl->current + speed <= compareFrame)) {
        *remainder = frameCtrl->current + speed - compareFrame;
        return true;
    }

    return false;
}

/**
 * Check if the current frame is past the specified frame number.
 *
 * @return Boolean. True if the current frame is past compareFrame.
 */
s32 cKF_FrameControl_passCheck_now(cKF_FrameControl_c *frameCtrl, f32 compareFrame) {
    s32 ret = false;

    if (compareFrame != frameCtrl->current) {
        f32 speed = (frameCtrl->start < frameCtrl->end) ? frameCtrl->speed : -frameCtrl->speed;

        if ((speed >= 0.0f && compareFrame <= frameCtrl->current && frameCtrl->current - speed < compareFrame) ||
            (speed < 0.0f && frameCtrl->current <= compareFrame && frameCtrl->current - speed > compareFrame)) {
            ret = true;
        }
    } else {
        ret = true;
    }

    return ret;
}

/**
 * Check if an animation that plays once has completed.
 *
 * @return 0 if the animation is still playing. 1 if the animation has completed.
 */
s32 cKF_FrameControl_stop_proc(cKF_FrameControl_c *frameCtrl) {
    f32 remainder;

    if (frameCtrl->current == frameCtrl->end) {
        return 1;
    }
    if (cKF_FrameControl_passCheck(frameCtrl, frameCtrl->end, &remainder)) {
        frameCtrl->current = frameCtrl->end;
        return 1;
    }
    if (cKF_FrameControl_passCheck(frameCtrl, frameCtrl->start, &remainder)) {
        frameCtrl->current = frameCtrl->end;
        return 1;
    }

    return 0;
}

/**
 * Check if an animation that repeats has completed one loop.
 *
 * @return 0 if the animation is still playing. 2 if the loop has completed.
 */
s32 cKF_FrameControl_repeat_proc(cKF_FrameControl_c *frameCtrl) {
    f32 remainder;

    if (cKF_FrameControl_passCheck(frameCtrl, frameCtrl->end, &remainder)) {
        frameCtrl->current = (f32)(frameCtrl->start + remainder);
        return 2;
    }
    if (cKF_FrameControl_passCheck(frameCtrl, frameCtrl->start, &remainder)) {
        frameCtrl->current = frameCtrl->end + remainder;
        return 2;
    }

    return 0;
}

/**
 * Advance a FrameControl struct by 1 frame.
 *
 * @return 0 if the animation is still playing. 1 if the animation has completed. 2 if the animation repeated.
 */
s32 cKF_FrameControl_play(cKF_FrameControl_c *frameCtrl) {
    f32 speed;
    s32 ret;

    if (frameCtrl->mode == cKF_FC_STOP) {
        ret = cKF_FrameControl_stop_proc(frameCtrl);
    } else {
        ret = cKF_FrameControl_repeat_proc(frameCtrl);
    }

    // if the animation is still playing
    if (ret == 0) {
        speed = (frameCtrl->start < frameCtrl->end) ? frameCtrl->speed : -frameCtrl->speed;
        frameCtrl->current += speed;
    }

    // if the current frame is past the end, wrap the frame counter back to the start of the animation
    if (frameCtrl->current < 1.0f) {
        frameCtrl->current = (frameCtrl->current - 1.0f) + frameCtrl->duration;
    } else if (frameCtrl->duration < frameCtrl->current) {
        frameCtrl->current = (frameCtrl->current - frameCtrl->duration) + 1.0f;
    }

    return ret;
}

/**
 * Interpolate between two points using a cubic Hermite curve.
 *
 * A Hermite curve is a parametric function p(t) where t is restricted to the domain [0, 1].
 * It's defined with a start point and an end point. The shape of the curve is controlled by the tangents of the end
 * points.
 * If keyframes aren't placed at fixed intervals in time, the animation will abruptly change speed and direction when
 * passing through keyframes. To avoid this, the tangents are multiplied by the length of time between the two
 * keyframes.
 *
 * @param t Represents the desired position between keyframe 1 and keyframe 2 to interpolate.
 * @param duration The amount of time between keyframe 1 and keyframe 2, in seconds.
 * @param p0 The start point.
 * @param p1 The end point.
 * @param v0 The velocity at p0.
 * @param v1 The velocity at p1.
 * @return Interpolated value.
 */
f32 cKF_HermitCalc(f32 t, f32 duration, f32 p0, f32 p1, f32 v0, f32 v1) {
    // Hermite basis functions
    f32 h3 = 3.0f * SQ(t) - 2.0f * CB(t);
    f32 h2 = -SQ(t) + CB(t);
    f32 h1 = CB(t) - 2.0f * SQ(t) + t;
    f32 h0 = 1.0f - h3;

    return h0 * p0 + h3 * p1 + (h1 * v0 + h2 * v1) * duration;
}

/**
 * Given a sequence of keyframes, return the position that corresponds to the current frame.
 *
 * Animations are defined by a small sequence of keyframes, which record a position at a specific frame of the
 * animation. Any position between two keyframes is calculated by interpolating between them.
 * Keyframes are 1 dimensional. In the context of a 3d position, x, y, and z coordinates each use a separate
 * sequence of keyframes.
 *
 * @param startIndex Which keyframe in dataSource to start with.
 * @param sequenceLength How many keyframes are in the sequence.
 * @param dataSource Array where all the keyframes are stored.
 * @param currentFrame The current frame of the animation.
 * @return The position that corresponds to currentFrame.
 */
s16 cKF_KeyCalc(s16 startIndex, s16 sequenceLength, Keyframe *dataSource, f32 currentFrame) {
    Keyframe *ds = &dataSource[startIndex];
    f32 frameDelta;
    s32 kf2;
    s32 kf1;

    // if currentFrame is before the first keyframe of the sequence
    if (currentFrame <= ds[0].frame) {
        return ds[0].point;
    }
    // if currentFrame is after the last frame of the sequence
    if (ds[sequenceLength - 1].frame <= currentFrame) {
        return ds[sequenceLength - 1].point;
    }
    // iterate over each keyframe to find which keyframes are before and after currentFrame
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

void cKF_SkeletonInfo_R_zeroClear(cKF_SkeletonInfo_R_c *skeletonInfo) {
    bzero(skeletonInfo, 0x70);
}

/**
 * Initialize a SkeletonInfo struct with default values.
 */
void cKF_SkeletonInfo_R_ct(cKF_SkeletonInfo_R_c *skeletonInfo, cKF_BaseSkeleton_R_c *skeleton,
                           cKF_BaseAnimation_R_c *animation, Vec3s *now_joint, Vec3s *morph_joint) {
    cKF_SkeletonInfo_R_zeroClear(skeletonInfo);
    cKF_FrameControl_ct(&skeletonInfo->frameCtrl);
    skeletonInfo->skeleton = Lib_SegmentedToVirtual(skeleton);
    skeletonInfo->animation = Lib_SegmentedToVirtual(animation);
    skeletonInfo->now_joint = now_joint;
    skeletonInfo->morph_joint = morph_joint;
}

void cKF_SkeletonInfo_R_dt(cKF_SkeletonInfo_R_c *skeletonInfo) {
}

/**
 * Initialize a SkeletonInfo struct with an animation that plays once.
 */
void cKF_SkeletonInfo_R_init_standard_stop(cKF_SkeletonInfo_R_c *skeletonInfo, cKF_BaseAnimation_R_c *animation,
                                           Vec3s *diff_rot_tbl) {
    cKF_SkeletonInfo_R_init(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f,
                            ((cKF_BaseAnimation_R_c *)Lib_SegmentedToVirtual(animation))->duration, 1.0f, 1.0, 0.0f,
                            cKF_FC_STOP, diff_rot_tbl);
}

/**
 * Initialize a SkeletonInfo struct with a specified playback speed that plays once.
 */
void cKF_SkeletonInfo_R_init_standard_stop_speedset(cKF_SkeletonInfo_R_c *skeletonInfo,
                                                    cKF_BaseAnimation_R_c *animation, Vec3s *diff_rot_tbl,
                                                    f32 frameSpeed) {
    cKF_SkeletonInfo_R_init(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f,
                            ((cKF_BaseAnimation_R_c *)Lib_SegmentedToVirtual(animation))->duration, 1.0f, frameSpeed,
                            0.0f, cKF_FC_STOP, diff_rot_tbl);
}

void cKF_SkeletonInfo_R_init_standard_stop_morph(cKF_SkeletonInfo_R_c *skeletonInfo, cKF_BaseAnimation_R_c *animation,
                                                 Vec3s *diff_rot_tbl, f32 morphCounter) {
    cKF_SkeletonInfo_R_init(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f,
                            ((cKF_BaseAnimation_R_c *)Lib_SegmentedToVirtual(animation))->duration, 1.0f, 1.0,
                            morphCounter, cKF_FC_STOP, diff_rot_tbl);
}

/**
 * Initialize a SkeletonInfo struct with an animation that repeats.
 */
void cKF_SkeletonInfo_R_init_standard_repeat(cKF_SkeletonInfo_R_c *skeletonInfo, cKF_BaseAnimation_R_c *animation,
                                             Vec3s *diff_rot_tbl) {
    cKF_SkeletonInfo_R_init(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f,
                            ((cKF_BaseAnimation_R_c *)Lib_SegmentedToVirtual(animation))->duration, 1.0f, 1.0, 0.0f,
                            cKF_FC_REPEAT, diff_rot_tbl);
}

/**
 * Initialize a SkeletonInfo struct with a specified playback speed that repeats.
 */
void cKF_SkeletonInfo_R_init_standard_repeat_speedset(cKF_SkeletonInfo_R_c *skeletonInfo,
                                                      cKF_BaseAnimation_R_c *animation, Vec3s *diff_rot_tbl,
                                                      f32 frameSpeed) {
    cKF_SkeletonInfo_R_init(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f,
                            ((cKF_BaseAnimation_R_c *)Lib_SegmentedToVirtual(animation))->duration, 1.0f, frameSpeed,
                            0.0f, cKF_FC_REPEAT, diff_rot_tbl);
}

void cKF_SkeletonInfo_R_init_standard_repeat_morph(cKF_SkeletonInfo_R_c *skeletonInfo, cKF_BaseAnimation_R_c *animation,
                                                   Vec3s *diff_rot_tbl, f32 morphCounter) {
    cKF_SkeletonInfo_R_init(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f,
                            ((cKF_BaseAnimation_R_c *)Lib_SegmentedToVirtual(animation))->duration, 1.0f, 1.0,
                            morphCounter, cKF_FC_REPEAT, diff_rot_tbl);
}

/**
 * Initialize a SkeletonInfo struct with manually specified parameters.
 */
void cKF_SkeletonInfo_R_init(cKF_SkeletonInfo_R_c *skeletonInfo, cKF_BaseSkeleton_R_c *skeleton,
                             cKF_BaseAnimation_R_c *animation, f32 startFrame, f32 endFrame, f32 frameCurrent,
                             f32 frameSpeed, f32 morphCounter, s32 frameMode, Vec3s *diff_rot_tbl) {
    skeletonInfo->morphCounter = morphCounter;
    skeletonInfo->skeleton = Lib_SegmentedToVirtual(skeleton);
    skeletonInfo->animation = Lib_SegmentedToVirtual(animation);
    cKF_FrameControl_setFrame(&skeletonInfo->frameCtrl, startFrame, endFrame, skeletonInfo->animation->duration,
                              frameCurrent, frameSpeed, frameMode);
    skeletonInfo->diff_rot_tbl = diff_rot_tbl;
}

/**
 * Assign a SkeletonInfo struct's animation.
 */
void cKF_SkeletonInfo_R_setAnim(cKF_SkeletonInfo_R_c *skeletonInfo, cKF_BaseAnimation_R_c *animation) {
    cKF_BaseAnimation_R_c *anim = (cKF_BaseAnimation_R_c *)Lib_SegmentedToVirtual(animation);

    skeletonInfo->animation = anim;
    skeletonInfo->frameCtrl.duration = anim->duration;
}

void cKF_SkeletonInfo_R_morphJoint(cKF_SkeletonInfo_R_c *skeletonInfo) {
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
// s32 cKF_SkeletonInfo_R_play(cKF_SkeletonInfo_R_c* skeletonInfo)
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

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/cKF_Si3_draw_SV_R_child.s")

/**
 * Draw a specified joint in a SkeletonInfo struct.
 *
 * This is a recursive function, that will call itself again for each child this joint has.
 *
 * @param jointIndex The index of the joint to draw.
 */
void cKF_Si3_draw_SV_R_child(PlayState *play, cKF_SkeletonInfo_R_c *skeletonInfo, s32 *jointIndex,
                             cKF_draw_callback prerenderCallback, cKF_draw_callback postrenderCallback, void *arg,
                             Mtx **mtx) {
    cKF_JointElem_R_c *jointElem =
        *jointIndex + (cKF_JointElem_R_c *)Lib_SegmentedToVirtual(skeletonInfo->skeleton->joint_tbl);
    s32 i;
    Gfx *newDlist;
    Gfx *shape;
    u8 jointElemFlag;
    Vec3s rotation;
    Vec3s *joint = &skeletonInfo->now_joint[*jointIndex];
    Vec3f translation;

    if (*jointIndex) {
        translation.x = jointElem->trs.x;
        translation.y = jointElem->trs.y;
        translation.z = jointElem->trs.z;
    } else {
        s32 skeletonInfoFlag = skeletonInfo->move_flag;
        Vec3f *temp = &skeletonInfo->base_shape_trs;

        if (skeletonInfoFlag & 1) {
            translation.x = temp->x;
            translation.z = temp->z;
        } else {
            translation.x = joint->x;
            translation.z = joint->z;
        }

        if (skeletonInfoFlag & 2) {
            translation.y = temp->y;
        } else {
            translation.y = joint->y;
        }
    }

    joint++;
    rotation = *joint;

    if (*jointIndex == 0) {
        s32 an_flag = skeletonInfo->move_flag;

        if (an_flag & 4) {
            rotation.x = skeletonInfo->base_data_angle.x;
            rotation.y = skeletonInfo->renew_base_data_angle.y;
            rotation.z = skeletonInfo->renew_base_data_angle.z;
        }
    }

    if (1) {}
    if (1) {}

    OPEN_DISPS(play->state.gfxCtx);
    Matrix_push();
    newDlist = shape = jointElem->shape;
    jointElemFlag = jointElem->work_flag;

    if ((prerenderCallback == NULL) ||
        ((prerenderCallback != NULL) && prerenderCallback(play, skeletonInfo, *jointIndex, &newDlist, &jointElemFlag,
                                                          arg, &rotation, &translation) != NULL)) {
        Matrix_softcv3_mult(&translation, &rotation);

        if (newDlist != NULL) {
            _Matrix_to_Mtx(*mtx);

            if (jointElemFlag & 1) {
                gSPMatrix(POLY_XLU_DISP++, *mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                if (1) {}
                gSPDisplayList(POLY_XLU_DISP++, newDlist);
            } else {
                gSPMatrix(POLY_OPA_DISP++, *mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_OPA_DISP++, newDlist);
            }

            (*mtx)++;

        } else if (shape != NULL) {
            _Matrix_to_Mtx(*mtx);
            if (1) {
                gSPMatrix(POLY_OPA_DISP++, *mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            }

            (*mtx)++;
        }
    }

    if (postrenderCallback != NULL) {
        postrenderCallback(play, skeletonInfo, *jointIndex, &newDlist, &jointElemFlag, arg, &rotation, &translation);
    }

    (*jointIndex)++;

    for (i = 0; i < jointElem->numberOfChildren; i++) {
        cKF_Si3_draw_SV_R_child(play, skeletonInfo, jointIndex, prerenderCallback, postrenderCallback, arg, mtx);
    }

    Matrix_pull();
    CLOSE_DISPS(play->state.gfxCtx);
}

/**
 * Draw all the joints in in a SkeletonInfo struct.
 *
 * This function calls cKF_Si3_draw_SV_R_child() to recursively draw each joint.
 */
void cKF_Si3_draw_R_SV(PlayState *play, cKF_SkeletonInfo_R_c *skeletonInfo, Mtx *mtx,
                       cKF_draw_callback prerenderCallback, cKF_draw_callback postrenderCallback, void *arg) {
    s32 jointIndex;

    if (mtx != NULL) {
        OPEN_DISPS(play->state.gfxCtx);
        do {
            gSPSegment(POLY_OPA_DISP++, 0x0D, mtx);
            do {
                gSPSegment(POLY_XLU_DISP++, 0x0D, mtx);
            } while (0);
        } while (0);
        jointIndex = 0;
        cKF_Si3_draw_SV_R_child(play, skeletonInfo, &jointIndex, prerenderCallback, postrenderCallback, arg, &mtx);
        CLOSE_DISPS(play->state.gfxCtx);
    }
}

void cKF_SkeletonInfo_R_init_standard_repeat_speedsetandmorph(cKF_SkeletonInfo_R_c *skeletonInfo,
                                                              cKF_BaseAnimation_R_c *animation, Vec3s *arg2, f32 arg3,
                                                              f32 arg4) {
    cKF_SkeletonInfo_R_init(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f,
                            ((cKF_BaseAnimation_R_c *)Lib_SegmentedToVirtual(animation))->duration, 1.0f, arg3, arg4,
                            cKF_FC_REPEAT, arg2);
}

void cKF_SkeletonInfo_R_init_standard_repeat_setframeandspeedandmorph(cKF_SkeletonInfo_R_c *skeletonInfo,
                                                                      cKF_BaseAnimation_R_c *animation, Vec3s *arg2,
                                                                      f32 arg3, f32 arg4, f32 arg5) {
    cKF_SkeletonInfo_R_init(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f,
                            ((cKF_BaseAnimation_R_c *)Lib_SegmentedToVirtual(animation))->duration, arg3, arg4, arg5,
                            cKF_FC_REPEAT, arg2);
}

void cKF_SkeletonInfo_R_init_standard_setframeandspeedandmorphandmode(cKF_SkeletonInfo_R_c *skeletonInfo,
                                                                      cKF_BaseAnimation_R_c *animation, Vec3s *arg2,
                                                                      f32 arg3, f32 arg4, f32 arg5, s32 arg6) {
    cKF_SkeletonInfo_R_init(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f,
                            ((cKF_BaseAnimation_R_c *)Lib_SegmentedToVirtual(animation))->duration, arg3, arg4, arg5,
                            arg6, arg2);
}

void cKF_SkeletonInfo_R_init_reverse_setspeedandmorphandmode(cKF_SkeletonInfo_R_c *skeletonInfo,
                                                             cKF_BaseAnimation_R_c *animation, Vec3s *arg2, f32 arg3,
                                                             f32 arg4, s32 arg5) {
    cKF_SkeletonInfo_R_init(skeletonInfo, skeletonInfo->skeleton, animation,
                            ((cKF_BaseAnimation_R_c *)Lib_SegmentedToVirtual(animation))->duration, 1.0f,
                            ((cKF_BaseAnimation_R_c *)Lib_SegmentedToVirtual(animation))->duration, arg3, arg4, arg5,
                            arg2);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/func_80053384_jp.s")
void func_80053384_jp(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, UNK_TYPE* arg6, UNK_TYPE* arg7,
                      UNK_TYPE* arg8) {
    if (arg3 != 0) {
        B_801458A0_jp[arg0] = PHYSICAL_TO_VIRTUAL(arg6);
    }
    if (arg4 != 0) {
        B_801458A0_jp[arg1] = PHYSICAL_TO_VIRTUAL(arg7);
    }
    if (arg5 != 0) {
        B_801458A0_jp[arg2] = PHYSICAL_TO_VIRTUAL(arg8);
    }
}

void cKF_SkeletonInfo_R_combine_work_set(cKF_SkeletonInfo_R_combine_work_c *combine, cKF_SkeletonInfo_R_c *skeleton) {
    combine->skeletonInfo = skeleton;
    combine->anm_const_val_tbl = Lib_SegmentedToVirtual(skeleton->animation->const_value_tbl);
    combine->anm_key_num = Lib_SegmentedToVirtual(skeleton->animation->key_num);
    combine->anm_data_src = Lib_SegmentedToVirtual(skeleton->animation->data_source);
    combine->anm_check_bit_tbl = Lib_SegmentedToVirtual(skeleton->animation->ConstKeyCheckBitTbl);
    combine->anm_key_num_idx = 0;
    combine->anm_const_val_tbl_idx = 0;
    combine->anm_data_src_idx = 0;
}

void cKF_SkeletonInfo_R_combine_translation(s16 **joint, u32 *flag, cKF_SkeletonInfo_R_combine_work_c *combine,
                                            s8 *arg3) {
    cKF_SkeletonInfo_R_combine_work_c *temp_s1;
    cKF_SkeletonInfo_R_combine_work_c *temp_s2;
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

void cKF_SkeletonInfo_R_combine_rotation(s16 **joint, u32 *flag, cKF_SkeletonInfo_R_combine_work_c *combine, s8 *arg3) {
    cKF_SkeletonInfo_R_combine_work_c *sp64;
    cKF_SkeletonInfo_R_combine_work_c *temp_s0;
    cKF_SkeletonInfo_R_combine_work_c *temp_s1;
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

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/cKF_SkeletonInfo_R_combine_play.s")
s32 cKF_SkeletonInfo_R_combine_play(cKF_SkeletonInfo_R_c *skeletonInfo1, cKF_SkeletonInfo_R_c *skeletonInfo2, s32 arg2,
                                    s32 arg3, s32 arg4, s32 arg5, s8 *flag) {
    Vec3s *var_v0;
    u32 spB0;
    s16 *joint;
    cKF_SkeletonInfo_R_combine_work_c combine1;
    cKF_SkeletonInfo_R_combine_work_c combine2;
    cKF_SkeletonInfo_R_combine_work_c combine3;
    s32 var_s0;
    UNK_TYPE *sp44;
    UNK_TYPE *sp40;
    s32 var_v1;

    sp44 = NULL;
    sp40 = NULL;

    if ((skeletonInfo1 == NULL) || (skeletonInfo2 == NULL) || (arg2 < 0) || (arg2 >= 0x10) || (arg3 < 0) ||
        (arg3 >= 0x10) || (flag == NULL)) {
        return 0;
    }

    if (!(fabsf(skeletonInfo1->morphCounter) < 0.008f)) {
        joint = (s16 *)skeletonInfo1->morph_joint;
    } else {
        joint = (s16 *)skeletonInfo1->now_joint;
    }

    if (arg4 != 0) {
        sp44 = PHYSICAL_TO_VIRTUAL(B_801458A0_jp[arg2]);
        B_801458A0_jp[arg2] = PHYSICAL_TO_VIRTUAL(arg4);
        cKF_SkeletonInfo_R_combine_work_set(&combine3, skeletonInfo1);
    }

    if (arg5 != 0) {
        sp40 = PHYSICAL_TO_VIRTUAL(B_801458A0_jp[arg3]);
        B_801458A0_jp[arg3] = PHYSICAL_TO_VIRTUAL(arg5);
        cKF_SkeletonInfo_R_combine_work_set(&combine2, skeletonInfo2);
        cKF_SkeletonInfo_R_combine_work_set(&combine1, skeletonInfo2);
    }

    spB0 = 0x20;
    cKF_SkeletonInfo_R_combine_translation(&joint, &spB0, &combine3, flag);
    cKF_SkeletonInfo_R_combine_rotation(&joint, &spB0, &combine3, flag);

    if (skeletonInfo1->diff_rot_tbl != NULL) {
        if (!IS_ZERO(skeletonInfo1->morphCounter)) {
            var_v0 = skeletonInfo1->morph_joint;
        } else {
            var_v0 = skeletonInfo1->now_joint;
        }

        var_v0++;

        for (var_v1 = 0; var_v1 < skeletonInfo1->skeleton->joint_num; var_v1++) {
            var_v0->x = var_v0->x + skeletonInfo1->diff_rot_tbl[var_v1].x;
            var_v0->y = var_v0->y + skeletonInfo1->diff_rot_tbl[var_v1].y;
            var_v0->z = var_v0->z + skeletonInfo1->diff_rot_tbl[var_v1].z;
            var_v0++;
        }
    }
    if (IS_ZERO(skeletonInfo1->morphCounter)) {
        cKF_FrameControl_play(&skeletonInfo2->frameCtrl);
        var_s0 = cKF_FrameControl_play(&skeletonInfo1->frameCtrl);
        func_80053384_jp(arg2, arg3, 0, arg4, arg5, 0, sp44, sp40, 0);
    } else {
        if (skeletonInfo1->morphCounter > 0.0f) {
            cKF_SkeletonInfo_R_morphJoint(skeletonInfo1);
            skeletonInfo1->morphCounter -= 1.0f;
            if (skeletonInfo1->morphCounter <= 0.0f) {
                skeletonInfo1->morphCounter = 0.0f;
            }
            func_80053384_jp(arg2, arg3, 0, arg4, arg5, 0, sp44, sp40, 0);
            return 0;
        }

        cKF_SkeletonInfo_R_morphJoint(skeletonInfo1);

        skeletonInfo1->morphCounter += 1.0f;
        if (skeletonInfo1->morphCounter >= 0.0f) {
            skeletonInfo1->morphCounter = 0.0f;
        }

        cKF_FrameControl_play(&skeletonInfo2->frameCtrl);
        var_s0 = cKF_FrameControl_play(&skeletonInfo1->frameCtrl);
        func_80053384_jp(arg2, arg3, 0, arg4, arg5, 0, sp44, sp40, 0);
    }
    return var_s0;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/c_keyframe/cKF_SkeletonInfo_R_T_combine_play.s")

void cKF_SkeletonInfo_R_Animation_Set_base_shape_trs(cKF_SkeletonInfo_R_c *skeletonInfo, f32 arg1, f32 arg2, f32 arg3,
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

void cKF_SkeletonInfo_R_AnimationMove_ct_base(Vec3f *arg0, Vec3f *arg1, s16 arg2, s16 arg3, f32 arg4,
                                              cKF_SkeletonInfo_R_c *skeletonInfo, s32 arg6) {
    s32 var_v0;

    skeletonInfo->move_flag = arg6;
    skeletonInfo->correct_counter = (arg4 >= 0.0f) ? arg4 : -arg4;
    skeletonInfo->idle_world_pos = ZeroVec;
    skeletonInfo->d_correct_base_world_pos = ZeroVec;

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

void cKF_SkeletonInfo_R_AnimationMove_dt(cKF_SkeletonInfo_R_c *skeletonInfo) {
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
// void cKF_SkeletonInfo_R_AnimationMove_base(Vec3f *arg0, s16 *arg1, Vec3f *arg2, s16 arg3, cKF_SkeletonInfo_R_c
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

void cKF_SkeletonInfo_R_AnimationMove_CulcTransToWorld(Vec3f *arg0, Vec3f *arg1, f32 arg2, f32 arg3, f32 arg4, s16 arg5,
                                                       Vec3f *arg6, cKF_SkeletonInfo_R_c *skeleton, s32 arg8) {
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
