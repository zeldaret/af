#include "audioMgr.h"
#include "irqmgr.h"
#include "code_variables.h"
#include "attributes.h"
#include "segment_symbols.h"
#include "audio.h"
#include "m_debug.h"
#include "6FB340.h"
#include "libc64/malloc.h"
#include "getcurrentms.h"
#include "libc64/sleep.h"
#include "macros.h"

Audiomgr* audiomgr_class_p;
Audiomgr audiomgr_class;
s32 B_80144FB8_jp;

void func_800D2590_jp(void) {
    AudioTask* task = audiomgr_class_p->rspTask;

    if (audiomgr_class_p->rspTask->taskQueue != NULL) {
        osSendMesg(task->taskQueue, NULL, OS_MESG_BLOCK);
    }
}

void func_800D25D0_jp(void) {
    AudioTask* rspTask;
    OSTimer timer;
    OSMesg msg;

    if (audiomgr_class_p->unk_28B == 0) {
        if (SREG(20) == 1) {
            audiomgr_class_p->rspTask = NULL;
        }
        while (!MQ_IS_EMPTY(&audiomgr_class_p->cmdQueue)) {
            osRecvMesg(&audiomgr_class_p->cmdQueue, NULL, OS_MESG_NOBLOCK);
        }

        if (audiomgr_class_p->rspTask != NULL) {
            audiomgr_class_p->audioTask.next = NULL;
            audiomgr_class_p->audioTask.flags = OS_SC_NEEDS_RSP;
            audiomgr_class_p->audioTask.framebuffer = NULL;

            audiomgr_class_p->audioTask.list = audiomgr_class_p->rspTask->task;
            audiomgr_class_p->audioTask.msgQ = &audiomgr_class_p->cmdQueue;

            audiomgr_class_p->audioTask.msg = NULL;
            osSendMesg(&B_80145DB8_jp, &audiomgr_class_p->audioTask, OS_MESG_BLOCK);
            func_800D85EC_jp();
        }
        if (SREG(20) >= 2) {
            rspTask = NULL;
        } else {
            audiomgr_class.unk_28A = 5;
            rspTask = func_800D19BC_jp();
            audiomgr_class.unk_28A = 6;
        }
        audiomgr_class.unk_28A = 7;
        if (audiomgr_class_p->rspTask != NULL) {
            while (true) {
                osSetTimer(&timer, OS_USEC_TO_CYCLES(20000), 0, &audiomgr_class_p->cmdQueue, (OSMesg)666);
                osRecvMesg(&audiomgr_class_p->cmdQueue, (OSMesg*)&msg, OS_MESG_BLOCK);
                osStopTimer(&timer);
                if ((msg == (OSMesg)666) && (msg == (OSMesg)666)) {
                    osSyncPrintf("AUDIO SP TIMEOUT2 %08x %08x\n", audiomgr_class_p->rspTask,
                                 &audiomgr_class_p->rspTask->task);
                    B_80144FB8_jp++;
                    func_800D8618_jp();
                    osSyncPrintf("AUDIO CANSEL&RETRY %d\n", B_80144FB8_jp);
                } else {
                    break;
                }
            }
            func_800D2590_jp();
        }
        audiomgr_class.unk_28A = 8;
        audiomgr_class_p->rspTask = rspTask;

        if ((SREG(20) >= 2) && (rspTask == NULL)) {
            audiomgr_class_p->unk_28B = 1;
        }
    }
}

void func_800D287C_jp(void) {
    func_800D19DC_jp();
}

void audiomgr_proc(UNUSED void* arg) {
    IrqmgrClient irq;
    s16* msg = NULL;
    s32 exit;
    UNUSED s32 pad;

    func_800F88E8_jp(malloc(0x47A00), (void*)0x47A00, SEGMENT_ROM_START(segment_027130),
                     SEGMENT_ROM_END(segment_027130), SEGMENT_ROM_START(segment_13D9A0));
    osSendMesg(&audiomgr_class_p->lockQueue, NULL, OS_MESG_BLOCK);
    func_800D213C_jp(DmaMgr_AudioDmaHandler);
    irqmgr_AddClient(&irq, &audiomgr_class_p->interruptQueue);

    exit = false;

    while (!exit) {
        B_80145FFC_jp = GetCurrentMilliseconds();
        audiomgr_class.unk_28A = 2;
        osRecvMesg(&audiomgr_class_p->interruptQueue, (OSMesg*)&msg, OS_MESG_BLOCK);
        switch (*msg) {
            case OS_SC_RETRACE_MSG:
                audiomgr_class.unk_28A = 3;
                if (ResetStatus < 2) {
                    func_800D25D0_jp();
                }
                audiomgr_class.unk_28A = 4;
                while (!MQ_IS_EMPTY(&audiomgr_class_p->interruptQueue)) {
                    osRecvMesg(&audiomgr_class_p->interruptQueue, (OSMesg*)&msg, OS_MESG_BLOCK);
                    switch (*msg) {
                        case OS_SC_RETRACE_MSG:
                            break;

                        case OS_SC_PRE_NMI_MSG:
                            func_800D287C_jp();
                            break;

                        case OS_SC_RDP_DONE_MSG:
                            exit = true;
                            break;
                    }
                }
                break;
            case OS_SC_PRE_NMI_MSG:
                func_800D287C_jp();
                break;
            case OS_SC_RDP_DONE_MSG:
                exit = true;
                break;
        }
    }
    irqmgr_RemoveClient(&irq);
}

void func_800D2AA0_jp(void) {
    osRecvMesg(&audiomgr_class_p->lockQueue, NULL, OS_MESG_BLOCK);
}

void func_800D2AD0_jp(void* stack, OSPri pri, OSId id) {
    Audiomgr* mgr = audiomgr_class_p = &audiomgr_class;

    bzero(mgr, sizeof(Audiomgr));
    audiomgr_class_p->rspTask = NULL;

    osCreateMesgQueue(&audiomgr_class_p->cmdQueue, audiomgr_class_p->cmdMsgBuf,
                      ARRAY_COUNT(audiomgr_class_p->cmdMsgBuf));
    osCreateMesgQueue(&audiomgr_class_p->interruptQueue, audiomgr_class_p->interruptMsgBuf,
                      ARRAY_COUNT(audiomgr_class_p->interruptMsgBuf));
    osCreateMesgQueue(&audiomgr_class_p->lockQueue, audiomgr_class_p->lockMsgBuf,
                      ARRAY_COUNT(audiomgr_class_p->lockMsgBuf));

    osCreateThread(&audiomgr_class_p->thread, id, audiomgr_proc, NULL, stack, pri);
    osStartThread(&audiomgr_class_p->thread);
}

void func_800D2B94_jp(void) {
    SREG(20) = 2;

    while (audiomgr_class.unk_28B == 0) {
        usleep(1000);
    }
}

void func_800D2BEC_jp(void) {
    SREG(20) = 0;
    audiomgr_class.unk_28B = 0;
}
