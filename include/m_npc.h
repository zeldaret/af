#ifndef M_NPC_H
#define M_NPC_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"
#include "m_land.h"
#include "6DB420.h"
#include "m_mail.h"

#define ANIMAL_NUM_MAX 15 /* Maximum number of villagers possible in town */

typedef struct NpcList {
    /* 0x00 */ char unk00[0x10];
    /* 0x10 */ Vec3f position;
    /* 0x14 */ char unk14[0x1C];
} NpcList; // size = 0x38

typedef struct AnmHome_c {
    /* 0x00 */ u8 typeUnused; /* Likely the house type, but seems to be unused outside of SChk_Anmhome_c_sub */
    /* 0x01 */ u8 blockX; /* acre x position */
    /* 0x02 */ u8 blockZ; /* acre y position */
    /* 0x03 */ u8 utX; /* unit x position */
    /* 0x04 */ u8 utZ; /* unit z position */
} AnmHome_c; // size = 0x5

typedef struct AnmPersonalId_c {
    /* 0x00 */ u16 npcId; /* id */
    /* 0x02 */ u16 landId; /* town id */
    /* 0x04 */ u8 landName[LAND_NAME_SIZE]; /* town name */
    /* 0x0A */ u8 nameId; /* lower byte of the id */
    /* 0x0B */ u8 looks; /* internal name for personality */
} AnmPersonalID_c; // size = 0xC

typedef struct Animal_c {
    /* 0x000 */ AnmPersonalID_c id; 
    /* 0x00C */ char unk00C[0x4D4];
    /* 0x4E0 */ AnmHome_c homeInfo;
    /* 0x4E5 */ char unk4E5[0x43]; 
} Animal_c;

typedef enum NpcLooks{
    /* 0 */ NPC_LOOKS_GIRL,
    /* 1 */ NPC_LOOKS_KO_GIRL,
    /* 2 */ NPC_LOOKS_BOY,
    /* 3 */ NPC_LOOKS_SPORT_MAN,
    /* 4 */ NPC_LOOKS_GRIM_MAN,
    /* 5 */ NPC_LOOKS_NANIWA_LADY,

    /* 6 */ NPC_LOOKS_NUM
}NpcLooks;

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
// void mNpc_CheckFreeAnimalInfo();
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
// void func_800ACF84_jp();
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
