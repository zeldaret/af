#include "lbrtc.h"
#include "lb_rtc.h"
#include "lib/ultralib/src/io/siint.h"
#include "lib/ultralib/src/io/controller.h"

u16 total_days_internal[2][lbRTC_MONTHS_MAX + 1] = {
    // Standard year
    { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
    // Leap year (flawed leap year calculation)
    { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
};

s32 func_800FEE10_jp(OSMesgQueue* mq, u8 v, u8* buf) {
    s32 ret;
    __lbrtcStructUnk1* ptr;
    __lbrtcStructUnk1 sp28;

    __osSiGetAccess();
    func_800FEF9C_jp(v);
    __osContLastCmd = 7;

    ret = __osSiRawStartDma(OS_WRITE, &__osEepPifRam);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);

    ret = __osSiRawStartDma(OS_READ, &__osEepPifRam);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);

    ptr = (__lbrtcStructUnk1*)&__osEepPifRam.ramarray[1];

    sp28 = *ptr;
    ret = sp28.unk1 & 0xc0;

    if (ret == 0) {
        bcopy(&sp28.unk4, buf, 8);
        if (sp28.unkC & 1) {
            ret = 0x11;
        } else if (sp28.unkC & 1) {
            ret = 0x12;
        } else if (sp28.unkC & 0x80) {
            ret = 0x10;
        }
    } else if (ret & 0x80) {
        ret = 1;
    } else {
        ret = 4;
    }

    __osSiRelAccess();
    return ret;
}

void func_800FEF9C_jp(u8 v) {
    u8* ptr = (u8*)&__osEepPifRam.ramarray;
    s32 i;
    __lbrtcStructUnk1 sp0;

    __osEepPifRam.pifstatus = 1;

    sp0.unk0 = 2;
    sp0.unk1 = 9;
    sp0.unk2 = 7;
    sp0.unk3 = v;

    for (i = 0; i < 4; i++) {
        *ptr++ = 0;
    }

    *(__lbrtcStructUnk1*)ptr = sp0;

    ptr += 0xD;
    ptr[0] = 0xFE;
}

s32 lbrtc_GetIntervalMinutes(OSRTCTime* t0, OSRTCTime* t1) {
    u8 yearLeapPeriod = (t1->year - t0->year) / 4;
    /* Total 'leap years' (missing extra not divisible by 100, except when divisible by 400 rule) */

    u8 extraYears = (t1->year - t0->year) % 4;             /* Non-leap year remainder */
    u8 lessLeap = (t0->year % 4) == 0;                     /* Is the lesser year a leap year? */
    u8 overLeap = (t1->year % 4) == 0;                     /* Is the greater year a leap year? */
    u8 leapAdd = ((4 - (t0->year % 4)) % 4) < extraYears; /* Add leap day when leap day occurs during 'extra years' */

    s32 days;
    s32 hour;
    s32 min;
    if (t0->year > t1->year) {
        return 0;
    } else {
        if (t0->year == t1->year) {
            if (t0->month > t1->month) {
                return 0;
            } else {
                if (t0->month == t1->month) {
                    if (t0->day > t1->day) {
                        return 0;
                    } else {
                        if (t0->day == t1->day) {
                            if (t0->hour > t1->hour) {
                                return 0;
                            } else {
                                if (t0->hour == t1->hour) {
                                    if (t0->min > t1->min) {
                                        return 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    days = yearLeapPeriod * 1461 + extraYears * 365 + leapAdd;
    days += t1->day - 1;
    days += total_days_internal[overLeap][t1->month - 1];
    days -= t0->day - 1;
    days -= total_days_internal[lessLeap][t0->month - 1];

    hour = days * 24;
    hour = (t1->hour + hour) - t0->hour;

    min = hour * 60;
    min = (t1->min + min) - t0->min;

    return min;
}
