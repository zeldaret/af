#include "stdarg.h"
#include "PR/os.h"

void __osSyncVPrintf(const char *fmt, va_list args) {
    // these functions intentionally left blank.  ifdeffed out in rom release
}

void osSyncPrintf(const char *fmt, ...) {
    int ans;
    va_list ap;
    // these functions intentionally left blank.  ifdeffed out in rom release
}

void rmonPrintf(const char *fmt, ...) {
    int ans;
    va_list ap;
}
