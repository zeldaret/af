#ifndef C_KEYFRAME_H
#define C_KEYFRAME_H

#include "ultra64.h"
#include "z64math.h"

struct PlayState;

typedef enum AnimationMode { ANIMATION_STOP = 0, ANIMATION_REPEAT = 1} AnimationMode;

typedef struct {
    /* 0x00 */ f32 start;
    /* 0x04 */ f32 end;
    /* 0x08 */ f32 duration;
    /* 0x0C */ f32 speed;
    /* 0x10 */ f32 currentFrame;
    /* 0x14 */ s32 mode;
} FrameControl; // size = 0x18

typedef struct {
    /* 0x0 */ Gfx* shape;
    /* 0x4 */ u8 numberOfChildren;
    /* 0x5 */ u8 work_flag;
    /* 0x6 */ Vec3s trs;
} JointElemR; // size = 0xC

typedef struct {
    /* 0x00 */ u8 joint_num;
    /* 0x01 */ u8 display_joint_num;
    /* 0x04 */ JointElemR* jointElemTable;
} BaseSkeletonR; // size = 0x8

// original name unknown
typedef struct {
    /* 0x00 */ s16 frame;
    /* 0x02 */ s16 point;
    /* 0x04 */ s16 velocity;
} Keyframe; // size = 0x06

typedef struct {
    /* 0x00 */ u8* ConstKeyCheckBitTbl;
    /* 0x04 */ Keyframe* data_source;
    /* 0x08 */ s16* key_num;
    /* 0x0C */ s16* const_value_tbl;
    /* 0x10 */ s16 ext;
    /* 0x12 */ s16 duration;
} BaseAnimationR; // size = 0x14

typedef struct {
    /* 0x00 */ FrameControl frameControl;
    /* 0x18 */ BaseSkeletonR* skeleton;
    /* 0x1C */ BaseAnimationR* animation;
    /* 0x20 */ f32 morphCounter;
    /* 0x24 */ Vec3s* jointTable;
    /* 0x28 */ Vec3s* morphTable;
    /* 0x2C */ Vec3s* diffRotTable;
    /* 0x30 */ s32 move_flag;
    /* 0x34 */ Vec3f idle_world_pos;
    /* 0x40 */ s16 idle_set_angleY;
    /* 0x44 */ Vec3f base_shape_trs;
    /* 0x50 */ Vec3s base_data_angle;
    /* 0x56 */ Vec3s renew_base_data_angle;
    /* 0x5C */ f32 correct_counter;
    /* 0x60 */ Vec3f d_correct_base_world_pos;
    /* 0x6C */ s16 d_correct_base_set_angleY;
} SkeletonInfoR; // size = 0x70

typedef struct {
    /* 0x00 */ SkeletonInfoR* skeletonInfo;
    /* 0x04 */ u8* anm_check_bit_tbl;
    /* 0x08 */ s16* anm_const_val_tbl;
    /* 0x0C */ Keyframe* anm_data_src;
    /* 0x10 */ s16* anm_key_num;
    /* 0x14 */ s32 anm_key_num_idx;
    /* 0x18 */ s32 anm_const_val_tbl_idx;
    /* 0x1C */ s32 anm_data_src_idx;
} SkeletonInfoRCombineWork; // size = 0x20

typedef int (*DrawCallback)(struct PlayState*, SkeletonInfoR*, int, Gfx**, u8*, void*, Vec3s*, Vec3f*);

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
// void cKF_SkeletonInfo_subRotInterpolation(f32 t, s16* out, s16 rot1, s16 rot2);
// void cKF_SkeletonInfo_morphST(s16 arg0[3], s16 arg1[3], f32 arg3);
void cKF_SkeletonInfo_R_zeroClear(SkeletonInfoR* skeletonInfo);
void cKF_SkeletonInfo_R_dt(SkeletonInfoR* skeletonInfo);
void cKF_SkeletonInfo_R_init_standard_stop(SkeletonInfoR* skeletonInfo, BaseAnimationR* animation, Vec3s* diffRotTable);
void cKF_SkeletonInfo_R_init_standard_stop_speedset(SkeletonInfoR* skeletonInfo, BaseAnimationR* animation,
                                                    Vec3s* diffRotTable, f32 speed);
void cKF_SkeletonInfo_R_init_standard_stop_morph(SkeletonInfoR* skeletonInfo, BaseAnimationR* animation,
                                                 Vec3s* diffRotTable, f32 morphCounter);
void cKF_SkeletonInfo_R_init_standard_repeat(SkeletonInfoR* skeletonInfo, BaseAnimationR* animation,
                                             Vec3s* diffRotTable);
void cKF_SkeletonInfo_R_init_standard_repeat_speedset(SkeletonInfoR* skeletonInfo, BaseAnimationR* animation,
                                                      Vec3s* diffRotTable, f32 speed);
