#ifndef C_KEYFRAME_H
#define C_KEYFRAME_H

#include "ultra64.h"
#include "z64math.h"
#include "unk.h"

struct Game_Play;

typedef enum AnimationMode {
    /* 0 */ ANIMATION_STOP,
    /* 1 */ ANIMATION_REPEAT
} AnimationMode;

typedef struct FrameControl {
    /* 0x00 */ f32 start;
    /* 0x04 */ f32 end;
    /* 0x08 */ f32 duration;
    /* 0x0C */ f32 speed;
    /* 0x10 */ f32 currentFrame;
    /* 0x14 */ AnimationMode mode;
} FrameControl; // size = 0x18

typedef struct JointElemR {
    /* 0x0 */ Gfx* shape;
    /* 0x4 */ u8 numberOfChildren;
    /* 0x5 */ u8 displayBufferFlag;
    /* 0x6 */ s_xyz translation;
} JointElemR; // size = 0xC

typedef struct BaseSkeletonR {
    /* 0x00 */ u8 numberOfJoints;
    /* 0x01 */ u8 unk01;
    /* 0x04 */ JointElemR* jointElemTable;
} BaseSkeletonR; // size = 0x8

// original name unknown
typedef struct Keyframe {
    /* 0x00 */ s16 frame;
    /* 0x02 */ s16 value;
    /* 0x04 */ s16 velocity;
} Keyframe; // size = 0x06

typedef struct BaseAnimationR {
    /* 0x00 */ u8* constKeyCheckBitTable;
    /* 0x04 */ Keyframe* dataSource;
    /* 0x08 */ s16* keyframeNumber;
    /* 0x0C */ s16* constValueTable;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 duration;
} BaseAnimationR; // size = 0x14

typedef struct AnimationMove {
    /* 0x00 */ s32 transformationFlag;
    /* 0x04 */ xyz_t baseWorldPosition;
    /* 0x10 */ s16 baseAngleY;
    /* 0x14 */ xyz_t baseShapeTranslation;
    /* 0x20 */ s_xyz baseShapeRotation;
    /* 0x26 */ s_xyz updatedBaseShapeRotation;
    /* 0x2C */ f32 counter;
    /* 0x30 */ xyz_t shapeWorldPositionCorrection;
    /* 0x3C */ s16 shapeAngleCorrection;
} AnimationMove; // size = 0x40

typedef struct SkeletonInfoR {
    /* 0x00 */ FrameControl frameControl;
    /* 0x18 */ BaseSkeletonR* skeleton;
    /* 0x1C */ BaseAnimationR* animation;
    /* 0x20 */ f32 morphCounter;
    /* 0x24 */ s_xyz* jointTable;
    /* 0x28 */ s_xyz* morphTable;
    /* 0x2C */ s_xyz* diffRotTable;
    /* 0x30 */ AnimationMove animationMove;
} SkeletonInfoR; // size = 0x70

typedef struct SkeletonInfoRCombineWork {
    /* 0x00 */ SkeletonInfoR* skeletonInfo;
    /* 0x04 */ u8* constKeyCheckBitTable;
    /* 0x08 */ s16* constValueTable;
    /* 0x0C */ Keyframe* dataSource;
    /* 0x10 */ s16* keyframeNumber;
    /* 0x14 */ s32 keyframeNumberIndex;
    /* 0x18 */ s32 ckcbIndex;
    /* 0x1C */ s32 keyframeStartIndex;
} SkeletonInfoRCombineWork; // size = 0x20

typedef s32 (*DrawCallback)(struct Game_Play* game_play, SkeletonInfoR* skeletonInfo, s32 jointIndex, Gfx** dlist, u8* displayBufferFlag, void*, s_xyz* rotation, xyz_t* translation);

void cKF_FrameControl_zeroClear(FrameControl* frameControl);
void cKF_FrameControl_ct(FrameControl* frameControl);
void cKF_FrameControl_setFrame(FrameControl* frameControl, f32 start, f32 end, f32 duration, f32 currentFrame,
                               f32 speed, AnimationMode mode);
s32 cKF_FrameControl_passCheck(FrameControl* frameControl, f32 compareFrame, f32* remainder);
s32 cKF_FrameControl_passCheck_now(FrameControl* frameControl, f32 compareFrame);
s32 cKF_FrameControl_stop_proc(FrameControl* frameControl);
s32 cKF_FrameControl_repeat_proc(FrameControl* frameControl);
s32 cKF_FrameControl_play(FrameControl* frameControl);
f32 cKF_HermitCalc(f32 t, f32 duration, f32 p0, f32 p1, f32 v0, f32 v1);
s16 cKF_KeyCalc(s16 startIndex, s16 sequenceLength, Keyframe* dataSource, f32 currentFrame);
void cKF_SkeletonInfo_subRotInterpolation(f32 t, s16* out, s16 jointRotation, s16 morphRotation);
void cKF_SkeletonInfo_morphST(s16* joint, s16* morph, f32 t);
void cKF_SkeletonInfo_R_zeroClear(SkeletonInfoR* skeletonInfo);
void cKF_SkeletonInfo_R_ct(SkeletonInfoR* skeletonInfo, BaseSkeletonR* skeleton, BaseAnimationR* animation,
                           s_xyz* jointTable, s_xyz* morphTable);
void cKF_SkeletonInfo_R_dt(SkeletonInfoR* skeletonInfo);
void cKF_SkeletonInfo_R_init_standard_stop(SkeletonInfoR* skeletonInfo, BaseAnimationR* animation, s_xyz* diffRotTable);
void cKF_SkeletonInfo_R_init_standard_stop_speedset(SkeletonInfoR* skeletonInfo, BaseAnimationR* animation,
                                                    s_xyz* diffRotTable, f32 speed);
