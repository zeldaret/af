#ifndef M_QUEST_H
#define M_QUEST_H

#include "ultra64.h"
#include "m_personal_id.h"

typedef struct mQst_base_c {
  /* 0x00 */ u32 quest_type:2; /* type, 0 = delivery, 1 = errand, 2 = contest, 3 = none */
  /* 0x00 */ u32 quest_kind:6; /* kind, differs by type */
  /* 0x01 */ u32 time_limit_enabled:1; /* when set, the time limit will be utilized */
  /* 0x01 */ u32 progress:4; /* progress towards quest goal */
  /* 0x01 */ u32 give_reward:1; /* set to true when player cannot take the item, and will skip quest completion checks */
  /* 0x01 */ u32 unused:2;

  /* 0x02 */ lbRTC_time_c time_limit;
} mQst_base_c; // size = 0xC

/* 'Not Saved' Quest */
typedef struct mQst_not_saved_c {
  /* 0x00 */ s32 work;
  /* 0x04 */ u8 h;
} mQst_not_saved_c; // size = 0x5

typedef struct mQst_delivery_c {
  /* 0x00 */ char unk00[0x24];
} mQst_delivery_c; // size = 0x24

typedef union mQst_contest_info_u {
  struct {
    /* 0x00 */ u8 flowers_requested; /* number of flowers village requests be planted in acre */
  } flower_data;

  struct {
    /* 0x00 */ u8 score; /* score rank of letter */
    /* 0x02 */ u16 present; /* present sent with letter */
  } letter_data;
} mQst_contest_info_u; // size = 0x4

typedef struct mQst_contest_c {
  /* 0x00 */ mQst_base_c base; /* quest base struct */
  /* 0x0C */ u16 requested_item; /* item (if any) requested by the villager */
  /* 0x0E */ PersonalID_c player_id; /* personal id of the player */
  /* 0x1E */ s8 type; /* type of quest, seems to be repeat of data in quest base */
  /* 0x20 */ mQst_contest_info_u info; /* contest info for flower & letter quests */
} mQst_contest_c; // size = 0x24

typedef struct mQst_errand_c {
  /* 0x00 */ mQst_base_c base;
  /* 0x0C */ char unk0C[0x44];
} mQst_errand_c; // size = 0x50

#endif
