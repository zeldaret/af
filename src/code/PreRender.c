#include "PreRender.h"

#include "libc/stdbool.h"
#include "PR/gs2dex.h"

#include "gfx.h"
#include "gfxalloc.h"
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

void wallpaper_draw1(Wallpaper* wallpaper, Gfx** gfxp) {
    Gfx* gfx;
    uObjBg* bg;
    u32 alphaCompare;
    Gfx* gfxHead;
    u32 loadS2DEX2;

    loadS2DEX2 = (wallpaper->flags & WALLPAPER_FLAGS_LOAD_S2DEX2) != 0;
    alphaCompare = (wallpaper->flags & WALLPAPER_FLAGS_AC_THRESHOLD) ? G_AC_THRESHOLD : G_AC_NONE;

    gfxHead = *gfxp;
    bg = gfxalloc(&gfxHead, sizeof(uObjBg));
    gfx = gfxHead;

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
        gSPLoadUcode(gfx++, ucode_GetSpriteTextStart(), ucode_GetSpriteDataStart());
    }

    if ((wallpaper->fmt == G_IM_FMT_CI) && (wallpaper->tlut != NULL)) {
        gDPLoadTLUT(gfx++, wallpaper->tlutCount, 256, wallpaper->tlut);
    } else {
        gDPPipeSync(gfx++);
    }

    if (wallpaper->flags & WALLPAPER_FLAGS_COPY) {
        bg->b.frameW = wallpaper->width * (1 << 2);
        bg->b.frameH = wallpaper->height * (1 << 2);

        guS2DInitBg(bg);

        if (!(wallpaper->flags & WALLPAPER_FLAGS_1)) {
            gDPSetOtherMode(gfx++, wallpaper->tt | G_CYC_COPY, alphaCompare);
        }

        gSPBgRectCopy(gfx++, bg);
    } else {
        bg->b.frameW = (s16)((u32)(wallpaper->width * (1 << 2)) * wallpaper->xScale);
        bg->b.frameH = (s16)((u32)(wallpaper->height * (1 << 2)) * wallpaper->yScale);
        bg->b.tmemW = (s16)(1024.0f / wallpaper->xScale);
        bg->b.tmemH = (s16)(1024.0f / wallpaper->yScale);
        bg->s.imageYorig = bg->b.imageY;

        if (!(wallpaper->flags & WALLPAPER_FLAGS_1)) {
            gDPSetOtherMode(gfx++, wallpaper->tt | G_AD_DISABLE | G_CD_DISABLE | G_TC_FILT,
                            AA_EN | CVG_X_ALPHA | ALPHA_CVG_SEL |
                                GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_BL, G_BL_1MA) |
                                GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_BL, G_BL_1MA) | alphaCompare);
        }

        if (!(wallpaper->flags & WALLPAPER_FLAGS_2)) {
            gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, 0, 0, 0, 1, 0, 0, 0, TEXEL0, 0, 0, 0, 1);
        }

        gSPObjRenderMode(gfx++, G_OBJRM_ANTIALIAS | G_OBJRM_BILERP);
        gSPBgRect1Cyc(gfx++, bg);
    }

    gDPPipeSync(gfx++);

    if (loadS2DEX2) {
        gSPLoadUcode(gfx++, ucode_GetPolyTextStart(), ucode_GetPolyDataStart());
    }

    *gfxp = gfx;
}

void wallpaper_draw(Gfx** gfxp, void* timg, void* tlut, u16 width, u16 height, u8 fmt, u8 siz, u16 tt, u16 tlutCount,
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

    wallpaper_draw1(wallpaperPtr, gfxp);
}

Gfx* gfx_SetUpCFB(Gfx* gfx, void* imgDst, u32 width, u32 height) {
    gDPPipeSync(gfx);
    gDPSetColorImage(gfx + 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, imgDst);
    gDPSetScissor(gfx + 2, G_SC_NON_INTERLACE, 0, 0, width, height);

    return gfx + 3;
}

void PreRender_setup_savebuf(PreRender* render, s32 arg1, s32 arg2, void* arg3, void* arg4, void* arg5) {
    render->unk_04 = arg1;
    render->unk_06 = arg2;
    render->unk_14 = arg3;
    render->unk_18 = arg5;
    render->unk_20 = arg4;
    render->unk_24 = 0;
    render->unk_26 = 0;
    render->unk_28 = arg1 - 1;
    render->unk_2A = arg2 - 1;
}

void PreRender_init(PreRender* render) {
    bzero(render, sizeof(PreRender));
    ListAlloc_Init(&render->alloc);
}

