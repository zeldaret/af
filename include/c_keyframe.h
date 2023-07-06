#ifndef C_KEYFRAME_H
#define C_KEYFRAME_H

#include "ultra64.h"
#include "z64math.h"

struct PlayState;
struct GameState;
struct cKF_SkeletonInfo_c;

typedef enum cKF_FC_Mode { cKF_FC_STOP = 0, cKF_FC_REPEAT = 1, cKF_FC_LAST_INDEX = 2 } cKF_FC_Mode;

typedef struct {
    /* 0x00 */ f32 start;
    /* 0x04 */ f32 end;
    /* 0x08 */ f32 duration;
    /* 0x0C */ f32 speed;
    /* 0x10 */ f32 current;
    /* 0x14 */ s32 mode;
} cKF_FrameControl_c; // size = 0x18

typedef struct {
    /* 0x0 */ Gfx *shape;
    /* 0x4 */ u8 child;
    /* 0x5 */ u8 work_flag;
    /* 0x6 */ u8 func_index;
} cKF_JointElem_c; // size = 0x8

typedef struct {
    /* 0x0 */ Gfx *shape;
    /* 0x4 */ u8 child;
    /* 0x5 */ u8 work_flag;
    /* 0x6 */ Vec3s trs;
} cKF_JointElem_R_c; // size = 0xC

typedef struct {
    /* 0x00 */ u8 joint_num;
    /* 0x01 */ u8 display_joint_num;
    /* 0x04 */ cKF_JointElem_c *joint_tbl;
} cKF_BaseSkeleton_c; // size = 0x8

typedef struct {
    /* 0x00 */ u8 joint_num;
    /* 0x01 */ u8 display_joint_num;
    /* 0x04 */ cKF_JointElem_R_c *joint_tbl;
} cKF_BaseSkeleton_R_c; // size = 0x8

// unknown original name
typedef struct {
    /* 0x00 */ s16 frame;
    /* 0x02 */ s16 point;
    /* 0x04 */ s16 velocity;
} Keyframe; // size = 0x06

typedef struct {
    /* 0x00 */ u8 *ConstKeyCheckBitTbl;
    /* 0x04 */ Keyframe *data_source;
    /* 0x08 */ s16 *key_num;
    /* 0x0C */ s16 *const_value_tbl;
    /* 0x10 */ s16 ext;
    /* 0x12 */ s16 duration;
} cKF_BaseAnimation_c; // size = 0x14

typedef struct {
    /* 0x00 */ u8 *ConstKeyCheckBitTbl;
    /* 0x04 */ Keyframe *data_source;
    /* 0x08 */ s16 *key_num;
    /* 0x0C */ s16 *const_value_tbl;
    /* 0x10 */ s16 ext;
    /* 0x12 */ s16 duration;
} cKF_BaseAnimation_R_c; // size = 0x14

typedef int (*BEFORE_FUNC_TBL)(struct GameState *, struct cKF_SkeletonInfo_c *, int, Gfx **, u8 *, void *);

typedef struct {
    /* 0x00 */ cKF_FrameControl_c frameCtrl;
    /* 0x18 */ cKF_BaseSkeleton_c *skeleton;
    /* 0x1C */ cKF_BaseAnimation_c *animation;
    /* 0x20 */ BEFORE_FUNC_TBL before_func_tbl;
    /* 0x24 */ f32 morphCounter;
    /* 0x28 */ Vec3s *now_joint;
    /* 0x2C */ Vec3s *morph_joint;
} cKF_SkeletonInfo_c; // size = 0x30

typedef struct {
    /* 0x00 */ cKF_FrameControl_c frameCtrl;
    /* 0x18 */ cKF_BaseSkeleton_R_c *skeleton;
    /* 0x1C */ cKF_BaseAnimation_R_c *animation;
    /* 0x20 */ f32 morphCounter;
    /* 0x24 */ Vec3s *now_joint;
    /* 0x28 */ Vec3s *morph_joint;
    /* 0x2C */ Vec3s *diff_rot_tbl;
    /* 0x30 */ s32 move_flag;
    /* 0x34 */ Vec3f idle_world_pos;
    /* 0x40 */ s16 idle_set_angleY;
    /* 0x44 */ Vec3f base_shape_trs;
    /* 0x50 */ Vec3s base_data_angle;
    /* 0x56 */ Vec3s renew_base_data_angle;
    /* 0x5C */ f32 correct_counter;
    /* 0x60 */ Vec3f d_correct_base_world_pos;
    /* 0x6C */ s16 d_correct_base_set_angleY;
} cKF_SkeletonInfo_R_c; // size = 0x70

