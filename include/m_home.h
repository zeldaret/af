#ifndef M_HOME_H_H
#define M_HOME_H_H

#include "ultra64.h"

#define HOME_MAILBOX_SIZE 10
#define HANIWA_ITEM_HOLD_NUM 4
#define HANIWA_MESSAGE_LEN 64

typedef struct HaniwaItem {
    /* 0x00 */ u16 item; /* held item */
    /* 0x02 */ s16 exchangeType; /* type of exchange (sale, free, trade) */
    /* 0x04 */ u16 extraData; /* trade related data */
} HaniwaItem; // size = 0x6

typedef struct Haniwa {
    /* 0x00 */ HaniwaItem items[HANIWA_ITEM_HOLD_NUM]; /* held items */
    /* 0x18 */ u8 message[HANIWA_MESSAGE_LEN]; /* message for visitors */
    /* 0x58 */ u32 bells; /* held bells from selling items */
} Haniwa; // size = 0x5C

typedef struct Home {
    /* 0x000 */ PersonalId ownerID; /* owner player's ID */
    /* 0x010 */ char unk010[0x12];
    /* 0x022 */ u8 unk_022;
    /* 0x023 */ char unk023[0x1];
    /* 0x024 */ u8 unk_024;
    /* 0x025 */ char unk025[0x453];
    /* 0x478 */ Mail mailbox[HOME_MAILBOX_SIZE]; /* mailbox */
    /* 0xAE0 */ Haniwa haniwa;
    /* 0xB3C */ char unkB3C[0xC];
} Home; // size = 0xB48


#endif
