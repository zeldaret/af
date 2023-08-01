#ifndef _FINALROM
#include "sys/asm.h"
#include "sys/regdef.h"

.set noreorder

LEAF(__assertBreak)
    break   0
    j       ra
END(__assertBreak)

#endif
