#include "sFRm_flashrom.h"

#include "libu64/stackcheck.h"
#include "os_internal_flash.h"

#include "macros.h"
#include "m_thread.h"
#include "stack.h"

OSMesgQueue sFlashromMsgQueue;
OSMesg sFlashromMsgBuf[1];
OSIoMesg sFlashromIOMsg;

STACK(sFlashromStack, 0x400);
StackEntry sFlashromStackInfo;
OSThread sFlashromThread;
FlashromRequest sFlashromRequest;

s32 sFlashromIsInit = FALSE;

s32 sFRm_Init(void) {
    s32 ret = TRUE;
    u32 type;
    u32 maker;

    osFlashInit();
    sFRm_InitRequest();
    osCreateMesgQueue(&sFlashromMsgQueue, sFlashromMsgBuf, ARRAY_COUNT(sFlashromMsgBuf));
    osFlashReadId(&type, &maker);

    switch (maker) {
        case FLASH_VERSION_MX_PROTO_A:
            break;

        case FLASH_VERSION_MX_A:
            break;

        case FLASH_VERSION_MX_C:
            break;

        case FLASH_VERSION_MX_B_AND_D:
            break;

        case FLASH_VERSION_MEI:
            break;

        default:
            ret = FALSE;
            break;
    }

    if (ret == TRUE) {
        sFlashromIsInit = TRUE;
    }

    return ret;
}

s32 sFRm_IsInit(void) {
    return sFlashromIsInit;
}

s32 sFRm_EraseSector(u32 pageNum) {
    return osFlashSectorErase(pageNum);
}

s32 sFRm_EraseAll(void) {
    return osFlashAllErase();
}

s32 sFRm_WritePage(void* addr, u32 pageNum) {
    s32 ret = -1;
    s32 err;

    osWritebackDCache(addr, FLASH_BLOCK_SIZE);
    err = osFlashWriteBuffer(&sFlashromIOMsg, OS_MESG_PRI_NORMAL, addr, &sFlashromMsgQueue);
    osRecvMesg(&sFlashromMsgQueue, NULL, OS_MESG_BLOCK);

    if ((err != -1) && (err == 0)) {
        ret = osFlashWriteArray(pageNum);
    }

    return ret;
}

s32 sFRm_Write(void* addr, u32 pageNum, u32 pageCount) {
    s32 ret;
    s32 retries;
    u32 i;

    if ((pageNum % FLASH_BLOCK_SIZE) != 0) {
        return 1;
    }

    osWritebackDCache(addr, pageCount * FLASH_BLOCK_SIZE);

    retries = 3;
    do {
        ret = osFlashSectorErase(pageNum);
        if (ret == -1) {
            return ret;
        }

        for (i = 0; i < pageCount; i++) {
            ret = osFlashWriteBuffer(&sFlashromIOMsg, OS_MESG_PRI_NORMAL, (u8*)addr + i * FLASH_BLOCK_SIZE,
                                     &sFlashromMsgQueue);
            osRecvMesg(&sFlashromMsgQueue, NULL, OS_MESG_BLOCK);
            if (ret == -1) {
                break;
            }

            ret = osFlashWriteArray(pageNum + i);
            if (ret == -1) {
                break;
            }
        }
        retries--;
    } while ((ret == -1) && (retries != 0));

    return ret;
}

s32 sFRm_ReadPage(void* addr, u32 pageNum) {
    s32 ret;

    osInvalDCache(addr, FLASH_BLOCK_SIZE);
    ret = osFlashReadArray(&sFlashromIOMsg, 0, pageNum, addr, 1, &sFlashromMsgQueue);
    osRecvMesg(&sFlashromMsgQueue, NULL, OS_MESG_BLOCK);

    return ret;
}

s32 sFRm_Read(void* addr, u32 pageNum, u32 pageCount) {
    s32 ret;
    OSIoMesg msg;

    osInvalDCache(addr, pageCount * FLASH_BLOCK_SIZE);
    ret = osFlashReadArray(&msg, OS_MESG_PRI_NORMAL, pageNum, addr, pageCount, &sFlashromMsgQueue);
    osRecvMesg(&sFlashromMsgQueue, NULL, OS_MESG_BLOCK);
    return ret;
}

void sFRm_InitRequest(void) {
    FlashromRequest* req = &sFlashromRequest;

    req->type = 0;
}

void sFRm_proc(void* arg) {
    FlashromRequest* req = (FlashromRequest*)arg;

    switch (req->type) {
        case FLASHROM_REQUEST_WRITE:
            req->response = sFRm_Write(req->addr, req->pageNum, req->pageCount);
            osSendMesg(&req->queue, (OSMesg)req->response, OS_MESG_BLOCK);
            break;

        case FLASHROM_REQUEST_READ:
            req->response = sFRm_Read(req->addr, req->pageNum, req->pageCount);
            osSendMesg(&req->queue, (OSMesg)req->response, OS_MESG_BLOCK);
            break;
    }
}

void sFRm_WriteAsync(void* addr, u32 pageNum, u32 pageCount) {
    FlashromRequest* req = &sFlashromRequest;

    req->type = FLASHROM_REQUEST_WRITE;
    req->addr = addr;
    req->pageNum = pageNum;
    req->pageCount = pageCount;

    osCreateMesgQueue(&req->queue, req->msgBuf, ARRAY_COUNT(req->msgBuf));
    StackCheck_Init(&sFlashromStackInfo, sFlashromStack, STACK_TOP(sFlashromStack), 0, 0x100, "sFRm_flashrom");
    osCreateThread(&sFlashromThread, M_THREAD_ID_FLASHROM, sFRm_proc, &sFlashromRequest, STACK_TOP(sFlashromStack),
                   M_PRIORITY_FLASHROM);
    osStartThread(&sFlashromThread);
}

s32 sFRm_IsBusy(void) {
    FlashromRequest* req = &sFlashromRequest;

    if (sFRm_IsInit() != 1) {
        return -1;
    }

    return MQ_IS_FULL(&req->queue);
}

s32 sFRm_AwaitResult(void) {
    FlashromRequest* req = &sFlashromRequest;

    osRecvMesg(&req->queue, NULL, OS_MESG_BLOCK);
    osDestroyThread(&sFlashromThread);
    StackCheck_Check(&sFlashromStackInfo);
    StackCheck_Cleanup(&sFlashromStackInfo);
    return req->response;
}

void sFRm_WriteSync(void* addr, u32 pageNum, u32 pageCount) {
    sFRm_WriteAsync(addr, pageNum, pageCount);
    sFRm_AwaitResult();
}

s32 sFRm_GetResult(void) {
    FlashromRequest* req = &sFlashromRequest;

    return req->response;
}
