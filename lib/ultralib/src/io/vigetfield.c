#include "PR/os_internal.h"
#include "PR/rcp.h"

u32 osViGetCurrentField(void) {
    return IO_READ(VI_CURRENT_REG) & 1;
}
