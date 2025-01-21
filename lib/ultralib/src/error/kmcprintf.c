// This file was added in 2.0J and removed in 2.0K
#include "stdarg.h"
#include "PR/os.h"
#include "PR/rcp.h"
#include "PR/rdb.h"
#include "ultraerror.h"
#include "../libc/xstdio.h"

extern u32 __kmc_pt_mode;

static void* proutSyncPrintf(void* str, const char* buf, size_t n) {
    size_t sent = 0;

    while (sent < n) {
        sent += __osRdbSend(buf + sent, n - sent, RDB_TYPE_GtoH_PRINT);
    }
    return 1;
}

static volatile unsigned int* stat = (unsigned*)0xbff08004;
static volatile unsigned int* wport = (unsigned*)0xbff08000;
static volatile unsigned int* piok = (unsigned*)PHYS_TO_K1(PI_STATUS_REG);

static void rmonPutchar(char c) {
    while (*piok & (PI_STATUS_DMA_BUSY | PI_STATUS_IO_BUSY)) {
    }

    while (!(*stat & 4)) {
    }
    
    *wport = c;
}

static void* kmc_proutSyncPrintf(void* str, const char* buf, int n) {
    int i;
    char c;
    char* p;
    char* q;
    char xbuf[128];
    static int column = 0;

    p = &xbuf;

    for (i = 0; i < n; i++) {
        c = *buf++;

        switch (c) {
            case '\n':
                *p++ = '\n';
                column = 0;
                break;
            case '\t':
                do {
                    *p++ = ' ';
                } while (++column % 8);
                break;
            default:
                column++;
                *p++ = c;
                break;
        }

        if (c == '\n' || (p - xbuf) > 100) {
            rmonPutchar((p - xbuf) - 1);

            q = xbuf;
            while (q != p) {
                rmonPutchar(*q++);
            }
            p = xbuf;
        }
    }
    if (p != xbuf) {
        rmonPutchar((p - xbuf) - 1);

        q = xbuf;
        while (q != p) {
            rmonPutchar(*q++);
        }
    }
    return (void*)1;
}

char NULSTR[] = "";

