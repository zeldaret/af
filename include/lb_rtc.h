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

#endif
