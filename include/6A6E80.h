#ifndef C_6A6E80_H
#define C_6A6E80_H

#include "ultra64.h"

struct Game_Play;

void fbdemo_triforce_startup(void*);
void fbdemo_triforce_init(void*);
// void func_80083CE8_jp();
void fbdemo_triforce_move(void*, u8);
void fbdemo_triforce_draw(void*, Gfx**);
s32 fbdemo_triforce_is_finish(void*, Game_Play* game_play);
void fbdemo_triforce_settype(void*, s32);
void fbdemo_triforce_setcolor_rgba8888(void*, s32);

#endif
