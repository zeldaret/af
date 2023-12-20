#ifndef M_PRIVATE_H
#define M_PRIVATE_H

#include "ultra64.h"
#include "m_mail.h"
#include "m_quest.h"
#include "m_private_internals.h"
#include "m_npc.h"
#include "unk.h"

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

typedef enum mPr_FACE_TYPE {
    /* 0 */ mPr_FACE_TYPE0,
    /* 1 */ mPr_FACE_TYPE1,
    /* 2 */ mPr_FACE_TYPE2,
    /* 3 */ mPr_FACE_TYPE3,
    /* 4 */ mPr_FACE_TYPE4,
    /* 5 */ mPr_FACE_TYPE5,
    /* 6 */ mPr_FACE_TYPE6,
    /* 7 */ mPr_FACE_TYPE7,
    /* 8 */ mPr_FACE_TYPE_NUM   
} mPr_FACE_TYPE;

typedef struct PrivateInfo {
    /* 0x000 */ PersonalID_c playerId; 
    /* 0x010 */ s8 gender;
    /* 0x011 */ s8 face;
    /* 0x012 */ UNK_TYPE1 unk_012[0x2];
    /* 0x014 */ PrivateInventory inventory;
    /* 0x040 */ mQst_delivery_c deliveries[mPr_DELIVERY_QUEST_NUM]; /* delivery quests */
    /* 0x25C */ QuestErrand errands[mPr_ERRAND_QUEST_NUM]; /* errand quests */
    /* 0x3EC */ UNK_TYPE1 unk_3EC[0x2];
    /* 0x3EE */ MailHeaderCommon unk_3EE;
    /* 0x40A */ Mail_c unk_40A[10];
    /* 0xA72 */ UNK_TYPE1 unk_A72[0x2];
    /* 0xA74 */ u8 exists;
    /* 0xA75 */ UNK_TYPE1 unkA75[1];
    /* 0xA76 */ PrivateCloth cloth;
    /* 0xA7A */ UNK_TYPE1 unkA7A[0xC];
    /* 0xA86 */ Private_Sub_A86 unk_A86;
    /* 0xA90 */ UNK_TYPE1 unk_A90[0x3C];
    /* 0xACC */ Anmremail remail;   
    /* 0xADE */ UNK_TYPE1 unk_ADE[0x6];
    /* 0xAE4 */ PrivateAnimalMemory animalMemory;
    /* 0xAEC */ UNK_TYPE1 unk_AEC[0x9C]; 
    /* 0xB88 */ mPr_map_info_c maps[mPr_FOREIGN_MAP_COUNT]; /* maps 'collected' for foreign towns */
    /* 0xBC8 */ UNK_TYPE1 unk_BC8[0x8];
} PrivateInfo; // size = 0xBD0

void mPr_ClearPlayerName(char* arg0);
void mPr_CopyPlayerName(char* dst, char* src);
s32 mPr_NullCheckPlayerName(char* arg0);
// void func_800B7804_jp();
// void func_800B785C_jp();
s32 mPr_NullCheckPersonalID(PersonalID_c* arg0);
void mPr_ClearPersonalID(PersonalID_c* arg0);
// void func_800B7998_jp();
void mPr_CopyPersonalID(PersonalID_c* arg0, PersonalID_c* arg1);
s32 mPr_CheckCmpPersonalID(PersonalID_c* arg0, PersonalID_c* arg1);
// void func_800B7A94_jp();
// void func_800B7AB0_jp();
void mPr_ClearPrivateInfo(PrivateInfo* private);
// void func_800B7B8C_jp();
// void func_800B7BC0_jp();
// void func_800B7CD0_jp();
// void func_800B7D50_jp();
void mPr_InitPrivateInfo(PrivateInfo* private);
// void func_800B7F00_jp();
// void func_800B7F48_jp();
s32 mPr_CheckPrivate(PrivateInfo* private);
// void func_800B7FA0_jp();
s32 mPr_GetPrivateIdx(PersonalID_c* arg0);
// void func_800B8068_jp();
// void func_800B80B4_jp();
// void func_800B8128_jp();
// void func_800B81A4_jp();
// void func_800B8204_jp();
// void func_800B828C_jp();
// void func_800B8318_jp();
// void func_800B83D4_jp();
// void func_800B8544_jp();
// void func_800B86EC_jp();
// void func_800B88EC_jp();
// void func_800B8A88_jp();
void mPr_SetPossessionItem(PrivateInfo* priv, int idx, u16 item, u32 cond);
// void func_800B8B8C_jp();
// void func_800B8BE4_jp();
// void func_800B8C10_jp();
// void func_800B8C20_jp();
// void func_800B8C34_jp();
// void func_800B8C9C_jp();
// void func_800B8D18_jp();
// void func_800B8D3C_jp();
s32 func_800B8D64_jp(u8 player_no, s32 arg1);
void mPr_ClearMotherMailInfo(PrivateMotherMail* arg0);
// void func_800B8F20_jp();
// void func_800B8FB8_jp();
// void func_800B9038_jp();
// void func_800B9170_jp();
// void func_800B9350_jp();
// void func_800B93AC_jp();
// void func_800B947C_jp();
// void func_800B94E0_jp();
// void func_800B9704_jp();
// void func_800B9790_jp();
// void func_800B97C8_jp();
// void func_800B97F8_jp();
// void func_800B996C_jp();
// void func_800B9AF0_jp();
void func_800B9B2C_jp(void);
// void func_800B9C34_jp();
void mPr_SendForeingerAnimalMail(PrivateInfo* privateInfo);
void mPr_StartSetCompleteTalkInfo(void);
// void func_800B9E90_jp();
// void func_800B9EB4_jp();
// void func_800B9ED4_jp();
// void func_800B9F00_jp();
// void func_800B9F74_jp();
// void func_800B9FA0_jp();
// void func_800BA014_jp();
// void func_800BA054_jp();
// void func_800BA09C_jp();
// void func_800BA0E4_jp();
// void func_800BA130_jp();
// void func_800BA150_jp();
// void func_800BA18C_jp();
// void func_800BA214_jp();
// void func_800BA2B0_jp();
// void func_800BA2D4_jp();
// void func_800BA344_jp();
// void func_800BA3D0_jp();
void mPr_RenewalMapInfo(mPr_map_info_c* maps, s32 count, struct LandInfo* landInfo);
// void mPr_RandomSetPlayerData_title_demo();
// void mPr_PrintMapInfo_debug();

#endif
