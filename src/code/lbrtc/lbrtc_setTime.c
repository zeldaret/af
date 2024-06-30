#include "lbrtc.h"
#include "attributes.h"

s32 lbrtc_setTime(OSMesgQueue* mq, OSRTCTime* time) {
    __OSContRTCData rtc[1];
    UNUSED s32 pad;
    __OSContRTCControlRegs cr[1];
    u8 status;
    s32 ret;

    ret = func_800FE480_jp(mq, &status);
    if (ret == 0) {
        ret = func_800FEE10_jp(mq, RTC_CR_BLOCK_TYPE, (u8*)&cr);
        if (ret == 0) {
            cr[0].writeProtectBitfield &= ~RTC_WRITE_PROTECT_RTC_BIT;
            cr[0].flagsBitfield |= RTC_WRITE_STOP_COUNT_BIT;
            ret = func_800FE8D0_jp(mq, RTC_CR_BLOCK_TYPE, (u8*)&cr);
            if (ret == RTC_STOPPED) {
                rtc[0].sec = (time->sec % 10) + ((time->sec / 10) * 0x10);
                rtc[0].min = (time->min % 10) + ((time->min / 10) * 0x10);
                rtc[0].hour = (time->hour % 10) + ((time->hour / 10) * 0x10);
                rtc[0].day = (time->day % 10) + ((time->day / 10) * 0x10);
                rtc[0].weekday = time->weekday;
                rtc[0].month = (time->month % 10) + ((time->month / 10) * 0x10);
                rtc[0].yearLo = (time->year % 10) + (((time->year % 100) / 10) * 0x10);
                if (time->year >= 2000) {
                    rtc[0].centuriesSince1900 = 1;
                } else {
                    rtc[0].centuriesSince1900 = 0;
                }
                ret = func_800FE8D0_jp(mq, RTC_TIME_BLOCK_TYPE, (u8*)&rtc);
                if (ret == RTC_STOPPED) {
                    cr[0].writeProtectBitfield |= RTC_WRITE_PROTECT_RTC_BIT;
                    cr[0].flagsBitfield &= ~RTC_WRITE_STOP_COUNT_BIT;
                    ret = func_800FE8D0_jp(mq, RTC_CR_BLOCK_TYPE, (u8*)&cr);
                }
            }
        }
    }
    return ret;
}
