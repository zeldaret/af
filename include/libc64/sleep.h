#ifndef LIBC64_SLEEP_H
#define LIBC64_SLEEP_H

#include "ultra64.h"

void csleep(OSTime t);
void nsleep(u32 t);
void usleep(u32 t);
void msleep(u32 t);
void sleep(u32 t);

#endif
