#include "PR/os_internal.h"
#include "io/controller.h"
#include "PR/os_voice.h"
#include "voiceinternal.h"
#include "io/siint.h"

s32 __osVoiceGetStatus(OSMesgQueue* mq, s32 port, u8* status) {
    __OSContRequesFormatShort header;
    s32 ret = 0;
    s32 i;
    u8* ptr = (u8*)&__osContPifRam.ramarray;
    s32 retry = 2;

    __osSiGetAccess();

    do {
        if (ret != CONT_ERR_CONTRFAIL) {
            __osContPifRam.pifstatus = CONT_CMD_EXE;

            for (i = 0; i < port; i++, *ptr++ = 0) {
                ;
            }

            *ptr++ = CONT_CMD_REQUEST_STATUS_TX;
            *ptr++ = CONT_CMD_REQUEST_STATUS_RX;
            *ptr = CONT_CMD_REQUEST_STATUS;
            ptr += 4;
            *ptr = CONT_CMD_END;

            __osContLastCmd = CONT_CMD_END;
            ret = __osSiRawStartDma(OS_WRITE, &__osContPifRam);
            osRecvMesg(mq, NULL, OS_MESG_BLOCK);
        }
        ret = __osSiRawStartDma(OS_READ, &__osContPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);

        ptr = (u8*)&__osContPifRam.ramarray + port;

        header = *((__OSContRequesFormatShort*)ptr);

        ret = (u8)CHNL_ERR(header);
        *status = header.status;

        if (ret == 0) {
            if (header.typeh == 0 && header.typel == 1) {
                if (header.status & 4) {
                    ret = CONT_ERR_CONTRFAIL;
                }
            } else {
                ret = CONT_ERR_DEVICE;
            }
        } else if (ret & CONT_NO_RESPONSE_ERROR) {
            ret = CONT_ERR_NO_CONTROLLER;
        } else {
            ret = CONT_ERR_CONTRFAIL;
        }
    } while ((ret == CONT_ERR_CONTRFAIL) && (retry-- >= 0));

    __osSiRelAccess();

    return ret;
}
