#ifndef _FINALROM
#include "sys/asm.h"
#include "sys/regdef.h"

LEAF(osDelay)
    sll     t0,a0,2
    addu    t0,a0  
    sll     t0,t0,2
    beqz    a0,2f

.set noreorder
1:
    subu    t0,1
    nop
    nop
    bnez    t0,1b
    nop
.set reorder
2:
    j   ra

END(osDelay)

#endif