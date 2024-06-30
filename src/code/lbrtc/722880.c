#include "lbrtc.h"
#include "attributes.h"

s32 func_800FEBE0_jp(OSMesgQueue* mq, OSRTCTime* time) {
    u32 ret;
    UNUSED s32 pad;
    __OSContRTCControlRegs rtc[1];
    u8 status;

    ret = func_800FE480_jp(mq, &status);
    if (ret == 0) {
        ret = func_800FEE10_jp(mq, RTC_CR_BLOCK_TYPE, (u8*)&rtc);
        if (ret == 0) {
            rtc[0].writeProtectBitfield &= ~RTC_WRITE_PROTECT_NVRAM_BIT;
            ret = func_800FE8D0_jp(mq, RTC_CR_BLOCK_TYPE, (u8*)&rtc);
            if (ret == 0) {
                ret = func_800FE8D0_jp(mq, RTC_SRAM_BLOCK_TYPE, (u8*)time);
                if (ret == 0) {
                    rtc[0].writeProtectBitfield |= RTC_WRITE_PROTECT_NVRAM_BIT;
                    ret = func_800FE8D0_jp(mq, RTC_CR_BLOCK_TYPE, (u8*)&rtc);
                }
            }
        }
    }
    return ret;
}
