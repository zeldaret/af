#ifndef SYNC_PRINTF_H
#define SYNC_PRINTF_H

#include "ultra64.h"

void osSyncPrintfUnused(const char* fmt, ...);
void osSyncPrintf(const char* fmt, ...);
void rmonPrintf(const char* fmt, ...);

#endif
