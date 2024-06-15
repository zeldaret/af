#include "PreRender.h"

#include "libc/stdbool.h"
#include "PR/gs2dex.h"

#include "color.h"
#include "gfx.h"
#include "gfxalloc.h"
#include "macros.h"
#include "sys_ucode.h"

typedef struct {
    /* 0x00 */ void* timg;
    /* 0x04 */ void* tlut;
    /* 0x08 */ u16 width;
    /* 0x0A */ u16 height;
    /* 0x0C */ u8 fmt;
    /* 0x0D */ u8 siz;
    /* 0x0E */ u16 tt;
    /* 0x10 */ u16 tlutCount;
    /* 0x14 */ f32 x;
    /* 0x18 */ f32 y;
    /* 0x1C */ f32 xScale;
    /* 0x20 */ f32 yScale;
    /* 0x24 */ u32 flags;
} Wallpaper; // size = 0x28

void wallpaper_draw1(Wallpaper* wallpaper, Gfx** glistpp) {
    Gfx* glistp;
    uObjBg* bg;
    u32 alphaCompare;
    Gfx* gfxHead;
    u32 loadS2DEX2;

    loadS2DEX2 = (wallpaper->flags & WALLPAPER_FLAGS_LOAD_S2DEX2) != 0;
    alphaCompare = (wallpaper->flags & WALLPAPER_FLAGS_AC_THRESHOLD) ? G_AC_THRESHOLD : G_AC_NONE;

    gfxHead = *glistpp;
    bg = gfxalloc(&gfxHead, sizeof(uObjBg));
    glistp = gfxHead;

    bg->b.imageX = 0;
    bg->b.imageW = (wallpaper->width * (1 << 2)) + 1;
    bg->b.frameX = wallpaper->x * (1 << 2);

    bg->b.imageY = 0;
    bg->b.imageH = (wallpaper->height * (1 << 2)) + 1;
    bg->b.frameY = wallpaper->y * (1 << 2);

    bg->b.imagePtr = wallpaper->timg;
    bg->b.imageLoad = G_BGLT_LOADTILE;
    bg->b.imageFmt = wallpaper->fmt;
    bg->b.imageSiz = wallpaper->siz;
    bg->b.imagePal = 0;
    bg->b.imageFlip = 0;

    if (loadS2DEX2) {
        gSPLoadUcode(glistp++, ucode_GetSpriteTextStart(), ucode_GetSpriteDataStart());
    }

    if ((wallpaper->fmt == G_IM_FMT_CI) && (wallpaper->tlut != NULL)) {
        gDPLoadTLUT(glistp++, wallpaper->tlutCount, 256, wallpaper->tlut);
    } else {
        gDPPipeSync(glistp++);
    }

    if (wallpaper->flags & WALLPAPER_FLAGS_COPY) {
        bg->b.frameW = wallpaper->width * (1 << 2);
        bg->b.frameH = wallpaper->height * (1 << 2);

        guS2DInitBg(bg);

        if (!(wallpaper->flags & WALLPAPER_FLAGS_1)) {
            gDPSetOtherMode(glistp++, wallpaper->tt | G_CYC_COPY, alphaCompare);
        }

        gSPBgRectCopy(glistp++, bg);
    } else {
        bg->b.frameW = (s16)((u32)(wallpaper->width * (1 << 2)) * wallpaper->xScale);
        bg->b.frameH = (s16)((u32)(wallpaper->height * (1 << 2)) * wallpaper->yScale);
        bg->b.tmemW = (s16)(1024.0f / wallpaper->xScale);
        bg->b.tmemH = (s16)(1024.0f / wallpaper->yScale);
        bg->s.imageYorig = bg->b.imageY;

        if (!(wallpaper->flags & WALLPAPER_FLAGS_1)) {
            gDPSetOtherMode(glistp++, wallpaper->tt | G_AD_DISABLE | G_CD_DISABLE | G_TC_FILT,
                            AA_EN | CVG_X_ALPHA | ALPHA_CVG_SEL |
                                GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_BL, G_BL_1MA) |
                                GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_BL, G_BL_1MA) | alphaCompare);
        }

        if (!(wallpaper->flags & WALLPAPER_FLAGS_2)) {
            gDPSetCombineLERP(glistp++, 0, 0, 0, TEXEL0, 0, 0, 0, 1, 0, 0, 0, TEXEL0, 0, 0, 0, 1);
        }

        gSPObjRenderMode(glistp++, G_OBJRM_ANTIALIAS | G_OBJRM_BILERP);
        gSPBgRect1Cyc(glistp++, bg);
    }

    gDPPipeSync(glistp++);

    if (loadS2DEX2) {
        gSPLoadUcode(glistp++, ucode_GetPolyTextStart(), ucode_GetPolyDataStart());
    }

    *glistpp = glistp;
}

