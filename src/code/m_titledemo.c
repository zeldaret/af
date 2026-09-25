#include "global.h"
#include "6EC9E0.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "m_player_lib.h"
#include "m_bgm.h"
#include "m_lib.h"
#include "m_event.h"
#include "overlays/actors/player_actor/m_player.h"

u16 func_800C8D40_jp(s32 titledemo_no, s32 key) {
    extern void* B_80144690_jp;
    extern u16* D_8010EDA8_jp[];

    SegmentBaseAddress[6] = (uintptr_t)B_80144690_jp - K0BASE;
    return ((u16*)Lib_SegmentedToVirtual(D_8010EDA8_jp[titledemo_no]))[key];
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_titledemo/func_800C8D98_jp.s")

UNK_RET mTD_demono_get(void) {
    extern s32 D_8010EDA4_jp;

    if (D_8010EDA4_jp == -1) {
        D_8010EDA4_jp = 1;
    } else {
        D_8010EDA4_jp++;
        if (D_8010EDA4_jp > 5) {
            D_8010EDA4_jp = 1;
        }
    }

    return D_8010EDA4_jp;
}

void mTD_player_keydata_init(Game_Play* game_play) {
    extern void func_800C8D98_jp(void);
    extern void func_800B5AA0_jp(u16 tool);
    extern s32 D_8010EDA0_jp;
    u16 angle;
    Player* player = get_player_actor_withoutCheck(game_play);

    if (mEv_CheckTitleDemo() > 0) {
        func_800C8D98_jp();
        func_800B5AA0_jp(func_800C8D40_jp(mEv_CheckTitleDemo() - 1, 4));
        angle = func_800C8D40_jp(mEv_CheckTitleDemo() - 1, 3);
        player->actor.shape.rot.y = angle;
        player->actor.world.rot.y = angle;
    }

    D_8010EDA0_jp = 0;
}

u16 func_800C8ECC_jp(void) {
    typedef struct {
        u16* data[5];
    } TitleDemoKeyTable;
    extern TitleDemoKeyTable D_8010EDBC_jp;
    extern void* B_80144690_jp;
    extern s32 D_8010EDA0_jp;
    u16* data;
    TitleDemoKeyTable keydata = D_8010EDBC_jp;

    SegmentBaseAddress[6] = (uintptr_t)B_80144690_jp - K0BASE;
    mEv_CheckTitleDemo();
    data = Lib_SegmentedToVirtual(keydata.data[mEv_CheckTitleDemo() - 1]);
    data += D_8010EDA0_jp;
    return *data;
}

void func_800C8F5C_jp(void) {
    extern u16 func_800C8ECC_jp(void);
    extern void func_800B5980_jp(u16 keydata);

    func_800B5980_jp(func_800C8ECC_jp());
}

void func_800C8F84_jp(Game_Play* game_play) {
    game_play->unk_1EE0 = 10;
    game_play->unk_1EE1 = 3;
    mPlib_request_main_invade_type1(game_play);
    mBGMPsComp_make_ps_wipe(0x521C);
}

void title_demo_move(Game_Play* game_play) {
    extern s32 D_8010EDA0_jp;

    if (mEv_CheckTitleDemo() > 0) {
        func_800C8F5C_jp();
        D_8010EDA0_jp++;
        if (D_8010EDA0_jp >= 1800) {
            func_800C8F84_jp(game_play);
        }
    }
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_titledemo/func_800C9010_jp.s")

void func_800C9088_jp(void) {
    extern u16 D_8010EDD0_jp;

    D_8010EDD0_jp = 1;
}

s32 mTD_get_titledemo_no(void) {
    extern s32 D_8010EDA4_jp;
    s32 titledemo_no = D_8010EDA4_jp;

    if (titledemo_no <= 0) {
        titledemo_no = 1;
    }

    return titledemo_no - 1;
}

s32 func_800C90BC_jp(void) {
    extern s32 D_8010EDA0_jp;
    s32 result = 1;

    if (D_8010EDA0_jp >= 1765) {
        result = 0;
    }

    return result;
}
