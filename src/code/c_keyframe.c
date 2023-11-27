/**
 * @file c_keyframe.c
 *
 * Skeletal animation with keyframes.
 *
 * This system was used in Majora's Mask, however Doubutsu no Mori uses the "R" variants of structs, which differ
 * slightly.
 *
 * Animation is broken down into multiple parts that work together.
 *
 * FrameControl: A struct responsible for keeping track of the time component of animations. Animations use frames
 * (one thirtieth of a second) as a unit of time.
 *
 * Joint: A display list that represents a small section of the overall model. Joints have a hierarchal structure, where
 * joints can specify child joints, and each joint inherits it's parent's transformation. Joints are represented in two
 * places. A JointElemR struct stores the joint's display list. There's also a jointTable gets passed in from an actor.
 * This is a s_xyz array, with the first vector storing the root translation, the second vector is the root rotation,
 * and each vector after that is a joint's rotation.
 *
 * Morph: Normally switching from the previous animation to a new animation produces jarring motion as the joints jump
 * to the first frame of the new animation in a single frame. Morph allows the joints to interpolate between their old
 * position and the current animation's position over multiple frames (specified by morphCounter) to avoid this. If an
 * animation is using morph an array separate from jointTable, morphTable stores the the animation's joint rotations for
 * the current frame.
 *
 * BaseSkeletonR: A collection of JointElemR structs that make up the skeleton that will be animated.
 *
 * BaseAnimationR: Stores keyframes used to animate the skeleton. Skeletons are animated by rotating joints. They can't
 * be translated or scaled, and the distance between two joints will always be the same. The only joint that has
 * translation data is the root joint.
 *
 * SkeletonInfoR: The large struct containing a FrameControl, BaseSkeletonR, BaseAnimationR, jointTable, morphTable, and
 * more.
 */

#include "global.h"
#include "c_keyframe.h"
#include "z64math.h"
#include "m_lib.h"
#include "gfx.h"
#include "libc64/fp.h"
#include "sys_matrix.h"
#include "sys_math3d.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void cKF_FrameControl_zeroClear(FrameControl* frameControl) {
    bzero(frameControl, sizeof(FrameControl));
    frameControl->mode = ANIMATION_STOP;
    frameControl->duration = 1.0f;
    frameControl->currentFrame = 1.0f;
    frameControl->speed = 1.0f;
    frameControl->end = 1.0f;
    frameControl->start = 1.0f;
}

void cKF_FrameControl_ct(FrameControl* frameControl) {
    cKF_FrameControl_zeroClear(frameControl);
}

void cKF_FrameControl_setFrame(FrameControl* frameControl, f32 start, f32 end, f32 duration, f32 currentFrame,
                               f32 speed, AnimationMode mode) {
    frameControl->start = start;
    frameControl->end = (end < 1.0f) ? duration : end;
    frameControl->duration = duration;
    frameControl->speed = speed;
    frameControl->currentFrame = currentFrame;
    frameControl->mode = mode;
}

/**
 * Check if the next frame will pass the specified frame number.
 *
 * @param[in] frameControl The FrameControl struct to check.
 * @param[in] compareFrame The frame number to compare against.
 * @param[out] remainder The amount of frames past compareFrame.
 * @return Boolean. True if the next frame passes compareFrame.
 */
s32 cKF_FrameControl_passCheck(FrameControl* frameControl, f32 compareFrame, f32* remainder) {
    f32 speed;

    *remainder = 0.0f;

    if (compareFrame == frameControl->currentFrame) {
        return false;
    }

    speed = (frameControl->start < frameControl->end) ? frameControl->speed : -frameControl->speed;

    if ((speed >= 0.0f && frameControl->currentFrame < compareFrame &&
         frameControl->currentFrame + speed >= compareFrame) ||
        (speed < 0.0f && compareFrame < frameControl->currentFrame &&
         frameControl->currentFrame + speed <= compareFrame)) {
        *remainder = frameControl->currentFrame + speed - compareFrame;
        return true;
    }

    return false;
}

/**
 * Check if the current frame is past the specified frame number.
 *
 * @return Boolean. True if the current frame is past compareFrame.
 */