void wallpaper_draw(Gfx** glistpp, void* timg, void* tlut, u16 width, u16 height, u8 fmt, u8 siz, u16 tt, u16 tlutCount,
                    f32 x, f32 y, f32 xScale, f32 yScale, u32 flags) {
    Wallpaper wallpaper;
    Wallpaper* wallpaperPtr = &wallpaper;

    wallpaper.timg = timg;
    wallpaper.tlut = tlut;
    wallpaper.width = width;
    wallpaper.height = height;
    wallpaper.fmt = fmt;
    wallpaper.siz = siz;
    wallpaper.tt = tt;
    wallpaper.tlutCount = tlutCount;
    wallpaper.x = x;
    wallpaper.y = y;
    wallpaper.xScale = xScale;
    wallpaper.yScale = yScale;
    wallpaper.flags = flags;

    wallpaper_draw1(wallpaperPtr, glistpp);
}

Gfx* gfx_SetUpCFB(Gfx* glistp, void* imgDst, u32 width, u32 height) {
    gDPPipeSync(glistp);
    gDPSetColorImage(glistp + 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, imgDst);
    gDPSetScissor(glistp + 2, G_SC_NON_INTERLACE, 0, 0, width, height);

    return glistp + 3;
}

void PreRender_setup_savebuf(PreRender* this, s32 width, s32 height, void* fbuf, void* zbuf, void* cvg) {
    this->width_save = width;
    this->height_save = height;
    this->fbuf_save = fbuf;
    this->cvg_save = cvg;
    this->zbuf_save = zbuf;
    this->ulx_save = 0;
    this->uly_save = 0;
    this->lrx_save = width - 1;
    this->lry_save = height - 1;
}

void PreRender_init(PreRender* this) {
    bzero(this, sizeof(PreRender));
    ListAlloc_Init(&this->alloc);
}

void PreRender_setup_renderbuf(PreRender* this, s32 width, s32 height, void* fbuf, void* zbuf) {
    this->width = width;
    this->height = height;
    this->fbuf = fbuf;
    this->zbuf = zbuf;
    this->ulx = 0;
    this->uly = 0;
    this->lrx = width - 1;
    this->lry = height - 1;
}

void PreRender_cleanup(PreRender* this) {
    ListAlloc_FreeAll(&this->alloc);
}

void PreRender_TransBufferCopy(PreRender* this, Gfx** glistpp, void* arg2, void* arg3, u32 useThresholdAlphaCompare) {
    Gfx* glistp = *glistpp;
    u32 flags;

    glistp = gfx_SetUpCFB(glistp, arg3, this->width, this->height);

    flags = WALLPAPER_FLAGS_LOAD_S2DEX2 | WALLPAPER_FLAGS_COPY;
    if (useThresholdAlphaCompare == true) {
        flags |= WALLPAPER_FLAGS_AC_THRESHOLD;
    }

    wallpaper_draw(&glistp, arg2, NULL, this->width, this->height, G_IM_FMT_RGBA, G_IM_SIZ_16b, G_TT_NONE, 0, 0.0f,
                   0.0f, 1.0f, 1.0f, flags);

    *glistpp = gfx_SetUpCFB(glistp, this->fbuf, this->width, this->height);
}

void PreRender_TransBuffer(PreRender* this, Gfx** glistpp, void* arg2, void* arg3) {
    PreRender_TransBufferCopy(this, glistpp, arg2, arg3, false);
}

