#include "m_rcp.h"

#include "6B3DC0.h"
#include "gfx.h"
#include "gfxalloc.h"
#include "macros.h"

#include "overlays/gamestates/ovl_play/m_play.h"

s32 fbdemo_mode;

static Gfx z_gsCPModeSet_Data[][6] = {
    {
        /* 0 */
        gsDPPipeSync(),
        gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
        gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, SHADE, 0, 0, 0, 0, PRIMITIVE),
        gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                             G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                         G_AC_NONE | G_ZS_PIXEL | G_RM_AA_ZB_XLU_SURF | G_RM_AA_ZB_XLU_SURF2),
        gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
        gsSPEndDisplayList(),
    },
    {
        /* 1 */
        gsDPPipeSync(),
        gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                             G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                         G_AC_THRESHOLD | G_ZS_PIXEL | G_RM_ZB_CLD_SURF | G_RM_ZB_CLD_SURF2),
        gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),
        gsSPEndDisplayList(),
    },
    {
        /* 2 */
        gsDPPipeSync(),
        gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIA_PRIM2),
        gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                             G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                         G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
        gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
        gsSPEndDisplayList(),
    },
    {
        /* 3 */
        gsDPPipeSync(),
        gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
        gsDPSetCombineMode(G_CC_MODULATEI_PRIM, G_CC_MODULATEI_PRIM),
        gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                             G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                         G_AC_NONE | G_ZS_PIXEL | G_RM_AA_ZB_OPA_SURF | G_RM_AA_ZB_OPA_SURF2),
        gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
        gsSPEndDisplayList(),
    },
    {
        /* 4 */
        gsDPPipeSync(),
        gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
        gsDPSetCombineMode(G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM),
        gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE |
                             G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                         G_AC_THRESHOLD | G_ZS_PIXEL | G_RM_AA_TEX_EDGE | G_RM_AA_TEX_EDGE2),
        gsSPLoadGeometryMode(G_SHADE | G_SHADING_SMOOTH),
        gsSPEndDisplayList(),
    },
    {
        /* 5 */
        gsDPPipeSync(),
        gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
        gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
        gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                             G_TD_CLAMP | G_TP_NONE | G_CYC_FILL | G_PM_NPRIMITIVE,
                         G_AC_THRESHOLD | G_ZS_PIXEL | G_RM_NOOP | G_RM_NOOP2),
        gsSPLoadGeometryMode(G_SHADE | G_SHADING_SMOOTH),
        gsSPEndDisplayList(),
    },
    {
        /* 6 */
        gsDPPipeSync(),
        gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
        gsDPSetCombineMode(G_CC_MODULATEI_PRIM, G_CC_MODULATEI_PRIM),
        gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                             G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                         G_AC_NONE | G_ZS_PIXEL | G_RM_ZB_XLU_SURF | G_RM_ZB_XLU_SURF2),
        gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),
        gsSPEndDisplayList(),
    },
    {
        /* 7 */
        gsDPPipeSync(),
        gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
        gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PRIMITIVE),
        gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                             G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                         G_AC_THRESHOLD | G_ZS_PIXEL | G_RM_CLD_SURF | G_RM_CLD_SURF2),
        gsSPLoadGeometryMode(G_SHADING_SMOOTH),
        gsSPEndDisplayList(),
    },
    {
        /* 8 */
        gsDPPipeSync(),
        gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                             G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                         G_AC_THRESHOLD | G_ZS_PIXEL | G_RM_CLD_SURF | G_RM_CLD_SURF2),
        gsSPLoadGeometryMode(G_SHADE | G_SHADING_SMOOTH),
        gsSPEndDisplayList(),
    },
    {
        /* 9 */
        gsDPPipeSync(),
        gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_PASS2),
        gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                             G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                         G_AC_NONE | G_ZS_PIXEL | G_RM_PASS | G_RM_ZB_CLD_SURF2),
        gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
        gsSPEndDisplayList(),
    },
    {
        /* 10 */
        gsDPPipeSync(),
        gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
        gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
        gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 |
                             G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                         G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_TEX_EDGE2),
        gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
        gsSPEndDisplayList(),
    },
    {
        /* 11 */
        gsDPPipeSync(),
        gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
        gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
        gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 |
                             G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                         G_AC_NONE | G_ZS_PIXEL | AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_FULL | ZMODE_OPA |
                             CVG_X_ALPHA | ALPHA_CVG_SEL | G_RM_FOG_SHADE_A |
                             GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)),
        gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
        gsSPEndDisplayList(),
    },
    {
        /* 12 */
        gsDPPipeSync(),
        gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
        gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
        gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 |
                             G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                         G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_TEX_EDGE2),
        gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
        gsSPEndDisplayList(),
    },
    {
        /* 13 */
        gsDPPipeSync(),
        gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
        gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
        gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 |
                             G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                         G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_CLD_SURF2),
        gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
        gsSPEndDisplayList(),
    },
    {
        /* 14 */
        gsDPPipeSync(),
        gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
        gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
        gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                             G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                         G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_ZB_OVL_SURF2),
        gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH),
        gsSPEndDisplayList(),
    },
};

