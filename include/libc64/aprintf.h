#ifndef LIBC64_APRINTF_H
#define LIBC64_APRINTF_H

#include "ultra64.h"
#include "lib/ultralib/src/libc/xstdio.h"

typedef void* (*PrintCallback)(void*, const char*, size_t);

s32 vaprintf(PrintCallback* func, const char* fmt, va_list ap);
s32 aprintf(PrintCallback* func, const char* fmt, ...);

#endif
