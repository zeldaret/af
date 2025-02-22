#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
LEAF(__osSetCause)
    MTC0(   a0, C0_CAUSE)
    jr      ra
END(__osSetCause)
