#include "ultra64.h"
#include "PR/os_internal_flash.h"

u32 __osFlashGetAddr(u32 page_num) {
    u32 devAddr;

    if (__osFlashVersion == OLD_FLASH) {
        devAddr = page_num * 64;
    } else {
        devAddr = page_num * 128;
    }

    return devAddr;
}
