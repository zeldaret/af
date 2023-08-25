#include "m_submenu_ovl.h"
#include "m_submenu.h"
#include "m_lib.h"
#include "game.h"
#include "sys_matrix.h"
#include "overlays/gamestates/ovl_play/m_play.h"

extern struct_8085E9B0 ovl_base;

typedef struct struct_8085E4D0 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x20];
} struct_8085E4D0; // size = 0x20
extern struct_8085E4D0 D_8085E4D0_jp[];

extern s32 D_8085E938_jp[];
extern f32 D_FLT_8085E7E8_jp[][4];

void func_8085BAC0_jp(mSM* arg0, GraphicsContext* gfxCtx, s32 arg1);

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085BAC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085BCD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085BD08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085C20C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085C7A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085C7B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085CE18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085D094_jp.s")

void func_8085D128_jp(mSM* arg0, struct_8085E4D0* arg1);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085D128_jp.s")

void func_8085D244_jp(mSM* arg0);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085D244_jp.s")

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
