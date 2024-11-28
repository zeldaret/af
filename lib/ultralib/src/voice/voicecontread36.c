/**
 * File: voicecontread36.c
 */

#include "PRinternal/macros.h"
#include "PR/os_internal.h"
#include "PRinternal/controller.h"
#include "PR/os_voice.h"
#include "voiceinternal.h"
#include "PRinternal/controller_voice.h"
#include "PRinternal/siint.h"

#define READ36FORMAT(ptr) ((__OSVoiceRead36Format*)(ptr))

s32 __osVoiceContRead36(OSMesgQueue* mq, int channel, u16 address, u8* buffer) {
    s32 ret = 0;
    u8 status;
    s32 i;
    u8* ptr;
    s32 retry = 2;

    __osSiGetAccess();

    do {

        ptr = (u8*)&__osPfsPifRam.ramarray;

        if ((__osContLastCmd != CONT_CMD_READ36_VOICE) || ((u32)__osPfsLastChannel != channel)) {
            __osContLastCmd = CONT_CMD_READ36_VOICE;
            __osPfsLastChannel = channel;

            for (i = 0; i < channel; i++) { *ptr++ = CONT_CMD_REQUEST_STATUS; }

            __osPfsPifRam.pifstatus = CONT_CMD_EXE;

            READ36FORMAT(ptr)->dummy = CONT_CMD_NOP;
            READ36FORMAT(ptr)->txsize = CONT_CMD_READ36_VOICE_TX;
            READ36FORMAT(ptr)->rxsize = CONT_CMD_READ36_VOICE_RX;
            READ36FORMAT(ptr)->cmd = CONT_CMD_READ36_VOICE;
            READ36FORMAT(ptr)->datacrc = 0xFF;

            ptr[sizeof(__OSVoiceRead36Format)] = CONT_CMD_END;
        } else {
            ptr += channel;
        }

        READ36FORMAT(ptr)->addrh = address >> 3;
        READ36FORMAT(ptr)->addrl = (address << 5) | __osContAddressCrc(address);

        ret = __osSiRawStartDma(OS_WRITE, &__osPfsPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
        ret = __osSiRawStartDma(OS_READ, &__osPfsPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);

        ret = CHNL_ERR(*READ36FORMAT(ptr));

        if (ret == 0) {
            if (__osVoiceContDataCrc(READ36FORMAT(ptr)->data, ARRLEN(READ36FORMAT(ptr)->data)) !=
                READ36FORMAT(ptr)->datacrc) {
                ret = __osVoiceGetStatus(mq, channel, &status);
                if (ret != 0) {
                    break;
                } else {
                    ret = CONT_ERR_CONTRFAIL;
                }
            } else {
                bcopy(READ36FORMAT(ptr)->data, buffer, ARRLEN(READ36FORMAT(ptr)->data));
            }
        } else {
            ret = CONT_ERR_NO_CONTROLLER;
        }

    } while ((ret == CONT_ERR_CONTRFAIL) && (retry-- >= 0));

    __osSiRelAccess();

    return ret;
}
