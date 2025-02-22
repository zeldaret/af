#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.set noreorder
.text
LEAF(__osGetTLBHi)
    mtc0    a0, C0_INX
    nop
    tlbr
    nop
    nop
    nop
    mfc0    v0, C0_ENTRYHI
    jr      ra
     nop
END(__osGetTLBHi)
