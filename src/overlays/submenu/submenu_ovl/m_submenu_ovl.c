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

typedef struct struct_8085E4D0 {
    /* 0x00 */ RomOffset unk_00;
    /* 0x00 */ RomOffset unk_04;
    /* 0x08 */ UNK_TYPE4 unk_08;
    /* 0x08 */ UNK_TYPE4 unk_0C;
    /* 0x08 */ UNK_FUN_PTR unk_10;
    /* 0x08 */ UNK_TYPE4 unk_14;
    /* 0x08 */ UNK_TYPE4 unk_18;
    /* 0x08 */ UNK_TYPE4 unk_1C;
} struct_8085E4D0; // size = 0x20
extern struct_8085E4D0 D_8085E4D0_jp[];

extern s32 D_8085E938_jp[];
extern f32 D_FLT_8085E7E8_jp[][4];
extern u8 D_8085E7D0_jp[];

void func_8085BAC0_jp(mSM* arg0, GraphicsContext* gfxCtx, s32 arg1) {
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

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085BCD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085BD08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085C20C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085C7A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085C7B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085CE18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085D094_jp.s")

#if 0
void func_8085D128_jp(mSM* arg0, struct_8085E4D0* arg1) {
    void* temp_t0_2; // sp34
    struct_8085E9B0* temp_t0;
    void* temp_v0; // sp2C
    void (*temp_a1)(mSM*); // sp28

    temp_t0 = arg0->unk_2C;
    if (arg1->unk_1C == 1) {
        arg1->unk_10(arg0);
        return;
    }

    temp_v0 = arg0->linkedAllocEnd;
    ovlmgr_Load(arg1->unk_00, arg1->unk_04, arg1->unk_08, arg1->unk_0C, temp_v0);
    arg0->linkedAllocEnd = (uintptr_t)temp_v0 + (((arg1->unk_0C - arg1->unk_08) + 0x3F) & ~0x3F);
    temp_a1 = ((uintptr_t)temp_v0 + (uintptr_t)arg1->unk_10) - arg1->unk_08;
    temp_a1(arg0);
    arg1->unk_10 = temp_a1;
    arg1->unk_14 = (s32) (((uintptr_t)temp_v0 + arg1->unk_14) - arg1->unk_08);
    arg1->unk_18 = (s32) (((uintptr_t)temp_v0 + arg1->unk_18) - arg1->unk_08);
    arg1->unk_1C = 1;
    temp_t0->unk_10068[temp_t0->unk_10064] = arg1;
    temp_t0->unk_10064++;
}
#else
void func_8085D128_jp(mSM* arg0, struct_8085E4D0* arg1);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085D128_jp.s")
#endif

#if 0
void func_8085D244_jp(mSM* arg0) {
    u8 var_v1;

    var_v1 = D_8085E7D0_jp[arg0->unk_08];
    if (var_v1 & 2) {
        func_8085D094_jp(arg0);
    }
    if (var_v1 & 4) {
        func_8085D128_jp(arg0, &D_8085E4D0_jp[0x15]);
    }
    if (var_v1 & 8) {
        func_8085D128_jp(arg0, &D_8085E4D0_jp[0x16]);
    }
    if (var_v1 & 0x10) {
        func_8085D128_jp(arg0, &D_8085E4D0_jp[0x17]);
    }
}
#else
void func_8085D244_jp(mSM* arg0);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085D244_jp.s")
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085D2EC_jp.s")

void func_8085D358_jp(mSM* arg0) {
    s32 temp_v0;

    temp_v0 = arg0->unk_04;
    func_8085D128_jp(arg0, &D_8085E4D0_jp[temp_v0]);
    arg0->unk_08 = temp_v0;
}

void func_8085D398_jp(mSM* arg0) {
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

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085D43C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085D4D4_jp.s")

void func_8085D500_jp(mSM* arg0) {
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
void func_8085D5D4_jp(mSM* arg0) {
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
void func_8085D5D4_jp(mSM* arg0);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085D5D4_jp.s")
#endif

void func_8085D638_jp(mSM* arg0) {
    func_8085D5D4_jp(arg0);
    func_8085D398_jp(arg0);
    func_8085D358_jp(arg0);
    func_8085D244_jp(arg0);
}

void func_8085D674_jp(mSM* arg0) {
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

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085D718_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085D860_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085D92C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085DA08_jp.s")

void func_8085DA28_jp(mSM* arg0) {
    struct_8085E9B0_unk_10670* sp24 = &arg0->unk_2C->unk_10670;

    func_8085D500_jp(arg0);
    if (arg0->unk_04 != arg0->unk_08) {
        func_8085D638_jp(arg0);
    }
    func_8085D674_jp(arg0);
    sp24->unk_00(arg0);
}

void func_8085DA9C_jp(mSM* arg0, Game_Play* game_play) {
    func_8085BAC0_jp(arg0, game_play->state.gfxCtx, 1);
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
    arg0->unk_2C->unk_106A4 = func_8085D718_jp;
    arg0->unk_2C->unk_106A8 = func_8085D92C_jp;
    arg0->unk_2C->unk_106AC = func_8085DA08_jp;
    arg0->unk_2C->unk_106B0 = func_8085D4D4_jp;
    arg0->unk_2C->unk_106B4 = func_8085BCD8_jp;
    arg0->unk_2C->unk_106B8 = func_8085BD08_jp;
    arg0->unk_2C->unk_106BC = func_8085C20C_jp;
    arg0->unk_2C->unk_106C0 = func_8085C7B8_jp;
    arg0->unk_2C->unk_106C4 = func_8085CE18_jp;
    arg0->unk_2C->unk_106C8 = func_8085BAC0_jp;
    arg0->unk_2C->unk_106CC = func_8085D43C_jp;
    func_8085D638_jp(arg0);
    arg0->play = func_8085DA28_jp;
    arg0->draw = (void (*)(mSM*, struct Game_Play*)) func_8085DA9C_jp;
    func_8085DA28_jp(arg0);
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/mSM_menu_ovl_init.s")
#endif
