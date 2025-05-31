#include "PR/os_version.h"

#if !defined(_FINALROM) || BUILD_VERSION < VERSION_J
#include "sys/asm.h"
#include "sys/regdef.h"
#include "PR/os_version.h"

LEAF(__osError)
#if BUILD_VERSION < VERSION_J
    lw      t0, __osErrorHandler
    beqz    t0, 1f
    jr      t0
#elif BUILD_VERSION < VERSION_K
    lw      t0, __kmc_pt_mode
    bnez    t0, _kmc_mode

    lw      t0, __osErrorHandler
    beqz    t0, 1f
    jr      t0
_kmc_mode:
    lw      t0, __kmcErrorHandler
    beqz    t0, 1f
    jr      t0
#else
    lw      t0, __osCommonHandler
    beqz    t0, 1f
    jr      t0
#endif
1:
    j       ra
END(__osError)

#endif
