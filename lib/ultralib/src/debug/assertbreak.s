#include "PR/os_version.h"

#if !defined(_FINALROM) || BUILD_VERSION < VERSION_J
#include "sys/asm.h"
#include "sys/regdef.h"

.set noreorder

LEAF(__assertBreak)
    break   0
    j       ra
END(__assertBreak)

#endif
