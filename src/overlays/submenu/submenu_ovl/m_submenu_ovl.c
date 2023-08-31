#include "m_submenu_ovl.h"
#include "m_submenu.h"
#include "m_lib.h"
#include "game.h"
#include "ovlmgr.h"
#include "PreRender.h"
#include "sys_matrix.h"
#include "z_std_dma.h"
#include "6BFE60.h"
#include "6E0F50.h"
#include "segment_symbols.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "overlays/gamestates/ovl__00743CD0/_00743CD0.h"

extern struct_8085E9B0 ovl_base;

extern struct_8085E4D0 mSM_program_dlftbl[];

extern s32 D_8085E938_jp[];
extern f32 D_FLT_8085E7E8_jp[][4];
extern u8 D_8085E7D0_jp[];

typedef struct struct_func_8085C20C_jp_arg1 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x4];
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ UNK_TYPE1 unk_08[0xC];
    /* 0x14 */ UNK_TYPE unk_14;
    /* 0x18 */ UNK_TYPE1 unk_18[0x8];
    /* 0x20 */ UNK_TYPE unk_20;
} struct_func_8085C20C_jp_arg1; // size > 0x24

extern Vp D_8085DCD0_jp;

// TODO: fix symbol size
extern Lightsn D_8085DCE0_jp;