void PreRender_setup_renderbuf(PreRender* render, s32 width, s32 height, void* arg3, void* arg4) {
    render->width = width;
    render->height = height;
    render->unk_10 = arg3;
    render->unk_1C = arg4;
    render->unk_2C = 0;
    render->unk_2E = 0;
    render->unk_30 = width - 1;
    render->unk_32 = height - 1;
}

void PreRender_cleanup(PreRender* render) {
    ListAlloc_FreeAll(&render->alloc);
}

void PreRender_TransBufferCopy(PreRender* render, Gfx** gfxP, void* arg2, void* arg3, u32 useThresholdAlphaCompare) {
    Gfx* gfx = *gfxP;
    u32 flags;

    gfx = gfx_SetUpCFB(gfx, arg3, render->width, render->height);

    flags = WALLPAPER_FLAGS_LOAD_S2DEX2 | WALLPAPER_FLAGS_COPY;
    if (useThresholdAlphaCompare == true) {
        flags |= WALLPAPER_FLAGS_AC_THRESHOLD;
    }

    wallpaper_draw(&gfx, arg2, NULL, render->width, render->height, G_IM_FMT_RGBA, G_IM_SIZ_16b, G_TT_NONE, 0, 0.0f,
                   0.0f, 1.0f, 1.0f, flags);

    *gfxP = gfx_SetUpCFB(gfx, render->unk_10, render->width, render->height);
}

void PreRender_TransBuffer(PreRender* render, Gfx** gfxP, void* arg2, void* arg3) {
    PreRender_TransBufferCopy(render, gfxP, arg2, arg3, false);
}

void PreRender_TransBuffer1_env(PreRender* render, Gfx** gfxP, void* arg2, void* arg3, s32 envR, s32 envG, s32 envB,
                                s32 envA) {
    Gfx* gfx = *gfxP;
    u32 mode0;
    u32 mode1;

    gDPPipeSync(gfx++);

    //! FAKE:
    if (envA && envA && envA) {}

    if (envA == 255) {
        mode0 = G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE | G_TD_CLAMP |
                G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE;
        mode1 = G_AC_NONE | G_ZS_PRIM | G_RM_OPA_SURF | G_RM_OPA_SURF2;
    } else {
        mode0 = G_AD_NOISE | G_CD_NOISE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE | G_TD_CLAMP |
                G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE;
        mode1 = G_AC_NONE | G_ZS_PRIM | G_RM_CLD_SURF | G_RM_CLD_SURF2;
    }

    gDPSetOtherMode(gfx++, mode0, mode1);
    gDPSetEnvColor(gfx++, envR, envG, envB, envA);
    gDPSetCombineLERP(gfx++, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0,
                      ENVIRONMENT);

    gfx = gfx_SetUpCFB(gfx, arg3, render->width, render->height);
    wallpaper_draw(&gfx, arg2, NULL, render->width, render->height, G_IM_FMT_RGBA, G_IM_SIZ_16b, G_TT_NONE, 0, 0.0f,
                   0.0f, 1.0f, 1.0f, WALLPAPER_FLAGS_1 | WALLPAPER_FLAGS_2 | WALLPAPER_FLAGS_LOAD_S2DEX2);
    *gfxP = gfx_SetUpCFB(gfx, render->unk_10, render->width, render->height);
}

void PreRender_TransBuffer1(PreRender* render, Gfx** gfxP, void* arg2, void* arg3) {
    PreRender_TransBuffer1_env(render, gfxP, arg2, arg3, 255, 255, 255, 255);
}

