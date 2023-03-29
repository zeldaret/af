#ifndef STACK_H
#define STACK_H

#include "alignment.h"
#include "ultra64.h"


#define STACK(stack, size) \
    u64 stack[ALIGN8(size) / sizeof(u64)]

#define STACK_TOP(stack) \
    ((u64*)((u8*)(stack) + sizeof(stack)))

#endif
