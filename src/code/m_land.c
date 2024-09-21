#include "m_land.h"
#include "m_string.h"
#include "m_lib.h"
#include "m_msg_main.h"
#include "6B81C0.h"

s32 mLd_NullCheckLandName(char* landName) {
    s32 isNull = FALSE;
    s32 i;

    for (i = 0; i < LAND_NAME_SIZE; i++) {
        if (*landName != ' ') {
            break;
        }
        landName++;
    }

    if (i == LAND_NAME_SIZE) {
        isNull = TRUE;
    }
    return isNull;
}

s32 mLd_CheckId(u16 landId) {
    s32 res = FALSE;

    if (mLd_CHECK_ID(landId)) {
        res = TRUE;
    }

    return res;
}

s32 mLd_CheckCmpLandName(char* nameA, char* nameB) {
    s32 equal = FALSE;

    if (mLd_NullCheckLandName(nameA) == FALSE && mLd_NullCheckLandName(nameB) == FALSE) {
        equal = mem_cmp((u8*)nameA, (u8*)nameB, LAND_NAME_SIZE);
    }

    return equal;
}

s32 mLd_CheckCmpLand(char* nameA, u16 idA, char* nameB, u16 idB) {
    s32 equal = FALSE;

    if (idA == idB && mLd_CheckCmpLandName(nameA, nameB) == TRUE) {
        equal = TRUE;
    }

    return equal;
}

void mLd_ClearLandName(char* name) {
    mem_clear((u8*)name, LAND_NAME_SIZE, ' ');
}

void mLd_CopyLandName(char* nameA, char* nameB) {
    mem_copy((u8*)nameA, (u8*)nameB, LAND_NAME_SIZE);
}

size_t mLd_AddMuraString(char* name, size_t len) {
    char buf[10];
    size_t size;
    UNUSED s32 pad;
    size_t lenNew;

    mString_Load_StringFromRom(buf, sizeof(buf), 484);
    size = mMsg_Get_Length_String(buf, sizeof(buf));
    lenNew = size + len;

    mem_copy((u8*)(name + len), (u8*)buf, size);

    return lenNew;
}

size_t mLd_GetLandNameStringAddMura(char* buf) {
    char* name;
    size_t size;
    size_t muraSize;
    s32 i;

    name = mLd_GetLandName();
    size = mMsg_Get_Length_String(name, LAND_NAME_SIZE);

    mem_copy((u8*)buf, (u8*)name, size);
    muraSize = mLd_AddMuraString(buf, size);

    for (i = muraSize; i < LAND_NAME_MURA_SIZE; i++) {
        buf[i] = ' ';
    }

    return muraSize;
}

void mLd_SetFreeStrLandMuraName(char* name, s32 freeStr) {
    char str[8];
    size_t nameLen;
    s32 i;

    for (i = 0; i < LAND_NAME_MURA_SIZE; i++) {
        str[i] = ' ';
    }

    nameLen = mMsg_Get_Length_String(name, LAND_NAME_SIZE);
    mem_copy((u8*)str, (u8*)name, nameLen);
    nameLen = mLd_AddMuraString(str, nameLen);
    mMsg_Set_free_str(mMsg_Get_base_window_p(), freeStr, str, nameLen);
}

char* mLd_GetLandName() {
    return common_data.save.landInfo.name;
}

u16 mLd_MakeLandId() {
    return (u16)(RANDOM_F(256)) | 0x3000;
}

s32 mLd_PlayerManKindCheckNo(u8 playerNo) {
    s32 foreigner = TRUE;

    if (playerNo < PLAYER_NUM) {
        foreigner = FALSE;
    }

    return foreigner;
}

s32 mLd_PlayerManKindCheck() {
    return mLd_PlayerManKindCheckNo(common_data.playerNumber);
}

s32 mLd_CheckThisLand(char* otherName, u16 otherId) {
    return mLd_CheckCmpLand(otherName, otherId, common_data.save.landInfo.name, common_data.save.landInfo.id);
}

void mLd_LandInfoInit() {
    LandInfo* landInfo = &common_data.save.landInfo;

    landInfo->id = mLd_MakeLandId();
    landInfo->exists = TRUE;
}

void mLd_LandDataInit() {
    mLd_LandInfoInit();
    mHm_ClearAllHomeInfo();
}
