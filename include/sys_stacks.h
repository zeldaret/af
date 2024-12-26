#ifndef SYS_STACKS_H
#define SYS_STACKS_H

#include "ultra64.h"
#include "stack.h"

extern STACK(graphStack, 0x1800);
extern STACK(schedStack, 0x600);
extern STACK(audioStack, 0x800);
extern STACK(padmgrStack, 0x500);
extern STACK(irqmgrStack, 0x500);

#endif
