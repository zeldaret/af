#include "macros.h"
#include "PR/os_internal.h"
#include "PR/ultraerror.h"
#include "piint.h"
#include "PR/rdb.h"

static OSThread piThread ALIGNED(8);
static char piThreadStack[OS_PIM_STACKSIZE] ALIGNED(16);

#ifndef _FINALROM
static OSThread ramromThread ALIGNED(8);
static char ramromThreadStack[1024] ALIGNED(16);
static OSMesgQueue getRamromQ ALIGNED(8);
static OSMesg getRamromBuf[1];
static OSMesgQueue freeRamromQ ALIGNED(8);
static OSMesg freeRamromBuf[1];
static void ramromMain(void*);
#endif

static OSMesgQueue piEventQueue ALIGNED(8);
static OSMesg piEventBuf[1];

OSDevMgr __osPiDevMgr = { 0 };
OSPiHandle* __osPiTable = NULL;
OSPiHandle __Dom1SpeedParam ALIGNED(8);
OSPiHandle __Dom2SpeedParam ALIGNED(8);
OSPiHandle* __osCurrentHandle[2] ALIGNED(8) = { &__Dom1SpeedParam, &__Dom2SpeedParam };

void osCreatePiManager(OSPri pri, OSMesgQueue* cmdQ, OSMesg* cmdBuf, s32 cmdMsgCnt) {
    u32 savedMask;
    OSPri oldPri;
    OSPri myPri;

#ifdef _DEBUG
    if ((pri < OS_PRIORITY_IDLE) || (pri > OS_PRIORITY_MAX)) {
        __osError(ERR_OSCREATEPIMANAGER, 1, pri);
        return;
    }
#endif

    if (__osPiDevMgr.active) {
        return;
    }
    osCreateMesgQueue(cmdQ, cmdBuf, cmdMsgCnt);
    osCreateMesgQueue(&piEventQueue, (OSMesg*)piEventBuf, 1);

    if (!__osPiAccessQueueEnabled) {
        __osPiCreateAccessQueue();
    }

    osSetEventMesg(OS_EVENT_PI, &piEventQueue, (OSMesg)0x22222222);
    oldPri = -1;
    myPri = osGetThreadPri(NULL);

    if (myPri < pri) {
        oldPri = myPri;
        osSetThreadPri(NULL, pri);
    }

    savedMask = __osDisableInt();
    __osPiDevMgr.active = 1;
    __osPiDevMgr.thread = &piThread;
    __osPiDevMgr.cmdQueue = cmdQ;
    __osPiDevMgr.evtQueue = &piEventQueue;
    __osPiDevMgr.acsQueue = &__osPiAccessQueue;
    __osPiDevMgr.dma = __osPiRawStartDma;
    __osPiDevMgr.edma = __osEPiRawStartDma;
    osCreateThread(&piThread, 0, __osDevMgrMain, &__osPiDevMgr, &piThreadStack[OS_PIM_STACKSIZE], pri);
    osStartThread(&piThread);

#ifndef _FINALROM
    osCreateThread(&ramromThread, 0, ramromMain, NULL, ramromThreadStack + 1024, (OSPri)pri - 1);
    osStartThread(&ramromThread);
#endif
    __osRestoreInt(savedMask);

    if (oldPri != -1) {
        osSetThreadPri(NULL, oldPri);
    }
}

#ifndef _FINALROM
static void ramromMain(void* arg) {
    u32 sent;
    u8 tmp[3];

    osCreateMesgQueue(&getRamromQ, getRamromBuf, 1);
    osCreateMesgQueue(&freeRamromQ, freeRamromBuf, 1);
    osSetEventMesg(OS_EVENT_RDB_REQ_RAMROM, &getRamromQ, NULL);
    osSetEventMesg(OS_EVENT_RDB_FREE_RAMROM, &freeRamromQ, NULL);

    while (TRUE) {
        osRecvMesg(&getRamromQ, NULL, OS_MESG_BLOCK);

        __osPiGetAccess();

        sent = 0;

        while (sent < 1) {
            sent += __osRdbSend(tmp, 1, RDB_TYPE_GtoH_RAMROM);
        }

        osRecvMesg(&freeRamromQ, NULL, OS_MESG_BLOCK);

        __osPiRelAccess();
    }
}
#endif
