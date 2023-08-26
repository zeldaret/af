#ifndef M_PRIVATE_H
#define M_PRIVATE_H

#include "ultra64.h"
#include "m_quest.h"
#include "lb_rtc.h"

#define FOREIGN_MAP_COUNT 8
#define PLAYER_NUM 4

typedef enum SEX {
    /* 0 */ SEX_MALE,
    /* 1 */ SEX_FEMALE,

    /* 2 */ SEX_NUM
} SEX;

typedef enum ITEM_COND {
    /* 0 */ ITEM_COND_NORMAL,
    /* 1 */ ITEM_COND_PRESENT,
    /* 2 */ ITEM_COND_QUEST,

    /* 3 */ ITEM_COND_NUM
} ITEM_COND;

#define POCKETS_SLOT_COUNT 15
#define DELIVERY_QUEST_NUM POCKETS_SLOT_COUNT
#define ERRAND_QUEST_NUM 5

typedef struct Destiny {
    /* 0x00 */ LBRTCTime receivedTime; /* time fortune was received */
    /* 0x08 */ u8 type; /* fortune type */ 
} Destiny; // size = 0xA

typedef struct AnimalMemory {
  /* 0x00 */ u16 npcId;
  /* 0x01 */ u8 landName[LAND_NAME_SIZE];
} AnimalMemory; // size = 0x8

typedef struct MapInfo {
  /* 0x00 */ char unk00[0x8];
} MapInfo; // size = 0x8

typedef struct PrivateInventory {
    /* 0x00 */ u16 pockets[POCKETS_SLOT_COUNT]; /* items in inventory */
    /* 0x1E */ u8 lottoTicketExpiryMonth;
    /* 0x1F */ u8 lottoTicketMailStorage;
    /* 0x20 */ u32 itemConditions; /* bitfield (15 values), 2 bits per pocket slot */
    /* 0x24 */ u32 wallet;
    /* 0x28 */ u32 loan;
} PrivateInventory; // size = 0x2C

typedef struct Private {
    /* 0x000 */ PersonalId playerId;
    /* 0x010 */ s8 gender;
    /* 0x011 */ char unk011[0x3];
    /* 0x014 */ PrivateInventory inventory;
    /* 0x040 */ QuestDelivery deliveries[DELIVERY_QUEST_NUM]; /* delivery quests */
    /* 0x25C */ QuestErrand errands[ERRAND_QUEST_NUM]; /* errand quests */
    /* 0x3EC */ char unk3EC[0x688];
    /* 0xA74 */ u8 exists;
    /* 0xA75 */ char unkA75[0x11];
    /* 0xA86 */ Destiny destiny; /* player fortune, seemingly called destiny */
    /* 0xA90 */ char unkA8F[0x3C];
    /* 0xACC */ AnmRemail remail; /* scheduled mail received from a foreign villager? */
    /* 0xADE */ char unkADE[0x6];
    /* 0xAE4 */ AnimalMemory animalMemory; /* id and town of last animal to move to another town */
    /* 0xAEC */ char unkAEC[0x9C];
    /* 0xB88 */ MapInfo maps[FOREIGN_MAP_COUNT]; /* maps 'collected' for foreign towns */
    /* 0xBC8 */ char unkBC8[0x8];
} Private; // size = 0xBD0

#endif
