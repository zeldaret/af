#include "m_submenu.h"
#include "m_common_data.h"
#include "m_debug.h"
#include "m_lib.h"
#include "m_msg_main.h"
#include "m_player_lib.h"
#include "fault.h"
#include "ovlmgr.h"
#include "game.h"
#include "sys_math3d.h"
#include "6E9650.h"
#include "6F5550.h"
#include "attributes.h"
#include "macros.h"

#include "overlays/gamestates/ovl_play/m_play.h"
#include "overlays/actors/player_actor/m_player.h"

void mSM_menu_ovl_init(UNK_PTR arg0);

extern void* D_8010DCE0_jp;
extern size_t D_8010DCE4_jp;

extern SubmenuArea* SubmenuArea_visit;
extern SubmenuArea SubmenuArea_dlftbl[];

typedef void (*fnptr_8010DD24)(Game_Play1CBC*);

extern fnptr_8010DD24 D_8010DD24_jp[];

extern FaultClient B_80144670_jp;
extern FaultAddrConvClient B_80144680_jp;

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/RO_STR_80117920_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/RO_STR_8011792C_jp.s")


s32 SubmenuArea_IsPlayer(void) {
    SubmenuArea* playerActorOvl = &SubmenuArea_dlftbl[1];

    return SubmenuArea_visit == playerActorOvl;
}

