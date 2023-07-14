#include "PR/os_internal.h"
#include "osint.h"

void osSetTime(OSTime time) {
    __osCurrentTime = time;
}
