#include "stdarg.h"
#include "PR/os.h"
#include "PR/rdb.h"
#include "xstdio.h"

extern void* __printfunc;

void __osSyncVPrintf(const char* fmt, va_list args) {

    int ans;
#ifndef _FINALROM
    if (__printfunc != NULL) {
        ans = _Printf(__printfunc, NULL, fmt, args);
    }
#endif
}

void osSyncPrintf(const char* fmt, ...) {
    int ans;
    va_list ap;

#ifndef _FINALROM
    va_start(ap, fmt);
    __osSyncVPrintf(fmt, ap);
    va_end(ap);
#endif
}

void rmonPrintf(const char* fmt, ...) {
    int ans;
    va_list ap;

#ifndef _FINALROM
    va_start(ap, fmt);
    if (__printfunc != NULL) {
        ans = _Printf(__printfunc, NULL, fmt, ap);
    }
    va_end(ap);
#endif
}
