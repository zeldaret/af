#include "lbrtc.h"
#include "attributes.h"

s32 D_801160C0_jp = 0;

s32 lbrtc_init(OSMesgQueue* mq) {
    s32 ret;
    u8 status;
    UNUSED s32 pad;
    __OSContRTCControlRegs rtc[1];

    ret = func_800FE480_jp(mq, &status);
    if (ret == 0) {
        if (D_801160C0_jp == 0) {
            osCreateMesgQueue(&__contRTCMesgQ, &__contRTCMesg, OS_MESG_BLOCK);
            D_801160C0_jp = 1;
        }
        if (status & RTC_STATUS_STOPPED) {
            ret = func_800FEE10_jp(mq, RTC_CR_BLOCK_TYPE, (u8*)&rtc);
            if ((ret == 0) || (ret == RTC_STOPPED)) {
                rtc[0].flagsBitfield &= ~RTC_WRITE_STOP_COUNT2_BIT;
                ret = func_800FE8D0_jp(mq, RTC_CR_BLOCK_TYPE, (u8*)&rtc);
            }
        }
        if (status & RTC_STATUS_BATTERY_FAILURE) {
            ret = (status & RTC_STATUS_CRYSTAL_FAILURE) ? 0x13 : RTC_ERR_BATTERY;

        } else if (status & RTC_STATUS_CRYSTAL_FAILURE) {
            ret = RTC_ERR_CRYSTAL;
        }
    }
    return ret;
}
