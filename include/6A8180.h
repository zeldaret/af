#ifndef C_6A8180_H
#define C_6A8180_H

#include "ultra64.h"

typedef struct PlayState2128 {
    /* 0x00 */ char unk00[0x10];
} PlayState2128; // size = 0x10

void fbdemo_fade_init(PlayState2128* arg0);
void fbdemo_fade_move(PlayState2128* arg0, u8 arg1);
void fbdemo_fade_draw(PlayState2128* arg0, Gfx** gfx);
void fbdemo_fade_startup(PlayState2128* arg0);
void fbdemo_fade_settype(PlayState2128* arg0, s32 arg1);
void fbdemo_fade_setcolor_rgba8888(PlayState2128* arg0, s32 arg1);
void fbdemo_fade_is_finish(PlayState2128* arg0);

#endif