typedef struct {
    /* 0x00 */ cKF_SkeletonInfo_R_c *skeletonInfo;
    /* 0x04 */ u8 *anm_check_bit_tbl;
    /* 0x08 */ s16 *anm_const_val_tbl;
    /* 0x0C */ Keyframe *anm_data_src;
    /* 0x10 */ s16 *anm_key_num;
    /* 0x14 */ s32 anm_key_num_idx;
    /* 0x18 */ s32 anm_const_val_tbl_idx;
    /* 0x1C */ s32 anm_data_src_idx;
} cKF_SkeletonInfo_R_combine_work_c; // size = 0x20

typedef int (*cKF_draw_callback)(struct PlayState *, cKF_SkeletonInfo_R_c *, int, Gfx **, u8 *, void *, Vec3s *, Vec3f *);

void cKF_FrameControl_zeroClear(cKF_FrameControl_c *frameCtrl);
void cKF_FrameControl_ct(cKF_FrameControl_c *frameCtrl);
void cKF_FrameControl_setFrame(cKF_FrameControl_c *frameCtrl, f32 start, f32 end, f32 duration, f32 current, f32 speed,
                               s32 mode);
s32 cKF_FrameControl_passCheck(cKF_FrameControl_c *frameCtrl, f32 compareFrame, f32 *remainder);
s32 cKF_FrameControl_passCheck_now(cKF_FrameControl_c *frameCtrl, f32 compareFrame);
s32 cKF_FrameControl_stop_proc(cKF_FrameControl_c *frameCtrl);
s32 cKF_FrameControl_repeat_proc(cKF_FrameControl_c *frameCtrl);
s32 cKF_FrameControl_play(cKF_FrameControl_c *frameCtrl);
f32 cKF_HermitCalc(f32 t, f32 duration, f32 p0, f32 p1, f32 v0, f32 v1);
s16 cKF_KeyCalc(s16 startIndex, s16 sequenceLength, Keyframe *dataSource, f32 currentFrame);
void cKF_SkeletonInfo_subRotInterpolation(f32 t, s16 *out, s16 rot1, s16 rot2);
void cKF_SkeletonInfo_morphST(s16 arg0[3], s16 arg1[3], f32 arg3);
void cKF_SkeletonInfo_R_zeroClear(cKF_SkeletonInfo_R_c *skeletonInfo);
void cKF_SkeletonInfo_R_ct(cKF_SkeletonInfo_R_c *skeletonInfo, cKF_BaseSkeleton_R_c *skeleton,
                           cKF_BaseAnimation_R_c *animation, Vec3s *now_joint, Vec3s *morph_joint);
void cKF_SkeletonInfo_R_dt(cKF_SkeletonInfo_R_c *skeletonInfo);
void cKF_SkeletonInfo_R_init_standard_stop(cKF_SkeletonInfo_R_c *skeletonInfo, cKF_BaseAnimation_R_c *animation,
                                           Vec3s *diff_rot_tbl);
void cKF_SkeletonInfo_R_init_standard_stop_speedset(cKF_SkeletonInfo_R_c *skeletonInfo,
                                                    cKF_BaseAnimation_R_c *animation, Vec3s *diff_rot_tbl,
                                                    f32 frameSpeed);
void cKF_SkeletonInfo_R_init_standard_stop_morph(cKF_SkeletonInfo_R_c *skeletonInfo, cKF_BaseAnimation_R_c *animation,
                                                 Vec3s *diff_rot_tbl, f32 morphCounter);
void cKF_SkeletonInfo_R_init_standard_repeat(cKF_SkeletonInfo_R_c *skeletonInfo, cKF_BaseAnimation_R_c *animation,
                                             Vec3s *diff_rot_tbl);
void cKF_SkeletonInfo_R_init_standard_repeat_speedset(cKF_SkeletonInfo_R_c *skeletonInfo,
                                                      cKF_BaseAnimation_R_c *animation, Vec3s *diff_rot_tbl,
                                                      f32 frameSpeed);
void cKF_SkeletonInfo_R_init_standard_repeat_morph(cKF_SkeletonInfo_R_c *skeletonInfo, cKF_BaseAnimation_R_c *animation,
                                                   Vec3s *diff_rot_tbl, f32 morphCounter);
