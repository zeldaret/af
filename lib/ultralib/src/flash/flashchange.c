#include "PR/os_internal.h"
#include "PR/R4300.h"

void osFlashChange(u32 flash_num) {
    __osFlashHandler.baseAddress = PHYS_TO_K1((FLASH_START_ADDR + flash_num * FLASH_SIZE));
    __osFlashHandler.type = DEVICE_TYPE_FLASH + flash_num;
    return;
}
