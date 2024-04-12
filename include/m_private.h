#ifndef M_PRIVATE_H
#define M_PRIVATE_H

#include "ultra64.h"
#include "m_mail.h"
#include "m_quest.h"
#include "m_private_internals.h"
#include "m_npc.h"
#include "m_museum.h"
#include "unk.h"

#define mPr_FOREIGN_MAP_COUNT 8
#define mPr_INVENTORY_MAIL_COUNT 10
#define PLAYER_NUM 4
#define mPR_FOREIGNER_NUMBER 4 

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

#define mPr_GET_ITEM_COND(allCond, slot) (((allCond) >> (((u32)(slot)) << 1)) & mPr_ITEM_COND_NUM)

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
    /* 0x012 */ s8 resetCount; 
    /* 0x013 */ MuseumRecord museumRecord;
    /* 0x014 */ PrivateInventory inventory;
    /* 0x040 */ mQst_delivery_c deliveries[mPr_DELIVERY_QUEST_NUM]; /* delivery quests */
    /* 0x25C */ QuestErrand errands[mPr_ERRAND_QUEST_NUM]; /* errand quests */
    /* 0x3EC */ UNK_TYPE1 unk_3EC[0x2];
    /* 0x3EE */ MailHeaderCommon savedMailHeader;
    /* 0x40A */ Mail_c mail[mPr_INVENTORY_MAIL_COUNT];
    /* 0xA72 */ u16 backgroundTextureId;
    /* 0xA74 */ u8 exists;
    /* 0xA75 */ u8 hintCount;
    /* 0xA76 */ PrivateCloth cloth;
    /* 0xA7A */ AnmPersonalID_c storedAnmId;
    /* 0xA86 */ PrivateDestiny destiny;
    /* 0xA90 */ PrivateBirthday birthday;
    /* 0xA94 */ UNK_TYPE1 unk_A94[0x28];
    /* 0xABC */ s32 completedFish;
    /* 0xAC0 */ s32 completedInsect;
    /* 0xAC4 */ UNK_TYPE1 unk_AC4[0x8];
    /* 0xACC */ Anmremail remail;
    /* 0xADE */ UNK_TYPE1 unk_ADE[0x6];
    /* 0xAE4 */ PrivateAnimalMemory animalMemory;
    /* 0xAEC */ u8 completeFishInsectFlags;
    /* 0xAEF */ UNK_TYPE1 unk_AEF[0x2];
    /* 0x108 */ u32 catalogFurniture[30];
    /* 0x1B4 */ u32 catalogWallpaper[2];
    /* 0x1C0 */ u32 catalogCarpet[2];
    /* 0x1CC */ u32 catalogPaper[2];
    /* 0x1D4 */ u32 catalogMusic[2];
    /* 0xB88 */ mPr_map_info_c maps[mPr_FOREIGN_MAP_COUNT];
    /* 0xBC8 */ UNK_TYPE1 unk_BC8[0x8];
} PrivateInfo; // size = 0xBD0