Gfx* func_800BE320_jp(Gfx*, s32, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */

typedef struct struct_8085DCF8 {
    /* 0x0 */ UNK_TYPE4 unk_0;
    /* 0x4 */ UNK_TYPE4 unk_4;
} struct_8085DCF8; // size = 0x8

extern struct_8085DCF8 D_8085DCF8_jp;
extern struct_8085DCF8 D_8085DD00_jp;
extern struct_8085DCF8 D_8085DD08_jp;
extern struct_8085DCF8 D_8085DD10_jp[];
extern struct_8085DCF8 D_8085DD38_jp;
extern struct_8085DCF8 D_8085DD68_jp[];
extern struct_8085DCF8 D_8085DD88_jp;

extern struct_8085DCF8* D_8085E460_jp[];

typedef struct struct_8085E948 {
    /* 0x0 */ f32 unk_0;
    /* 0x4 */ f32 unk_4;
    /* 0x8 */ f32 unk_8;
    /* 0xC */ f32 unk_C;
} struct_8085E948; // size = 0x10

extern struct_8085E948 D_8085E948_jp[];

void mSM_setup_view(mSM* arg0, GraphicsContext* gfxCtx, s32 arg1) {
    Mtx* var_t0;
    UNUSED s32 pad;
    Gfx* gfx;

    if (arg1 != 0) {
        var_t0 = GRAPH_ALLOC(gfxCtx, sizeof(Mtx));
        guOrtho(var_t0, -2560.0f, 2560.0f, -1920.0f, 1920.0f, 1.0f, 2000.0f, 1.0f);
        arg0->unk_2C->unk_1072C = var_t0;
    } else {
        var_t0 = arg0->unk_2C->unk_1072C;
    }

    OPEN_DISPS(gfxCtx);

    gfx = POLY_OPA_DISP;
    if (arg1 == 0) {
        Game_Play1938* var_a0;

        if (arg0->unk_00 != 4) {
            var_a0 = &((Game_Play*)gamePT)->unk_1938;
        } else {
            var_a0 = &((Game__00743CD0*)gamePT)->unk_00E0;
        }

        gDPPipeSync(gfx++);
        gDPSetScissor(gfx++, G_SC_NON_INTERLACE, var_a0->unk_010, var_a0->unk_008, var_a0->unk_014, var_a0->unk_00C);
        gSPViewport(gfx++, &var_a0->vp);
        gDPSetColorImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, gfxCtx->unk_2E4);
        gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
    }

    if (1) {}
    if (1) {}
    if (1) {}

    gSPMatrix(gfx++, var_t0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(gfxCtx);
}

void mSM_set_char_matrix(GraphicsContext* gfxCtx) {
    Gfx* gfx;

    OPEN_DISPS(gfxCtx);

    gfx = POLY_OPA_DISP;
    gSPMatrix(gfx++, &Mtx_clear, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(gfxCtx);
}

#ifdef NON_EQUIVALENT
void mSM_cbuf_copy(GraphicsContext* gfxCtx, PreRender* render, s32 arg2, s32 arg3, s32 arg4) {
    s32 spCC;
    void* sp9C;
    void* sp98;
    Gfx* sp8C;
    // Gfx* temp_v0_11;
    // Gfx* temp_v0_12;
    // Gfx* temp_v0_13;
    // Gfx* temp_v0_14;
    // Gfx* temp_v0_15;
    // Gfx* temp_v0_16;
    // Gfx* temp_v0_17;
    // Gfx* temp_v0_6;
    // Gfx* temp_v0_8;
    // Gfx* temp_v0_9;
    s32 temp_a2;
    s32 temp_v0_7;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;
    s32 var_t1;
    s32 var_t2;
    s32 var_t3;
    s32 var_v1;
    u16 temp_a0;
    u16 temp_v0;
    u16 var_ra;
    s32 var_t0;
    u16 var_t4;
    u16 var_t5;

    if (arg2 >= 0x13F) {
        return;
    }

    temp_v0 = render->unk_04;
    if (-(s32)temp_v0 >= arg2) {
        return;
    }

    temp_a0 = render->unk_06;
    if (1) {}
    if (1) {}
    if (1) {}
    if (1) {}
    if (-(s32)temp_a0 >= arg3) {
        return;
    }

    if ((arg3 >= 0xEF)) {
        return;
    }

    if (arg2 < 0) {
        var_t5 = temp_v0 + arg2;
        var_t3 = -arg2;
        arg2 = 0;
    } else {
        var_t3 = 0;
        if ((temp_v0 + arg2) >= 0x140) {
            var_t5 = 0x140 - arg2;
        } else {
            var_t5 = temp_v0;
        }
    }

    var_t4 = 0x140;
    if (arg3 < 0) {
        var_t0 = temp_a0 + arg3;
        var_v1 = -arg3;
        arg3 = 0;
    } else {
        var_v1 = 0;
        if ((temp_a0 + arg3) >= 0xF0) {
            var_t0 = 0xEF - arg3;
        } else {
            var_t0 = temp_a0;
        }
    }

    OPEN_DISPS(gfxCtx);

    var_ra = temp_a0;
    if (arg4 == 0) {
        spCC = 0x140;
        var_t4 = temp_v0;
        sp9C = gfxCtx->unk_2E4;
        var_a1 = arg2;
        var_t1 = arg3;
        var_t2 = var_v1;
        var_a2 = var_t3;
        sp98 = render->unk_14;
    } else {
        spCC = (s32)temp_v0;
        var_ra = 0xF0;
        var_a1 = var_t3;
        var_t1 = var_v1;
        sp9C = render->unk_14;
        var_t2 = arg3;
        var_a2 = arg2;
        sp98 = gfxCtx->unk_2E4;
    }

    var_a3 = 0x1000 / (s32)(((var_t5 + 3) & ~3) * 2);
    if (arg4 != 0) {
        sp8C = POLY_OPA_DISP;
        render->unk_00 = 0x140;
        render->unk_02 = 0xF0;
        render->unk_10 = gfxCtx->unk_2E4;
        PreRender_CopyRGBC(render, &sp8C, arg2 - var_t3, arg3 - var_v1);
        POLY_OPA_DISP = sp8C;
    } else {
        gDPPipeSync(POLY_OPA_DISP++);
        gSPClearGeometryMode(POLY_OPA_DISP++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                                                  G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING |
                                                  0x0040F9FA);

        gDPSetOtherMode(POLY_OPA_DISP++,
                        G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                            G_TD_CLAMP | G_TP_NONE | G_CYC_COPY | G_PM_NPRIMITIVE,
                        G_AC_NONE | G_ZS_PRIM | G_RM_NOOP | G_RM_NOOP2);

        // temp_v0_5 = gfxCtx->polyOpa.p;
        // gfxCtx->polyOpa.p = temp_v0_5 + 8;
        // temp_v0_5->words.w0 = ((var_t4 - 1) & 0xFFF) | 0xFF100000;
        // temp_v0_5->words.w1 = (u32) sp98;
        gDPSetColorImage(POLY_OPA_DISP++, G_IM_FMT_RGBA, G_IM_SIZ_16b, var_t4, sp98);

        // temp_v0_6 = gfxCtx->polyOpa.p;
        // gfxCtx->polyOpa.p = temp_v0_6 + 8;
        // temp_v0_6->words.w0 = 0xED000000;
        // temp_v0_6->words.w1 = (((s32) ((f32) var_t4 * 4.0f) & 0xFFF) << 0xC) | ((s32) ((f32) var_ra * 4.0f) & 0xFFF);
        gDPSetScissorFrac(POLY_OPA_DISP++, G_SC_NON_INTERLACE, 0, 0, (s32)var_t4 * 4.0f, (s32)var_ra * 4.0f);

        while ((s32)var_t0 > 0) {
            if ((s32)var_t0 < var_a3) {
                var_a3 = (s32)var_t0;
            }
            var_t0 -= var_a3;

            temp_v0_7 = ((var_t5 + var_a1) - 1);

#if 0
            temp_v0_8 = gfxCtx->polyOpa.p;
            gfxCtx->polyOpa.p = temp_v0_8 + 8;
            temp_v0_8->words.w0 = ((spCC - 1) & 0xFFF) | 0xFD100000;
            temp_v0_8->words.w1 = (u32) sp9C;
            // gDPSetTextureImage(POLY_OPA_DISP++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 0x12345678);

            temp_v0_9 = gfxCtx->polyOpa.p;
            gfxCtx->polyOpa.p = temp_v0_9 + 8;
            temp_v0_9->words.w1 = 0x07000000;
            temp_v0_9->words.w0 = ((((s32) (((temp_v0_7 - var_a1) * 2) + 9) >> 3) & 0x1FF) << 9) | 0xF5100000;

            //temp_v0_10 = gfxCtx->polyOpa.p;
            //gfxCtx->polyOpa.p = temp_v0_10 + 8;
            //temp_v0_10->words.w1 = 0x00000000;
            //temp_v0_10->words.w0 = 0xE6000000;
            gDPLoadSync(POLY_OPA_DISP++);

            temp_v0_11 = gfxCtx->polyOpa.p;
            gfxCtx->polyOpa.p = temp_v0_11 + 8;
            temp_a2 = var_t1 + var_a3;
            temp_v0_11->words.w0 = (((var_a1 * 4) & 0xFFF) << 0xC) | 0xF4000000 | ((var_t1 * 4) & 0xFFF);
            temp_v0_11->words.w1 = (((temp_v0_7 * 4) & 0xFFF) << 0xC) | 0x07000000 | (((temp_a2 - 1) * 4) & 0xFFF);

            temp_v0_12 = gfxCtx->polyOpa.p;
            gfxCtx->polyOpa.p = temp_v0_12 + 8;
            temp_v0_12->words.w1 = 0x00000000;
            temp_v0_12->words.w0 = 0xE7000000;

            temp_v0_13 = gfxCtx->polyOpa.p;
            gfxCtx->polyOpa.p = temp_v0_13 + 8;
            temp_v0_13->words.w1 = 0x00000000;
            temp_v0_13->words.w0 = ((((s32) (((temp_v0_7 - var_a1) * 2) + 9) >> 3) & 0x1FF) << 9) | 0xF5100000;

            temp_v0_14 = gfxCtx->polyOpa.p;
            gfxCtx->polyOpa.p = temp_v0_14 + 8;
            temp_v0_14->words.w1 = (((temp_v0_7 * 4) & 0xFFF) << 0xC) | (((temp_a2 - 1) * 4) & 0xFFF);
            temp_v0_14->words.w0 = (((var_a1 * 4) & 0xFFF) << 0xC) | 0xF2000000 | ((var_t1 * 4) & 0xFFF);
#endif
            gDPLoadTextureTile(POLY_OPA_DISP++, sp9C, G_IM_FMT_RGBA, G_IM_SIZ_16b, spCC, 0, var_a1, var_t1, temp_v0_7,
                               temp_a2 - 1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                               G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

#if 0
            temp_v0_15 = gfxCtx->polyOpa.p;
            gfxCtx->polyOpa.p = temp_v0_15 + 8;
            temp_v0_15->words.w0 = ((((((var_a2 + var_t5) - 1) * 4) & 0xFFF) << 0xC) | 0xE4000000) | (((var_t2 + var_a3 - 1) * 4) & 0xFFF);
            temp_v0_15->words.w1 = (((var_a2 * 4) & 0xFFF) << 0xC) | ((var_t2 * 4) & 0xFFF);

            temp_v0_16 = gfxCtx->polyOpa.p;
            gfxCtx->polyOpa.p = temp_v0_16 + 8;
            temp_v0_16->words.w0 = 0xE1000000;
            temp_v0_16->words.w1 = (var_a1 << 0x15) | ((var_t1 << 5) & 0xFFFF);

            temp_v0_17 = gfxCtx->polyOpa.p;
            gfxCtx->polyOpa.p = temp_v0_17 + 8;
            temp_v0_17->words.w0 = 0xF1000000;
            temp_v0_17->words.w1 = 0x10000400;
#endif
            gSPTextureRectangle(POLY_OPA_DISP++, (var_a2 * 4), (var_t2 * 4), (((var_a2 + var_t5) - 1) * 4),
                                ((var_t2 + var_a3 - 1) * 4), G_TX_RENDERTILE, (var_a1 << 0x5), (var_t1 << 5), 0x1000,
                                0x0400);

            var_t1 = temp_a2;

            var_t2 = var_t2 + var_a3;
        }
    }

    CLOSE_DISPS(gfxCtx);
}
#else
void mSM_cbuf_copy(GraphicsContext* gfxCtx, PreRender* render, s32 arg2, s32 arg3, s32 arg4);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/mSM_cbuf_copy.s")
#endif

// mSM_set_drawMode?
void func_8085C20C_jp(GraphicsContext* gfxCtx, struct_func_8085C20C_jp_arg1* arg1, f32 arg2, f32 xAt, s16 angle) {
    s32 temp_a3 = arg1->unk_04;
    s32 temp_t1 = arg1->unk_06;
    f32 temp_fv1;
    f32 temp_fa0;

    OPEN_DISPS(gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x00, NULL);

    gDPPipeSync(POLY_OPA_DISP++);
    gSPClearGeometryMode(POLY_OPA_DISP++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                                              G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING |
                                              0x0040F9FA);
    gSPTexture(POLY_OPA_DISP++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF);
    gDPSetCombineMode(POLY_OPA_DISP++, G_CC_SHADE, G_CC_SHADE);
    gDPSetOtherMode(POLY_OPA_DISP++,
                    G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                        G_TD_CLAMP | G_TP_PERSP | G_CYC_FILL | G_PM_NPRIMITIVE,
                    G_AC_NONE | G_ZS_PIXEL | G_RM_NOOP | G_RM_NOOP2);
    gSPLoadGeometryMode(POLY_OPA_DISP++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH);

    temp_fv1 = temp_a3;
    temp_fa0 = temp_t1;

    gDPSetScissorFrac(POLY_OPA_DISP++, G_SC_NON_INTERLACE, 0, 0, temp_fv1 * 4.0f, temp_fa0 * 4.0f);

    gSPClipRatio(POLY_OPA_DISP++, FRUSTRATIO_1);

    gDPSetColorImage(POLY_OPA_DISP++, G_IM_FMT_RGBA, G_IM_SIZ_16b, temp_a3, arg1->unk_20);

    gDPSetFillColor(POLY_OPA_DISP++, 0xFFFCFFFC);

    gDPFillRectangle(POLY_OPA_DISP++, 0, 0, temp_a3 - 1, temp_t1 - 1);

    gDPPipeSync(POLY_OPA_DISP++);

    gDPSetColorImage(POLY_OPA_DISP++, G_IM_FMT_RGBA, G_IM_SIZ_16b, temp_a3, arg1->unk_14);

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetDepthImage(POLY_OPA_DISP++, arg1->unk_20);

    {
        Vp* vp = GRAPH_ALLOC(gfxCtx, sizeof(Vp));
        Mtx* sp84 = GRAPH_ALLOC(gfxCtx, sizeof(Mtx));
        Mtx* sp54 = GRAPH_ALLOC(gfxCtx, sizeof(Mtx));
        u16 sp7E;

        if (vp == NULL) {
            vp = &D_8085DCD0_jp;
        } else {
            vp->vp.vtrans[2] = 0x1FF;
            vp->vp.vtrans[3] = 0;
            vp->vp.vscale[0] = vp->vp.vtrans[0] = temp_a3 * 2;
            vp->vp.vscale[1] = vp->vp.vtrans[1] = temp_t1 * 2;
            vp->vp.vscale[2] = vp->vp.vtrans[2];
            vp->vp.vscale[3] = vp->vp.vtrans[3];
        }

        gSPViewport(POLY_OPA_DISP++, vp);

        if (temp_a3 - 1 != 0x7F) {
            guPerspective(sp84, &sp7E, 35.0f, temp_fv1 / temp_fa0, 1.0f, 2000.0f, 1.0f);
        } else {
            guPerspective(sp84, &sp7E, 20.0f, temp_fv1 / temp_fa0, 100.0f, 800.0f, 1.0f);
        }

        gSPPerspNormalize(POLY_OPA_DISP++, sp7E);
        gSPMatrix(POLY_OPA_DISP++, sp84, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

        {
            f32 yEye;
            f32 zEye;

            if (angle == 0x4000) {
                angle = 0x4100;
            } else if (angle == -0x4000) {
                angle = -0x3F00;
            }

            yEye = sin_s(angle) * arg2 + xAt;
            zEye = cos_s(angle) * arg2;
            if ((angle < -0x4000) || (angle >= 0x4000)) {
                guLookAt(sp54, 0.0f, yEye, zEye, 0.0f, xAt, 0.0f, 0.0f, -1.0f, 0.0f);
            } else {
                guLookAt(sp54, 0.0f, yEye, zEye, 0.0f, xAt, 0.0f, 0.0f, 1.0f, 0.0f);
            }
        }

        gSPMatrix(POLY_OPA_DISP++, sp54, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
        gSPSetLights1(POLY_OPA_DISP++, D_8085DCE0_jp);
    }

    POLY_OPA_DISP = gfx_set_fog_nosync(POLY_OPA_DISP++, 0xFFU, 0xFFU, 0xFFU, 0xFF, 0x3D0, 0x500);

    CLOSE_DISPS(gfxCtx);
}

u8 func_8085C7A4_jp(u16 arg0) {
    return arg0;
}

#ifdef NON_EQUIVALENT
// float messed up
// maybe equivalent, but hard to tell
void mSM_draw_item(GraphicsContext* gfxCtx, f32 arg1, f32 arg2, f32 arg3, u16 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    struct_8085DCF8* var_a1; // spAC
    s32 pad;
    s32 var_a2;
    s32 var_a3;
    s32 var_v1;
    s32 temp_v0;
    void* var_a2_2;
    s32 temp;

    Gfx* gfx;

    var_a2 = -1;
    var_a3 = 0;
    if (arg3 < 0.05f) {
        return;
    }

    if (arg5 != 0) {
        if (arg7 >= 6) {
            var_a1 = &D_8085DD38_jp;
            if (arg7 >= 0xC) {
                var_a3 = 1;
            }
        } else {
            var_a1 = &D_8085DD10_jp[arg7];
        }
    } else if (((s32) arg4 >= 0x15B0) && ((s32) arg4 < 0x17AC)) {
        var_a1 = &D_8085DD00_jp;
    } else if (((s32) arg4 >= 0x1E3C) && ((s32) arg4 < 0x1EA0)) {
        var_a1 = &D_8085DD08_jp;
    } else if (((s32) (arg4 & 0xF000) >> 0xC) == 1) {
        var_a1 = &D_8085DCF8_jp;
    } else {
        temp_v0 = func_8085C7A4_jp(arg4);

        var_a2 = (s32) (arg4 & 0xF00) >> 8;
        if (var_a2 == 0xE) {
            // var_a1 = *(D_8085E460_jp + (var_a2 * 4)) + (arg7 * 8);
            var_a1 = &D_8085E460_jp[var_a2][arg7];
        } else if ((var_a2 == 0) || (var_a2 == 4) || (var_a2 == 6) || (var_a2 == 7) || (var_a2 == 0xA) || (var_a2 == 0xB)) {
            // var_a1 = *(D_8085E460_jp + (var_a2 * 4));
            var_a1 = &D_8085E460_jp[var_a2][0];
        } else if (var_a2 == 2) {
            if (((s32) arg4 >= 0x2204) && ((s32) arg4 < 0x2224)) {
                var_a1 = &D_8085DD88_jp;
            } else {
                var_a1 = &D_8085DD68_jp[temp_v0];
            }
        } else {
            //var_a1 = *(D_8085E460_jp + (var_a2 * 4)) + (temp_v0 * 8);
            var_a1 = &D_8085E460_jp[var_a2][temp_v0];
        }
    }

    if (((var_a2 == 3) || (var_a2 == 0xD)) && (arg7 != 0)) {
        var_a2_2 = var_a1->unk_0 + 0x20;
    } else {
        var_a2_2 = var_a1->unk_0;
    }

    OPEN_DISPS(gfxCtx);

    gfx = POLY_OPA_DISP;

    gDPPipeSync(gfx++);
    gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);


    if (arg6 != 0) {
        if (var_a3 != 0) {
            var_v1 = (s32) ((arg7 * -0xFF) + 0x17E8) / 13;
        } else {
            var_v1 = 0xFF;
        }

        gDPSetPrimColor(gfx++, 0, 0xFF, 255, 255, 255, var_v1);
    } else {
        var_v1 = 0xFF;

        gDPSetPrimColor(gfx++, 0, 0x64, 115, 160, 255, var_v1);
    }

    if (arg8 != 0) {
        gDPSetBlendColor(gfx++, 255, 255, 255, 40);
    } else if (var_v1 == 0xFF) {
        gDPSetBlendColor(gfx++, 255, 255, 255, 254);
        gDPSetCombineLERP(gfx++, TEXEL0, PRIMITIVE, PRIM_LOD_FRAC, PRIMITIVE, 0, 0, 0, TEXEL0, TEXEL0, PRIMITIVE, PRIM_LOD_FRAC, PRIMITIVE, 0, 0, 0, TEXEL0);
    } else {
        gDPSetBlendColor(gfx++, 255, 255, 255, 40);
        gDPSetCombineLERP(gfx++, TEXEL0, PRIMITIVE, PRIM_LOD_FRAC, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, PRIMITIVE, PRIM_LOD_FRAC, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
    }

    gDPPipeSync(gfx++);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPLoadTLUT_pal16(gfx++, 15, Lib_SegmentedToVirtual(var_a2_2));
    if (arg3) {}
    gDPLoadTextureBlock_4b(gfx++, Lib_SegmentedToVirtual(var_a1->unk_4), G_IM_FMT_CI, 32, 32, 15, G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    {
        s32 ar1;
        s32 ar2;
        s32 ar3;
        s32 ar4;
        s32 ar5;
        s32 ar6;
        s32 ar7;
        s32 ar8;
        s32 ar9;

        temp = (arg1 * 0.975f);

        ar1 = (s32) (((temp + 160.0f) - 12.0f * arg3) * 4.0f);
        ar2 = (s32) (((120.0f - arg2) - 12.0f * arg3) * 4.0f);
        ar3 = (s32) ((24.0f * arg3 + ((temp + 160.0f) - 12.0f * arg3)) * 4.0f);
        ar4 = (s32) ((24.0f * arg3 + ((120.0f - arg2) - 12.0f * arg3)) * 4.0f);
        ar5 = 0;
        ar6 = 0;
        ar7 = 0;
        ar8 = (s32) ((1.0f / arg3) * 1365.3334f);
        ar9 = (s32) ((1.0f / arg3) * 1365.3334f);

        gfx = func_800BE320_jp(gfx, ar1, ar2, ar3, ar4, ar5, ar6, ar7, ar8, ar9);
    }

    gDPPipeSync(gfx++);
    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetBlendColor(gfx++, 255, 255, 255, 8);
    gDPSetTexturePersp(gfx++, G_TP_PERSP);

    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(gfxCtx);
}
#else
void mSM_draw_item(GraphicsContext* gfxCtx, f32 arg1, f32 arg2, f32 arg3, u16 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/mSM_draw_item.s")
#endif

// maybe same struct as struct_8085DCF8?
typedef struct struct_8085E4A0 {
    /* 0x0 */ UNK_PTR unk_0;
    /* 0x4 */ UNK_PTR unk_4;
} struct_8085E4A0; // size = 0x8

extern struct_8085E4A0 D_8085E4A0_jp[];

extern Gfx D_C012370[]; // inv_item_model

#ifdef NON_MATCHING
// stack issues
void mSM_draw_mail(GraphicsContext* arg0, f32 arg1, f32 arg2, f32 arg3, struct_func_8085CE18_jp_arg4* arg4, s32 arg5, s32 arg6) {
    struct_8085E4A0* temp_a1;
    s32 var_t0;
    UNUSED s32 pad;
    Gfx* gfx;

    if (mMl_check_send_mail(arg4) != 0) {
        var_t0 = 2;
    } else if ((arg4->unk_26 == 4) || (arg4->unk_26 == 2)) {
        var_t0 = 4;
    } else {
        var_t0 = 0;
    }

    if (arg4->unk_24 != 0) {
        var_t0 += 1;
    }

    Matrix_scale(16.0f, 16.0f, 1.0f, MTXMODE_NEW);
    Matrix_translate(arg1, arg2, 140.0f, MTXMODE_APPLY);
    Matrix_scale(arg3, arg3, 1.0f, MTXMODE_APPLY);

    if (1) {}

    OPEN_DISPS(arg0);

    gfx = POLY_OPA_DISP;

    gDPPipeSync(gfx++);
    gSPMatrix(gfx++, _Matrix_to_Mtx_new(arg0), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    temp_a1 = &D_8085E4A0_jp[var_t0];

    gSPSegment(gfx++, 0x09, Lib_SegmentedToVirtual(temp_a1->unk_0));
    gSPSegment(gfx++, 0x0A, Lib_SegmentedToVirtual(temp_a1->unk_4));
    gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);
    gDPSetBlendColor(gfx++, 255, 255, 255, 40);

    if (arg5 != 0) {
        gDPSetPrimColor(gfx++, 0, 0xFF, 255, 255, 255, 255);
    } else {
        gDPSetPrimColor(gfx++, 0, 0x82, 255, 110, 105, 255);
    }

    if (arg6 == 0) {
        gDPSetCombineLERP(gfx++, TEXEL0, PRIMITIVE, PRIM_LOD_FRAC, PRIMITIVE, 0, 0, 0, TEXEL0, TEXEL0, PRIMITIVE, PRIM_LOD_FRAC, PRIMITIVE, 0, 0, 0, TEXEL0);
    }

    gSPDisplayList(gfx++, D_C012370);
    gDPPipeSync(gfx++);
    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetBlendColor(gfx++, 255, 255, 255, 8);

    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(arg0);
}
#else
void mSM_draw_mail(GraphicsContext* arg0, f32 arg1, f32 arg2, f32 arg3, struct_func_8085CE18_jp_arg4* arg4, s32 arg5, s32 arg6);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/mSM_draw_mail.s")
#endif

void func_8085D094_jp(mSM* arg0) {
    struct_8085E9B0_unk_10000* sp2C = &arg0->unk_2C->unk_10000;
    void* vram;
    s32 romStart;

    if (sp2C->unk_04) {
        return;
    }

    //! FAKE: needs s32 instead of unsigned type
    romStart = SEGMENT_ROM_START(segment_00A58000);

    vram = sp2C->unk_00;
    sp2C->unk_08 = vram;

    DmaMgr_RequestSyncDebug(vram, romStart, SEGMENT_ROM_SIZE(segment_00A58000), "../m_submenu_ovl.c", 0x7C0);
    sp2C->unk_00 = (void* ) ALIGN16(SEGMENT_ROM_SIZE(segment_00A58000) + (uintptr_t)vram);

    sp2C->unk_04 = 1;
}

void mSM_ovl_prog_seg(mSM* arg0, struct_8085E4D0* arg1) {
    struct_8085E9B0_unk_10000* temp;
    UNUSED s32 pad;
    void* allocatedVram;
    struct_8085E4D0_unk_10 temp_a1;
    struct_8085E4D0_unk_10 new_var;

    temp = &arg0->unk_2C->unk_10000;
    if (arg1->unk_1C == 1) {
        new_var = arg1->unk_10;
        new_var(arg0);
        return;
    }

    allocatedVram = arg0->linkedAllocEnd;
    ovlmgr_Load(arg1->vromStart, arg1->vromEnd, arg1->vramStart, arg1->vramEnd, allocatedVram);
    arg0->linkedAllocEnd =
        (void*)((uintptr_t)allocatedVram + ALIGN64((uintptr_t)arg1->vramEnd - (uintptr_t)arg1->vramStart));

    temp_a1 = (void*)((uintptr_t)allocatedVram + (uintptr_t)arg1->unk_10 - (uintptr_t)arg1->vramStart);
    temp_a1(arg0);
    arg1->unk_10 = temp_a1;

    //! FAKE
dummy_label_595693:
    arg1->unk_14 = (void*)((uintptr_t)allocatedVram + (uintptr_t)arg1->unk_14 - (uintptr_t)arg1->vramStart);
    arg1->unk_18 = (void*)((uintptr_t)allocatedVram + (uintptr_t)arg1->unk_18 - (uintptr_t)arg1->vramStart);

    arg1->unk_1C = 1;
    temp->unk_68[temp->unk_64] = arg1;
    temp->unk_64++;

    //! FAKE
    if (temp_a1) {}
}

void mSM_set_other_seg(mSM* arg0) {
    s32 temp = arg0->unk_08;
    u32 var_v1 = D_8085E7D0_jp[temp];

    if (var_v1 & 2) {
        func_8085D094_jp(arg0);
    }
    if (var_v1 & 4) {
        mSM_ovl_prog_seg(arg0, &mSM_program_dlftbl[0x15]);
    }
    if (var_v1 & 8) {
        mSM_ovl_prog_seg(arg0, &mSM_program_dlftbl[0x16]);
    }
    if (var_v1 & 0x10) {
        mSM_ovl_prog_seg(arg0, &mSM_program_dlftbl[0x17]);
    }
}

void mSM_set_before_menu_proc(mSM* arg0) {
    s32 temp_v0 = arg0->unk_04;
    struct_8085E9B0_unk_10088* temp;

    mSM_program_dlftbl[temp_v0].unk_18(arg0);
    arg0->unk_08 = temp_v0;

    //! FAKE
    if (((!temp_v0) && (!temp_v0)) && (!temp_v0)) {}

    temp = &arg0->unk_2C->unk_10088[temp_v0];

    temp->unk_14 = 0;
}

void mSM_set_new_seg(mSM* arg0) {
    s32 temp_v0;

    temp_v0 = arg0->unk_04;
    mSM_ovl_prog_seg(arg0, &mSM_program_dlftbl[temp_v0]);
    arg0->unk_08 = temp_v0;
}

void mSM_set_new_start_data(mSM* arg0) {
    s32 temp_v0 = arg0->unk_04;
    struct_8085E9B0_unk_10088* temp_v1 = &arg0->unk_2C->unk_10088[temp_v0];
    f32* temp_a1 = D_FLT_8085E7E8_jp[temp_v0];

    temp_v1->unk_00 = temp_v0;
    temp_v1->unk_18 = temp_a1[0];
    temp_v1->unk_1C = temp_a1[1];
    temp_v1->unk_20 = temp_a1[2];
    temp_v1->unk_24 = temp_a1[3];
    temp_v1->unk_38 = arg0->unk_10;
    temp_v1->unk_3C = arg0->unk_14;
    temp_v1->unk_40 = arg0->unk_18;
    temp_v1->unk_44 = arg0->unk_1C;

    if ((temp_v0 == 1) && (arg0->unk_10 == 0xE)) {
        temp_v1->unk_18 = -300.0f;
    }
}

void func_8085D43C_jp(mSM* arg0, void** arg1, func_8085D43C_jp_arg2* arg2) {
    void* temp_a0 = arg0->unk_2C->unk_10000.unk_00;
    size_t size;

    *arg1 = temp_a0;
    size = arg2->vromEnd - arg2->vromStart;
    DmaMgr_RequestSyncDebug(temp_a0, arg2->vromStart, size, "../m_submenu_ovl.c", 2307);
    arg0->unk_2C->unk_10000.unk_00 = (void*)ALIGN16((uintptr_t)size + (uintptr_t)temp_a0);
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/mSM_move_chg_base.s")

void mSM_make_trigger_data(mSM* arg0) {
    s32 var_a0 = (getButton() & 0xF) | getTrigger();
    struct_8085E9B0_unk_10670* temp_v1 = &arg0->unk_2C->unk_10670;

    if (gamePT->controller.moveR > 0.5f) {
        u16 temp = gamePT->controller.moveAngle + 0x2000;

        var_a0 |= D_8085E938_jp[temp >> 0xE];
    }

    if (var_a0 == temp_v1->unk_20) {
        if (temp_v1->unk_24 > 0) {
            temp_v1->unk_24--;
            var_a0 = 0;
        } else {
            temp_v1->unk_24 = 1;
        }
    } else {
        temp_v1->unk_20 = var_a0;
        temp_v1->unk_24 = 0xC;
    }

    temp_v1->unk_1C = var_a0;
}

#if 0
void mSM_save_before_func(mSM* arg0) {
    s32 temp_a2;
    struct_8085E9B0* temp_v0;
    struct_8085E9B0_unk_10088* temp_v1;

    temp_v1 = &arg0->unk_2C->unk_10088[arg0->unk_04];
    temp_v0 = arg0->unk_2C;
    temp_a2 = arg0->unk_08;
    temp_v1->unk_08 = temp_a2;
    temp_v1->unk_0C = temp_v0->unk_10670.unk_00;
    temp_v1->unk_10 = temp_v0->unk_10670.unk_04;
    temp_v0->unk_10088[temp_a2].unk_14 = arg0->unk_04;
}
#else
void mSM_save_before_func(mSM* arg0);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/mSM_save_before_func.s")
#endif

void mSM_set_proc(mSM* arg0) {
    mSM_save_before_func(arg0);
    mSM_set_new_start_data(arg0);
    mSM_set_new_seg(arg0);
    mSM_set_other_seg(arg0);
}

void mSM_tex_move(mSM* arg0) {
    struct_8085E9B0_unk_10670* temp_v0;

    temp_v0 = &arg0->unk_2C->unk_10670;
    temp_v0->unk_28 += 0.707f;
    temp_v0->unk_2C += 0.707f;

    while (temp_v0->unk_28 >= 1024.0f) {
        temp_v0->unk_28 -= 1024.0f;
    }

    while (temp_v0->unk_2C >= 1024.0f) {
        temp_v0->unk_2C -= 1024.0f;
    }
}

typedef struct struct_mSM_return_func_arg1 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x4];
    /* 0x04 */ UNK_TYPE unk_04;
    /* 0x08 */ UNK_TYPE unk_08;
    /* 0x0C */ UNK_TYPE unk_0C;
    /* 0x10 */ UNK_TYPE unk_10;
    /* 0x14 */ UNK_TYPE unk_14;
    /* 0x18 */ UNK_TYPE1 unk_18[0x14];
    /* 0x2C */ UNK_TYPE unk_2C;
    /* 0x30 */ UNK_TYPE unk_30;
} struct_mSM_return_func_arg1; // size >= 0x34

#if 0
void mSM_return_func(mSM* arg0, struct_mSM_return_func_arg1* arg1) {
    s32 temp_t6;
    struct_8085E9B0* temp_v1;
    struct_8085E9B0_unk_10088* temp_v0;

    if (arg1->unk_14 != 0) {
        temp_v1 = arg0->unk_2C;
        temp_v0 = &temp_v1->unk_10088[arg1->unk_14];
        temp_v0->unk_08 = arg1->unk_08;
        temp_v0->unk_0C = arg1->unk_0C;
        temp_v0->unk_10 = arg1->unk_10;
        temp_v1->unk_10088[arg1->unk_14].unk_14 = arg1->unk_14;
    } else {
        temp_v1 = arg0->unk_2C;
        arg0->unk_04 = arg1->unk_08;
        if (arg0->unk_04 == 0) {
            while (temp_v1->unk_10000.unk_64 != 0) {
                temp_t6 = temp_v1->unk_10000.unk_64 - 1;
                temp_v1->unk_10000.unk_64 = temp_t6;
                temp_v1->unk_10000.unk_68[temp_t6]->unk_14(arg0);
            }
            arg0->moveProcIndex = MSM_MOVE_PROC_END;
            arg0->play = none_proc1;
            arg0->unk_08 = arg1->unk_08;
            arg0->unk_2C->unk_10670.unk_00 = none_proc1;
            arg0->unk_2C->unk_10670.unk_04 = none_proc1;
        } else {
            mSM_set_before_menu_proc(arg0);
        }
    }

    arg1->unk_2C = 0;
    arg1->unk_08 = 0;
    arg1->unk_14 = 0;
    arg1->unk_04 = 0;
    arg1->unk_30 = 0;
}
#else
void mSM_return_func(mSM* arg0, struct_mSM_return_func_arg1* arg1);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/mSM_return_func.s")
#endif

s32 mSM_move_menu(f32* arg0, f32* arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    if (((*arg0 - arg3) * arg5) >= 0.0f) {
        *arg1 *= arg2;
        if (*arg1 < 1.0f) {
            *arg1 = 1.0f;
        } else if (*arg1 > 75.0f) {
            *arg1 = 75.0f;
        }
    }

    *arg0 += *arg1 * arg5;
    if (((*arg0 - arg4) * arg5) > 0.0f) {
        *arg0 = arg4;
        return 1;
    }

    return 0;
}

void mSM_move_Move(mSM* arg0, struct_mSM_move_Move_arg1* arg1) {
    f32 var_fv0;
    s32 temp_t0 = arg1->unk_34;
    struct_8085E948* temp_v0 = &D_8085E948_jp[temp_t0 & 1];
    s32 index;
    s32 new_var;

    if (temp_t0 & 2) {
        var_fv0 = -1.0f;
    } else {
        var_fv0 = 1.0f;
    }

    index = (temp_t0 >> 2);

    if (mSM_move_menu(&arg1->unk_18[index], &arg1->unk_20[index], temp_v0->unk_0, temp_v0->unk_4 * var_fv0, temp_v0->unk_8 * var_fv0, temp_v0->unk_C * var_fv0) == 1) {
        arg1->unk_04 = arg1->unk_30;
    }

    // truncate
    new_var = arg1->unk_18[index];
    arg1->unk_18[index] = new_var;
}

void mSM_move_End_(mSM* arg0, struct_mSM_return_func_arg1* arg1) {
    mSM_return_func(arg0, arg1);
}

void mSM_menu_ovl_move(mSM* arg0) {
    struct_8085E9B0_unk_10670* sp24 = &arg0->unk_2C->unk_10670;

    mSM_make_trigger_data(arg0);
    if (arg0->unk_04 != arg0->unk_08) {
        mSM_set_proc(arg0);
    }
    mSM_tex_move(arg0);
    sp24->unk_00(arg0);
}

void mSM_menu_ovl_draw(mSM* arg0, Game_Play* game_play) {
    mSM_setup_view(arg0, game_play->state.gfxCtx, 1);
    arg0->unk_2C->unk_10670.unk_04(arg0, game_play);
}

#if 0
void mSM_menu_ovl_init(mSM* arg0) {
    void* var_v1;

    arg0->unk_2C = &ovl_base;
    bzero(&ovl_base, 0x10730);
    if (arg0->unk_00 != 4) {
        var_v1 = gamePT + 0x110;
    } else {
        var_v1 = gamePT + 0x2FC;
    }
    ovl_base.unk_10000 = (s32) var_v1->unk_1818;
    arg0->unk_8 = 0;
    ovl_base.unk_00000[0x10670] = none_proc1;
    ovl_base.unk_00000[0x10670] = none_proc1;
    ovl_base.unk_00000[0x10678] = none_proc1;
    ovl_base.unk_00000[0x10678] = none_proc1;
    ovl_base.unk_00000[0x10680] = none_proc1;
    ovl_base.unk_00000[0x10680] = none_proc1;
    ovl_base.unk_00000[0x10696] = 0x2000;
    arg0->unk_2C->unk_106A4 = mSM_return_func;
    arg0->unk_2C->unk_106A8 = mSM_move_Move;
    arg0->unk_2C->unk_106AC = mSM_move_End_;
    arg0->unk_2C->unk_106B0 = mSM_move_chg_base;
    arg0->unk_2C->unk_106B4 = mSM_set_char_matrix;
    arg0->unk_2C->unk_106B8 = mSM_cbuf_copy;
    arg0->unk_2C->unk_106BC = func_8085C20C_jp;
    arg0->unk_2C->unk_106C0 = mSM_draw_item;
    arg0->unk_2C->unk_106C4 = mSM_draw_mail;
    arg0->unk_2C->unk_106C8 = mSM_setup_view;
    arg0->unk_2C->unk_106CC = func_8085D43C_jp;
    mSM_set_proc(arg0);
    arg0->play = mSM_menu_ovl_move;
    arg0->draw = (void (*)(mSM*, struct Game_Play*)) mSM_menu_ovl_draw;
    mSM_menu_ovl_move(arg0);
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/mSM_menu_ovl_init.s")
#endif
