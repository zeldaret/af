#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
LEAF(__osGetCompare)
    MFC0(   v0, C0_COMPARE)
    jr      ra
END(__osGetCompare)
