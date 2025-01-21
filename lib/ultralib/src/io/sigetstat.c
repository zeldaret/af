#include "PR/os_internal.h"
#include "PRinternal/siint.h"

// TODO: this comes from a header
#ident "$Revision: 1.17 $"

u32 __osSiGetStatus(void) {
    return IO_READ(SI_STATUS_REG);
}
