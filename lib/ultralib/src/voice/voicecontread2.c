/**
 * File: voicecontread2.c
 */

#include "PRinternal/macros.h"
#include "PR/os_internal.h"
#include "PRinternal/controller.h"
#include "PR/os_voice.h"
#include "voiceinternal.h"
#include "PRinternal/controller_voice.h"
#include "PRinternal/siint.h"

#define READ2FORMAT(ptr) ((__OSVoiceRead2Format*)(ptr))

s32 __osVoiceContRead2(OSMesgQueue* mq, int channel, u16 address, u8* buffer) {
    s32 ret = 0;
    u8 status;
    int i;
    u8* ptr;
    int retry = 2;

    __osSiGetAccess();

    do {

        ptr = (u8*)&__osPfsPifRam.ramarray;

        if ((__osContLastCmd != CONT_CMD_READ2_VOICE) || ((u32)__osPfsLastChannel != channel)) {
            __osContLastCmd = CONT_CMD_READ2_VOICE;
            __osPfsLastChannel = channel;

            for (i = 0; i < channel; i++) { *ptr++ = CONT_CMD_REQUEST_STATUS; }

            __osPfsPifRam.pifstatus = CONT_CMD_EXE;

            READ2FORMAT(ptr)->dummy = CONT_CMD_NOP;
            READ2FORMAT(ptr)->txsize = CONT_CMD_READ2_VOICE_TX;
            READ2FORMAT(ptr)->rxsize = CONT_CMD_READ2_VOICE_RX;
            READ2FORMAT(ptr)->cmd = CONT_CMD_READ2_VOICE;
            READ2FORMAT(ptr)->datacrc = 0xFF;

            ptr[sizeof(__OSVoiceRead2Format)] = CONT_CMD_END;
        } else {
            ptr += channel;
        }

        READ2FORMAT(ptr)->addrh = address >> 3;
        READ2FORMAT(ptr)->addrl = (address << 5) | __osContAddressCrc(address);

        ret = __osSiRawStartDma(OS_WRITE, &__osPfsPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
        ret = __osSiRawStartDma(OS_READ, &__osPfsPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);

        ret = CHNL_ERR(*READ2FORMAT(ptr));

        if (ret == 0) {
            if (__osVoiceContDataCrc(READ2FORMAT(ptr)->data, ARRLEN(READ2FORMAT(ptr)->data)) !=
                READ2FORMAT(ptr)->datacrc) {
                ret = __osVoiceGetStatus(mq, channel, &status);
                if (ret != 0) {
                    break;
                } else {
                    ret = CONT_ERR_CONTRFAIL;
                }
            } else {
                bcopy(READ2FORMAT(ptr)->data, buffer, ARRLEN(READ2FORMAT(ptr)->data));
            }
        } else {
            ret = CONT_ERR_NO_CONTROLLER;
        }

    } while ((ret == CONT_ERR_CONTRFAIL) && (retry-- >= 0));

    __osSiRelAccess();

    return ret;
}
