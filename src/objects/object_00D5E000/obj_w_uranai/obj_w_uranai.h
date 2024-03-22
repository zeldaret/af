#ifndef OBJECT_OBJ_W_URANAI_H
#define OBJECT_OBJ_W_URANAI_H

#include "gbi.h"
#include "c_keyframe.h"

/**
 * @file obj_w_uranai
 * 占い Katrina's tent (winter)
 */

extern Vtx obj_w_uranai_v[];
extern Gfx obj_w_uranai_window_model[];
extern Gfx obj_w_uranai_t2_model[];
extern Gfx obj_w_uranai_t1_model[];
extern Gfx obj_w_uranai_light_model[];
extern Gfx obj_w_uranai_doorA_model[];
extern Gfx obj_w_uranai_doorB_model[];
extern u8 obj_w_uranai_t2_tex_txt[];
extern u8 obj_w_uranai_window_tex_txt[];
extern u8 obj_w_uranai_t1_tex_txt[];
extern JointElemR cKF_je_r_obj_w_uranai_tbl[];
extern BaseSkeletonR cKF_bs_r_obj_w_uranai;
extern u8 cKF_ckcb_r_obj_w_uranai_tbl[];
extern s16 cKF_kn_obj_w_uranai_tbl[];
extern s16 cKF_c_obj_w_uranai_tbl[];
extern Keyframe cKF_ds_obj_w_uranai_tbl[];
extern BaseAnimationR cKF_ba_r_obj_w_uranai;

#endif
