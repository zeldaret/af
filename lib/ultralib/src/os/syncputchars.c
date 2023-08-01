#include "PR/os_internal.h"
#include "PR/rdb.h"
#include "PR/rcp.h"
#include "PR/R4300.h"

unsigned int __osRdbSendMessage = 0;
unsigned int __osRdbWriteOK = 1;

void __osSyncPutChars(int type, int length, const char* buf) {
    rdbPacket packet;
    int i;
    u32 mask;

    packet.type = type;
    packet.length = length;

    for (i = 0; i < length; i++) {
        packet.buf[i] = buf[i];
    }

    while (!__osAtomicDec(&__osRdbWriteOK)) {
        ;
    }

    mask = __osDisableInt();
    *(vu32*)RDB_BASE_REG = *(vu32*)&packet;

    while (!(__osGetCause() & CAUSE_IP6)) {
        ;
    }

    *(vu32*)RDB_READ_INTR_REG = 0;
    __osRdbWriteOK++;
    __osRestoreInt(mask);
}
