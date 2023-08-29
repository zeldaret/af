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
#include "overlays/gamestates/ovl_play/m_play.h"
#include "overlays/gamestates/ovl__00743CD0/_00743CD0.h"

extern struct_8085E9B0 ovl_base;

extern struct_8085E4D0 mSM_program_dlftbl[];

extern s32 D_8085E938_jp[];
extern f32 D_FLT_8085E7E8_jp[][4];
extern u8 D_8085E7D0_jp[];

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

    if (1) { } if (1) { } if (1) { }

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
    //Gfx* temp_v0_11;
    //Gfx* temp_v0_12;
    //Gfx* temp_v0_13;
    //Gfx* temp_v0_14;
    //Gfx* temp_v0_15;
    //Gfx* temp_v0_16;
    //Gfx* temp_v0_17;
    //Gfx* temp_v0_6;
    //Gfx* temp_v0_8;
    //Gfx* temp_v0_9;
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
    if (-(s32) temp_v0 >= arg2) {
        return;
    }

    temp_a0 = render->unk_06;
    if (1) { } if (1) { } if (1) { } if (1) { }
    if (-(s32) temp_a0 >= arg3) {
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
        spCC = (s32) temp_v0;
        var_ra = 0xF0;
        var_a1 = var_t3;
        var_t1 = var_v1;
        sp9C = render->unk_14;
        var_t2 = arg3;
        var_a2 = arg2;
        sp98 = gfxCtx->unk_2E4;
    }

    var_a3 = 0x1000 / (s32) (((var_t5 + 3) & ~3) * 2);
    if (arg4 != 0) {
        sp8C = POLY_OPA_DISP;
        render->unk_00 = 0x140;
        render->unk_02 = 0xF0;
        render->unk_10 = gfxCtx->unk_2E4;
        PreRender_CopyRGBC(render, &sp8C, arg2 - var_t3, arg3 - var_v1);
        POLY_OPA_DISP = sp8C;
    } else {
        gDPPipeSync(POLY_OPA_DISP++);
        gSPClearGeometryMode(POLY_OPA_DISP++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING | 0x0040F9FA);

        gDPSetOtherMode(POLY_OPA_DISP++, G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_NONE | G_CYC_COPY | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PRIM | G_RM_NOOP | G_RM_NOOP2);

        //temp_v0_5 = gfxCtx->polyOpa.p;
        //gfxCtx->polyOpa.p = temp_v0_5 + 8;
        //temp_v0_5->words.w0 = ((var_t4 - 1) & 0xFFF) | 0xFF100000;
        //temp_v0_5->words.w1 = (u32) sp98;
        gDPSetColorImage(POLY_OPA_DISP++, G_IM_FMT_RGBA, G_IM_SIZ_16b, var_t4, sp98);

        //temp_v0_6 = gfxCtx->polyOpa.p;
        //gfxCtx->polyOpa.p = temp_v0_6 + 8;
        //temp_v0_6->words.w0 = 0xED000000;
        //temp_v0_6->words.w1 = (((s32) ((f32) var_t4 * 4.0f) & 0xFFF) << 0xC) | ((s32) ((f32) var_ra * 4.0f) & 0xFFF);
        gDPSetScissorFrac(POLY_OPA_DISP++, G_SC_NON_INTERLACE, 0, 0, (s32)var_t4 * 4.0f, (s32)var_ra * 4.0f);

        while ((s32) var_t0 > 0) {
            if ((s32) var_t0 < var_a3) {
                var_a3 = (s32) var_t0;
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
            gDPLoadTextureTile(POLY_OPA_DISP++, sp9C, G_IM_FMT_RGBA, G_IM_SIZ_16b, spCC, 0, var_a1, var_t1, temp_v0_7, temp_a2 - 1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);



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
            gSPTextureRectangle(POLY_OPA_DISP++, (var_a2 * 4), (var_t2 * 4), (((var_a2 + var_t5) - 1) * 4), ((var_t2 + var_a3 - 1) * 4), G_TX_RENDERTILE, (var_a1 << 0x5), (var_t1 << 5), 0x1000, 0x0400);

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

typedef struct struct_func_8085C20C_jp_arg1 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x4];
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ UNK_TYPE1 unk_08[0xC];
    /* 0x14 */ UNK_TYPE unk_14;
    /* 0x18 */ UNK_TYPE1 unk_18[0x8];
    /* 0x20 */ UNK_TYPE unk_20;
} struct_func_8085C20C_jp_arg1; // size > 0x24

extern s16 D_8085DCD0_jp;

extern Lightsn D_8085DCE0_jp;

#if 0
void func_8085C20C_jp(GraphicsContext* gfxCtx, struct_func_8085C20C_jp_arg1* arg1, f32 arg2, f32 arg3, s16 arg4) {
    Mtx* sp84;
    u16 sp7E;
    f32 sp6C;
    Mtx* sp54;
    Gfx* temp_a0;
    Gfx* temp_a0_10;
    Gfx* temp_a0_11;
    Gfx* temp_a0_12;
    Gfx* temp_a0_13;
    Gfx* temp_a0_14;
    Gfx* temp_a0_15;
    Gfx* temp_a0_16;
    Gfx* temp_a0_17;
    Gfx* temp_a0_18;
    Gfx* temp_a0_19;
    Gfx* temp_a0_21;
    Gfx* temp_a0_22;
    Gfx* temp_a0_23;
    Gfx* temp_a0_24;
    Gfx* temp_a0_25;
    Gfx* temp_a0_26;
    Gfx* temp_a0_27;
    Gfx* temp_a0_28;
    Gfx* temp_a0_2;
    Gfx* temp_a0_3;
    Gfx* temp_a0_4;
    Gfx* temp_a0_5;
    Gfx* temp_a0_6;
    Gfx* temp_a0_7;
    Gfx* temp_a0_8;
    Gfx* temp_a0_9;
    Mtx* temp_t0_2;
    Mtx* temp_t0_3;
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fv1;
    f32 temp_fv1_2;
    s16 temp_a0_20;
    s16 temp_t4;
    s16 temp_t9;
    s16 temp_v1_2;
    s16 var_a0;
    s16* temp_t0;
    s16* var_v0;
    s32 temp_a1;
    u16 temp_a3;
    u16 temp_t1;
    u32 temp_v1;

    temp_a3 = arg1->unk_04;
    temp_t1 = arg1->unk_06;

    OPEN_DISPS(gfxCtx);

    #if 0
    temp_a0 = gfxCtx->polyOpa.p;
    gfxCtx->polyOpa.p = temp_a0 + 8;
    temp_a0->words.w1 = 0x00000000;
    temp_a0->words.w0 = 0xDB060000;

    temp_a0_2 = gfxCtx->polyOpa.p;
    gfxCtx->polyOpa.p = temp_a0_2 + 8;
    temp_a0_2->words.w1 = 0x00000000;
    temp_a0_2->words.w0 = 0xE7000000;

    temp_a0_3 = gfxCtx->polyOpa.p;
    gfxCtx->polyOpa.p = temp_a0_3 + 8;
    temp_a0_3->words.w1 = 0x00000000;
    temp_a0_3->words.w0 = 0xD9000000;

    temp_a0_4 = gfxCtx->polyOpa.p;
    gfxCtx->polyOpa.p = temp_a0_4 + 8;
    temp_a0_4->words.w1 = 0xFFFFFFFF;
    temp_a0_4->words.w0 = 0xD7000000;

    temp_a0_5 = gfxCtx->polyOpa.p;
    gfxCtx->polyOpa.p = temp_a0_5 + 8;
    temp_a0_5->words.w1 = 0xFFFE793C;
    temp_a0_5->words.w0 = 0xFCFFFFFF;

    temp_a0_6 = gfxCtx->polyOpa.p;
    gfxCtx->polyOpa.p = temp_a0_6 + 8;
    temp_a0_6->words.w1 = 0x00000000;
    temp_a0_6->words.w0 = 0xEF382C30;

    temp_a0_7 = gfxCtx->polyOpa.p;
    gfxCtx->polyOpa.p = temp_a0_7 + 8;
    temp_a0_7->words.w1 = 0x00220405;
    temp_a0_7->words.w0 = 0xD9000000;
    #endif
    gSPSegment(POLY_OPA_DISP++, 0x00, 0x00000000);
    gDPPipeSync(POLY_OPA_DISP++);
    gSPClearGeometryMode(POLY_OPA_DISP++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING | 0x0040F9FA);
    gSPTexture(POLY_OPA_DISP++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF);
    gDPSetCombineMode(POLY_OPA_DISP++, G_CC_SHADE, G_CC_SHADE);
    gDPSetOtherMode(POLY_OPA_DISP++, G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_FILL | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PIXEL | G_RM_NOOP | G_RM_NOOP2);
    gSPLoadGeometryMode(POLY_OPA_DISP++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH);

    temp_fv1 = (f32) temp_a3;
    temp_a1 = temp_a3 - 1;
    temp_fa0 = (f32) temp_t1;
    #if 0
    temp_a0_8 = gfxCtx->polyOpa.p;
    gfxCtx->polyOpa.p = temp_a0_8 + 8;
    temp_a0_8->words.w0 = 0xED000000;
    temp_a0_8->words.w1 = (((s32) (temp_fv1 * 4.0f) & 0xFFF) << 0xC) | ((s32) (temp_fa0 * 4.0f) & 0xFFF);
    #endif
    gDPSetScissorFrac(POLY_OPA_DISP++, G_SC_NON_INTERLACE, 0, 0, (temp_fv1 * 4.0f), (temp_fa0 * 4.0f));

    #if 0
    temp_a0_9 = gfxCtx->polyOpa.p;
    gfxCtx->polyOpa.p = temp_a0_9 + 8;
    temp_a0_9->words.w1 = 0x00000001;
    temp_a0_9->words.w0 = 0xDB040004;

    temp_a0_10 = gfxCtx->polyOpa.p;
    gfxCtx->polyOpa.p = temp_a0_10 + 8;
    temp_a0_10->words.w1 = 0x00000001;
    temp_a0_10->words.w0 = 0xDB04000C;

    temp_a0_11 = gfxCtx->polyOpa.p;
    gfxCtx->polyOpa.p = temp_a0_11 + 8;
    temp_a0_11->words.w1 = 0x0000FFFF;
    temp_a0_11->words.w0 = 0xDB040014;

    temp_a0_12 = gfxCtx->polyOpa.p;
    gfxCtx->polyOpa.p = temp_a0_12 + 8;
    temp_a0_12->words.w1 = 0x0000FFFF;
    temp_a0_12->words.w0 = 0xDB04001C;
    #endif
    gSPClipRatio(POLY_OPA_DISP++, FRUSTRATIO_1);


    #if 0
    temp_a0_13 = gfxCtx->polyOpa.p;
    gfxCtx->polyOpa.p = temp_a0_13 + 8;
    temp_a0_13->words.w0 = (temp_a1 & 0xFFF) | 0xFF100000;
    temp_a0_13->words.w1 = arg1->unk_20;
    #endif
    gDPSetColorImage(POLY_OPA_DISP++, G_IM_FMT_RGBA, G_IM_SIZ_16b, temp_a1, arg1->unk_20);

    #if 0
    temp_a0_14 = gfxCtx->polyOpa.p;
    gfxCtx->polyOpa.p = temp_a0_14 + 8;
    temp_a0_14->words.w1 = 0xFFFCFFFC;
    temp_a0_14->words.w0 = 0xF7000000;
    #endif
    gDPSetFillColor(POLY_OPA_DISP++, 0xFFFCFFFC);

    #if 0
    temp_a0_15 = gfxCtx->polyOpa.p;
    gfxCtx->polyOpa.p = temp_a0_15 + 8;
    temp_a0_15->words.w0 = ((temp_a1 & 0x3FF) << 0xE) | 0xF6000000 | (((temp_t1 - 1) & 0x3FF) * 4);
    temp_a0_15->words.w1 = 0x00000000;
    #endif
    gDPFillRectangle(POLY_OPA_DISP++, 0, 0, temp_a1, temp_t1 - 1);

    #if 0
    temp_a0_16 = gfxCtx->polyOpa.p;
    gfxCtx->polyOpa.p = temp_a0_16 + 8;
    temp_a0_16->words.w1 = 0x00000000;
    temp_a0_16->words.w0 = 0xE7000000;
    #endif
    gDPPipeSync(POLY_OPA_DISP++);

    #if 0
    temp_a0_17 = gfxCtx->polyOpa.p;
    gfxCtx->polyOpa.p = temp_a0_17 + 8;
    temp_a0_17->words.w0 = (temp_a1 & 0xFFF) | 0xFF100000;
    temp_a0_17->words.w1 = arg1->unk_14;
    #endif
    gDPSetColorImage(POLY_OPA_DISP++, G_IM_FMT_RGBA, G_IM_SIZ_16b, temp_a1, arg1->unk_14);

    #if 0
    temp_a0_18 = gfxCtx->polyOpa.p;
    gfxCtx->polyOpa.p = temp_a0_18 + 8;
    temp_a0_18->words.w1 = 0x00000000;
    temp_a0_18->words.w0 = 0xE7000000;

    temp_a0_19 = gfxCtx->polyOpa.p;
    gfxCtx->polyOpa.p = temp_a0_19 + 8;
    temp_a0_19->words.w0 = 0xFE000000;
    temp_a0_19->words.w1 = arg1->unk_20;
    #endif
    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetDepthImage(POLY_OPA_DISP++, arg1->unk_20);


    #if 0
    temp_t0 = (uintptr_t)gfxCtx->polyOpa.d - 0x10;
    var_v0 = temp_t0;
    temp_t0_2 = (uintptr_t)temp_t0 - 0x40;
    sp84 = temp_t0_2;
    temp_t0_3 = temp_t0_2 - 0x40;
    gfxCtx->polyOpa.d = temp_t0_3;
    #endif
    var_v0 = GRAPH_ALLOC(gfxCtx, 0x10);
    sp84 = GRAPH_ALLOC(gfxCtx, 0x40);

    if (var_v0 == NULL) {
        var_v0 = &D_8085DCD0_jp;
    } else {
        *var_v0 = 0x1FF;
        *var_v0 = 0;
        temp_t9 = *var_v0;
        temp_t4 = *var_v0;
        temp_v1_2 = temp_a3 * 2;
        temp_a0_20 = temp_t1 * 2;
        *var_v0 = temp_v1_2;
        *var_v0 = temp_v1_2;
        *var_v0 = temp_a0_20;
        *var_v0 = temp_a0_20;
        *var_v0 = temp_t9;
        *var_v0 = temp_t4;
    }

    #if 0
    temp_a0_21 = gfxCtx->polyOpa.p;
    gfxCtx->polyOpa.p = temp_a0_21 + 8;
    temp_a0_21->words.w1 = (u32) var_v0;
    temp_a0_21->words.w0 = 0xDC080008;
    #endif
    gSPViewport(POLY_OPA_DISP++, var_v0);

    if (temp_a1 != 0x7F) {
        sp54 = temp_t0_3;
        guPerspective(sp84, &sp7E, 35.0f, temp_fv1 / temp_fa0, 1.0f, 2000.0f, 1.0f);
    } else {
        sp54 = temp_t0_3;
        guPerspective(sp84, &sp7E, 20.0f, temp_fv1 / temp_fa0, 100.0f, 800.0f, 1.0f);
    }

    gSPPerspNormalize(POLY_OPA_DISP++, sp7E);
    gSPMatrix(POLY_OPA_DISP++, sp84, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    var_a0 = arg4;
    if (var_a0 == 0x4000) {
        var_a0 = 0x4100;
    } else if (var_a0 == -0x4000) {
        var_a0 = -0x3F00;
    }
    arg4 = var_a0;
    temp_fa0_2 = (sin_s(var_a0) * arg2) + arg3;
    sp6C = temp_fa0_2;
    temp_fv1_2 = cos_s(arg4) * arg2;
    if ((arg4 < -0x4000) || (arg4 >= 0x4000)) {
        guLookAt(sp54, 0.0f, temp_fa0_2, temp_fv1_2, 0.0f, arg3, 0.0f, 0.0f, -1.0f, 0.0f);
    } else {
        guLookAt(sp54, 0.0f, temp_fa0_2, temp_fv1_2, 0.0f, arg3, 0.0f, 0.0f, 1.0f, 0.0f);
    }

    #if 0
    temp_a0_24 = gfxCtx->polyOpa.p;
    gfxCtx->polyOpa.p = temp_a0_24 + 8;
    temp_a0_24->words.w0 = 0xDA380005;
    temp_a0_24->words.w1 = (u32) sp54;

    temp_a0_25 = gfxCtx->polyOpa.p;
    gfxCtx->polyOpa.p = temp_a0_25 + 8;
    temp_a0_25->words.w1 = 0x18;
    temp_a0_25->words.w0 = 0xDB020000;

    temp_a0_26 = gfxCtx->polyOpa.p;
    gfxCtx->polyOpa.p = temp_a0_26 + 8;
    temp_a0_26->words.w1 = (u32) &D_8085DCE8_jp;
    temp_a0_26->words.w0 = 0xDC08060A;

    temp_a0_27 = gfxCtx->polyOpa.p;
    gfxCtx->polyOpa.p = temp_a0_27 + 8;
    temp_a0_27->words.w0 = 0xDC08090A;
    temp_a0_27->words.w1 = (u32) &D_8085DCE0_jp;
    #endif
    gSPMatrix(POLY_OPA_DISP++, sp54, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
    gSPSetLights1(POLY_OPA_DISP++, D_8085DCE0_jp);

    #if 0
    temp_a0_28 = gfxCtx->polyOpa.p;
    gfxCtx->polyOpa.p = temp_a0_28 + 8;
    gfxCtx->polyOpa.p = gfx_set_fog_nosync(temp_a0_28, 0xFFU, 0xFFU, 0xFFU, 0xFF, (s16) 0x3D0, (s16) 0x500);
    #endif
    POLY_OPA_DISP = gfxCtx->polyOpa.p = gfx_set_fog_nosync(POLY_OPA_DISP++, 0xFFU, 0xFFU, 0xFFU, 0xFF, (s16) 0x3D0, (s16) 0x500);

    CLOSE_DISPS(gfxCtx);
}

#else
void func_8085C20C_jp(GraphicsContext* gfxCtx, struct_func_8085C20C_jp_arg1* arg1, f32 arg2, f32 arg3, s16 arg4);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085C20C_jp.s")
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085C7A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085C7B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085CE18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085D094_jp.s")

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
    arg0->linkedAllocEnd = (void*)((uintptr_t)allocatedVram + ALIGN64((uintptr_t)arg1->vramEnd - (uintptr_t)arg1->vramStart));

    temp_a1 = (void*)((uintptr_t)allocatedVram + (uintptr_t)arg1->unk_10 - (uintptr_t)arg1->vramStart);
    temp_a1(arg0);
    arg1->unk_10 = temp_a1;

    dummy_label_595693:
    arg1->unk_14 = (void*)((uintptr_t)allocatedVram + (uintptr_t)arg1->unk_14 - (uintptr_t)arg1->vramStart);
    arg1->unk_18 = (void*)((uintptr_t)allocatedVram + (uintptr_t)arg1->unk_18 - (uintptr_t)arg1->vramStart);

    arg1->unk_1C = 1;
    temp->unk_68[temp->unk_64] = arg1;
    temp->unk_64++;

    //! FAKE
    if (temp_a1) {}
}

#if 0
void mSM_set_other_seg(mSM* arg0) {
    u8 var_v1;

    var_v1 = D_8085E7D0_jp[arg0->unk_08];
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
#else
void mSM_set_other_seg(mSM* arg0);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/mSM_set_other_seg.s")
#endif

#if 0
void mSM_set_before_menu_proc(mSM* arg0) {
    s32 temp_v0;


    temp_v0 = arg0->unk_04;
    mSM_program_dlftbl[temp_v0].unk_18(arg0);
    arg0->unk_08 = temp_v0;

    arg0->unk_2C->unk_10088[temp_v0].unk_14 = 0;
}
#else
void mSM_set_before_menu_proc(mSM* arg0);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/mSM_set_before_menu_proc.s")
#endif

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

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/mSM_return_func.s")

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

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/mSM_move_Move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/mSM_move_End_.s")

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
    arg0->unk_2C->unk_106C0 = func_8085C7B8_jp;
    arg0->unk_2C->unk_106C4 = func_8085CE18_jp;
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
