#ifndef M_HOME_H_H
#define M_HOME_H_H

#include "ultra64.h"

#define HOME_MAILBOX_SIZE 10
#define HANIWA_ITEM_HOLD_NUM 4
#define HANIWA_MESSAGE_LEN 64

enum {
  mHm_ROOM_MAIN,
  mHm_ROOM_UPPER,
  mHm_ROOM_BASEMENT,

  mHm_ROOM_NUM
};

enum {
  mHm_ROOMTYPE_SMALL,
  mHm_ROOMTYPE_MEDIUM,
  mHm_ROOMTYPE_LARGE,
  mHm_ROOMTYPE_COTTAGE,

  mHm_ROOMTYPE_NUM
};

enum {
  mHm_HOMESIZE_SMALL,   /* initial size */
  mHm_HOMESIZE_MEDIUM,  /* paid off first debt */
  mHm_HOMESIZE_LARGE,   /* paid off second debt (excluding basement) */
  mHm_HOMESIZE_UPPER,   /* paid off third debt & basement */
  mHm_HOMESIZE_STATUE,  /* paid off final debt */

  mHm_HOMESIZE_NUM
};

typedef struct Haniwa_Item_c {
  /* 0x00 */ mActor_name_t item; /* held item */
  /* 0x02 */ s16 exchange_type; /* type of exchange (sale, free, trade) */
  /* 0x04 */ u16 extra_data; /* trade related data */
} Haniwa_Item_c; // size = 0x6

typedef struct Haniwa_c {
  /* 0x00 */ Haniwa_Item_c items[HANIWA_ITEM_HOLD_NUM]; /* held items */
  /* 0x18 */ u8 message[HANIWA_MESSAGE_LEN]; /* message for visitors */
  /* 0x58 */ u32 bells; /* held bells from selling items */
} Haniwa_c; // size = 0x5C

typedef struct mHm_hs_c {
  /* 0x000 */ char unk000[0x22];
  /* 0x022 */ u8 unk_022;
  /* 0x023 */ char unk023[0x1];
  /* 0x024 */ u8 unk_024;
  /* 0x025 */ char unk025[0xABB];
  /* 0xAE0 */ Haniwa_c haniwa;
  /* 0xB3C */ char unkB3C[0xC];
} mHm_hs_c; // size = 0xB48


#endif
