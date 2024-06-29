#include "lbrtc.h"
#include "attributes.h"

s32 func_800FEBE0_jp(OSMesgQueue* mq, OSRTCTime* time) {
    u32 ret;
    UNUSED s32 pad;
    u8 rtc[1];
    u8 sp1B;

    ret = func_800FE480_jp(mq, &sp1B);
    if (ret == 0) {
        ret = func_800FEE10_jp(mq, 0, &rtc[0]);
        if (ret == 0) {
            rtc[0] &= ~1;
            ret = func_800FE8D0_jp(mq, 0, &rtc[0]);
            if (ret == 0) {
                ret = func_800FE8D0_jp(mq, 1, (u8*)time);
                if (ret == 0) {
                    rtc[0] |= 1;
                    ret = func_800FE8D0_jp(mq, 0, rtc);
                }
            }
        }
    }
    return ret;
}
