
#include "m_cockroach.h"
#include "m_common_data.h"
#include "m_house.h"
#include "m_field_info.h"
#include "code_variables.h"
#include "attributes.h"

s32 mCkRh_GokiFamilyCount2Good(s32 count) {
    if (count < 0) {
        return 0;
    }

    if (count > mCkRh_MAX_NUM) {
        return mCkRh_MAX_NUM;
    }

    return count;
}

s32 mCkRh_InitGokiSaveData_1Room(s32 player) {
    common_data.homes[player & 3].goki.num = 0;
    common_data.homes[player & 3].goki.pad = 0;
    common_data.homes[player & 3].goki.time.year = common_data.time.rtcTime.year;
    common_data.homes[player & 3].goki.time.month = common_data.time.rtcTime.month;
    common_data.homes[player & 3].goki.time.day = common_data.time.rtcTime.day;
}

void mCkRh_InitGokiSaveData_1Room_ByHomeData(mHm_hs_c* home) {
    home->goki.num = 0;
    home->goki.pad = 0;
    home->goki.time.year = common_data.time.rtcTime.year;
    home->goki.time.month = common_data.time.rtcTime.month;
    home->goki.time.day = common_data.time.rtcTime.day;
}

void mCkRh_InitGokiSaveData_InitNewPlayer() {
    s32 i;

    for (i = 0; i < PLAYER_NUM; i++) {
        mCkRh_InitGokiSaveData_1Room(i);
    }
}

void mCkRh_SavePlayTime(s32 player) {
    s32 home;

    if (player < PLAYER_NUM) {
        home = mHS_get_arrange_idx(player) & 3;
        common_data.homes[home].goki.time.year = common_data.time.rtcTime.year;
        common_data.homes[home].goki.time.month = common_data.time.rtcTime.month;
        common_data.homes[home].goki.time.day = common_data.time.rtcTime.day;
    }
}

s32 mCkRh_DaysGapCompareWithSaveTime(s32 player) {
    s32 home;
    s32 pad UNUSED;

    if (player < PLAYER_NUM) {
        lbRTC_time_c gokiTime;

        home = mHS_get_arrange_idx(player) & 3;
        gokiTime.year = common_data.homes[home].goki.time.year;
        gokiTime.month = common_data.homes[home].goki.time.month;
        gokiTime.day = common_data.homes[home].goki.time.day;

        gokiTime.weekday = lbRTC_Week(gokiTime.year, gokiTime.month, gokiTime.day);
        gokiTime.hour = 1;
        gokiTime.min = 1;
        gokiTime.sec = 1;

        return lbRTC_GetIntervalDays(&gokiTime, &common_data.time.rtcTime);
    } else {
        return 0;
    }
}

void mCkRh_DecideNowGokiFamilyCount(s32 player) {
    s32 dayGap;
    s32 home;

    if (player < PLAYER_NUM) {
        dayGap = mCkRh_DaysGapCompareWithSaveTime(player);
        home = mHS_get_arrange_idx(player) & 3;
        if (dayGap > 6) {
            s32 gokiNum;
            s32 count;
            gokiNum = common_data.homes[home].goki.num;
            count = gokiNum > 0 ? dayGap : dayGap - 6;
            common_data.homes[home].goki.num = mCkRh_GokiFamilyCount2Good(count + gokiNum);
        }
    }
}

s32 mCkRh_PlussGokiN_NowRoom(s32 count) {
    u16 fieldId = mFI_GetFieldId();
    s32 player;
    s32 housefieldId;
    s32 homeId;
    s32 num;
    s32 pad[1] UNUSED;

    if (FI_IS_PLAYER_ROOM(fieldId)) {
        player = common_data.playerNumber;
        housefieldId = FI_GET_PLAYER_ROOM_NO(fieldId);
        homeId = mHS_get_arrange_idx(player) & 3;
        if ((player < PLAYER_NUM) && (housefieldId == homeId)) {
            num = common_data.homes[homeId].goki.num;

            common_data.homes[homeId].goki.num = mCkRh_GokiFamilyCount2Good(count + num);
            return TRUE;
        }
    }
    return FALSE;
}

s32 mCkRh_MinusGokiN_NowRoom(s32 count) {
    u16 fieldId = mFI_GetFieldId();
    s32 player;
    s32 housefieldId;
    s32 homeId;
    s32 num;
    s32 pad[1] UNUSED;

    if (FI_IS_PLAYER_ROOM(fieldId)) {
        player = common_data.playerNumber;
        housefieldId = FI_GET_PLAYER_ROOM_NO(fieldId);
        homeId = mHS_get_arrange_idx(player) & 3;
        if ((player < PLAYER_NUM) && (housefieldId == homeId)) {
            num = common_data.homes[homeId].goki.num;
            common_data.homes[homeId].goki.num = mCkRh_GokiFamilyCount2Good(num - count);
            return TRUE;
        }
    }
    return FALSE;
}

s32 mCkRh_NowSceneGokiFamilyCount() {
    u16 fieldid = mFI_GetFieldId();

    if (FI_IS_PLAYER_ROOM(fieldid)) {
        return common_data.homes[FI_GET_PLAYER_ROOM_NO(fieldid)].goki.num;
    } else {
        return 0;
    }
}

void mCkRh_InitCanLookGokiCount() {
    CanLookGokiCount = 0;
}

s32 mCkRh_CalcCanLookGokiCount(s32 count) {
    s32 calc = count + CanLookGokiCount;

    if (calc < 0) {
        CanLookGokiCount = 0;
        return FALSE;
    }

    if (calc > mCkRh_MAX_LOOK_NUM) {
        CanLookGokiCount = mCkRh_MAX_LOOK_NUM;
        return FALSE;
    }

    CanLookGokiCount = calc;

    return TRUE;
}

s32 mCkRh_GetCanLookGokiCount() {
    return CanLookGokiCount;
}