void cKF_SkeletonInfo_R_init_standard_repeat_morph(SkeletonInfoR* skeletonInfo, BaseAnimationR* animation,
                                                   Vec3s* diffRotTable, f32 morphCounter);
void cKF_SkeletonInfo_R_init(SkeletonInfoR* skeletonInfo, BaseSkeletonR* skeleton, BaseAnimationR* animation,
                             f32 startFrame, f32 endFrame, f32 currentFrame, f32 speed, f32 morphCounter,
                             AnimationMode mode, Vec3s* diffRotTable);
void cKF_SkeletonInfo_R_setAnim(SkeletonInfoR* skeletonInfo, BaseAnimationR* animation);
void cKF_SkeletonInfo_R_morphJoint(SkeletonInfoR* skeletonInfo);
s32 cKF_SkeletonInfo_R_play(SkeletonInfoR* skeletonInfo);
void cKF_Si3_draw_SV_R_child(struct PlayState* play, SkeletonInfoR* skeletonInfo, s32* jointIndex,
                             DrawCallback beforeCallback, DrawCallback afterCallback, void* arg, Mtx** mtx);
void cKF_Si3_draw_R_SV(struct PlayState* play, SkeletonInfoR* skeletonInfo, Mtx* mtx, DrawCallback beforeCallback,
                       DrawCallback afterCallback, void* arg);
void cKF_SkeletonInfo_R_init_standard_repeat_speedsetandmorph(SkeletonInfoR* skeletonInfo, BaseAnimationR* animation,
                                                              Vec3s* diffRotTable, f32 speed, f32 morphCounter);
void cKF_SkeletonInfo_R_init_standard_repeat_setframeandspeedandmorph(SkeletonInfoR* skeletonInfo,
                                                                      BaseAnimationR* animation, Vec3s* diffRotTable,
                                                                      f32 currentFrame, f32 speed, f32 morphCounter);
void cKF_SkeletonInfo_R_init_standard_setframeandspeedandmorphandmode(SkeletonInfoR* skeletonInfo,
                                                                      BaseAnimationR* animation, Vec3s* diffRotTable,
                                                                      f32 currentFrame, f32 speed, f32 morphCounter,
                                                                      AnimationMode mode);
void cKF_SkeletonInfo_R_init_reverse_setspeedandmorphandmode(SkeletonInfoR* skeletonInfo, BaseAnimationR* animation,
                                                             Vec3s* diffRotTable, f32 currentFrame, f32 speed,
                                                             AnimationMode mode);
// void func_80053384_jp(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, UNK_TYPE* arg6, UNK_TYPE* arg7,
//                       UNK_TYPE* arg8);
void cKF_SkeletonInfo_R_combine_work_set(SkeletonInfoRCombineWork* combineWork, SkeletonInfoR* skeletonInfo);
// void cKF_SkeletonInfo_R_combine_translation(s16** joint, u32* flag, SkeletonInfoRCombineWork* combineWork, s8* arg3);
// void cKF_SkeletonInfo_R_combine_rotation(s16** joint, u32* flag, SkeletonInfoRCombineWork* combineWork, s8* arg3);
// s32 cKF_SkeletonInfo_R_combine_play(SkeletonInfoR* skeletonInfo1, SkeletonInfoR* skeletonInfo2, s32 arg2, s32 arg3,
//                                     s32 arg4, s32 arg5, s8* flag);
// void cKF_SkeletonInfo_R_T_combine_play(s32* arg0, s32* arg1, s32* arg2, SkeletonInfoR* skeletonInfo1,
//                                        SkeletonInfoR* skeletonInfo2, SkeletonInfoR* skeletonInfo3, s32 arg6, s32
//                                        arg7, s32 arg8, s32 arg9, s32 argA, s32 argB, s8* flag);
// void cKF_SkeletonInfo_R_Animation_Set_base_shape_trs(SkeletonInfoR* skeletonInfo, f32 arg1, f32 arg2, f32 arg3,
//                                                      s16 arg4, s16 arg5, s16 arg6);
// void cKF_SkeletonInfo_R_AnimationMove_ct_base(Vec3f* arg0, Vec3f* arg1, s16 arg2, s16 arg3, f32 arg4,
//                                               SkeletonInfoR* skeletonInfo, s32 arg6);
// void cKF_SkeletonInfo_R_AnimationMove_dt(SkeletonInfoR* skeletonInfo);
// void cKF_SkeletonInfo_R_AnimationMove_base(Vec3f* arg0, Vec3s* arg1, Vec3f* arg2, s16 arg3,
//                                            SkeletonInfoR* skeletonInfo);
// void cKF_SkeletonInfo_R_AnimationMove_CulcTransToWorld(Vec3f* arg0, Vec3f* arg1, f32 arg2, f32 arg3, f32 arg4, s16
// arg5,
//                                                        Vec3f* arg6, SkeletonInfoR* skeleton, s32 arg8);

#endif
