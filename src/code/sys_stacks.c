#include "sys_stacks.h"

STACK(graphStack, 0x1800);
STACK(schedStack, 0x600);
STACK(audioStack, 0x800);
STACK(padmgrStack, 0x500);
STACK(irqmgrStack, 0x500);
