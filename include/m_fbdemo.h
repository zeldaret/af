#ifndef M_FBDEMO_H
#define M_FBDEMO_H

#include "ultra64.h"
#include "z64math.h"

typedef struct fbDemo {
    /* 0x00 */ s32 cols;
    /* 0x04 */ s32 rows;
    /* 0x08 */ s32 frame;
    /* 0x0C */ xy_t* vtxData;
    /* 0x10 */ Vtx* vtxFrame1;
    /* 0x14 */ Vtx* vtxFrame2;
    /* 0x18 */ Mtx projection;
    /* 0x58 */ Mtx modelView1;
    /* 0x98 */ Mtx modelView2;
    /* 0xD8 */ Gfx* gfxtbl;
    /* 0xDC */ u16* zBuffer;
} fbDemo;  // size = 0xE0

void fbdemo_init_gfx(fbDemo* this);
void fbdemo_init_data(fbDemo* this);
void fbdemo_cleanup(fbDemo* this);
fbDemo* fbdemo_init(fbDemo* this, s32 cols, s32 rows);
void fbdemo_update(fbDemo* this);
void fbdemo_draw(fbDemo* this, Gfx** gfxP);
void fbdemo_move_type_A(fbDemo* this);
void fbdemo_move(fbDemo* this);
s32 fbdemo_is_finish(fbDemo* this);


#endif