#include "m_fbdemo_wipe1.h"
#include "m_common_data.h"
#include "m_rcp.h"

extern Gfx wipe1_modelT[]; // TODO: extract

fbDemoWipe1* fbdemo_wipe1_init(fbDemoWipe1* this) {
    bzero(this, sizeof(fbDemoWipe1));
    return this;
}

void fbdemo_wipe1_move(fbDemoWipe1* this, s32 rate) {
    if (this->direction != 0) {
        this->texY += (common_data.wipeRate * 3) / rate;
        if (this->texY >= (s32)(153.0f * (1 << 2))) {
            this->texY = (s32)(153.0f * (1 << 2));
            this->finished = TRUE;
        }
    } else {
        this->texY -= (common_data.wipeRate * 3) / rate;
        if (this->texY <= (s32)(83.25f * (1 << 2))) {
            this->texY = (s32)(83.25f * (1 << 2));
            this->finished = TRUE;
        }
    }
}

void fbdemo_wipe1_draw(fbDemoWipe1* this, Gfx** gfxP) {
    Gfx* gfx = *gfxP;
    Mtx* modelView;
    UNUSED s32 pad[5];

    Gfx* texScroll;

    modelView = this->modelView[this->frame];
    this->frame ^= 1;

    guScale(&modelView[0], 0.56f, 0.56f, 1.0f);
    guRotate(&modelView[1], 0.0f, 0.0f, 0.0f, 1.0f);
    guTranslate(&modelView[2], 0.0f, 0.0f, 0.0f);
    gDPPipeSync(gfx++);

    texScroll = gfx_tex_scroll2(&gfx, this->texX, this->texY, 0, 0);
    gSPSegment(gfx++, 8, texScroll);

    gDPSetPrimColor(gfx++, 0, 0x80, this->color.r, this->color.g, this->color.b, 255);

    gSPMatrix(gfx++, &this->projection, G_MTX_LOAD | G_MTX_PROJECTION);
    gSPPerspNormalize(gfx++, this->normal);

    gSPMatrix(gfx++, &this->lookAt, G_MTX_MUL | G_MTX_PROJECTION);
    gSPMatrix(gfx++, &modelView[0], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPMatrix(gfx++, &modelView[1], G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    gSPMatrix(gfx++, &modelView[2], G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);

    gSPDisplayList(gfx++, wipe1_modelT);
    gDPPipeSync(gfx++);
    *gfxP = gfx;
}

void fbdemo_wipe1_startup(fbDemoWipe1* this) {
    this->finished = 0;

    if (this->direction != 0) {
        this->texY = (s32)(83.25f * (1 << 2));
    } else {
        this->texY = (s32)(153.0f * (1 << 2));
    }

    guPerspective(&this->projection, &this->normal, 60.0f, 4.0f / 3.0f, 10.0f, 12800.0f, 1.0f);
    guLookAt(&this->lookAt, 0.0f, 0.0f, 400.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}

void fbdemo_wipe1_settype(fbDemoWipe1* this, s32 type) {
    if (type == 1) {
        this->direction = 1;
        this->texY = 0x14D;
        return;
    }
    this->direction = 0;
    this->texY = 0x264;
}

void fbdemo_wipe1_setcolor_rgba8888(fbDemoWipe1* this, u32 color) {
    this->color.rgba = color;
}

void fbdemo_wipe1_setaltcolor_rgba8888(fbDemoWipe1* this, u32 color) {
    this->altColor.rgba = color;
}

u8 fbdemo_wipe1_is_finish(fbDemoWipe1* this) {
    return this->finished;
}
