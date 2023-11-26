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

typedef enum Room {
    /* 0 */ ROOM_MAIN,
    /* 1 */ ROOM_UPPER,
    /* 2 */ ROOM_BASEMENT,
    /* 3 */ ROOM_NUM
} Room;

typedef enum RoomType {
    /* 0 */ ROOMTYPE_SMALL,
    /* 1 */ ROOMTYPE_MEDIUM,
    /* 2 */ ROOMTYPE_LARGE,
    /* 3 */ ROOMTYPE_COTTAGE,
    /* 4 */ ROOMTYPE_NUM
} RoomType;

typedef enum HomeSize {
    /* 0 */ HOMESIZE_SMALL,   // initial size
    /* 1 */ HOMESIZE_MEDIUM,  // paid off first debt
    /* 2 */ HOMESIZE_LARGE,   // paid off second debt (excluding basement)
    /* 3 */ HOMESIZE_UPPER,   // paid off third debt & basement
    /* 4 */ HOMESIZE_STATUE,  // paid off final debt
    /* 5 */ HOMESIZE_NUM
} HomeSize;

// original name, taken from m_flashrom
typedef struct Haniwa_Item_c {
    /* 0x00 */ u16 item; // held item
    /* 0x02 */ s16 exchangeType; // type of exchange (sale, free, trade)
    /* 0x04 */ u16 extraData; // trade related data
} Haniwa_Item_c; // size = 0x6

// original name, taken from m_flashrom
typedef struct Haniwa_c {
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
    /* 0x023 */ UNK_TYPE1 unk_023[0x1];
    /* 0x024 */ u8 unk_024;
    /* 0x025 */ UNK_TYPE1 unk_025[0x453];
    /* 0x478 */ Mail_c mailbox[HOME_MAILBOX_SIZE];
    /* 0xAE0 */ Haniwa_c haniwa;
    /* 0xB3C */ mHm_goki_c goki;
    /* 0xB42 */ UNK_TYPE1 unk_B42[0x6];
} mHm_hs_c; // size = 0xB48

#endif