#ifdef NON_MATCHING
// regalloc
void mSM_load_player_anime(Game_Play* game_play) {
    Game_Play_unk_0110* var_s4;
    s32 var_s0;
    s32 var_s3;
    Player* temp_v0;
    void* segment;

    temp_v0 = get_player_actor_withoutCheck(game_play);
    if (temp_v0 == NULL) {
        return;
    }

    var_s4 = game_play->unk_0110;
    var_s4 += mSc_bank_regist_check(var_s4, 9);

    for (var_s3 = 0; var_s3 < 2; var_s3++, var_s4++) {
        segment = var_s4->segment;

        if (var_s3 == 0) {
            func_800B1D94_jp(segment, temp_v0->unk_0DAC);
        } else {
            func_800B1D94_jp(segment, temp_v0->unk_0DB0);
            if (segment && segment) {}
        }

        var_s0 = temp_v0->unk_0DBC[var_s3];
        if (temp_v0->unk_0DDC[var_s3] >= 0) {
            func_800B167C_jp(var_s0, temp_v0->unk_0DDC[var_s3]);
            var_s0 += func_800B131C_jp(temp_v0->unk_0DDC[var_s3]);
        }

        if (temp_v0->unk_0DE4[var_s3] >= 0) {
            func_800B167C_jp(var_s0, temp_v0->unk_0DE4[var_s3]);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/mSM_load_player_anime.s")
#endif

void SubmenuArea_DoLink(SubmenuArea* area, Game_Play1CBC* arg1, s32 arg2) {
    size_t var_t0;
    struct OverlayRelocationSection* var_t1;
    size_t temp_v0;

    area->allocatedRamAddr = D_8010DCE0_jp;
    if (arg2 == 1) {
        temp_v0 = (((uintptr_t)area->vramEnd - (uintptr_t)area->vramStart) + 0xF) & ~0xF;
        if ((u32) D_8010DCE4_jp >= temp_v0) {
            var_t0 = D_8010DCE4_jp - temp_v0;
            var_t1 = (void*)((uintptr_t)D_8010DCE0_jp + temp_v0);
        } else {
            var_t0 = 0;
            var_t1 = NULL;
        }
        ovlmgr_LoadImpl(area->vromStart, area->vromEnd, area->vramStart, area->vramEnd, area->allocatedRamAddr, var_t1, var_t0);
    } else {
        ovlmgr_Load(area->vromStart, area->vromEnd, area->vramStart, area->vramEnd, area->allocatedRamAddr);
    }

    area->unk_14 = (uintptr_t)area->allocatedRamAddr - (uintptr_t)area->vramStart;
    SubmenuArea_visit = area;
    arg1->unk_24 = area->allocatedRamAddr;
    arg1->unk_28 = (void*) ((uintptr_t)area->allocatedRamAddr + ((((uintptr_t)area->vramEnd - (uintptr_t)area->vramStart) + 0x3F) & ~0x3F));
}

void SubmenuArea_DoUnlink(SubmenuArea* area, Game_Play1CBC* arg1) {
    if (area->allocatedRamAddr == NULL) {
        return;
    }

    arg1->unk_24 = area->allocatedRamAddr;
    arg1->unk_28 = area->allocatedRamAddr;
    area->unk_14 = 0;
    bzero(area->allocatedRamAddr, (uintptr_t)area->vramEnd - (uintptr_t)area->vramStart);
    area->allocatedRamAddr = NULL;
    SubmenuArea_visit = NULL;
}

s32 mSM_ovlptr_dllcnv_sub(void* vram, SubmenuArea* area, Game_Play1CBC* arg2) {
    s32 var_a3;
    s32 len = 2;

    for (var_a3 = 0; var_a3 < len; var_a3++) {
        if ((vram >= area->vramStart) && (vram <= area->vramEnd)) {
            SubmenuArea_DoLink(area, arg2, var_a3);
            return 1;
        }
    }

    return 0;
}

void* mSM_ovlptr_dllcnv(void* vram, Game_Play1CBC* arg1) {
    SubmenuArea* var_v1 = SubmenuArea_visit;

    if (var_v1 == NULL) {
        var_v1 = SubmenuArea_dlftbl;
        if (!mSM_ovlptr_dllcnv_sub(vram, SubmenuArea_dlftbl, arg1)) {
            return NULL;
        }
    }

    if ((var_v1 == NULL) || (vram < var_v1->vramStart) || (vram >= var_v1->vramEnd)) {
        return NULL;
    }

    return (void*)((uintptr_t)vram + var_v1->unk_14);
}

#if 0
void func_800C47B4_jp(void* arg0, void* arg1) {
    s32 sp34;
    u32 sp30;
    u32 sp2C;
    void* sp20;
    Player* temp_v0_3;
    s32 temp_a3;
    u32 var_t0;
    u32 var_t1;
    void* temp_a2;
    void* temp_s0;
    void* temp_v0;
    void* temp_v0_2;

    temp_v0 = *(&B_800418D6_jp + 2);
    var_t0 = 0;
    if (temp_v0 != NULL) {
        var_t0 = temp_v0->unk_11C;
    }
    var_t1 = 0;
    if (temp_v0 != NULL) {
        var_t1 = temp_v0->unk_104;
    }
    sp2C = var_t0;
    sp30 = var_t1;
    FaultDrawer_Printf("SubmenuArea_visit\n");
    FaultDrawer_Printf("RamStart-RamEnd  Offset\n");
    if (SubmenuArea_visit != NULL) {
        temp_v0_2 = SubmenuArea_visit->vramStart;
        temp_s0 = SubmenuArea_visit->allocatedRamAddr;
        temp_a3 = temp_v0_2 - temp_s0;
        if (temp_s0 != NULL) {
            temp_a2 = temp_s0 + (SubmenuArea_visit->vramEnd - temp_v0_2);
            sp20 = temp_a2;
            sp34 = temp_a3;
            sp2C = var_t0;
            sp30 = var_t1;
            FaultDrawer_Printf("%08x-%08x %06x", temp_s0, temp_a2, temp_a3);
            if ((var_t0 >= (u32) temp_s0) && (var_t0 < (u32) temp_a2)) {
                FaultDrawer_Printf(" PC:%08x", var_t0 + temp_a3, temp_a2, temp_a3);
            } else if ((var_t1 >= (u32) temp_s0) && (var_t1 < (u32) temp_a2)) {
                FaultDrawer_Printf(" RA:%08x", var_t1 + temp_a3, temp_a2, temp_a3);
            }
            FaultDrawer_Printf("\n");
            temp_v0_3 = get_player_actor_withoutCheck((Game_Play* ) gamePT);
            if (temp_v0_3 != NULL) {
                FaultDrawer_Printf("\n");
                FaultDrawer_Printf("player infomation\n");
                FaultDrawer_Printf("main_index         :%d %d\n", temp_v0_3->unk_CF0, temp_v0_3->unk_CF4);
                FaultDrawer_Printf("request_main_index :%d %d %d\n", temp_v0_3->unk_D00, temp_v0_3->unk_D04, temp_v0_3->unk_D08);
                FaultDrawer_Printf("pos :%d %d %d\n", (s32) temp_v0_3->actor.world.pos.x, (s32) temp_v0_3->actor.world.pos.y, (s32) temp_v0_3->actor.world.pos.z);
                FaultDrawer_Printf("angleY :%d %d\n", temp_v0_3->actor.world.rot.y, temp_v0_3->actor.shape.rot.y);
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C47B4_jp.s")
#endif

uintptr_t func_800C497C_jp(uintptr_t address, UNUSED void* param) {
    uintptr_t addr = address;

    if (SubmenuArea_visit != NULL) {
        size_t ovlSize = ((uintptr_t)SubmenuArea_visit->vramEnd - (uintptr_t)SubmenuArea_visit->vramStart);
        uintptr_t loadedRamAddr = (uintptr_t)SubmenuArea_visit->allocatedRamAddr;
        size_t relocationDiff = (uintptr_t)SubmenuArea_visit->vramStart - loadedRamAddr;

        if (loadedRamAddr != NULL) {
            if ((addr >= loadedRamAddr) && (addr < loadedRamAddr + ovlSize)) {
                return addr + relocationDiff;
            }
        }
    }

    return (uintptr_t)NULL;
}

extern UNK_TYPE1 D_8086F0E0_jp;
extern UNK_TYPE1 D_808796B0_jp;
extern UNK_TYPE1 D_8087CA30_jp;
extern UNK_TYPE1 D_80881C20_jp;
extern UNK_TYPE1 D_80888B20_jp;
extern UNK_TYPE1 D_8088ACC0_jp;
extern UNK_TYPE1 D_8088CA90_jp;
extern UNK_TYPE1 D_80896A70_jp;
extern UNK_TYPE1 D_80897870_jp;
extern UNK_TYPE1 D_808A2E00_jp;
extern UNK_TYPE1 D_808A45E0_jp;
extern UNK_TYPE1 D_808B2B30_jp;
extern UNK_TYPE1 D_808E04D0_jp;
extern UNK_TYPE1 func_8085BAC0_jp;
extern UNK_TYPE1 func_8086F310_jp;
extern UNK_TYPE1 func_8087A330_jp;
extern UNK_TYPE1 func_8087D480_jp;
extern UNK_TYPE1 func_80885140_jp;
extern UNK_TYPE1 func_80888E90_jp;
extern UNK_TYPE1 func_8088ADB0_jp;
extern UNK_TYPE1 func_80895E00_jp;
extern UNK_TYPE1 func_80896B20_jp;
extern UNK_TYPE1 func_8089AD40_jp;
extern UNK_TYPE1 func_808A2EA0_jp;
extern UNK_TYPE1 func_808A6100_jp;
extern UNK_TYPE1 func_808B2D50_jp;

// mSM_submenu_ovlptr_init
#ifdef NON_MATCHING
// regalloc
void func_800C49D4_jp(Game_Play* game_play) {
    u32 temp_a0;
    UNUSED u32 temp_a1_2;
    u32 temp_v1;
    u32 temp_t1;
    u32 var_a3;
    u32 var_s0;
    u32 temp_a1;
    u32 var_t0;
    u32 temp;
    u32 temp2;
    u32 temp3;
    u32 temp4;
    u32 temp5;

    u32 temp6;
    u32 temp7;
    u32 temp8;
    u32 temp9;

    temp6 = (((&D_8088CA90_jp - &func_8088ADB0_jp) + 0x3F) & ~0x3F);
    temp7 = (((&D_80897870_jp - &func_80896B20_jp) + 0x3F) & ~0x3F);
    temp8 = (((&D_808A2E00_jp - &func_8089AD40_jp) + 0x3F) & ~0x3F);
    temp9 = (((&D_808A45E0_jp - &func_808A2EA0_jp) + 0x3F) & ~0x3F);

    temp_v1 = ((&D_8086F0E0_jp - &func_8085BAC0_jp) + 0x3F) & ~0x3F;
    temp_a0 = ((&D_808796B0_jp - &func_8086F310_jp) + 0x3F) & ~0x3F;

    var_t0 = temp6 + temp7;
    temp_a1 = temp8 + temp9;
    var_t0 = MAX(temp_a1, var_t0);

    temp_a1 = ((&D_8087CA30_jp - &func_8087A330_jp) + 0x3F) & ~0x3F;
    temp = (((&D_80881C20_jp - &func_8087D480_jp) + 0x3F) & ~0x3F);
    temp2 = (((&D_8088ACC0_jp - &func_80888E90_jp) + 0x3F) & ~0x3F);
    temp3 = (((&D_80888B20_jp - &func_80885140_jp) + 0x3F) & ~0x3F);
    temp4 = (((&D_80896A70_jp - &func_80895E00_jp) + 0x3F) & ~0x3F);
    temp5 = (((&D_808B2B30_jp - &func_808A6100_jp) + 0x3F) & ~0x3F);

    var_a3 = temp_v1 + temp + temp_a0 + temp_a1 + temp2 + temp3 + temp4 + var_t0;
    temp_t1 = temp_v1 + temp_a0 + temp_a1 + temp5 + 0x4000;
    var_a3 = MAX(temp_t1, var_a3);

    temp_v1 = &D_808E04D0_jp - &func_808B2D50_jp;

    var_s0 = MAX(var_a3, temp_v1);

    debug_mode->r[0xB31] = (var_s0 >> 0x10);
    debug_mode->r[0xB32] = var_s0;
    debug_mode->r[0xB33] = (temp_v1 >> 0x10);
    debug_mode->r[0xB34] = temp_v1;
    debug_mode->r[0xB35] = (var_a3 >> 0x10);
    debug_mode->r[0xB36] = var_a3;

    //! FAKE
    dummy_label_255895: ;

    D_8010DCE0_jp = THA_alloc16(&game_play->state.heap, var_s0);
    D_8010DCE4_jp = var_s0;
    SubmenuArea_visit = NULL;

    Fault_AddClient(&B_80144670_jp, func_800C47B4_jp, NULL, NULL);
    Fault_AddAddrConvClient(&B_80144680_jp, func_800C497C_jp, NULL);
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C49D4_jp.s")
#endif

void mSM_submenu_ovlptr_cleanup(Game_Play1CBC* arg0) {
    Fault_RemoveClient(&B_80144670_jp);
    Fault_RemoveAddrConvClient(&B_80144680_jp);
    if (SubmenuArea_visit != NULL) {
        SubmenuArea_DoUnlink(SubmenuArea_visit, arg0);
        SubmenuArea_visit = NULL;
    }

    // One of those two is SubmenuArea_allocp
    D_8010DCE0_jp = 0;
    D_8010DCE4_jp = 0;
}

void load_player(Game_Play1CBC* arg0) {
    SubmenuArea* playerActorOvl = &SubmenuArea_dlftbl[1];

    if (SubmenuArea_visit == playerActorOvl) {
        return;
    }

    if (SubmenuArea_visit != NULL) {
        SubmenuArea_DoUnlink(SubmenuArea_visit, arg0);
    }

    SubmenuArea_DoLink(playerActorOvl, arg0, 1);
}

void mSM_submenu_ct(Game_Play1CBC* arg0) {
    bzero(arg0, sizeof(Game_Play1CBC));

    arg0->unk_0C = 0;
    arg0->unk_20 = 0;

    if (common_data.unk_104AD == 1) {
        arg0->unk_E2 = 1;
        common_data.unk_104AD = 0;
    }

    arg0->unk_30 = (void*)none_proc1;
    arg0->unk_34 = (void*)none_proc1;
}

void mSM_submenu_dt(UNUSED Game_Play1CBC* arg0) {
}

void mSM_open_submenu(Game_Play1CBC* arg0, s32 arg1, s32 arg2, s32 arg3) {
    mSM_open_submenu_new2(arg0, arg1, arg2, arg3, 0, 0);
}

void mSM_open_submenu_new(Game_Play1CBC* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    mSM_open_submenu_new2(arg0, arg1, arg2, arg3, arg4, 0);
}

void mSM_open_submenu_new2(Game_Play1CBC* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    arg0->unk_04 = arg1;
    arg0->unk_10 = arg2;
    arg0->unk_14 = arg3;
    arg0->unk_18 = arg4;
    arg0->unk_1C = arg5;
}

void mSM_Reset_player_btn_type1(Game_Play* game_play) {
    Player* player = get_player_actor_withoutCheck(game_play);

    if (player != NULL) {
        player->unk_12B8 = 0;
        player->unk_12BC = 1;
    }
}

void mSM_Reset_player_btn_type2(Game_Play* game_play) {
    Player* player = get_player_actor_withoutCheck(game_play);

    if (player != NULL) {
        player->unk_12BC = 1;
    }
}

void mSM_submenu_ctrl(Game_Play* game_play) {
    Game_Play1CBC* temp_v0;

    temp_v0 = &game_play->unk_1CBC;
    if ((game_play->unk_1CBC.unk_0C != 0) || (game_play->unk_1EE0 != 0) || (game_play->unk_1EE3 != 0)) {
        return;
    }

    if (
        (!((chkTrigger(START_BUTTON) == 0) || (common_data.unk_10A68 != 0))
            ||
            ((((chkTrigger(R_TRIG) != 0) && (common_data.unk_10140 == 1)) == 1) && (common_data.unk_10A68 == 0)))

            && ((temp_v0->unk_E2 == 0) && (temp_v0->unk_E3 <= 0) && (mPlib_able_submenu_type1(game_play) != 0) && (mEv_CheckFirstIntro() == 0))
        ) {
        if (chkTrigger(START_BUTTON) != 0) {
            mSM_open_submenu(temp_v0, 1, 0, 0);
        } else {
            mSM_open_submenu(temp_v0, 5, 1, 0);
        }
        mSM_Reset_player_btn_type2(game_play);
    } else {
        Player* player = get_player_actor_withoutCheck(game_play);
        UNUSED s32 pad;

        if ((player != NULL) && (player->unk_12B8 == 1) && (common_data.unk_10A68 == 0) && (temp_v0->unk_E2 == 0) && (temp_v0->unk_E3 <= 0)) {
            if (mPlib_able_submenu_type1(game_play) != 0) {
                if (ABS(BINANG_ROT180(player->actor.shape.rot.y)) < 0x2000) {
                    switch (player->unk_12C0) {
                        case 0x7:
                        case 0xB:
                            mSM_open_submenu(temp_v0, 6, 0, 0);
                            mSM_Reset_player_btn_type1(game_play);
                            break;

                        case 0xC:
                        case 0xD:
                            mSM_open_submenu(temp_v0, 5, 0, 0);
                            mSM_Reset_player_btn_type1(game_play);
                            break;

                        case 0xE:
                        case 0xF:
                            mSM_open_submenu(temp_v0, 8, 0, 0);
                            mSM_Reset_player_btn_type1(game_play);
                            break;
                    }
                }
            }
        }
    }

    if (temp_v0->unk_04 != 0) {
        temp_v0->unk_0C = 1;
        temp_v0->unk_00 = 1;
        SetGameFrame(2);
    }
}

void mSM_move_Wait(Game_Play1CBC* arg0) {
    if (arg0->unk_20 != 0) {
        arg0->unk_20--;
    }

    if (arg0->unk_E3 > 0) {
        arg0->unk_E3--;
    }
}

void mSM_move_PREWait(Game_Play1CBC* arg0) {
    if (arg0->unk_00 > 2) {
        arg0->unk_0C = 2;
    }
}

#ifdef NON_MATCHING
void mSM_move_LINKWait(Game_Play1CBC* arg0) {
    SubmenuArea* submenuOvl = &SubmenuArea_dlftbl[0];

    if (SubmenuArea_visit == submenuOvl) {
        return;
    }

    if (SubmenuArea_visit != NULL) {
        SubmenuArea_DoUnlink(SubmenuArea_visit, arg0);
    }
    SubmenuArea_DoLink(submenuOvl, arg0, 0);

    arg0->unk_30 = mSM_ovlptr_dllcnv(&mSM_menu_ovl_init, arg0);
    arg0->unk_34 = (void*)none_proc1;
    arg0->unk_0C = 3;
    arg0->unk_DC = 1;
    arg0->unk_E0 = 0;
    arg0->unk_DF = 0xF;
    arg0->unk_DD = 7;
    arg0->unk_DE = 0;
    mMl_clear_mail(&arg0->unk_38);
    xyz_t_move(&arg0->unk_E4, &ZeroVec);

    if (arg0->unk_00 != 4) {
        if (((arg0->unk_04 == 4) && (arg0->unk_10 == 0)) || (common_data.now_private->gender == 0)) {
            sAdo_SpecChange(5);
        } else {
            sAdo_SpecChange(6);
        }
        sAdo_SetVoiceMode(0);
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/mSM_move_LINKWait.s")
#endif

void mSM_move_Play(Game_Play1CBC* arg0) {
    arg0->unk_30(arg0);
}

#ifdef NON_MATCHING
// likely memes
void mSM_move_End(Game_Play1CBC* arg0) {
    UNUSED s32 pad;
    Game_Play* sp28;
    UNK_TYPE sp24;
    UNUSED s32 sp20[1];

    sp28 = (Game_Play*)gamePT;
    arg0->unk_30(arg0);
    arg0->unk_0C = 0;
    arg0->unk_04 = 0;
    arg0->unk_20 = 2;
    arg0->unk_DC = 0;

    SetGameFrame(2);

    if (arg0->unk_00 != 4) {
        sp24 = mMsg_Get_base_window_p();
        arg0->unk_00 = 0;
        mSc_dmacopy_all_exchange_bank(sp28->unk_0110);
        SubmenuArea_DoUnlink(SubmenuArea_dlftbl, arg0);
        load_player(arg0);
        mSM_load_player_anime(sp28);
        arg0->unk_E3 = 1;
        sp20[0] = 0;
        if ((mMsg_Check_main_hide(sp24) == 0) && (mMsg_Check_not_series_main_wait(sp24) != 0)) {
            mMsg_sound_spec_change_voice(sp24);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/mSM_move_End.s")
#endif

void mSM_submenu_move(Game_Play1CBC* arg0) {
    D_8010DD24_jp[arg0->unk_0C](arg0);
}

void mSM_submenu_draw(Game_Play1CBC* arg0, struct Game_Play* game_play) {
    SubmenuArea* submenuOvl = &SubmenuArea_dlftbl[0];

    if ((arg0->unk_00 >= 3) && (arg0->unk_0C == 3) && (submenuOvl == SubmenuArea_visit)) {
        arg0->unk_34(arg0, game_play);
    }
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C53B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C543C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C54A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C54F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C557C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C55E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C5640_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C56AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C5798_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C582C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C58B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C592C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C5960_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C5984_jp.s")
