#include "libc/stdbool.h"
#include "ultra64.h"

#include "macros.h"
#include "main.h"
#include "m_thread.h"
#include "segment_symbols.h"
#include "stack.h"
#include "libu64/stackcheck.h"
#include "m_std_dma.h"

OSThread sMainThread;
STACK(sMainStack, 0x900);
StackEntry sMainStackInfo;
OSMesg sPiMgrCmdBuff[50];
OSMesgQueue sPiMgrCmdQueue;
OSViMode gViConfigMode;

s8 D_8003BBC0_jp = 1;
u32 gViConfigFeatures = OS_VI_DITHER_FILTER_ON | OS_VI_GAMMA_OFF;
f32 gViConfigXScale = 1.0f;
f32 gViConfigYScale = 1.0f;

void Main_ThreadEntry(void* arg) {
    DmaMgr_Init();
    DmaMgr_RequestSyncDebug(SEGMENT_VRAM_START(code), SEGMENT_ROM_START(code), SEGMENT_ROM_SIZE_ALT(code), "../idle.c",
                            53);
    bzero(SEGMENT_BSS_START(code), SEGMENT_BSS_SIZE(code));
    func_800D66D0_jp(arg);
    DmaMgr_Stop();
}

void Idle_InitVideo(void) {
    osCreateViManager(OS_PRIORITY_VIMGR);

    gViConfigFeatures = OS_VI_DITHER_FILTER_ON | OS_VI_GAMMA_OFF;
    gViConfigXScale = 1.0f;
    gViConfigYScale = 1.0f;

    switch (osTvType) {
        case OS_TV_NTSC:
            gViConfigMode = osViModeNtscLan1;
            break;

        case OS_TV_MPAL:
            gViConfigMode = osViModeMpalLan1;
            break;

        case OS_TV_PAL:
            gViConfigMode = osViModeFpalLan1;
            gViConfigYScale = 0.833f;
            break;
    }

    D_8003BBC0_jp = 1;
}

void Idle_ThreadEntry(void* arg) {
    Idle_InitVideo();
    osViBlack(true);
    osCreatePiManager(OS_PRIORITY_PIMGR, &sPiMgrCmdQueue, sPiMgrCmdBuff, ARRAY_COUNT(sPiMgrCmdBuff));
    StackCheck_Init(&sMainStackInfo, sMainStack, STACK_TOP(sMainStack), 0, 0x400, "main");
    osCreateThread(&sMainThread, M_THREAD_ID_MAIN, Main_ThreadEntry, arg, &sMainStackInfo, M_PRIORITY_MAIN);
    osStartThread(&sMainThread);
    osSetThreadPri(NULL, OS_PRIORITY_IDLE);

    for (;;) {}
}
