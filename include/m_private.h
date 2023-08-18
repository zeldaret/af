#ifndef M_PRIVATE_H
#define M_PRIVATE_H

#include "ultra64.h"
#include "m_quest.h"
#include "lb_rtc.h"

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

typedef struct mPr_destiny_c {
    /* 0x00 */ lbRTC_time_c received_time; /* time fortune was received */
    /* 0x08 */ u8 type; /* fortune type */ 
} mPr_destiny_c; // size = 0xA

typedef struct mPr_animal_memory_c {
  /* 0x00 */ u16 npc_id;
  /* 0x01 */ u8 land_name[LAND_NAME_SIZE];
} mPr_animal_memory_c; // size = 0x8

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
    /* 0x000 */ PersonalID_c player_ID;
    /* 0x010 */ s8 gender;
    /* 0x011 */ char unk011[0x3];
    /* 0x014 */ PrivateInventory inventory;
    /* 0x040 */ mQst_delivery_c deliveries[mPr_DELIVERY_QUEST_NUM]; /* delivery quests */
    /* 0x25C */ mQst_errand_c errands[mPr_ERRAND_QUEST_NUM]; /* errand quests */
    /* 0x3EC */ char unk3EC[0x688];
    /* 0xA74 */ u8 exists;
    /* 0xA75 */ char unkA75[0x11];
    /* 0xA86 */ mPr_destiny_c destiny; /* player fortune, seemingly called destiny */
    /* 0xA90 */ char unkA8F[0x3C];
    /* 0xACC */ Anmremail_c remail; /* scheduled mail received from a foreign villager? */
    /* 0xADE */ char unkADE[0x6];
    /* 0xAE4 */ mPr_animal_memory_c animal_memory; /* id and town of last animal to move to another town */
    /* 0xAEC */ char unkAEC[0x9C];
    /* 0xB88 */ mPr_map_info_c maps[mPr_FOREIGN_MAP_COUNT]; /* maps 'collected' for foreign towns */
    /* 0xBC8 */ char unkBC8[0x8];
} Private_c; // size = 0xBD0

#endif
