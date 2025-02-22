/**
 * File: voicecontwrite4.c
 */

#include "PRinternal/macros.h"
#include "PR/os_internal.h"
#include "PRinternal/controller.h"
#include "PR/os_voice.h"
#include "voiceinternal.h"
#include "PRinternal/controller_voice.h"
#include "PRinternal/siint.h"

#define WRITE4FORMAT(ptr) ((__OSVoiceWrite4Format*)(ptr))

s32 __osVoiceContWrite4(OSMesgQueue* mq, int channel, u16 address, u8* buffer) {
    s32 ret = 0;
    u8 status;
    int i;
    u8* ptr;
    s32 retry = 2;
    u8 crc;

    __osSiGetAccess();

    do {

        ptr = (u8*)&__osPfsPifRam;

        if ((__osContLastCmd != CONT_CMD_WRITE4_VOICE) || ((u32)__osPfsLastChannel != channel)) {
            __osContLastCmd = CONT_CMD_WRITE4_VOICE;
            __osPfsLastChannel = channel;

            for (i = 0; i < channel; i++) { *ptr++ = CONT_CMD_REQUEST_STATUS; }

            __osPfsPifRam.pifstatus = CONT_CMD_EXE;

            WRITE4FORMAT(ptr)->dummy = CONT_CMD_NOP;
            WRITE4FORMAT(ptr)->txsize = CONT_CMD_WRITE4_VOICE_TX;
            WRITE4FORMAT(ptr)->rxsize = CONT_CMD_WRITE4_VOICE_RX;
            WRITE4FORMAT(ptr)->cmd = CONT_CMD_WRITE4_VOICE;
            WRITE4FORMAT(ptr)->datacrc = 0xFF;

            ptr[sizeof(__OSVoiceWrite4Format)] = CONT_CMD_END;
        } else {
            ptr += channel;
        }

        WRITE4FORMAT(ptr)->addrh = address >> 3;
        WRITE4FORMAT(ptr)->addrl = (address << 5) | __osContAddressCrc(address);

        bcopy(buffer, WRITE4FORMAT(ptr)->data, ARRLEN(WRITE4FORMAT(ptr)->data));

        ret = __osSiRawStartDma(OS_WRITE, &__osPfsPifRam);
        crc = __osVoiceContDataCrc(buffer, ARRLEN(WRITE4FORMAT(ptr)->data));
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
        ret = __osSiRawStartDma(OS_READ, &__osPfsPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);

        ret = CHNL_ERR(*WRITE4FORMAT(ptr));

        if (ret == 0) {
            if (crc != WRITE4FORMAT(ptr)->datacrc) {
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
