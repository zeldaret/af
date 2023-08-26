#ifndef M_QUEST_H
#define M_QUEST_H

#include "ultra64.h"
#include "m_personal_id.h"

typedef struct QuestBase {
  /* 0x00 */ u32 questType:2; /* type, 0 = delivery, 1 = errand, 2 = contest, 3 = none */
  /* 0x00 */ u32 questKind:6; /* kind, differs by type */
  /* 0x01 */ u32 timeLimitEnabled:1; /* when set, the time limit will be utilized */
  /* 0x01 */ u32 progress:4; /* progress towards quest goal */
  /* 0x01 */ u32 giveReward:1; /* set to true when player cannot take the item, and will skip quest completion checks */
  /* 0x01 */ u32 unused:2;

  /* 0x02 */ LBRTCTime timeLimit;
} QuestBase; // size = 0xC

/* 'Not Saved' Quest */
typedef struct QuestNotSaved {
  /* 0x00 */ s32 work;
  /* 0x04 */ u8 h;
} QuestNotSaved; // size = 0x5

typedef struct QuestDelivery {
  /* 0x00 */ char unk00[0x24];
} QuestDelivery; // size = 0x24

typedef union QuestContestInfo {
  struct {
    /* 0x00 */ u8 flowersRequested; /* number of flowers village requests be planted in acre */
  } flowerData;

  struct {
    /* 0x00 */ u8 score; /* score rank of letter */
    /* 0x02 */ u16 present; /* present sent with letter */
  } letterData;
} QuestContestInfo; // size = 0x4

typedef struct QuestContest {
  /* 0x00 */ QuestBase base; /* quest base struct */
  /* 0x0C */ u16 requestedItem; /* item (if any) requested by the villager */
  /* 0x0E */ PersonalId playerId; /* personal id of the player */
  /* 0x1E */ s8 type; /* type of quest, seems to be repeat of data in quest base */
  /* 0x20 */ QuestContestInfo info; /* contest info for flower & letter quests */
} QuestContest; // size = 0x24

typedef struct QuestErrand {
  /* 0x00 */ QuestBase base;
  /* 0x0C */ char unk0C[0x44];
} QuestErrand; // size = 0x50

#endif
