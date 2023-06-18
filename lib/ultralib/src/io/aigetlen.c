#include "PR/rcp.h"

// TODO: this comes from a header
#ident "$Revision: 1.17 $"

u32 osAiGetLength(void) {
    return IO_READ(AI_LEN_REG);
}
