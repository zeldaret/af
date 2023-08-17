#ifndef M_LIB_H
#define M_LIB_H

#include "ultra64.h"
#include "z64math.h"
#include "unk.h"

// void mem_copy();
s32 mem_clear(void* ptr, size_t size, u8 value);
// void mem_cmp();
f32 cos_s(s16 angle);
f32 sin_s(s16 angle);
// void chase_angle();
// void chase_s();
s32 chase_f(f32* arg0, f32 arg1, f32 arg2);
// void chase_angle2();
// void chase_s2();
// void chase_s3();
// void chase_f2();
// void chase_f3();
// void inter_float();
// void stick_ratio_set();
// void get_random_timer();
// void get_random_pattern_timer();
void xyz_t_move(Vec3f* dst, Vec3f* src);
void xyz_t_move_s_xyz(Vec3f* dst, Vec3s* src);
// void xyz_t_add();
// void xyz_t_sub();
// void xyz_t_sub_ss();
// void xyz_t_mult_v();
// void search_position_distance();
// void search_position_distance2();
f32 search_position_distanceXZ(Vec3f* arg0, Vec3f* arg1);
// void search_position_high();
s16 search_position_angleY(Vec3f* arg0, Vec3f* arg1);
// void search_position_angleX();
// void ValueSet_process();
// void ValueSet__s_char();
// void ValueSet__u_char();
// void ValueSet__s_short();
// void ValueSet__u_short();
// void ValueSet__s_int();
// void ValueSet__u_int();
// void ValueSet__float();
// void ValueSet__float_x1000();
// void ValueSet__xyz_t();
// void ValueSet__xyz_t_x1000();
// void ValueSet__s_xyz();
// void add_calc();
// void add_calc2();
// void add_calc0();
// void add_calc_a();
// void add_calc_short_angle2();
// void add_calc_short_angle3();
// void adds();
// void rgba_t_move();
UNK_RET none_proc1(void);
// void none_proc2();
// void Cheap_gfx_display();
// void Cheap_gfx_display_xlu();
// void _Game_play_isPause();
void *Lib_SegmentedToVirtual(void *ptr); //original name unknown, taken from majora's mask
// void func_8009ADE0_jp();
// void func_8009AE28_jp();
// void func_8009AE44_jp();
f32 check_percent_abs(f32 x, f32 min, f32 max, f32 scale, int shift_by_min);
// void get_percent_forAccelBrake();
// void Game_play_Projection_Trans();
// void get_percent();

#endif