const char* __os_error_message[] = {
    NULSTR,
    "osCreateThread: stack pointer not aligned to 8 bytes (0x%x)",
    "osCreateThread: priority not in range [0-255] (%d)",
    "osStartThread: thread has bad state (running/runnable/other)",
    "osSetThreadPri: priority not in range [0-255] (%d)",
    "osCreateMesgQueue: message count not > 0 (%d)",
    "osSendMesg: flag not OS_MESG_NOBLOCK or OS_MESG_BLOCK (%d)",
    "osJamMesg: flag not OS_MESG_NOBLOCK or OS_MESG_BLOCK (%d)",
    "osRecvMesg: flag not OS_MESG_NOBLOCK or OS_MESG_BLOCK (%d)",
    "osSetEventMesg: unknown event type (%d)",
    "osMapTLB: index not in range [0-30] (%d)",
    "osMapTLB: asid argument not -1 or in range [0-255] (%d)",
    "osUnmapTLB: index not in range [0-30] (%d)",
    "osSetTLBASID: asid not in range [0-255] (%d)",
    "osAiSetFrequency: freq not in range [%d-%d] (%d)",
    "osAiSetNextBuffer: address not aligned to 8 bytes (0x%x)",
    "osAiSetNextBuffer: size not aligned to 8 bytes (0x%x)",
    "osDpSetNextBuffer: address not aligned to 8 bytes (0x%x)",
    "osDpSetNextBuffer: size not aligned to 8 bytes (0x%x)",
    "osPiRawReadIo: address not aligned to 4 bytes (0x%x)",
    "osPiRawWriteIo: address not aligned to 4 bytes (0x%x)",
    "osPiRawStartDma: direction not OS_READ or OS_WRITE (%d)",
    "osPiRawStartDma: device address not aligned to 2 bytes (0x%x)",
    "osPiRawStartDma: DRAM address not aligned to 8 bytes (0x%x)",
    "osPiRawStartDma: size not aligned to 2 bytes (%d)",
    "osPiRawStartDma: size not in range [0,16777216] (%d)",
    "osPiReadIo: address not aligned to 4 bytes (0x%x)",
    "osPiWriteIo: address not aligned to 4 bytes (0x%x)",
    "osPiStartDma: PI Manager not yet begun by osCreatePiManager",
    "osPiStartDma: priority not OS_MESG_PRI_[NORMAL|HIGH] (%d)",
    "osPiStartDma: direction not OS_READ or OS_WRITE (%d)",
    "osPiStartDma: device address not aligned to 2 bytes (0x%x)",
    "osPiStartDma: DRAM address not aligned to 8 bytes (0x%x)",
    "osPiStartDma: size not aligned to 2 bytes (%d)",
    "osPiStartDma: size not in range [0,16777216] (%d)",
    "osCreatePiManager: priority not in range [0-255] (%d)",
    "osViGetCurrentMode: VI Manager not yet begun",
    "osViGetCurrentFramebuffer: VI Manager not yet begun",
    "osViGetNextFramebuffer: VI Manager not yet begun",
    "osViSetXScale: value not in range [0.25,1.0] (%f)",
    "osViSetXScale: VI Manager not yet begun by osCreateViManager",
    "osViSetYScale: value not in range [0.05,1.0] (%f)",
    "osViSetYScale: VI Manager not yet begun by osCreateViManager",
    "osViSetSpecialFeatures: not a known feature value (%d)",
    "osViSetSpecialFeatures: VI Manager not yet begun",
    "osViSetMode: VI Manager not yet begun by osCreateViManager",
    "osViSetEvent: VI Manager not yet begun by osCreateViManager",
    "osViSwapBuffer: frame buffer not aligned to 64 bytes (0x%x)",
    "osViSwapBuffer: VI Manager not yet begun",
    "osCreateViManager: priority not in range [0-255] (%d)",
    "osCreateRegion: not a known alignment (%d)",
    "osCreateRegion: length (%d) too small for buffer size (%d)",
    "osMalloc: invalid or corrupt region (0x%x)",
    "osFree: invalid or corrupt region (0x%x)",
    "osFree: invalid address (0x%x) or\n                           corrupt region (0x%x)",
    "osGetRegionBufCount: invalid or corrupt region (0x%x)",
    "osGetRegionBufSize: invalid or corrupt region (0x%x)",
    "osSpTaskLoad: dram_stack not aligned to 16 bytes (0x%x)",
    "osSpTaskLoad: output_buff not aligned to 16 bytes (0x%x)",
    "osSpTaskLoad: output_buff_size not aligned to 16 bytes (0x%x)",
    "osSpTaskLoad: yield_data_ptr not aligned to 16 bytes (0x%x)",
    "osProfileInit: profile counter is running, call osProfileStop before init",
    "osProfileInit: profcnt is %d",
    "osProfileInit: histo_base pointer must be 32-bit aligned (%x)",
    "osProfileInit: text_start (%x) >= text_end (%x)",
    "osProfileInit: histo_size is an illegal size (%d)",
    "osProfileStart: microseconds is < PROF_MIN_INTERVAL (%d)",
    "osProfileStart: profiling has already been started",
    "osProfileStop: profiling has already been stopped",
    "osProfileStop: no profile timer to stop",
    "osReadHost: address not aligned to 8 bytes (0x%x)",
    "osReadHost: size either 0 or not aligned to 4 bytes (0x%x)",
    "osWriteHost: address not aligned to 8 bytes (0x%x)",
    "osWriteHost: size either 0 or not aligned to 4 bytes (0x%x)",
    "osGetTime: VI manager not yet begun by osCreateViManager",
    "osSetTime: VI manager not yet begun by osCreateViManager",
    "osSetTimer: VI manager not yet begun by osCreateViManager",
    "osStopTimer: VI manager not yet begun by osCreateViManager",
    NULSTR,
    NULSTR,
    NULSTR,
    NULSTR,
    NULSTR,
    NULSTR,
    NULSTR,
    NULSTR,
    NULSTR,
    NULSTR,
    NULSTR,
    NULSTR,
    NULSTR,
    NULSTR,
    NULSTR,
    NULSTR,
    NULSTR,
    NULSTR,
    NULSTR,
    NULSTR,
    NULSTR,
    NULSTR,
    "_handleMIDIMsg: no sound mapped",
    "_handleMIDIMsg: no free voices",
    "_handleMIDIMsg: couldn't map voice",
    "_handleMIDIMsg: note off - couldn't find voice",
    "_handleMIDIMsg: poly pressure - couldn't find voice",
    "_handleEvent: no free voices",
    "Synthesizer: no free updates",
    "alSndPDeallocate: attempt to deallocate a sound which is playing",
    "alSndpDelete: attempt to delete player with playing sounds",
    "alSndpPlay: attempt to play a sound which is playing",
    "alSndpSetSound: sound id (%d) out of range (0 - %d)",
    "alSndpSetPriority: sound id (%d) out of range (0 - %d)",
    "alSndpSet Parameter: target (%d) out of range (0 - %d)",
    "alBnkfNew: bank file out of date",
    "alSeqNew: 0x%x is not a midi file",
    "alSeqNew: 0x%x is not a type 0 midi file",
    "alSeqNew: 0x%x has more than 1 track",
    "alSeqNew: SMPTE delta times not supported",
    "alSeqNew: Error parsing file 0x%x (no track header)",
    "alSeqNextEvent: Unsupported system exclusive",
    "alSeqNextEvent: Unsupported midi meta event 0x%x",
    "_handleMIDIMsg: Invalid program change to %d, max instruments %d",
    "_handleMIDIMsg: Unknown midi message 0x%x",
    "_unmapVoice: Couldn't unmap voice 0x%x",
    "alEvtqPostEvent: Out of free events",
    "alHeapAlloc: Can't allocate %d bytes",
    "alHeapCheck: Heap corrupt",
    "alHeapCheck: Heap corrupt - first block is bad",
    "alCSeqGetTrackEvent: Running status of zero on track %d",
    "alCSeqGetTrackEvent: Note on velocity of zero on track %d",
    "alCSPVoiceHandler: Stopping sequence but voice not free chan %d, key %d",
    "alSeqNextEvent: Read past end of sequence",
    "osAiSetNextBuffer: DMA buffer location may cause audio clicks (0x%x)",
    "_loadOutputBuffer: Modulated delay greater than total delay by %d samples",
    "osViExtendVStart: VI Manager not yet begun by osCreateViManager",
    "osViExtendVStart: value not in range [0-48] %d",
    NULSTR,
};

static void kmcErrorHandler(s16 code, s16 numArgs, ...);
OSErrorHandler __kmcErrorHandler = kmcErrorHandler;

static void kmcErrorHandler(s16 code, s16 numArgs, ...) {
    int ans;
    va_list ap;
    char* fmt;

    fmt = __os_error_message[code];
    va_start(ap, numArgs);

    if (__kmc_pt_mode) {
        ans = _Printf(kmc_proutSyncPrintf, NULL, fmt, ap);
    } else {
        ans = _Printf(proutSyncPrintf, NULL, fmt, ap);
    }

    osSyncPrintf("\n");

    va_end(ap);
}
