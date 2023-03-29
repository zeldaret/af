#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

#define index a0
#define pm a1
#define vaddr a2
#define evenpaddr a3
#define oddpaddr 16(sp)
#define asid 20(sp)
.text
LEAF(osMapTLB)
    STAY2(mfc0 t0, C0_ENTRYHI)
    STAY2(mtc0 index, C0_INX)
    STAY2(mtc0 pm, C0_PAGEMASK)
.set noreorder
    lw t1, asid
    beq t1, -1, 7f
    li ta0, TLBLO_G
.set reorder
    li t2, TLBLO_NONCOHRNT | TLBLO_D | TLBLO_V
    or vaddr, vaddr, t1
    b 8f

7:
    li t2, TLBLO_NONCOHRNT | TLBLO_D | TLBLO_V | TLBLO_G
8:
    STAY2(mtc0 vaddr, C0_ENTRYHI)
    beq evenpaddr, -1, 9f
    #nop
    srl t3, evenpaddr, TLBLO_PFNSHIFT
    or t3, t3, t2
    STAY2(mtc0 t3, C0_ENTRYLO0)
    b 10f
    #nop
9:
    STAY2(mtc0 ta0, C0_ENTRYLO0)
10:
    lw t3, oddpaddr
    beq t3, -1, 11f
    #nop
    srl t3, t3, TLBLO_PFNSHIFT
    or t3, t3, t2
    STAY2(mtc0 t3, C0_ENTRYLO1)
    b 12f
    #nop
11:
    STAY2(mtc0 ta0, C0_ENTRYLO1)
    bne evenpaddr, -1, 12f
    #nop
    li t3, K0BASE
    STAY2(mtc0 t3, C0_ENTRYHI)
12:
    .set noreorder
    nop
    tlbwi
    nop
    nop
    nop
    nop
    STAY2(mtc0 t0, C0_ENTRYHI)
    jr ra
    #nop
END(osMapTLB)
