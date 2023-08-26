#ifndef M_NPC_H
#define M_NPC_H

#include "ultra64.h"
#include "unk.h"
#include "m_npc_personal_id.h"
#include "m_mail.h"
#include "m_personal_id.h"
#include "lb_rtc.h"
#include "m_quest.h"

struct Actor;
struct gfxprint;
struct NpcInfo;
struct Struct_B_80142D08_jp;
struct Private;
struct Game;
struct Struct_B_80142ED8_jp;
struct Struct_D_E03000;
struct FieldInfo_Unk_Struct;
struct Struct_B_80142F70_jp;
struct Npc;
struct FieldMake_Unk_Struct;

#define mNpc_GET_IDX(npcId) ((npcId) & 0x0FFF)
#define mNpc_GET_TYPE(npcId) ((npcId) & 0xF000)
#define mNpc_IS_SPECIAL(npcId) (mNpc_GET_TYPE(npcId) == 0xD000)

#define ANIMAL_NUM_MAX 15 /* Maximum number of villagers possible in town */
#define ANIMAL_MEMORY_NUM 7
#define ANIMAL_CATCHPHRASE_LEN 4
#define ANIMAL_HP_MAIL_NUM 4
#define ANIMAL_NAME_LEN PLAYER_NAME_LEN

typedef struct AnmRemail {
    /* 0x00 */ LBRTC_Ymd date; /* date sent */
    /* 0x04 */ u8 name[ANIMAL_NAME_LEN]; /* villager name */
    /* 0x0A */ u8 landName[LAND_NAME_SIZE]; /* town name */
    /* 0x10 */ struct {
                    /* Bit 7    */ u8 passwordLetter:1; /* is mail normal or password */
                    /* Bit 6..0 */ u8 looks:7; /* personality */
               } flags;
} AnmRemail; // size = 0x12

typedef struct AnmPLMail {
  /* 0x00 */ u8 font; /* 'font' to use for letter info */
  /* 0x01 */ u8 paperType; 
  /* 0x02 */ u16 present;
  /* 0x04 */ u8 headerBackStart; /* position for name insertion in header */
  /* 0x05 */ u8 header[MAIL_HEADER_LEN];
  /* 0x0F */ u8 body[MAIL_BODY_LEN];
  /* 0x6F */ u8 footer[MAIL_FOOTER_LEN];
  /* 0x7F */ u8 pad0; /* likely pad */
  /* 0x80 */ LBRTC_Ymd date; /* sent date */
} AnmPLMail; // size = 0x84

typedef struct AnmHome {
  /* 0x00 */ u8 typeUnused; /* Likely the house type, but seems to be unused outside of SChk_Anmhome_c_sub */
  /* 0x01 */ u8 blockX; /* acre x position */
  /* 0x02 */ u8 blockZ; /* acre y position */
  /* 0x03 */ u8 utX; /* unit x position */
  /* 0x04 */ u8 utZ; /* unit z position */
} AnmHome; // size = 0x5

typedef struct AnmLet {
    /* 0x00 Bit 15..8 */ s16 friendship:8;   /* friendship with the player */
    /* 0x01 Bit 7     */ u16 exists:1;   /* letter received by villager and exists */
    /* 0x01 Bit 6     */ u16 passwordLetter:1;   /* set when the letter contains a 'key' symbol and is considered a password letter */
    /* 0x01 Bit 5     */ u16 sendReply:1;   /* set when the villager should reply */
    /* 0x01 Bit 4     */ u16 hasPresentCloth:1;   /* set when the villager's held present shirt is from this letter */
    /* 0x01 Bit 3     */ u16 wearingPresentCloth:1;   /* set when a villager is wearing the shirt sent with the saved letter */
    /* 0x01 Bit 2     */ u16 bit2_0:3; /* seemingly unused */
} AnmLet; // size = 0x2

typedef struct AnmLand {
    /* 0x00 */ u8 name[LAND_NAME_SIZE];
    /* 0x06 */ u16 id;
} AnmLand; // size = 0x8

typedef union AnmMemory_18 {
    AnmLand land;
    u32 check;
} AnmMemory_18; // size = 0x8

typedef struct AnmMemory {
    /* 0x00 */ PersonalId memoryPlayerId; /* personal id of the player memory belongs to */
    /* 0x10 */ LBRTCTime lastSpeakTime; /* time the player last spoke to this villager */
    /* 0x18 */ AnmMemory_18 unk_18; /* union between town NPC land memory & islander player action memory */
    /* 0x20 */ u64 savedTownTune; /* memory origin town tune */
    /* 0x28 */ AnmLet info; /* saved letter flags */
    /* 0x2A */ AnmPLMail letter; /* saved letter */
} AnmMemory; // size = 0xB0