Gfx RSP_RDP_clear_data[] = {
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_FILL | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_NOOP | G_RM_NOOP2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT),
    gsDPSetBlendColor(0, 0, 0, 8),
    gsSPClipRatio(FRUSTRATIO_2),
    gsSPEndDisplayList(),
};

void gfx_set_fog_position(Gfx** gfxP, s32 near, s32 far) {
    if (near == far) {
        gSPFogFactor((*gfxP)++, 0, 0);
    } else {
        gSPFogPosition((*gfxP)++, near, far);
    }
}

Gfx* gfx_set_fog_nosync(Gfx* gfx, s32 r, s32 g, s32 b, s32 a, s32 near, s32 far) {
    gDPSetFogColor(gfx++, r, g, b, a);
    gfx_set_fog_position(&gfx, near, far);
    return gfx;
}

Gfx* func_800BD3EC_jp(Gfx* gfx, s32 i) {
    s32 dListIndex = 6 * i;

    gSPDisplayList(gfx++, &((Gfx*)z_gsCPModeSet_Data)[dListIndex]);
    // Equivalent to gSPDisplayList(gfx++, z_gsCPModeSet_Data[i])
    return gfx;
}

Gfx* func_800BD428_jp(Gfx* gfx, s32 i) {
    return func_800BD3EC_jp(gfx, i);
}

Gfx* func_800BD448_jp(Gfx* gfx) {
    gSPDisplayList(gfx++, z_gsCPModeSet_Data[7]);
    return gfx;
}

void func_800BD470_jp(GraphicsContext* gfxCtx) {
    OPEN_DISPS(gfxCtx);

    gSPDisplayList(POLY_OPA_DISP++, z_gsCPModeSet_Data[7]);

    CLOSE_DISPS(gfxCtx);
}

void func_800BD498_jp(GraphicsContext* gfxCtx) {
    OPEN_DISPS(gfxCtx);

    gSPDisplayList(POLY_OPA_DISP++, z_gsCPModeSet_Data[3]);

    CLOSE_DISPS(gfxCtx);
}

void texture_z_light_prim_xlu_disp(GraphicsContext* gfxCtx) {
    OPEN_DISPS(gfxCtx);

    gSPDisplayList(POLY_XLU_DISP++, z_gsCPModeSet_Data[2]);

    CLOSE_DISPS(gfxCtx);
}

void _texture_z_light_fog_prim(GraphicsContext* gfxCtx) {
    OPEN_DISPS(gfxCtx);

    gSPDisplayList(POLY_OPA_DISP++, z_gsCPModeSet_Data[2]);

    CLOSE_DISPS(gfxCtx);
}

