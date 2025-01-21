#include "PR/os_version.h"

#if !defined(_FINALROM) || BUILD_VERSION < VERSION_J
#include "sys/asm.h"
#include "sys/regdef.h"

LEAF(osDelay)
    sll     t0, a0, 2
    addu    t0, a0  
    sll     t0, t0, 2
    beqz    a0, 2f

1:
    subu    t0, 1
    NOP
    NOP
    bnez    t0, 1b

2:
    j   ra

END(osDelay)

#endif
