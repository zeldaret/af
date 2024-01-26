#ifndef OBJECT_TOL_KEITAI_1_H
#define OBJECT_TOL_KEITAI_1_H

#include "gbi.h"
#include "c_keyframe.h"

/**
 * @file tol_keitai_1
 * 携帯 Cell Phone
 */

extern u8 cKF_ckcb_r_tol_keitai_1_keitai_off1_tbl[];
extern s16 cKF_kn_tol_keitai_1_keitai_off1_tbl[];
extern s16 cKF_c_tol_keitai_1_keitai_off1_tbl[];
extern Keyframe cKF_ds_tol_keitai_1_keitai_off1_tbl[];
extern BaseAnimationR cKF_ba_r_tol_keitai_1_keitai_off1;
extern u8 cKF_ckcb_r_tol_keitai_1_keitai_on1_tbl[];
extern s16 cKF_kn_tol_keitai_1_keitai_on1_tbl[];
extern s16 cKF_c_tol_keitai_1_keitai_on1_tbl[];
extern Keyframe cKF_ds_tol_keitai_1_keitai_on1_tbl[];
extern BaseAnimationR cKF_ba_r_tol_keitai_1_keitai_on1;
extern Vtx tol_keitai_1_v[];
extern Gfx main1_keitai1_model[];
extern Gfx main2_keitai1_model[];
extern unsigned short tol_keitai_1_pal[];
// 上裏 Top half back side
extern unsigned char tol_keitai_1_ueura1_tex_txt[];
// 上面 Top half front side
extern unsigned char tol_keitai_1_ueomote1_tex_txt[];
// 下裏 Bottom half back side
extern unsigned char tol_keitai_1_shitaura1_tex_txt[];
// 下面 Bottom half front side
extern unsigned char tol_keitai_1_shitaomote1_tex_txt[];
extern JointElemR cKF_je_r_tol_keitai_1_tbl[];
extern BaseSkeletonR cKF_bs_r_tol_keitai_1;

#endif
