#ifndef C_6DE300_H
#define C_6DE300_H

#include "ultra64.h"
#include "unk.h"

struct QuestContest;
struct QuestDelivery;
struct QuestErrand;
struct QuestNotSaved;
struct RandomFieldGate;
struct MailName;
struct QuestBase;

void func_800BA660_jp(struct QuestBase* base);
void mQst_ClearDelivery(struct QuestDelivery* deliveries, s32 count);
void mQst_ClearErrand(struct QuestErrand* errands, s32 count);
void func_800BA778_jp(struct QuestContest* quest);
void mQst_ClearNotSaveQuest(struct QuestNotSaved* quest);
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
s32 func_800BB5DC_jp(s32 arg0);
// void func_800BB634_jp();
// void func_800BB658_jp();
// void func_800BB67C_jp();
// void func_800BB6A0_jp();
// void func_800BB6F0_jp();
// void func_800BB740_jp();
// void func_800BB86C_jp();
// void func_800BB990_jp();
// void func_800BBAB0_jp();
void func_800BBB30_jp(struct QuestContest* contest, struct MailName* mailName, u8* body, u16 present);
struct QuestErrand* func_800BBBEC_jp(void);
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
s32 func_800BC414_jp(s32 arg0);
// void func_800BC454_jp();
// void func_800BC528_jp();
// void func_800BC5D4_jp();
// void func_800BC6B0_jp();
// void func_800BC724_jp();
// void func_800BC830_jp();
// void mQst_PrintQuestInfo();
// void func_800BCBA0_jp();
// void func_800BCBDC_jp();
// void func_800BCC20_jp();
// void func_800BCC30_jp();
// void func_800BCC40_jp();
// void func_800BCCFC_jp();
// void func_800BCDCC_jp();
// void func_800BCDFC_jp();
// void func_800BCE80_jp();
// void func_800BCEA4_jp();
// void func_800BCF64_jp();
// void func_800BCFA4_jp();
struct RandomFieldGate* mRF_BlockTypeDirect2GateData(s32* gateCount, u8 blockType, s32 direct);
// void func_800BD02C_jp();
// void func_800BD1E4_jp();

#endif
