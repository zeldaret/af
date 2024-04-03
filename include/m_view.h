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

typedef struct Stretch {
    /* 0x00 */ xyz_t targetRotate;
    /* 0x0C */ xyz_t targetScale;
    /* 0x18 */ f32 step;
    /* 0x1C */ xyz_t rotate;
    /* 0x28 */ xyz_t scale;
} Stretch; // size = 0x34

typedef struct View {   
    /* 0x000 */ s32 unk_000;
    /* 0x004 */ struct GraphicsContext* gfxCtx;
    /* 0x008 */ Viewport viewport;
    /* 0x018 */ f32 fovY;
    /* 0x01C */ f32 near;
    /* 0x020 */ f32 far;
    /* 0x024 */ f32 scale;
    /* 0x028 */ xyz_t eye;
    /* 0x034 */ xyz_t at;
    /* 0x040 */ xyz_t up;
    /* 0x050 */ Vp vp;
    /* 0x060 */ Mtx projectionMtx;
    /* 0x0A0 */ Mtx viewingMtx;
    /* 0x0E0 */ Mtx* projectionMtxPtr;
    /* 0x0E4 */ Mtx* viewingMtxPtr;
    /* 0x0E8 */ Stretch stretch;
    /* 0x11C */ u16 normal;
    /* 0x120 */ s32 flag;
    /* 0x124 */ s8 unk_124[0x4];
} View;


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
void set_viewport(Vp* vp, Viewport* viewport);
void initView(View* view, struct GraphicsContext* graph);
void setLookAtView(View* view, xyz_t* eye, xyz_t* center, xyz_t* up);
void getLookAtView(View* view, xyz_t* eye, xyz_t* center, xyz_t* up);
void setScaleView(View* view, f32 scale);
void getScaleView(View* view, f32* scale);
void setPerspectiveView(View* view, f32 fovY, f32 near, f32 far);
void getPerspectiveView(View* view, f32* fovY, f32* near, f32* far);
void setScissorView(View* view, Viewport* viewport);
void getScissorView(View* view, Viewport* viewport);
void setScissorX(Gfx** gfxP, s32 leftX, s32 topY, s32 rightX, s32 bottomY);
void setScissorOvl(View* view, Gfx** gfxP);
void setScissor(View* view);
s32 stretchViewInit(View* view);
s32 do_stretch_view(View* view, Mtx* mtx);
s32 showView(View* view, s32 flagMask);
s32 showPerspectiveView(View* view);
s32 showOrthoView(View* view);
s32 showOverLayView(View* view);
s32 showPerspectiveOverLayView(View* view);
s32 showOrthoView1(View* view, Gfx** gfxPtr);
s32 showView1(View* view, s32 flagMask, Gfx** gfxPtr);


#endif
