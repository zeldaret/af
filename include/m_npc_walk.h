#ifndef M_NPC_WALK_H
#define M_NPC_WALK_H

#include "ultra64.h"
#include "m_npc.h"

#define NPCW_GET_WALK_NUM(x) (int)((x) / 3)
#define NPCW_MAX NPCW_GET_WALK_NUM(ANIMAL_NUM_MAX)

typedef struct NpcWalk {
    /* 0x00 */ char unk00[0x7C];
} NpcWalk; // size = 0x7C

typedef struct NpcWalkGoalData {
    /* 0x0 */ u8* types;
    /* 0x1 */ u8 count;
    /* 0x2 */ s32 time;
} NpcWalkGoalData; // size = 0x6

typedef struct NpcWalkGoalDataTable {
    /* 0x0 */ NpcWalkGoalData* data;
    /* 0x4 */ int count;
} NpcWalkGoalDataTable; // size = 0x8

typedef struct NpcWalkAppear {
    /* 0x0 */ u8 status;
    /* 0x1 */ u8 way;
} NpcWalkAppear; // size = 0x2;

typedef struct NpcWalkInfo {
    /* 0x00 */ AnmPersonalID_c id;
    /* 0x0C */ s32 idx;
    /* 0x10 */ u8 status;
    /* 0x11 */ u8 type;
    /* 0x12 */ u8 goalX;
    /* 0x13 */ u8 goalZ;
    /* 0x14 */ NpcWalkAppear appearInfo;
} NpcWalkInfo; // size = 0x18

typedef struct NpcWalking {
    /* 0x00 */ NpcWalkInfo info[NPCW_MAX];
    /* 0x78 */ u16 idxUse;
    /* 0x7A */ u8 infoUse;
    /* 0x7B */ u8 infoMax;
} NpcWalking; //size = 0x7C

typedef enum WalkGoal{
    /* 0 */ NPCW_GOAL_SHRINE,    /* Shrine/Wishing Well acre */
    /* 1 */ NPCW_GOAL_HOME,      /* Randomly selected acre with a villager house */
    /* 2 */ NPCW_GOAL_ALONE,     /* Randomly selected acre with no other animals in it */
    /* 3 */ NPCW_GOAL_MY_HOME,   /* Acre containing the villager's house */

    /* 4 */ NPCW_GOAL_NUM
}WalkGoal;

typedef enum WalkGoalBlock{
    /* 0 */ NPCW_GOAL_BLOCK_SHRINE,
    /* 1 */ NPCW_GOAL_BLOCK_HOME,

    /* 2 */ NPCW_GOAL_BLOCK_NUM
}WalkGoalBlock;

typedef enum WalkAppearStatus {
    /* 0 */ NPCW_APPEAR_STATUS_0,
    /* 1 */ NPCW_APPEAR_STATUS_1,

    /* 2 */ NPCW_APPEAR_STATUS_NUM
}WalkAppearStatus;

typedef enum WalkAppearDirection {
    /* 0 */ NPCW_APPEAR_WAY_UP,
    /* 1 */ NPCW_APPEAR_WAY_DOWN,
    /* 2 */ NPCW_APPEAR_WAY_LEFT,
    /* 3 */ NPCW_APPEAR_WAY_RIGHT,

    /* 4 */ NPCW_APPEAR_WAY_NUM
}WalkAppearDirection;

typedef enum WalkInfoStatus {
    /* 0 */ NPCW_INFO_STATUS_0,
    /* 1 */ NPCW_INFO_STATUS_WALKING,
    /* 2 */ NPCW_INFO_STATUS_2,
    /* 3 */ NPCW_INFO_STATUS_3,
    /* 4 */ NPCW_INFO_STATUS_4,    

    /* 5 */ NPCW_INFO_STATUS_NUM
}WalkInfoStatus;

NpcWalkGoalData* mNpcW_GetGoalDataInfo(s32 looks, s32 time);
void mNpcW_ClearNpcWalkAppear(NpcWalkAppear* info);
void mNpcW_ClearNpcWalkInfo(NpcWalkInfo*  info , s32 count);
void mNpcW_ClearNpcWalk(NpcWalking* walk);
s32 mNpcW_CheckFreeNpcWalkInfo(NpcWalkInfo*  info );
s32 mNpcW_GetFreeNpcWalkInfoIdx(NpcWalkInfo*  info , s32  num );
s32 mNpcW_GetNpcWalkInfoIdx(NpcWalkInfo*  info , s32  num , AnmPersonalID_c*  anmId );
s32 mNpcW_GetNpcWalkInfoIdxbyIdx(NpcWalkInfo*  info , s32  num , s32  idx );
s32 mNpcW_DecideNpc(Animal_c*  animal , u16  used );
void mNpcW_SetNpcWalkInfo(NpcWalkInfo*  info , Animal_c*  animal , s32  idx );
s32 mNpcW_ChangeNpcWalk(NpcWalking*  walk , NpcWalkInfo*  info );
s32 mNpcW_GetAloneBlock(u8*  goalBlockX , u8*  goalBlockZ );
void mNpcW_GetBlockXZNumExceptHome(s32*  goalBlockX , s32*  goalBlockZ , Animal_c*  animal );
s32 mNpcW_CheckDiffBlockWalkNpcHome(s32  blockX , s32  blockZ , NpcWalkInfo*  info );
void mNpcW_SetHomeBlockSource(NpcWalking*  walk , Animal_c*  animal );
void mNpcW_InitGoalBlockSource(NpcWalking*  walk , Animal_c*  animal );
void mNpcW_SetGoalBlock(NpcWalkInfo*  info );
void mNpcW_InitNpcWalk(NpcWalking*  walk );
s32 mNpcW_GetAppearStatusWay(u8*  status , u8*  way , Animal_c*  animal );
s32* mNpcW_GetArriveStayCountP(s32  idx );
s32 mNpcW_GetWalkInfoStatusGoalAnimalIdx(s32*  status , s32*  goal , s32  idx );
s32 mNpcW_GetNearGate(s32*  targetUtX , s32*  targetUtZ , s32  blockX , s32  blockZ , s32  utX , s32  utZ );

#endif
