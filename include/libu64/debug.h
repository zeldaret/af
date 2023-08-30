#ifndef LIBU64_DEBUG_H
#define LIBU64_DEBUG_H

#include "ultra64.h"
#include "attributes.h"

void _dbg_hungup(const char* name, int line) NORETURN;
void Reset(void);

#endif
