#include "PR/os_internal.h"

void osExit() {
    __osGIOInterrupt(16);

    for (;;) {
        ;
    }
}
