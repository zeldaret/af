#ifndef M_FBDEMO_FADE_H
#define M_FBDEMO_FADE_H

#include "ultra64.h"
#include "color.h"

typedef struct fbDemoFade {
    /* 0x000 */ u8 type;
    /* 0x001 */ u8 isDone;
    /* 0x002 */ u8 direction;
    /* 0x004 */ Color_RGBA8_u32 color;
    /* 0x008 */ s16 frame;
    /* 0x00A */ u16 unkA;
    /* 0x00C */ u16 timer;
} fbDemoFade; // size = 0x10

fbDemoFade* fbdemo_fade_init(fbDemoFade* this);
void fbdemo_fade_move(fbDemoFade* this, s32 rate);
void fbdemo_fade_draw(fbDemoFade* this, Gfx** gfxP);
void fbdemo_fade_startup(fbDemoFade* this);
void fbdemo_fade_settype(fbDemoFade* this, int type);
void fbdemo_fade_setcolor_rgba8888(fbDemoFade* this, u32 color);
u8 fbdemo_fade_is_finish(fbDemoFade* this);


#endif
