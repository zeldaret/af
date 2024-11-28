#include "libc64/sprintf.h"
#include "memory.h"
#include "lib/ultralib/src/libc/xstdio.h"

void* proutPrintf(void* dst, const char* fmt, size_t size) {
    return (void*)((u8*)memcpy(dst, fmt, size) + size);
}

int vsprintf(char* dst, char* fmt, va_list args) {
    s32 ret = _Printf(proutPrintf, dst, fmt, args);

    if (ret >= 0) {
        dst[ret] = '\0';
    }
    return ret;
}
int sprintf(char* s, const char* fmt, ...) {
    s32 ret;
    va_list args;
    va_start(args, fmt);

    ret = _Printf(proutPrintf, s, fmt, args);
    if (ret >= 0) {
        s[ret] = '\0';
    }

    va_end(args);

    return ret;
}