s32 cKF_FrameControl_passCheck_now(FrameControl* frameControl, f32 compareFrame) {
    s32 ret = false;

    if (compareFrame != frameControl->currentFrame) {
        f32 speed = (frameControl->start < frameControl->end) ? frameControl->speed : -frameControl->speed;

        if ((speed >= 0.0f && compareFrame <= frameControl->currentFrame &&
             frameControl->currentFrame - speed < compareFrame) ||
            (speed < 0.0f && frameControl->currentFrame <= compareFrame &&
             frameControl->currentFrame - speed > compareFrame)) {
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
 * @return 0 if the animation is still playing. 1 if the animation mode is ANIMATION_STOP and has completed.
 */
s32 cKF_FrameControl_stop_proc(FrameControl* frameControl) {
    f32 remainder;

    if (frameControl->currentFrame == frameControl->end) {
        return 1;
    }
    if (cKF_FrameControl_passCheck(frameControl, frameControl->end, &remainder)) {
        frameControl->currentFrame = frameControl->end;
        return 1;
    }
    if (cKF_FrameControl_passCheck(frameControl, frameControl->start, &remainder)) {
        frameControl->currentFrame = frameControl->end;
        return 1;
    }

    return 0;
}

/**
 * Check if an animation that repeats has completed one loop.
 *
 * @return 0 if the animation is still playing. 2 if the animation mode is ANIMATION_REPEAT and a loop has completed.
 */
s32 cKF_FrameControl_repeat_proc(FrameControl* frameControl) {
    f32 remainder;

    if (cKF_FrameControl_passCheck(frameControl, frameControl->end, &remainder)) {
        frameControl->currentFrame = (f32)(frameControl->start + remainder);
        return 2;
    }
    if (cKF_FrameControl_passCheck(frameControl, frameControl->start, &remainder)) {
        frameControl->currentFrame = frameControl->end + remainder;
        return 2;
    }

    return 0;
}

/**
 * Advance a FrameControl struct by 1 frame.
 *
 * @return 0 if the animation is still playing. 1 if the animation mode is ANIMATION_STOP and has completed. 2 if the
 * animation mode is ANIMATION_REPEAT and a loop has completed.
 */
s32 cKF_FrameControl_play(FrameControl* frameControl) {
    f32 speed;
    s32 ret;

    if (frameControl->mode == ANIMATION_STOP) {
        ret = cKF_FrameControl_stop_proc(frameControl);
    } else {
        ret = cKF_FrameControl_repeat_proc(frameControl);
    }

    // if the animation is still playing
    if (ret == 0) {
        speed = (frameControl->start < frameControl->end) ? frameControl->speed : -frameControl->speed;
        frameControl->currentFrame += speed;
    }

    // if the current frame is past the end, wrap the frame counter back to the start of the animation
    if (frameControl->currentFrame < 1.0f) {
        frameControl->currentFrame = (frameControl->currentFrame - 1.0f) + frameControl->duration;
    } else if (frameControl->duration < frameControl->currentFrame) {
        frameControl->currentFrame = (frameControl->currentFrame - frameControl->duration) + 1.0f;
    }

    return ret;
}

/**
 * Interpolate between two values using a cubic Hermite curve.
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
 * Given a sequence of keyframes, return the value from currentFrame of the animation.
 *
 * Animations are defined by a small sequence of keyframes, which record a value at a specific frame of the
 * animation. Any value between two keyframes is calculated by interpolating between them.
 * Keyframes are 1 dimensional. In the context of a joint the x, y, and z rotation each use a separate
 * sequence of keyframes.
 *
 * @param startIndex Which keyframe in dataSource to start with.
 * @param sequenceLength How many keyframes are in the sequence.
 * @param dataSource Array where all the keyframes are stored.
 * @return The value that corresponds to currentFrame.
 */
s16 cKF_KeyCalc(s16 startIndex, s16 sequenceLength, Keyframe* dataSource, f32 currentFrame) {
    Keyframe* ds = &dataSource[startIndex];
    f32 frameDelta;
    s32 kf2;
    s32 kf1;

    // If currentFrame is before the first keyframe of the sequence.
    if (currentFrame <= ds[0].frame) {
        return ds[0].value;
    }
    // If currentFrame is after the last frame of the sequence.
    if (ds[sequenceLength - 1].frame <= currentFrame) {
        return ds[sequenceLength - 1].value;
    }
    // Iterate over each keyframe to find which keyframes are before and after currentFrame.
    for (kf2 = 1, kf1 = 0; true; kf1++, kf2++) {
        if (currentFrame < ds[kf2].frame) {
            frameDelta = ds[kf2].frame - ds[kf1].frame;
            if (!IS_ZERO(frameDelta)) {
                return nearbyint(cKF_HermitCalc((currentFrame - ds[kf1].frame) / frameDelta, frameDelta * (1.0f / 30),
                                                ds[kf1].value, ds[kf2].value, ds[kf1].velocity, ds[kf2].velocity));
            } else {
                return ds[kf1].value;
            }
        }
    }
}

void cKF_SkeletonInfo_subRotInterpolation(f32 t, s16* out, s16 jointRotation, s16 morphRotation) {
    u16 urot1 = jointRotation;
    s32 pad UNUSED;
    u16 urot2 = morphRotation;
    f32 f1 = jointRotation;
    f32 signedDiff = morphRotation - f1;
    f32 f2 = urot1;
    f32 unsignedDiff = urot2 - f2;

    if (fabsf(signedDiff) < fabsf(unsignedDiff)) {
        *out = f1 + signedDiff * t;
    } else {
        *out = f2 + unsignedDiff * t;
    }
}

/**
 * When playing a morph animation, linearly interpolate the root joint between it's current position and it's position
 * in the current frame of the animation.
 *
 * Linear interpolation uses a parametric function p(t) where t is restricted to the domain [0, 1].
 *
 * @param t Represents the desired position between p0 and p1 to interpolate.
 */
void cKF_SkeletonInfo_morphST(s16* joint, s16* morph, f32 t) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (*joint != *morph) {
            f32 p0 = *joint;
            f32 p1 = *morph;

            *joint = p0 + (p1 - p0) * t;
        }
        joint++;
        morph++;
    }
}

void cKF_SkeletonInfo_R_zeroClear(SkeletonInfoR* skeletonInfo) {
    bzero(skeletonInfo, sizeof(SkeletonInfoR));
}

void cKF_SkeletonInfo_R_ct(SkeletonInfoR* skeletonInfo, BaseSkeletonR* skeleton, BaseAnimationR* animation,
                           s_xyz* jointTable, s_xyz* morphTable) {
    cKF_SkeletonInfo_R_zeroClear(skeletonInfo);
    cKF_FrameControl_ct(&skeletonInfo->frameControl);
    skeletonInfo->skeleton = Lib_SegmentedToVirtual(skeleton);
    skeletonInfo->animation = Lib_SegmentedToVirtual(animation);
    skeletonInfo->jointTable = jointTable;
    skeletonInfo->morphTable = morphTable;
}

void cKF_SkeletonInfo_R_dt(SkeletonInfoR* skeletonInfo UNUSED) {
}

void cKF_SkeletonInfo_R_init_standard_stop(SkeletonInfoR* skeletonInfo, BaseAnimationR* animation,
                                           s_xyz* diffRotTable) {
    BaseAnimationR* animationPtr = Lib_SegmentedToVirtual(animation);

    cKF_SkeletonInfo_R_init(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f, animationPtr->duration, 1.0f, 1.0,
                            0.0f, ANIMATION_STOP, diffRotTable);
}

void cKF_SkeletonInfo_R_init_standard_stop_speedset(SkeletonInfoR* skeletonInfo, BaseAnimationR* animation,
                                                    s_xyz* diffRotTable, f32 speed) {
    BaseAnimationR* animationPtr = Lib_SegmentedToVirtual(animation);

    cKF_SkeletonInfo_R_init(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f, animationPtr->duration, 1.0f, speed,
                            0.0f, ANIMATION_STOP, diffRotTable);
}

void cKF_SkeletonInfo_R_init_standard_stop_morph(SkeletonInfoR* skeletonInfo, BaseAnimationR* animation,
                                                 s_xyz* diffRotTable, f32 morphCounter) {
    BaseAnimationR* animationPtr = Lib_SegmentedToVirtual(animation);

    cKF_SkeletonInfo_R_init(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f, animationPtr->duration, 1.0f, 1.0,
                            morphCounter, ANIMATION_STOP, diffRotTable);
}

void cKF_SkeletonInfo_R_init_standard_repeat(SkeletonInfoR* skeletonInfo, BaseAnimationR* animation,
                                             s_xyz* diffRotTable) {
    BaseAnimationR* animationPtr = Lib_SegmentedToVirtual(animation);

    cKF_SkeletonInfo_R_init(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f, animationPtr->duration, 1.0f, 1.0,
                            0.0f, ANIMATION_REPEAT, diffRotTable);
}

void cKF_SkeletonInfo_R_init_standard_repeat_speedset(SkeletonInfoR* skeletonInfo, BaseAnimationR* animation,
                                                      s_xyz* diffRotTable, f32 speed) {
    BaseAnimationR* animationPtr = Lib_SegmentedToVirtual(animation);

    cKF_SkeletonInfo_R_init(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f, animationPtr->duration, 1.0f, speed,
                            0.0f, ANIMATION_REPEAT, diffRotTable);
}

void cKF_SkeletonInfo_R_init_standard_repeat_morph(SkeletonInfoR* skeletonInfo, BaseAnimationR* animation,
                                                   s_xyz* diffRotTable, f32 morphCounter) {
    BaseAnimationR* animationPtr = Lib_SegmentedToVirtual(animation);

    cKF_SkeletonInfo_R_init(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f, animationPtr->duration, 1.0f, 1.0,
                            morphCounter, ANIMATION_REPEAT, diffRotTable);
}

void cKF_SkeletonInfo_R_init(SkeletonInfoR* skeletonInfo, BaseSkeletonR* skeleton, BaseAnimationR* animation,
                             f32 startFrame, f32 endFrame, f32 currentFrame, f32 speed, f32 morphCounter,
                             AnimationMode mode, s_xyz* diffRotTable) {
    skeletonInfo->morphCounter = morphCounter;
    skeletonInfo->skeleton = Lib_SegmentedToVirtual(skeleton);
    skeletonInfo->animation = Lib_SegmentedToVirtual(animation);
    cKF_FrameControl_setFrame(&skeletonInfo->frameControl, startFrame, endFrame, skeletonInfo->animation->duration,
                              currentFrame, speed, mode);
    skeletonInfo->diffRotTable = diffRotTable;
}

void cKF_SkeletonInfo_R_setAnim(SkeletonInfoR* skeletonInfo, BaseAnimationR* animation) {
    BaseAnimationR* animationPtr = Lib_SegmentedToVirtual(animation);

    skeletonInfo->animation = animationPtr;
    skeletonInfo->frameControl.duration = animationPtr->duration;
}

void cKF_SkeletonInfo_R_morphJoint(SkeletonInfoR* skeletonInfo) {
    // the current position of the joints
    s_xyz* joint = skeletonInfo->jointTable;
    // the animation's current position
    s_xyz* morph = skeletonInfo->morphTable;
    // Represents the position between joint 1 and joint 2 to interpolate.
    f32 parameter = !IS_ZERO(skeletonInfo->morphCounter) ? 1.0f / fabsf(skeletonInfo->morphCounter) : 0.0f;
    s_xyz jointTemp;
    s_xyz morphTemp;
    s_xyz temp_vec;
    s32 i;
    f32 new_var;
    f32 new_var2;

    // the first s_xyz is the root joint's translation
    cKF_SkeletonInfo_morphST((s16*)joint, (s16*)morph, parameter);

    joint++;
    morph++;

    for (i = 0; i < skeletonInfo->skeleton->numberOfJoints; i++) {
        jointTemp.x = joint->x;
        jointTemp.y = joint->y;
        jointTemp.z = joint->z;

        morphTemp.x = morph->x;
        morphTemp.y = morph->y;
        morphTemp.z = morph->z;

        if ((jointTemp.x != morphTemp.x) || (jointTemp.y != morphTemp.y) || (jointTemp.z != morphTemp.z)) {
            temp_vec.x = 0x7FFF + jointTemp.x;
            temp_vec.y = 0x7FFF - jointTemp.y;
            temp_vec.z = 0x7FFF + jointTemp.z;

            new_var = (fabsf(((f32)morphTemp.x) - jointTemp.x) + fabsf(((f32)morphTemp.y) - jointTemp.y)) +
                      fabsf(((f32)morphTemp.z) - jointTemp.z);
            new_var2 = (fabsf(((f32)morphTemp.x) - temp_vec.x) + fabsf(((f32)morphTemp.y) - temp_vec.y)) +
                       fabsf(((f32)morphTemp.z) - temp_vec.z);

            if (new_var < new_var2) {
                cKF_SkeletonInfo_subRotInterpolation(parameter, &joint->x, jointTemp.x, morphTemp.x);
                cKF_SkeletonInfo_subRotInterpolation(parameter, &joint->y, jointTemp.y, morphTemp.y);
                cKF_SkeletonInfo_subRotInterpolation(parameter, &joint->z, jointTemp.z, morphTemp.z);
            } else {
                cKF_SkeletonInfo_subRotInterpolation(parameter, &joint->x, temp_vec.x, morphTemp.x);
                cKF_SkeletonInfo_subRotInterpolation(parameter, &joint->y, temp_vec.y, morphTemp.y);
                cKF_SkeletonInfo_subRotInterpolation(parameter, &joint->z, temp_vec.z, morphTemp.z);
            }
        }
        morph++;
        joint++;
    }
}

/**
 * Advance the animation one frame and transform the joints accordingly.
 *
 * Joints can be animated in two ways, with keyframes or constant values. Which one a value uses is stored in
 * constKeyCheckBitTable. In this table, there is a byte for every joint, which is a bitfield. 1 is keyframe, 0 is
 * constant value. The 00111000 bits correspond to  that joint's x, y, or z translation. the 00000111 bits correspond to
 * that joint's x, y, or z rotation. Note that only the root joint can be translated.
 *
 * @return 0 if the animation is still playing. 1 if the animation has completed. 2 if the animation repeated.
 */
s32 cKF_SkeletonInfo_R_play(SkeletonInfoR* skeletonInfo) {
    s32 jointIndex;
    s32 componentIndex;
    u8* ckcbTable;
    s32 keyframeNumberIndex = 0;
    s32 constValueIndex = 0;
    s32 keyframeStartIndex = 0;
    s16* jointComponent =
        (!IS_ZERO(skeletonInfo->morphCounter)) ? (s16*)skeletonInfo->morphTable : (s16*)skeletonInfo->jointTable;
    s16* constValueTable;
    Keyframe* dataSource;
    s16* keyframeNumberTable;
    u32 ckcbIndex;
    s_xyz* joint;

    constValueTable = Lib_SegmentedToVirtual(skeletonInfo->animation->constValueTable);
    keyframeNumberTable = Lib_SegmentedToVirtual(skeletonInfo->animation->keyframeNumber);
    dataSource = Lib_SegmentedToVirtual(skeletonInfo->animation->dataSource);
    ckcbTable = Lib_SegmentedToVirtual(skeletonInfo->animation->constKeyCheckBitTable);

    // Translate the root joint.
    for (ckcbIndex = 0x20, componentIndex = 0; componentIndex < 3; componentIndex++) {

        if (*ckcbTable & ckcbIndex) {
            *jointComponent = cKF_KeyCalc(keyframeStartIndex, keyframeNumberTable[keyframeNumberIndex], dataSource,
                                          skeletonInfo->frameControl.currentFrame);
            keyframeStartIndex += keyframeNumberTable[keyframeNumberIndex];
            keyframeNumberIndex++;

        } else {
            *jointComponent = constValueTable[constValueIndex];
            constValueIndex++;
        }

        ckcbIndex >>= 1;
        jointComponent++;
    }

    // Rotate every joint.
    for (jointIndex = 0; jointIndex < skeletonInfo->skeleton->numberOfJoints; jointIndex++) {
        ckcbIndex = 4;
        for (componentIndex = 0; componentIndex < 3; componentIndex++) {

            if (ckcbTable[jointIndex] & ckcbIndex) {
                *jointComponent = cKF_KeyCalc(keyframeStartIndex, keyframeNumberTable[keyframeNumberIndex], dataSource,
                                              skeletonInfo->frameControl.currentFrame);
                keyframeStartIndex += keyframeNumberTable[keyframeNumberIndex];
                keyframeNumberIndex++;

            } else {
                *jointComponent = constValueTable[constValueIndex];
                constValueIndex++;
            }

            // Animations store angles in degrees * 10. These are converted to binary angles.
            *jointComponent = DEG_TO_BINANG(FMOD(*jointComponent * 0.1f, 360.0f));

            ckcbIndex >>= 1;
            jointComponent++;
        }
    }

    if (skeletonInfo->diffRotTable) {
        joint = (!IS_ZERO(skeletonInfo->morphCounter)) ? skeletonInfo->morphTable : skeletonInfo->jointTable;
        joint++;
        for (jointIndex = 0; jointIndex < skeletonInfo->skeleton->numberOfJoints; jointIndex++) {
            joint->x = joint->x + skeletonInfo->diffRotTable[jointIndex].x;
            joint->y = joint->y + skeletonInfo->diffRotTable[jointIndex].y;
            joint->z = joint->z + skeletonInfo->diffRotTable[jointIndex].z;
            joint++;
        }
    }

    // If the animation isn't using morph.
    if (IS_ZERO(skeletonInfo->morphCounter)) {
        return cKF_FrameControl_play(&skeletonInfo->frameControl);

    } else if (skeletonInfo->morphCounter > 0.0f) {
        // A positive morphCounter will wait to play the animation until the morph has finished.
        cKF_SkeletonInfo_R_morphJoint(skeletonInfo);

        skeletonInfo->morphCounter -= 1.0f;
        if (skeletonInfo->morphCounter <= 0.0f) {
            skeletonInfo->morphCounter = 0.0f;
        }
        return 0;

    } else {
        // A negative morphCounter will play the animation and morph at the same time.
        cKF_SkeletonInfo_R_morphJoint(skeletonInfo);

        skeletonInfo->morphCounter += 1.0f;
        if (skeletonInfo->morphCounter >= 0.0f) {
            skeletonInfo->morphCounter = 0.0f;
        }
        return cKF_FrameControl_play(&skeletonInfo->frameControl);
    }
}

/**
 * Draw a specified joint in a SkeletonInfo struct.
 *
 * This is a recursive function, that will call itself again for each child this joint has.
 *
 * Joints inherit the transformation of their parent joint. This is accomplished with a matrix stack, where each joint
 * pushes it's own transformation matrix onto the stack, and pops the matrix when there are no more children.
 *
 * Actors can override the drawing process with beforeCallback and afterCallback functions. One common example is to set
 * a specific joint's display list to null in order to make it invisible.
 *
 * @param jointIndex The index of the jointElem to draw.
 */
void cKF_Si3_draw_SV_R_child(Game_Play* game_play, SkeletonInfoR* skeletonInfo, s32* jointIndex,
                             DrawCallback beforeCallback, DrawCallback afterCallback, void* arg, Mtx** mtx) {
    JointElemR* jointElem = *jointIndex + (JointElemR*)Lib_SegmentedToVirtual(skeletonInfo->skeleton->jointElemTable);
    s32 i;
    Gfx* newDlist;
    Gfx* shape;
    u8 displayBufferFlag;
    s_xyz rotation;
    s_xyz* joint = &skeletonInfo->jointTable[*jointIndex];
    xyz_t translation;

    // if this is not the root joint.
    if (*jointIndex != 0) {
        translation.x = jointElem->translation.x;
        translation.y = jointElem->translation.y;
        translation.z = jointElem->translation.z;

    } else {
        s32 transformationFlag = skeletonInfo->animationMove.transformationFlag;
        xyz_t* baseTranslation = &skeletonInfo->animationMove.baseShapeTranslation;

        // Translate the root joint.
        // The AnimationMove struct can specify an override translation.
        if (transformationFlag & 1) {
            translation.x = baseTranslation->x;
            translation.z = baseTranslation->z;
        } else {
            translation.x = joint->x;
            translation.z = joint->z;
        }

        if (transformationFlag & 2) {
            translation.y = baseTranslation->y;
        } else {
            translation.y = joint->y;
        }
    }

    // jointIndex increases by 1 each recursive call, but because the root joint uses the first 2 s_xyz in jointTable,
    // the index of the current joint is actually jointIndex + 1.
    joint++;
    rotation = *joint;

    if (*jointIndex == 0) {
        s32 transformationFlag = skeletonInfo->animationMove.transformationFlag;

        if (transformationFlag & 4) {
            rotation.x = skeletonInfo->animationMove.baseShapeRotation.x;
            rotation.y = skeletonInfo->animationMove.updatedBaseShapeRotation.y;
            rotation.z = skeletonInfo->animationMove.updatedBaseShapeRotation.z;
        }
    }

    OPEN_DISPS(game_play->state.gfxCtx);
    Matrix_push();
    newDlist = shape = jointElem->shape;
    displayBufferFlag = jointElem->displayBufferFlag;

    if ((beforeCallback == NULL) ||
        (beforeCallback != NULL && beforeCallback(game_play, skeletonInfo, *jointIndex, &newDlist, &displayBufferFlag,
                                                  arg, &rotation, &translation) != NULL)) {
        Matrix_softcv3_mult(&translation, &rotation);

        if (newDlist != NULL) {
            _Matrix_to_Mtx(*mtx);

            if (displayBufferFlag & 1) {
                gSPMatrix(POLY_XLU_DISP++, *mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_XLU_DISP++, newDlist);
            } else {
                gSPMatrix(POLY_OPA_DISP++, *mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_OPA_DISP++, newDlist);
            }

            (*mtx)++;

        } else if (shape != NULL) {
            _Matrix_to_Mtx(*mtx);
            gSPMatrix(POLY_OPA_DISP++, *mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            (*mtx)++;
        }
    }

    if (afterCallback != NULL) {
        afterCallback(game_play, skeletonInfo, *jointIndex, &newDlist, &displayBufferFlag, arg, &rotation,
                      &translation);
    }

    (*jointIndex)++;

    for (i = 0; i < jointElem->numberOfChildren; i++) {
        cKF_Si3_draw_SV_R_child(game_play, skeletonInfo, jointIndex, beforeCallback, afterCallback, arg, mtx);
    }

    Matrix_pull();
    CLOSE_DISPS(game_play->state.gfxCtx);
}

/**
 * Draw all the joints in in a SkeletonInfo struct.
 *
 * This function calls cKF_Si3_draw_SV_R_child() to recursively draw each joint.
 */
void cKF_Si3_draw_R_SV(Game_Play* game_play, SkeletonInfoR* skeletonInfo, Mtx* mtx, DrawCallback beforeCallback,
                       DrawCallback afterCallback, void* arg) {
    s32 jointIndex;

    if (mtx != NULL) {
        OPEN_DISPS(game_play->state.gfxCtx);
        gSPSegment(POLY_OPA_DISP++, 0x0D, mtx);
        gSPSegment(POLY_XLU_DISP++, 0x0D, mtx);
        jointIndex = 0;
        cKF_Si3_draw_SV_R_child(game_play, skeletonInfo, &jointIndex, beforeCallback, afterCallback, arg, &mtx);
        CLOSE_DISPS(game_play->state.gfxCtx);
    }
}

void cKF_SkeletonInfo_R_init_standard_repeat_speedsetandmorph(SkeletonInfoR* skeletonInfo, BaseAnimationR* animation,
                                                              s_xyz* diffRotTable, f32 speed, f32 morphCounter) {
    BaseAnimationR* animationPtr = Lib_SegmentedToVirtual(animation);

    cKF_SkeletonInfo_R_init(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f, animationPtr->duration, 1.0f, speed,
                            morphCounter, ANIMATION_REPEAT, diffRotTable);
}

void cKF_SkeletonInfo_R_init_standard_repeat_setframeandspeedandmorph(SkeletonInfoR* skeletonInfo,
                                                                      BaseAnimationR* animation, s_xyz* diffRotTable,
                                                                      f32 currentFrame, f32 speed, f32 morphCounter) {
    BaseAnimationR* animationPtr = Lib_SegmentedToVirtual(animation);

    cKF_SkeletonInfo_R_init(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f, animationPtr->duration, currentFrame,
                            speed, morphCounter, ANIMATION_REPEAT, diffRotTable);
}

void cKF_SkeletonInfo_R_init_standard_setframeandspeedandmorphandmode(SkeletonInfoR* skeletonInfo,
                                                                      BaseAnimationR* animation, s_xyz* diffRotTable,
                                                                      f32 currentFrame, f32 speed, f32 morphCounter,
                                                                      AnimationMode mode) {
    BaseAnimationR* animationPtr = Lib_SegmentedToVirtual(animation);

    cKF_SkeletonInfo_R_init(skeletonInfo, skeletonInfo->skeleton, animation, 1.0f, animationPtr->duration, currentFrame,
                            speed, morphCounter, mode, diffRotTable);
}

void cKF_SkeletonInfo_R_init_reverse_setspeedandmorphandmode(SkeletonInfoR* skeletonInfo, BaseAnimationR* animation,
                                                             s_xyz* diffRotTable, f32 currentFrame, f32 speed,
                                                             AnimationMode mode) {
    cKF_SkeletonInfo_R_init(
        skeletonInfo, skeletonInfo->skeleton, animation, ((BaseAnimationR*)Lib_SegmentedToVirtual(animation))->duration,
        1.0f, ((BaseAnimationR*)Lib_SegmentedToVirtual(animation))->duration, currentFrame, speed, mode, diffRotTable);
}

void func_80053384_jp(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, UNK_PTR* arg6, UNK_PTR* arg7,
                      UNK_PTR* arg8) {
    if (arg3 != 0) {
        gSegments[arg0] = (uintptr_t)OS_K0_TO_PHYSICAL(arg6);
    }
    if (arg4 != 0) {
        gSegments[arg1] = (uintptr_t)OS_K0_TO_PHYSICAL(arg7);
    }
    if (arg5 != 0) {
        gSegments[arg2] = (uintptr_t)OS_K0_TO_PHYSICAL(arg8);
    }
}

void cKF_SkeletonInfo_R_combine_work_set(SkeletonInfoRCombineWork* combineWork, SkeletonInfoR* skeletonInfo) {
    combineWork->skeletonInfo = skeletonInfo;
    combineWork->constValueTable = Lib_SegmentedToVirtual(skeletonInfo->animation->constValueTable);
    combineWork->keyframeNumber = Lib_SegmentedToVirtual(skeletonInfo->animation->keyframeNumber);
    combineWork->dataSource = Lib_SegmentedToVirtual(skeletonInfo->animation->dataSource);
    combineWork->constKeyCheckBitTable = Lib_SegmentedToVirtual(skeletonInfo->animation->constKeyCheckBitTable);
    combineWork->keyframeNumberIndex = 0;
    combineWork->ckcbIndex = 0;
    combineWork->keyframeStartIndex = 0;
}

void cKF_SkeletonInfo_R_combine_translation(s16** joint, u32* flag, SkeletonInfoRCombineWork* combineWork, s8* arg3) {
    SkeletonInfoRCombineWork* temp_s1;
    SkeletonInfoRCombineWork* temp_s2;
    s32 i;

    temp_s1 = &combineWork[1];
    temp_s2 = &combineWork[2];
    for (i = 0; i < 3; i++) {
        switch (*arg3) {
            case 0:
                if (*combineWork[0].constKeyCheckBitTable & *flag) {
                    **joint =
                        cKF_KeyCalc(combineWork[0].keyframeStartIndex,
                                    combineWork[0].keyframeNumber[combineWork->keyframeNumberIndex],
                                    combineWork[0].dataSource, combineWork[0].skeletonInfo->frameControl.currentFrame);
                } else {
                    **joint = combineWork->constValueTable[combineWork->ckcbIndex];
                }
                break;

            case 1:
                if (*temp_s1->constKeyCheckBitTable & *flag) {
                    **joint =
                        cKF_KeyCalc(temp_s1->keyframeStartIndex, temp_s1->keyframeNumber[temp_s1->keyframeNumberIndex],
                                    temp_s1->dataSource, temp_s1->skeletonInfo->frameControl.currentFrame);
                } else {
                    **joint = temp_s1->constValueTable[temp_s1->ckcbIndex];
                }
                break;

            case 2:
                if (*temp_s2->constKeyCheckBitTable & *flag) {
                    **joint =
                        cKF_KeyCalc(temp_s2->keyframeStartIndex, temp_s2->keyframeNumber[temp_s2->keyframeNumberIndex],
                                    temp_s2->dataSource, temp_s2->skeletonInfo->frameControl.currentFrame);
                } else {
                    **joint = temp_s2->constValueTable[temp_s2->ckcbIndex];
                }
                break;
        }
        if (*combineWork[0].constKeyCheckBitTable & *flag) {
            combineWork->keyframeStartIndex += combineWork[0].keyframeNumber[combineWork->keyframeNumberIndex++];
        } else {
            combineWork->ckcbIndex += 1;
        }
        if (*temp_s1->constKeyCheckBitTable & *flag) {
            temp_s1->keyframeStartIndex += temp_s1->keyframeNumber[temp_s1->keyframeNumberIndex++];
        } else {
            temp_s1->ckcbIndex++;
        }
        if (*temp_s2->constKeyCheckBitTable & *flag) {
            temp_s2->keyframeStartIndex += temp_s2->keyframeNumber[temp_s2->keyframeNumberIndex++];
        } else {
            temp_s2->ckcbIndex += 1;
        }
        *flag >>= 1;
        (*joint)++;
    }
}

void cKF_SkeletonInfo_R_combine_rotation(s16** joint, u32* flag, SkeletonInfoRCombineWork* combineWork, s8* arg3) {
    SkeletonInfoRCombineWork* sp64;
    SkeletonInfoRCombineWork* temp_s0;
    SkeletonInfoRCombineWork* temp_s1;
    s32 i;
    s32 j;

    sp64 = combineWork;
    temp_s0 = &combineWork[1];
    temp_s1 = &combineWork[2];
    for (i = 0; i < sp64->skeletonInfo->skeleton->numberOfJoints; i++) {
        *flag = 4;
        for (j = 0; j < 3; j++) {
            switch (arg3[i + 1]) {
                case 0:
                    if (combineWork->constKeyCheckBitTable[i] & *flag) {
                        **joint =
                            cKF_KeyCalc(combineWork[0].keyframeStartIndex,
                                        combineWork->keyframeNumber[combineWork->keyframeNumberIndex],
                                        combineWork->dataSource, combineWork->skeletonInfo->frameControl.currentFrame);
                    } else {
                        **joint = combineWork->constValueTable[combineWork->ckcbIndex];
                    }
                    break;

                case 1:
                    if (temp_s0->constKeyCheckBitTable[i] & *flag) {
                        **joint = cKF_KeyCalc(temp_s0->keyframeStartIndex,
                                              temp_s0->keyframeNumber[temp_s0->keyframeNumberIndex],
                                              temp_s0->dataSource, temp_s0->skeletonInfo->frameControl.currentFrame);
                    } else {
                        **joint = temp_s0->constValueTable[temp_s0->ckcbIndex];
                    }
                    break;

                case 2:
                    if (temp_s1->constKeyCheckBitTable[i] & *flag) {
                        **joint = cKF_KeyCalc(temp_s1->keyframeStartIndex,
                                              temp_s1->keyframeNumber[temp_s1->keyframeNumberIndex],
                                              temp_s1->dataSource, temp_s1->skeletonInfo->frameControl.currentFrame);
                    } else {
                        **joint = temp_s1->constValueTable[temp_s1->ckcbIndex];
                    }
                    break;
            }
            if (combineWork->constKeyCheckBitTable[i] & *flag) {
                combineWork->keyframeStartIndex += combineWork->keyframeNumber[combineWork->keyframeNumberIndex++];
            } else {
                combineWork->ckcbIndex++;
            }
            if (temp_s0->constKeyCheckBitTable[i] & *flag) {
                temp_s0->keyframeStartIndex += temp_s0->keyframeNumber[temp_s0->keyframeNumberIndex++];
            } else {
                temp_s0->ckcbIndex++;
            }
            if (temp_s1->constKeyCheckBitTable[i] & *flag) {
                temp_s1->keyframeStartIndex += temp_s1->keyframeNumber[temp_s1->keyframeNumberIndex++];
            } else {
                temp_s1->ckcbIndex++;
            }
            **joint = DEG_TO_BINANG(FMOD(**joint * 0.1f, 360.0f));
            *flag >>= 1;
            *joint += 1;
        }
    }
}

s32 cKF_SkeletonInfo_R_combine_play(SkeletonInfoR* skeletonInfo1, SkeletonInfoR* skeletonInfo2, s32 arg2, s32 arg3,
                                    s32 arg4, s32 arg5, s8* flag) {
    s_xyz* var_v0;
    u32 spB0;
    s16* joint;
    SkeletonInfoRCombineWork combine1;
    SkeletonInfoRCombineWork combine2;
    SkeletonInfoRCombineWork combine3;
    s32 var_s0;
    UNK_PTR* sp44 = NULL;
    UNK_PTR* sp40 = NULL;
    s32 var_v1;

    if ((skeletonInfo1 == NULL) || (skeletonInfo2 == NULL) || (arg2 < 0) || (arg2 >= 0x10) || (arg3 < 0) ||
        (arg3 >= 0x10) || (flag == NULL)) {
        return 0;
    }

    joint = (!IS_ZERO(skeletonInfo1->morphCounter)) ? (s16*)skeletonInfo1->morphTable : (s16*)skeletonInfo1->jointTable;

    if (arg4 != 0) {
        sp44 = OS_PHYSICAL_TO_K0(gSegments[arg2]);
        gSegments[arg2] = (uintptr_t)OS_K0_TO_PHYSICAL(arg4);
        cKF_SkeletonInfo_R_combine_work_set(&combine3, skeletonInfo1);
    }

    if (arg5 != 0) {
        sp40 = OS_PHYSICAL_TO_K0(gSegments[arg3]);
        gSegments[arg3] = (uintptr_t)OS_K0_TO_PHYSICAL(arg5);
        cKF_SkeletonInfo_R_combine_work_set(&combine2, skeletonInfo2);
        cKF_SkeletonInfo_R_combine_work_set(&combine1, skeletonInfo2);
    }

    spB0 = 0x20;
    cKF_SkeletonInfo_R_combine_translation(&joint, &spB0, &combine3, flag);
    cKF_SkeletonInfo_R_combine_rotation(&joint, &spB0, &combine3, flag);

    if (skeletonInfo1->diffRotTable != NULL) {
        var_v0 = (!IS_ZERO(skeletonInfo1->morphCounter)) ? skeletonInfo1->morphTable : skeletonInfo1->jointTable;
        var_v0++;

        for (var_v1 = 0; var_v1 < skeletonInfo1->skeleton->numberOfJoints; var_v1++) {
            var_v0->x = var_v0->x + skeletonInfo1->diffRotTable[var_v1].x;
            var_v0->y = var_v0->y + skeletonInfo1->diffRotTable[var_v1].y;
            var_v0->z = var_v0->z + skeletonInfo1->diffRotTable[var_v1].z;
            var_v0++;
        }
    }
    if (IS_ZERO(skeletonInfo1->morphCounter)) {
        cKF_FrameControl_play(&skeletonInfo2->frameControl);
        var_s0 = cKF_FrameControl_play(&skeletonInfo1->frameControl);
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

        cKF_FrameControl_play(&skeletonInfo2->frameControl);
        var_s0 = cKF_FrameControl_play(&skeletonInfo1->frameControl);
        func_80053384_jp(arg2, arg3, 0, arg4, arg5, 0, sp44, sp40, 0);
    }
    return var_s0;
}

void cKF_SkeletonInfo_R_T_combine_play(s32* arg0, s32* arg1, s32* arg2, SkeletonInfoR* skeletonInfo1,
                                       SkeletonInfoR* skeletonInfo2, SkeletonInfoR* skeletonInfo3, s32 arg6, s32 arg7,
                                       s32 arg8, s32 arg9, s32 argA, s32 argB, s8* flag) {
    s32 i;
    u32 spB0;
    s16* spAC;
    SkeletonInfoRCombineWork sp8C;
    SkeletonInfoRCombineWork sp6C;
    SkeletonInfoRCombineWork sp4C;
    UNK_PTR* sp48 = NULL;
    UNK_PTR* sp44 = NULL;
    UNK_PTR* sp40 = NULL;
    s_xyz* var_v0;

    if ((skeletonInfo1 == NULL) || (skeletonInfo2 == NULL) || (skeletonInfo3 == NULL) || (arg6 < 0) || (arg6 >= 0x10) ||
        (arg7 < 0) || (arg7 >= 0x10) || (arg8 < 0) || (arg8 >= 0x10) || (flag == NULL)) {
        return;
    }

    spAC = (!IS_ZERO(skeletonInfo1->morphCounter)) ? (s16*)skeletonInfo1->morphTable : (s16*)skeletonInfo1->jointTable;

    if (arg9 != 0) {
        sp48 = OS_PHYSICAL_TO_K0(gSegments[arg6]);
        gSegments[arg6] = (uintptr_t)OS_K0_TO_PHYSICAL(arg9);
        cKF_SkeletonInfo_R_combine_work_set(&sp4C, skeletonInfo1);
    }
    if (argA != 0) {
        sp44 = OS_PHYSICAL_TO_K0(gSegments[arg7]);
        gSegments[arg7] = (uintptr_t)OS_K0_TO_PHYSICAL(argA);
        cKF_SkeletonInfo_R_combine_work_set(&sp6C, skeletonInfo2);
    }
    if (argB != 0) {
        sp40 = OS_PHYSICAL_TO_K0(gSegments[arg8]);
        gSegments[arg8] = (uintptr_t)OS_K0_TO_PHYSICAL(argB);
        cKF_SkeletonInfo_R_combine_work_set(&sp8C, skeletonInfo3);
    }

    spB0 = 0x20;
    cKF_SkeletonInfo_R_combine_translation(&spAC, &spB0, &sp4C, flag);
    cKF_SkeletonInfo_R_combine_rotation(&spAC, &spB0, &sp4C, flag);

    if (skeletonInfo1->diffRotTable != NULL) {
        var_v0 = (!IS_ZERO(skeletonInfo1->morphCounter)) ? skeletonInfo1->morphTable : skeletonInfo1->jointTable;
        var_v0++;

        for (i = 0; i < skeletonInfo1->skeleton->numberOfJoints; i++) {
            var_v0->x = var_v0->x + skeletonInfo1->diffRotTable[i].x;
            var_v0->y = var_v0->y + skeletonInfo1->diffRotTable[i].y;
            var_v0->z = var_v0->z + skeletonInfo1->diffRotTable[i].z;
            var_v0++;
        }
    }

    if (IS_ZERO(skeletonInfo1->morphCounter)) {
        *arg0 = cKF_FrameControl_play(&skeletonInfo1->frameControl);
        *arg1 = cKF_FrameControl_play(&skeletonInfo2->frameControl);
        *arg2 = cKF_FrameControl_play(&skeletonInfo3->frameControl);
    } else if (skeletonInfo1->morphCounter > 0.0f) {
        cKF_SkeletonInfo_R_morphJoint(skeletonInfo1);
        skeletonInfo1->morphCounter -= 1.0f;
        if (skeletonInfo1->morphCounter <= 0.0f) {
            skeletonInfo1->morphCounter = 0.0f;
        }
        *arg0 = 0;
        *arg1 = 0;
        *arg2 = 0;
    } else {
        cKF_SkeletonInfo_R_morphJoint(skeletonInfo1);
        skeletonInfo1->morphCounter += 1.0f;
        if (skeletonInfo1->morphCounter >= 0.0f) {
            skeletonInfo1->morphCounter = 0.0f;
        }
        *arg0 = cKF_FrameControl_play(&skeletonInfo1->frameControl);
        *arg1 = cKF_FrameControl_play(&skeletonInfo2->frameControl);
        *arg2 = cKF_FrameControl_play(&skeletonInfo3->frameControl);
    }
    func_80053384_jp(arg6, arg7, arg8, arg9, argA, argB, sp48, sp44, sp40);
}

void cKF_SkeletonInfo_R_Animation_Set_base_shape_trs(SkeletonInfoR* skeletonInfo, f32 translationX, f32 translationY,
                                                     f32 translationZ, s16 rotX, s16 rotY, s16 rotZ) {
    skeletonInfo->animationMove.baseShapeTranslation.x = translationX;
    skeletonInfo->animationMove.baseShapeTranslation.y = translationY;
    skeletonInfo->animationMove.baseShapeTranslation.z = translationZ;
    skeletonInfo->animationMove.updatedBaseShapeRotation.x = skeletonInfo->animationMove.baseShapeRotation.x = rotX;
    skeletonInfo->animationMove.updatedBaseShapeRotation.y = skeletonInfo->animationMove.baseShapeRotation.y = rotY;
    skeletonInfo->animationMove.updatedBaseShapeRotation.z = skeletonInfo->animationMove.baseShapeRotation.z = rotZ;
}

void cKF_SkeletonInfo_R_AnimationMove_ct_base(xyz_t* arg0, xyz_t* arg1, s16 arg2, s16 arg3, f32 arg4,
                                              SkeletonInfoR* skeletonInfo, s32 transformationFlag) {
    s32 var_v0;

    skeletonInfo->animationMove.transformationFlag = transformationFlag;
    skeletonInfo->animationMove.counter = ABS(arg4);
    skeletonInfo->animationMove.baseWorldPosition = ZeroVec;
    skeletonInfo->animationMove.shapeWorldPositionCorrection = ZeroVec;

    if (arg0 != NULL) {
        if (arg1 == NULL) {
            arg1 = arg0;
        }
        if (transformationFlag & 1) {
            skeletonInfo->animationMove.baseWorldPosition.x = arg1->x;
            skeletonInfo->animationMove.baseWorldPosition.z = arg1->z;
            skeletonInfo->animationMove.shapeWorldPositionCorrection.x = arg0->x - arg1->x;
            skeletonInfo->animationMove.shapeWorldPositionCorrection.z = arg0->z - arg1->z;
        }
        if (transformationFlag & 2) {
            skeletonInfo->animationMove.baseWorldPosition.y = arg1->y;
            skeletonInfo->animationMove.shapeWorldPositionCorrection.y = (f32)(arg0->y - arg1->y);
        }
    }
    skeletonInfo->animationMove.baseAngleY = arg3;
    skeletonInfo->animationMove.shapeAngleCorrection = 0;
    if (transformationFlag & 4) {
        var_v0 = arg2 - arg3;
        if (var_v0 > 0x8000) {
            var_v0 = -(0x10000 - var_v0);
        } else if (var_v0 < -0x8000) {
            var_v0 = var_v0 + 0x10000;
        }
        skeletonInfo->animationMove.shapeAngleCorrection = var_v0;
    }
}

void cKF_SkeletonInfo_R_AnimationMove_dt(SkeletonInfoR* skeletonInfo) {
    s32 transformationFlag = skeletonInfo->animationMove.transformationFlag;
    s_xyz* rootJointTranslation = &skeletonInfo->jointTable[0];
    xyz_t* baseShapeTranslation = &skeletonInfo->animationMove.baseShapeTranslation;

    if (transformationFlag & 1) {
        rootJointTranslation->x = baseShapeTranslation->x;
        rootJointTranslation->z = baseShapeTranslation->z;
    }
    if (transformationFlag & 2) {
        rootJointTranslation->y = baseShapeTranslation->y;
    }
    if (transformationFlag & 4) {
        s_xyz* rootJointRotation = &skeletonInfo->jointTable[1];

        rootJointRotation->x = skeletonInfo->animationMove.baseShapeRotation.x;
        rootJointRotation->y = skeletonInfo->animationMove.baseShapeRotation.y;
        rootJointRotation->z = skeletonInfo->animationMove.baseShapeRotation.z;
    }
    skeletonInfo->animationMove.transformationFlag = 0;
}

void cKF_SkeletonInfo_R_AnimationMove_base(xyz_t* arg0, s_xyz* arg1, xyz_t* arg2, s16 arg3,
                                           SkeletonInfoR* skeletonInfo) {
    u32 transformationFlag = skeletonInfo->animationMove.transformationFlag;
    f32 counter = skeletonInfo->animationMove.counter;
    f32 count;
    f32 var_ft4;

    count = counter + 1.0f;
    if (count > 1.0f) {
        var_ft4 = 1.0f / count;
    } else {
        var_ft4 = 0.0f;
    }

    if (transformationFlag & 4) {
        f32 temp6 = skeletonInfo->animationMove.shapeAngleCorrection;

        if (count > 1.0f) {
            temp6 *= var_ft4;
            skeletonInfo->animationMove.shapeAngleCorrection -= (s16)temp6;
        } else {
            skeletonInfo->animationMove.shapeAngleCorrection = 0;
        }
    }
    if (count > 1.0f) {
        if (transformationFlag & 1) {
            f32 posXTemp;
            f32 posZTemp;

            posXTemp = skeletonInfo->animationMove.shapeWorldPositionCorrection.x;
            posXTemp *= var_ft4;

            posZTemp = skeletonInfo->animationMove.shapeWorldPositionCorrection.z;
            posZTemp *= var_ft4;

            skeletonInfo->animationMove.shapeWorldPositionCorrection.x -= posXTemp;
            skeletonInfo->animationMove.shapeWorldPositionCorrection.z -= posZTemp;
        }
        if (transformationFlag & 2) {
            f32 posYTemp;

            posYTemp = skeletonInfo->animationMove.shapeWorldPositionCorrection.y;
            posYTemp *= var_ft4;

            skeletonInfo->animationMove.shapeWorldPositionCorrection.y -= posYTemp;
        }
    } else {
        skeletonInfo->animationMove.shapeWorldPositionCorrection.x = 0.0f;
        skeletonInfo->animationMove.shapeWorldPositionCorrection.y = 0.0f;
        skeletonInfo->animationMove.shapeWorldPositionCorrection.z = 0.0f;
    }

    if ((arg1 != NULL) && (transformationFlag & 4)) {
        s32 sp8C = skeletonInfo->animationMove.baseAngleY;
        s32 sp88 = skeletonInfo->animationMove.shapeAngleCorrection;
        s_xyz* sp28 = &skeletonInfo->animationMove.updatedBaseShapeRotation;
        s32 sp80 = skeletonInfo->animationMove.baseShapeRotation.x;
        s32 temp;

        Matrix_push();
        Matrix_rotateXYZ(skeletonInfo->jointTable[1].x, skeletonInfo->jointTable[1].y, skeletonInfo->jointTable[1].z,
                         0);
        Matrix_to_rotate2_new(get_Matrix_now(), sp28, 0);
        Matrix_pull();
        temp = sp28->x - sp80;
        arg1->x = (sp8C + sp88) + temp;
    }

    if (arg0 != NULL) {
        s_xyz* sp78 = skeletonInfo->jointTable;
        s16 var_a0 = 0;

        if (arg1 != NULL) {
            var_a0 = arg1->x - arg3;
        }

        if (transformationFlag & 1) {
            f32 baseTranslationXTemp = skeletonInfo->animationMove.baseShapeTranslation.x;
            f32 baseTranslationZTemp = skeletonInfo->animationMove.baseShapeTranslation.z;
            f32 sin1 = sin_s(var_a0);
            f32 cos1 = cos_s(var_a0);
            s32 pad[2] UNUSED;
            f32 move_x = arg2->x * (sp78->x - ((baseTranslationXTemp * cos1) + (baseTranslationZTemp * sin1)));
            f32 move_z = arg2->z * (sp78->z - ((-baseTranslationXTemp * sin1) + (baseTranslationZTemp * cos1)));
            f32 sin2 = sin_s(arg3);
            f32 cos2 = cos_s(arg3);
            f32 correctBaseWorldXTemp = skeletonInfo->animationMove.shapeWorldPositionCorrection.x;
            f32 correctBaseWorldZTemp = skeletonInfo->animationMove.shapeWorldPositionCorrection.z;
            s32 pad2[2] UNUSED;

            arg0->x = (skeletonInfo->animationMove.baseWorldPosition.x + correctBaseWorldXTemp) +
                      ((move_x * cos2) + (move_z * sin2));
            arg0->z = (skeletonInfo->animationMove.baseWorldPosition.z + correctBaseWorldZTemp) +
                      ((-move_x * sin2) + (move_z * cos2));
        }

        if (transformationFlag & 2) {
            f32 yTemp = skeletonInfo->animationMove.baseShapeTranslation.y;
            f32 temp3 = (arg2->y * (sp78->y - yTemp));
            f32 new_var = skeletonInfo->animationMove.shapeWorldPositionCorrection.y;

            arg0->y = (skeletonInfo->animationMove.baseWorldPosition.y + new_var) + temp3;
        }
    }
    counter -= 1.0f;

    if (counter < 0.0f) {
        counter = 0.0f;
    }

    skeletonInfo->animationMove.counter = counter;
}

void cKF_SkeletonInfo_R_AnimationMove_CulcTransToWorld(xyz_t* arg0, xyz_t* arg1, f32 arg2, f32 arg3, f32 arg4, s16 arg5,
                                                       xyz_t* arg6, SkeletonInfoR* skeleton, s32 arg8) {
    s_xyz* temp_v0 = &skeleton->jointTable[0];
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    f32 temp_fv0;

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
