#include "lbrtc.h"

s32 lbrtc_getTime(OSMesgQueue* mq, OSRTCTime* time) {
    __OSContRTCData rtc[1];
    __OSContRTCData data;
    u8 status;
    s32 ret;

    ret = func_800FE480_jp(mq, &status);
    if (ret == 0) {
        ret = func_800FEE10_jp(mq, RTC_TIME_BLOCK_TYPE, (u8*)&data);
        if (ret == 0) {
            ret = func_800FEE10_jp(mq, RTC_TIME_BLOCK_TYPE, (u8*)&rtc);
            if (bcmp(&data, &rtc, sizeof(__OSContRTCData)) != 0) {
                ret = func_800FEE10_jp(mq, RTC_TIME_BLOCK_TYPE, (u8*)&rtc);
            }
            time->sec = (rtc[0].sec & 0xF) + ((rtc[0].sec >> 4) * 10);
            time->min = (rtc[0].min & 0xF) + ((rtc[0].min >> 4) * 10);
            time->hour = (((rtc[ret * 0].hour - 0x80) >> 4) * 10) + (((rtc + 0)->hour - 0x80) & 0xF);
            time->day = (rtc[0].day & 0xF) + ((rtc[0].day >> 4) * 10);
            time->weekday = rtc[0].weekday;
            time->month = (rtc[0].month & 0xF) + ((rtc[0].month >> 4) * 10);
            if (rtc[0].centuriesSince1900 != 0) {
                time->year = ((rtc[0].yearLo & 0xF) + ((rtc[0].yearLo >> 4) * 10)) + 2000;
            } else {
                time->year = ((rtc[0].yearLo & 0xF) + ((rtc[0].yearLo >> 4) * 10)) + 1900;
            }
        }
    }
    return ret;
}
