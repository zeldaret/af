#include "main.h"
#include "6FB340.h"
#include "6FD190.h"
#include "audioMgr.h"
#include "code_variables.h"
#include "fault.h"
#include "game.h"
#include "getcurrentms.h"
#include "graph.h"
#include "irqmgr.h"
#include "libu64/stackcheck.h"
#include "m_debug.h"
#include "m_flashrom.h"
#include "m_thread.h"
#include "macros.h"
#include "padmgr.h"
#include "segment_symbols.h"
#include "sys_initial_check.h"
#include "sys_stacks.h"
#include "system_heap.h"
#include "zurumode.h"

OSThread graphThread;
StackEntry graphStackInfo;
StackEntry schedStackInfo;
StackEntry audioStackInfo;
StackEntry padmgrStackInfo;
StackEntry irqmgrStackInfo;
OSMesgQueue l_serialMsgQ;
OSMesg serialMsgBuf[1];
size_t gSystemHeapSize;

uintptr_t gSegments[NUM_SEGMENTS];

void func_800D64E0_jp(void) {
    u32 baseTime;
    u32 graphTime;
    u32 audioTime;
    u32 graphReg;
    u32 audioReg;
    u8 unk9C;
    u8 unk9D;

    if ((zurumode_flag != 0) && (fault_class.msgId == 0) && (D_8010F3E8_jp != 0)) {

        baseTime = GetCurrentMilliseconds();

        graphTime = (B_80145FF8_jp != 0) ? (baseTime - B_80145FF8_jp) : 0;
        audioTime = (B_80145FFC_jp != 0) ? (baseTime - B_80145FFC_jp) : 0;

        if (SREG(31) != 0) {
            graphReg = SREG(31) < graphTime;
            audioReg = SREG(31) < audioTime;
        } else {
            graphReg = (graphTime >= 3001);
            audioReg = (audioTime >= 3001);
        }

        if ((graphReg != 0) || (audioReg != 0)) {
            FaultDrawer_SetDrawerFB(osViGetCurrentFramebuffer(), SCREEN_WIDTH, SCREEN_HEIGHT);
            FaultDrawer_SetForeColor(GPACK_RGBA5551(255, 255, 255, 1));
            FaultDrawer_SetBackColor(GPACK_RGBA5551(128, 0, 0, 1));
            FaultDrawer_SetCharPad(0, 0);
            if (graphReg != 0) {
                unk9D = (game_class_p != NULL) ? game_class_p->unk_9D : 0;

                unk9C = (game_class_p != NULL) ? game_class_p->unk_9C : 0;

                FaultDrawer_DrawText(24, 16, "GRAPH INF.LOOP %2d %3d %3d %6lu", B_80145370_jp, unk9D, unk9C, graphTime);
                fault_DrawStackTrace(&graphThread, 32, 26, 10);
            }
            if (audioReg != 0) {
                FaultDrawer_DrawText(24, 126, "AUDIO INF.LOOP %2d %3d     %6lu", audiomgr_class.unk_28A, D_80113854_jp,
                                     audioTime);
                fault_DrawStackTrace(&audiomgr_class.thread, 32, 136, 10);
            }
            FaultDrawer_WritebackFBDCache();
        }
    }
}

void mainproc(void* arg) {
    IrqmgrClient client;
    OSMesgQueue irqMsgQueue;
    OSMesg irqMsgBuf[10];
    uintptr_t fb;
    uintptr_t sysHeap;
    s16* msg;

    ScreenWidth = SCREEN_WIDTH;
    ScreenHeight = SCREEN_HEIGHT;

    fault_Init();
    Check_RegionIsSupported();

    fb = func_800D94F0_jp();
    sysHeap = (uintptr_t)SEGMENT_VRAM_END(buffers);
    gSystemHeapSize = fb - sysHeap;
    SystemHeap_Init((void*)sysHeap, gSystemHeapSize);

    func_800D9524_jp();

    func_800D955C_jp(0);
    func_800D955C_jp(1);
    func_800D955C_jp(2);
    func_800D955C_jp(3);

    func_8008EE24_jp();

    new_Debug_mode();
    SREG(0) = 0;

    osCreateMesgQueue(&l_serialMsgQ, serialMsgBuf, ARRAY_COUNT(serialMsgBuf));
    osSetEventMesg(OS_EVENT_SI, &l_serialMsgQ, NULL);

    osCreateMesgQueue(&irqMsgQueue, irqMsgBuf, ARRAY_COUNT(irqMsgBuf));
    StackCheck_Init(&irqmgrStackInfo, irqmgrStack, STACK_TOP(irqmgrStack), 0, 0x100, "irqmgr");
    CreateIRQManager(STACK_TOP(irqmgrStack), M_PRIORITY_IRQMGR, 1);

    StackCheck_Init(&schedStackInfo, schedStack, STACK_TOP(schedStack), 0, 0x100, "sched");
    func_800D87C0_jp(STACK_TOP(schedStack), M_PRIORITY_SCHED);

    irqmgr_AddClient(&client, &irqMsgQueue);

    StackCheck_Init(&audioStackInfo, audioStack, STACK_TOP(audioStack), 0, 0x100, "audio");
    func_800D2AD0_jp(STACK_TOP(audioStack), M_PRIORITY_AUDIOMGR, M_THREAD_ID_AUDIOMGR);

    StackCheck_Init(&padmgrStackInfo, padmgrStack, STACK_TOP(padmgrStack), 0, 0x100, "padmgr");
    padmgr_Init(&l_serialMsgQ, 7, M_PRIORITY_PADMGR, STACK_TOP(padmgrStack));

    func_800D2AA0_jp();

    StackCheck_Init(&graphStackInfo, &graphStack, STACK_TOP(graphStack), 0, 0x100, "graph");
    osCreateThread(&graphThread, M_THREAD_ID_GRAPH, graph_proc, arg, STACK_TOP(graphStack), M_PRIORITY_GRAPH);
    osStartThread(&graphThread);

    osSetThreadPri(NULL, M_PRIORITY_MAIN_HIGH);

    while (true) {
        msg = NULL;

        while (irqMsgQueue.validCount != 0) {
            osRecvMesg(&irqMsgQueue, NULL, OS_MESG_NOBLOCK);
        }

        osRecvMesg(&irqMsgQueue, (OSMesg*)&msg, OS_MESG_BLOCK);
        if (msg == NULL) {
            break;
        }

        switch (*msg) {
            case OS_SC_RETRACE_MSG:
                if ((zurumode_flag != 0) && (fault_class.msgId == 0) && (D_8010F3E8_jp != 0)) {
                    func_800D64E0_jp();
                }
                break;
        }
    }
}