typedef struct Animal {
    /* 0x000 */ AnmPersonalId id; /* this villager's ID */
    /* 0x00C */ char unk00C[0x4];
    /* 0x010 */ AnmMemory memories[ANIMAL_MEMORY_NUM]; /* memories of players who've spoken to this villager */
    /* 0x4E0 */ AnmHome homeInfo; /* home position info */
    /* 0x4E5 */ u8 catchphrase[ANIMAL_CATCHPHRASE_LEN]; /* may be called 'word_ending' */
    /* 0x4E9 */ char unk4E9[0x3];
    /* 0x4EC */ QuestContest contestQuest; /* current contest quest information */
    /* 0x510 */ u8 previousLandName[LAND_NAME_SIZE]; /* name of the last town the villager lived in or saved island ftr */
    /* 0x516 */ u8 parentName[PLAYER_NAME_LEN]; /* name of the player who 'spawned' the villager in, unsure why this is tracked */
    /* 0x51C */ s16 unk_51C;
    /* 0x51E */ char unk51E[0x2];
    /* 0x520 */ s16 unk_520;
    /* 0x522 */ u16 unk_522;
    /* 0x524 */ u8 unk_524;
    /* 0x525 */ u8 unk_525;
    /* 0x526 */ u8 unk_526;
} Animal; // size = 0x528

typedef struct NpcDemoNpc {
    /* 0x00 */ u16 npcName; /* villager id, E0XX */
    /* 0x04 */ u32 blockX; /* spawn acre */
    /* 0x08 */ u32 blockZ;
    /* 0x0C */ u32 utX; /* spawn unit in acre */
    /* 0x10 */ u32 utZ;
} NpcDemoNpc; // size = 0x14

typedef struct NpcHouseData {
    /* 0x00 */ u8 type;
    /* 0x01 */ u8 palette;
    /* 0x02 */ u8 wallId;
    /* 0x03 */ u8 floorId;
    /* 0x04 */ u16 mainLayerId;
    /* 0x06 */ u16 secondaryLayerId;
} NpcHouseData; // size = 0x8

typedef struct NpcList_Flags {
    /* 0x00 Bit 31..24 */ u32 unk_31:8;
    /* 0x01 Bit 23     */ u32 unk_23:1;
    /* 0x01 Bit 22     */ u32 unk_22:1;
    /* 0x01 Bit 21     */ u32 unk_21:1;
    /* 0x01 Bit 20..16 */ u32 unk20:4;
    /* 0x02 Bit 15..8  */ u32 unk16:8;
    /* 0x03 Bit 7..0   */ u32 unk8:8;
} NpcList_Flags; // size = 0x4

typedef struct NpcList {
    /* 0x00 */ u16 name;
    /* 0x02 */ u16 fieldName;
    /* 0x04 */ Vec3f homePosition;
    /* 0x10 */ Vec3f position;
    /* 0x1C */ NpcList_Flags flags;
    /* 0x20 */ QuestBase questInfo;
    /* 0x2C */ NpcHouseData houseData;
    /* 0x34 */ u16 rewardFurniture;
} NpcList; // size = 0x38

