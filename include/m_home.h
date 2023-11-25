#ifndef M_HOME_H_H
#define M_HOME_H_H

#include "ultra64.h"
#include "unk.h"
#include "lb_rtc.h"
#include "m_private_internals.h"
#include "m_mail.h"

#define HOME_MAILBOX_SIZE 10
#define HANIWA_ITEM_HOLD_NUM 4
#define HANIWA_MESSAGE_LEN 64

typedef enum mHm_ROOM{
    /* 0 */ mHm_ROOM_MAIN,
    /* 1 */ mHm_ROOM_UPPER,
    /* 2 */ mHm_ROOM_BASEMENT,

    /* 3 */ mHm_ROOM_NUM
} mHm_ROOM;

typedef enum mHm_ROOMTYPE {
    /* 0 */ mHm_ROOMTYPE_SMALL,
    /* 1 */ mHm_ROOMTYPE_MEDIUM,
    /* 2 */ mHm_ROOMTYPE_LARGE,
    /* 3 */ mHm_ROOMTYPE_COTTAGE,

    /* 4 */ mHm_ROOMTYPE_NUM
} mHm_ROOMTYPE;

typedef enum mHm_HOMESIZE {
    /* 0 */ mHm_HOMESIZE_SMALL,   // initial size
    /* 1 */ mHm_HOMESIZE_MEDIUM,  // paid off first debt
    /* 2 */ mHm_HOMESIZE_LARGE,   // paid off second debt (excluding basement)
    /* 3 */ mHm_HOMESIZE_UPPER,   // paid off third debt & basement
    /* 4 */ mHm_HOMESIZE_STATUE,  // paid off final debt

    /* 5 */ mHm_HOMESIZE_NUM
}mHm_HOMESIZE;

// original name, taken from m_flashrom
typedef struct Haniwa_Item_c {
    /* 0x00 */ u16 item; // held item
    /* 0x02 */ s16 exchange_type; // type of exchange (sale, free, trade)
    /* 0x04 */ u16 extra_data; // trade related data
} Haniwa_Item_c; // size = 0x6

// original name, taken from m_flashrom
typedef struct HomeHaniwa {
    /* 0x00 */ Haniwa_Item_c items[HANIWA_ITEM_HOLD_NUM]; // held items
    /* 0x18 */ u8 message[HANIWA_MESSAGE_LEN]; // message for visitors
    /* 0x58 */ u32 bells; // held bells from selling items
} Haniwa_c; // size = 0x5C

// Original name, taken from m_flashrom
typedef struct mHm_goki_c {
  /* 0x00 */ lbRTC_ymd_t time;
  /* 0x04 */ u8 num;
  /* 0x05 */ u8 pad;
} mHm_goki_c; // size = 0x6

// Original name, taken from m_flashrom
typedef struct mHm_hs_c {
    /* 0x000 */ PersonalID_c ownerID;
    /* 0x010 */ UNK_TYPE1 unk_010[0x12];
    /* 0x022 */ u8 unk_022;
    /* 0x023 */ UNK_TYPE1 unk023[0x1];
    /* 0x024 */ u8 unk_024;
    /* 0x025 */ UNK_TYPE1 unk025[0x453];
    /* 0x478 */ Mail_c mailbox[HOME_MAILBOX_SIZE];
    /* 0xAE0 */ Haniwa_c haniwa;
    /* 0xB3C */ mHm_goki_c goki;
    /* 0xB42 */ UNK_TYPE1 unkB42[0x6];
} mHm_hs_c; // size = 0xB48


#endif
