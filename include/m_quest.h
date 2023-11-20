#ifndef M_QUEST_H
#define M_QUEST_H

#include "ultra64.h"

/* 'Not Saved' Quest */
typedef struct mQst_not_saved_c {
  /* 0x00 */ s32 work;
  /* 0x04 */ u8 h;
} mQst_not_saved_c; // size = 0x5

typedef struct mQst_delivery_c {
  /* 0x00 */ char unk00[0x24];
} mQst_delivery_c; // size = 0x24

typedef struct mQst_errand_c {
  /* 0x00 */ char unk00[0x50];
} mQst_errand_c; // size = 0x50

typedef struct QuestContest {
  /* 0x00 */ mQst_base_c base; /* quest base struct */
  /* 0x0C */ u16 requestedItem; /* item (if any) requested by the villager */
  /* 0x0E */ PersonalID_c playerId; /* personal id of the player */
  /* 0x22 */ s8 type; /* type of quest, seems to be repeat of data in quest base */
  /* 0x23 */ mQst_contest_info_u info; /* contest info for flower & letter quests */
} QuestContest;

#endif
