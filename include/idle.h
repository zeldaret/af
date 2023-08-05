#ifndef IDLE_H
#define IDLE_H

#include "ultra64.h"

extern OSViMode gViConfigMode;

extern u32 gViConfigFeatures;
extern f32 gViConfigXScale;
extern f32 gViConfigYScale;

void Idle_ThreadEntry(void* arg);

#endif
