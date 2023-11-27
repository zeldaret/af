#ifndef M_LAND_H_H
#define M_LAND_H_H

#include "ultra64.h"

// Town name character count
#define LAND_NAME_SIZE 6
#define LAND_NAME_MURA_SIZE (LAND_NAME_SIZE + 2)

typedef struct LandInfo {
    /* 0x0 */char name[LAND_NAME_SIZE];
    /* 0x6 */s8 exists;
    /* 0x8 */u16 id;
} LandInfo; // size = 0xA

// void func_80094DD0_jp();
// void func_80094E10_jp();
s32 mLd_CheckCmpLandName(char* name1, char* name2);
s32 mLd_CheckCmpLand(char* name1, u16 id1, char* name2, u16 id2);
void mLd_ClearLandName(char* name);
void mLd_CopyLandName(char* arg0, char* arg1);
// void func_80094F24_jp();
// void func_80094F84_jp();
// void func_8009504C_jp();
char* mLd_GetLandName(void);
// void func_800950E8_jp();
// void func_8009519C_jp();
s32 mLd_PlayerManKindCheck(void);
s32 mLd_CheckThisLand(char* arg0, u16 arg1);
// void func_80095218_jp();
void mLd_LandDataInit(void);


#endif
