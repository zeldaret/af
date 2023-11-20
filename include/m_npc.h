#ifndef M_NPC_H
#define M_NPC_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"
#include "m_land.h"
#include "6DB420.h"
#include "m_mail.h"
#include "lb_rtc.h"


#define ANIMAL_NUM_MAX 15 /* Maximum number of villagers possible in town */
#define ANIMAL_MEMORY_NUM 7
#define ANIMAL_CATCHPHRASE_LEN 4
#define ANIMAL_NAME_LEN PLAYER_NAME_LEN

#define NPC_NUM 216


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
    /* 0x20 */ char unk20[0xC];
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

typedef struct AnmPersonalId_c {
    /* 0x00 */ u16 npcId; /* id */
    /* 0x02 */ u16 landId; /* town id */
    /* 0x04 */ u8 landName[LAND_NAME_SIZE]; /* town name */
    /* 0x0A */ u8 nameId; /* lower byte of the id */
    /* 0x0B */ u8 looks; /* internal name for personality */
} AnmPersonalID_c; // size = 0xC

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
    /* 0x4E9 */ char parentName[ANIMAL_NAME_LEN]; 
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

typedef enum NpcSex{
    NPC_SEX_MALE,
    NPC_SEX_FEMALE,
    NPC_SEX_OTHER
}NpcSex;

typedef enum NpcLooks{
    /* 0 */ NPC_LOOKS_GIRL,
    /* 1 */ NPC_LOOKS_KO_GIRL,
    /* 2 */ NPC_LOOKS_BOY,
    /* 3 */ NPC_LOOKS_SPORT_MAN,
    /* 4 */ NPC_LOOKS_GRIM_MAN,
    /* 5 */ NPC_LOOKS_NANIWA_LADY,

    /* 6 */ NPC_LOOKS_NUM
}NpcLooks;

typedef enum NpcFeels{
    /* 0 */ NPC_FEEL_NORMAL,
    /* 1 */ NPC_FEEL_HAPPY,
    /* 2 */ NPC_FEEL_ANGRY,
    /* 3 */ NPC_FEEL_SAD,
    /* 4 */ NPC_FEEL_SLEEPY,
    /* 5 */ NPC_FEEL_PITFALL,
    /* 6 */ NPC_FEEL_NUM
}NpcFeels;

typedef enum NpcPatience {
    /* 0 */ NPC_PATIENCE_MILDLY_ANNOYED,
    /* 1 */ NPC_PATIENCE_ANNOYED,
    /* 2 */ NPC_PATIENCE_NORMAL,
    /* 3 */ NPC_PATIENCE_NUM
}NpcPatience;

