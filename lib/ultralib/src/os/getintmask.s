#include "PR/R4300.h"
#include "PR/rcp.h"
#include "PR/os.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
.set noreorder
LEAF(osGetIntMask)
    mfc0    v0, C0_SR
    andi    v0, v0, OS_IM_CPU
    la      t0, __OSGlobalIntMask
    lw      t1, 0(t0)
    xor     t0, t1, -1
    andi    t0, t0, SR_IMASK
    or      v0, v0, t0

    lw      t1, PHYS_TO_K1(MI_INTR_MASK_REG)
    beqz    t1, 1f
     la      t0, __OSGlobalIntMask # this is intentionally a macro in the branch delay slot

    lw      t0, 0(t0)
    srl     t0, t0, 0x10
    xor     t0, t0, -1
    andi    t0, t0, 0x3f
    or      t1, t1, t0
1:
    sll     t2, t1, 0x10
    or      v0, v0, t2
    jr      ra
     nop
END(osGetIntMask)
