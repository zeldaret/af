#include "libc/memmove.h"

void* memmove(void* dst, const void* src, size_t len) {
    u8* d = dst;
    const u8* s = src;

    if (d == s) {
        return dst;
    }
    if (d < s) {
        while (len--) {
            *d++ = *s++;
        }
    } else {
        d += len - 1;
        s += len - 1;
        while (len--) {
            *d-- = *s--;
        }
    }

    return dst;
}
