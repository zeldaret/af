#ifndef LIBU64_STACK_CHECK_H
#define LIBU64_STACK_CHECK_H

#include "ultra64.h"

typedef enum StackStatus {
    /* 0 */ STACK_STATUS_OK,
    /* 1 */ STACK_STATUS_WARNING,
    /* 2 */ STACK_STATUS_OVERFLOW
} StackStatus;

typedef struct StackEntry {
    /* 0x00 */ struct StackEntry* next;
    /* 0x04 */ struct StackEntry* prev;
    /* 0x08 */ void* head;
    /* 0x0C */ void* tail;
    /* 0x10 */ u32 initValue;
    /* 0x14 */ s32 minSpace;
    /* 0x18 */ const char* name;
} StackEntry; // size = 0x1C

void StackCheck_Init(StackEntry* entry, void* stackBottom, void* stackTop, u32 initValue, s32 minSpace, const char* name);
void StackCheck_Cleanup(StackEntry* entry);
s32 StackCheck_Check(StackEntry* entry);

#endif
