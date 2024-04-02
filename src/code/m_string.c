#include "m_string.h"
#include "m_std_dma.h"
#include "m_lib.h"

#include "m_msg_main.h"
#include "6B3DC0.h"

extern u32 D_D18000[];
extern u32 D_D16000;
void mString_Get_StringDataAddressAndSize(s32 idx, uintptr_t* vramp, size_t* size) {
    s32 sized;
    uintptr_t offsetPtrs[5];

    if (idx >= 0 && idx < 0x61A) {
        uintptr_t vrom;
        if (idx & 1) {
            DmaMgr_RequestSyncDebug(offsetPtrs, (u32)&D_D18000[idx - 1], 8, "../m_string.c", 62);
            vrom = offsetPtrs[0];
            sized = offsetPtrs[1] - vrom;
        } else if (idx == 0) {
            DmaMgr_RequestSyncDebug(offsetPtrs, (u32)&D_D18000, 8, "../m_string.c", 69);
            vrom = 0;
            sized = offsetPtrs[0] - vrom;
        } else {
            DmaMgr_RequestSyncDebug(offsetPtrs, (u32)&D_D18000[idx - 2], 16, "../m_string.c", 75);
            vrom = offsetPtrs[1];
            sized = offsetPtrs[2] - vrom;
        }
        if (sized < 65) {
            *vramp = (uintptr_t)vrom + (u32)&D_D16000;
            *size = sized;
        } else {
            *vramp = NULL;
            *size = 0;
        }
    } else {
        *vramp = NULL;
        *size = 0;
    }
}

void mString_Load_StringFromRom(char* dst, s32 dstLen, s32 strIdx) {
    uintptr_t stringAddr;
    size_t stringSize;

    if (strIdx >= 0 && strIdx < 0x61A) {
        mString_Get_StringDataAddressAndSize(strIdx, &stringAddr, &stringSize);

        if (stringSize == 0) {
            mem_clear((u8*)dst, dstLen, ' ');
        } else if (stringAddr != 0) {
            char buff[80];
            u32 baseAddr = stringAddr & ~7;
            s32 ofs = stringAddr - baseAddr;
            s32 i;
            char* strSrc;
            s32 sizeCopy;
            char* strDst;
            UNUSED s32 pad;

            DmaMgr_RequestSyncDebug(buff, baseAddr, ALIGN8(ofs + stringSize), "../m_string.c", 153);
            if (dstLen < (s32)stringSize) {
                stringSize = dstLen;
            }

            strDst = dst;
            sizeCopy = stringSize;
            strSrc = &buff[ofs];
            for (i = 0; i < sizeCopy; i++) {
                *strDst++ = *strSrc++;
            }

            for (; i < dstLen; i++) {
                *strDst++ = ' ';
            }
        }
    }
}

s32 mString_Load_YearStringFromRom(char* dst, lbRTC_year_t year) {
    s32 idx;

    if (year < lbRTC_YEAR_MIN || year > lbRTC_YEAR_MAX) {
        year = GAME_YEAR_MIN;
    }

    idx = mFont_UnintToString(dst, year, 6, TRUE, FALSE);
    mString_Load_StringFromRom(&dst[idx], 6 - idx, 3);
    return mMsg_Get_Length_String(dst, 6);
}

s32 mString_Load_MonthStringFromRom(char* dst, lbRTC_month_t month) {
    s32 idx;

    if (month < lbRTC_JANUARY || month > lbRTC_DECEMBER) {
        month = lbRTC_JANUARY;
    }

    idx = mFont_UnintToString(dst, month, 4, TRUE, FALSE);
    mString_Load_StringFromRom(&dst[idx], 4 - idx, 4);
    return mMsg_Get_Length_String(dst, 4);
}

s32 mString_Load_WeekStringFromRom(char* dst, lbRTC_weekday_t weekday) {
    if (weekday > lbRTC_SATURDAY) {
        weekday = 0;
    }

    mString_Load_StringFromRom(dst, 5, weekday + 9);
    return mMsg_Get_Length_String(dst, 4);
}

s32 mString_Load_DayStringFromRom(char* dst, lbRTC_day_t day) {
    s32 idx;

    if (day < 1 || day > 31) {
        day = 1;
    }

    idx = mFont_UnintToString(dst, day, 4, TRUE, FALSE);
    mString_Load_StringFromRom(&dst[idx], 4 - idx, 5);
    return mMsg_Get_Length_String(dst, 4);
}

s32 mString_Load_HourStringFromRom(char* dst, lbRTC_hour_t hour) {
    UNUSED s32 pad;
    s32 specifier;
    s32 len;

    if (hour > 23) {
        hour = 0;
    }

    specifier = hour < 12 ? 1 : 2;

    mString_Load_StringFromRom(dst, 6, specifier);
    len = mMsg_Get_Length_String(dst, 6);
    len += mFont_UnintToString(dst + len, hour % 12, 6 - len, TRUE, FALSE);

    mString_Load_StringFromRom(dst + len, 6 - len, 6);
    return mMsg_Get_Length_String(dst, 6);
}

s32 mString_Load_MinStringFromRom(char* dst, lbRTC_min_t min) {
    s32 idx;

    if (min > 59) {
        min = 0;
    }

    idx = mFont_UnintToString(dst, min, 4, TRUE, FALSE);
    mString_Load_StringFromRom(&dst[idx], 4 - idx, 7);
    return mMsg_Get_Length_String(dst, 4);
}

s32 mString_Load_SecStringFromRom(char* dst, lbRTC_sec_t sec) {
    s32 idx;

    if (sec > 59) {
        sec = 0;
    }

    idx = mFont_UnintToString(dst, sec, 5, TRUE, FALSE);
    mString_Load_StringFromRom(&dst[idx], 5 - idx, 8);
    return mMsg_Get_Length_String(dst, 5);
}

s32 mString_Load_NumberStringAddUnitFromRom(char* dst, u16 num, s32 idx) {
    s32 len = mFont_UnintToString(dst, num, 10, TRUE, FALSE);

    mString_Load_StringFromRom(&dst[len], 10 - len, idx);
    return mMsg_Get_Length_String(dst, 10);
}
