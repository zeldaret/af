#ifndef M_PRIVATE_INTERNALS_H
#define M_PRIVATE_INTERNALS_H

#include "ultra64.h"
#include "m_land.h"
#include "lb_rtc.h"

#define mPr_POCKETS_SLOT_COUNT 15
#define mPr_DELIVERY_QUEST_NUM mPr_POCKETS_SLOT_COUNT
#define mPr_ERRAND_QUEST_NUM 5

#define mPr_MOTHER_MAIL_NORMAL_NUM 7
#define mPr_MOTHER_MAIL_MONTHLY_NUM 2

#define PLAYER_NAME_LEN 6

typedef struct PersonalID_c {
	/* 0x00 */ char playerName[PLAYER_NAME_LEN];
    /* 0x06 */ char landName[LAND_NAME_SIZE];
	/* 0x0C */ u16 playerId;
	/* 0x0E */ u16 landId;
} PersonalID_c; // size = 0x10 

typedef struct mPr_map_info_c {
	/* 0x00 */ char landName[LAND_NAME_SIZE];
	/* 0x06 */ u16 landId;
} mPr_map_info_c; // size = 0x8

typedef struct PrivateAnimalMemory{
    /* 0x00 */ u16 npcId; 
    /* 0x02 */ char landName[LAND_NAME_SIZE];
}PrivateAnimalMemory; // size 0x8

typedef struct PrivateInventory {
    /* 0x00 */ u16 pockets[mPr_POCKETS_SLOT_COUNT]; /* items in inventory */
    /* 0x1E */ u8 lotto_ticket_expiry_month;
    /* 0x1F */ u8 lotto_ticket_mail_storage;
    /* 0x20 */ u32 item_conditions; /* bitfield (15 values), 2 bits per pocket slot */
    /* 0x24 */ u32 wallet;
    /* 0x28 */ u32 loan;
} PrivateInventory; // size = 0x2C

typedef struct PrivateCloth {
    /* 0x00 */ u16 id;
    /* 0x02 */ u16 item;
} PrivateCloth; // size = 0x4

typedef struct PrivateDestiny {
    /* 0x00 */ lbRTC_time_c receivedTime; /* time fortune was received */
    /* 0x08 */ u8 type; /* fortune type */ 
} PrivateDestiny; // size = 0xA

typedef struct PrivateMotherMailData {
    /* 0x0 */ u8 normal[mPr_MOTHER_MAIL_NORMAL_NUM];
    /* 0x7 */ u8 monthly[mPr_MOTHER_MAIL_MONTHLY_NUM];
    /* 0x9 */ u8 august; // unique byte for month of august
} PrivateMotherMailData; // size = 0xA

typedef struct PrivateMotherMail {
    /* 0x0 */ lbRTC_ymd_t date;
    /* 0x8 */ PrivateMotherMailData data;
} PrivateMotherMail; // size = 0xE

typedef struct PrivateBirthday{
    /* 0x0 */ u16 year;
    /* 0x2 */ u8 month;
    /* 0x3 */ u8 day;
}PrivateBirthday; // size = 0x4


#endif
