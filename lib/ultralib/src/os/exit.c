#include "PR/os_internal.h"

void osExit(void) {
    __osGIOInterrupt(16);

    for (;;) {
        ;
    }
}
