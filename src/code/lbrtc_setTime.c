#include "lbrtc.h"
#include "attributes.h"


s32 lbrtc_setTime(OSMesgQueue* mq, OSRTCTime* time) {
    __OSRTCTime rtc[1];
    UNUSED s32 pad;
    __lbrtc_struct_unk3 unk[1];
    s8 sp1F; 
    s32 ret;

    ret = func_800FE480_jp(mq, (u8*)&sp1F);
    if (ret == 0) {
        ret = func_800FEE10_jp(mq, 0, (u8*)&unk);
        if (ret == 0) {
            unk[0].unk0 &= ~2;
            unk[0].unk1 |= 4;
            ret = func_800FE8D0_jp(mq, 0, (u8*)&unk);
            if (ret == 0x10) {
                rtc[0].sec = (time->sec % 10) + ((time->sec / 10) * 0x10);
                rtc[0].min = (time->min % 10) + ((time->min / 10) * 0x10);
                rtc[0].hour = (time->hour % 10) + ((time->hour / 10) * 0x10);
                rtc[0].day = (time->day % 10) + ((time->day / 10) * 0x10);
                rtc[0].weekday = time->weekday;
                rtc[0].month = (time->month % 10) + ((time->month / 10) * 0x10);
                rtc[0].centuryYear = (time->year % 10) + (((time->year % 100) / 10) * 0x10);
                if (time->year >= 2000) {
                    rtc[0].status = RTC_STATUS_VALID;
                } else {
                    rtc[0].status = RTC_STATUS_CRASHED;
                }
                ret = func_800FE8D0_jp(mq, 2, (u8*)&rtc);
                if (ret == 0x10) {
                    unk[0].unk0 |= 2;
                    unk[0].unk1 &= ~4;
                    ret = func_800FE8D0_jp(mq, 0, (u8*)&unk);
                }
            }
        }
    }
    return ret;
}
 