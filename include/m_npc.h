#ifndef M_NPC_H
#define M_NPC_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"
#include "m_land.h"
#include "lb_rtc.h"
#include "libu64/gfxprint.h"
#include "m_quest.h"
#include "m_mail.h"
#include "m_private_internals.h"
#include "overlays/actors/ovl_Npc/ac_npc.h"
#include "m_field_make.h"
#include "m_npc_base.h"

#define ANIMAL_NUM_MIN 5
#define ANIMAL_NUM_MAX 15 /* Maximum number of villagers possible in town */

#define ANIMAL_MEMORY_NUM 7
#define ANIMAL_CATCHPHRASE_LEN 4
#define ANIMAL_NAME_LEN PLAYER_NAME_LEN

#define NPC_NUM 216

struct Game;
struct PrivateInfo;

typedef struct NpcHouseData{
    /* 0x00 */ u8 type;
    /* 0x01 */ u8 palette;
    /* 0x02 */ u8 wallId;
    /* 0x03 */ u8 floorId;
    /* 0x04 */ u16 mainLayerId;
    /* 0x06 */ u16 secondaryLayerId;
} NpcHouseData; // size = 0x8

typedef struct NpcListFlags{
    /* 0x00 */ u8 beeSting:1; // [8]
    /* 0x00 */ u8 fishComplete:1; // [7]
    /* 0x00 */ u8 insectComplete:1; // [6]
    /* 0x00 */ u8 unk3:6; // [5:0]
}NpcListFlags; //size = 0x1

typedef struct NpcList {
    /* 0x00 */ u16 name;
    /* 0x02 */ u16 fieldName;
    /* 0x04 */ xyz_t homePosition;
    /* 0x10 */ xyz_t position;
    /* 0x1C */ u8 appearFlag;
    /* 0x1D */ NpcListFlags flags;
    /* 0x1F */ u8 unk1F; 
    /* 0x20 */ QuestBase questInfo;
    /* 0x2C */ NpcHouseData houseData;
    /* 0x34 */ u16 rewardFurniture;
} NpcList; // size = 0x38

typedef struct Anmland{
    /* 0x00 */ u8 name[LAND_NAME_SIZE];
    /* 0x08 */ u16 id;
}Anmland; // size = 0x10

typedef struct Anmhome_c {
    /* 0x00 */ u8 typeUnused; /* Likely the house type, but seems to be unused outside of SChk_Anmhome_c_sub */
    /* 0x01 */ u8 blockX; /* acre x position */
    /* 0x02 */ u8 blockZ; /* acre y position */
    /* 0x03 */ u8 utX; /* unit x position */
    /* 0x04 */ u8 utZ; /* unit z position */
} Anmhome_c; // size = 0x5

typedef struct Anmlet {
    /* 0x00 */ u8 exists:1;   /* letter received by villager and exists */
    /* 0x00 */ u8 cond:1;   /* mNpc_LETTER_RANK_* */
    /* 0x00 */ u8 sendReply:1;   /* set when the villager should reply */
    /* 0x00 */ u8 hasPresentCloth:1;   /* set when the villager's held present shirt is from this letter */
    /* 0x00 */ u8 wearingPresentCloth:1;   /* set when a villager is wearing the shirt sent with the saved letter */
    /* 0x00 */ u8 unk5:3; /* seemingly unused */
} Anmlet; // size = 0x1

typedef struct AnmRemailFlags{
    /* 0x00 */ u8 cond:1;
    /* 0x00 */ u8 looks:7;
}AnmremailFlags; // size 0x1

typedef struct Anmremail {
    /* 0x00 */ lbRTC_ymd_t date; /* date sent */
    /* 0x04 */ u8 name[ANIMAL_NAME_LEN]; /* villager name */
    /* 0x0A */ u8 landName[LAND_NAME_SIZE]; /* town name */
    /* 0x10 */ AnmremailFlags flags;
} Anmremail; // size = 0x12

