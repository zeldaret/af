#ifndef STACK_CHECK_H
#define STACK_CHECK_H

#include "ultra64.h"

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
// void StackCheck_Cleanup();
// void StackCheck_GetState();
// void StackCheck_CheckAll();
void StackCheck_Check(StackEntry* entry);

#endif
