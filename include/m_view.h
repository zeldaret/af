#ifndef M_VIEW_H
#define M_VIEW_H

#include "ultra64.h"
#include "z64math.h"
#include "unk.h"

struct Game_Play;
struct GraphicsContext;

typedef struct Viewport {
    /* 0x00 */ s32 topY;    // uly (upper left y)
    /* 0x04 */ s32 bottomY; // lry (lower right y)
    /* 0x08 */ s32 leftX;   // ulx (upper left x)
    /* 0x0C */ s32 rightX;  // lrx (lower right x)
} Viewport; // size = 0x10

typedef struct Game_Play1938 {
    /* 0x000 */ UNK_TYPE1 unk_000[0x8];
    /* 0x008 */ Viewport viewport;
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


#define SET_FULLSCREEN_VIEWPORT(view)      \
    {                                      \
        Viewport viewport;                 \
        viewport.bottomY = SCREEN_HEIGHT;  \
        viewport.rightX = SCREEN_WIDTH;    \
        viewport.topY = 0;                 \
        viewport.leftX = 0;                \
        setScissorView(view, &viewport); \
    }                                      \
    (void)0

// void set_viewport();
void initView(Game_Play1938* arg0, struct GraphicsContext* gfxCtx);
// void setLookAtView();
// void getLookAtView();
// void setScaleView();
// void getScaleView();
// void setPerspectiveView();
// void getPerspectiveView();
void setScissorView(Game_Play1938* arg0, Viewport* arg1);
// void getScissorView();
// void setScissorX();
// void setScissorOvl();
// void setScissor();
// void stretchViewInit();
// void do_stretch_view();
void showView(Game_Play1938* arg0, s32 arg1);
// void showPerspectiveView();
// void showOrthoView();
// void showOverLayView();
// void showPerspectiveOverLayView();
// void showOrthoView1();
void showView1(Game_Play1938* arg0, s32 arg1, Gfx** gfx);

#endif
