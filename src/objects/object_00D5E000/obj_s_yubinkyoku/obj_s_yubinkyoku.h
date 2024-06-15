#ifndef OBJECT_OBJ_S_YUBINKYOKU_H
#define OBJECT_OBJ_S_YUBINKYOKU_H

#include "gbi.h"
#include "c_keyframe.h"

/**
 * @file obj_w_yubinkyouku
 * 郵便局 Post Office (non winter)
 */

extern Vtx obj_s_yubinkyoku_v[];
extern Gfx obj_s_yubinkyoku_window_model[];
extern Gfx obj_s_yubinkyoku_t3_1_model[];
extern Gfx obj_s_yubinkyoku_t2_model[];
extern Gfx obj_s_yubinkyoku_t1_model[];
extern Gfx obj_s_yubinkyoku_neon_model[];
extern Gfx obj_s_yubinkyoku_light_model[];
extern Gfx obj_s_yubinkyoku_door_model[];
extern u8 obj_s_yubinkyoku_t3_txt[];
extern u8 obj_s_yubinkyoku_t1_txt[];
extern u8 obj_s_yubinkyoku_window_tex_txt[];
extern u8 obj_s_yubinkyoku_t2_txt[];
extern JointElemR cKF_je_r_obj_s_yubinkyoku_tbl[];
extern BaseSkeletonR cKF_bs_r_obj_s_yubinkyoku;
extern u8 cKF_ckcb_r_obj_s_yubinkyoku_tbl[];
extern s16 cKF_kn_obj_s_yubinkyoku_tbl[];
extern s16 cKF_c_obj_s_yubinkyoku_tbl[];
extern Keyframe cKF_ds_obj_s_yubinkyoku_tbl[];
extern BaseAnimationR cKF_ba_r_obj_s_yubinkyoku;
extern u8 cKF_ckcb_r_obj_s_yubinkyoku_out_tbl[];
extern s16 cKF_kn_obj_s_yubinkyoku_out_tbl[];
extern s16 cKF_c_obj_s_yubinkyoku_out_tbl[];
extern Keyframe cKF_ds_obj_s_yubinkyoku_out_tbl[];
extern BaseAnimationR cKF_ba_r_obj_s_yubinkyoku_out;

#endif
