#include "PR/os_internal.h"
#include "PRinternal/controller.h"
#include "PRinternal/siint.h"

void __osPackResetData(void);

s32 osContReset(OSMesgQueue* mq, OSContStatus* data) {
    u8 pattern;
    s32 ret;

    __osSiGetAccess();

    if (__osContLastCmd != CONT_CMD_RESET) {
        __osPackResetData();

        ret = __osSiRawStartDma(OS_WRITE, __osContPifRam.ramarray);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);

        ret = __osSiRawStartDma(OS_READ, __osContPifRam.ramarray);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);

        __osPackRequestData(CONT_CMD_RESET);

        ret = __osSiRawStartDma(OS_WRITE, __osContPifRam.ramarray);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);

        __osContLastCmd = CONT_CMD_RESET;
    }

    ret = __osSiRawStartDma(OS_READ, __osContPifRam.ramarray);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);

    __osContGetInitData(&pattern, data);
    __osSiRelAccess();

    return ret;
}

void __osPackResetData(void) {
    u8* ptr;
    int i;

    __osContPifRam.pifstatus = CONT_CMD_EXE;
    ptr = (u8*)__osContPifRam.ramarray;

    for (i = 0; i < MAXCONTROLLERS; i++) {
        *ptr++ = CONT_CMD_CHANNEL_RESET;
    }

    *ptr = CONT_CMD_END;
}
