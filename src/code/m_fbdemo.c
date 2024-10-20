#include "m_fbdemo.h"
#include "libc64/sleep.h"
#include "libc64/malloc.h"
#include "attributes.h"

Gfx fbdemo_gfx_init[] = {
    gsDPPipeSync(),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                          G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_1PRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_AA_OPA_SURF | G_RM_AA_OPA_SURF2),
    gsSPEndDisplayList(),
};

#define SET_VERTEX(vtx, x, y, z, s, t, nx, ny, nz, alpha) \
    {                                                     \
        Vtx_tn* vtxn = &(vtx)->n;                         \
        vtxn->ob[0] = (x);                                \
        vtxn->ob[1] = (y);                                \
        vtxn->ob[2] = (z);                                \
        vtxn->flag = 0;                                   \
        vtxn->tc[0] = (s);                                \
        vtxn->tc[1] = (t);                                \
        vtxn->n[0] = (nx);                                \
        vtxn->n[1] = (ny);                                \
        vtxn->n[2] = (nz);                                \
        vtxn->a = (alpha);                                \
    }

void fbdemo_init_gfx(fbDemo* this) {
    s32 col;
    s32 col2;
    s32 colTex;
    s32 rowTex;
    s32 row;
    s32 frame;
    Vtx* vtx;
    Gfx* gfx;

    guMtxIdent(&this->modelView1);
    guMtxIdent(&this->modelView2);
    guOrtho(&this->projection, 0.0f, 320, 240, 0.0f, -1000.0f, 1000.0f, 1.0f);

    for (frame = 0; frame < 2; frame++) {
        this->frame = frame;
        vtx = (this->frame == 0) ? this->vtxFrame1 : this->vtxFrame2;
        for (rowTex = 0, row = 0; row < (this->rows + 1); rowTex += 0x20, row++) {
            for (colTex = 0, col = 0; col < (this->cols + 1); col++, colTex += 0x20) {
                SET_VERTEX(vtx++, col * 0x20, row * 0x20, -5, colTex << 6, rowTex << 6, 0, 0, 120, 255);
            }
        }
    }

    gfx = this->gfxtbl;

    for (rowTex = 0, row = 0; row < this->rows; rowTex += 0x20, row++) {
        gSPVertex(gfx++, SEGMENT_ADDR(G_MWO_SEGMENT_A, (u32)row * (this->cols + 1) * sizeof(Vtx)), 2 * (this->cols + 1),
                  0);

        colTex = 0;
        col = 0;
        col2 = 0;
        while (col < this->cols) {
            gDPPipeSync(gfx++);

            gDPLoadTextureTile(gfx++, SEGMENT_ADDR(G_MWO_SEGMENT_B, 0), G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, 240, colTex,
                               rowTex, colTex + 0x20, rowTex + 0x20, 0, G_TX_NOMIRROR | G_TX_WRAP,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

            gSP1Quadrangle(gfx++, col2, col2 + 1, col2 + (this->cols) + 2, this->cols + 1 + col2, 0);

            colTex += 0x20;
            col2++;
            col++;
        }
    }

    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
}

void fbdemo_init_data(fbDemo* this) {
    s32 col;
    s32 row;

    for (row = 0; row < this->rows + 1; row++) {
        for (col = 0; col < this->cols + 1; col++) {
            (this->vtxData + col + row * (this->cols + 1))->x = col * 0x20;
            (this->vtxData + col + row * (this->cols + 1))->y = row * 0x20;
        }
    }
}

void fbdemo_cleanup(fbDemo* this) {
    msleep(100);

    if (this->vtxData != NULL) {
        free(this->vtxData);
        this->vtxData = NULL;
    }
    if (this->vtxFrame1 != NULL) {
        free(this->vtxFrame1);
        this->vtxFrame1 = NULL;
    }
    if (this->vtxFrame2 != NULL) {
        free(this->vtxFrame2);
        this->vtxFrame2 = NULL;
    }
    if (this->gfxtbl != NULL) {
        free(this->gfxtbl);
        this->gfxtbl = NULL;
    }
}

fbDemo* fbdemo_init(fbDemo* this, s32 cols, s32 rows) {
    bzero(this, sizeof(fbDemo));

    this->cols = cols;
    this->rows = rows;

    this->frame = 0;
    this->vtxData = malloc((cols + 1) * sizeof(xy_t) * (rows + 1));

    this->vtxFrame1 = malloc((cols + 1) * sizeof(Vtx) * (rows + 1));
    this->vtxFrame2 = malloc((cols + 1) * sizeof(Vtx) * (rows + 1));

    this->gfxtbl = malloc((this->rows * (this->cols * 9 + 1) + 2) * sizeof(Gfx));

    if ((this->vtxData == NULL) || (this->vtxFrame1 == NULL) || (this->vtxFrame2 == NULL) || (this->gfxtbl == NULL)) {
        if (this->vtxData != NULL) {
            free(this->vtxData);
            this->vtxData = NULL;
        }

        if (this->vtxFrame1 != NULL) {
            free(this->vtxFrame1);
            this->vtxFrame1 = NULL;
        }

        if (this->vtxFrame2 != NULL) {
            free(this->vtxFrame2);
            this->vtxFrame2 = NULL;
        }

        if (this->gfxtbl != NULL) {
            free(this->gfxtbl);
            this->gfxtbl = NULL;
        }

        return NULL;
    }

    fbdemo_init_gfx(this);
    fbdemo_init_data(this);
    this->frame = 0;

    return this;
}

void fbdemo_update(fbDemo* this) {
    s32 col;
    s32 row;
    Vtx* vtx;

    for (row = 0; row < this->rows + 1; row++) {
        for (col = 0; col < this->cols + 1; col++) {
            vtx = (this->frame == 0) ? this->vtxFrame1 : this->vtxFrame2;
            (vtx + col + row * (this->cols + 1))->n.ob[0] = (this->vtxData + col + row * (this->cols + 1))->x;

            vtx = (this->frame == 0) ? this->vtxFrame1 : this->vtxFrame2;
            (vtx + col + row * (this->cols + 1))->n.ob[1] = (this->vtxData + col + row * (this->cols + 1))->y;
        }
    }
}

void fbdemo_draw(fbDemo* this, Gfx** gfxP) {
    Gfx* gfx = *gfxP;

    gSPDisplayList(gfx++, fbdemo_gfx_init);
    fbdemo_update(this);
    gSPMatrix(gfx++, &this->projection, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(gfx++, &this->modelView1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(gfx++, G_MWO_SEGMENT_A, this->frame == 0 ? this->vtxFrame1 : this->vtxFrame2);
    gSPSegment(gfx++, G_MWO_SEGMENT_B, this->zBuffer);
    gSPDisplayList(gfx++, fbdemo_gfx_init);
    gSPDisplayList(gfx++, this->gfxtbl);
    gDPPipeSync(gfx++);
    this->frame ^= 1;
    *gfxP = gfx;
}

void fbdemo_move_type_A(fbDemo* this) {
    s32 row;
    s32 col;
    f32 diffX;
    f32 diffY;
    f32 scale;

    for (row = 0; row < this->rows + 1; row++) {
        for (col = 0; col < this->cols + 1; col++) {
            diffX = (this->vtxData + col + row * (this->cols + 1))->x - (this->vtxData + 5 + 4 * (this->cols + 1))->x;
            diffY = (this->vtxData + col + row * (this->cols + 1))->y - (this->vtxData + 5 + 4 * (this->cols + 1))->y;
            scale = (SQ(diffX) + SQ(diffY)) / 100.0f;
            if (scale != 0.0f) {
                if (scale < 1.0f) {
                    scale = 1.0f;
                }
                (this->vtxData + col + row * (this->cols + 1))->x -= diffX / scale;
                (this->vtxData + col + row * (this->cols + 1))->y -= diffY / scale;
            }
        }
    }
}

void fbdemo_move(UNUSED fbDemo* this) {
}

s32 fbdemo_is_finish(UNUSED fbDemo* this) {
    return FALSE;
}
