#include "lb_rtc.h"
#include "m_common_data.h"
#include "padmgr.h"
#include "722970.h"
#include "721EC0.h"
#include "7220C0.h"
#include "722310.h"
#include "722AB0.h"
#include "722880.h"
#include "macros.h"
#include "attributes.h"

s32 l_lbRTC_isInitial = 1;
s32 l_lbRTC_IsSampled = 0;

s32 B_80145620_jp;
lbRTC_time_c l_lbRTC_Time;

s32 lbRTC_Initial() {
    OSMesgQueue* mq;

    if (l_lbRTC_isInitial == 1) {
        mq = padmgr_LockSerialMesgQ();
        l_lbRTC_isInitial = 0;
        B_80145620_jp = func_800FECD0_jp(mq);
        padmgr_UnlockSerialMesgQ(mq);
    }
    return B_80145620_jp;
}

s32 lbRTC_IsOki(lbRTC_time_c* ptr) {
    s32 isInitial;
    OSMesgQueue* mq;

    isInitial = lbRTC_Initial();

    if (isInitial == 0) {
        mq = padmgr_LockSerialMesgQ();
        isInitial = func_800FE220_jp(mq, ptr);
        padmgr_UnlockSerialMesgQ(mq);
        if (isInitial == 0) {
            return isInitial;
        }
    }
    l_lbRTC_isInitial = 1;
    return isInitial;
}

s32 lbRTC_IsAbnormal() {
    lbRTC_time_c time;
    s32 temp UNUSED;
    s32 res = lbRTC_IsOki(&time);

    if ((res == 0) && (l_lbRTC_IsSampled == 1)) {
        s32 baseTimer = (l_lbRTC_Time.sec + (l_lbRTC_Time.min * 60));

        if ((time.sec + (time.min * 60)) != baseTimer) {
            return res;
        }
    }
    return res;
}

void lbRTC_Sampling() {
    lbRTC_time_c time;

    if ((lbRTC_IsOki(&time) == 0) && (!l_lbRTC_IsSampled)) {
        l_lbRTC_Time.sec = time.sec;
        l_lbRTC_Time.min = time.min;
        l_lbRTC_IsSampled = 1;
    }
}

void func_800D4F6C_jp(lbRTC_time_c* time) {
    OSMesgQueue* mq;

    if (lbRTC_Initial() == 0) {
        mq = padmgr_LockSerialMesgQ();
        func_800FEBE0_jp(mq, time);
        padmgr_UnlockSerialMesgQ(mq);
    }
}

void func_800D4FB8_jp(lbRTC_time_c* time) {
    OSMesgQueue* mq;

    if (lbRTC_Initial() == 0) {
        mq = padmgr_LockSerialMesgQ();
        func_800FE420_jp(mq, time);
        padmgr_UnlockSerialMesgQ(mq);
    }
}

void lbRTC_SetTime(lbRTC_time_c* time) {
    OSMesgQueue* mq;

    if (common_data.time.rtcEnabled == 1 && !common_data.time.rtcCrashed) {
        time->weekday = lbRTC_Week(time->year, time->month, time->day);
        mq = padmgr_LockSerialMesgQ();
        func_800FE670_jp(mq, time);
        padmgr_UnlockSerialMesgQ(mq);
    } else {
        lbRTC_TimeCopy(&common_data.time.rtcTime, time);
    }
}

void lbRTC_GetTime(lbRTC_time_c* time) {
    OSMesgQueue* mq;

    if (common_data.time.rtcEnabled == 1 && !common_data.time.rtcCrashed) {
        mq = padmgr_LockSerialMesgQ();
        func_800FE220_jp(mq, time);
        padmgr_UnlockSerialMesgQ(mq);
    } else {
        lbRTC_TimeCopy(time, &common_data.time.rtcTime);
    }
}

