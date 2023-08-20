#include "m_trademark.h"
#include "m_actor.h"
#include "m_common_data.h"
#include "m_event.h"
#include "m_field_info.h"
#include "m_npc.h"
#include "m_view.h"
#include "sys_math.h"
#include "sys_matrix.h"
#include "libc64/qrand.h"
#include "z_std_dma.h"
#include "67E840.h"
#include "69CB30.h"
#include "6B3DC0.h"
#include "6B8F20.h"
#include "6BFE60.h"
#include "6DE300.h"
#include "6DB420.h"
#include "6E0F50.h"
#include "6EC9E0.h"
#include "6EDD10.h"
#include "6F5550.h"
#include "segment_symbols.h"
#include "macros.h"

#include "overlays/gamestates/ovl_play/m_play.h"

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/gamestates/ovl_trademark/m_trademark/func_80804C40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/gamestates/ovl_trademark/m_trademark/func_80804CC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/gamestates/ovl_trademark/m_trademark/func_80804D18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/gamestates/ovl_trademark/m_trademark/trademark_goto_demo_scene.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/gamestates/ovl_trademark/m_trademark/func_80804EE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/gamestates/ovl_trademark/m_trademark/func_80804F78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/gamestates/ovl_trademark/m_trademark/func_80805104_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/gamestates/ovl_trademark/m_trademark/func_808052B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/gamestates/ovl_trademark/m_trademark/func_80805360_jp.s")

void trademark_cancel(Game_Trademark* this) {
    if ((this->unk_25A70 == 0) && (this->unk_25A6E == 4)) {
        if (common_data.unk_10AB0 != 0) {
            if (CHECK_FLAG_ALL(CONTROLLER1(gamePT)->press.button, START_BUTTON)) {
                this->unk_25A70 = 1;
            }
        }
    }
}

extern u8 D_80808520_jp[];
extern UNK_TYPE B_80808560_jp;
extern UNK_TYPE B_80818560_jp;

void trademark_move(Game_Trademark* this) {
    if (this->unk_25A6E == 0) {
        if (DECR(this->unk_25A68) == 0) {
            mBGMPsComp_make_ps_lost_fanfare(D_80808520_jp[mTD_get_titledemo_no()], 0x168);
            func_800D1A9C_jp(0x105);
            this->unk_25A60 = 0;
            this->unk_25A6E = 1;
        }
    }

    if ((func_80804C40_jp() != 0) && ((this->unk_25A6E == 3) || (this->unk_25A70 != 0))) {
        if (this->unk_25A60 < 0xFF) {
            this->unk_25A60 += 8;
        }

        if (this->unk_25A71 != 1) {
            if (func_8008F768_jp(&B_80808560_jp, &B_80818560_jp) == 1) {
                this->unk_25A71 = 1;
            }
        }

        if ((this->unk_25A60 >= 0xFF) && (this->unk_25A71 == 1)) {
            this->unk_25A60 = 0xFF;
            this->unk_25A6E = 5;
        }
    }
}

void trademark_draw(Game_Trademark* this);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/gamestates/ovl_trademark/m_trademark/trademark_draw.s")

void trademark_main(Game* thisx) {
    Game_Trademark* this = (Game_Trademark*)thisx;
    GraphicsContext* gfxCtx;

    fqrand();

    trademark_cancel(this);
    trademark_move(this);
    trademark_draw(this);

    gfxCtx = this->state.gfxCtx;
    game_debug_draw_last(&this->state, gfxCtx);
    game_draw_last(gfxCtx);

    if (this->unk_25A6E == 5) {
        this->unk_25A6E = 0;
        trademark_goto_demo_scene(this);
    }
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/gamestates/ovl_trademark/m_trademark/trademark_cleanup.s")

extern UNK_TYPE B_80828560_jp;
extern OSMesgQueue B_80828620_jp;
extern UNK_TYPE B_808286B0_jp;

void trademark_init(Game* thisx) {
    s32 pad;
    Game_Trademark* this = (Game_Trademark*)thisx;
    GraphicsContext* sp2C = this->state.gfxCtx;

    common_data_reinit();

    this->state.main = trademark_main;
    this->state.destroy = trademark_cleanup;

    initView(&this->view, sp2C);
    new_Matrix(&this->state);

    this->unk_25A60 = 0xFF;
    this->unk_25A66 = 0;
    this->unk_25A64 = 0x3C;
    this->unk_25A68 = 0;
    this->unk_0025C = 0;
    this->unk_00218 = 0;
    this->unk_25A6E = 0;
    this->unk_00208 = 0.0f;
    this->unk_0020C = 0.0f;
    this->unk_00210 = 0.0f;
    this->unk_00214 = 0.5f;
    this->unk_25A6A = 0;
    this->unk_25A6C = 0x13D0;
    this->unk_25A6F = 0;
    this->unk_25A70 = 0;
    this->unk_25A71 = 0;

    SetGameFrame(1);
    common_data.player_no = 0;
    common_data.unk_10008 = 0;
    common_data.scene_from_title_demo = -1U;
    func_80095414_jp();
    func_800ABAF0_jp();
    func_800AC1C8_jp();
    func_800BB0E8_jp();
    func_8008FA50_jp();
    func_8008F210_jp();

    func_80026E10_jp(&this->unk_00260, SEGMENT_ROM_START(segment_01136000), SEGMENT_ROM_SIZE(segment_01136000), "../m_trademark.c", 1081);
    func_800924CC_jp(&B_80828560_jp, &B_80828620_jp, &B_808286B0_jp);

    func_8005EAA0_jp(0);
    func_8007D91C_jp(func_800C8E08_jp());
}
