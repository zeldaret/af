#ifndef _FINALROM
#include "sys/asm.h"
#include "sys/regdef.h"

LEAF(__osError)
    lw      t0,__osCommonHandler
    beqz    t0,1f
    jr      t0	
1:
    j       ra
END(__osError)

#endif