const lbRTC_day_t days_month[2][lbRTC_MONTHS_MAX + 1] = {
    // Regular year
    { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },

    // Leap year
    { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

lbRTC_day_t lbRTC_GetDaysByMonth(lbRTC_year_t year, lbRTC_month_t month) {
    s32 leap = !(year & 3) ? 1 : 0;
    s32 idx = leap == 1 ? 1 : 0;

    return days_month[idx][month];
}

typedef union lbRTCYMD {
    s32 raw;
    lbRTC_ymd_t ymd;
} lbRTCYMD;

s32 lbRTC_IsEqualDate(lbRTC_year_t y0, lbRTC_month_t m0, lbRTC_day_t d0, lbRTC_year_t y1, lbRTC_month_t m1,
                      lbRTC_day_t d1) {
    lbRTCYMD ymd0;
    lbRTCYMD ymd1;
    s32 res;

    ymd0.ymd.year = y0;
    ymd0.ymd.month = m0;
    ymd0.ymd.day = d0;

    ymd1.ymd.year = y1;
    ymd1.ymd.month = m1;
    ymd1.ymd.day = d1;

    res = ymd0.raw - ymd1.raw;
    if (res == 0) {
        return lbRTC_EQUAL;
    }

    if (res < 0) {
        return lbRTC_LESS;
    }
    return lbRTC_OVER;
}

s32 lbRTC_IsEqualTime(const lbRTC_time_c* t0, const lbRTC_time_c* t1, s32 flags) {
    s32 equal = 0;

    if (flags & lbRTC_CHECK_SECONDS) {
        if (t0->sec == t1->sec) {
            equal |= lbRTC_CHECK_SECONDS;
        }
    }

    if (flags & lbRTC_CHECK_MINUTES) {
        if (t0->min == t1->min) {
            equal |= lbRTC_CHECK_MINUTES;
        }
    }

    if (flags & lbRTC_CHECK_HOURS) {
        if (t0->hour == t1->hour) {
            equal |= lbRTC_CHECK_HOURS;
        }
    }

    if (flags & lbRTC_CHECK_WEEKDAYS) {
        if (t0->weekday == t1->weekday) {
            equal |= lbRTC_CHECK_WEEKDAYS;
        }
    }

    if (flags & lbRTC_CHECK_DAYS) {
        if (t0->day == t1->day) {
            equal |= lbRTC_CHECK_DAYS;
        }
    }

    if (flags & lbRTC_CHECK_MONTHS) {
        if (t0->month == t1->month) {
            equal |= lbRTC_CHECK_MONTHS;
        }
    }

    if (flags & lbRTC_CHECK_YEARS) {
        if (t0->year == t1->year) {
            equal |= lbRTC_CHECK_YEARS;
        }
    }

    return flags == (equal & flags);
}

s32 lbRTC_IsOverTime(const lbRTC_time_c* t0, const lbRTC_time_c* t1) {

    if (t1->year < t0->year) {
        return lbRTC_LESS;
    }

    if (t1->year == t0->year) {
        if (t1->month >= t0->month) {
            if (t1->month == t0->month) {
                if (t1->day >= t0->day) {
                    if (t1->day == t0->day) {
                        if (t1->hour >= t0->hour) {
                            if (t1->hour == t0->hour) {
                                if (t1->min >= t0->min) {
                                    if (t1->min == t0->min) {
                                        if (t1->sec < t0->sec) {
                                            return lbRTC_LESS;
                                        }
                                    }
                                } else {
                                    return lbRTC_LESS;
                                }
                            }
                        } else {
                            return lbRTC_LESS;
                        }
                    }
                } else {
                    return lbRTC_LESS;
                }
            }
        } else {
            return lbRTC_LESS;
        }
    }

    return lbRTC_OVER;
}

s32 lbRTC_IsJustAtRTC(const lbRTC_time_c* time, s32 flags) {
    lbRTC_time_c rtcTime;

    lbRTC_GetTime(&rtcTime);

    return lbRTC_IsEqualTime(&rtcTime, time, flags);
}

s32 lbRTC_IsOverRTC(const lbRTC_time_c* time) {
    lbRTC_time_c rtcTime;

    lbRTC_GetTime(&rtcTime);

    return lbRTC_IsOverTime(time, &rtcTime) == lbRTC_OVER;
}

s32 lbRTC_IsOverWeekRTC(const lbRTC_time_c* t0, lbRTC_weekday_t week) {
    s32 curWeek;
    lbRTC_time_c t1;

    curWeek = week - t0->weekday;
    t1 = *t0;

    if (curWeek <= 0) {
        curWeek += 7;
    }

    t1.hour = 0;
    t1.min = 0;
    t1.sec = 0;

    lbRTC_Add_DD(&t1, curWeek);
    lbRTC_IsOverRTC(&t1);
}

s32 lbRTC_IntervalTime(lbRTC_time_c* t0, lbRTC_time_c* t1) {

    lbRTC_time_c t2;
    lbRTC_time_c t3;

    t2 = *t0;
    t3 = *t1;

    func_800FF060_jp(&t3, &t2);
}

const int total_days[2][lbRTC_MONTHS_MAX + 1] = {
    // Standard year
    { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
    // Leap year
    { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
};

s32 lbRTC_GetIntervalDays(const lbRTC_time_c* t0, const lbRTC_time_c* t1) {
    s32 leapPeriod = (t1->year - t0->year) / 4;
    s32 years = (t1->year - t0->year) % 4;
    s32 lessLeap = (t0->year % 4) == 0;
    s32 overLeap = (t1->year % 4) == 0;
    s32 leapAdd = ((4 - (t0->year % 4)) % 4) < years;

    s32 days;

    if (t0->year > t1->year) {
        return 0;
    } else {
        if (t0->year == t1->year) {
            if (t0->month > t1->month) {
                return 0;
            } else {
                if (t0->month == t1->month) {
                    if (t0->day > t1->day) {
                        return 0;
                    } else {
                        if (t0->day == t1->day) {
                            if (t0->hour > t1->hour) {
                                return 0;
                            } else {
                                if (t0->hour == t1->hour) {
                                    if (t0->min > t1->min) {
                                        return 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    days = leapPeriod * 1461 + years * 365 + leapAdd;

    days += t1->day - 1;
    days += total_days[overLeap][t1->month - 1];

    days -= t0->day - 1;
    days -= total_days[lessLeap][t0->month - 1];

    return days;
}

void lbRTC_Add_YY(lbRTC_time_c* time, s32 years) {
    time->year += (u16)years;
}

void lbRTC_Add_MM(lbRTC_time_c* time, s32 month) {
    s32 timeMonth = time->month;

    timeMonth += month;

    if (timeMonth > lbRTC_MONTHS_MAX) {
        lbRTC_Add_YY(time, timeMonth / lbRTC_MONTHS_MAX);
        timeMonth %= lbRTC_MONTHS_MAX;
    }

    time->month = (lbRTC_month_t)timeMonth;
}

void lbRTC_Add_DD(lbRTC_time_c* time, s32 day) {
    s32 days = lbRTC_GetDaysByMonth(time->year, (lbRTC_month_t)time->month);
    s32 timeDay = time->day;

    timeDay += day;

    if (timeDay > days) {
        timeDay -= days;
        lbRTC_Add_MM(time, 1);
    }

    time->day = (lbRTC_day_t)timeDay;
}

void lbRTC_Add_hh(lbRTC_time_c* time, s32 hour) {
    s32 timeHour = time->hour;

    timeHour += hour;
    if (timeHour >= lbRTC_HOURS_PER_DAY) {
        lbRTC_Add_DD(time, timeHour / lbRTC_HOURS_PER_DAY);
        timeHour %= lbRTC_HOURS_PER_DAY;
    }

    time->hour = (lbRTC_hour_t)timeHour;
}

void lbRTC_Add_mm(lbRTC_time_c* time, s32 min) {
    s32 timeSec = time->min;

    timeSec += min;
    if (timeSec >= lbRTC_MINUTES_PER_HOUR) {
        lbRTC_Add_hh(time, timeSec / lbRTC_MINUTES_PER_HOUR);
        timeSec %= lbRTC_MINUTES_PER_HOUR;
    }

    time->min = (lbRTC_min_t)timeSec;
}

void lbRTC_Add_ss(lbRTC_time_c* time, s32 sec) {
    int timeSec = time->sec;

    timeSec += sec;
    if (timeSec >= lbRTC_SECONDS_PER_MINUTE) {
        lbRTC_Add_mm(time, timeSec / lbRTC_SECONDS_PER_MINUTE);
        timeSec %= lbRTC_SECONDS_PER_MINUTE;
    }

    time->sec = (lbRTC_sec_t)timeSec;
}

void lbRTC_Add_Date(lbRTC_time_c* time, const lbRTC_time_c* add_time) {
    lbRTC_Add_ss(time, add_time->sec);
    lbRTC_Add_mm(time, add_time->min);
    lbRTC_Add_hh(time, add_time->hour);
    lbRTC_Add_DD(time, add_time->day);
    lbRTC_Add_MM(time, add_time->month);
    lbRTC_Add_YY(time, add_time->year);
}

void lbRTC_Sub_YY(lbRTC_time_c* time, s32 year) {
    time->year -= (lbRTC_year_t)year;
}

void lbRTC_Sub_MM(lbRTC_time_c* time, s32 month) {
    s32 calcMonth = time->month - month;
    if (calcMonth < 1) {
        s32 temp = calcMonth;
        s32 year;

        if (calcMonth == 0) {
            calcMonth = lbRTC_MONTHS_MAX;
            year = 1;
        } else {
            temp = ABS(calcMonth);
            year = temp / lbRTC_MONTHS_MAX + 1;
            calcMonth = lbRTC_MONTHS_MAX - (temp % lbRTC_MONTHS_MAX);
        }

        lbRTC_Sub_YY(time, year);
    }

    time->month = (lbRTC_month_t)calcMonth;
}

void lbRTC_Sub_DD(lbRTC_time_c* time, s32 days) {
    s32 currentDay = time->day;
    s32 day;

    if (time->month == lbRTC_JANUARY) {
        day = lbRTC_GetDaysByMonth(time->year, lbRTC_MONTHS_MAX);
    } else {
        day = lbRTC_GetDaysByMonth(time->year, (time->month - 1));
    }

    currentDay -= days;

    if (currentDay <= 0) {
        if (currentDay == 0) {
            currentDay = day;
        } else {
            currentDay += day;
        }

        lbRTC_Sub_MM(time, 1);
    }

    time->day = (lbRTC_day_t)currentDay;
}

void lbRTC_Sub_hh(lbRTC_time_c* time, s32 hour) {
    s32 timeHour = time->hour;
    timeHour -= hour;

    if (timeHour < 0) {
        s32 temp = timeHour;
        s32 days;

        temp = ABS(timeHour);
        days = temp / lbRTC_HOURS_PER_DAY + 1;
        timeHour = lbRTC_HOURS_PER_DAY - (temp % lbRTC_HOURS_PER_DAY);

        if (timeHour == lbRTC_HOURS_PER_DAY) {
            timeHour = 0;
            days--;
        }

        lbRTC_Sub_DD(time, days);
    }

    time->hour = (lbRTC_hour_t)timeHour;
}

void lbRTC_Sub_mm(lbRTC_time_c* time, s32 min) {
    s32 timeMin = time->min;
    timeMin -= min;

    if (timeMin < 0) {
        s32 temp = timeMin;
        s32 hours;

        temp = ABS(timeMin);
        hours = temp / lbRTC_MINUTES_PER_HOUR + 1;
        timeMin = lbRTC_MINUTES_PER_HOUR - (temp % lbRTC_MINUTES_PER_HOUR);

        if (timeMin == lbRTC_MINUTES_PER_HOUR) {
            timeMin = 0;
            hours--;
        }

        lbRTC_Sub_hh(time, hours);
    }

    time->min = (lbRTC_min_t)timeMin;
}

void lbRTC_Sub_ss(lbRTC_time_c* time, s32 sec) {
    s32 timeSec = time->sec;
    timeSec -= sec;

    if (timeSec < 0) {
        s32 temp = timeSec;
        s32 mins;

        temp = ABS(timeSec);
        mins = temp / lbRTC_SECONDS_PER_MINUTE + 1;
        timeSec = lbRTC_SECONDS_PER_MINUTE - (temp % lbRTC_SECONDS_PER_MINUTE);

        if (timeSec == lbRTC_SECONDS_PER_MINUTE) {
            timeSec = 0;
            mins--;
        }

        lbRTC_Sub_mm(time, mins);
    }

    time->sec = (lbRTC_sec_t)timeSec;
}

void lbRTC_Sub_Date(lbRTC_time_c* time, const lbRTC_time_c* sub_time) {
    lbRTC_Sub_ss(time, sub_time->sec);
    lbRTC_Sub_mm(time, sub_time->min);
    lbRTC_Sub_hh(time, sub_time->hour);
    lbRTC_Sub_DD(time, sub_time->day);
    lbRTC_Sub_MM(time, sub_time->month);
    lbRTC_Sub_YY(time, sub_time->year);
}

const lbRTC_time_c a_time = { 0, 0, 0, 1, 0, 1, 1901 };

lbRTC_weekday_t lbRTC_Week(lbRTC_year_t year, lbRTC_month_t month, lbRTC_day_t day) {

    lbRTC_time_c b_time = { 0, 0, 0, 0, 0, 0, 0000 };

    b_time.year = year;
    b_time.month = month;
    b_time.day = day;

    return (lbRTC_weekday_t)((lbRTC_GetIntervalDays(&a_time, &b_time) + 2) % lbRTC_WEEKDAYS_MAX);
}

void lbRTC_TimeCopy(lbRTC_time_c* dst, const lbRTC_time_c* src) {
    *dst = *src;
}

const lbRTC_day_t day_tbl[] = { 00, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

s32 lbRTC_IsValidTime(const lbRTC_time_c* time) {
    s32 res;

    if ((time->year < lbRTC_YEAR_MIN || time->year > lbRTC_YEAR_MAX) || (time->month == lbRTC_MONTHS_BEGIN) ||
        (time->month > lbRTC_MONTHS_MAX) || (time->day == 0) || (time->hour > lbRTC_HOURS_PER_DAY - 1) ||
        (time->min > lbRTC_MINUTES_PER_HOUR - 1) || (time->sec > lbRTC_SECONDS_PER_MINUTE - 1)) {
        res = 0;
    } else {
        if (time->day == 29 && time->month == lbRTC_FEBRUARY) {
            res = !(time->year & 3) ? 1 : 0;
        } else if (time->day > day_tbl[time->month]) {
            res = 0;
        } else {
            res = 1;
        }
    }

    return res;
}