void _texture_z_light_fog_prim_shadow(GraphicsContext* gfxCtx) {
    OPEN_DISPS(gfxCtx);

    gSPDisplayList(SHADOW_DISP++, z_gsCPModeSet_Data[2]);

    CLOSE_DISPS(gfxCtx);
}

void _texture_z_light_fog_prim_npc_shadow(GraphicsContext* gfxCtx) {
    OPEN_DISPS(gfxCtx);

    gSPDisplayList(SHADOW_DISP++, z_gsCPModeSet_Data[10]);
    gDPPipeSync(SHADOW_DISP++);
    gDPSetPrimColor(SHADOW_DISP++, 0, 0x80, 255, 255, 255, 255);

    CLOSE_DISPS(gfxCtx);
}

void _texture_z_light_fog_prim_xlu(GraphicsContext* gfxCtx) {
    OPEN_DISPS(gfxCtx);

    gSPDisplayList(POLY_XLU_DISP++, z_gsCPModeSet_Data[2]);

    CLOSE_DISPS(gfxCtx);
}

void _texture_z_light_fog_prim_light(GraphicsContext* gfxCtx) {
    OPEN_DISPS(gfxCtx);

    gSPDisplayList(LIGHT_DISP++, z_gsCPModeSet_Data[2]);

    CLOSE_DISPS(gfxCtx);
}

void _texture_z_light_fog_prim_npc(GraphicsContext* gfxCtx) {
    OPEN_DISPS(gfxCtx);

    gSPDisplayList(POLY_OPA_DISP++, z_gsCPModeSet_Data[10]);
    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0x80, 255, 255, 255, 255);

    CLOSE_DISPS(gfxCtx);
}

Gfx* texture_z_light_fog_prim_bb_pal_opa(Gfx* gfx) {
    gSPDisplayList(gfx++, z_gsCPModeSet_Data[12]);
    gDPSetPrimColor(gfx++, 0, 0x80, 255, 255, 255, 255);

    return gfx;
}

Gfx* texture_z_light_fog_prim_bb_pal_xlu(Gfx* gfx) {
    gSPDisplayList(gfx++, z_gsCPModeSet_Data[13]);
    gDPSetPrimColor(gfx++, 0, 0x80, 255, 255, 255, 255);

    return gfx;
}

Gfx* texture_z_fog_lod_alpha_shadow(Gfx* gfx) {
    gSPDisplayList(gfx++, z_gsCPModeSet_Data[14]);

    return gfx;
}

void func_800BD6F8_jp(GraphicsContext* gfxCtx) {
    OPEN_DISPS(gfxCtx);

    gSPDisplayList(POLY_OPA_DISP++, z_gsCPModeSet_Data[5]);

    CLOSE_DISPS(gfxCtx);
}

Gfx* gfx_rect_moji(Gfx* gfx) {
    gSPDisplayList(gfx++, z_gsCPModeSet_Data[4]);

    return gfx;
}

void rect_moji(GraphicsContext* gfxCtx) {
    OPEN_DISPS(gfxCtx);

    gSPDisplayList(POLY_OPA_DISP++, z_gsCPModeSet_Data[4]);

    CLOSE_DISPS(gfxCtx);
}

void polygon_z_light_prim(GraphicsContext* gfxCtx) {
    OPEN_DISPS(gfxCtx);

    gSPDisplayList(POLY_XLU_DISP++, z_gsCPModeSet_Data[0]);

    CLOSE_DISPS(gfxCtx);
}

void softsprite_prim(GraphicsContext* gfxCtx) {
    OPEN_DISPS(gfxCtx);

    gSPDisplayList(POLY_XLU_DISP++, z_gsCPModeSet_Data[6]);

    CLOSE_DISPS(gfxCtx);
}

#define HREG_21 0
#define HREG_22 0

