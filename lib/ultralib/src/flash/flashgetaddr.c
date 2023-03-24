#include "PR/os_internal.h"

u32 __osFlashGetAddr(u32 page_num) {
    u32 devAddr = (__osFlashVersion == OLD_FLASH) ? page_num << 6 : page_num << 7;

    return devAddr;
}