void cKF_SkeletonInfo_R_init_standard_stop_morph(SkeletonInfoR* skeletonInfo, BaseAnimationR* animation,
                                                 s_xyz* diffRotTable, f32 morphCounter);
void cKF_SkeletonInfo_R_init_standard_repeat(SkeletonInfoR* skeletonInfo, BaseAnimationR* animation,
                                             s_xyz* diffRotTable);
void cKF_SkeletonInfo_R_init_standard_repeat_speedset(SkeletonInfoR* skeletonInfo, BaseAnimationR* animation,
                                                      s_xyz* diffRotTable, f32 speed);
void cKF_SkeletonInfo_R_init_standard_repeat_morph(SkeletonInfoR* skeletonInfo, BaseAnimationR* animation,
                                                   s_xyz* diffRotTable, f32 morphCounter);
void cKF_SkeletonInfo_R_init(SkeletonInfoR* skeletonInfo, BaseSkeletonR* skeleton, BaseAnimationR* animation,
                             f32 startFrame, f32 endFrame, f32 currentFrame, f32 speed, f32 morphCounter,
                             AnimationMode mode, s_xyz* diffRotTable);
void cKF_SkeletonInfo_R_setAnim(SkeletonInfoR* skeletonInfo, BaseAnimationR* animation);
void cKF_SkeletonInfo_R_morphJoint(SkeletonInfoR* skeletonInfo);
s32 cKF_SkeletonInfo_R_play(SkeletonInfoR* skeletonInfo);
void cKF_Si3_draw_SV_R_child(struct Game_Play* game_play, SkeletonInfoR* skeletonInfo, s32* jointIndex,
                             DrawCallback beforeCallback, DrawCallback afterCallback, void* arg, Mtx** mtx);
void cKF_Si3_draw_R_SV(struct Game_Play* game_play, SkeletonInfoR* skeletonInfo, Mtx* mtx, DrawCallback beforeCallback,
                       DrawCallback afterCallback, void* arg);
void cKF_SkeletonInfo_R_init_standard_repeat_speedsetandmorph(SkeletonInfoR* skeletonInfo, BaseAnimationR* animation,
                                                              s_xyz* diffRotTable, f32 speed, f32 morphCounter);
void cKF_SkeletonInfo_R_init_standard_repeat_setframeandspeedandmorph(SkeletonInfoR* skeletonInfo,
                                                                      BaseAnimationR* animation, s_xyz* diffRotTable,
                                                                      f32 currentFrame, f32 speed, f32 morphCounter);
void cKF_SkeletonInfo_R_init_standard_setframeandspeedandmorphandmode(SkeletonInfoR* skeletonInfo,
                                                                      BaseAnimationR* animation, s_xyz* diffRotTable,
                                                                      f32 currentFrame, f32 speed, f32 morphCounter,
                                                                      AnimationMode mode);
void cKF_SkeletonInfo_R_init_reverse_setspeedandmorphandmode(SkeletonInfoR* skeletonInfo, BaseAnimationR* animation,
                                                             s_xyz* diffRotTable, f32 currentFrame, f32 speed,
                                                             AnimationMode mode);
void func_80053384_jp(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, UNK_PTR* arg6, UNK_PTR* arg7,
                      UNK_PTR* arg8);
void cKF_SkeletonInfo_R_combine_work_set(SkeletonInfoRCombineWork* combineWork, SkeletonInfoR* skeletonInfo);
void cKF_SkeletonInfo_R_combine_translation(s16** joint, u32* flag, SkeletonInfoRCombineWork* combineWork, s8* arg3);
void cKF_SkeletonInfo_R_combine_rotation(s16** joint, u32* flag, SkeletonInfoRCombineWork* combineWork, s8* arg3);
s32 cKF_SkeletonInfo_R_combine_play(SkeletonInfoR* skeletonInfo1, SkeletonInfoR* skeletonInfo2, s32 arg2, s32 arg3,
                                    s32 arg4, s32 arg5, s8* flag);
void cKF_SkeletonInfo_R_T_combine_play(s32* arg0, s32* arg1, s32* arg2, SkeletonInfoR* skeletonInfo1,
                                       SkeletonInfoR* skeletonInfo2, SkeletonInfoR* skeletonInfo3, s32 arg6, s32 arg7,
                                       s32 arg8, s32 arg9, s32 argA, s32 argB, s8* flag);
void cKF_SkeletonInfo_R_Animation_Set_base_shape_trs(SkeletonInfoR* skeletonInfo, f32 translationX, f32 translationY,
                                                     f32 translationZ, s16 rotX, s16 rotY, s16 rotZ);
void cKF_SkeletonInfo_R_AnimationMove_ct_base(xyz_t* arg0, xyz_t* arg1, s16 arg2, s16 arg3, f32 arg4,
                                              SkeletonInfoR* skeletonInfo, s32 transformationFlag);
void cKF_SkeletonInfo_R_AnimationMove_dt(SkeletonInfoR* skeletonInfo);
void cKF_SkeletonInfo_R_AnimationMove_base(xyz_t* arg0, s_xyz* arg1, xyz_t* arg2, s16 arg3,
                                           SkeletonInfoR* skeletonInfo);
void cKF_SkeletonInfo_R_AnimationMove_CulcTransToWorld(xyz_t* arg0, xyz_t* arg1, f32 arg2, f32 arg3, f32 arg4, s16 arg5,
                                                       xyz_t* arg6, SkeletonInfoR* skeleton, s32 arg8);

#endif
