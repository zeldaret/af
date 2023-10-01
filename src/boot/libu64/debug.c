#include "libu64/debug.h"
#include "fault.h"

void _dbg_hungup(const char* name, int line) {
    osGetThreadId(NULL);
    fault_AddHungupAndCrash(name, line);
}

void Reset() {
    fault_AddHungupAndCrash("Reset", 0);
}
