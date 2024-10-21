#ifndef M_FBDEMO_WIPE_H
#define M_FBDEMO_WIPE_H

#include "ultra64.h"
#include "color.h"

typedef struct fbDemoWipe1 {
    /* 0x000 */ Color_RGBA8_u32 color;
    /* 0x004 */ Color_RGBA8_u32 altColor;
    /* 0x008 */ u8 direction;
    /* 0x009 */ u8 frame;
    /* 0x00A */ u8 finished;
    /* 0x00C */ u16 texX;
    /* 0x00E */ u16 texY;
    /* 0x010 */ u16 normal;
    /* 0x018 */ Mtx projection;
    /* 0x058 */ Mtx lookAt;
    /* 0x098 */ Mtx modelView[2][3];
} fbDemoWipe1; // size = 0x218

fbDemoWipe1* fbdemo_wipe1_init(fbDemoWipe1* this);
void fbdemo_wipe1_move(fbDemoWipe1* this, s32 rate);
void fbdemo_wipe1_draw(fbDemoWipe1* this, Gfx** gfxP);
void fbdemo_wipe1_startup(fbDemoWipe1* this);
void fbdemo_wipe1_settype(fbDemoWipe1* this, s32 type);
void fbdemo_wipe1_setcolor_rgba8888(fbDemoWipe1* this, u32 color);
void fbdemo_wipe1_setaltcolor_rgba8888(fbDemoWipe1* this, u32 color);
u8 fbdemo_wipe1_is_finish(fbDemoWipe1* this);

#endif
