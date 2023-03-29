#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
LEAF(__osGetWatchLo)
    STAY2(mfc0 v0, C0_WATCHLO)
    jr ra
END(__osGetWatchLo)
