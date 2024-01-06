#ifndef LB_RTC_H
#define LB_RTC_H

#include "ultra64.h"

/* TODO: do these have a better header? */
#define GAME_YEAR_MIN 2000 /* Minimum year supported by the game */
#define GAME_YEAR_MAX 2032 /* Maximum year supported by the game */

#define lbRTC_YEAR_MIN 1901
#define lbRTC_YEAR_MAX 2099

typedef u8 lbRTC_sec_t;
typedef u8 lbRTC_min_t;
typedef u8 lbRTC_hour_t;
typedef u8 lbRTC_day_t;
typedef u8 lbRTC_weekday_t;
typedef u8 lbRTC_month_t;
typedef u16 lbRTC_year_t;

/* Name leaked in lbRTC_time_c_save_data_check */
typedef struct lbRTC_time_c {
  /* 0x00 */ lbRTC_sec_t sec;
  /* 0x01 */ lbRTC_min_t min;
  /* 0x02 */ lbRTC_hour_t hour;
  /* 0x03 */ lbRTC_day_t day;
  /* 0x04 */ lbRTC_weekday_t weekday;
  /* 0x05 */ lbRTC_month_t month;
  /* 0x06 */ lbRTC_year_t year;
} lbRTC_time_c; // size = 0x8

/* Name leaked in mTM_ymd_2_time */
typedef struct lbRTC_ymd_t {
    /* 0x00 */ lbRTC_year_t year;
    /* 0x02 */ lbRTC_month_t month;
    /* 0x03 */ lbRTC_day_t day;
} lbRTC_ymd_t; // size = 0x4

typedef enum WEEKDAYS {
    /* 0 */ lbRTC_WEEKDAYS_BEGIN = 0,
    /* 0 */ lbRTC_SUNDAY = lbRTC_WEEKDAYS_BEGIN,
    /* 1 */ lbRTC_MONDAY,
    /* 2 */ lbRTC_TUESDAY,
    /* 3 */ lbRTC_WEDNESDAY,
    /* 4 */ lbRTC_THURSDAY,
    /* 5 */ lbRTC_FRIDAY,
    /* 6 */ lbRTC_SATURDAY,
    /* 7 */ lbRTC_WEEK,
    /* 7 */ lbRTC_WEEKDAYS_MAX = lbRTC_WEEK
} WEEKDAYS;

typedef enum MONTHS {
    /* 0 */ lbRTC_MONTHS_BEGIN = 0,
    /* 1 */ lbRTC_JANUARY = 1,
    /* 2 */ lbRTC_FEBRUARY,
    /* 3 */ lbRTC_MARCH,
    /* 4 */ lbRTC_APRIL,
    /* 5 */ lbRTC_MAY,
    /* 6 */ lbRTC_JUNE,
    /* 7 */ lbRTC_JULY,
    /* 8 */ lbRTC_AUGUST,
    /* 9 */ lbRTC_SEPTEMBER,
    /* 10 */ lbRTC_OCTOBER,
    /* 11 */ lbRTC_NOVEMBER,
    /* 12 */ lbRTC_DECEMBER,
    /* 12 */ lbRTC_MONTHS_MAX = lbRTC_DECEMBER
} MONTHS;

typedef enum RTC_EQUALITY {
    lbRTC_LESS = -1,
    lbRTC_EQUAL = 0,
    lbRTC_OVER = 1
} RTC_EQUALITY;

typedef enum RTC_EQUALITY_FLAGS {
    /* 0x00 */lbRTC_CHECK_NONE = 0,

    /* 0x01 */lbRTC_CHECK_SECONDS = 1 << 0,   
    /* 0x02 */lbRTC_CHECK_MINUTES = 1 << 1,   
    /* 0x04 */lbRTC_CHECK_HOURS = 1 << 2,     
    /* 0x08 */lbRTC_CHECK_WEEKDAYS = 1 << 3,  
    /* 0x10 */lbRTC_CHECK_DAYS = 1 << 4,      
    /* 0x20 */lbRTC_CHECK_MONTHS = 1 << 5,    
    /* 0x40 */lbRTC_CHECK_YEARS = 1 << 6,     
    
    /* 0x7F */
    lbRTC_CHECK_ALL = lbRTC_CHECK_SECONDS |
                      lbRTC_CHECK_MINUTES |
                      lbRTC_CHECK_HOURS |
                      lbRTC_CHECK_WEEKDAYS |
                      lbRTC_CHECK_DAYS |
                      lbRTC_CHECK_MONTHS |
                      lbRTC_CHECK_YEARS
} RTC_EQUALITY_FLAGS;

