/**
 * File: voicesetadconverter.c
 */

#include "PR/os_internal.h"
#include "PRinternal/controller.h"
#include "PR/os_voice.h"
#include "voiceinternal.h"
#include "PRinternal/controller_voice.h"
#include "PRinternal/siint.h"

#define SWRITEFORMAT(ptr) ((__OSVoiceSWriteFormat*)(ptr))

s32 __osVoiceSetADConverter(OSMesgQueue* mq, s32 channel, u8 data) {
    s32 ret = 0;
    int i;
    u8* ptr;
    u8 status;
    int retry = 2;

    __osSiGetAccess();

    do {

        ptr = (u8*)__osPfsPifRam.ramarray;

        if ((__osContLastCmd != CONT_CMD_SWRITE_VOICE) || (__osPfsLastChannel != channel)) {
            __osContLastCmd = CONT_CMD_SWRITE_VOICE;
            __osPfsLastChannel = channel;

            for (i = 0; i < channel; i++) { *ptr++ = CONT_CMD_REQUEST_STATUS; }

            __osPfsPifRam.pifstatus = CONT_CMD_EXE;

            SWRITEFORMAT(ptr)->txsize = CONT_CMD_SWRITE_VOICE_TX;
            SWRITEFORMAT(ptr)->rxsize = CONT_CMD_SWRITE_VOICE_RX;
            SWRITEFORMAT(ptr)->cmd = CONT_CMD_SWRITE_VOICE;
            SWRITEFORMAT(ptr)->datacrc = 0;

            ptr[sizeof(__OSVoiceSWriteFormat)] = CONT_CMD_END;
        } else {
            ptr += channel;
        }

        SWRITEFORMAT(ptr)->data = data;
        SWRITEFORMAT(ptr)->scrc = __osContAddressCrc(data << 3);

        ret = __osSiRawStartDma(OS_WRITE, &__osPfsPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
        ret = __osSiRawStartDma(OS_READ, &__osPfsPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);

        ret = CHNL_ERR(*SWRITEFORMAT(ptr));

        if (ret == 0) {
            if (SWRITEFORMAT(ptr)->datacrc & 1) {
                ret = __osVoiceGetStatus(mq, channel, &status);
                if (ret != 0) {
                    break;
                } else {
                    ret = CONT_ERR_CONTRFAIL;
                }
            }
        } else {
            ret = CONT_ERR_NO_CONTROLLER;
        }

    } while ((ret == CONT_ERR_CONTRFAIL) && (retry-- >= 0));

    __osSiRelAccess();

    return ret;
}
