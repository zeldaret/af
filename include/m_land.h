#ifndef M_LAND_H_H
#define M_LAND_H_H

#include "ultra64.h"
#include "unk.h"

#define mLd_CHECK_LAND_ID(id) (((id) & 0xFF00) == 0x3000)
#define mLd_CHECK_ID(id) ((id & 0x3000) == 0x3000)

// Town name character count
#define LAND_NAME_SIZE 6
#define LAND_NAME_MURA_SIZE (LAND_NAME_SIZE + 2)

typedef struct LandInfo {
    /* 0x0 */ char name[LAND_NAME_SIZE];
    /* 0x6 */ s8 exists;
    /* 0x8 */ u16 id;
} LandInfo; // size = 0xA

s32 mLd_NullCheckLandName(char* landName);
s32 mLd_CheckId(u16 landId);
s32 mLd_CheckCmpLandName(char* nameA, char* nameB);
s32 mLd_CheckCmpLand(char* nameA, u16 idA, char* nameB, u16 idB);
void mLd_ClearLandName(char* name);
void mLd_CopyLandName(char* nameA, char* nameB);
size_t mLd_AddMuraString(char* name, size_t len);
size_t mLd_GetLandNameStringAddMura(char* buf);
void mLd_SetFreeStrLandMuraName(char* name, s32 freeStr);
char* mLd_GetLandName(void);
u16 mLd_MakeLandId(void);
s32 mLd_PlayerManKindCheckNo(u8 playerNo);
s32 mLd_PlayerManKindCheck(void);
s32 mLd_CheckThisLand(char* otherName, u16 otherId);
void mLd_LandInfoInit(void);
void mLd_LandDataInit(void);


#endif
