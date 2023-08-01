#include "PR/os_internal.h"
#include "io/controller.h"
#include "PR/os_voice.h"
#include "voiceinternal.h"
#include "io/controller_voice.h"
#include "io/siint.h"

#define WRITE20FORMAT(p) ((__OSVoiceWrite20Format*)(ptr))

s32 __osVoiceContWrite20(OSMesgQueue* mq, int channel, u16 address, u8* buffer) {
    s32 ret = 0;
    u8 status;
    int i;
    u8* ptr;
    int retry;
    u8 crc;

    retry = 2;

    __osSiGetAccess();

    do {

        ptr = (u8*)&__osPfsPifRam;

        if ((__osContLastCmd != CONT_CMD_WRITE20_VOICE) || ((u32)__osPfsLastChannel != channel)) {
            __osContLastCmd = CONT_CMD_WRITE20_VOICE;
            __osPfsLastChannel = channel;

            for (i = 0; i < channel; i++) { *ptr++ = 0; }

            __osPfsPifRam.pifstatus = CONT_CMD_EXE;

            WRITE20FORMAT(ptr)->dummy = CONT_CMD_NOP;
            WRITE20FORMAT(ptr)->txsize = CONT_CMD_WRITE20_VOICE_TX;
            WRITE20FORMAT(ptr)->rxsize = CONT_CMD_WRITE20_VOICE_RX;
            WRITE20FORMAT(ptr)->cmd = CONT_CMD_WRITE20_VOICE;
            WRITE20FORMAT(ptr)->datacrc = 0xFF;

            ptr[sizeof(__OSVoiceWrite20Format)] = CONT_CMD_END;
        } else {
            ptr += channel;
        }

        WRITE20FORMAT(ptr)->addrh = address >> 3;
        WRITE20FORMAT(ptr)->addrl = (address << 5) | __osContAddressCrc(address);

        bcopy(buffer, &WRITE20FORMAT(ptr)->data, 20);

        ret = __osSiRawStartDma(OS_WRITE, &__osPfsPifRam);
        crc = __osVoiceContDataCrc(buffer, 20);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
        ret = __osSiRawStartDma(OS_READ, &__osPfsPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);

        ret = (WRITE20FORMAT(ptr)->rxsize & 0xC0) >> 4;

        if (ret == 0) {
            if (crc != WRITE20FORMAT(ptr)->datacrc) {
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
