#ifndef M_LIB_H
#define M_LIB_H

#include "ultra64.h"
#include "z64math.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "color.h"
#include "sys_math.h"


typedef struct {
    u32 cont:   1;
    u32 type:   4;
    u32 offset: 11;
    s32 value:  16;
} ValueSet; 


typedef void (*ValueSetProc)(u8*, ValueSet*);


extern ValueSetProc D_80107B00_jp[];

void mem_copy(u8* dest, u8* src, size_t len);
void mem_clear(u8* ptr, size_t len, u8 value);
s32 mem_cmp(u8* ptr1, u8* ptr2, size_t len);
f32 cos_s(s16 angle);
f32 sin_s(s16 angle);
s32 chase_angle(s16* pValue, s16 target, s16 step);
s32 chase_s(s16* pValue, s16 target, s16 step);
s32 chase_f(f32* pValue, f32 target, f32 step);
s32 chase_angle2(s16* pValue, s16 limit, s16 step);
s32 chase_s2(s16* pValue, s16 limit, s16 step);
s32 chase_s3(s16* pValue, s16 target, s16 step);
s32 chase_f2(f32* pValue, f32 limit, f32 step);
s32 chase_f3(f32* pValue, f32 target, f32 incrStep, f32 decrStep);
void inter_float(f32* pValue, f32 arg1, s32 stepCount);
void stick_ratio_set(f32* magnitude, s16* angle, Input* input);
s16 get_random_timer(s16 base, s16 range);
s16 get_random_pattern_timer(s16 base, s16 stride, s16 range);
void xyz_t_move(xyz_t* dest, xyz_t* src);
void xyz_t_move_s_xyz(xyz_t* dest, s_xyz* src);
void xyz_t_add(xyz_t* augend, xyz_t* addend, xyz_t* total);
void xyz_t_sub(xyz_t* minuend, xyz_t* subtrahend, xyz_t* diff);
void xyz_t_sub_ss(xyz_t* dest, s_xyz* minuend, s_xyz* subtrahend);
void xyz_t_mult_v(xyz_t* multiplicand, f32 multiplier);
f32 search_position_distance(xyz_t* subtrahend, xyz_t* minuend);
f32 search_position_distance2(xyz_t* subtrahend, xyz_t* minuend, xyz_t* dest);
f32 search_position_distanceXZ(xyz_t* subtrahend, xyz_t* minuend);
f32 search_position_high(xyz_t* subtrahend, xyz_t* minuend);
s16 search_position_angleY(xyz_t* subtrahend, xyz_t* minuend);
s16 search_position_angleX(xyz_t* subtrahend, xyz_t* minuend);
void ValueSet_process(u8* ptr, ValueSet* values);
void ValueSet__s_char(u8* ptr, ValueSet* value_set);
void ValueSet__u_char(u8* ptr, ValueSet* value_set);
void ValueSet__s_short(u8* ptr, ValueSet* value_set);
void ValueSet__u_short(u8* ptr, ValueSet* value_set);
void ValueSet__s_int(u8* ptr, ValueSet* value_set);
void ValueSet__u_int(u8* ptr, ValueSet* value_set);
void ValueSet__float(u8* ptr, ValueSet* value_set);
void ValueSet__float_x1000(u8* ptr, ValueSet* value_set);
void ValueSet__xyz_t(u8* ptr, ValueSet* value_set);
void ValueSet__xyz_t_x1000(u8* ptr, ValueSet* value_set);
void ValueSet__s_xyz(u8* ptr, ValueSet* value_set);
f32 add_calc(f32* pValue, f32 target, f32 fraction, f32 step, f32 minStep);
void add_calc2(f32* pValue, f32 target, f32 fraction, f32 step);
void add_calc0(f32* pValue, f32 fraction, f32 step);
f32 add_calc_a(f32* pValue, f32 target, f32 fraction, f32 step, f32 minStep);
s16 add_calc_short_angle2(s16* pValue, s16 target, f32 fraction, s16 step, s16 minStep);
s16 add_calc_short_angle3(s16* pValue, s16 target, f32 fraction, s16 maxStep, s16 minStep);
void adds(s16* pValue, s16 target, s16 scale, s16 maxStep);
void rgba_t_move(Color_RGBA8* dest, Color_RGBA8* src);
s32 none_proc1();
void none_proc2(Actor* actor, struct Game_Play* play);
void Cheap_gfx_display(struct Game_Play* play, Gfx* dl);
void Cheap_gfx_display_xlu(struct Game_Play* play, Gfx* dl);
s32 _Game_play_isPause(struct Game_Play* play);
void* Lib_SegmentedToVirtual(void* ptr);
void* Lib_SegmentedToVirtualNull(void* ptr);
void* PhysicalToVirtual(uintptr_t ptr);
void* PhysicalToVirtualNull(uintptr_t ptr);
f32 check_percent_abs(f32 x, f32 min, f32 max, f32 scale, s32 shiftMin);
f32 get_percent_forAccelBrake(f32 x, f32 min, f32 max, f32 accelRange, f32 brakeRange);
void Game_play_Projection_Trans(struct Game_Play* play, xyz_t* src, xyz_t* dst);
f32 get_percent(s32 max, s32 min, s32 x);

#endif
