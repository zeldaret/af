#ifndef C_71FA20_H
#define C_71FA20_H

#include "ultra64.h"

// void func_800FBD80_jp();
// void func_800FBE20_jp();
// void func_800FBEF4_jp();
// void func_800FBFF8_jp();
// void func_800FC02C_jp();
// void func_800FC0B8_jp();
void Na_RhythmStart(s32 arg0, s8 arg1, s8 arg2);
void Na_RhythmStop(void);
void Na_RhythmAllStop(void);
// void func_800FC1F0_jp();
f32 get_rhythm_buffer(void);
s16 Na_GetRhythmSubTrack(void);
// void func_800FC430_jp();
void Na_GetRhythmInfo(void*);
void Na_SetRhythmInfo(void*);
// void func_800FC5C8_jp();
// void func_800FC6A0_jp();

#endif
