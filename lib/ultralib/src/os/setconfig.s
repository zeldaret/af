#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
LEAF(__osSetConfig)
    MTC0(   a0, C0_CONFIG)
    jr      ra
END(__osSetConfig)