Gfx* gfx_softsprite_prim_xlu(Gfx* gfx) {
    gSPDisplayList(gfx++, z_gsCPModeSet_Data[8]);
    gDPSetColorDither(gfx++, G_CD_DISABLE);

    // clang-format off
    switch (HREG_21) {
        case 1: gDPSetAlphaDither(gfx++, G_AD_DISABLE); break;
        case 2: gDPSetAlphaDither(gfx++, G_AD_PATTERN); break;
        case 3: gDPSetAlphaDither(gfx++, G_AD_NOTPATTERN); break;
        case 4: gDPSetAlphaDither(gfx++, G_AD_NOISE); break;
        default: break;
    }

    switch (HREG_22) {
        case 1: gDPSetColorDither(gfx++, G_CD_DISABLE); break;
        case 2: gDPSetColorDither(gfx++, G_CD_MAGICSQ); break;
        case 3: gDPSetColorDither(gfx++, G_CD_BAYER); break;
        case 4: gDPSetColorDither(gfx++, G_CD_NOISE); break;
        default: break;
    }
    // clang-format on

    return gfx;
}

Gfx* gfx_tex_scroll2(Gfx** gfxP, u32 x, u32 y, s32 width, s32 height) {
    Gfx* dList = gfxalloc(gfxP, 3 * sizeof(Gfx));

    gDPTileSync(dList);
    gDPSetTileSize(dList + 1, G_TX_RENDERTILE, x, y, x + ((width - 1) << 2), y + ((height - 1) << 2));
    gSPEndDisplayList(dList + 2);

    return dList;
}

Gfx* gfx_two_tex_scroll(Gfx** gfxP, s32 tile1, u32 x1, u32 y1, s32 width1, s32 height1, s32 tile2, u32 x2, u32 y2,
                        s32 width2, s32 height2) {
    Gfx* dList = gfxalloc(gfxP, 5 * sizeof(Gfx));

    x1 %= 512 << 2;
    y1 %= 512 << 2;
    x2 %= 512 << 2;
    y2 %= 512 << 2;

    gDPTileSync(dList);
    gDPSetTileSize(dList + 1, tile1, x1, y1, x1 + ((width1 - 1) << 2), y1 + ((height1 - 1) << 2));
    gDPTileSync(dList + 2);
    gDPSetTileSize(dList + 3, tile2, x2, y2, x2 + ((width2 - 1) << 2), y2 + ((height2 - 1) << 2));
    gSPEndDisplayList(dList + 4);

    return dList;
}

Gfx* func_800BD9D8_jp(Gfx** gfxP, u32 x, u32 y) {
    return gfx_tex_scroll2(gfxP, x, y, 0, 0);
}

Gfx* func_800BD9FC_jp(GraphicsContext* gfxCtx, u32 x, u32 y) {
    return tex_scroll2(gfxCtx, x, y, 0, 0);
}

Gfx* tex_scroll2(GraphicsContext* gfxCtx, u32 x, u32 y, s32 width, s32 height) {
    Gfx* dList = GRAPH_ALLOC_NO_ALIGN(gfxCtx, 3 * sizeof(Gfx));

    if (dList != NULL) {
        x %= 512 << 2;
        y %= 512 << 2;

        gDPTileSync(dList);
        gDPSetTileSize(dList + 1, G_TX_RENDERTILE, x, y, x + ((width - 1) << 2), y + ((height - 1) << 2));
        gSPEndDisplayList(dList + 2);
    }

    return dList;
}

Gfx* two_tex_scroll(GraphicsContext* gfxCtx, s32 tile1, u32 x1, u32 y1, s32 width1, s32 height1, s32 tile2, u32 x2,
                    u32 y2, s32 width2, s32 height2) {
    Gfx* dList = GRAPH_ALLOC_NO_ALIGN(gfxCtx, 5 * sizeof(Gfx));

    if (dList != NULL) {
        x1 %= 512 << 2;
        y1 %= 512 << 2;
        x2 %= 512 << 2;
        y2 %= 512 << 2;

        gDPTileSync(dList);
        gDPSetTileSize(dList + 1, tile1, x1, y1, x1 + ((width1 - 1) << 2), y1 + ((height1 - 1) << 2));
        gDPTileSync(dList + 2);
        gDPSetTileSize(dList + 3, tile2, x2, y2, x2 + ((width2 - 1) << 2), y2 + ((height2 - 1) << 2));
        gSPEndDisplayList(dList + 4);
    }

    return dList;
}

