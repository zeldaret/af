#ifndef M_VIEW_H
#define M_VIEW_H

#include "ultra64.h"

struct PlayState;
struct GraphicsContext;

typedef struct PlayState1938 {
    /* 0x000 */ char unk000[0x28];
    /* 0x028 */ Vec3f unk_028;
    /* 0x034 */ char unk034[0x2C];
    /* 0x060 */ Mtx unk_060;
    /* 0x0A0 */ Mtx unk_0A0;
    /* 0x0E0 */ char unk0E0[0x40];
    /* 0x120 */ s32 unk_120;
    /* 0x124 */ char unk124[0x4];
} PlayState1938; // size = 0x128

typedef struct ScissorViewArg1 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} ScissorViewArg1; // size = 0x10

// void set_viewport();
void initView(PlayState1938* arg0, struct GraphicsContext* gfxCtx);
// void setLookAtView();
// void getLookAtView();
// void setScaleView();
// void getScaleView();
// void setPerspectiveView();
// void getPerspectiveView();
void setScissorView(PlayState1938* arg0, ScissorViewArg1* arg1);
// void getScissorView();
// void setScissorX();
// void setScissorOvl();
// void setScissor();
// void stretchViewInit();
// void do_stretch_view();
void showView(PlayState1938* arg0, s32 arg1, struct PlayState* play);
// void showPerspectiveView();
// void showOrthoView();
// void showOverLayView();
// void showPerspectiveOverLayView();
// void showOrthoView1();
void showView1(PlayState1938* arg0, s32 arg1, Gfx** gfx);

#endif
