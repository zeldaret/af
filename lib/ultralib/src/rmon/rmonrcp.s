#include "PR/os_version.h"
#if !defined(_FINALROM) || BUILD_VERSION < VERSION_J

#include "sys/asm.h"
#include "sys/regdef.h"
#include "PR/rcp.h"
#include "PR/R4300.h"

.text

/* check if the rsp is currently running by polling HALT or BROKE bits in SP_STATUS */
LEAF(__rmonRCPrunning)
    move    v0, zero
    lw      t0, PHYS_TO_K1(SP_STATUS_REG)
    and     t0, (SP_STATUS_HALT | SP_STATUS_BROKE)
    bnez    t0, isHalted
    ori     v0, 1
isHalted:
    jr      ra
END(__rmonRCPrunning)

/* stop the rsp, first wait for any ongoing dma to complete before setting HALT in SP_STATUS */
LEAF(__rmonIdleRCP)
    li      a0, PHYS_TO_K1(SP_DMA_BUSY_REG)
wait4dma:
    lw      v0, (a0)
    bnez    v0, wait4dma
    li      a1, SP_CLR_INTR_BREAK | SP_SET_HALT
    li      a0, PHYS_TO_K1(SP_STATUS_REG)
    sw      a1, (a0)

/* wait for the rsp to stop */
awaitIdle:
    li      a0, PHYS_TO_K1(SP_STATUS_REG)
    lw      v0, (a0)
    and     v0, (SP_STATUS_HALT | SP_STATUS_BROKE)
    beqz    v0, awaitIdle
    jr      ra
END(__rmonIdleRCP)

/* run the rsp in single-step mode to step one instruction */
LEAF(__rmonStepRCP)
    li      a0, PHYS_TO_K1(SP_STATUS_REG)
    li      a1, (SP_CLR_INTR_BREAK | SP_SET_SSTEP | SP_CLR_BROKE | SP_CLR_HALT)
    sw      a1, (a0)
    b       awaitIdle
END(__rmonStepRCP)

/* run the rsp normally */
LEAF(__rmonRunRCP)
    li      a0, PHYS_TO_K1(MI_INTR_MASK_REG)
    li      a1, MI_INTR_MASK_SET_SP
    sw      a1, (a0)
    li      a0, PHYS_TO_K1(SP_STATUS_REG)
    li      a1, (SP_SET_INTR_BREAK | SP_CLR_SSTEP | SP_CLR_BROKE | SP_CLR_HALT)
    sw      a1, (a0)
    jr      ra
END(__rmonRunRCP)

#endif
