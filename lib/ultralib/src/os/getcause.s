#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
LEAF(__osGetCause)
    STAY2(mfc0 v0, C0_CAUSE)
    jr ra
END(__osGetCause)
