#ifndef M_PRIVATE_H
#define M_PRIVATE_H

#include "ultra64.h"
#include "m_quest.h"

#define mPr_FOREIGN_MAP_COUNT 8
#define PLAYER_NUM 4

typedef enum mPr_SEX {
    /* 0 */ mPr_SEX_MALE,
    /* 1 */ mPr_SEX_FEMALE,

    /* 2 */ mPr_SEX_NUM
} mPr_SEX;

typedef enum mPr_ITEM_COND{
    /* 0 */ mPr_ITEM_COND_NORMAL,
    /* 1 */ mPr_ITEM_COND_PRESENT,
    /* 2 */ mPr_ITEM_COND_QUEST,

    /* 3 */ mPr_ITEM_COND_NUM
} mPr_ITEM_COND;

#define mPr_POCKETS_SLOT_COUNT 15
#define mPr_DELIVERY_QUEST_NUM mPr_POCKETS_SLOT_COUNT
#define mPr_ERRAND_QUEST_NUM 5

typedef struct Private_Sub_A86 {
    /* 0x00 */ char unk00[0x3];
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ char unk04[0x1];
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ u8 unk_08;
} Private_Sub_A86; // size >= 0xA

typedef struct mPr_map_info_c {
  /* 0x00 */ char unk00[0x8];
} mPr_map_info_c; // size = 0x8

typedef struct PrivateInventory {
    /* 0x00 */ u16 pockets[mPr_POCKETS_SLOT_COUNT]; /* items in inventory */
    /* 0x1E */ u8 lotto_ticket_expiry_month;
    /* 0x1F */ u8 lotto_ticket_mail_storage;
    /* 0x20 */ u32 item_conditions; /* bitfield (15 values), 2 bits per pocket slot */
    /* 0x24 */ u32 wallet;
    /* 0x28 */ u32 loan;
} PrivateInventory; // size = 0x2C

typedef struct Private_c {
    /* 0x000 */ char unk000[0x10];
    /* 0x010 */ s8 gender;
    /* 0x011 */ char unk011[0x3];
    /* 0x014 */ PrivateInventory inventory;
    /* 0x040 */ mQst_delivery_c deliveries[mPr_DELIVERY_QUEST_NUM]; /* delivery quests */
    /* 0x25C */ mQst_errand_c errands[mPr_ERRAND_QUEST_NUM]; /* errand quests */
    /* 0x3EC */ char unk3EC[0x688];
    /* 0xA74 */ u8 exists;
    /* 0xA75 */ char unkA75[0x11];
    /* 0xA86 */ Private_Sub_A86 unk_A86;
    /* 0xA90 */ char unkA8F[0xF8];
    /* 0xB88 */ mPr_map_info_c maps[mPr_FOREIGN_MAP_COUNT]; /* maps 'collected' for foreign towns */
    /* 0xBC8 */ char unkBC8[0x8];
} Private_c; // size = 0xBD0

#endif
