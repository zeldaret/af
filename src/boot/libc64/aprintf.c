#include "libc64/aprintf.h"

s32 vaprintf(PrintCallback* func, const char* fmt, va_list ap) {
    return _Printf(*func, func, fmt, ap);
}

s32 aprintf(PrintCallback* func, const char* fmt, ...) {
    s32 ret;
    va_list args;
    va_start(args, fmt);

    ret = vaprintf(func, fmt, args);

    va_end(args);

    return ret;
}
