#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
LEAF(__osGetFpcCsr)
    CFC1(   v0, fcr31)
    jr      ra
#ifndef MODERN_CC
END(__osGetSR) # @bug: Should be __osGetFpcCsr
#else
END(__osGetFpcCsr)
#endif
