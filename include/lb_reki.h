#ifndef LB_REKI_H
#define LB_REKI_H

#include "ultra64.h"
#include "lb_rtc.h"

typedef struct lbRekiPhase {
  /* 0x00 */ lbRTC_month_t month;
  /* 0x01 */ lbRTC_day_t day;
} lbRekiPhase; // size = 0x2

#define lbRk_YEAR_MIN GAME_YEAR_MIN
#define lbRk_YEAR_MAX GAME_YEAR_MAX
#define lbRk_YEAR_NUM ((lbRk_YEAR_MAX - lbRk_YEAR_MIN) + 1)

#define lbRk_KYUU_MONTH_START 1
#define lbRk_KYUU_MONTH_END 12
#define lbRk_KYUU_LEAP_MONTH 13

#define lbRk_HARVEST_MOON_YEAR_MIN 2002
#define lbRk_HARVEST_MOON_YEAR_MAX 2030

#define lbRk_KYUU_DAY_START 1

s32 lbRk_SeirekiDays(s32 /*year*/, s32 /*month*/);
lbRekiPhase* lbRk_ToSeiyoMonthAndDay(s32 /*year*/, s32 /*month*/);
s32 lbRk_KyuurekiLeapDays(s32 /*year*/);
s32 lbRk_IsKyuurekiLeapYear(s32 /*year*/);
s32 lbRk_IsLeapMonth(s32 /*month*/);
s32 lbRk_IsLeapOnNextMonth(s32 /*year*/, s32 /*month*/);
s32 lbRk_KyuurekiDays(s32 /*year*/, s32 /*month*/);
s32 lbRk_ToSeiyouReki(lbRTC_ymd_t* /*seiyoTime*/, const lbRTC_ymd_t* /*kyuuTime*/);
s32 lbRk_ToKyuuReki(lbRTC_ymd_t* /*kyuuTime*/, const lbRTC_ymd_t* /*seiyoTime*/);
#endif
