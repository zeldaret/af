#ifndef _FINALROM

#include "PR/os_internal.h"
#include "PR/rdb.h"
#include "PR/ultraerror.h"

#include "PRinternal/macros.h"

static int writeHostInitialized = FALSE;
static OSMesgQueue writeHostMesgQueue ALIGNED(0x8);
static OSMesg writeHostMesgBuf[1];

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

void osWriteHost(void* dramAddr, u32 nbytes) {
    u8* tPtr = dramAddr;
    u32 sent;
    u8 dCount[3];
    u32 count;

#ifndef NDEBUG
    if (nbytes == 0) {
        __osError(ERR_OSWRITEHOST_SIZE, 1, nbytes);
        return;
    }
#endif

    if (writeHostInitialized == FALSE) {
        osCreateMesgQueue(&writeHostMesgQueue, writeHostMesgBuf, ARRLEN(writeHostMesgBuf));
        osSetEventMesg(OS_EVENT_RDB_DATA_DONE, &writeHostMesgQueue, NULL);
        writeHostInitialized = TRUE;
    }

    while (nbytes != 0) {
        count = MIN(nbytes, 0x8000);

        dCount[0] = (count & 0xFF0000) >> 0x10;
        dCount[1] = (count & 0xFF00) >> 8;
        dCount[2] = count & 0xFF;

        sent = 0;
        while (sent < ARRLEN(dCount)) {
            sent += __osRdbSend(dCount + sent, ARRLEN(dCount) - sent, RDB_TYPE_GtoH_DATA_CT);
        }

        sent = 0;
        while (sent < count) {
            sent += __osRdbSend(tPtr + sent, count - sent, RDB_TYPE_GtoH_DATA);
        }

        nbytes -= count;
        tPtr += count;
        osRecvMesg(&writeHostMesgQueue, NULL, OS_MESG_BLOCK);
    }
}

#endif
