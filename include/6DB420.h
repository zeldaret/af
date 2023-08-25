#ifndef C_6DB420_H
#define C_6DB420_H

#include "ultra64.h"
#include "6B8A70.h"
#include "unk.h"

struct Private_c;
struct mPr_map_info_c;
struct mLd_land_info_c;
struct mPr_mother_mail_info_c;

typedef struct PlayerName {
    /* 0x0 */ UNK_TYPE1 unk_0[0x6];
} PlayerName; // size = 0x6

typedef struct PersonalID {
    /* 0x0 */ PlayerName unk_0;
    /* 0x6 */ LandName unk_6;
    /* 0xC */ u16 unk_C;
    /* 0xE */ u16 unk_E;
} PersonalID; // size = 0x10

// void func_800B7780_jp();
void mPr_CopyPlayerName(PlayerName* dst, PlayerName* src);
// void func_800B77C4_jp();
// void func_800B7804_jp();
// void func_800B785C_jp();
// void func_800B7914_jp();
void mPr_ClearPersonalID(PersonalID* arg0);
// void func_800B7998_jp();
void mPr_CopyPersonalID(PersonalID* arg0, PersonalID* arg1);
s32 mPr_CheckCmpPersonalID(PersonalID* arg0, PersonalID* arg1);
// void func_800B7A94_jp();
// void func_800B7AB0_jp();
void mPr_ClearPrivateInfo(struct Private_c* private);
// void func_800B7B8C_jp();
// void func_800B7BC0_jp();
// void func_800B7CD0_jp();
// void func_800B7D50_jp();
void mPr_InitPrivateInfo(struct Private_c* private);
// void func_800B7F00_jp();
// void func_800B7F48_jp();
s32 mPr_CheckPrivate(struct Private_c* private);
// void func_800B7FA0_jp();
// void func_800B7FD4_jp();
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
void mPr_SetPossessionItem(struct Private_c* priv, int idx, u16 item, u32 cond);
// void func_800B8B8C_jp();
// void func_800B8BE4_jp();
// void func_800B8C10_jp();
// void func_800B8C20_jp();
// void func_800B8C34_jp();
// void func_800B8C9C_jp();
// void func_800B8D18_jp();
// void func_800B8D3C_jp();
s32 func_800B8D64_jp(u8 player_no, s32 arg1);
void mPr_ClearMotherMailInfo(struct mPr_mother_mail_info_c* arg0);
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
void mPr_SendForeingerAnimalMail(struct Private_c* now_private);
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
void mPr_RenewalMapInfo(struct mPr_map_info_c* maps, s32 count, struct mLd_land_info_c* land_info);
// void mPr_RandomSetPlayerData_title_demo();
// void mPr_PrintMapInfo_debug();

#endif