void PreRender_TransBuffer1_env(PreRender* this, Gfx** glistpp, void* arg2, void* arg3, s32 envR, s32 envG, s32 envB,
                                s32 envA) {
    Gfx* glistp = *glistpp;

    gDPPipeSync(glistp++);

    {
        u32 mode0;
        u32 mode1;

        if (envA == 255) {
            mode0 = G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                    G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE;
            mode1 = G_AC_NONE | G_ZS_PRIM | G_RM_OPA_SURF | G_RM_OPA_SURF2;
        } else {
            mode0 = G_AD_NOISE | G_CD_NOISE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE | G_TD_CLAMP |
                    G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE;
            mode1 = G_AC_NONE | G_ZS_PRIM | G_RM_CLD_SURF | G_RM_CLD_SURF2;
        }

        gDPSetOtherMode(glistp++, mode0, mode1);
    }

    gDPSetEnvColor(glistp++, envR, envG, envB, envA);
    gDPSetCombineLERP(glistp++, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0,
                      ENVIRONMENT);

    glistp = gfx_SetUpCFB(glistp, arg3, this->width, this->height);
    wallpaper_draw(&glistp, arg2, NULL, this->width, this->height, G_IM_FMT_RGBA, G_IM_SIZ_16b, G_TT_NONE, 0, 0.0f,
                   0.0f, 1.0f, 1.0f, WALLPAPER_FLAGS_1 | WALLPAPER_FLAGS_2 | WALLPAPER_FLAGS_LOAD_S2DEX2);
    *glistpp = gfx_SetUpCFB(glistp, this->fbuf, this->width, this->height);
}

void PreRender_TransBuffer1(PreRender* this, Gfx** glistpp, void* arg2, void* arg3) {
    PreRender_TransBuffer1_env(this, glistpp, arg2, arg3, 255, 255, 255, 255);
}

void PreRender_TransBuffer2(PreRender* this, Gfx** glistpp, void* arg2, void* arg3) {
    Gfx* glistp = *glistpp;
    s32 rowsRemaining;
    s32 curRow;
    s32 nRows;
    s32 pad UNUSED;

    gDPPipeSync(glistp++);
    gDPSetOtherMode(glistp++,
                    G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                        G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                    G_AC_NONE | G_ZS_PRIM | G_RM_PASS | G_RM_OPA_CI2);

    // Set the combiner to draw the texture as-is, discarding alpha channel
    gDPSetCombineLERP(glistp++, 0, 0, 0, TEXEL0, 0, 0, 0, 0, 0, 0, 0, TEXEL0, 0, 0, 0, 0);
    // Set the destination color image to the provided address
    gDPSetColorImage(glistp++, G_IM_FMT_I, G_IM_SIZ_8b, this->width, arg3);
    // Set up a scissor based on the source image
    gDPSetScissor(glistp++, G_SC_NON_INTERLACE, 0, 0, this->width, this->height);

    // Calculate the max number of rows that can fit into TMEM at once
    nRows = TMEM_SIZE / (this->width * G_IM_SIZ_16b_BYTES);

    // Set up the number of remaining rows
    rowsRemaining = this->height;
    curRow = 0;
    while (rowsRemaining > 0) {
        s32 uls = 0;
        s32 lrs = this->width - 1;
        s32 ult;
        s32 lrt;

        // Make sure that we don't load past the end of the source image
        if (nRows > rowsRemaining) {
            nRows = rowsRemaining;
        }

        // Determine the upper and lower bounds of the rect to draw
        ult = curRow;
        lrt = curRow + nRows - 1;

        // Load a horizontal strip of the source image in IA16 format. Since the source image is stored in memory as
        // RGBA16, the bits are reinterpreted into IA16:
        //
        // r     g      b     a
        // 11111 111 11 11111 1
        // i         a
        // 11111 111 11 11111 1
        //
        // I = (r << 3) | (g >> 2)
        // A = (g << 6) | (b << 1) | a
        //
        // Since it is expected that r = g = b = cvg in the source image, this results in
        //  I = (cvg << 3) | (cvg >> 2)
        // This expands the 5-bit coverage into an 8-bit value
        gDPLoadTextureTile(glistp++, arg2, G_IM_FMT_IA, G_IM_SIZ_16b, this->width, this->height, uls, ult, lrs, lrt, 0,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                           G_TX_NOLOD);

        // Draw that horizontal strip to the destination image. With the combiner and blender configuration set above,
        // the intensity (I) channel of the loaded IA16 texture will be written as-is to the I8 color image, each pixel
        // in the final image is
        //  I = (cvg << 3) | (cvg >> 2)
        gSPTextureRectangle(glistp++, uls << 2, ult << 2, (lrs + 1) << 2, (lrt + 1) << 2, G_TX_RENDERTILE, uls << 5,
                            ult << 5, 1 << 10, 1 << 10);

        // Update the number of rows remaining and index of the row being drawn
        curRow += nRows;
        rowsRemaining -= nRows;
    }

    // Reset the color image to the current framebuffer

    *glistpp = gfx_SetUpCFB(glistp, this->fbuf, this->width, this->height);
}

