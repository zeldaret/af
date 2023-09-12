#ifndef M_NPC_WALK_H
#define M_NPC_WALK_H

#include "ultra64.h"
#include "m_npc.h"

#define NPCW_GET_WALK_NUM(x) (int)((x) / 3)
#define NPCW_MAX NPCW_GET_WALK_NUM(ANIMAL_NUM_MAX)

typedef struct mNpcW_c {
    /* 0x00 */ char unk00[0x7C];
} mNpcW_c; // size = 0x7C

typedef struct mNpcW_GoalData_c {
    /* 0x0 */ u8* types;
    /* 0x1 */ u8 count;
    /* 0x2 */ s32 time;
} mNpcW_GoalData_c; // size = 0x6

typedef struct mNpcW_GoalDataTable_c {
    /* 0x0 */ mNpcW_GoalData_c* data;
    /* 0x4 */ int count;
} mNpcW_GoalDataTable_c; // size = 0x8

typedef struct mNpcW_Appear_c {
    /* 0x0 */ u8 status;
    /* 0x1 */ u8 way;
} mNpcW_Appear_c; // size = 0x2;

typedef struct mNpcW_info_c {
    /* 0x00 */ AnmPersonalID_c id;
    /* 0x0C */ s32 idx;
    /* 0x10 */ u8 status;
    /* 0x11 */ u8 type;
    /* 0x12 */ u8 goalX;
    /* 0x13 */ u8 goalZ;
    /* 0x14 */ mNpcW_Appear_c appearInfo;
} mNpcW_info_c; // size = 0x18

typedef struct mNpcW_walk_c {
    /* 0x00 */ mNpcW_info_c info[NPCW_MAX];
    /* 0x78 */ u16 idxUse;
    /* 0x7A */ u8 infoUse;
    /* 0x7B */ u8 infoMax;
} mNpcW_walk_c; //size = 0x7C

enum {
    /* 0 */ NPCW_GOAL_SHRINE,    /* Shrine/Wishing Well acre */
    /* 1 */ NPCW_GOAL_HOME,      /* Randomly selected acre with a villager house */
    /* 2 */ NPCW_GOAL_ALONE,     /* Randomly selected acre with no other animals in it */
    /* 3 */ NPCW_GOAL_MY_HOME,   /* Acre containing the villager's house */

    /* 4 */ NPCW_GOAL_NUM
};

enum {
    /* 0 */ NPCW_GOAL_BLOCK_SHRINE,
    /* 1 */ NPCW_GOAL_BLOCK_HOME,

    /* 2 */ NPCW_GOAL_BLOCK_NUM
};

enum {
    /* 0 */ NPCW_APPEAR_STATUS_0,
    /* 1 */ NPCW_APPEAR_STATUS_1,

    /* 2 */ NPCW_APPEAR_STATUS_NUM
};

enum {
    /* 0 */ NPCW_APPEAR_WAY_UP,
    /* 1 */ NPCW_APPEAR_WAY_DOWN,
    /* 2 */ NPCW_APPEAR_WAY_LEFT,
    /* 3 */ NPCW_APPEAR_WAY_RIGHT,

    /* 4 */ NPCW_APPEAR_WAY_NUM
};
enum {
    /* 0 */ NPCW_INFO_STATUS_0,
    /* 1 */ NPCW_INFO_STATUS_WALKING,
    /* 2 */ NPCW_INFO_STATUS_2,
    /* 3 */ NPCW_INFO_STATUS_3,
    /* 4 */ NPCW_INFO_STATUS_4,    

    /* 5 */ NPCW_INFO_STATUS_NUM
};

mNpcW_GoalData_c* mNpcW_GetGoalDataInfo(s32 /*looks*/, s32 /*time*/);
void mNpcW_ClearNpcWalkAppear(mNpcW_Appear_c* /*info*/);
void mNpcW_ClearNpcWalkInfo(mNpcW_info_c* /*info*/, s32 /*count*/);
void mNpcW_ClearNpcWalk(mNpcW_walk_c* /*walk*/);
s32 mNpcW_CheckFreeNpcWalkInfo(mNpcW_info_c* /*info*/);
s32 mNpcW_GetFreeNpcWalkInfoIdx(mNpcW_info_c* /*info*/, s32 /*num*/);
s32 mNpcW_GetNpcWalkInfoIdx(mNpcW_info_c* /*info*/, s32 /*num*/, AnmPersonalID_c* /*anmId*/);
s32 mNpcW_GetNpcWalkInfoIdxbyIdx(mNpcW_info_c* /*info*/, s32 /*num*/, s32 /*idx*/);
s32 mNpcW_DecideNpc(Animal_c* /*animal*/, u16 /*used*/);
void mNpcW_SetNpcWalkInfo(mNpcW_info_c* /*info*/, Animal_c* /*animal*/, s32 /*idx*/);
s32 mNpcW_ChangeNpcWalk(mNpcW_walk_c* /*walk*/, mNpcW_info_c* /*info*/);
s32 mNpcW_GetAloneBlock(u8* /*goalBlockX*/, u8* /*goalBlockZ*/);
void mNpcW_GetBlockXZNumExceptHome(s32* /*goalBlockX*/, s32* /*goalBlockZ*/, Animal_c* /*animal*/);
s32 mNpcW_CheckDiffBlockWalkNpcHome(s32 /*blockX*/, s32 /*blockZ*/, mNpcW_info_c* /*info*/);
void mNpcW_SetHomeBlockSource(mNpcW_walk_c* /*walk*/, Animal_c* /*animal*/);
void mNpcW_InitGoalBlockSource(mNpcW_walk_c* /*walk*/, Animal_c* /*animal*/);
void mNpcW_SetGoalBlock(mNpcW_info_c* /*info*/);
void mNpcW_InitNpcWalk(mNpcW_walk_c* /*walk*/);
s32 mNpcW_GetAppearStatusWay(u8* /*status*/, u8* /*way*/, Animal_c* /*animal*/);
s32* mNpcW_GetArriveStayCountP(s32 /*idx*/);
s32 mNpcW_GetWalkInfoStatusGoalAnimalIdx(s32* /*status*/, s32* /*goal*/, s32 /*idx*/);
s32 mNpcW_GetNearGate(s32* /*targetUtX*/, s32* /*targetUtZ*/, s32 /*blockX*/, s32 /*blockZ*/, s32 /*utX*/, s32 /*utZ*/);

#endif
