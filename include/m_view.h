#ifndef M_VIEW_H
#define M_VIEW_H

#include "ultra64.h"
#include "z64math.h"
#include "unk.h"

struct Game_Play;
struct GraphicsContext;

typedef struct Game_Play1938 {
    /* 0x000 */ UNK_TYPE1 unk_000[0x8];
    /* 0x008 */ s32 unk_008;
    /* 0x00C */ s32 unk_00C;
    /* 0x010 */ s32 unk_010;
    /* 0x018 */ s32 unk_014;
    /* 0x01C */ UNK_TYPE1 unk_018[0x10];
    /* 0x028 */ xyz_t unk_028;
    /* 0x034 */ UNK_TYPE1 unk_034[0x1C];
    /* 0x050 */ Vp vp;
    /* 0x060 */ Mtx unk_060;
    /* 0x0A0 */ Mtx unk_0A0;
    /* 0x0E0 */ UNK_TYPE1 unk_0E0[0x40];
    /* 0x120 */ s32 unk_120;
    /* 0x124 */ UNK_TYPE1 unk_124[0x4];
} Game_Play1938; // size = 0x128

typedef struct ScissorViewArg1 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} ScissorViewArg1; // size = 0x10

// void set_viewport();
void initView(Game_Play1938* arg0, struct GraphicsContext* gfxCtx);
// void setLookAtView();
// void getLookAtView();
// void setScaleView();
// void getScaleView();
// void setPerspectiveView();
// void getPerspectiveView();
void setScissorView(Game_Play1938* arg0, ScissorViewArg1* arg1);
// void getScissorView();
// void setScissorX();
// void setScissorOvl();
// void setScissor();
// void stretchViewInit();
// void do_stretch_view();
void showView(Game_Play1938* arg0, s32 arg1, struct Game_Play* game_play);
// void showPerspectiveView();
// void showOrthoView();
// void showOverLayView();
// void showPerspectiveOverLayView();
// void showOrthoView1();
void showView1(Game_Play1938* arg0, s32 arg1, Gfx** gfx);

#endif
