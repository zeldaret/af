#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
LEAF(osWritebackDCache)
    blez a1, 2f
    li t3, DCACHE_SIZE
    bgeu a1,t3, 3f
    move t0, a0
    addu t1, a0,a1
    bgeu t0, t1, 2f
    addiu t1, t1, -DCACHE_LINESIZE
    andi t2, t0, DCACHE_LINEMASK
    subu t0, t0,t2
1:
	.set noreorder
    cache (C_HWB|CACH_PD), (t0)
    bltu t0, t1, 1b
     addiu t0, t0, DCACHE_LINESIZE
	.set reorder
2:
    jr ra
3:
    li t0, KUSIZE
    addu t1, t0,t3
    addiu t1, t1, -DCACHE_LINESIZE
4:
	.set noreorder
    cache (C_IWBINV|CACH_PD), (t0)
    bltu t0, t1, 4b
     addiu t0, t0, DCACHE_LINESIZE
	.set reorder
    jr ra
END(osWritebackDCache)
