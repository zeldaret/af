#include "libc/strcpy.h"

char* strcpy(char* dst, const char* src) {
    char* d = dst;

    while (*src != '\0') {
        *d++ = *src++;
    }
    *d = '\0';

    return dst;
}
