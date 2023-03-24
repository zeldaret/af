#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
.set noreorder
LEAF(__osProbeTLB)
    mfc0 t0, C0_ENTRYHI
    andi t1, t0, TLBHI_PIDMASK
    and t2, a0, -8192 # This also works: (TLBHI_VPN2MASK << 32) >> 32
    or t1, t1, t2
    mtc0 t1, C0_ENTRYHI
    nop
    nop
    nop
    tlbp
    nop
    nop
    mfc0 t3, C0_INX
    and t3, t3, TLBINX_PROBE
    bnez t3, 3f
    nop
    tlbr
    nop
    nop
    nop
    mfc0 t3, C0_PAGEMASK
    addi t3, t3, DCACHE_SIZE
    srl t3, t3, 0x1
    and ta0, t3, a0
    bnez ta0, 1f
    addi t3, t3,-1
    mfc0 v0, C0_ENTRYLO0
    b 2f
    nop
1:
    mfc0 v0, C0_ENTRYLO1
2:
    andi ta1, v0,TLBLO_V
    beqz ta1, 3f
    nop
    and v0, v0, TLBLO_PFNMASK
    sll v0, v0, TLBLO_PFNSHIFT
    and ta1, a0, t3
    add v0, v0, ta1
    b 4f
    nop
3:
    li v0, -1
4:
    mtc0 t0, C0_ENTRYHI
    jr ra
    nop	
END(__osProbeTLB)
