#ifndef M_ROLL_LIB_H
#define M_ROLL_LIB_H

#include "ultra64.h"

struct xyz_t;
struct Actor;
struct s_xyz;
struct Game_Play;

void mRlib_spdXZ_to_spdF_Angle(struct xyz_t* speed, f32* speedf, s16* angle);
void mRlib_spdF_Angle_to_spdXZ(struct xyz_t* speed, f32* speedf, s16* angle);
s32 mRlib_position_move_for_sloop(struct Actor* actor, struct s_xyz* slopeAngle);
s32 mRlib_Get_norm_Clif(struct Actor* actor, struct xyz_t* norm);
void mRlib_Roll_Matrix_to_s_xyz(struct Actor* actor, struct s_xyz* rot, s16 angle);
s16 mRlib_Get_HitWallAngleY(struct Actor* actor);
void mRlib_Station_step_modify_to_wall(struct Actor* actor);
s32 mRlib_Set_Position_Check(struct Actor* actor);
s32 mRlib_HeightGapCheck_And_ReversePos(struct Actor* actor);
s32 mRlib_Hole_check(struct Actor* actor);
s32 mRlib_Get_ground_norm_inHole(struct Actor* actor, struct xyz_t* norm, f32* dist, s16* angleY, s16* angleRate, f32 rate);
s32 mRlib_PSnowmanTouchCheck(const struct xyz_t* wpos);
s32 mRlib_PSnowmanBreakCheck(struct Actor* actor, struct Game_Play* play, f32* speed);
s32 mRlib_PSnowmanBreakNeckSwing(f32 f0, f32 scale, s16* angleY);
s32 mRlib_PSnowman_NormalTalk(struct Actor* actor, struct Game_Play* play, f32* speed, void* proc);


#endif
