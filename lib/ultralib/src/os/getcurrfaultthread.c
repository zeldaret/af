#include "PR/os_internal.h"
#include "PRinternal/osint.h"

OSThread* __osGetCurrFaultedThread(void) {
    return __osFaultedThread;
}
