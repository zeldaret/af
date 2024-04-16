#ifndef OBJECT_ACT_BALLOON_H
#define OBJECT_ACT_BALLOON_H

#include "gbi.h"
#include "c_keyframe.h"

extern Vtx act_balloon_v[];
extern Gfx act_balloon_head_model[];
extern Gfx act_balloon_wireB_model[];
extern Gfx act_balloon_wireA_model[];
extern u8 act_balloon_wire_tex_txt[];
extern u16 act_balloon_head_tex_rgb_ia16[];
extern u8 cKF_ckcb_r_act_balloon_tbl[];
extern s16 cKF_kn_act_balloon_tbl[];
extern s16 cKF_c_act_balloon_tbl[];
extern Keyframe cKF_ds_act_balloon_tbl[];
extern BaseAnimationR cKF_ba_r_act_balloon;
extern JointElemR cKF_je_r_act_balloon_tbl[];
extern BaseSkeletonR cKF_bs_r_act_balloon;

#endif
