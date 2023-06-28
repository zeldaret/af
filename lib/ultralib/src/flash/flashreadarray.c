#include "ultra64.h"
#include "PR/os_internal_flash.h"


s32 osFlashReadArray(OSIoMesg* mb, s32 priority, u32 page_num, void* dramAddr, u32 n_pages, OSMesgQueue* mq) {
    u32 ret;
    u32 tmp;
    u32 end_page;
    u32 one_dma_pages;

    // select read array mode
    osEPiWriteIo(&__osFlashHandler, __osFlashHandler.baseAddress | FLASH_CMD_REG, FLASH_CMD_READ_ARRAY);
    // dummy read?
    osEPiReadIo(&__osFlashHandler, __osFlashHandler.baseAddress, &tmp);

    // DMA requested pages
    mb->hdr.pri = priority;
    mb->hdr.retQueue = mq;
    mb->dramAddr = dramAddr;

    end_page = page_num + n_pages - 1;

    if ((end_page & 0xF00) != (page_num & 0xF00)) {
        one_dma_pages = 256 - (page_num & 0xFF);
        n_pages -= one_dma_pages;
        mb->size = one_dma_pages * FLASH_BLOCK_SIZE;
        mb->devAddr = __osFlashGetAddr(page_num);
        osEPiStartDma(&__osFlashHandler, mb, OS_READ);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
        page_num = (page_num + 256) & 0xF00;
        mb->dramAddr = (u32)mb->dramAddr + mb->size;
    }

    while (n_pages > 256) {
        one_dma_pages = 256;
        n_pages -= 256;
        mb->size = one_dma_pages * FLASH_BLOCK_SIZE;
        mb->devAddr = __osFlashGetAddr(page_num);
        osEPiStartDma(&__osFlashHandler, mb, OS_READ);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
        page_num += 256;
        mb->dramAddr = (u32)mb->dramAddr + mb->size;
    }

    mb->size = n_pages * FLASH_BLOCK_SIZE;
    mb->devAddr = __osFlashGetAddr(page_num);

    ret = osEPiStartDma(&__osFlashHandler, mb, OS_READ);

    return ret;
}
