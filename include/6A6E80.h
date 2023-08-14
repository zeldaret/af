#ifndef C_6A6E80_H
#define C_6A6E80_H

#include "ultra64.h"

struct PlayState;

typedef struct Play80804480 {
    /* 0x00 */ char unk00[0xDC];
} Play80804480; // size = 0xDC

// void func_800831E0_jp();
// void func_800835AC_jp();
void fbdemo_cleanup(Play80804480* arg0);
s32 fbdemo_init(Play80804480* arg0, s32 arg1, s32 arg2, struct PlayState* play);
// void func_80083870_jp();
void fbdemo_draw(Play80804480* arg0, Gfx** gfx);
// void func_80083AB0_jp();
void fbdemo_move(Play80804480* arg0);
// void func_80083BF0_jp();
// void fbdemo_triforce_startup();
// void fbdemo_triforce_init();
// void func_80083CE8_jp();
// void fbdemo_triforce_move();
// void fbdemo_triforce_draw();
// void fbdemo_triforce_is_finish();
// void fbdemo_triforce_settype();
// void fbdemo_triforce_setcolor_rgba8888();

#endif
