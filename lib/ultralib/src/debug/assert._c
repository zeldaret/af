#include "PR/os_internal.h"

extern void __assertBreak(void);

void __assert(const char *exp, const char *filename, int line) {
    osSyncPrintf("\nASSERTION FAULT: %s, %d: \"%s\"\n", filename, line, exp);
	__assertBreak;
}
