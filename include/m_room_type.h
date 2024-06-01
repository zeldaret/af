#ifndef M_ROOM_TYPE_H
#define M_ROOM_TYPE_H

#include "ultra64.h"
#include "libu64/gfxprint.h"

struct Game;

#define mRmTp_FTR_UNIT_MAX 4
#define FTR_NUM 947

typedef enum mRmTp_FurnitureSize {
    mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x2,
    mRmTp_FTRSIZE_2x2,
    mRmTp_FTRSIZE_MAX
} mRmTp_FurnitureSize;

typedef enum mRmTp_Direction {
    mRmTp_DIRECT_SOUTH,
    mRmTp_DIRECT_EAST,
    mRmTp_DIRECT_NORTH,
    mRmTp_DIRECT_WEST,
    mRmTp_DIRECT_MAX
} mRmTp_Direction;

typedef enum mRmTp_SEType {
    mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_SOFT_CHAIR,
    mRmTp_FTR_SE_HARD_CHAIR,
    mRmTp_FTR_SE_BUBU_CHAIR,
    mRmTp_FTR_SE_TOILET_CHAIR,
    mRmTp_FTR_SE_MAX
} mRmTp_SEType;

typedef enum mRmTp_Action {
    mRmTp_CHAIR_ACTION_SIT,
    mRmTp_CHAIR_ACTION_STAND,

    mRmTp_CHAIR_ACTION_MAX
} mRmTp_Action;

typedef enum mRmTp_BirthType {
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_BIRTHDAY,
    mRmTp_BIRTH_TYPE_HALLOWEEN,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_SINGLE_FOSSIL,
    mRmTp_BIRTH_TYPE_MULTI_FOSSIL,
    mRmTp_BIRTH_TYPE_XMAS,
    mRmTp_BIRTH_TYPE_SANTA,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_SNOWMAN,
} mRmTp_BirthType;

typedef struct mRmTp_FtrPlaceInfo {
    s32 exists;
    s32 utX;
    s32 utZ;
} mRmTp_FtrPlaceInfo;

typedef struct mRmTp_FtrPlaceData {
    u8 exist;
    s16 ofsX;
    s16 ofsZ;
} mRmTp_FtrPlaceData;

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