void mPr_ClearPlayerName(char* buf);
void mPr_CopyPlayerName(char* dst, char* src);
s32 mPr_NullCheckPlayerName(char* name);
s32 mPr_CheckCmpPlayerName(char* name0, char* name1);
s32 mPr_GetPlayerName(char* buf, s32 playerNumber);
s32 mPr_NullCheckPersonalID(PersonalID_c* pid);
void mPr_ClearPersonalID(PersonalID_c* pid);
void mPr_ClearAnyPersonalID(PersonalID_c* pid, s32 count);
void mPr_CopyPersonalID(PersonalID_c* dst, PersonalID_c* src);
s32 mPr_CheckCmpPersonalID(PersonalID_c* pid0, PersonalID_c* pid1);
void mPr_ClearPrivateBirthday(PrivateBirthday* birthday);
void mPr_ClearAnimalMemory(PrivateAnimalMemory* memory);
void mPr_ClearPrivateInfo(PrivateInfo* info);
s32 mPr_GetRandomFace(void);
s32 mPr_GetRandomOriginalFace(void);
u16 mPr_GetRandomCloth(u8 sex);
void mPr_SetNowPrivateCloth(void);
void mPr_InitPrivateInfo(PrivateInfo* priv);
void mPr_InitAnyPrivates(PrivateInfo* info, s32 amount);
void mPr_CopyPrivateInfo(PrivateInfo* dst, PrivateInfo* src);
s32 mPr_CheckPrivate(PrivateInfo* priv);
s32 mPr_CheckCmpPrivate(PrivateInfo* priv0, PrivateInfo* priv1);
s32 mPr_GetPrivateIdx(PersonalID_c* pid);
s32 mPr_GetPossessionItemIdx(PrivateInfo* priv, u16 item);
s32 mPr_GetPossessionItemIdxWithCond(PrivateInfo* priv, u16 item, u32 cond);
s32 mPr_GetPossessionItemIdxFGTypeWithCond_cancel(PrivateInfo* priv, u16 fg_type, u32 cond);
s32 mPr_GetPossessionItemIdxItem1Category(PrivateInfo* priv, u8 type);
s32 mPr_GetPossessionItemIdxItem1CategoryWithCond_cancel(PrivateInfo* priv, u8 itemType, u32 cond);
s32 mPr_GetPossessionItemIdxKindWithCond(PrivateInfo* priv, u16 kind_start, u16 kind_end, u32 cond);
s32 mPr_GetPossessionItemSum(PrivateInfo* priv, u16 item);
s32 mPr_GetPossessionItemSumWithCond(PrivateInfo* priv, u16 item, u32 cond);
s32 mPr_GetPossessionItemSumFGTypeWithCond_cancel(PrivateInfo* priv, u16 fg_type, u32 cond);
s32 mPr_GetPossessionItemSumItemCategoryWithCond_cancel(PrivateInfo* priv, u8 itemType, u32 cond);
void mPr_SetItemCollectBit(u16 item);
u16 mPr_DummyPresentToTruePresent(void);
void mPr_SetPossessionItem(PrivateInfo* priv, s32 idx, u16 item, u32 cond);
s32 mPr_SetFreePossessionItem(PrivateInfo* priv, u16 item, u32 cond);
void mPr_AddFirstJobHint(PrivateInfo* priv);
s32 mPr_GetFirstJobHintTime(PrivateInfo* priv);
s32 mPr_CheckFirstJobHint(PrivateInfo* priv);
s16 mPr_GetMoneyPower(void);
s16 mPr_GetGoodsPower(void);
s32 mPr_CheckMuseumAddress(PrivateInfo* priv);
s32 mPr_CheckMuseumInfoMail(PrivateInfo* priv);
s32 mPr_LoadPak_and_SetPrivateInfo2(u8 player, void* pak);
void mPr_ClearMotherMailInfo(PrivateMotherMail* motherMail);
s32 mPr_GetMotherMailPaperType(s32 month, s32 day);
void mPr_GetMotherMail(Mail_c* mail, PersonalID_c* pid, u16 present, s32 stationery, s32 mailNumber);
s32 mPr_SendMotherMailPost(PersonalID_c* pid, s32 playerNumber, u16 present, s32 stationery, s32 mailNumber);
s32 mPr_SendMotherMailDate(PrivateMotherMail* motherMail, lbRTC_time_c* sendTime);
s32 mPr_CheckMotherMailMonthly(PrivateMotherMailData* sendData, s32 month, s32 idx);
s32 mPr_GetMotherMailMonthlyNotSendNum(PrivateMotherMailData* sendData, s32 month);
void mPr_SetMotherMailMonthly(PrivateMotherMailData* sendData, s32 month, s32 idx);
void mPr_GetMotherMailMonthlyData(PrivateMotherMailData* sendData, s32* mailNumber, u16* present,
                                  s32* eventNumber, s32 month, s32 notSendNum);
s32 mPr_GetMotherMailNormalNotSendNum(PrivateMotherMailData* sendData);
void mPr_SetMotherMailNormal(PrivateMotherMailData* sendData, s32 idx);
s32 mPr_CheckMotherMailNormal(PrivateMotherMailData* sendData, s32 idx);
void mPr_GetMotherMailNormalData(PrivateMotherMailData* sendData, s32* mailNumber, u16* present, s32* eventNumber,
                                 s32 noSendNum);
void mPr_SendMotherMailNormal(PrivateMotherMail* motherMail, lbRTC_time_c* sendTime);
void mPr_SendMotherMail(PrivateMotherMail* motherMail, lbRTC_time_c* sendTime);
void mPr_SendMailFromMother(void);
void mPr_GetForeingerAnimalMail(Mail_c* mail, PrivateInfo* priv, PrivateAnimalMemory* animalMemory);
void mPr_SendForeingerAnimalMail(PrivateInfo* priv);
void mPr_StartSetCompleteTalkInfo(void);
void mPr_SetCompleteTalk(u8* flags, s32 type);
s32 mPr_GetCompleteTalk(u8 flags, s32 type);
void mPr_SetFishCompleteTalk(void);
s32 mPr_CheckFishCompleteTalk(u8 playerNumber);
void mPr_SetInsectCompleteTalk(void);
s32 mPr_CheckInsectCompleteTalk(u8 playerNumber);
s32 mPr_GetTalkPermission(u8 flags, s32 type);
s32 mPr_GetFishCompTalkPermission(void);
s32 mPr_GetInsectCompTalkPermission(void);
void mPr_ClearMapInfo(mPr_map_info_c* mapInfo, s32 max);
void mPr_CopyMapInfo(mPr_map_info_c* dst, mPr_map_info_c* src);
void mPr_SetMapThisLand(mPr_map_info_c* mapInfo);
s32 mPr_GetMapFreeIdx(mPr_map_info_c* mapInfo, s32 max);
s32 mPr_GetLandMapIdx(mPr_map_info_c* mapInfo, s32 max, LandInfo* landInfo);
s32 mPr_GetThisLandMapIdx(mPr_map_info_c* map_info, s32 max);
void mPr_PushMapInfo(mPr_map_info_c* map_info, s32 max);
void mPr_SetNewMap(mPr_map_info_c* map_info, s32 max);
void mPr_SetUseMap(mPr_map_info_c* map_info, s32 max);
void mPr_RenewalMapInfo(mPr_map_info_c* mapInfo, s32 max, LandInfo* landInfo);
void mPr_RandomSetPlayerData_title_demo(void);
void mPr_PrintMapInfo_debug(gfxprint* gfxprint);

#endif
