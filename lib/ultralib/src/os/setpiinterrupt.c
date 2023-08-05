#include "PR/os_internal.h"

struct __osHwInt {
    s32 (*handler)(void);
    void* stackEnd;
};

extern struct __osHwInt __osPiIntTable;

void __osSetPIIntrRoutine(struct __osHwInt* ir) {
    register u32 saveMask = __osDisableInt();

    __osPiIntTable.handler = ir->handler;
    __osPiIntTable.stackEnd = ir->stackEnd;
    __osRestoreInt(saveMask);
}