// void func_800A6920_jp();
// void func_800A6940_jp();
// void func_800A695C_jp();
void mNpc_ClearAnimalPersonalID(AnmPersonalID_c*);
s32 mNpc_CheckFreeAnimalPersonalID(AnmPersonalID_c*);
void mNpc_CopyAnimalPersonalID(AnmPersonalID_c*, AnmPersonalID_c*);
s32 mNpc_CheckCmpAnimalPersonalID(AnmPersonalID_c*, AnmPersonalID_c*);
// void func_800A6AF0_jp();
// void func_800A6B58_jp();
// void func_800A6B6C_jp();
// void func_800A6B7C_jp();
// void func_800A6B9C_jp();
// void func_800A6BC8_jp();
// void func_800A6C1C_jp();
// void func_800A6C84_jp();
// void func_800A6CE4_jp();
// void func_800A6D04_jp();
// void func_800A6DB0_jp();
// void func_800A6DD0_jp();
// void func_800A6E0C_jp();
void mNpc_RenewalAnimalMemory(void);
// void func_800A6F48_jp();
// void func_800A6FF4_jp();
// void func_800A706C_jp();
// void func_800A71AC_jp();
// void func_800A71F8_jp();
// void func_800A7238_jp();
// void func_800A72C0_jp();
// void func_800A73D8_jp();
// void func_800A74A0_jp();
// void func_800A7530_jp();
// void func_800A75FC_jp();
// void func_800A76E4_jp();
// void func_800A77F0_jp();
// void func_800A7858_jp();
// void func_800A78DC_jp();
// void mNpc_ClearAnimalInfo();
// void mNpc_ClearAnyAnimalInfo();
s32 mNpc_CheckFreeAnimalInfo(Animal_c*);
// void mNpc_GetFreeAnimalInfo();
// void mNpc_UseFreeAnimalInfo();
// void mNpc_CopyAnimalInfo();
// void mNpc_SearchAnimalinfo();
// void func_800A7C94_jp();
// void func_800A7D08_jp();
// void func_800A7DA0_jp();
// void mNpc_GetOtherAnimalPersonalID();
// void func_800A80D8_jp();
// void func_800A8148_jp();
// void func_800A820C_jp();
// void func_800A82C8_jp();
// void func_800A8344_jp();
// void func_800A83F0_jp();
// void func_800A845C_jp();
// void func_800A8614_jp();
// void func_800A86C4_jp();
// void func_800A86E8_jp();
// void func_800A8764_jp();
// void func_800A8814_jp();
// void func_800A8868_jp();
// void func_800A8AB4_jp();
// void func_800A8B10_jp();
// void func_800A8B84_jp();
// void func_800A8C48_jp();
// void func_800A8DB4_jp();
// void func_800A8F30_jp();
// void func_800A9028_jp();
// void func_800A9110_jp();
// void func_800A918C_jp();
void func_800A91DC_jp(void);
// void func_800A9364_jp();
// void func_800A93AC_jp();
// void func_800A9468_jp();
// void func_800A94C8_jp();
// void func_800A956C_jp();
// void func_800A96B0_jp();
// void func_800A9780_jp();
// void func_800A992C_jp();
// void func_800A99B8_jp();
// void func_800A9A98_jp();
// void func_800A9BC4_jp();
// void func_800A9BD4_jp();
// void func_800A9CD4_jp();
// void func_800A9D68_jp();
// void func_800A9E54_jp();
// void func_800A9E7C_jp();
// void func_800A9EC8_jp();
// void func_800A9F9C_jp();
// void func_800AA028_jp();
// void func_800AA0B8_jp();
void func_800AA124_jp(void);
// void func_800AA14C_jp();
s32 mNpc_GetLooks(u16 arg0);
// void func_800AA218_jp();
// void func_800AA29C_jp();
// void func_800AA2F8_jp();
// void func_800AA35C_jp();
// void func_800AA3A4_jp();
// void func_800AA438_jp();
// void func_800AA49C_jp();
// void func_800AA4FC_jp();
// void func_800AA51C_jp();
// void mNpc_SetAnimalTitleDemo();
// void func_800AA8C4_jp();
// void func_800AA9F4_jp();
// void func_800AAA40_jp();
// void func_800AAB48_jp();
// void func_800AAC88_jp();
// void func_800AADE8_jp();
// void func_800AAEFC_jp();
void func_800AB054_jp(void);
void func_800AB09C_jp(void);
void mNpc_SetNpcList(NpcList* npclist, Animal_c* animals, s32 count, s32 malloc_flag);
void mNpc_SetNpcinfo(struct Actor* actor, s8 arg1);
// void func_800AB498_jp();
// void func_800AB62C_jp();
// void func_800AB6C8_jp();
// void func_800AB734_jp();
// void func_800AB7D0_jp();
// void func_800AB80C_jp();
// void func_800AB8A0_jp();
// void func_800ABA14_jp();
// void func_800ABAA8_jp();
// void func_800ABAF0_jp();
s32 mNpc_GetInAnimalP(void);
// void func_800ABB24_jp();
// void func_800ABCF8_jp();
void mNpc_SetRemoveAnimalNo(Animal_c* animal);
// void func_800ABE30_jp();
// void func_800ABF40_jp();
// void func_800AC1A0_jp();
// void func_800AC1C8_jp();
// void func_800AC1EC_jp();
// void func_800AC284_jp();
// void func_800AC358_jp();
// void func_800AC488_jp();
void mNpc_SendRegisteredGoodbyMail(void);
// void func_800AC57C_jp();
// void func_800AC804_jp();
void mNpc_SetReturnAnimal(s32 arg0);
// void func_800ACB24_jp();
// void func_800ACB54_jp();
// void func_800ACC38_jp();
// void func_800ACCAC_jp();
void mNpc_GetNpcWorldNameAnm(PlayerName* arg0, struct mMl_get_npcinfo_from_mail_name_arg0* arg1);
// void func_800ACD74_jp();
// void func_800ACDF8_jp();
// void func_800ACE90_jp();
void mNpc_GetAnimalPlateName(char* arg0, xyz_t arg1);
// void func_800AD084_jp();
// void func_800AD0B8_jp();
// void func_800AD104_jp();
// void func_800AD154_jp();
// void func_800AD188_jp();
// void func_800AD1E0_jp();
// void func_800AD22C_jp();
// void func_800AD2B8_jp();
void mNpc_InitNpcAllInfo(s32 arg0);
// void func_800AD338_jp();
// void func_800AD3BC_jp();
// void func_800AD4B8_jp();
// void func_800AD614_jp();
// void func_800AD6D4_jp();
// void func_800AD8C4_jp();
// void func_800AD954_jp();
void func_800AD9FC_jp(void);
// void func_800ADBE4_jp();
// void func_800ADC28_jp();
// void func_800ADC8C_jp();
// void func_800ADD20_jp();
// void func_800ADEFC_jp();
// void func_800AE110_jp();
void mNpc_ClearTalkInfo(void);
// void func_800AE1A0_jp();
// void func_800AE1B8_jp();
// void func_800AE1D8_jp();
// void func_800AE23C_jp();
// void func_800AE284_jp();
// void func_800AE2E8_jp();
// void func_800AE320_jp();
// void func_800AE37C_jp();
// void func_800AE3B4_jp();
// void func_800AE4B4_jp();
// void func_800AE558_jp();
// void func_800AE5C8_jp();
// void func_800AE64C_jp();
// void func_800AE670_jp();
// void func_800AE694_jp();
// void func_800AE6B0_jp();
// void func_800AE6CC_jp();
// void func_800AE76C_jp();
// void func_800AE898_jp();
// void mNpc_PrintFriendship_fdebug();

#endif
