#include "PR/rdb.h"
#include "PR/ultratypes.h"
#include "PR/os.h"
#include "PR/ultraerror.h"
#include "PR/ultralog.h"
#include "PR/sptask.h"
#include "PRinternal/osint.h"
#include "PRinternal/macros.h"
#include "osint_debug.h"

#ifndef _FINALROM

OSTimer __osProfTimer;
OSMesg __osProfTimerMsg;

OSMesgQueue __osProfFlushMQ ALIGNED(0x8);
OSMesg __osProfFlushMesg;

OSMesgQueue __osProfAckMQ ALIGNED(0x8);
OSMesg __osProfAckMesg;

u32 __osProfTimerPeriod;

u32 __osProfNumSections;

static u32 __osProfileActive = FALSE;
static u32 __osProfileIOActive = FALSE;

STACK(__osProfileIOStack, 0x960) ALIGNED(0x10);

static OSThread __osProfileIOThread;

void osProfSendWord(u32 word);

void __osProfileIO(void* arg) {
    s32 totalBytes;
    u32 bytesThisBlock;
    u32 ct;
    u8* sendPtr;
    OSProf* t;

    while (TRUE) {
        osRecvMesg(&__osProfFlushMQ, NULL, OS_MESG_BLOCK);
        osProfSendWord(__osProfNumSections);
        osProfSendWord(__osProfTimerPeriod);
        osProfSendWord(__osProfileOverflowBin);

        for (t = __osProfileList; t < __osProfileListEnd; t++) {
            osProfSendWord(t->text_start);
            osProfSendWord(t->histo_size);
            osRecvMesg(&__osProfAckMQ, NULL, OS_MESG_BLOCK);

            totalBytes = t->histo_size * 2;
            sendPtr = t->histo_base;
            while (totalBytes > 0) {
                bytesThisBlock = (totalBytes < 0x800U) ? totalBytes : 0x800U;

                ct = 0;
                while (ct < bytesThisBlock) {
                    ct += __osRdbSend(sendPtr + ct, bytesThisBlock - ct, RDB_TYPE_GtoH_PROF_DATA);
                }

                sendPtr += bytesThisBlock;
                totalBytes -= bytesThisBlock;
                osRecvMesg(&__osProfAckMQ, NULL, OS_MESG_BLOCK);
            }
        }
    }
}

void osProfSendWord(u32 word) {
    u32 ct = 0;
    u8* sendPtr = &word;

    while (ct < sizeof(word)) {
        ct += __osRdbSend(sendPtr + ct, sizeof(word) - ct, RDB_TYPE_GtoH_PROF_DATA);
    }
}

void osProfileFlush(void) {
    osSendMesg(&__osProfFlushMQ, NULL, OS_MESG_BLOCK);
}

void osProfileInit(OSProf* profp, u32 profcnt) {
    u32 i;
    OSProf* t;

#if !defined(NDEBUG) && BUILD_VERSION >= VERSION_K
    if (__osProfileActive) {
        __osError(ERR_OSPROFILEINIT_STR, 0);
        return;
    }

    if (profcnt == 0) {
        __osError(ERR_OSPROFILEINIT_CNT, 1, profcnt);
        return;
    }
#endif

    for (t = profp; t < profp + profcnt; t++) {
#ifndef NDEBUG
        if ((u32)t->histo_base & 1) {
            __osError(ERR_OSPROFILEINIT_ALN, 1, t->histo_base);
            return;
        }

        if (t->text_start >= t->text_end) {
            __osError(ERR_OSPROFILEINIT_ORD, 2, t->text_start, t->text_end);
            return;
        }

        if (((u32)(t->text_end - t->text_start) / 4) > t->histo_size) {
            __osError(ERR_OSPROFILEINIT_SIZ, 1, t->histo_size);
            return;
        }
#endif

        for (i = 0; i < t->histo_size; i++) {
            t->histo_base[i] = 0;
        }
    }

    __osProfileActive = FALSE;
    __osProfileOverflowBin = 0;
    __osProfileList = profp;
    __osProfileListEnd = profp + profcnt;
    __osProfNumSections = profcnt;
    if (!__osProfileIOActive) {
        osCreateMesgQueue(&__osProfFlushMQ, &__osProfFlushMesg, 1);
        osSetEventMesg(OS_EVENT_RDB_FLUSH_PROF, &__osProfFlushMQ, 0);
        osCreateMesgQueue(&__osProfAckMQ, &__osProfAckMesg, 1);
        osSetEventMesg(OS_EVENT_RDB_ACK_PROF, &__osProfAckMQ, 0);
        osCreateThread(&__osProfileIOThread, 0, __osProfileIO, NULL, STACK_START(__osProfileIOStack), 0x81);
        osStartThread(&__osProfileIOThread);
        __osProfileIOActive = TRUE;
    }
}

void osProfileStart(u32 microseconds) {
#ifndef NDEBUG
    if (microseconds < 50) {
        __osError(ERR_OSPROFILESTART_TIME, 1, microseconds);
        return;
    }

    if (__osProfileActive) {
        __osError(ERR_OSPROFILESTART_FLAG, 0);
        return;
    }
#endif

    osCreateMesgQueue(&__osProfTimerQ, &__osProfTimerMsg, 1);
    osSetTimer(&__osProfTimer, 0, OS_USEC_TO_CYCLES(microseconds), &__osProfTimerQ, NULL);
    __osProfTimerPeriod = microseconds;
    __osProfileActive = TRUE;
}

void osProfileStop(void) {
#ifndef NDEBUG
    if (!__osProfileActive) {
        __osError(ERR_OSPROFILESTOP_FLAG, 0);
        return;
    }
#endif

    if (osStopTimer(&__osProfTimer) < 0) {
#ifndef NDEBUG
        __osError(ERR_OSPROFILESTOP_TIMER, 0);
        return;
#endif
    }

    __osProfileActive = FALSE;
}

#endif
