#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
LEAF(osSetTLBASID)
    STAY2(mtc0 a0, C0_ENTRYHI)
    jr ra
END(osSetTLBASID)
