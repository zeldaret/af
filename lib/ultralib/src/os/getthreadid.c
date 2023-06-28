#include "PR/os_internal.h"
#include "osint.h"

OSId osGetThreadId(OSThread* thread) {
    if (thread == NULL) {
        thread = __osRunningThread;
    }

    return thread->id;
}
