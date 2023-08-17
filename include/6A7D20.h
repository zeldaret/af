#ifndef C_6A7D20_H
#define C_6A7D20_H

#include "ultra64.h"

void fbdemo_wipe1_init(void*);
void fbdemo_wipe1_move(void*, u8);
void fbdemo_wipe1_draw(void*, Gfx**);
void fbdemo_wipe1_startup(void*);
void fbdemo_wipe1_settype(void*, s32);
void fbdemo_wipe1_setcolor_rgba8888(void*, s32);
// void func_800844BC_jp();
s32 fbdemo_wipe1_is_finish(void*, Game_Play* play);

#endif
