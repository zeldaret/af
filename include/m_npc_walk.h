#ifndef M_NPC_WALK_H
#define M_NPC_WALK_H

#include "ultra64.h"
#include "m_npc.h"

#define NPC_GET_WALK_NUM(x) (int)((x) / 3)
#define NPC_MAX NPC_GET_WALK_NUM(ANIMAL_NUM_MAX)

typedef struct NpcGoalData {
    /* 0x00 */ u8* types;
    /* 0x04 */ u8 count;
    /* 0x08 */ s32 endTime;
} NpcGoalData; // size = 0xC

typedef struct NpcGoalDataTable {
    /* 0x00 */ NpcGoalData* data;
    /* 0x04 */ s32 count;
} NpcGoalDataTable;// size = 0x8

typedef enum NPC_GOAL {
  /* 0 */ NPC_GOAL_SHRINE,    /* Shrine acre */
  /* 1 */ NPC_GOAL_HOME,      /* Randomly selected acre with a villager house */
  /* 2 */ NPC_GOAL_ALONE,     /* Randomly selected acre with no other animals in it */
  /* 3 */ NPC_GOAL_MY_HOME,   /* Acre containing the villager's house */
  
  /* 4 */ NPC_GOAL_NUM
} NPC_GOAL;

typedef enum NPC_GOAL_BLOCK {
  /* 0 */ NPC_GOAL_BLOCK_SHRINE,
  /* 1 */ NPC_GOAL_BLOCK_HOME,

  /* 2 */ NPC_GOAL_BLOCK_NUM
} NPC_GOAL_BLOCK;

/* TODO: figure out remaining enums */
typedef enum NPC_APPEAR_STATUS {
  /* 0 */ NPC_APPEAR_STATUS_0,
  /* 1 */ NPC_APPEAR_STATUS_1,

  /* 2 */ NPC_APPEAR_STATUS_NUM
} NPC_APPEAR_STATUS;

typedef enum NPC_APPEAR_WAY {
    /* 0 */ NPC_APPEAR_WAY_UP,
    /* 1 */ NPC_APPEAR_WAY_DOWN,
    /* 2 */ NPC_APPEAR_WAY_LEFT,
    /* 3 */ NPC_APPEAR_WAY_RIGHT,

    /* 4 */ NPC_APPEAR_WAY_NUM
} NPC_APPEAR_WAY;

/* TODO: figure out remaining enums */
typedef enum NPC_INFO_STATUS {
    /* 0 */ NPC_INFO_STATUS_0,
    /* 1 */ NPC_INFO_STATUS_WALKING,
    /* 2 */ NPC_INFO_STATUS_2,
    /* 3 */ NPC_INFO_STATUS_3,
    /* 4 */ NPC_INFO_STATUS_4,

    /* 5 */ NPC_INFO_STATUS_NUM
} NPC_INFO_STATUS;

typedef struct NpcAppear {
    /* 0x00 */ u8 status;
    /* 0x01 */ u8 way;
} NpcAppear;

typedef struct NpcInfo {
    /* 0x00 */ AnmPersonalId id;
    /* 0x0C */ s32 idx;
    /* 0x10 */ u8 status;
    /* 0x11 */ u8 goalType;
    /* 0x12 */ u8 goalBlockX;
    /* 0x13 */ u8 goalBlockZ;
    /* 0x14 */ NpcAppear appearInfo;
} NpcInfo; // size = 0x18

typedef struct NpcWalk {
    /* 0x00 */ NpcInfo info[NPC_MAX];
    /* 0x78 */ u16 usedIdxBitfield;
    /* 0x7A */ u8 usedInfoNum;
    /* 0x7B */ u8 infoMax;
} NpcWalk; // size = 0x7C

NpcGoalData* mNpcW_GetGoalDataInfo(s32 looks, s32 nowSec);
void mNpcW_ClearNpcWalkAppear(NpcAppear* appearInfo);
void mNpcW_ClearNpcWalkInfo(NpcInfo* info, s32 count);
void mNpcW_ClearNpcWalk(NpcWalk* walk);
s32 mNpcW_CheckFreeNpcWalkInfo(NpcInfo* info);
s32 mNpcW_GetFreeNpcWalkInfoIdx(NpcInfo* info, s32 num);
s32 mNpcW_GetNpcWalkInfoIdx(NpcInfo* info, s32 num, AnmPersonalId* anmId);
s32 func_800AF060_jp(NpcInfo* info, s32 num, s32 want_idx);
s32 mNpcW_DecideNpc(Animal* animal, u16 used);
void mNpcW_SetNpcWalkInfo(NpcInfo* info, Animal* animal, s32 idx);
s32 mNpcW_ChangeNpcWalk(NpcWalk* walk, NpcInfo* info);
s32 mNpcW_GetAloneBlock(u8* goalBlockX, u8* goalBlockZ);
void mNpcW_GetBlockXZNumExceptHome(s32* goalBlockX, s32* goalBlockZ, Animal* animal);
s32 mNpcW_CheckDiffBlockWalkNpcHome(s32 blockX, s32 blockZ, NpcInfo* info);
void mNpcW_SetHomeBlockSource(NpcWalk* walk, Animal* animal);
void mNpcW_InitGoalBlockSource(NpcWalk* walk, Animal* animal);
void mNpcW_SetGoalBlock(NpcInfo* info);
void mNpcW_InitNpcWalk(NpcWalk* walk);
s32 mNpcW_GetAppearStatusWay(u8* status, u8* way, Animal* animal);
s32* mNpcW_GetArriveStayCountP(s32 idx);
s32 mNpcW_GetWalkInfoStatusGoalAnimalIdx(s32* status, s32* goal, s32 idx);
s32 mNpcW_GetNearGate(s32* targetUtX, s32* targetUtZ, s32 blockX, s32 blockZ, s32 utX, s32 utZ);

#endif
