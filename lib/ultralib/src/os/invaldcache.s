#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
LEAF(osInvalDCache)
    blez a1, 3f
    li t3, DCACHE_SIZE
    bgeu a1, t3, 4f


    move t0, a0
    addu t1, a0, a1
    bgeu t0, t1, 3f


    addiu t1, t1, -DCACHE_LINESIZE
    andi t2, t0, DCACHE_LINEMASK
    beqz t2, 1f


    subu t0, t0, t2
    CACHE((C_HWBINV|CACH_PD), (t0))
    bgeu t0, t1, 3f


    addiu t0, t0, DCACHE_LINESIZE
1:
    andi t2, t1, DCACHE_LINEMASK
    beqz t2, 2f

    subu t1, t1, t2
    CACHE((C_HWBINV|CACH_PD), 0x10(t1))
    bltu t1, t0, 3f

2:
    CACHE((C_HINV|CACH_PD), (t0))
    .set noreorder
    bltu t0, t1, 2b
    addiu t0, t0, DCACHE_LINESIZE
    .set reorder
3:
    jr ra

4:
    li t0, KUSIZE
    addu t1, t0, t3
    addiu t1, t1, -DCACHE_LINESIZE
5:
    CACHE((C_IINV|CACH_PD), (t0))
    .set noreorder
    bltu t0, t1, 5b
    addiu t0, t0, DCACHE_LINESIZE
    .set reorder

    jr ra

END(osInvalDCache)
