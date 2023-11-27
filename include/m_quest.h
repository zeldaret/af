#ifndef M_QUEST_H
#define M_QUEST_H

#include "ultra64.h"
#include "lb_rtc.h"
#include "m_private_internals.h"
#include "m_npc_base.h"

typedef struct QuestBase {
    /* 0x00 */ u32 questType:2; /* type, 0 = delivery, 1 = errand, 2 = contest, 3 = none */
    /* 0x00 */ u32 questKind:6; /* kind, differs by type */
    /* 0x01 */ u32 timeLimitEnabled:1; /* when set, the time limit will be utilized */
    /* 0x01 */ u32 progress:4; /* progress towards quest goal */
    /* 0x01 */ u32 giveReward:1; /* set to true when player cannot take the item, and will skip quest completion checks */
    /* 0x01 */ u32 unused:2;
 
    /* 0x02 */ lbRTC_time_c timeLimit;
} QuestBase; // size = 0xC

/* 'Not Saved' Quest */
typedef struct mQst_not_saved_c {
    /* 0x00 */ s32 work;
    /* 0x04 */ u8 h;
} mQst_not_saved_c; // size = 0x5

typedef struct mQst_delivery_c {
    /* 0x00 */ char unk00[0x24];
} mQst_delivery_c; // size = 0x24

typedef struct QuestFirstJob {
    /* 0x00 */ AnmPersonalID_c usedId[2]; /* villagers already used for first job quest (furniture, then letter) */
    /* 0x1C */ u8 usedNum:7; /* used count for 'used_ids' */
    /* 0x1C */ u8 wrongNum:1; /* set to TRUE if player changes out of work uniform during chores */
} QuestFirstJob;

typedef struct QuestErrandChain {
    /* 0x00 */ AnmPersonalID_c usedId[3];
    /* 0x24 */ u8 usedNum;
} QuestErrandChain; // size 0x26


typedef union ErrandInfo{
    /* 0x00 */ QuestErrandChain chain;
    /* 0x12 */ QuestFirstJob firstJob;
} ErrandInfo; // size = 0x24

typedef struct QuestErrand {
    /* 0x00 */ QuestBase base; /* quest base info */
    /* 0x0C */ AnmPersonalID_c recipient; /* villager who will receive it */
    /* 0x1A */ AnmPersonalID_c sender; /* villager who sent it */
    /* 0x28 */ u16 item; /* errand item */
    /* 0x2A */ s8 pocketIdx:5; /* index in player pockets where the errand item is */
    /* 0x2A */ s8 errandType:3; /* errand type */
    /* 0x2C */ ErrandInfo info; /* errand type-specific data */
} QuestErrand; // size = 0x50

typedef struct QuestContest {
    /* 0x00 */ char unk00[0x24];
} QuestContest; // size = 0x24


void mQst_ClearQuestInfo(QuestBase*);
void mQst_ClearDelivery(mQst_delivery_c* deliveries, s32 count);
void mQst_ClearErrand(QuestErrand* errands, s32 count);
void mQst_ClearContest(QuestContest* contest);
void mQst_ClearNotSaveQuest(mQst_not_saved_c* quest);
// void func_800BA7E8_jp();
// void func_800BA8A0_jp();
// void func_800BA8F4_jp();
// void func_800BAA10_jp();
// void func_800BAA7C_jp();
// void func_800BAAA4_jp();
// void func_800BABE8_jp();
// void func_800BAC84_jp();
// void func_800BACEC_jp();
// void func_800BADBC_jp();
// void func_800BAE78_jp();
UNK_RET mQst_CheckLimitbyPossessionIdx(s32 arg0);
// void func_800BB0A8_jp();
// void func_800BB0E8_jp();
// void func_800BB10C_jp();
// void func_800BB270_jp();
// void func_800BB3A4_jp();
// void func_800BB4B0_jp();
s32 mQst_GetOccuredContestIdx(s32);
// void func_800BB634_jp();
// void func_800BB658_jp();
// void func_800BB67C_jp();
// void func_800BB6A0_jp();
// void func_800BB6F0_jp();
// void func_800BB740_jp();
// void func_800BB86C_jp();
// void func_800BB990_jp();
// void func_800BBAB0_jp();
void mQst_SetReceiveLetter(QuestContest*, PersonalID_c*, u8*, u16);
QuestErrand* mQst_GetFirstJobData(void);
// void func_800BBCBC_jp();
// void func_800BBD00_jp();
// void func_800BBD68_jp();
// void func_800BBD90_jp();
// void func_800BBDE0_jp();
// void func_800BBE78_jp();
// void func_800BBEE0_jp();
// void func_800BBF3C_jp();
// void func_800BBF98_jp();
// void func_800BC064_jp();
// void func_800BC10C_jp();
// void func_800BC12C_jp();
// void func_800BC14C_jp();
// void func_800BC1E4_jp();
// void func_800BC28C_jp();
// void func_800BC33C_jp();
// void func_800BC368_jp();
// void func_800BC394_jp();
s32 mQst_GetRandom(s32);
// void func_800BC454_jp();
// void func_800BC528_jp();
// void func_800BC5D4_jp();
// void func_800BC6B0_jp();
// void func_800BC724_jp();
// void func_800BC830_jp();
// void mQst_PrintQuestInfo();

#endif
