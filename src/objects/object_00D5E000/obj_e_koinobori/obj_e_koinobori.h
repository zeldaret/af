#ifndef OBJECT_OBJ_E_KOINOBORI_H
#define OBJECT_OBJ_E_KOINOBORI_H

#include "gbi.h"
#include "c_keyframe.h"

/**
 * @file obj_e_koinobori
 * 鯉幟 Carp streamers for Children's Day
 */

extern Vtx obj_e_koinobori_v[];
extern Gfx obj_e_koinobori_pole_1_model[];
extern Gfx obj_e_koinobori_rope_model[];
// 真鯉 Black Carp
extern Gfx obj_e_koinobori_magoiA_model[];
extern Gfx obj_e_koinobori_magoiB_model[];
extern Gfx obj_e_koinobori_magoiC_model[];
// 緋鯉 Red Carp
extern Gfx obj_e_koinobori_higoiA_model[];
extern Gfx obj_e_koinobori_higoiB_model[];
extern Gfx obj_e_koinobori_higoiC_model[];
// 吹き流し Colored Strips
extern Gfx obj_e_koinobori_fukiA_model[];
extern Gfx obj_e_koinobori_fukiB_model[];
extern Gfx obj_e_koinobori_fukiC_model[];
// 矢車 Spinning wheel at the top of the pole
extern Gfx obj_e_koinobori_yaguruma_model[];
extern unsigned char obj_e_koinobori_t1_tex_txt[];
extern unsigned char obj_e_koinobori_t3_tex_txt[];
extern JointElemR cKF_je_r_obj_e_koinobori_tbl[];
extern BaseSkeletonR cKF_bs_r_obj_e_koinobori;
extern u8 cKF_ckcb_r_obj_e_koinobori_tbl[];
extern s16 cKF_kn_obj_e_koinobori_tbl[];
extern s16 cKF_c_obj_e_koinobori_tbl[];
extern Keyframe cKF_ds_obj_e_koinobori_tbl[];
extern BaseAnimationR cKF_ba_r_obj_e_koinobori;

#endif
