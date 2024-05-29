#ifndef M_TIME_H
#define M_TIME_H

#include "ultra64.h"
#include "lb_rtc.h"

/* TODO: this might have a better header to live in */
#define mTM_FIELD_RENEW_HOUR 6 /* hour which daily things 'reset' */

#define mTM_MIN_YEAR 2001
#define mTM_MAX_YEAR 2030

typedef enum mTM_SEASON{
    /* 0 */ mTM_SEASON_BEGIN = 0,
    /* 0 */ mTM_SEASON_SPRING = mTM_SEASON_BEGIN,
    /* 1 */ mTM_SEASON_SUMMER,
    /* 2 */ mTM_SEASON_AUTUMN,
    /* 3 */ mTM_SEASON_WINTER,

    /* 4 */ mTM_SEASON_NUM
} mTM_SEASON;

typedef enum mTM_TERM{
    /*  0 */ mTM_TERM_BEGIN = 0,
    /*  0 */ mTM_TERM_0 = mTM_TERM_BEGIN,
    /*  1 */ mTM_TERM_1,
    /*  2 */ mTM_TERM_2,
    /*  3 */ mTM_TERM_3,
    /*  4 */ mTM_TERM_4,
    /*  5 */ mTM_TERM_5,
    /*  6 */ mTM_TERM_6,
    /*  7 */ mTM_TERM_7,
    /*  8 */ mTM_TERM_8,
    /*  9 */ mTM_TERM_9,
    /* 10 */ mTM_TERM_10,
    /* 11 */ mTM_TERM_11,
    /* 12 */ mTM_TERM_12,
    /* 13 */ mTM_TERM_13,
    /* 14 */ mTM_TERM_14,
    /* 15 */ mTM_TERM_15,
    /* 16 */ mTM_TERM_16,
    /* 17 */ mTM_TERM_17,

    /* 18 */ mTM_TERM_MAX
} mTM_TERM;

#define mTM_RENEW_TIME_NONE 0
#define mTM_RENEW_TIME_ALL 0xFF

typedef enum mTM_RENEW_TIME{
  /* 0 */ mTM_RENEW_TIME_BEGIN = 0,
  /* 0 */ mTM_RENEW_TIME_WEATHER = mTM_RENEW_TIME_BEGIN,
  /* 1 */ mTM_RENEW_TIME_DAILY
} mTM_RENEW_TIME;

#define mTM_SECONDS_IN_MINUTE 60
#define mTM_SECONDS_IN_HOUR 60*60
#define mTM_SECONDS_IN_HALFDAY 12*60*60
#define mTM_SECONDS_IN_DAY 24*60*60

#define mTM_MINUTES_IN_HOUR 60

typedef struct TimeCalendarTerm {
    /* 0x00 */ lbRTC_month_t month;
    /* 0x01 */ lbRTC_day_t day;
    /* 0x02 */ u16 season;
    /* 0x04 */ s16 bgitemProfile;
    /* 0x06 */ s16 bgitemBank;
} TimeCalendarTerm; // size = 0x8

extern const lbRTC_time_c mTM_rtcTime_clear_code;
extern const lbRTC_ymd_t mTM_rtcTime_ymd_clear_code;
extern const lbRTC_time_c mTM_rtcTime_default_code;

#define mTM_IsTimeCleared(time) (lbRTC_IsEqualTime((time), &mTM_rtcTime_clear_code, lbRTC_CHECK_ALL) == TRUE)
#define mTM_AreTimesEqual(t0, t1) (lbRTC_IsEqualTime(t0, t1, lbRTC_CHECK_ALL))

#define mTM_CheckCmpYMDEqual(ymd0, ymd1) ((ymd0)->year == (ymd1)->year && (ymd0)->month == (ymd1)->month && (ymd0)->day == (ymd1)->day)
#define mTM_CheckCmpYMDClear(ymd0) ((ymd0)->year == mTM_rtcTime_ymd_clear_code.year || (ymd0)->month == mTM_rtcTime_ymd_clear_code.month || (ymd0)->day == mTM_rtcTime_ymd_clear_code.day)

s32 mTM_get_termIdx(void);
void mTM_set_season(void);
void mTM_clear_renew_is(void);
s32 mTM_check_renew_time(u8 flag);
void mTM_off_renew_time(u8 flag);
void mTM_set_renew_is(void);
void mTM_set_renew_time(lbRTC_ymd_t* renewTime, lbRTC_time_c* time);
void mTM_renewal_renew_time(void);
void mTM_disp_time(s32 unused);
s32 mTM_TimestepControl(void);
void mTM_time(void);


#endif
