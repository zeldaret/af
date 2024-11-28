#include "PR/ultraerror.h"
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
.set noreorder
LEAF(osMapTLB)
#if defined (_DEBUG) && defined (__sgi)
    bgez    index, 1f
     nop
    b       2f
     nop
1:
    li      t0, 0x1F
.set noat
    slt     AT, index, t0
    bnez    AT, 3f
     nop
.set at
2:
    move    a2, a0
    li      a0, ERR_OSMAPTLB_INDEX
    li      a1, 1
    j       __osError
     nop

3:
    lw      t0, asid
    li      t1, -1
.set noat
    slt     AT, t0, t1
    beqz    AT, 4f
     nop
.set at
    b       5f
     nop
4:
    li      t1, 0xFF
.set noat
    slt     AT, t1, t0
    beqz    AT, 6f
     nop
.set at
5:
    move    a2, t0
    li      a0, ERR_OSMAPTLB_ASID
    li      a1, 1
    j       __osError
     nop
6:
.set reorder
#endif
    MFC0(   t0, C0_ENTRYHI)
    MTC0(   index, C0_INX)
    MTC0(   pm, C0_PAGEMASK)
.set noreorder
    lw      t1, asid
    beq     t1, -1, 7f
    li      ta0, TLBLO_G
    li      t2, (TLBLO_NONCOHRNT | TLBLO_D | TLBLO_V)
    b       8f
     or     vaddr, vaddr, t1
.set reorder

7:
    li      t2, (TLBLO_NONCOHRNT | TLBLO_D | TLBLO_V | TLBLO_G)
8:
    MTC0(   vaddr, C0_ENTRYHI)
    beq     evenpaddr, -1, 9f

    srl     t3, evenpaddr, TLBLO_PFNSHIFT
    or      t3, t3, t2
    MTC0(   t3, C0_ENTRYLO0)
    b       10f

9:
    MTC0(   ta0, C0_ENTRYLO0)
10:
    lw      t3, oddpaddr
    beq     t3, -1, 11f

    srl     t3, t3, TLBLO_PFNSHIFT
    or      t3, t3, t2
    MTC0(   t3, C0_ENTRYLO1)
    b       12f

11:
    MTC0(   ta0, C0_ENTRYLO1)
    bne     evenpaddr, -1, 12f

    li      t3, K0BASE
    MTC0(   t3, C0_ENTRYHI)
12:
    .set noreorder
    nop
    tlbwi
    nop
    nop
    nop
    nop
    MTC0(   t0, C0_ENTRYHI)
    jr      ra
END(osMapTLB)
