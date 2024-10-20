#include "m_fbdemo_triforce.h"
#include "gfxalloc.h"
#include "m_rcp.h"
#include "attributes.h"

extern u8 ef_wipe1_modelT[];
extern u8 ef_wipe2_modelT[];
extern u8 ef_wipe3_modelT[];

void fbdemo_triforce_startup(fbDemoTriforce* this) {
    this->finished = 0;
    this->frame = 16;

    if (this->direction != 0) {
        this->txt = 0;
    } else {
        this->txt = 0x224;
    }

    guPerspective(&this->perspMtx, &this->normal, 60.0f, 4.0f / 3.0f, 10.0f, 12800.0f, 1.0f);
    guLookAt(&this->lookAtMtx, 0.0f, 0.0f, 400.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}

fbDemoTriforce* fbdemo_triforce_init(fbDemoTriforce* this) {
    bzero(this, sizeof(fbDemoTriforce));
    return this;
}

void fbdemo_triforce_setrate(s32* rate, f32 scale) {
    *rate = 548.0f * scale;
}

void fbdemo_triforce_move(fbDemoTriforce* this, s32 rate) {
    s32 moveRate;
    UNUSED s32 txt = this->txt;
    f32 temp = (1.0f - (this->txt / 548.0f));

    moveRate = this->frame + (s32)(12.0f * temp);

    if (this->direction != 0) {

        this->txt += (moveRate << 1) / rate;
        if (this->txt >= 548) {
            this->txt = 548;
            this->finished = TRUE;
        }
    } else {
        this->txt -= (moveRate << 1) / rate;
        if (this->txt <= 0) {
            this->txt = 0;
            this->finished = TRUE;
        }
    }
}

void fbdemo_triforce_draw(fbDemoTriforce* this, Gfx** gfxP) {
    Gfx* gfx = *gfxP;
    Gfx* scroll;
    f32 scale;

    gDPPipeSync(gfx++);
    scroll = gfx_tex_scroll2(&gfx, this->txt, 0, 16, 4);
    gSPSegment(gfx++, G_MWO_SEGMENT_9, scroll);
    gSPMatrix(gfx++, &this->perspMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPPerspNormalize(gfx++, this->normal);
    gSPMatrix(gfx++, &this->lookAtMtx, G_MTX_MUL | G_MTX_PROJECTION);

    scale = 0.019f;

    if (1.0f != scale) {
        Mtx* mtxBuf;

        mtxBuf = gfxalloc(&gfx, sizeof(Mtx));

        guScale(mtxBuf, 0.019f, 0.019f, 1.0f);
        gSPMatrix(gfx++, mtxBuf, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    }

    switch (this->textureNo) {
        case 0:
            gSPDisplayList(gfx++, ef_wipe1_modelT);
            break;
        case 1:
            gSPDisplayList(gfx++, ef_wipe2_modelT);
            break;
        case 2:
            gSPDisplayList(gfx++, ef_wipe3_modelT);
            break;
    }
    gDPPipeSync(gfx++);
    *gfxP = gfx;
}

u8 fbdemo_triforce_is_finish(fbDemoTriforce* this) {
    return this->finished;
}

void fbdemo_triforce_settype(fbDemoTriforce* this, s32 type) {
    this->textureNo = ((type & 0x80) != 0) ? 1 : ((type & 0x40) != 0 ? 2 : 0);

    if ((type & 0xF) == 1) {
        this->direction = 0;
    } else {
        this->direction = 1;
    }
}

void fbdemo_triforce_setcolor_rgba8888(UNUSED fbDemoTriforce* this, UNUSED u32* rgba) {
}
