#ifndef M_FBDEMO_TRIFORCE_H
#define M_FBDEMO_TRIFORCE_H

#include "ultra64.h"

typedef struct fbDemoTriforce {
    /* 0x00 */ s32 txt;
    /* 0x04 */ s32 frame;
    /* 0x08 */ u8 direction;
    /* 0x09 */ u8 textureNo;
    /* 0x0A */ u8 finished;
    /* 0x0B */ u8 unkB;
    /* 0x0C */ u16 normal;
    /* 0x0E */  u8 unkE[2]; 
    /* 0x10 */ Mtx perspMtx;
    /* 0x50 */ Mtx lookAtMtx;
} fbDemoTriforce; // size = 0x90;

void fbdemo_triforce_startup(fbDemoTriforce* this);
fbDemoTriforce* fbdemo_triforce_init(fbDemoTriforce* this);
void fbdemo_triforce_setrate(s32* rate, f32 scale);
void fbdemo_triforce_move(fbDemoTriforce* this, s32 rate);
void fbdemo_triforce_draw(fbDemoTriforce* this, Gfx** gfxP);
u8 fbdemo_triforce_is_finish(fbDemoTriforce* this);
void fbdemo_triforce_settype(fbDemoTriforce* this, s32 type);
void fbdemo_triforce_setcolor_rgba8888(fbDemoTriforce* this, u32* color);


#endif
