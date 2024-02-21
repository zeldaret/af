#include "obj_w_douzou.h"

s32 padD6B180[] = { 0x00000000, 0x00000000 };
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_v.vtx.inc.c"
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_name_model.gfx.inc.c"
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_dai_model.gfx.inc.c"
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_girl_mouth_model.gfx.inc.c"
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_girl_face_model.gfx.inc.c"
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_girl_model.gfx.inc.c"
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_boy_mouth_model.gfx.inc.c"
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_boy_face_model.gfx.inc.c"
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_boy_model.gfx.inc.c"
u8 obj_w_douzou_dai_tex_txt[] = {
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_dai_tex_txt.ci4.inc.c"
};
u8 obj_w_douzou_name_tex_txt[] = {
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_name_tex_txt.i4.inc.c"
};
u8 obj_w_douzou_b1_tex_pic_i4[] = {
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_b1_tex_pic_i4.i4.inc.c"
};
u8 obj_w_douzou_b2_tex_pic_i4[] = {
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_b2_tex_pic_i4.i4.inc.c"
};
u8 obj_w_douzou_b3_tex_pic_i4[] = {
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_b3_tex_pic_i4.i4.inc.c"
};
u8 obj_w_douzou_b4_tex_pic_i4[] = {
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_b4_tex_pic_i4.i4.inc.c"
};
u8 obj_w_douzou_b5_tex_pic_i4[] = {
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_b5_tex_pic_i4.i4.inc.c"
};
u8 obj_w_douzou_b6_tex_pic_i4[] = {
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_b6_tex_pic_i4.i4.inc.c"
};
u8 obj_w_douzou_b7_tex_pic_i4[] = {
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_b7_tex_pic_i4.i4.inc.c"
};
u8 obj_w_douzou_b8_tex_pic_i4[] = {
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_b8_tex_pic_i4.i4.inc.c"
};
u8 obj_w_douzou_bm1_tex_pic_i4[] = {
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_bm1_tex_pic_i4.i4.inc.c"
};
u8 obj_w_douzou_bm2_tex_pic_i4[] = {
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_bm2_tex_pic_i4.i4.inc.c"
};
u8 obj_w_douzou_g1_tex_pic_i4[] = {
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_g1_tex_pic_i4.i4.inc.c"
};
u8 obj_w_douzou_g2_tex_pic_i4[] = {
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_g2_tex_pic_i4.i4.inc.c"
};
u8 obj_w_douzou_g3_tex_pic_i4[] = {
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_g3_tex_pic_i4.i4.inc.c"
};
u8 obj_w_douzou_g4_tex_pic_i4[] = {
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_g4_tex_pic_i4.i4.inc.c"
};
u8 obj_w_douzou_g5_tex_pic_i4[] = {
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_g5_tex_pic_i4.i4.inc.c"
};
u8 obj_w_douzou_g6_tex_pic_i4[] = {
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_g6_tex_pic_i4.i4.inc.c"
};
u8 obj_w_douzou_g8_tex_pic_i4[] = {
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_g8_tex_pic_i4.i4.inc.c"
};
u8 obj_w_douzou_gm1_tex_pic_i4[] = {
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_gm1_tex_pic_i4.i4.inc.c"
};
u8 obj_w_douzou_gm2_tex_pic_i4[] = {
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_gm2_tex_pic_i4.i4.inc.c"
};
u8 obj_w_douzou_metal_tex_pic_i4[] = {
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/obj_w_douzou_metal_tex_pic_i4.i4.inc.c"
};
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/cKF_ckcb_r_obj_w_douzou_tbl.inc.c"
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/cKF_c_obj_w_douzou_tbl.inc.c"
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/cKF_ba_r_obj_w_douzou.inc.c"
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/cKF_je_r_obj_w_douzou_tbl.inc.c"
#include "assets/jp/objects/object_00D5E000/obj_w_douzou/cKF_bs_r_obj_w_douzou.inc.c"
