#ifndef LIBC64_SPRINTF_H
#define LIBC64_SPRINTF_H

#include "ultra64.h"
#include "libc/stdarg.h"

void* proutPrintf(void* dst, const char* fmt, size_t size);
int vsprintf(char* dst, char* fmt, va_list args);
int sprintf(char* dst, const char* fmt, ...);

#endif
