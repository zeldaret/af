#include "libc/stdint.h"
#include "ultra64.h"

#include "idle.h"
#include "m_thread.h"
#include "segment_symbols.h"
#include "stack.h"
#include "stackcheck.h"

extern OSPiHandle* gCartHandle; // TODO: Determine where this goes

STACK(sIdleStack, 0x400);
StackEntry sIdleStackInfo;
StackEntry sBootStackInfo;
OSThread sIdleThread;
STACK(sBootStack, 0x400);

// Unknown original name
void bootclear(void) {
    s32 size = (uintptr_t)bootclear - BOOT_ADDRESS_ULTRA;

    if (size > 0) {
        bzero((void*)BOOT_ADDRESS_ULTRA, size);
    }

    size = osMemSize - OS_K0_TO_PHYSICAL(SEGMENT_VRAM_START(dmadata));
    if (size > 0) {
        bzero(SEGMENT_VRAM_START(dmadata), size);
    }
}

void bootproc(void) {
    StackCheck_Init(&sBootStackInfo, sBootStack, STACK_TOP(sBootStack), 0, -1, "boot");

    osMemSize = 0x400000; // 4MB
    osInitialize();

    if (osAppNMIBuffer[15] & 4) {
        osAppNMIBuffer[15] &= ~4;
        osAppNMIBuffer[15] |= 2;
    } else {
        osAppNMIBuffer[15] &= ~2;
    }

    osUnmapTLBAll();
    bootclear();

    gCartHandle = osCartRomInit();

    StackCheck_Init(&sIdleStackInfo, sIdleStack, STACK_TOP(sIdleStack), 0, 0x100, "idle");
    osCreateThread(&sIdleThread, M_THREAD_ID_IDLE, Idle_ThreadEntry, NULL, STACK_TOP(sIdleStack), M_PRIORITY_IDLE);
    osStartThread(&sIdleThread);
}