typedef struct Anmplmail_c {
  /* 0x000 */ u8 font; /* 'font' to use for letter info */
  /* 0x001 */ u8 paperType; 
  /* 0x002 */ u16 present;
  /* 0x004 */ u8 headerBackStart; /* position for name insertion in header */
  /* 0x005 */ u8 header[MAIL_HEADER_LEN];
  /* 0x00F */ u8 body[MAIL_BODY_LEN];
  /* 0x06F */ u8 footer[MAIL_FOOTER_LEN];
  /* 0x07F */ u8 unk7F; /* likely pad */
  /* 0x080 */ lbRTC_ymd_t date; /* sent date */
} Anmplmail_c; // size = 0x84

typedef struct AnmGoodbyeMail {
  /* 0x000 */ AnmPersonalID_c id;
  /* 0x00C */ u8 deliverTo;
} AnmGoodbyeMail; // size = 0xE

typedef struct Anmmem_c {
  /* 0x000 */ PersonalID_c memoryPlayerId; /* personal id of the player memory belongs to */
  /* 0x014 */ lbRTC_time_c lastSpeakTime; /* time the player last spoke to this villager */
  /* 0x01C */ Anmland land; /* union between town NPC land memory & islander player action memory */
  /* 0x028 */ u64 savedTownTune; /* memory origin town tune */
  /* 0x030 */ s8 friendship; /* friendship with the player */
  /* 0x031 */ Anmlet letterInfo; /* saved letter flags */
  /* 0x032 */ Anmplmail_c letter; /* saved letter */
} Anmmem_c; // size 0xB0

typedef struct Animal_c { 
    /* 0x000 */ AnmPersonalID_c id;
    /* 0x00C */ Anmmem_c memories[ANIMAL_MEMORY_NUM];  
    /* 0x4E0 */ Anmhome_c homeInfo;
    /* 0x4E5 */ u8 catchphrase[ANIMAL_CATCHPHRASE_LEN];
    /* 0x4E9 */ char unk4E9[0x3];
    /* 0x4EC */ QuestContest contestQuest;
    /* 0x4E9 */ u8 previousLandName[LAND_NAME_SIZE];
    /* 0x4E9 */ u8 parentName[ANIMAL_NAME_LEN]; 
    /* 0x51C */ u16 previousLandId;
    /* 0x4E9 */ u8 mood;
    /* 0x4E9 */ u8 moodTime;
    /* 0x4E9 */ u16 cloth;
    /* 0x4E9 */ u16 removeInfo;
    /* 0x4E9 */ u8 isHome;
    /* 0x4E9 */ u8 movedIn;
    /* 0x4E9 */ u8 isMoving;
} Animal_c; // size = 0x528

typedef struct SpecialNpcData {
    /* 0x00 */ u16 specialNpcId;
    /* 0x02 */ u16 sex;
    /* 0x04 */ s32 nameStringNumber;
    /* 0x08 */ s32 soundId;
} SpecialNpcData; // size = 0xC

typedef struct NpcDefaultData {
    /* 0x00 */ u16 cloth;
    /* 0x02 */ u16 catchphraseIdx;
    /* 0x04 */ s8 umbrella;
} NpcDefaultData; // size = 0x5

typedef struct NpcTalkInfo {
    /* 0x00 */ u16 timer;
    /* 0x02 */ u8 talkNum;
    /* 0x03 */ u8 questRequest;
    /* 0x04 */ u16 unlockTimer;
    /* 0x06 */ u16 resetTimer;
} NpcTalkInfo; // size = 0x8

typedef struct NpcTemper {
    /* 0x0 */ u16 unlockTimer;
    /* 0x2 */ u8 overImpatientNum;
    /* 0x3 */ u8 talkNumMax;
} NpcTemper; // size = 0x4