void func_800A6810_jp(s32* arg0, s32 arg1, s32 arg2);
void func_800A6920_jp(u8* catchphrase, s32 len);
void func_800A6940_jp(u8* npcMax);
void func_800A695C_jp(u8* arg0);
void mNpc_ClearAnimalPersonalID(AnmPersonalId* anmId);
s32 mNpc_CheckFreeAnimalPersonalID(AnmPersonalId* anmId);
void mNpc_CopyAnimalPersonalID(AnmPersonalId* dst, AnmPersonalId* src);
s32 mNpc_CheckCmpAnimalPersonalID(AnmPersonalId* id0, AnmPersonalId* id1);
s32 func_800A6AF0_jp(void);
s32 func_800A6B58_jp(Animal* animal);
s32 func_800A6B6C_jp(Animal* animal);
void func_800A6B7C_jp(Animal* animal);
void func_800A6B9C_jp(Animal* animal, u16 arg1);
void func_800A6BC8_jp(Animal* animal, PersonalId* pid);
void func_800A6C1C_jp(void);
void func_800A6C84_jp(AnmPLMail* letter);
void func_800A6CE4_jp(AnmPLMail* dst, AnmPLMail* src);
void func_800A6D04_jp(AnmMemory* memory, s32 count);
void func_800A6DB0_jp(AnmMemory* dst, AnmMemory* src);
void func_800A6DD0_jp(AnmMemory* memory, s32 arg1);
s32 func_800A6E0C_jp(PersonalId* pid);
void mNpc_RenewalAnimalMemory(void);
s32 func_800A6F48_jp(AnmMemory* memory, s32 count);
s32 func_800A6FF4_jp(AnmMemory* memory, s32 count);
s32 func_800A706C_jp(AnmMemory* memory, s32 count);
void func_800A71AC_jp(struct Private* private, AnmMemory* memory);
void func_800A71F8_jp(struct Private* private, AnmMemory* memory);
s32 func_800A7238_jp(PersonalId* pid, AnmMemory* memory, s32 count);
void func_800A72C0_jp(Animal* animal);
void func_800A73D8_jp(AnmPersonalId* anmId);
s32 func_800A74A0_jp(AnmMemory* memory, s32 count);
s32 func_800A7530_jp(AnmMemory** outMemory, AnmMemory* memory, s8* arg2);
s32 func_800A75FC_jp(AnmMemory* memory, s32 count);
s32 func_800A76E4_jp(AnmMemory* memory, s32 count, s32 arg2);
s32 func_800A77F0_jp(AnmMemory* memory, s32 count);
s32 func_800A7858_jp(AnmMemory* memory, s32 count);
s32 func_800A78DC_jp(AnmMemory* memory, s32 count);
void mNpc_ClearAnimalInfo(Animal* animal);
void mNpc_ClearAnyAnimalInfo(Animal* animals, s32 count);
s32 mNpc_CheckFreeAnimalInfo(Animal* animal);
s32 mNpc_GetFreeAnimalInfo(Animal* animal, s32 count);
s32 mNpc_UseFreeAnimalInfo(Animal* animal, s32 count);
void mNpc_CopyAnimalInfo(Animal* dst, Animal* src);
s32 mNpc_SearchAnimalinfo(Animal* animal, u16 npcName, s32 count);
Animal* func_800A7C94_jp(u16 npcName);
s32 func_800A7D08_jp(AnmPersonalId* anmId);
AnmPersonalId* func_800A7DA0_jp(AnmPersonalId* ids, s32 numIds, s32 arg0, s32 arg1, s32 arg2);
AnmPersonalId* mNpc_GetOtherAnimalPersonalID(AnmPersonalId* ids, s32 numIds);
void func_800A80D8_jp(Animal* animal, s32 count);
s32 func_800A8148_jp(u8 looks);
s32 func_800A820C_jp(s32 arg0, s32 arg1, s32 arg2);
void func_800A82C8_jp(AnmPLMail* letter, Mail* mail);
void func_800A8344_jp(Mail* mail, AnmPLMail* letter, PersonalId* pid, AnmPersonalId* anmId);
s32 func_800A83F0_jp(u8 c);
s32 func_800A845C_jp(s32* arg0, u8* body);
u8 func_800A8614_jp(s32* arg0, u8* body);
u8 func_800A86C4_jp(u8* body);
u8 func_800A86E8_jp(AnmMemory* memory, u8* body);
s32 func_800A8764_jp(Animal* animal, u8* body);
s32 func_800A8814_jp(Animal* animal, AnmMemory* memory, u8* body);
s32 func_800A8868_jp(Mail* mail);
void func_800A8AB4_jp(AnmRemail* remail);
void func_800A8B10_jp(u16* present);
s32 func_800A8B84_jp(Mail* mail, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_800A8C48_jp(struct Private* private, AnmPersonalId* anmId, AnmRemail* remail);
void func_800A8DB4_jp(Mail* mail, struct Private* private, AnmPersonalId* anmId, AnmRemail* remail, u8 arg4);
void func_800A8F30_jp(Mail* mail, struct Private* private, AnmPersonalId* anmId, AnmRemail* remail, u8 arg4);
void func_800A9028_jp(Mail* mail, struct Private* private, AnmPersonalId* anmId, AnmRemail* remail, u32 arg4, u8 arg5);
s32 func_800A9110_jp(struct Private* private, AnmPersonalId* anmId, AnmRemail* remail, u32 arg3, u8 arg4);
s32 func_800A918C_jp(LBRTC_Ymd* ymd, LBRTCTime* time);
void func_800A91DC_jp(void);
u8 func_800A9364_jp(void);
void func_800A93AC_jp(Mail* mail, PersonalId* pid, AnmPersonalId* anmId, u16 arg3, u8 arg4, s32 arg5);
void func_800A9468_jp(u16* arg0, s32 arg1);
void func_800A94C8_jp(Mail* mail, AnmMemory* memory, Animal* animal, s32 arg3, s32 arg4);
s32 func_800A956C_jp(AnmMemory* memory, s32 arg1, Animal* animal, s32 arg2);
void func_800A96B0_jp(s32* outIdx, u8* arg1, Animal* animal, s32 arg3);
s32 func_800A9780_jp(s32 arg0);
void func_800A992C_jp(u16* arg0);
void func_800A99B8_jp(Mail* mail, PersonalId* pid, AnmPersonalId* anmId);
s32 func_800A9A98_jp(PersonalId* pid, s32 playerNo, AnmPersonalId* anmId);
s32 func_800A9BC4_jp(s32 arg0);
s32 func_800A9BD4_jp(PersonalId* pid, s32 playerNo);
void func_800A9CD4_jp(Mail* mail, PersonalId* pid);
s32 func_800A9D68_jp(PersonalId* pid, s32 arg1);
void func_800A9E54_jp(Animal* animal, u8* arg1);
u8* func_800A9E7C_jp(struct Actor* actor);
void func_800A9EC8_jp(struct Actor* actor);
s32 func_800A9F9C_jp(void);
s32 func_800AA028_jp(u16 arg0, u16 arg1, u16 arg2, u16 arg3);
void func_800AA0B8_jp(u16 fgname);
void func_800AA124_jp(void);
struct CommonData_unk_10170* func_800AA14C_jp(u16 fgName);
s32 mNpc_GetLooks(u16 npcName);
void func_800AA218_jp(Animal* animal, u16 arg1, u8 arg2, struct Struct_D_E03000* arg3);
void func_800AA29C_jp(Animal* animal, u16 arg1, struct Struct_D_E03000* arg2);
void func_800AA2F8_jp(u16 arg0);
s32 func_800AA35C_jp(s32 arg0);
s32 func_800AA3A4_jp(u8 arg0);
void func_800AA438_jp(u8* arg0, Animal* animal);
void func_800AA49C_jp(void);
s32 func_800AA4FC_jp(s32 arg0, u8* arg1, s32 arg2);
void func_800AA51C_jp(Animal* animal, u8 arg1, s32 count);
void mNpc_SetAnimalTitleDemo(NpcDemoNpc* demoNpc, Animal* animal, struct Game* game);
s32 func_800AA8C4_jp(s32* arg0, s32* arg1, u16* arg2);
s32 func_800AA9F4_jp(s32* arg0, s32* arg1, UNK_TYPE arg2, UNK_TYPE arg3);
void func_800AAA40_jp(struct Struct_B_80142D08_jp* arg0, s32 count, u8* arg2);
void func_800AAB48_jp(struct Struct_B_80142D08_jp* arg0, s32 arg1, u8* arg2, u8 arg3, u8 arg4);
void func_800AAC88_jp(u16 npcId, s32 blockX, s32 blockZ, s32 utX, s32 utZ);
void func_800AADE8_jp(AnmHome* homeInfo);
void func_800AAEFC_jp(Animal* animal, struct Struct_B_80142D08_jp* arg1, u8 arg2);
void func_800AB054_jp(void);
void func_800AB09C_jp(void);
void mNpc_SetNpcList(NpcList* npcList, Animal* animal, s32 count, s32 mallocFlag);
void mNpc_SetNpcinfo(struct Actor* actor, s8 npcInfoIdx);
void func_800AB498_jp(struct FieldInfo_Unk_Struct* arg0, u8 arg1, u8 arg2);
void func_800AB62C_jp(s16* arg0);
void func_800AB6C8_jp(struct Actor* actor);
s32 func_800AB734_jp(struct Private* private);
s32 func_800AB7D0_jp(struct Private* private);
s32 func_800AB80C_jp(u16 arg0);
u16 func_800AB8A0_jp(struct FieldMake_Unk_Struct* arg0, NpcList* npcList, s32 count);
void func_800ABA14_jp(struct FieldMake_Unk_Struct* arg0, s32 count);
u16 func_800ABAA8_jp(AnmPersonalId* anmId);
void func_800ABAF0_jp(void);
Animal* mNpc_GetInAnimalP(void);
s32 func_800ABB24_jp(Animal* animal, s32 arg1);
u8 func_800ABCF8_jp(Animal* animal, s32 arg1);
void mNpc_SetRemoveAnimalNo(Animal* animal);
s32 func_800ABE30_jp(Animal* animal1, Animal* animal2);
s32 func_800ABF40_jp(void);
void func_800AC1A0_jp(struct Struct_B_80142F70_jp* arg0);
void func_800AC1C8_jp(void);
void func_800AC1EC_jp(struct Struct_B_80142F70_jp* arg0, Animal* animal);
s32 func_800AC284_jp(Mail* mail, PersonalId* pid, AnmPersonalId* anmId);
s32 func_800AC358_jp(Mail* mail, struct Private* priv, s32 playerNo, AnmPersonalId* anmId);
void func_800AC488_jp(struct Struct_B_80142F70_jp* arg0);
void mNpc_SendRegisteredGoodbyMail(void);
void func_800AC57C_jp(Animal* inAnimal, s32 arg1);
s32 func_800AC804_jp(s32 blockX, s32 blockZ, u8 utX, u8 utZ);
void mNpc_SetReturnAnimal(Animal* animal);
void func_800ACB24_jp(struct FieldInfo_Unk_Struct* arg0, u8 arg1, u8 arg2);
void func_800ACB54_jp(Animal* animal, s32 count);
void func_800ACC38_jp(u8* name, u8 npcId);
void func_800ACCAC_jp(u8* name, u16 npcId);
void mNpc_GetNpcWorldNameAnm(u8* name, AnmPersonalId* anmId);
void func_800ACD74_jp(u8* arg0, u16 name);
void func_800ACDF8_jp(u8* arg0, struct Npc* npc);
void func_800ACE90_jp(u8* arg0);
void func_800ACF84_jp(u8* arg0, Vec3f arg1);
s32 func_800AD084_jp(struct Actor* actor);
s32 func_800AD0B8_jp(u16 name);
s32 func_800AD104_jp(s32 arg0);
s32 func_800AD154_jp(AnmPersonalId* anmId);
s32 func_800AD188_jp(struct Actor* actor);
s32 func_800AD1E0_jp(u16 name);
s32 func_800AD22C_jp(struct Actor* actor);
void func_800AD2B8_jp(UNK_TYPE arg0);
void mNpc_InitNpcAllInfo(s32 mallocFlag);
s32 func_800AD338_jp(void);
s32 func_800AD3BC_jp(void);
u8 func_800AD4B8_jp(u8* arg0, s32* arg1);
s32 func_800AD614_jp(void);
s32 func_800AD6D4_jp(u8 arg0);
void func_800AD8C4_jp(Animal* animal, s32 arg1);
s32 func_800AD954_jp(u8 arg0);
void func_800AD9FC_jp(void);
s32 func_800ADBE4_jp(u16 arg0, s32 arg1);
s32 func_800ADC28_jp(u16 arg0, u32 arg1);
s32 func_800ADC8C_jp(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_800ADD20_jp(s32* arg0, s32* arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_800ADEFC_jp(s32* arg0, s32* arg1, s32 arg2, s32 arg3, s32 arg4);
void func_800AE110_jp(s32* arg0, s32* arg1, s32 arg2, s32 arg3);
void mNpc_ClearTalkInfo(void);
void func_800AE1A0_jp(struct Struct_B_80142ED8_jp* arg0);
void func_800AE1B8_jp(u16* arg0, u16* arg1, s32 arg2);
s32 func_800AE1D8_jp(s32 arg0, s32 arg1);
s32 func_800AE23C_jp(s32 arg0, s32 arg1);
s32 func_800AE284_jp(s32 arg0, s32 arg1);
s32 func_800AE2E8_jp(s32 arg0);
void func_800AE320_jp(s32 arg0, s32 arg1);
void func_800AE37C_jp(struct Struct_B_80142ED8_jp* arg0);
void func_800AE3B4_jp(void);
void func_800AE4B4_jp(s32 arg0, s32 arg1);
s32 func_800AE558_jp(void);
void func_800AE5C8_jp(void);
u8 func_800AE64C_jp(NpcList* npcList);
u8 func_800AE670_jp(NpcList* npcList);
void func_800AE694_jp(NpcList* npcList);
void func_800AE6B0_jp(NpcList* npcList);
void func_800AE6CC_jp(void);
void func_800AE76C_jp(struct gfxprint* print);
void func_800AE898_jp(AnmPersonalId* anmId);
void mNpc_PrintFriendship_fdebug(struct gfxprint* gfxprint);

extern u16 D_8010AF00_jp[];
extern u16 D_8010AF30_jp[];
extern u32* D_8010B334_jp[];
extern s16 D_8010B374_jp[];
extern u32 D_8010B478_jp[];
extern u32 D_8010B484_jp[];
extern u32 D_8010B490_jp[];
extern u32 D_8010B4A0_jp[];
extern u16 D_8010B4B0_jp[];
extern u16 D_8010B4FC_jp[];
extern u8 D_8010B500_jp[];
extern u16 D_8010B504_jp[];

#endif
