#include "m_fbdemo_fade.h"
#include "m_common_data.h"
#include "macros.h"

Gfx fbdemo_fade_gfx_init[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                          G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_1PRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_CLD_SURF | G_RM_CLD_SURF2),
    gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PRIMITIVE),
    gsSPEndDisplayList(),
};

fbDemoFade* fbdemo_fade_init(fbDemoFade* this) {
    bzero(this, sizeof(fbDemoFade));
    return this;
}

void fbdemo_fade_move(fbDemoFade* this, s32 rate) {
    f32 ftimer;
    s32 alpha;

    if (this->timer != 0) {
        this->timer -= 1;
        return;
    }

    if (this->type != 7) {
        this->frame += rate;
        if (this->frame >= common_data.fadeRate) {
            this->frame = common_data.fadeRate;
            this->isDone = 1;
        }
        ftimer = (f32)this->frame;
        if (ftimer < 0.0f) {
            ftimer = 0.0f;
        }

        alpha = (255.0f * ftimer) / common_data.fadeRate;
        if (this->type == 1) {
            this->color.a = 255 - alpha;
        } else {
            this->color.a = alpha;
        }
    }
}

void fbdemo_fade_draw(fbDemoFade* this, Gfx** gfxP) {
    Gfx* gfx;
    Color_RGBA8_u32* color = &this->color;

    if (color->a != 0) {
        gfx = *gfxP;
        gSPDisplayList(gfx++, fbdemo_fade_gfx_init);
        gDPSetPrimColor(gfx++, 0, 0, color->r, color->g, color->b, color->a);
        gDPFillRectangle(gfx++, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        gDPPipeSync(gfx++);
        *gfxP = gfx;
    }
}

void fbdemo_fade_startup(fbDemoFade* this) {
    static s16 start_frame[] = { 0x0000, 0xFFFA, 0x0000, 0x0000, 0x0000, 0x0000,
                                 0xFFAB, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 };

    static s32 start_color[] = { 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

    u8 type = this->type;

    this->color.a = start_color[type];
    this->frame = start_frame[type];

    this->isDone = 0;
    if (this->type == 1) {
        this->timer = 5;
    }
}

void fbdemo_fade_settype(fbDemoFade* this, int type) {
    this->type = type;
}

void fbdemo_fade_setcolor_rgba8888(fbDemoFade* this, u32 color) {
    this->color.rgba = color;
}

u8 fbdemo_fade_is_finish(fbDemoFade* this) {
    return this->isDone;
}
