#include "m_rcp.h"

#include "gfx.h"
#include "macros.h"

static Gfx z_gsCPModeSet_Data[][6] = {
    {
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

void func_800BD4C0_jp(GraphicsContext* gfxCtx) {
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

void func_800BD538_jp(GraphicsContext* gfxCtx) {
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

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD68C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD6D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD6F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD720_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/rect_moji.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD770_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD798_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD7C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD804_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD8A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD9D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD9FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/tex_scroll2.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/two_tex_scroll.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/DisplayList_initialize.s")

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

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/fade_rgba8888_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BE030_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/fade_black_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BE094_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BE0E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BE12C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BE184_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BE1D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BE27C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BE320_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BE4F8_jp.s")
