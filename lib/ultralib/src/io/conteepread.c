#include "macros.h"
#include "PR/rcp.h"
#include "controller.h"
#include "siint.h"

OSPifRam __osEepPifRam ALIGNED(16);
s32 __osEepromRead16K;
static void __osPackEepReadData(u8 address);

s32 osEepromRead(OSMesgQueue* mq, u8 address, u8* buffer) {
    s32 ret = 0;
    int i = 0;
    u16 type;
    u8* ptr;
    OSContStatus sdata;
    __OSContEepromFormat eepromformat;

    ptr = (u8*)&__osEepPifRam.ramarray;
    __osSiGetAccess();
    ret = __osEepStatus(mq, &sdata);
    type = sdata.type & (CONT_EEPROM | CONT_EEP16K);

    if (ret == 0) {
        switch (type) {
            case CONT_EEPROM:
                if (address >= EEPROM_MAXBLOCKS) {
                    ret = CONT_RANGE_ERROR;
                }
                break;
            case CONT_EEPROM | CONT_EEP16K:
                if (address >= EEP16K_MAXBLOCKS) {
                    // not technically possible
                    ret = CONT_RANGE_ERROR;
                } else {
                    __osEepromRead16K = 1;
                }
                break;
            default:
                ret = CONT_NO_RESPONSE_ERROR;
        }
    }

    if (ret != 0) {
        __osSiRelAccess();
        return ret;
    }

    while (sdata.status & CONT_EEPROM_BUSY) {
        __osEepStatus(mq, &sdata);
    }

    __osPackEepReadData(address);
    ret = __osSiRawStartDma(OS_WRITE, &__osEepPifRam); // send command to pif
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    ret = __osSiRawStartDma(OS_READ, &__osEepPifRam); // recv response
    __osContLastCmd = CONT_CMD_READ_EEPROM;
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);

    for (i = 0; i < MAXCONTROLLERS; i++) {
        // skip the first 4 bytes
        ptr++;
    }

    eepromformat = *(__OSContEepromFormat*)ptr;
    ret = CHNL_ERR(eepromformat);

    if (ret == 0) {
        for (i = 0; i < ARRLEN(eepromformat.data); i++) {
            *buffer++ = eepromformat.data[i];
        }
    }
    __osSiRelAccess();
    return ret;
}

static void __osPackEepReadData(u8 address) {
    u8* ptr = (u8*)&__osEepPifRam.ramarray;
    __OSContEepromFormat eepromformat;
    int i;

    __osEepPifRam.pifstatus = CONT_CMD_EXE;

    eepromformat.txsize = CONT_CMD_READ_EEPROM_TX;
    eepromformat.rxsize = CONT_CMD_READ_EEPROM_RX;
    eepromformat.cmd = CONT_CMD_READ_EEPROM;
    eepromformat.address = address;

    for (i = 0; i < MAXCONTROLLERS; i++) {
        *ptr++ = 0;
    }

    *(__OSContEepromFormat*)(ptr) = eepromformat;
    ptr += sizeof(__OSContEepromFormat);
    ptr[0] = CONT_CMD_END;
}
