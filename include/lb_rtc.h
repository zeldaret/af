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

enum WEEKDAYS {
    lbRTC_WEEKDAYS_BEGIN = 0,
    lbRTC_SUNDAY = lbRTC_WEEKDAYS_BEGIN,
    lbRTC_MONDAY,
    lbRTC_TUESDAY,
    lbRTC_WEDNESDAY,
    lbRTC_THURSDAY,
    lbRTC_FRIDAY,
    lbRTC_SATURDAY,
    lbRTC_WEEK,
    lbRTC_WEEKDAYS_MAX = lbRTC_WEEK
};

enum MONTHS {
    lbRTC_MONTHS_BEGIN = 0,
    lbRTC_JANUARY = 1,
    lbRTC_FEBRUARY,
    lbRTC_MARCH,
    lbRTC_APRIL,
    lbRTC_MAY,
    lbRTC_JUNE,
    lbRTC_JULY,
    lbRTC_AUGUST,
    lbRTC_SEPTEMBER,
    lbRTC_OCTOBER,
    lbRTC_NOVEMBER,
    lbRTC_DECEMBER,
    lbRTC_MONTHS_MAX = lbRTC_DECEMBER
};

enum RTC_EQUALITY {
    lbRTC_LESS = -1,
    lbRTC_EQUAL = 0,
    lbRTC_OVER = 1
};

enum RTC_EQUALITY_FLAGS {
    lbRTC_CHECK_NONE = 0,           /* 0x00 */
    
    lbRTC_CHECK_SECONDS = 1 << 0,   /* 0x01 */
    lbRTC_CHECK_MINUTES = 1 << 1,   /* 0x02 */
    lbRTC_CHECK_HOURS = 1 << 2,     /* 0x04 */
    lbRTC_CHECK_WEEKDAYS = 1 << 3,  /* 0x08 */
    lbRTC_CHECK_DAYS = 1 << 4,      /* 0x10 */
    lbRTC_CHECK_MONTHS = 1 << 5,    /* 0x20 */
    lbRTC_CHECK_YEARS = 1 << 6,     /* 0x40 */
    
    /* 0x7F */
    lbRTC_CHECK_ALL = lbRTC_CHECK_SECONDS |
                      lbRTC_CHECK_MINUTES |
                      lbRTC_CHECK_HOURS |
                      lbRTC_CHECK_WEEKDAYS |
                      lbRTC_CHECK_DAYS |
                      lbRTC_CHECK_MONTHS |
                      lbRTC_CHECK_YEARS
};

#define lbRTC_HOURS_PER_DAY 24
#define lbRTC_MINUTES_PER_HOUR 60
#define lbRTC_SECONDS_PER_MINUTE 60

#define lbRTC_IS_LEAPYEAR(year) \
  (((year % 4) == 0 && ((year % 100) != 0)) || ((year % 400) == 0))

#endif