void PreRender_ShowCoveredge(Gfx** glistpp, s32 ulx, s32 uly, s32 lrx, s32 lry) {
    Gfx* glistp = *glistpp;

    gDPPipeSync(glistp++);
    // Set the blend color to full white and set maximum depth
    gDPSetBlendColor(glistp++, 255, 255, 255, 8);
    gDPSetPrimDepth(glistp++, 0xFFFF, 0xFFFF);

    // Uses G_RM_VISCVG to blit the coverage values to the framebuffer
    //
    // G_RM_VISCVG is the following special render mode:
    //  IM_RD    : Allow read-modify-write operations on the framebuffer
    //  FORCE_BL : Apply the blender to all pixels rather than just edges, skip the division step of the blend formula
    //  (G_BL_CLR_IN * G_BL_0 + G_BL_CLR_BL * G_BL_A_MEM) = G_BL_CLR_BL * G_BL_A_MEM
    //
    // G_BL_A_MEM ("memory alpha") is coverage, therefore this blender configuration emits only the coverage (up to a
    // constant factor determined by blend color) and discards any pixel colors. For an RGBA16 framebuffer, each of the
    // three color channels r,g,b will receive the coverage value individually.
    //
    // Also disables other modes such as alpha compare and texture perspective correction
    gDPSetOtherMode(glistp++,
                    G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                        G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                    G_AC_NONE | G_ZS_PRIM | G_RM_VISCVG | G_RM_VISCVG2);

    // Fill rectangle to obtain the coverage values as an RGBA16 image
    gDPFillRectangle(glistp++, ulx, uly, lrx, lry);
    gDPPipeSync(glistp++);

    *glistpp = glistp;
}

#ifdef NON_MATCHING
void PreRender_CopyRGBC(PreRender* this, Gfx** gfxp, s32 width, s32 height) {
    Gfx* gfx = *gfxp;

    u32 remain;
    u32 term;

    u32 uls;
    u32 ult;
    u32 lrs;
    u32 lrt;

    u32 w;
    u32 h;
    u32 lrs_max;
    u32 lrt_max;

    if ((this->width_save + width) <= 0 || (this->height_save + height) <= 0) {
        return;
    }

    gDPPipeSync(gfx++);

    gfx = gfx_SetUpCFB(gfx, this->fbuf, this->width, this->height);

    gDPSetOtherMode(gfx++,
                    G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                        G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                    G_AC_NONE | G_ZS_PRIM | G_RM_OPA_SURF | G_RM_OPA_SURF2);
    gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, 0, 0, 0, 1, 0, 0, 0, TEXEL0, 0, 0, 0, 1);

    wallpaper_draw(&gfx, this->fbuf_save, 0, this->width_save, this->height_save, 0, 2, 0, 0, width, height, 1.0f, 1.0f,
                   11);

    gfx = gfx_SetUpCFB(gfx, this->fbuf_save, this->width_save, this->height_save);

    PreRender_ShowCoveredge(&gfx, 0, 0, this->width_save, this->height_save);

    gfx = gfx_SetUpCFB(gfx, this->fbuf, this->width, this->height);

    gDPSetOtherMode(gfx++,
                    G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                        G_TD_CLAMP | G_TP_NONE | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                    G_AC_NONE | G_ZS_PRIM | AA_EN | IM_RD | CVG_DST_WRAP | ZMODE_OPA | CVG_X_ALPHA | ALPHA_CVG_SEL |
                        FORCE_BL | G_RM_PASS | GBL_c2(G_BL_CLR_IN, G_BL_0, G_BL_CLR_MEM, G_BL_1));

    gDPSetCombineLERP(gfx++, 0, 0, 0, 0, 1, 0, TEXEL0, ENVIRONMENT, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);

    gDPSetEnvColor(gfx++, 255, 255, 255, 32);

    remain = (1 << 12) / (u32)(this->width_save * 2);

    if (width < 0) {
        uls = -width;
        lrs = 0;
    } else {
        uls = 0;
        lrs = width;
    }

    if (height < 0) {
        ult = -height;
        lrt = 0;
        term = this->height_save + height;
    } else {
        term = this->height_save;
        lrt = height;
        ult = 0;
    }

    w = (this->width_save + width);
    lrs_max = this->width_save;

    while (term > 0) {
        if (remain > term) {
            remain = term;
        }

        lrt_max = ult + remain;
        if (lrt_max > this->width_save) {
            lrt_max = this->width_save;
            remain = this->width_save - ult;
        }

        if ((lrt_max && lrt_max) && lrt_max) {}
        h = lrt + remain;

        gDPLoadTextureTile(gfx++, this->fbuf_save, G_IM_FMT_I, G_IM_SIZ_8b, this->width_save * 2, this->height_save * 2,
                           uls * 2, ult, lrs_max * 2 - 1, lrt_max - 1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                           G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);

        gSPTextureRectangle(gfx++, lrs * 4, lrt * 4, w * 4, h * 4, G_TX_RENDERTILE, (uls * 2) << 5, ult << 5, 2 << 10,
                            1 << 10);

        term -= remain;
        ult += remain;
        lrt += remain;
    }
    gDPPipeSync(gfx++);
    *gfxp = gfx;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/PreRender/PreRender_CopyRGBC.s")
