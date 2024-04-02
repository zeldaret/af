#ifndef C_6E7AD0_H
#define C_6E7AD0_H

#include "ultra64.h"
#include "lb_rtc.h"
#include "libc/stdint.h"

void mString_Get_StringDataAddressAndSize(s32 idx, uintptr_t* vramp, size_t* size);
void mString_Load_StringFromRom(char* dst, s32 dstLen, s32 strIdx);
s32 mString_Load_YearStringFromRom(char* dst, lbRTC_year_t year);
s32 mString_Load_MonthStringFromRom(char* dst, lbRTC_month_t month);
s32 mString_Load_WeekStringFromRom(char* dst, lbRTC_weekday_t weekday);
s32 mString_Load_DayStringFromRom(char* dst, lbRTC_day_t day);
s32 mString_Load_HourStringFromRom(char* dst, lbRTC_hour_t hour);
s32 mString_Load_MinStringFromRom(char* dst, lbRTC_min_t min);
s32 mString_Load_SecStringFromRom(char* dst, lbRTC_sec_t sec);
s32 mString_Load_NumberStringAddUnitFromRom(char* dst, u16 num, s32 idx);

#endif
