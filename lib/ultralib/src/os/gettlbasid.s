#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.set noreorder
.text
LEAF(__osGetTLBASID)
    mfc0    v0, C0_ENTRYHI
    jr      ra
     nop
END(__osGetTLBASID)
