#include "PR/os_internal.h"

// TODO: this comes from a header
#ident "$Revision: 1.17 $"

s32 osPiGetDeviceType(void) {
    return osRomType;
}