#define lbRTC_HOURS_PER_DAY 24
#define lbRTC_MINUTES_PER_HOUR 60
#define lbRTC_SECONDS_PER_MINUTE 60

#define lbRTC_IS_LEAPYEAR(year) \
  (((year % 4) == 0 && ((year % 100) != 0)) || ((year % 400) == 0))

s32 lbRTC_Initial(void);
s32 lbRTC_IsOki(lbRTC_time_c* ptr);
s32 lbRTC_IsAbnormal(void);
void lbRTC_Sampling(void);
void func_800D4F6C_jp(lbRTC_time_c* time);
void func_800D4FB8_jp(lbRTC_time_c* time);
void lbRTC_SetTime(lbRTC_time_c* time);
void lbRTC_GetTime(lbRTC_time_c* time);
lbRTC_day_t lbRTC_GetDaysByMonth(lbRTC_year_t year, lbRTC_month_t month);
s32 lbRTC_IsEqualDate(lbRTC_year_t y0, lbRTC_month_t m0, lbRTC_day_t d0, lbRTC_year_t y1,
                      lbRTC_month_t m1, lbRTC_day_t d1);
s32 lbRTC_IsEqualTime(const lbRTC_time_c* t0, const lbRTC_time_c* t1, s32 flags);
s32 lbRTC_IsOverTime(const lbRTC_time_c* t0, const lbRTC_time_c* t1);
s32 lbRTC_IsJustAtRTC(const lbRTC_time_c* time, s32 flags);
s32 lbRTC_IsOverRTC(const lbRTC_time_c* time);
s32 lbRTC_IsOverWeekRTC(const lbRTC_time_c* t0, lbRTC_weekday_t week);
s32 lbRTC_IntervalTime(lbRTC_time_c* t0, lbRTC_time_c* t1);
s32 lbRTC_GetIntervalDays(const lbRTC_time_c* t0, const lbRTC_time_c* t1);
void lbRTC_Add_YY(lbRTC_time_c* time, s32 years);
void lbRTC_Add_MM(lbRTC_time_c* time, s32 month);
void lbRTC_Add_DD(lbRTC_time_c* time, s32 day);
void lbRTC_Add_hh(lbRTC_time_c* time, s32 hour);
void lbRTC_Add_mm(lbRTC_time_c* time, s32 min);
void lbRTC_Add_ss(lbRTC_time_c* time, s32 sec);
void lbRTC_Add_Date(lbRTC_time_c* time, const lbRTC_time_c* add_time);
void lbRTC_Sub_YY(lbRTC_time_c* time, s32 year);
void lbRTC_Sub_MM(lbRTC_time_c* time, s32 month);
void lbRTC_Sub_DD(lbRTC_time_c* time, s32 days);
void lbRTC_Sub_hh(lbRTC_time_c* time, s32 hour);
void lbRTC_Sub_mm(lbRTC_time_c* time, s32 min);
void lbRTC_Sub_ss(lbRTC_time_c* time, s32 sec);
void lbRTC_Sub_Date(lbRTC_time_c* time, const lbRTC_time_c* sub_time);
lbRTC_weekday_t lbRTC_Week(lbRTC_year_t year, lbRTC_month_t month, lbRTC_day_t day);
void lbRTC_TimeCopy(lbRTC_time_c* dst, const lbRTC_time_c* src);
s32 lbRTC_IsValidTime(const lbRTC_time_c* time);

extern s32 l_lbRTC_isInitial;
extern s32 l_lbRTC_IsSampled;

extern s32 B_80145620_jp;
extern lbRTC_time_c l_lbRTC_Time;

#endif
