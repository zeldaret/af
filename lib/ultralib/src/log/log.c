#include "stdarg.h"
#include "PR/rdb.h"
#include "PR/os.h"
#include "PR/os_internal.h"
#include "PR/ultraerror.h"
#include "PR/ultralog.h"
#include "PRinternal/macros.h"

#ifndef _FINALROM

static u32 __osLogOKtoWrite = TRUE;
static u32 __osLogInitialized = FALSE;

static OSMesgQueue __osLogDoneMsgQ ALIGNED(0x8);
static OSMesg __osLogMsgBuf;

void __osLogWrite(OSLog* log, s16 code, s16 numArgs, va_list argPtr);

void osCreateLog(OSLog* log, u32* base, s32 byteLen) {
    log->magic = OS_LOG_MAGIC;
    log->base = base;
    log->len = byteLen;
    log->startCount = osGetCount();
    log->writeOffset = 0;
}

void osLogEvent(OSLog* log, s16 code, s16 numArgs, ...) {
    va_list argPtr;

    if (numArgs > 16) {
        return;
    }

    va_start(argPtr, numArgs);
    __osLogWrite(log, code, numArgs, argPtr);
    va_end(argPtr);
}

void osFlushLog(OSLog* log) {
    s32 mask;
    u32 sent;
    u32 count;
    u32 subcount;
    u8* base;
    u8 dCount[3];

    if (!__osLogInitialized) {
        osCreateMesgQueue(&__osLogDoneMsgQ, &__osLogMsgBuf, 1);
        osSetEventMesg(OS_EVENT_RDB_LOG_DONE, &__osLogDoneMsgQ, 0);
        __osLogInitialized = 1;
    }

    mask = __osDisableInt();
    __osLogOKtoWrite = 0;
    base = log->base;
    count = log->writeOffset * 4;
    __osRestoreInt(mask);

    while (count != 0) {
        subcount = (count < 0x8000) ? count : 0x8000;
        dCount[0] = (subcount & 0xFF0000) >> 0x10;
        dCount[1] = (subcount & 0xFF00) >> 8;
        dCount[2] = subcount & 0xFF;

        sent = 0;
        while (sent < 3) {
            sent += __osRdbSend(dCount + sent, 3 - sent, RDB_TYPE_GtoH_LOG_CT);
        }

        sent = 0;
        while (sent < subcount) {
            sent += __osRdbSend(base + sent, subcount - sent, RDB_TYPE_GtoH_LOG);
        }

        count -= subcount;
        base += subcount;
        osRecvMesg(&__osLogDoneMsgQ, NULL, OS_MESG_BLOCK);
    }
    mask = __osDisableInt();
    log->writeOffset = 0;
    __osLogOKtoWrite = 1;
    __osRestoreInt(mask);
}

void __osLogWrite(OSLog* log, s16 code, s16 numArgs, va_list argPtr) {
    int i;
    u32 saveEnable;
    u32 buf[19];
    u32* bufp;
    OSLogItem* hdr;
    s32* args;
    s32* dest;
    int numLongs;

    bufp = buf;
    hdr = buf;
    args = buf + 3;
    numLongs = numArgs + 3;
    saveEnable = __osDisableInt();

    hdr->magic = log->magic;
    hdr->timeStamp = osGetCount() - log->startCount;
    hdr->argCount = numArgs;
    hdr->eventID = code;

    for (i = 0; i < numArgs; i++) {
        *args++ = va_arg(argPtr, int);
    }

    if (__osLogOKtoWrite) {
        if ((log->writeOffset + numLongs) < (log->len >> 2)) {
            dest = log->base + log->writeOffset;
            for (i = 0; i < numLongs; i++) {
                *dest++ = *bufp++;
            }
            log->writeOffset += numLongs;
        } else {
            __osLogOKtoWrite = FALSE;
        }
    }
    __osRestoreInt(saveEnable);
}

#endif
