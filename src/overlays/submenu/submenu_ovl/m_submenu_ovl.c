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

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/mSM_cbuf_copy.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085C20C_jp.s")

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
    arg0->unk_2C->unk_10000.unk_00 = ALIGN16((uintptr_t)size + (uintptr_t)temp_a0);
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
