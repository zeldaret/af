#include "ultra64.h"
#include "PR/os_internal_flash.h"

void osFlashAllEraseThrough(void) {
    // start chip erase operation, no waiting for completion
    osEPiWriteIo(&__osFlashHandler, __osFlashHandler.baseAddress | FLASH_CMD_REG, FLASH_CMD_CHIP_ERASE);
    osEPiWriteIo(&__osFlashHandler, __osFlashHandler.baseAddress | FLASH_CMD_REG, FLASH_CMD_EXECUTE_ERASE);
}
