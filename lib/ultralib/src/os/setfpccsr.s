#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
LEAF(__osSetFpcCsr)
    STAY2(cfc1 v0, fcr31)
    STAY2(ctc1 a0, fcr31)
    jr ra
END(__osSetSR) # @bug: Should be __osSetFpcCsr
