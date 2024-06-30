#include "lbrtc.h"
#include "lib/ultralib/src/io/siint.h"
#include "lib/ultralib/src/io/controller.h"

OSTimer __contRTCTimer;
OSMesgQueue __contRTCMesgQ;
OSMesg __contRTCMesg;

s32 func_800FE8D0_jp(OSMesgQueue* mq, u8 blockType, u8* data) {
    s32 ret;
    u8* ptr;
    __OSContRTCRWFormat format;

    __osSiGetAccess();
    func_800FEABC_jp(blockType, data);
    ret = __osSiRawStartDma(OS_WRITE, &__osEepPifRam);
    __osContLastCmd = CONT_CMD_WRITE_RTC;

    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    ret = __osSiRawStartDma(OS_READ, &__osEepPifRam);
    ptr = (u8*)(&__osEepPifRam.ramarray[1]);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);

    format = *((__OSContRTCRWFormat*)ptr);
    ret = CHNL_ERR(format);

    __osSiRelAccess();

    osSetTimer(&__contRTCTimer, OS_USEC_TO_CYCLES(300), 0, &__contRTCMesgQ, &__contRTCMesg);
    osRecvMesg(&__contRTCMesgQ, NULL, OS_MESG_BLOCK);
    if (ret == 0) {
        bcopy(&format.data, data, sizeof(__OSContRTCData));
        if (format.status & RTC_STATUS_BATTERY_FAILURE) {
            ret = RTC_ERR_BATTERY;
            //! @bug should have checked for RTC_STATUS_CRYSTAL_FAILURE
        } else if (format.status & RTC_STATUS_BATTERY_FAILURE) {
            ret = RTC_ERR_CRYSTAL;
        } else if (format.status & RTC_STATUS_STOPPED) {
            ret = RTC_STOPPED;
        }
    } else if (ret & CHNL_ERR_NORESP) {
        ret = 1;
    } else {
        ret = 4;
    }
    __osSiRelAccess();

    return ret;
}

s32 func_800FEABC_jp(u8 blockType, u8* data) {
    s32 i;
    u8* ptr = (u8*)&__osEepPifRam;
    __OSContRTCRWFormat format;

    for (i = 0; i < ARRLEN(__osEepPifRam.ramarray); i++) {
        __osEepPifRam.ramarray[i] = 0xFF;
    }

    __osEepPifRam.pifstatus = CONT_CMD_EXE;

    format.txsize = CONT_CMD_WRITE_RTC_TX;
    format.rxsize = CONT_CMD_WRITE_RTC_RX;
    format.cmd = CONT_CMD_WRITE_RTC;
    format.blockType = blockType;

    for (i = 0; i < (s32)sizeof(__OSContRTCData); i++) {
        (&format.txsize)[i + 4] = *data++;
    }

    for (i = 0; i < 4; i++) {
        *ptr++ = 0;
    }
    *(__OSContRTCRWFormat*)ptr = format;

    ptr += sizeof(__OSContRTCRWFormat);
    *ptr = CONT_CMD_END;
}