typedef struct NpcEvent{
    /* 0x0 */ u16 eventId;
    /* 0x2 */ u16 textureId;
    /* 0x4 */ u16 npcId; 
    /* 0x6 */ u16 clothId; 
    /* 0x8 */ u8 exists; 
    /* 0x9 */ u8 use;
    /* 0xA */ u16 unkA;
}NpcEvent; // size = 0xC

typedef struct DemoNpc {
    /* 0x0 */ u16 npcName; /* villager id */
    /* 0x2 */ u32 blockX; // spawn acre x
    /* 0x6 */ u32 blockZ; // spawn acre z
    /* 0xA */ u32 utX; // spawn unit x in acre
    /* 0xE */ u32 utZ; // spawn unit z in acre
} DemoNpc;



void mNpc_MakeRandTable(s32*, s32, s32);
void mNpc_ClearBufSpace1(u8*, s32);
void mNpc_AddNowNpcMax(u8*);
void mNpc_SubNowNpcMax(u8*);
void mNpc_ClearAnimalPersonalID(AnmPersonalID_c*);
s32 mNpc_CheckFreeAnimalPersonalID(AnmPersonalID_c*);
void mNpc_CopyAnimalPersonalID(AnmPersonalID_c*, AnmPersonalID_c*);
s32 mNpc_CheckCmpAnimalPersonalID(AnmPersonalID_c*, AnmPersonalID_c*);
s32 mNpc_GetAnimalNum(void);
s32 mNpc_CheckRemoveExp(Animal_c*);
s32 mNpc_GetRemoveTime(Animal_c*);
void mNpc_AddRemoveTime(Animal_c*);
void mNpc_SetRemoveExp(Animal_c*, u16);
void mNpc_SetParentName(Animal_c*, PersonalID_c*);
void mNpc_SetParentNameAllAnimal(void);
void mNpc_ClearAnimalMail(Anmplmail_c*);
void mNpc_CopyAnimalMail(Anmplmail_c*, Anmplmail_c*);
void mNpc_ClearAnimalMemory(Anmmem_c*, s32);
void mNpc_CopyAnimalMemory(Anmmem_c*, Anmmem_c*);
void mNpc_AddFriendship(Anmmem_c*, s32);
s32 mNpc_CheckFreeAnimalMemory(Anmmem_c*);
void mNpc_RenewalAnimalMemory(void);
s32 mNpc_GetOldAnimalMemoryIdx(Anmmem_c*, s32);
s32 mNpc_GetFreeAnimalMemoryIdx(Anmmem_c*, s32);
s32 mNpc_ForceGetFreeAnimalMemoryIdx(Anmmem_c*, s32);
void mNpc_SetAnimalMemory_NotSetDay(PersonalID_c*, Anmmem_c*);
void mNpc_SetAnimalMemory(PersonalID_c*, Anmmem_c*);
s32 mNpc_GetAnimalMemoryIdx(PersonalID_c*, Anmmem_c*, s32);
void mNpc_SetAnimalLastTalk(Animal_c*);
void mNpc_SetAnimalPersonalID2Memory(AnmPersonalID_c*);
s32 mNpc_GetHighestFriendshipIdx(Anmmem_c*, s32);
s32 mNpc_SelectBestFriend(Anmmem_c**, Anmmem_c*, s8*);
s32 mNpc_GetAnimalMemoryBestFriend(Anmmem_c*, s32);
s32 mNpc_GetAnimalMemoryFriend_Land_Sex(Anmmem_c*, s32, s32);
s32 mNpc_GetAnimalMemoryNum(Anmmem_c*, s32);
s32 mNpc_GetAnimalMemoryLetterNum(Anmmem_c*, s32);
s32 mNpc_GetAnimalMemoryLandKindNum(Anmmem_c*, s32);
void mNpc_ClearAnimalInfo(Animal_c*);
void mNpc_ClearAnyAnimalInfo(Animal_c*, s32);
s32 mNpc_CheckFreeAnimalInfo(Animal_c*);
s32 mNpc_GetFreeAnimalInfo(Animal_c*, s32);
s32 mNpc_UseFreeAnimalInfo(Animal_c*, s32);
void mNpc_CopyAnimalInfo(Animal_c*, Animal_c*);
s32 mNpc_SearchAnimalinfo(Animal_c*, u16, s32);
Animal_c* mNpc_GetAnimalInfoP(u16);
s32 mNpc_SearchAnimalPersonalID(AnmPersonalID_c*);
AnmPersonalID_c* mNpc_GetOtherAnimalPersonalIDOtherBlock(AnmPersonalID_c*, s32, s32, s32, s32);
AnmPersonalID_c* mNpc_GetOtherAnimalPersonalID(AnmPersonalID_c*, s32);
void mNpc_SetAnimalThisLand(Animal_c*, s32);
s32 mNpc_GetSameLooksNum(u8);
s32 mNpc_CheckNpcExistBlock(s32, s32, s32);
void mNpc_Mail2AnimalMail(Anmplmail_c*, Mail_c*);
void mNpc_AnimalMail2Mail(Mail_c*, Anmplmail_c*, PersonalID_c*, AnmPersonalID_c*);
s32 mNpc_CheckMailChar(u8);
s32 mNpc_CheckNormalMail_sub(s32*, u8*);
u8 mNpc_CheckNormalMail_length(s32*, u8*);
u8 mNpc_CheckNormalMail(u8*);
s32 mNpc_SetMailCondThisLand(Anmmem_c*, u8*);
s32 mNpc_SetMailCondOtherLand(Animal_c*, u8*);
s32 mNpc_SetRemailCond(Animal_c*, Anmmem_c*, u8*);
s32 mNpc_SendMailtoNpc(Mail_c*);
void mNpc_ClearRemail(Anmremail*);
void mNpc_GetRemailPresent(u16*);
s32 mNpc_GetHandbillz(Mail_c*, s32, s32, s32, s32, s32);
void mNpc_SetRemailFreeString(PersonalID_c*, AnmPersonalID_c*, Anmremail*);
void mNpc_GetRemailGoodData(Mail_c*, PersonalID_c*, AnmPersonalID_c*, Anmremail*, u8);
void mNpc_GetRemailWrongData(Mail_c*, PersonalID_c*, AnmPersonalID_c*, Anmremail*, u8);
void mNpc_GetRemailData(Mail_c*, PersonalID_c*, AnmPersonalID_c*, Anmremail*, s32, u8);
s32 mNpc_SendRemailPostOffice(PersonalID_c*, AnmPersonalID_c*, Anmremail*, s32, u8);
s32 mNpc_CheckLetterTime(lbRTC_ymd_t*, lbRTC_time_c*);
void mNpc_Remail(void);
u8 mNpc_GetPaperType(void);
void mNpc_LoadMailDataCommon2(Mail_c*, PersonalID_c*, AnmPersonalID_c*, u16, u8, s32);
void mNpc_GetEventPresent(u16*, s32);
void mNpc_GetEventMail(Mail_c*, PersonalID_c*, AnmPersonalID_c*, s32, s32);
s32 mNpc_SendEventPresentMail(PersonalID_c*, s32, AnmPersonalID_c*, s32);
void mNpc_SendEventPresentMailSex(s32*, u8*, Animal_c*, s32);
s32 mNpc_SendEventPresentMail_common(s32);
void mNpc_GetBirthdayPresent(u16*);
void mNpc_GetBirthdayCard(Mail_c*, PersonalID_c*, AnmPersonalID_c*);
s32 mNpc_SendBirthdayCard(PersonalID_c*, s32, AnmPersonalID_c*);
s32 mNpc_SendEventBirthdayCard(PersonalID_c*);
s32 mNpc_SendEventBirthdayCard2(PersonalID_c*, s32);
void mNpc_GetXmasCardData(Mail_c*, PersonalID_c*);
s32 mNpc_SendEventXmasCard(PersonalID_c*, s32);
void mNpc_SetWordEnding(Animal_c*, u8*);
u8* mNpc_GetWordEnding(Actor*);
void mNpc_ResetWordEnding(Actor*);
s32 mNpc_GetFreeEventNpcIdx(void);
s32 mNpc_RegistEventNpc(u16, u16, u16, u16);
void mNpc_UnRegistEventNpc(u16);
void mNpc_ClearEventNpc(void);
NpcEvent* mNpc_GetSameEventNpc(u16);
u8 mNpc_GetLooks(u16);
void mNpc_SetDefAnimalInfo(Animal_c*, u16, u8, NpcDefaultData*);
void mNpc_SetDefAnimal(Animal_c*, u16, NpcDefaultData*);
void mNpc_SetHaveAppeared(u16);
s32 mNpc_GetHaveAppeared_idx(s32);
s32 mNpc_GetLooks2NotHaveAppearedNum(u8);
void mNpc_ResetHaveAppeared_common(u8*, Animal_c*);
void mNpc_ResetHaveAppeared(void);
s32 mNpc_GetDefGrowPermission(s32, s8*, s32);
void mNpc_DecideLivingNpcMax(Animal_c*, u8, s32);
void mNpc_SetAnimalTitleDemo(DemoNpc*, Animal_c*, struct Game*);
s32 mNpc_GetReservedUtNum(s32*, s32*, u16*);
s32 mNpc_BlockNum2ReservedUtNum(s32*, s32*, s32, s32);
void mNpc_MakeReservedListBeforeFieldct(Anmhome_c*, s32, u8*);
void mNpc_MakeReservedListAfterFieldct(Anmhome_c*, s32, u8*, u8, u8);
void mNpc_BuildHouseBeforeFieldct(u16, s32, s32, s32, s32);
void mNpc_DestroyHouse(Anmhome_c*);
void mNpc_SetNpcHome(Animal_c*, Anmhome_c*, u8);
void mNpc_InitNpcData(void);
void mNpc_InitNpcList(void);
void mNpc_SetNpcList(NpcList*, Animal_c*, s32, s32);
void mNpc_SetNpcinfo(Actor*, s8);
void mNpc_AddNpc_inNpcRoom(FieldMakeMoveActor*, u8, u8);
void mNpc_RenewalNpcRoom(s16*);
void mNpc_RenewalSetNpc(Actor*);
s32 mNpc_GetFriendAnimalNum(PersonalID_c*);
s32 mNpc_CheckFriendAllAnimal(PersonalID_c*);
s32 mNpc_CheckSelectFurniture(u16);
u16 func_800AB8A0_jp(FieldMakeFGData**, NpcList*, s32);
void mNpc_SetNpcFurnitureRandom(FieldMakeFGData**, s32);
u16 mNpc_GetNpcFurniture(AnmPersonalID_c*);
void mNpc_ClearInAnimal(void);
Animal_c* mNpc_GetInAnimalP(void);
u8 mNpc_DecideRemoveAnimalNo(Animal_c*, s32);
void mNpc_SetRemoveAnimalNo(Animal_c*);
s32 mNpc_CheckGoodbyAnimalMemoryNum(Animal_c*, Animal_c*);
s32 mNpc_GetGoodbyAnimalIdx(void);
void mNpc_ClearGoodbyMail(AnmGoodbyeMail*);
void mNpc_FirstClearGoodbyMail(void);
void mNpc_SetGoodbyAnimalMail(AnmGoodbyeMail*, Animal_c*);
s32 mNpc_SetGoodbyMailData(Mail_c*, PersonalID_c*, AnmPersonalID_c*);
s32 mNpc_SendGoodbyAnimalMailOne(Mail_c*, struct PrivateInfo*, s32, AnmPersonalID_c*);
void mNpc_SendGoodbyAnimalMail(AnmGoodbyeMail*);
void mNpc_SendRegisteredGoodbyMail(void);
void mNpc_GetRemoveAnimal(Animal_c*, s32);
s32 mNpc_CheckBuildHouse(s32, s32, u8, u8);
void mNpc_SetReturnAnimal(Animal_c*);
void mNpc_AddActor_inBlock(FieldMakeMoveActor*, u8, u8);
void mNpc_SetNpcNameID(Animal_c*, s32);
void mNpc_LoadNpcNameString(u8*, u8);
void mNpc_GetNpcWorldNameTableNo(u8*, u16);
void mNpc_GetNpcWorldNameAnm(u8*, AnmPersonalID_c*);
void mNpc_GetNpcWorldNameP(u8*, u16);
void mNpc_GetNpcWorldName(u8*,Npc*);
void mNpc_GetRandomAnimalName(u8*);
void mNpc_GetAnimalPlateName(u8*, xyz_t);
s32 mNpc_GetNpcLooks(Actor*);
s32 mNpc_GetActorSex(u16);
s32 mNpc_GetLooks2Sex(s32);
s32 mNpc_GetAnimalSex(Animal_c*);
s32 mNpc_GetNpcSex(Actor*);
s32 mNpc_GetNpcSoundSpecNotAnimal(u16);
s32 mNpc_GetNpcSoundSpec(Actor*);
void mNpc_GetMsg(s32);
void mNpc_InitNpcAllInfo(s32);
s32 mNpc_CheckGrowFieldRank(void);
s32 mNpc_CheckGrow(void);
u8 mNpc_GetMinLooks(u8*, s32*);
s32 mNpc_GetMinSex(void);
s32 mNpc_GrowLooksNpcIdx(u8);
void mNpc_SetAnimalInfoNpcIdx(Animal_c*, s32);
s32 mNpc_SetGrowNpc(u8);
void mNpc_Grow(void);
s32 mNpc_CheckNpcSet_fgcol(u16, u32);
s32 mNpc_CheckNpcSet_fgcol_hard(u16, u32);
s32 mNpc_CheckNpcSet(s32, s32, s32, s32);
s32 mNpc_GetMakeUtNuminBlock_hard_area(s32*, s32*, s32, s32, s32);
s32 mNpc_GetMakeUtNuminBlock_area(s32*, s32*, s32, s32, s32);
s32 mNpc_GetMakeUtNuminBlock(s32*, s32*, s32, s32);
void mNpc_ClearTalkInfo(void);
void mNpc_TimerCountDown(NpcTalkInfo*);
void mNpc_SetUnlockTimer(u16*, u16*, s32);
s32 mNpc_CountTalkNum(s32, s32);
s32 mNpc_CheckOverImpatient(s32, s32);
s32 mNpc_GetOverImpatient(s32, s32);
s32 mNpc_CheckQuestRequest(s32);
void mNpc_SetQuestRequestOFF(s32, s32);
void mNpc_UnlockTimerCountDown(NpcTalkInfo*);
void mNpc_TalkInfoMove(void);
void mNpc_TalkEndMove(s32, s32);
s32 mNpc_GetNpcFloorNo(void);
void mNpc_SetTalkBee(void);
u8 mNpc_GetFishCompleteTalk(NpcList*);
u8 mNpc_GetInsectCompleteTalk(NpcList*);
void mNpc_SetFishCompleteTalk(NpcList*);
void mNpc_SetInsectCompleteTalk(NpcList*);
void mNpc_SetNpcHomeYpos(void);
void mNpc_PrintRemoveInfo(gfxprint*);
void mNpc_SetTalkAnimalIdx_fdebug(AnmPersonalID_c*);
void mNpc_PrintFriendship_fdebug(gfxprint*);


#endif
