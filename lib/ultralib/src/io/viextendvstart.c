#include <PR/os_internal.h>
#include "viint.h"

void osViExtendVStart(u32 value) {
    __additional_scanline = value;
}
