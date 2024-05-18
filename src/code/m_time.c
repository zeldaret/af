#include "m_time.h"
#include "zurumode.h"
#include "m_common_data.h"
#include "gfx.h"
#include "gfxalloc.h"
#include "6BA500.h"
#include "game.h"

s32 debug_disp = FALSE;

TimeCalendarTerm mTM_calender[mTM_TERM_MAX] = {
    { lbRTC_FEBRUARY, 3, mTM_SEASON_WINTER, 0x0050, 0x0025 },
    { lbRTC_FEBRUARY, 17, mTM_SEASON_WINTER, 0x0050, 0x0025 },
    { lbRTC_FEBRUARY, 24, mTM_SEASON_WINTER, 0x0050, 0x0025 },
    { lbRTC_MARCH, 31, mTM_SEASON_SPRING, 0x0001, 0x0004 },
    { lbRTC_APRIL, 8, mTM_SEASON_SPRING, 0x004f, 0x0024 },
    { lbRTC_MAY, 25, mTM_SEASON_SPRING, 0x0001, 0x0004 },
    { lbRTC_JULY, 22, mTM_SEASON_SUMMER, 0x0001, 0x0004 },
    { lbRTC_AUGUST, 31, mTM_SEASON_SUMMER, 0x0001, 0x0004 },
    { lbRTC_SEPTEMBER, 15, mTM_SEASON_SUMMER, 0x0001, 0x0004 },
    { lbRTC_SEPTEMBER, 30, mTM_SEASON_AUTUMN, 0x0001, 0x0004 },
    { lbRTC_OCTOBER, 15, mTM_SEASON_AUTUMN, 0x0001, 0x0004 },
    { lbRTC_OCTOBER, 29, mTM_SEASON_AUTUMN, 0x0001, 0x0004 },
    { lbRTC_NOVEMBER, 12, mTM_SEASON_AUTUMN, 0x0001, 0x0004 },
    { lbRTC_NOVEMBER, 26, mTM_SEASON_AUTUMN, 0x0001, 0x0004 },
    { lbRTC_DECEMBER, 9, mTM_SEASON_AUTUMN, 0x0001, 0x0004 },
    { lbRTC_DECEMBER, 17, mTM_SEASON_WINTER, 0x0051, 0x0026 },
    { lbRTC_DECEMBER, 24, mTM_SEASON_WINTER, 0x0051, 0x0026 },
    { lbRTC_DECEMBER, 31, mTM_SEASON_WINTER, 0x0050, 0x0025 },
};

u8 l_renew_is = mTM_RENEW_TIME_NONE;

const lbRTC_time_c mTM_rtcTime_clear_code = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFFFF,
};

const lbRTC_ymd_t mTM_rtcTime_ymd_clear_code = {
    0xFF,
    0xFF,
    0xFF,
};

const lbRTC_time_c mTM_rtcTime_default_code = {
    0, 0, 12, 1, lbRTC_SATURDAY, lbRTC_JANUARY, 2000,
};

s32 mTM_get_termIdx() {
    lbRTC_month_t month = common_data.time.rtcTime.month;
    lbRTC_day_t day = common_data.time.rtcTime.day;
    TimeCalendarTerm* info = mTM_calender;
    u32 term;

    for (term = 0; term < mTM_TERM_MAX; info++, term++) {
        if (month < info->month || (month == info->month && day <= info->day)) {
            return term;
        }
    }

    return -1;
}

void mTM_set_season() {
    s32 termIdx = mTM_get_termIdx();
    TimeCalendarTerm* info = mTM_calender + termIdx;

    common_data.time.season = info->season;
    common_data.time.termIdx = termIdx;
    common_data.time.bgitemProfile = info->bgitemProfile;
    common_data.time.bgitemBank = info->bgitemBank;
}

void mTM_clear_renew_is() {
    l_renew_is = mTM_RENEW_TIME_NONE;
}

s32 mTM_check_renew_time(u8 flag) {
    s32 renew = FALSE;

    if (((l_renew_is >> flag) & 1) == 1) {
        renew = TRUE;
    }

    return renew;
}

void mTM_off_renew_time(u8 flag) {
    l_renew_is &= ~(1 << flag);
}

void mTM_set_renew_is() {
    l_renew_is = mTM_RENEW_TIME_ALL;
}

void mTM_set_renew_time(lbRTC_ymd_t* renewTime, lbRTC_time_c* time) {
    renewTime->year = time->year;
    renewTime->month = time->month;
    renewTime->day = time->day;
}

void mTM_renewal_renew_time() {
    lbRTC_ymd_t* renewTime = &common_data.renewTime;
    lbRTC_time_c* rtcTime = &common_data.time.rtcTime;

    if ((renewTime->year != rtcTime->year) || (renewTime->month != rtcTime->month) ||
        (renewTime->day != rtcTime->day)) {
        mTM_set_renew_time(renewTime, rtcTime);
        mTM_set_renew_is();
    }
}

