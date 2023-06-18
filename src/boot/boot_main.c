#include "libc/stdint.h"
#include "ultra64.h"

#include "idle.h"
#include "stack.h"
#include "stackcheck.h"

extern u8 dmadata_VRAM[];
extern OSPiHandle* gCartHandle;

STACK(sIdleStack, 0x400);
StackEntry sIdleStackInfo;
StackEntry sBootStackInfo;
OSThread sIdleThread;
STACK(sBootStack, 0x400);

void func_80025C60_jp(void) {
    s32 size = (uintptr_t)func_80025C60_jp + 0x7FFFFC00;
    
    if (size > 0) {
        bzero(0x80000400, size);
    }
    
    size = osMemSize - OS_K0_TO_PHYSICAL(dmadata_VRAM);
    if (size > 0) {
        bzero(dmadata_VRAM, size);
    }
}

void bootproc(void) {
    StackCheck_Init(&sBootStackInfo, sBootStack, STACK_TOP(sBootStack), 0, -1, "boot");
    osMemSize = 0x400000;
    __osInitialize_common();
    if (osAppNMIBuffer[15] & 4) {
        osAppNMIBuffer[15] &= ~4;
        osAppNMIBuffer[15] |= 2;
    } else {
        osAppNMIBuffer[15] &= ~2;
    }
    osUnmapTLBAll();
    func_80025C60_jp();
    gCartHandle = osCartRomInit();
    StackCheck_Init(&sIdleStackInfo, sIdleStack, STACK_TOP(sIdleStack), 0, 0x100, "idle");
    osCreateThread(&sIdleThread, 1, Idle_ThreadEntry, NULL, STACK_TOP(sIdleStack), 0xC);
    osStartThread(&sIdleThread);
}
