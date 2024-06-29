#include "lbrtc.h"

s32 lbrtc_getTime(OSMesgQueue* mq, OSRTCTime* time) {
    __OSRTCTime rtc[1];
    __OSRTCTime sp1F;
    u8 sp20;
    s32 ret;

    ret = func_800FE480_jp(mq, &sp20);
    if (ret == 0) {
        ret = func_800FEE10_jp(mq, 2, (u8*)&sp1F);
        if (ret == 0) {
            ret = func_800FEE10_jp(mq, 2, (u8*)&rtc);
            if (bcmp(&sp1F, &rtc, 8) != 0) {
                ret = func_800FEE10_jp(mq, 2, (u8*)&rtc);
            }
            time->sec = (rtc[0].sec & 0xF) + ((rtc[0].sec >> 4) * 0xA);
            time->min = (rtc[0].min & 0xF) + ((rtc[0].min >> 4) * 0xA);
            time->hour = (((rtc[ret * 0].hour - 0x80) >> 4) * 0xA) + (((rtc + 0)->hour - 0x80) & 0xF);
            time->day = (rtc[0].day & 0xF) + ((rtc[0].day >> 4) * 0xA);
            time->weekday = rtc[0].weekday;
            time->month = (rtc[0].month & 0xF) + ((rtc[0].month >> 4) * 0xA);
            if (rtc[0].status != RTC_STATUS_CRASHED) {
                time->year = ((rtc[0].centuryYear & 0xF) + ((rtc[0].centuryYear >> 4) * 0xA)) + 2000;
            } else {
                time->year = ((rtc[0].centuryYear & 0xF) + ((rtc[0].centuryYear >> 4) * 0xA)) + 1900;
            }
        }
    }
    return ret;
}