void DisplayList_initialize(GraphicsContext* gfxCtx, u8 clearR, u8 clearG, u8 clearB, Game_Play* game_play) {
    void* unk_008;

    OPEN_DISPS(gfxCtx);

    gSPDisplayList(POLY_OPA_DISP++, RSP_RDP_clear_data);
    gSPDisplayList(POLY_XLU_DISP++, RSP_RDP_clear_data);
    gSPDisplayList(OVERLAY_DISP++, RSP_RDP_clear_data);
    gSPDisplayList(UNK_2B0_DISP++, RSP_RDP_clear_data);
    gSPDisplayList(SHADOW_DISP++, z_gsCPModeSet_Data[2]);
    gSPDisplayList(LIGHT_DISP++, z_gsCPModeSet_Data[2]);

    gDPSetScissor(POLY_OPA_DISP++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    gDPSetScissor(POLY_XLU_DISP++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    gDPSetScissor(OVERLAY_DISP++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    gDPSetScissor(UNK_2B0_DISP++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    gDPSetScissor(SHADOW_DISP++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    gDPSetScissor(LIGHT_DISP++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    gDPSetColorImage(POLY_OPA_DISP++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, gfxCtx->unk_2E4);
    gDPSetColorImage(POLY_XLU_DISP++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, gfxCtx->unk_2E4);
    gDPSetColorImage(OVERLAY_DISP++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, gfxCtx->unk_2E4);
    gDPSetColorImage(UNK_2B0_DISP++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, gfxCtx->unk_2E4);
    gDPSetColorImage(SHADOW_DISP++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, gfxCtx->unk_2E4);
    gDPSetColorImage(LIGHT_DISP++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, gfxCtx->unk_2E4);

    unk_008 = gfxCtx->unk_008;

    gDPSetDepthImage(POLY_OPA_DISP++, unk_008);
    gDPSetDepthImage(POLY_XLU_DISP++, unk_008);
    gDPSetDepthImage(OVERLAY_DISP++, unk_008);
    gDPSetDepthImage(UNK_2B0_DISP++, unk_008);
    gDPSetDepthImage(SHADOW_DISP++, unk_008);
    gDPSetDepthImage(LIGHT_DISP++, unk_008);

    if ((game_play == NULL) || ((game_play->submenu.unk_00 < 2) && (fbdemo_mode < 2))) {
        gDPSetColorImage(POLY_OPA_DISP++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, gfxCtx->unk_008);
        gDPSetCycleType(POLY_OPA_DISP++, G_CYC_FILL);
        gDPSetRenderMode(POLY_OPA_DISP++, G_RM_NOOP, G_RM_NOOP2);
        gDPSetFillColor(POLY_OPA_DISP++, (GPACK_RGBA5551(255, 255, 240, 0) << 16) | GPACK_RGBA5551(255, 255, 240, 0));
        gDPFillRectangle(POLY_OPA_DISP++, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetColorImage(POLY_OPA_DISP++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, gfxCtx->unk_2E4);
        gDPSetCycleType(POLY_OPA_DISP++, G_CYC_FILL);
        gDPSetRenderMode(POLY_OPA_DISP++, G_RM_NOOP, G_RM_NOOP2);
        gDPSetFillColor(POLY_OPA_DISP++,
                        (GPACK_RGBA5551(clearR, clearG, clearB, 1) << 16) | GPACK_RGBA5551(clearR, clearG, clearB, 1));
        gDPFillRectangle(POLY_OPA_DISP++, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
        gDPPipeSync(POLY_OPA_DISP++);
    }

    //! FAKE:
    if (gfxCtx && gfxCtx && gfxCtx) {}

    CLOSE_DISPS(gfxCtx);

    func_80091074_jp(gfxCtx);
}

void fade_rgba8888_draw(Gfx** gfxP, u32 color) {
    static Gfx fade_gfx[] = {
        gsDPPipeSync(),
        gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                             G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_1PRIMITIVE,
                         G_AC_NONE | G_ZS_PIXEL | G_RM_CLD_SURF | G_RM_CLD_SURF2),
        gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PRIMITIVE),
        gsDPFillRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT),
        gsDPPipeSync(),
        gsSPEndDisplayList(),
    };
    static Gfx fill_gfx[] = {
        gsDPPipeSync(),
        gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                             G_TD_CLAMP | G_TP_NONE | G_CYC_FILL | G_PM_1PRIMITIVE,
                         G_AC_NONE | G_ZS_PIXEL | G_RM_NOOP | G_RM_NOOP2),
        gsDPFillRectangle(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
        gsDPPipeSync(),
        gsSPEndDisplayList(),
    };
    Gfx* gfx;

    if ((color & 0xFF) == 255) {
        u32 c;

        gfx = *gfxP;
        c = ((color >> 27) << 11) | ((color >> 19) << 6) | (color >> 10) | 1;
        gDPSetFillColor(gfx, (c << 0x10) | c);
        gSPDisplayList(gfx + 1, fill_gfx);
        *gfxP = gfx + 2;
    } else if ((color & 0xFF) != 0) {
        gfx = *gfxP;
        gDPSetColor(gfx, G_SETPRIMCOLOR, color);
        gSPDisplayList(gfx + 1, fade_gfx);
        *gfxP = gfx + 2;
    }
}

void func_800BE030_jp(Gfx** gfxP, u32 r, u32 g, u32 b, u32 a) {
    fade_rgba8888_draw(gfxP, (r << 24) | (g << 16) | (b << 8) | a);
}

void fade_black_draw(Gfx** gfxP, u32 color) {
    //! FAKE:
    fade_rgba8888_draw(gfxP, color ^ 0);
}

Gfx* gfx_gDPFillRectangle1(Gfx* gfx, s32 ulx, s32 uly, s32 lrx, s32 lry) {
    gDPFillRectangle(gfx++, ulx, uly, lrx, lry);
    return gfx;
}

void func_800BE0E4_jp(Gfx** gfxP, s32 ulx, s32 uly, s32 lrx, s32 lry) {
    gDPFillRectangle(*gfxP, ulx, uly, lrx, lry);
}

Gfx* gfx_gDPFillRectangleF(Gfx* gfx, s32 ulx, s32 uly, s32 lrx, s32 lry) {
    gDPFillRectangle(gfx++, ulx, uly, lrx - 1, lry - 1);
    return gfx;
}

void func_800BE184_jp(Gfx** gfxP, s32 ulx, s32 uly, s32 lrx, s32 lry) {
    gDPFillRectangle(*gfxP, ulx, uly, lrx - 1, lry - 1);
}

Gfx* gfx_gSPTextureRectangle1(Gfx* gfx, s32 xl, s32 yl, s32 xh, s32 yh, s32 tile, s32 s, s32 t, s32 dsdx, s32 dtdy) {
    gSPTextureRectangle(gfx++, xl, yl, xh, yh, tile, s, t, dsdx, dtdy);
    return gfx;
}

Gfx* func_800BE27C_jp(Gfx* gfx, s32 xl, s32 yl, s32 xh, s32 yh, s32 tile, s32 s, s32 t) {
    gSPTextureRectangle(gfx++, xl, yl, xh - 1, yh - 1, tile, s, t, 1 << 10, 1 << 10);
    return gfx;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BE320_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BE4F8_jp.s")
