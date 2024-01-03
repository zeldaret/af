#include "ultra64.h"
#include "z64math.h"
#include "c_keyframe.h"

// obj_s_toudai

// Vtx obj_s_toudai_v[] = {
// #include "assets/jp/objects/object_00D5E000/obj_s_toudai/obj_s_toudai_v.vtx.inc.c"
// };

// Gfx obj_s_toudai_mirror_model[] = {
// #include "assets/jp/objects/object_00D5E000/obj_s_toudai/obj_s_toudai_mirror_model.gfx.inc.c"
// };

// Gfx obj_s_toudai_glass_model[] = {
// #include "assets/jp/objects/object_00D5E000/obj_s_toudai/obj_s_toudai_glass_model.gfx.inc.c"
// };

// Gfx obj_s_toudai_body_model[] = {
// #include "assets/jp/objects/object_00D5E000/obj_s_toudai/obj_s_toudai_body_model.gfx.inc.c"
// };

// Gfx obj_s_toudai_light_model[] = {
// #include "assets/jp/objects/object_00D5E000/obj_s_toudai/obj_s_toudai_light_model.gfx.inc.c"
// };

// Gfx obj_s_toudai_lenz_model[] = {
// #include "assets/jp/objects/object_00D5E000/obj_s_toudai/obj_s_toudai_lenz_model.gfx.inc.c"
// };

// Gfx obj_s_toudai_arm_model[] = {
// #include "assets/jp/objects/object_00D5E000/obj_s_toudai/obj_s_toudai_arm_model.gfx.inc.c"
// };

// u64 obj_s_toudai_light_tex_txt[] = {
// #include "assets/jp/objects/object_00D5E000/obj_s_toudai/obj_s_toudai_light_tex_txt.png.inc.c"
// }

// u64 obj_s_toudai_arm_tex_txt[] = {
// #include "assets/jp/objects/object_00D5E000/obj_s_toudai/obj_s_toudai_arm_tex_txt.png.inc.c"
// }

// u64 obj_s_toudai_dai_tex_txt[] = {
// #include "assets/jp/objects/object_00D5E000/obj_s_toudai/obj_s_toudai_dai_tex_txt.png.inc.c"
// }

// u64 obj_s_toudai_dou_tex_txt[] = {
// #include "assets/jp/objects/object_00D5E000/obj_s_toudai/obj_s_toudai_dou_tex_txt.png.inc.c"
// }

// u64 obj_s_toudai_plate_tex_txt[] = {
// #include "assets/jp/objects/object_00D5E000/obj_s_toudai/obj_s_toudai_plate_tex_txt.png.inc.c"
// }

// u64 obj_s_toudai_side_tex_txt[] = {
// #include "assets/jp/objects/object_00D5E000/obj_s_toudai/obj_s_toudai_side_tex_txt.png.inc.c"
// }

// u64 obj_s_toudai_tesuri_tex_txt[] = {
// #include "assets/jp/objects/object_00D5E000/obj_s_toudai/obj_s_toudai_tesuri_tex_txt.png.inc.c"
// }

// u64 obj_s_toudai_yane_tex_txt[] = {
// #include "assets/jp/objects/object_00D5E000/obj_s_toudai/obj_s_toudai_yane_tex_txt.png.inc.c"
// }

// u64 obj_s_toudai_glass_tex_pic_ci4_pal[] = {
// #include "assets/jp/objects/object_00D5E000/obj_s_toudai/obj_s_toudai_glass_tex_pic_ci4_pal.pal.inc.c"
// }

// u64 obj_s_toudai_glass_tex_pic_ci4[] = {
// #include "assets/jp/objects/object_00D5E000/obj_s_toudai/obj_s_toudai_glass_tex_pic_ci4.pal.inc.c"
// }

// JointElemR cKF_je_r_obj_s_toudai_tbl[] = {
// #include "assets/jp/objects/object_00D5E000/obj_s_toudai/cKF_je_r_obj_s_toudai_tbl.inc.c"
// };

// BaseSkeletonR cKF_bs_r_obj_s_toudai = {
// #include "assets/jp/objects/object_00D5E000/obj_s_toudai/cKF_bs_r_obj_s_toudai.inc.c"
// };

// u8 cKF_ckcb_r_obj_s_toudai_tbl[] = {
// #include "assets/jp/objects/object_00D5E000/obj_s_toudai/cKF_ckcb_r_obj_s_toudai_tbl.inc.c"
// };

// s16 cKF_kn_obj_s_toudai_tbl[] = {
// #include "assets/jp/objects/object_00D5E000/obj_s_toudai/cKF_kn_obj_s_toudai_tbl.inc.c"
// };

// s16 cKF_c_obj_s_toudai_tbl[] = {
// #include "assets/jp/objects/object_00D5E000/obj_s_toudai/cKF_c_obj_s_toudai_tbl.inc.c"
// };

// Keyframe cKF_ds_obj_s_toudai_tbl[] = {
// #include "assets/jp/objects/object_00D5E000/obj_s_toudai/cKF_ds_obj_s_toudai_tbl.inc.c"
// };

// BaseAnimationR cKF_ba_r_obj_s_toudai = {
// #include "assets/jp/objects/object_00D5E000/obj_s_toudai/cKF_ba_r_obj_s_toudai.inc.c"
// };

// obj_w_toudai

// Vtx obj_w_toudai_v[] = {
// #include "assets/jp/objects/object_00D5E000/obj_w_toudai/obj_w_toudai_v.vtx.inc.c"
// };

// JointElemR cKF_je_r_obj_w_toudai_tbl[] = {
// #include "assets/jp/objects/object_00D5E000/obj_w_toudai/cKF_je_r_obj_w_toudai_tbl.inc.c"
// };

// BaseSkeletonR cKF_bs_r_obj_w_toudai = {
// #include "assets/jp/objects/object_00D5E000/obj_w_toudai/cKF_bs_r_obj_w_toudai.inc.c"
// };

// u8 cKF_ckcb_r_obj_w_toudai_tbl[] = {
// #include "assets/jp/objects/object_00D5E000/obj_w_toudai/cKF_ckcb_r_obj_w_toudai_tbl.inc.c"
// };

// s16 cKF_kn_obj_w_toudai_tbl[] = {
// #include "assets/jp/objects/object_00D5E000/obj_w_toudai/cKF_kn_obj_w_toudai_tbl.inc.c"
// };

// s16 cKF_c_obj_w_toudai_tbl[] = {
// #include "assets/jp/objects/object_00D5E000/obj_w_toudai/cKF_c_obj_w_toudai_tbl.inc.c"
// };

// Keyframe cKF_ds_obj_w_toudai_tbl[] = {
// #include "assets/jp/objects/object_00D5E000/obj_w_toudai/cKF_ds_obj_w_toudai_tbl.inc.c"
// };

// BaseAnimationR cKF_ba_r_obj_w_toudai = {
// #include "assets/jp/objects/object_00D5E000/obj_w_toudai/cKF_ba_r_obj_w_toudai.inc.c"
// };
