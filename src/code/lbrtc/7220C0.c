#include "lbrtc.h"
#include "lib/ultralib/src/io/siint.h"
#include "lib/ultralib/src/io/controller.h"

s32 func_800FE420_jp(OSMesgQueue* mq, OSRTCTime* time) {
    u8 status;
    s32 ret;

    ret = func_800FE480_jp(mq, &status);

    if (ret == 0) {
        ret = func_800FEE10_jp(mq, RTC_SRAM_BLOCK_TYPE, (u8*)time);
    }

    return ret;
}

s32 func_800FE480_jp(OSMesgQueue* mq, u8* status) {
    s32 ret = 0;
    s32 i;
    u8* ptr;
    __OSContRTCInfoFormat format;

    __osSiGetAccess();

    __osEepPifRam.pifstatus = CONT_CMD_EXE;

    ptr = (u8*)&__osEepPifRam.ramarray;

    for (i = 0; i < 4; i++) {
        *ptr++ = 0;
    }

    format.txsize = CONT_CMD_RTC_INFO_TX;
    format.rxsize = CONT_CMD_RTC_INFO_RX;
    format.cmd = CONT_CMD_RTC_INFO;

    *(__OSContRTCInfoFormat*)ptr = format;

    ptr += sizeof(__OSContRTCInfoFormat);

    *ptr = CONT_CMD_END;

    ret = __osSiRawStartDma(OS_WRITE, &__osEepPifRam);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);

    __osContLastCmd = CONT_CMD_RTC_INFO;

    ret = __osSiRawStartDma(OS_READ, &__osEepPifRam);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);

    ptr = (u8*)&__osEepPifRam.ramarray[1];

    format = *(__OSContRTCInfoFormat*)ptr;

    ret = (format.rxsize & CHNL_ERR_MASK) & 0xFF;

    if (ret == 0) {
        if (!(((format.unk4 << 8) | format.unk3) & 0xFFFF & 0x1000)) {
            ret = 0xB;
        } else {
            *status = format.status;
        }
    } else if (ret & CHNL_ERR_NORESP) {
        ret = 1;
    } else {
        ret = 4;
    }

    __osSiRelAccess();
    return ret;
}
