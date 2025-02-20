#include "PR/os_internal.h"
#include "PRinternal/controller.h"
#include "PRinternal/siint.h"

s32 __osContChannelReset(OSMesgQueue* mq, int channel) {
    s32 i;
    s32 ret;
    u8* ptr = (u8*)&__osPfsPifRam;

    __osSiGetAccess();
    __osPfsPifRam.pifstatus = CONT_CMD_EXE;

    for (i = 0; i < channel; i++) {
        *ptr++ = CONT_CMD_REQUEST_STATUS;
    }

    *ptr++ = CONT_CMD_CHANNEL_RESET;
    *ptr = CONT_CMD_END;

    ret = __osSiRawStartDma(OS_WRITE, &__osPfsPifRam);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);

    ret = __osSiRawStartDma(OS_READ, &__osPfsPifRam);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);

    __osSiRelAccess();
    return ret;
}
