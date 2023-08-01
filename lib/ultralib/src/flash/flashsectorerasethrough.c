#include "ultra64.h"
#include "PR/os_internal_flash.h"

void osFlashSectorEraseThrough(u32 page_num) {
    // start sector erase operation
    osEPiWriteIo(&__osFlashHandler, __osFlashHandler.baseAddress | FLASH_CMD_REG, FLASH_CMD_SECTOR_ERASE | page_num);
    osEPiWriteIo(&__osFlashHandler, __osFlashHandler.baseAddress | FLASH_CMD_REG, FLASH_CMD_EXECUTE_ERASE);
}
