#include "PR/os_internal.h"
#include "PR/rcp.h"
#include "controller.h"
#include "siint.h"

s32 __osPfsLastChannel = -1;

#define READFORMAT(ptr) ((__OSContRamReadFormat*)(ptr))

s32 __osContRamRead(OSMesgQueue* mq, int channel, u16 address, u8* buffer) {
    s32 ret;
    s32 i;
    u8* ptr;
    s32 retry = 2;

    __osSiGetAccess();

    do {
        ptr = (u8*)&__osPfsPifRam;

        if (__osContLastCmd != CONT_CMD_READ_PAK || __osPfsLastChannel != channel) {
            __osContLastCmd = CONT_CMD_READ_PAK;
            __osPfsLastChannel = channel;

            for (i = 0; i < channel; i++) {
                *ptr++ = CONT_CMD_REQUEST_STATUS;
            }

            __osPfsPifRam.pifstatus = CONT_CMD_EXE;

            READFORMAT(ptr)->dummy = CONT_CMD_NOP;
            READFORMAT(ptr)->txsize = CONT_CMD_READ_PAK_TX;
            READFORMAT(ptr)->rxsize = CONT_CMD_READ_PAK_RX;
            READFORMAT(ptr)->cmd = CONT_CMD_READ_PAK;
            READFORMAT(ptr)->datacrc = 0xFF;

            ptr[sizeof(__OSContRamReadFormat)] = CONT_CMD_END;
        } else {
            ptr += channel;
        }

        READFORMAT(ptr)->addrh = address >> 3;
        READFORMAT(ptr)->addrl = (u8)(__osContAddressCrc(address) | (address << 5));

        __osSiRawStartDma(OS_WRITE, &__osPfsPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);

        __osSiRawStartDma(OS_READ, &__osPfsPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);

        ret = CHNL_ERR(*READFORMAT(ptr));

        if (!ret) {
            if (__osContDataCrc(&READFORMAT(ptr)->data) != READFORMAT(ptr)->datacrc) {
                ret = __osPfsGetStatus(mq, channel);

                if (ret) {
                    break;
                }

                ret = PFS_ERR_CONTRFAIL;
            } else {
                bcopy(&READFORMAT(ptr)->data, buffer, BLOCKSIZE);
            }
        } else {
            ret = PFS_ERR_NOPACK;
        }
        if (ret != PFS_ERR_CONTRFAIL) {
            break;
        }
    } while (0 <= retry--);
    __osSiRelAccess();

    return ret;
}
