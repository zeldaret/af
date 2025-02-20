#include "PR/ultraerror.h"
#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
.set noreorder
LEAF(osUnmapTLB)
#if defined (_DEBUG) && defined (__sgi)
    bgez    a0, 1f
     nop
    b       2f
     nop
1:
    li      t0, 0x1F
.set noat
    slt     AT, a0, t0
    bnez    AT, 3f
     nop
.set at
2:
    move    a2, a0
    li      a0, ERR_OSUNMAPTLB
    li      a1, 1
    j       __osError
     nop
3:
#endif
    mfc0    t0, C0_ENTRYHI
    mtc0    a0, C0_INX
    li      t1, K0BASE
    mtc0    t1, C0_ENTRYHI
    mtc0    zero, C0_ENTRYLO0
    mtc0    zero, C0_ENTRYLO1
    nop
    tlbwi
    nop
    nop
    nop
    nop
    mtc0    t0, C0_ENTRYHI
    jr      ra
     nop
END(osUnmapTLB)

