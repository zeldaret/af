#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
LEAF(__osGetConfig)
    MFC0(   v0, C0_CONFIG)
    jr      ra
END(__osGetConfig)
