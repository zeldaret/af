#include "PR/os_internal.h"

struct __osHwInt {
    s32 (*handler)(void);
    void* stackEnd;
};

extern struct __osHwInt __osHwIntTable[];

void __osGetHWIntrRoutine(OSHWIntr interrupt, s32 (**handler)(void), void** stackEnd) {
    *handler = __osHwIntTable[interrupt].handler;
    *stackEnd = __osHwIntTable[interrupt].stackEnd;
}
