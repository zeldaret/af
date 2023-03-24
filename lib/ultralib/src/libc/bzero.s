#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
WEAK(_bzero, bzero)
WEAK(_blkclr, blkclr)
LEAF(bzero)
XLEAF(blkclr)
    negu v1, a0
    blt a1, 12, bytezero

    andi v1, v1, 0x3
    subu a1, a1, v1

    beqz v1, blkzero
    swl zero, 0(a0)
    addu a0, a0, v1
blkzero:
    and a3, a1, ~31
    subu a1, a1, a3
    beqz a3, wordzero

    addu a3, a3, a0
1:
    sw zero, 0(a0)
    sw zero, 4(a0)
    sw zero, 8(a0)
    sw zero, 12(a0)
    addiu a0, a0, 32
    sw zero, -16(a0)
    sw zero, -12(a0)
    sw zero, -8(a0)
    sw zero, -4(a0)
    bne a0, a3, 1b

wordzero:
    and a3, a1, ~3
    subu a1, a1, a3
    beqz a3, bytezero

    addu a3, a3, a0
1:
    addiu a0, a0, 4
    sw zero, -4(a0)
    bne a0, a3, 1b

bytezero:
    blez a1, zerodone
    #nop
    addu a1, a1, a0
1:
    addiu a0, a0, 1
    sb zero, -1(a0)
    bne a0, a1, 1b
zerodone:
    jr ra
END(bzero)
