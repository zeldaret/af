#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
.set noreorder
LEAF(osUnmapTLB)
    mfc0 t0, C0_ENTRYHI
    mtc0 a0, C0_INX
    li t1, K0BASE
    mtc0 t1, C0_ENTRYHI
    mtc0 zero, C0_ENTRYLO0
    mtc0 zero, C0_ENTRYLO1
    nop
    tlbwi
    nop
    nop
    nop
    nop
    mtc0 t0, C0_ENTRYHI
    jr ra
    nop	
END(osUnmapTLB)

