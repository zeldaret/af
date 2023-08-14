#ifndef C_6A8180_H
#define C_6A8180_H

#include "ultra64.h"

struct PlayState;

typedef struct PlayState2128 {
    /* 0x00 */ char unk00[0x10];
} PlayState2128; // size = 0x10

void fbdemo_fade_init(void* arg0);
void fbdemo_fade_move(void* arg0, u8 arg1);
void fbdemo_fade_draw(void* arg0, Gfx** gfx);
void fbdemo_fade_startup(void* arg0);
void fbdemo_fade_settype(void* arg0, s32 arg1);
void fbdemo_fade_setcolor_rgba8888(void* arg0, s32 arg1);
s32 fbdemo_fade_is_finish(void* arg0, struct PlayState* play);

#endif
