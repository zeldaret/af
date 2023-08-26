#ifndef M_NPC_WALK_H
#define M_NPC_WALK_H

#include "ultra64.h"
#include "m_npc.h"

#define mNpcW_GET_WALK_NUM(x) (int)((x) / 3)
#define mNpcW_MAX mNpcW_GET_WALK_NUM(ANIMAL_NUM_MAX)

typedef struct mNpcW_GoalData_c {
    /* 0x00 */ u8* types;
    /* 0x04 */ u8 count;
    /* 0x08 */ s32 end_time;
} mNpcW_GoalData_c; // size = 0xC

typedef struct mNpcW_GoalDataTable_c {
    /* 0x00 */ mNpcW_GoalData_c* data_p;
    /* 0x04 */ s32 count;
} mNpcW_GoalDataTable_c;// size = 0x8

typedef enum mNpcW_GOAL{
  /* 0 */ mNpcW_GOAL_SHRINE,    /* Shrine acre */
  /* 1 */ mNpcW_GOAL_HOME,      /* Randomly selected acre with a villager house */
  /* 2 */ mNpcW_GOAL_ALONE,     /* Randomly selected acre with no other animals in it */
  /* 3 */ mNpcW_GOAL_MY_HOME,   /* Acre containing the villager's house */
  
  /* 4 */ mNpcW_GOAL_NUM
} mNpcW_GOAL;

typedef enum mNpcW_GOAL_BLOCK{
  /* 0 */ mNpcW_GOAL_BLOCK_SHRINE,
  /* 1 */ mNpcW_GOAL_BLOCK_HOME,

  /* 2 */ mNpcW_GOAL_BLOCK_NUM
} mNpcW_GOAL_BLOCK;

/* TODO: figure out remaining enums */
typedef enum mNpcW_APPEAR_STATUS{
  /* 0 */ mNpcW_APPEAR_STATUS_0,
  /* 1 */ mNpcW_APPEAR_STATUS_1,

  /* 2 */ mNpcW_APPEAR_STATUS_NUM
} mNpcW_APPEAR_STATUS;

typedef enum mNpcW_APPEAR_WAY {
    /* 0 */ mNpcW_APPEAR_WAY_UP,
    /* 1 */ mNpcW_APPEAR_WAY_DOWN,
    /* 2 */ mNpcW_APPEAR_WAY_LEFT,
    /* 3 */ mNpcW_APPEAR_WAY_RIGHT,

    /* 4 */ mNpcW_APPEAR_WAY_NUM
} mNpcW_APPEAR_WAY;

/* TODO: figure out remaining enums */
typedef enum mNpcW_INFO_STATUS {
    /* 0 */ mNpcW_INFO_STATUS_0,
    /* 1 */ mNpcW_INFO_STATUS_WALKING,
    /* 2 */ mNpcW_INFO_STATUS_2,
    /* 3 */ mNpcW_INFO_STATUS_3,
    /* 4 */ mNpcW_INFO_STATUS_4,

    /* 5 */ mNpcW_INFO_STATUS_NUM
} mNpcW_INFO_STATUS;

typedef struct mNpcW_appear_c {
    /* 0x00 */ u8 status;
    /* 0x01 */ u8 way;
} mNpcW_appear_c;

typedef struct mNpcW_info_c {
    /* 0x00 */ AnmPersonalID_c id;
    /* 0x0C */ s32 idx;
    /* 0x10 */ u8 status;
    /* 0x11 */ u8 goal_type;
    /* 0x12 */ u8 goal_block_x;
    /* 0x13 */ u8 goal_block_z;
    /* 0x14 */ mNpcW_appear_c appear_info;
} mNpcW_info_c; // size = 0x18

typedef struct mNpc_walk_c {
    /* 0x00 */ mNpcW_info_c info[mNpcW_MAX];
    /* 0x78 */ u16 used_idx_bitfield;
    /* 0x7A */ u8 used_info_num;
    /* 0x7B */ u8 info_max;
} mNpc_walk_c; // size = 0x7C

mNpcW_GoalData_c* mNpcW_GetGoalDataInfo(s32 looks, s32 now_sec);
void mNpcW_ClearNpcWalkAppear(mNpcW_appear_c* appear_info);
void mNpcW_ClearNpcWalkInfo(mNpcW_info_c* info, s32 count);
void mNpcW_ClearNpcWalk(mNpc_walk_c* walk);
s32 mNpcW_CheckFreeNpcWalkInfo(mNpcW_info_c* info);
s32 mNpcW_GetFreeNpcWalkInfoIdx(mNpcW_info_c* info, s32 num);
s32 mNpcW_GetNpcWalkInfoIdx(mNpcW_info_c* info, s32 num, AnmPersonalID_c* anm_id);
s32 func_800AF060_jp(mNpcW_info_c* info, s32 num, s32 want_idx);
s32 mNpcW_DecideNpc(Animal_c* animal, u16 used);
void mNpcW_SetNpcWalkInfo(mNpcW_info_c* info, Animal_c* animal, s32 idx);
s32 mNpcW_ChangeNpcWalk(mNpc_walk_c* walk, mNpcW_info_c* info);
s32 mNpcW_GetAloneBlock(u8* goal_block_x, u8* goal_block_z);
void mNpcW_GetBlockXZNumExceptHome(s32* goal_block_x, s32* goal_block_z, Animal_c* animal);
s32 mNpcW_CheckDiffBlockWalkNpcHome(s32 block_x, s32 block_z, mNpcW_info_c* info);
void mNpcW_SetHomeBlockSource(mNpc_walk_c* walk, Animal_c* animal);
void mNpcW_InitGoalBlockSource(mNpc_walk_c* walk, Animal_c* animal);
void mNpcW_SetGoalBlock(mNpcW_info_c* info);
void mNpcW_InitNpcWalk(mNpc_walk_c* walk);
s32 mNpcW_GetAppearStatusWay(u8* status, u8* way, Animal_c* animal);
s32* mNpcW_GetArriveStayCountP(s32 idx);
s32 mNpcW_GetWalkInfoStatusGoalAnimalIdx(s32* status, s32* goal, s32 idx);
s32 mNpcW_GetNearGate(s32* target_ut_x, s32* target_ut_z, s32 block_x, s32 block_z, s32 ut_x, s32 ut_z);

#endif