void mTM_disp_time(UNUSED s32 unused) {

    if (common_data.time.addIdx != 1 && zurumode_flag != 0 && (gamePT->input[1].press.button & A_BUTTON) == A_BUTTON) {
        static s32 disp = FALSE;
        disp = disp ^ TRUE;
        common_data.time.disp = disp;
    }

    if (common_data.time.disp == TRUE) {
        GraphicsContext* graph = gamePT->gfxCtx;
        Gfx* gfxTemp;
        Gfx* gfxTemp2;
        gfxprint* gfxprintPtr;
        gfxprint gfxprint;

        gfxprintPtr = &gfxprint;

        gfxprint_init(gfxprintPtr);

        OPEN_DISPS(graph);
        gfxTemp2 = POLY_OPA_DISP;
        gfxTemp = gfxopen(gfxTemp2);

        gSPDisplayList(OVERLAY_DISP++, gfxTemp);

        gfxprint_open(gfxprintPtr, gfxTemp);
        gfxprint_color(gfxprintPtr, 255, 255, 255, 255);
        gfxprint_locate8x8(gfxprintPtr, 3, 3);
        gfxprint_printf(gfxprintPtr, "%04d", (common_data.time.rtcTime.year));
        gfxprint_locate8x8(gfxprintPtr, 8, 3);
        gfxprint_printf(gfxprintPtr, "%02d/", (common_data.time.rtcTime.month));
        gfxprint_locate8x8(gfxprintPtr, 11, 3);
        gfxprint_printf(gfxprintPtr, "%02d", (common_data.time.rtcTime.day));
        gfxprint_locate8x8(gfxprintPtr, 14, 3);
        gfxprint_printf(gfxprintPtr, "%02d:", (common_data.time.rtcTime.hour));
        gfxprint_locate8x8(gfxprintPtr, 17, 3);
        gfxprint_printf(gfxprintPtr, "%02d", (common_data.time.rtcTime.min));
        gfxprint_locate8x8(gfxprintPtr, 20, 3);
        gfxprint_printf(gfxprintPtr, "%02d", (common_data.time.rtcTime.sec));

        gfxTemp = gfxprint_close(gfxprintPtr);
        gSPEndDisplayList(gfxTemp++);

        gfxclose(gfxTemp2, gfxTemp);

        POLY_OPA_DISP = gfxTemp;

        CLOSE_DISPS(graph);

        gfxprint_cleanup(gfxprintPtr);
    }
}

s32 mTM_TimestepControl() {
    static s32 id = 0;
    static s32 timestep[] = { 240, 480, 960 };
    s32 addSec;

    if (zurumode_flag != 0 && zurumode_flag >= 2 && debug_disp == TRUE &&
        (gamePT->input[1].press.button & R_TRIG) == R_TRIG) {
        if (id < 3) {
            common_data.time.rtcCrashed = TRUE;

            common_data.time.addSec = timestep[id];

            addSec -= 1;
            id++;
        } else {
            common_data.time.rtcCrashed = FALSE;
            common_data.time.addIdx = 0;
            lbRTC_SetTime(&common_data.time.rtcTime);

            id = 0;
        }
    }

    return id != 0;
}
void mTM_time() {
    u8 day = common_data.time.rtcTime.day;

    mTM_TimestepControl();
    if (common_data.time.rtcEnabled == TRUE && common_data.time.rtcCrashed == FALSE) {
        lbRTC_GetTime(&common_data.time.rtcTime);
        if ((zurumode_flag != 0) && ((gamePT->input[1].press.button & A_BUTTON) == A_BUTTON)) {
            debug_disp ^= TRUE;
        }
        if (debug_disp == TRUE) {
            mTM_disp_time(0);
        }
    } else {
        s32 addSec = common_data.time.addSec;
        s32 sec = common_data.time.underSec;

        {
            s32 timeAddSec = 0;
            sec += addSec;
            while (sec >= mTM_SECONDS_IN_MINUTE) {
                timeAddSec++;
                sec -= mTM_SECONDS_IN_MINUTE;
            }

            lbRTC_Add_ss(&common_data.time.rtcTime, timeAddSec);
            common_data.time.rtcTime.weekday = lbRTC_Week(
                (common_data.time.rtcTime.year), (common_data.time.rtcTime.month), (common_data.time.rtcTime.day));
        }

        common_data.time.underSec = sec;
        if ((zurumode_flag != 0) && (gamePT->input[1].press.button & A_BUTTON) == A_BUTTON) {
            debug_disp ^= TRUE;
        }
        if (debug_disp == TRUE) {
            mTM_disp_time(sec);
        }
    }

    {
        s32 temp2 = (common_data.time.rtcTime.sec) + (common_data.time.rtcTime.min * mTM_MINUTES_IN_HOUR) +
                    (common_data.time.rtcTime.hour) * mTM_SECONDS_IN_HOUR;

        common_data.time.nowSec = temp2;
    }

    if (common_data.time.rtcTime.day != day) {
        Kabu_manager();
    }

    {
        s32 temp3 = (common_data.time.rtcTime.min * 60) + (common_data.time.rtcTime.sec);

        common_data.time.radMin = ((temp3 / ((f32)mTM_SECONDS_IN_HOUR)) * 65536.0f);
        common_data.time.radHour =
            ((((common_data.time.rtcTime.hour) * 3600 + temp3) / ((f32)mTM_SECONDS_IN_HALFDAY)) * 65536.0f);
    }

    mTM_renewal_renew_time();
}