#endif

void PreRender_saveZBuffer(PreRender* this, Gfx** glistpp) {
    if ((this->zbuf_save != NULL) && (this->zbuf != NULL)) {
        PreRender_TransBuffer(this, glistpp, this->zbuf, this->zbuf_save);
    }
}

void PreRender_saveFrameBuffer(PreRender* this, Gfx** glistpp) {
    if ((this->fbuf_save != NULL) && (this->fbuf != NULL)) {
        PreRender_TransBuffer1(this, glistpp, this->fbuf, this->fbuf_save);
    }
}

void PreRender_saveCVG(PreRender* this, Gfx** glistpp) {
    PreRender_ShowCoveredge(glistpp, 0, 0, this->width, this->height);
    if (this->cvg_save != NULL) {
        PreRender_TransBuffer2(this, glistpp, this->fbuf, this->cvg_save);
    }
}

void PreRender_loadZBuffer(PreRender* this, Gfx** glistpp) {
    PreRender_TransBuffer(this, glistpp, this->zbuf_save, this->zbuf);
}

void PreRender_loadFrameBuffer(PreRender* this, Gfx** glistpp) {
    Gfx* glistp;
    s32 rowsRemaining;
    s32 curRow;
    s32 nRows;
    s32 rtile = 1;

    if (this->cvg_save != NULL) {
        glistp = *glistpp;

        gDPPipeSync(glistp++);
        gDPSetEnvColor(glistp++, 255, 255, 255, 32);
        // Effectively disable blending in both cycles. It's 2-cycle so that TEXEL1 can be used to point to a different
        // texture tile.
        gDPSetOtherMode(glistp++,
                        G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                            G_TD_CLAMP | G_TP_NONE | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                        G_AC_NONE | G_ZS_PRIM | AA_EN | CVG_DST_CLAMP | ZMODE_OPA | CVG_X_ALPHA |
                            GBL_c1(G_BL_CLR_IN, G_BL_0, G_BL_CLR_IN, G_BL_1) |
                            GBL_c2(G_BL_CLR_IN, G_BL_0, G_BL_CLR_IN, G_BL_1));

        // Set up the color combiner: first cycle: TEXEL0, TEXEL1 + ENVIRONMENT; second cycle: G_CC_PASS2
        gDPSetCombineLERP(glistp++, 0, 0, 0, TEXEL0, 1, 0, TEXEL1, ENVIRONMENT, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);

        nRows = (this->width > SCREEN_WIDTH) ? 2 : 4;

        rowsRemaining = this->height;
        curRow = 0;

        while (rowsRemaining > 0) {
            s32 uls = 0;
            s32 lrs = this->width - 1;
            s32 ult;
            s32 lrt;

            // Make sure that we don't load past the end of the source image
            if (nRows > rowsRemaining) {
                nRows = rowsRemaining;
            }

            // Determine the upper and lower bounds of the rect to draw
            ult = curRow;
            lrt = curRow + nRows - 1;

            // Load the frame buffer line
            gDPLoadMultiTile(glistp++, this->fbuf_save, 0x0000, G_TX_RENDERTILE, G_IM_FMT_RGBA, G_IM_SIZ_16b,
                             this->width, this->height, uls, ult, lrs, lrt, 0, G_TX_NOMIRROR | G_TX_WRAP,
                             G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

            // Load the coverage line
            gDPLoadMultiTile(glistp++, this->cvg_save, 0x0160, rtile, G_IM_FMT_I, G_IM_SIZ_8b, this->width,
                             this->height, uls, ult, lrs, lrt, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                             G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

            // Draw a texture for which the rgb channels come from the framebuffer and the alpha channel comes from
            // coverage, modulated by env color
            gSPTextureRectangle(glistp++, uls << 2, ult << 2, (lrs + 1) << 2, (lrt + 1) << 2, G_TX_RENDERTILE, uls << 5,
                                ult << 5, 1 << 10, 1 << 10);

            curRow += nRows;
            rowsRemaining -= nRows;
        }

        gDPPipeSync(glistp++);
        *glistpp = glistp;
    }
}

void PreRender_loadFrameBufferAlpha(PreRender* this, Gfx** glistpp, s32 alpha) {
    PreRender_TransBuffer1_env(this, glistpp, this->fbuf_save, this->fbuf, 255, 255, 255, alpha);
}

void PreRender_loadFrameBufferCopy(PreRender* this, Gfx** glistpp) {
    PreRender_TransBuffer(this, glistpp, this->fbuf_save, this->fbuf);
}

/**
 * Applies the Video Interface anti-aliasing of silhouette edges to an image.
 *
 * This filter performs a linear interpolation on partially covered pixels between the current pixel color (called
 * foreground color) and a "background" pixel color obtained by sampling fully covered pixels at the six highlighted
 * points in the following 5x3 neighborhood:
 *    _ _ _ _ _
 *  |   o   o   |
 *  | o   X   o |
 *  |   o   o   |
 *    ‾ ‾ ‾ ‾ ‾
 * Whether a pixel is partially covered is determined by reading the coverage values associated with the image.
 * Coverage is a measure of how many subpixels the last drawn primitive covered. A fully covered pixel is one with a
 * full coverage value, the entire pixel was covered by the primitive.
 * The background color is calculated as the average of the "penultimate" minimum and maximum colors in the 5x3
 * neighborhood.
 *
 * The final color is calculated by interpolating the foreground and background color weighted by the coverage:
 *      OutputColor = cvg * ForeGround + (1.0 - cvg) * BackGround
 *
 * This is a software implementation of the same algorithm used in the Video Interface hardware when Anti-Aliasing is
 * enabled in the VI Control Register.
 *
 * Patent describing the algorithm:
 *
 * Gossett, C. P., & van Hook, T. J. (Filed 1995, Published 1998)
 * Antialiasing of silhouette edges (USOO5742277A)
 * U.S. Patent and Trademark Office
 * Expired 2015-10-06
 * https://patents.google.com/patent/US5742277A/en
 *
 * @param this  PreRender instance
 * @param x     Center pixel x
 * @param y     Center pixel y
 */
void ASAlgorithm(PreRender* this, s32 x, s32 y) {
    s32 i;
    s32 j;
    s32 buffCvg[3 * 5];
    s32 buffR[3 * 5];
    s32 buffG[3 * 5];
    s32 buffB[3 * 5];
    s32 xi;
    s32 yi;
    s32 invCvg;
    s32 pmaxR;
    s32 pmaxG;
    s32 pmaxB;
    s32 pminR;
    s32 pminG;
    s32 pminB;
    Color_RGBA16 pxIn;
    Color_RGBA16 pxOut;
    u32 outR;
    u32 outG;
    u32 outB;

    // Extract pixels in the 5x3 neighborhood
    for (i = 0; i < 5 * 3; i++) {
        xi = x + (i % 5) - 2;
        yi = y + (i / 5) - 1;

        // Clamp coordinates to the edges of the image
        if (xi < 0) {
            xi = 0;
        } else if (xi > (this->width - 1)) {
            xi = this->width - 1;
        }
        if (yi < 0) {
            yi = 0;
        } else if (yi > (this->height - 1)) {
            yi = this->height - 1;
        }

        // Extract color channels for each pixel, convert 5-bit color channels to 8-bit
        pxIn.rgba = this->fbuf_save[xi + yi * this->width];
        buffR[i] = (pxIn.r << 3) | (pxIn.r >> 2);
        buffG[i] = (pxIn.g << 3) | (pxIn.g >> 2);
        buffB[i] = (pxIn.b << 3) | (pxIn.b >> 2);
        buffCvg[i] = this->cvg_save[xi + yi * this->width] >> 5;
    }

    pmaxR = pminR = buffR[7];
    pmaxG = pminG = buffG[7];
    pmaxB = pminB = buffB[7];

    // For each neighbor
    for (i = 1; i < 5 * 3; i += 2) {
        // Only sample fully covered pixels
        if (buffCvg[i] != 7) {
            continue;
        }
        // Determine "Penultimate Maximum" Value

        // If current maximum is less than this neighbor
        if (pmaxR < buffR[i]) {
            // For each neighbor (again)
            for (j = 1; j < 5 * 3; j += 2) {
                // If not the neighbor we were at before, and this neighbor has a larger value and this pixel is
                // fully covered, that means the neighbor at `i` is the "penultimate maximum"
                if ((i != j) && (buffR[j] >= buffR[i]) && (buffCvg[j] == 7)) {
                    pmaxR = buffR[i];
                }
            }
        }
        if (pmaxG < buffG[i]) {
            for (j = 1; j < 5 * 3; j += 2) {
                if ((i != j) && (buffG[j] >= buffG[i]) && (buffCvg[j] == 7)) {
                    pmaxG = buffG[i];
                }
            }
        }
        if (pmaxB < buffB[i]) {
            for (j = 1; j < 5 * 3; j += 2) {
                if ((i != j) && (buffB[j] >= buffB[i]) && (buffCvg[j] == 7)) {
                    pmaxB = buffB[i];
                }
            }
        }

        // Determine "Penultimate Minimum" Value

        // Same as above with inverted conditions
        if (pminR > buffR[i]) {
            for (j = 1; j < 5 * 3; j += 2) {
                if ((i != j) && (buffR[j] <= buffR[i]) && (buffCvg[j] == 7)) {
                    pminR = buffR[i];
                }
            }
        }
        if (pminG > buffG[i]) {
            for (j = 1; j < 5 * 3; j += 2) {
                if ((i != j) && (buffG[j] <= buffG[i]) && (buffCvg[j] == 7)) {
                    pminG = buffG[i];
                }
            }
        }
        if (pminB > buffB[i]) {
            for (j = 1; j < 5 * 3; j += 2) {
                if ((i != j) && (buffB[j] <= buffB[i]) && (buffCvg[j] == 7)) {
                    pminB = buffB[i];
                }
            }
        }
    }

    // The background color is determined by averaging the penultimate minimum and maximum pixels, and subtracting the
    // Foreground color:
    //      BackGround = (pMax + pMin) - (ForeGround) * 2

    // OutputColor = cvg * ForeGround + (1.0 - cvg) * BackGround
    invCvg = 7 - buffCvg[7];
    outR = buffR[7] + ((s32)(invCvg * (pmaxR + pminR - (buffR[7] * 2)) + 4) >> 3);
    outG = buffG[7] + ((s32)(invCvg * (pmaxG + pminG - (buffG[7] * 2)) + 4) >> 3);
    outB = buffB[7] + ((s32)(invCvg * (pmaxB + pminB - (buffB[7] * 2)) + 4) >> 3);

    pxOut.r = outR >> 3;
    pxOut.g = outG >> 3;
    pxOut.b = outB >> 3;
    pxOut.a = 1;
    this->fbuf_save[x + y * this->width] = pxOut.rgba;
}

void AntiAliasFilter(PreRender* this) {
    s32 x;
    s32 y;
    u8* cvg = this->cvg_save;

    for (y = 0; y < this->height; y++) {
        for (x = 0; x < this->width; x++) {
            if (*cvg != 0xFF) {
                ASAlgorithm(this, x, y);
            }
            cvg++;
        }
    }
}

void PreRender_ConvertFrameBuffer_fg(PreRender* this) {
    if ((this->cvg_save == NULL) || (this->fbuf_save == NULL)) {
        this->filterState = 0;
        return;
    }

    this->filterState = 1;
    AntiAliasFilter(this);
    this->filterState = 2;
}

void PreRender_ConvertFrameBuffer(PreRender* this) {
    if ((this->cvg_save != NULL) && (this->fbuf_save != NULL)) {
        PreRender_ConvertFrameBuffer_fg(this);
    }
}
