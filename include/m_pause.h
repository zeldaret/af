#ifndef M_PAUSE_H
#define M_PAUSE_H

#include "ultra64.h"
#include "libu64/pad.h"

typedef struct Pause{
    /* 0x0 */ s32 enabled;
    /* 0x4 */ s32 timer;
} Pause; // size = 0x8

void Pause_ct(Pause* pause);
s32 Pause_proc(Pause* pause, Input* input);

#endif
