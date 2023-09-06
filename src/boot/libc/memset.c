#include "libc/memset.h"

void* memset(void* dst, s32 val, size_t len) {
    u8* d = dst;

    while (len--) {
        *d++ = val;
    }

    return dst;
}
