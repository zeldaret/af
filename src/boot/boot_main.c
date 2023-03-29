#include "ultra64.h"
#include "stack.h"

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/boot_main/func_80025C60_jp.s")


typedef struct StackEntry {
    /* 0x00 */ struct StackEntry* next;
    /* 0x04 */ struct StackEntry* prev;
    /* 0x08 */ u32 head;
    /* 0x0C */ u32 tail;
    /* 0x10 */ u32 initValue;
    /* 0x14 */ s32 minSpace;
    /* 0x18 */ const char* name;
} StackEntry; // size = 0x1C


void StackCheck_Init(StackEntry* entry, void* stackTop, void* stackBottom, u32 initValue, s32 minSpace, const char* name);
void func_80025C60_jp(void);
void func_80025FD0_jp(void* arg);

extern OSPiHandle* D_8003BBD0_jp;

extern STACK(B_8003E940_jp, 0x400);
extern StackEntry B_8003ED40_jp;
extern StackEntry B_8003ED60_jp;
extern OSThread B_8003ED80_jp;
extern STACK(B_8003EF30_jp, 0x400);

void func_80025CC0_jp(void) {
    StackCheck_Init(&B_8003ED60_jp, B_8003EF30_jp, STACK_TOP(B_8003EF30_jp), 0, -1, "boot");
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
    D_8003BBD0_jp = osCartRomInit();
    StackCheck_Init(&B_8003ED40_jp, B_8003E940_jp, STACK_TOP(B_8003E940_jp), 0, 0x100, "idle");
    osCreateThread(&B_8003ED80_jp, 1, func_80025FD0_jp, NULL, &B_8003ED40_jp, 0xC);
    osStartThread(&B_8003ED80_jp);
}
