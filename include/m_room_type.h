#ifndef M_ROOM_TYPE_H
#define M_ROOM_TYPE_H

#include "ultra64.h"
#include "libu64/gfxprint.h"

struct Game;

#define mRmTp_FTR_UNIT_MAX 4
#define FTR_NUM 947

typedef enum mRmTp_FurnitureSize {
    /* 0 */ mRmTp_FTRSIZE_1x1,
    /* 1 */ mRmTp_FTRSIZE_1x2,
    /* 2 */ mRmTp_FTRSIZE_2x2,
    /* 3 */ mRmTp_FTRSIZE_MAX
} mRmTp_FurnitureSize;

typedef enum mRmTp_Direction {
    /* 0 */ mRmTp_DIRECT_SOUTH,
    /* 1 */ mRmTp_DIRECT_EAST,
    /* 2 */ mRmTp_DIRECT_NORTH,
    /* 3 */ mRmTp_DIRECT_WEST,
    /* 4 */ mRmTp_DIRECT_MAX
} mRmTp_Direction;

typedef enum mRmTp_SEType {
    /* 0 */ mRmTp_FTR_SE_NONE,
    /* 1 */ mRmTp_FTR_SE_SOFT_CHAIR,
    /* 2 */ mRmTp_FTR_SE_HARD_CHAIR,
    /* 3 */ mRmTp_FTR_SE_BUBU_CHAIR,
    /* 4 */ mRmTp_FTR_SE_TOILET_CHAIR,
    /* 5 */ mRmTp_FTR_SE_MAX
} mRmTp_SEType;

typedef enum mRmTp_Action {
    /* 0 */    mRmTp_CHAIR_ACTION_SIT,
    /* 1 */    mRmTp_CHAIR_ACTION_STAND,
    /* 2 */    mRmTp_CHAIR_ACTION_MAX
} mRmTp_Action;

typedef enum mRmTp_BirthType {
    /* 00 */ mRmTp_BIRTH_TYPE_GRP_A,
    /* 01 */ mRmTp_BIRTH_TYPE_GRP_B,
    /* 02 */ mRmTp_BIRTH_TYPE_GRP_C,
    /* 03 */ mRmTp_BIRTH_TYPE_EVENT,
    /* 04 */ mRmTp_BIRTH_TYPE_BIRTHDAY,
    /* 05 */ mRmTp_BIRTH_TYPE_HALLOWEEN,
    /* 06 */ mRmTp_BIRTH_TYPE_HANIWA,
    /* 07 */ mRmTp_BIRTH_TYPE_LOTTERY,
    /* 08 */ mRmTp_BIRTH_TYPE_FTR_CLOTH,
    /* 09 */ mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    /* 10 */ mRmTp_BIRTH_TYPE_FTR_INSECT,
    /* 11 */ mRmTp_BIRTH_TYPE_FTR_FISH,
    /* 12 */ mRmTp_BIRTH_TYPE_SINGLE_FOSSIL,
    /* 13 */ mRmTp_BIRTH_TYPE_MULTI_FOSSIL,
    /* 14 */ mRmTp_BIRTH_TYPE_XMAS,
    /* 15 */ mRmTp_BIRTH_TYPE_SANTA,
    /* 16 */ mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    /* 17 */ mRmTp_BIRTH_TYPE_SNOWMAN,
} mRmTp_BirthType;

typedef struct mRmTp_FtrPlaceInfo {
    /* 0x0 */ s32 exists;
    /* 0x4 */ s32 utX;
    /* 0x8 */ s32 utZ;
} mRmTp_FtrPlaceInfo; // size = 0xC

typedef struct mRmTp_FtrPlaceData {
    /* 0x0 */ u8 exist;
    /* 0x2 */ s16 ofsX;
    /* 0x4 */ s16 ofsZ;
} mRmTp_FtrPlaceData; // size = 0x8

void mRmTp_InitFtrPlaceInfo(mRmTp_FtrPlaceInfo* info);
s32 mRmTp_ItemNo2FtrSize(u16 name);
mRmTp_FtrPlaceData* mRmTp_GetFtrUnitPlaceData(s32 size, s32 dir);
s32 mRmTp_GetFurnitureData(u16 ftr, s32 ut_x, s32 ut_z, mRmTp_FtrPlaceInfo* info);
void mRmTp_AssignFtrFgIdx(u16* dst, u16* src, u16* arg2, u16* arg3);
void mRmTp_MakeFtrNoTable(u16* dst, u16* src);
void* mRmTp_MallocRam(struct Game* game, size_t size);
void mRmTp_FreeRam(struct Game* game, void* ptr);
s32 mRmTp_CharVacRight2Left(u8* str, s32 len);
s32 mRmTp_GetFtrActionSE(s32 ftr_idx, s32 mode);
s32 mRmTp_CheckShopFtr(u16 item);
u8* mRmTp_CheckFtrBirthInfoTop();
s32 mRmTp_GetFloorIdx(void);
u16 mRmTp_Item1ItemNo2FtrItemNo_AtPlayerRoom(u16 item);
u16 mRmTp_FtrItemNo2Item1ItemNo(u16 item);
void mRmTp_MakeMelodyData();
u8* mRmTp_GetMelodyData();
void mRmTp_DrawFamicomInfo(gfxprint* gfxprint);
void mRmTp_MakeFamicom_Fdebug();

#endif