void cKF_SkeletonInfo_R_init(cKF_SkeletonInfo_R_c *skeletonInfo, cKF_BaseSkeleton_R_c *skeleton, cKF_BaseAnimation_R_c *animation,
                             f32 startFrame, f32 endFrame, f32 frameCurrent, f32 frameSpeed, f32 morphCounter,
                             s32 frameMode, Vec3s *diff_rot_tbl);
void cKF_SkeletonInfo_R_setAnim(cKF_SkeletonInfo_R_c *skeletonInfo, cKF_BaseAnimation_R_c *animation);
void cKF_SkeletonInfo_R_morphJoint(cKF_SkeletonInfo_R_c *skeletonInfo);
s32 cKF_SkeletonInfo_R_play(cKF_SkeletonInfo_R_c *skeletonInfo);
void cKF_Si3_draw_SV_R_child(struct PlayState *play, cKF_SkeletonInfo_R_c *skeletonInfo, s32 *joint_num,
                             cKF_draw_callback prerender_callback, cKF_draw_callback postrender_callback, void *arg,
                             Mtx **mtxpp);
void cKF_Si3_draw_R_SV(struct PlayState *play, cKF_SkeletonInfo_R_c *skeletonInfo, Mtx *mtxp,
                       cKF_draw_callback prerender_callback, cKF_draw_callback postrender_callback, void *arg);
void cKF_SkeletonInfo_R_init_standard_repeat_speedsetandmorph(cKF_SkeletonInfo_R_c *skeletonInfo, cKF_BaseAnimation_R_c *animation,
                                                              Vec3s *arg2, f32 arg3, f32 arg4);
void cKF_SkeletonInfo_R_init_standard_repeat_setframeandspeedandmorph(cKF_SkeletonInfo_R_c *skeletonInfo,
                                                                      cKF_BaseAnimation_R_c *animation, Vec3s *arg2, f32 arg3,
                                                                      f32 arg4, f32 arg5);
void cKF_SkeletonInfo_R_init_standard_setframeandspeedandmorphandmode(cKF_SkeletonInfo_R_c *skeletonInfo,
                                                                      cKF_BaseAnimation_R_c *animation, Vec3s *arg2, f32 arg3,
                                                                      f32 arg4, f32 arg5, s32 arg6);
void cKF_SkeletonInfo_R_init_reverse_setspeedandmorphandmode(cKF_SkeletonInfo_R_c *skeletonInfo, cKF_BaseAnimation_R_c *animation,
                                                             Vec3s *arg2, f32 arg3, f32 arg4, s32 arg5);
void func_80053384_jp(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);
void cKF_SkeletonInfo_R_combine_work_set(cKF_SkeletonInfo_R_combine_work_c *combine, cKF_SkeletonInfo_R_c *skeleton);
void cKF_SkeletonInfo_R_combine_translation(s16 **joint, u32 *flag, cKF_SkeletonInfo_R_combine_work_c *combine, s8 *arg3);
void cKF_SkeletonInfo_R_combine_rotation(s16 **joint, u32 *flag, cKF_SkeletonInfo_R_combine_work_c *combine, s8 *arg3);
s32 cKF_SkeletonInfo_R_combine_play(cKF_SkeletonInfo_R_c *arg0, cKF_SkeletonInfo_R_c *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
                                    s8 *arg6);
// void func_80053EF8_jp();
void cKF_SkeletonInfo_R_Animation_Set_base_shape_trs(cKF_SkeletonInfo_R_c *skeletonInfo, f32 arg1, f32 arg2, f32 arg3,
                                                     s16 arg4, s16 arg5, s16 arg6);
void cKF_SkeletonInfo_R_AnimationMove_ct_base(Vec3f *arg0, Vec3f *arg1, s16 arg2, s16 arg3, f32 arg4,
                                              cKF_SkeletonInfo_R_c *skeletonInfo, s32 arg6);
void cKF_SkeletonInfo_R_AnimationMove_dt(cKF_SkeletonInfo_R_c *skeletonInfo);
void cKF_SkeletonInfo_R_AnimationMove_base(Vec3f *arg0, s16 *arg1, Vec3f *arg2, s16 arg3, cKF_SkeletonInfo_R_c *skeletonInfo);
void cKF_SkeletonInfo_R_AnimationMove_CulcTransToWorld(Vec3f *arg0, Vec3f *arg1, f32 arg2, f32 arg3, f32 arg4, s16 arg5,
                                                       Vec3f *arg6, cKF_SkeletonInfo_R_c *skeleton, s32 arg8);

#endif
