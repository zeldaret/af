#ifndef OBJECT_OBJ_LOTUS_H
#define OBJECT_OBJ_LOTUS_H

#include "gbi.h"
#include "c_keyframe.h"

/**
 * @file obj_lotus
 * Lotus flower that floats in the town lake
 */

extern Vtx obj_s_lotus_v[];
extern Gfx obj_s_lotus_flower1_model[];
extern Gfx obj_s_lotus_leafH_model[];
extern Gfx obj_s_lotus_leafG_model[];
extern Gfx obj_s_lotus_leafF_model[];
extern Gfx obj_s_lotus_leafE_model[];
extern Gfx obj_s_lotus_leafD_model[];
extern Gfx obj_s_lotus_leafC_model[];
extern Gfx obj_s_lotus_leafB_model[];
extern Gfx obj_s_lotus_leafA_model[];
extern u8 obj_lotus_flower_tex_txt[];
extern u8 obj_lotus_leaf_tex_txt[];
extern JointElemR cKF_je_r_obj_s_lotus_tbl[];
extern BaseSkeletonR cKF_bs_r_obj_s_lotus;
extern u8 cKF_ckcb_r_obj_s_lotus_tbl[];
extern s16 cKF_kn_obj_s_lotus_tbl[];
extern s16 cKF_c_obj_s_lotus_tbl[];
extern Keyframe cKF_ds_obj_s_lotus_tbl[];
extern BaseAnimationR cKF_ba_r_obj_s_lotus;

#endif