void PreRender_TransBuffer2(PreRender* render, Gfx** gfxP, void* arg2, void* arg3) {
    Gfx* gfx = *gfxP;
    s32 rowsRemaining;
    s32 curRow;
    s32 nRows;
    s32 pad UNUSED;

    gDPPipeSync(gfx++);
    gDPSetOtherMode(gfx++,
                    G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                        G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                    G_AC_NONE | G_ZS_PRIM | G_RM_PASS | G_RM_OPA_CI2);

    // Set the combiner to draw the texture as-is, discarding alpha channel
    gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, 0, 0, 0, 0, 0, 0, 0, TEXEL0, 0, 0, 0, 0);
    // Set the destination color image to the provided address
    gDPSetColorImage(gfx++, G_IM_FMT_I, G_IM_SIZ_8b, render->width, arg3);
    // Set up a scissor based on the source image
    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, render->width, render->height);

    // Calculate the max number of rows that can fit into TMEM at once
    nRows = TMEM_SIZE / (render->width * G_IM_SIZ_16b_BYTES);

    // Set up the number of remaining rows
    rowsRemaining = render->height;
    curRow = 0;
    while (rowsRemaining > 0) {
        s32 uls = 0;
        s32 lrs = render->width - 1;
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
        gDPLoadTextureTile(gfx++, arg2, G_IM_FMT_IA, G_IM_SIZ_16b, render->width, render->height, uls, ult, lrs, lrt, 0,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                           G_TX_NOLOD);

        // Draw that horizontal strip to the destination image. With the combiner and blender configuration set above,
        // the intensity (I) channel of the loaded IA16 texture will be written as-is to the I8 color image, each pixel
        // in the final image is
        //  I = (cvg << 3) | (cvg >> 2)
        gSPTextureRectangle(gfx++, uls << 2, ult << 2, (lrs + 1) << 2, (lrt + 1) << 2, G_TX_RENDERTILE, uls << 5,
                            ult << 5, 1 << 10, 1 << 10);

        // Update the number of rows remaining and index of the row being drawn
        curRow += nRows;
        rowsRemaining -= nRows;
    }

    // Reset the color image to the current framebuffer

    *gfxP = gfx_SetUpCFB(gfx, render->unk_10, render->width, render->height);
}

void PreRender_ShowCoveredge(Gfx** gfxP, s32 ulx, s32 uly, s32 lrx, s32 lry) {
    Gfx* gfx = *gfxP;

    gDPPipeSync(gfx++);
    // Set the blend color to full white and set maximum depth
    gDPSetBlendColor(gfx++, 255, 255, 255, 8);
    gDPSetPrimDepth(gfx++, 0xFFFF, 0xFFFF);

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
    gDPSetOtherMode(gfx++,
                    G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                        G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                    G_AC_NONE | G_ZS_PRIM | G_RM_VISCVG | G_RM_VISCVG2);

    // Fill rectangle to obtain the coverage values as an RGBA16 image
    gDPFillRectangle(gfx++, ulx, uly, lrx, lry);
    gDPPipeSync(gfx++);

    *gfxP = gfx;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/PreRender/PreRender_CopyRGBC.s")

void PreRender_saveZBuffer(PreRender* render, Gfx** gfxP) {
    if ((render->unk_20 != NULL) && (render->unk_1C != NULL)) {
        PreRender_TransBuffer(render, gfxP, render->unk_1C, render->unk_20);
    }
}

void PreRender_saveFrameBuffer(PreRender* render, Gfx** gfxP) {
    if ((render->unk_14 != NULL) && (render->unk_10 != NULL)) {
        PreRender_TransBuffer1(render, gfxP, render->unk_10, render->unk_14);
    }
}

void PreRender_saveCVG(PreRender* render, Gfx** gfxP) {
    PreRender_ShowCoveredge(gfxP, 0, 0, render->width, render->height);
    if (render->unk_18 != NULL) {
        PreRender_TransBuffer2(render, gfxP, render->unk_10, render->unk_18);
    }
}

void PreRender_loadZBuffer(PreRender* render, Gfx** gfxP) {
    PreRender_TransBuffer(render, gfxP, render->unk_20, render->unk_1C);
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/PreRender/PreRender_loadFrameBuffer.s")

void PreRender_loadFrameBufferAlpha(PreRender* render, Gfx** gfxP, s32 alpha) {
    PreRender_TransBuffer1_env(render, gfxP, render->unk_14, render->unk_10, 255, 255, 255, alpha);
}

void PreRender_loadFrameBufferCopy(PreRender* render, Gfx** gfxP) {
    PreRender_TransBuffer(render, gfxP, render->unk_14, render->unk_10);
}

void ASAlgorithm(PreRender* render, s32 x, s32 y);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/PreRender/ASAlgorithm.s")

void AntiAliasFilter(PreRender* render) {
    s32 x;
    s32 y;
    u8* cvg = render->unk_18;

    for (y = 0; y < render->height; y++) {
        for (x = 0; x < render->width; x++) {
            if (*cvg != 0xFF) {
                ASAlgorithm(render, x, y);
            }
            cvg++;
        }
    }
}

void PreRender_ConvertFrameBuffer_fg(PreRender* render) {
    if ((render->unk_18 == NULL) || (render->unk_14 == NULL)) {
        render->unk_4D = 0;
        return;
    }

    render->unk_4D = 1;
    AntiAliasFilter(render);
    render->unk_4D = 2;
}

void PreRender_ConvertFrameBuffer(PreRender* render) {
    if ((render->unk_18 != NULL) && (render->unk_14 != NULL)) {
        PreRender_ConvertFrameBuffer_fg(render);
    }
}
