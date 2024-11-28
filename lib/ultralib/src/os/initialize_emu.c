#ifndef _FINALROM

#include "PR/os_internal.h"
#include "PR/rdb.h"
#include "PRinternal/osint.h"

typedef struct {
    /* 0x0 */ unsigned int inst1;
    /* 0x4 */ unsigned int inst2;
    /* 0x8 */ unsigned int inst3;
    /* 0xC */ unsigned int inst4;
} __osExceptionVector;

static void* proutSyncPrintf(void* str, const char* buf, size_t n) {
    size_t sent = 0;

    while (sent < n) {
        sent += __osRdbSend(buf + sent, n - sent, RDB_TYPE_GtoH_PRINT);
    }
    return 1;
}

void __osInitialize_emu(void) {
    __printfunc = proutSyncPrintf;
}

#endif
