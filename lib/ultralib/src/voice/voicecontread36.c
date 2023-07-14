#include "PR/os_internal.h"
#include "io/controller.h"
#include "PR/os_voice.h"
#include "voiceinternal.h"
#include "io/controller_voice.h"

#define READ36FORMAT(p) ((__OSVoiceRead36Format*)(ptr))

s32 __osVoiceContRead36(OSMesgQueue* mq, s32 channel, u16 address, u8* buffer) {
    s32 ret;
    u8 status;
    s32 i;
    u8* ptr;
    s32 retry = 2;

    __osSiGetAccess();

    do {

        ptr = (u8*)&__osPfsPifRam.ramarray;

        if ((__osContLastCmd != CONT_CMD_READ36_VOICE) || (__osPfsLastChannel != channel)) {
            __osContLastCmd = CONT_CMD_READ36_VOICE;
            __osPfsLastChannel = channel;

            for (i = 0; i < channel; i++) {
                *ptr++ = 0;
            }

            __osPfsPifRam.pifstatus = CONT_CMD_EXE;

            READ36FORMAT(ptr)->dummy = CONT_CMD_NOP;
            READ36FORMAT(ptr)->txsize = CONT_CMD_READ36_VOICE_TX;
            READ36FORMAT(ptr)->rxsize = CONT_CMD_READ36_VOICE_RX;
            READ36FORMAT(ptr)->cmd = CONT_CMD_READ36_VOICE;
            READ36FORMAT(ptr)->datacrc = 0xFF;

            ptr[sizeof(__OSVoiceRead36Format)] = CONT_CMD_END;
        } else {
            ptr = (u8*)&__osPfsPifRam + channel;
        }

        READ36FORMAT(ptr)->addrh = address >> 3;
        READ36FORMAT(ptr)->addrl = __osContAddressCrc(address) | (address << 5);

        __osSiRawStartDma(OS_WRITE, &__osPfsPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
        __osSiRawStartDma(OS_READ, &__osPfsPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);

        ret = CHNL_ERR(*READ36FORMAT(ptr));

        if (ret == 0) {
            if (__osVoiceContDataCrc(&READ36FORMAT(ptr)->data, ARRLEN(READ36FORMAT(ptr)->data)) != READ36FORMAT(ptr)->datacrc) {
                ret = __osVoiceGetStatus(mq, channel, &status);
                if (ret != 0) {
                    break;
                }

                ret = CONT_ERR_CONTRFAIL;
            } else {
                bcopy(&READ36FORMAT(ptr)->data, buffer, ARRLEN(READ36FORMAT(ptr)->data));
            }
        } else {
            ret = CONT_ERR_NO_CONTROLLER;
        }

    } while ((ret == CONT_ERR_CONTRFAIL) && (retry-- >= 0));

    __osSiRelAccess();

    return ret;
}
