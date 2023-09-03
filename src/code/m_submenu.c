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
#include "6DE300.h"
#include "6F5550.h"
#include "libc/stddef.h"
#include "attributes.h"
#include "segment_symbols.h"
#include "macros.h"

#include "overlays/gamestates/ovl_play/m_play.h"
#include "overlays/actors/player_actor/m_player.h"
#include "overlays/submenu/submenu_ovl/m_submenu_ovl.h"

FaultClient B_80144670_jp;
FaultAddrConvClient B_80144680_jp;

void* D_8010DCE0_jp = NULL;
size_t D_8010DCE4_jp = 0;

typedef enum SubmenuAreaIndex {
    /* 0 */ SUBMENU_AREA_INDEX_SUBMENU,
    /* 1 */ SUBMENU_AREA_INDEX_PLAYER,
    /* 2 */ SUBMENU_AREA_INDEX_MAX
} SubmenuAreaIndex;

typedef struct SubmenuArea {
    /* 0x00 */ void* allocatedRamAddr;
    /* 0x04 */ RomOffset vromStart;
    /* 0x08 */ RomOffset vromEnd;
    /* 0x0C */ void* vramStart;
    /* 0x10 */ void* vramEnd;
    /* 0x14 */ ptrdiff_t relocationDiff;
    /* 0x18 */ const char* name;
} SubmenuArea; // size = 0x1C

#define SUBMENU_OVERLAY(name) \
    { NULL, SEGMENT_ROM_START(name), SEGMENT_ROM_END(name), SEGMENT_VRAM_START(name), SEGMENT_VRAM_END(name), 0, #name }

SubmenuArea* SubmenuArea_visit = NULL;
SubmenuArea SubmenuArea_dlftbl[SUBMENU_AREA_INDEX_MAX] = {
    SUBMENU_OVERLAY(submenu_ovl),  // SUBMENU_AREA_INDEX_SUBMENU
    SUBMENU_OVERLAY(player_actor), // SUBMENU_AREA_INDEX_PLAYER
};

s32 SubmenuArea_IsPlayer(void) {
    SubmenuArea* playerActorOvl = &SubmenuArea_dlftbl[SUBMENU_AREA_INDEX_PLAYER];

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
            //! FAKE
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
void mSM_load_player_anime(Game_Play* game_play);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/mSM_load_player_anime.s")
#endif

void SubmenuArea_DoLink(SubmenuArea* area, mSM* submenu, SubmenuAreaIndex index) {
    area->allocatedRamAddr = D_8010DCE0_jp;

    if (index == SUBMENU_AREA_INDEX_PLAYER) {
        size_t ovlSize = ALIGN16((uintptr_t)area->vramEnd - (uintptr_t)area->vramStart);
        size_t size;
        struct OverlayRelocationSection* ovl;

        if (D_8010DCE4_jp >= ovlSize) {
            size = D_8010DCE4_jp - ovlSize;
            ovl = (void*)((uintptr_t)D_8010DCE0_jp + ovlSize);
        } else {
            size = 0;
            ovl = NULL;
        }
        ovlmgr_LoadImpl(area->vromStart, area->vromEnd, area->vramStart, area->vramEnd, area->allocatedRamAddr, ovl,
                        size);
    } else {
        ovlmgr_Load(area->vromStart, area->vromEnd, area->vramStart, area->vramEnd, area->allocatedRamAddr);
    }

    area->relocationDiff = (uintptr_t)area->allocatedRamAddr - (uintptr_t)area->vramStart;
    SubmenuArea_visit = area;
    submenu->linkedAllocStart = area->allocatedRamAddr;
    submenu->linkedAllocEnd =
        (void*)((uintptr_t)area->allocatedRamAddr + ALIGN64((uintptr_t)area->vramEnd - (uintptr_t)area->vramStart));
}

void SubmenuArea_DoUnlink(SubmenuArea* area, mSM* submenu) {
    if (area->allocatedRamAddr == NULL) {
        return;
    }

    submenu->linkedAllocStart = area->allocatedRamAddr;
    submenu->linkedAllocEnd = area->allocatedRamAddr;
    area->relocationDiff = 0;
    bzero(area->allocatedRamAddr, (uintptr_t)area->vramEnd - (uintptr_t)area->vramStart);
    area->allocatedRamAddr = NULL;
    SubmenuArea_visit = NULL;
}

s32 mSM_ovlptr_dllcnv_sub(void* vram, SubmenuArea* area, mSM* submenu) {
    SubmenuAreaIndex index;
    s32 len = SUBMENU_AREA_INDEX_MAX;

    for (index = 0; index < len; index++) {
        if ((vram >= area->vramStart) && (vram <= area->vramEnd)) {
            SubmenuArea_DoLink(area, submenu, index);
            return 1;
        }
    }

    return 0;
}

void* mSM_ovlptr_dllcnv(void* vram, mSM* submenu) {
    SubmenuArea* area = SubmenuArea_visit;

    if (area == NULL) {
        area = SubmenuArea_dlftbl;
        if (!mSM_ovlptr_dllcnv_sub(vram, SubmenuArea_dlftbl, submenu)) {
            return NULL;
        }
    }

    if ((area == NULL) || (vram < area->vramStart) || (vram >= area->vramEnd)) {
        return NULL;
    }

    return (void*)((uintptr_t)vram + area->relocationDiff);
}

void func_800C47B4_jp(UNUSED void* arg0, UNUSED void* arg1) {
    void* temp_s0;
    Player* temp_v0_3;
    UNUSED void* temp_v0_2;
    OSThread* temp_v0;
    u32 temp_a3; // sp34
    u32 var_t1;  // sp30
    u32 var_t0;  // sp2C
    size_t ovlSize;
    void* temp_a2; // sp20

    temp_v0 = gFaultMgr.faultedThread;
    var_t0 = (temp_v0 != NULL) ? temp_v0->context.pc : 0;
    var_t1 = (temp_v0 != NULL) ? temp_v0->context.ra : 0;

    FaultDrawer_Printf("SubmenuArea_visit\n");
    FaultDrawer_Printf("RamStart-RamEnd  Offset\n");

    if (SubmenuArea_visit == NULL) {
        return;
    }

    ovlSize = (uintptr_t)SubmenuArea_visit->vramEnd - (uintptr_t)SubmenuArea_visit->vramStart;
    temp_s0 = SubmenuArea_visit->allocatedRamAddr;

    temp_a3 = (uintptr_t)SubmenuArea_visit->vramStart - (uintptr_t)temp_s0;
    temp_a2 = (void*)((uintptr_t)temp_s0 + ovlSize);

    if (temp_s0 != NULL) {
        FaultDrawer_Printf("%08x-%08x %06x", temp_s0, temp_a2, temp_a3);
        if ((var_t0 >= (u32)temp_s0) && (var_t0 < (u32)temp_a2)) {
            FaultDrawer_Printf(" PC:%08x", var_t0 + temp_a3);
        } else if ((var_t1 >= (u32)temp_s0) && (var_t1 < (u32)temp_a2)) {
            FaultDrawer_Printf(" RA:%08x", var_t1 + temp_a3);
        }

        FaultDrawer_Printf("\n");
        temp_v0_3 = get_player_actor_withoutCheck((Game_Play*)gamePT);
        if (temp_v0_3 != NULL) {
            FaultDrawer_Printf("\n");
            FaultDrawer_Printf("player infomation\n");
            FaultDrawer_Printf("main_index         :%d %d\n", temp_v0_3->unk_0CF0, temp_v0_3->unk_0CF4);
            FaultDrawer_Printf("request_main_index :%d %d %d\n", temp_v0_3->unk_0D00, temp_v0_3->unk_0D04,
                               temp_v0_3->unk_0D08);
            FaultDrawer_Printf("pos :%d %d %d\n", (s32)temp_v0_3->actor.world.pos.x, (s32)temp_v0_3->actor.world.pos.y,
                               (s32)temp_v0_3->actor.world.pos.z);
            FaultDrawer_Printf("angleY :%d %d\n", temp_v0_3->actor.world.rot.y, temp_v0_3->actor.shape.rot.y);
        }
    }
}

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

void mSM_submenu_ovlptr_init(Game_Play* game_play) {
    size_t temp6 = ALIGN64(SEGMENT_VRAM_SIZE(ovl__00792700));
    size_t temp7 = ALIGN64(SEGMENT_VRAM_SIZE(ovl__0079A290));
    size_t temp8 = ALIGN64(SEGMENT_VRAM_SIZE(ovl__0079E430));
    size_t temp9 = ALIGN64(SEGMENT_VRAM_SIZE(ovl__0079F810));
    size_t submenuOvlSize = ALIGN64(SEGMENT_VRAM_SIZE(submenu_ovl));
    size_t temp_a0 = ALIGN64(SEGMENT_VRAM_SIZE(ovl__00777AE0));
    size_t var_t0 = temp6 + temp7;
    size_t temp10;
    size_t temp1;
    size_t temp2;
    size_t temp3;
    size_t temp4;
    size_t temp5;
    size_t var_a3;
    size_t playerOvlSize;
    size_t var_s0;

    var_t0 = MAX(temp8 + temp9, var_t0);

    temp10 = ALIGN64(SEGMENT_VRAM_SIZE(ovl__007829E0));
    temp1 = ALIGN64(SEGMENT_VRAM_SIZE(ovl__00785700));
    temp2 = ALIGN64(SEGMENT_VRAM_SIZE(ovl__007908A0));
    temp3 = ALIGN64(SEGMENT_VRAM_SIZE(ovl__0078CB80));
    temp4 = ALIGN64(SEGMENT_VRAM_SIZE(ovl__00799580));
    temp5 = ALIGN64(SEGMENT_VRAM_SIZE(ovl__007A28F0));

    var_a3 = submenuOvlSize + temp1 + temp_a0 + temp10 + temp2 + temp3 + temp4 + var_t0;
    var_a3 = MAX(submenuOvlSize + temp_a0 + temp10 + temp5 + 0x4000, var_a3);

    playerOvlSize = SEGMENT_VRAM_SIZE(player_actor);

    var_s0 = MAX(var_a3, playerOvlSize);

    PLAYERREG(81) = (var_s0 >> 0x10) & 0xFFFF;
    PLAYERREG(82) = var_s0 & 0xFFFF;
    PLAYERREG(83) = (playerOvlSize >> 0x10) & 0xFFFF;
    PLAYERREG(84) = playerOvlSize & 0xFFFF;
    PLAYERREG(85) = (var_a3 >> 0x10) & 0xFFFF;
    PLAYERREG(86) = var_a3 & 0xFFFF;

//! FAKE
dummy_label_255895:

    D_8010DCE0_jp = THA_alloc16(&game_play->state.heap, var_s0);
    D_8010DCE4_jp = var_s0;
    SubmenuArea_visit = NULL;

    fault_AddClient(&B_80144670_jp, func_800C47B4_jp, NULL, NULL);
    fault_AddressConverterAddClient(&B_80144680_jp, func_800C497C_jp, NULL);
}

void mSM_submenu_ovlptr_cleanup(mSM* submenu) {
    fault_RemoveClient(&B_80144670_jp);
    fault_AddressConverterRemoveClient(&B_80144680_jp);
    if (SubmenuArea_visit != NULL) {
        SubmenuArea_DoUnlink(SubmenuArea_visit, submenu);
        SubmenuArea_visit = NULL;
    }

    // One of those two is SubmenuArea_allocp
    D_8010DCE0_jp = 0;
    D_8010DCE4_jp = 0;
}

void load_player(mSM* submenu) {
    SubmenuArea* playerActorOvl = &SubmenuArea_dlftbl[SUBMENU_AREA_INDEX_PLAYER];

    if (SubmenuArea_visit == playerActorOvl) {
        return;
    }

    if (SubmenuArea_visit != NULL) {
        SubmenuArea_DoUnlink(SubmenuArea_visit, submenu);
    }

    SubmenuArea_DoLink(playerActorOvl, submenu, SUBMENU_AREA_INDEX_PLAYER);
}

void mSM_submenu_ct(mSM* submenu) {
    bzero(submenu, sizeof(mSM));

    submenu->moveProcIndex = MSM_MOVE_PROC_WAIT;
    submenu->unk_20 = 0;

    if (common_data.unk_104AD == 1) {
        submenu->unk_E2 = 1;
        common_data.unk_104AD = 0;
    }

    submenu->play = (void*)none_proc1;
    submenu->draw = (void*)none_proc1;
}

void mSM_submenu_dt(UNUSED mSM* submenu) {
}

void mSM_open_submenu(mSM* submenu, s32 arg1, s32 arg2, s32 arg3) {
    mSM_open_submenu_new2(submenu, arg1, arg2, arg3, 0, 0);
}

void mSM_open_submenu_new(mSM* submenu, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    mSM_open_submenu_new2(submenu, arg1, arg2, arg3, arg4, 0);
}

void mSM_open_submenu_new2(mSM* submenu, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    submenu->unk_04 = arg1;
    submenu->unk_10 = arg2;
    submenu->unk_14 = arg3;
    submenu->unk_18 = arg4;
    submenu->unk_1C = arg5;
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
    mSM* submenu = &game_play->submenu;

    if ((game_play->submenu.moveProcIndex != MSM_MOVE_PROC_WAIT) || (game_play->unk_1EE0 != 0) ||
        (game_play->unk_1EE3 != 0)) {
        return;
    }

    if ((!((chkTrigger(START_BUTTON) == 0) || (common_data.unk_10A68 != 0)) ||
         ((((chkTrigger(R_TRIG) != 0) && (common_data.unk_10140 == 1)) == 1) && (common_data.unk_10A68 == 0))) &&
        ((submenu->unk_E2 == 0) && (submenu->unk_E3 <= 0) && (mPlib_able_submenu_type1(game_play) != 0) &&
         (mEv_CheckFirstIntro() == 0))) {
        if (chkTrigger(START_BUTTON) != 0) {
            mSM_open_submenu(submenu, 1, 0, 0);
        } else {
            mSM_open_submenu(submenu, 5, 1, 0);
        }
        mSM_Reset_player_btn_type2(game_play);
    } else {
        Player* player = get_player_actor_withoutCheck(game_play);
        UNUSED s32 pad;

        if ((player != NULL) && (player->unk_12B8 == 1) && (common_data.unk_10A68 == 0) && (submenu->unk_E2 == 0) &&
            (submenu->unk_E3 <= 0)) {
            if (mPlib_able_submenu_type1(game_play) != 0) {
                if (ABS(BINANG_ROT180(player->actor.shape.rot.y)) < 0x2000) {
                    switch (player->unk_12C0) {
                        case 0x7:
                        case 0xB:
                            mSM_open_submenu(submenu, 6, 0, 0);
                            mSM_Reset_player_btn_type1(game_play);
                            break;

                        case 0xC:
                        case 0xD:
                            mSM_open_submenu(submenu, 5, 0, 0);
                            mSM_Reset_player_btn_type1(game_play);
                            break;

                        case 0xE:
                        case 0xF:
                            mSM_open_submenu(submenu, 8, 0, 0);
                            mSM_Reset_player_btn_type1(game_play);
                            break;
                    }
                }
            }
        }
    }

    if (submenu->unk_04 != 0) {
        submenu->moveProcIndex = MSM_MOVE_PROC_PREWAIT;
        submenu->unk_00 = 1;
        SetGameFrame(2);
    }
}

void mSM_move_Wait(mSM* submenu) {
    if (submenu->unk_20 != 0) {
        submenu->unk_20--;
    }

    if (submenu->unk_E3 > 0) {
        submenu->unk_E3--;
    }
}

void mSM_move_PREWait(mSM* submenu) {
    if (submenu->unk_00 > 2) {
        submenu->moveProcIndex = MSM_MOVE_PROC_LINKWAIT;
    }
}

void mSM_move_LINKWait(mSM* submenu) {
    SubmenuArea* submenuOvl = &SubmenuArea_dlftbl[SUBMENU_AREA_INDEX_SUBMENU];

    if (SubmenuArea_visit == submenuOvl) {
        return;
    }

    if (SubmenuArea_visit != NULL) {
        SubmenuArea_DoUnlink(SubmenuArea_visit, submenu);
    }
    SubmenuArea_DoLink(submenuOvl, submenu, SUBMENU_AREA_INDEX_SUBMENU);

    submenu->play = mSM_ovlptr_dllcnv(mSM_menu_ovl_init, submenu);
    submenu->draw = (void*)none_proc1;
    submenu->moveProcIndex = MSM_MOVE_PROC_PLAY;
    submenu->unk_DC = 1;
    submenu->unk_E0 = 0;
    submenu->unk_DF = 0xF;
    submenu->unk_DD = 7;
    submenu->unk_DE = 0;
    mMl_clear_mail(&submenu->mail);
    xyz_t_move(&submenu->unk_E4, &ZeroVec);

    if (submenu->unk_00 != 4) {
        if (((submenu->unk_04 == 4) && (submenu->unk_10 == 0)) || (common_data.now_private->gender == 0)) {
            sAdo_SpecChange(5);
        } else {
            sAdo_SpecChange(6);
        }
        sAdo_SetVoiceMode(0);
    }
}

void mSM_move_Play(mSM* submenu) {
    submenu->play(submenu);
}

#ifdef NON_MATCHING
// likely branch instead of normal branch
void mSM_move_End(mSM* submenu) {
    UNUSED s32 pad;
    Game_Play* sp28;
    UNK_TYPE sp24;
    UNUSED s32 sp20[1];

    sp28 = (Game_Play*)gamePT;
    submenu->play(submenu);
    submenu->moveProcIndex = MSM_MOVE_PROC_WAIT;
    submenu->unk_04 = 0;
    submenu->unk_20 = 2;
    submenu->unk_DC = 0;

    SetGameFrame(2);

    if (submenu->unk_00 == 4) {
        return;
    }

    sp24 = mMsg_Get_base_window_p();
    submenu->unk_00 = 0;
    mSc_dmacopy_all_exchange_bank(sp28->unk_0110);
    SubmenuArea_DoUnlink(SubmenuArea_dlftbl, submenu);
    load_player(submenu);
    mSM_load_player_anime(sp28);
    submenu->unk_E3 = 1;
    sp20[0] = 0;

    if (mMsg_Check_main_hide(sp24) != 0) {
        return;
    }
    if (mMsg_Check_not_series_main_wait(sp24) == 0) {
        return;
    }

    mMsg_sound_spec_change_voice(sp24);
}
#else
void mSM_move_End(mSM* submenu);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/mSM_move_End.s")
#endif

typedef void (*MoveProcFunc)(mSM*);

MoveProcFunc move_proc_616[MSM_MOVE_PROC_MAX] = {
    mSM_move_Wait,     // MSM_MOVE_PROC_WAIT
    mSM_move_PREWait,  // MSM_MOVE_PROC_PREWAIT
    mSM_move_LINKWait, // MSM_MOVE_PROC_LINKWAIT
    mSM_move_Play,     // MSM_MOVE_PROC_PLAY
    mSM_move_End,      // MSM_MOVE_PROC_END
};

void mSM_submenu_move(mSM* submenu) {
    move_proc_616[submenu->moveProcIndex](submenu);
}

void mSM_submenu_draw(mSM* submenu, struct Game_Play* game_play) {
    SubmenuArea* submenuOvl = &SubmenuArea_dlftbl[SUBMENU_AREA_INDEX_SUBMENU];

    if ((submenu->unk_00 >= 3) && (submenu->moveProcIndex == 3) && (submenuOvl == SubmenuArea_visit)) {
        submenu->draw(submenu, game_play);
    }
}

s32 mSM_check_item_for_furniture(s32 index, UNUSED s32 arg1) {
    u16 temp_v0 = common_data.now_private->inventory.pockets[index];

    if (((temp_v0 & 0xF000) >> 0xC) == 2) {
        if ((((temp_v0 & 0xF00) >> 8) != 3) && (((temp_v0 & 0xF00) >> 8) != 0xF) && (((temp_v0 & 0xF00) >> 8) != 0xD)) {
            if (!((common_data.now_private->inventory.item_conditions >> (index << 1)) & 3)) {
                if (temp_v0 != 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

s32 mSM_check_item_for_sell(s32 index, UNUSED s32 arg1) {
    u16 temp_v0 = common_data.now_private->inventory.pockets[index];
    Private_c* private = common_data.now_private;

    if (!((private->inventory.item_conditions >> (index << 1)) & 3)) {
        if (temp_v0 != 0) {
            if ((((temp_v0 & 0xF000) >> 0xC) != 2) || (((temp_v0 & 0xF00) >> 8) != 1)) {
                return true;
            }
        }
    }
    return false;
}

s32 mSM_check_item_for_give(s32 index, UNUSED s32 arg1) {
    Private_c* private = common_data.now_private;

    if (!((private->inventory.item_conditions >> (index << 1)) & 3)) {
        if (private->inventory.pockets[index] != 0) {
            return true;
        }
    }
    return false;
}

s32 mSM_check_item_for_take(s32 index, s32 arg1) {
    u16 temp_v0 = common_data.now_private->inventory.pockets[index];
    Private_c* private = common_data.now_private;

    if (temp_v0 != 0) {
        if (!((private->inventory.item_conditions >> (index << 1)) & 3)) {
            if ((arg1 == 0) ||
                ((((temp_v0 & 0xF000) >> 0xC) == 2) && ((((((temp_v0 & 0xF00) >> 8) == 3)) && (arg1 == 1)) ||
                                                        ((((temp_v0 & 0xF00) >> 8) == 0xD) && (arg1 == 2))))) {
                return true;
            }
        }
    }
    return false;
}

s32 mSM_check_item_for_minidisk(s32 index, UNUSED s32 arg1) {
    u16 temp_v0 = common_data.now_private->inventory.pockets[index];
    Private_c* private = common_data.now_private;

    if (((temp_v0 & 0xF000) >> 0xC) == 2) {
        if (!((private->inventory.item_conditions >> (index << 1)) & 3)) {
            if (((temp_v0 & 0xF00) >> 8) == 0xA) {
                return true;
            }
        }
    }
    return false;
}

s32 mSM_check_item_for_shrine(s32 index, UNUSED s32 arg1) {
    if (((common_data.now_private->inventory.item_conditions >> (index * 2)) & 3) == 2) {
        if (mQst_CheckLimitbyPossessionIdx(index) != 0) {
            return true;
        }
    }

    return false;
}

s32 mSM_check_item_for_entrust(s32 index, UNUSED s32 arg1) {
    u16 temp_v0 = common_data.now_private->inventory.pockets[index];
    Private_c* temp_v1 = common_data.now_private;

    if ((temp_v0 == 0) || (!((temp_v1->inventory.item_conditions >> (index << 1)) & 3) &&
                           ((((temp_v0 & 0xF000) >> 0xC) != 2) || (((temp_v0 & 0xF00) >> 8) != 1)))) {
        return true;
    }

    return false;
}

s32 mSM_check_item_for_exchange(s32 index, s32 arg1) {
    Private_c* temp_v0 = common_data.now_private;
    u16 temp_v1 = temp_v0->inventory.pockets[index];
    UNUSED s32 pad;

    if (!((temp_v0->inventory.item_conditions >> (index << 1)) & 3) && (temp_v1 != 0)) {
        if ((((temp_v1 & 0xF000) >> 0xC) == 2) && (((temp_v1 & 0xF00) >> 8) == 3) &&
            ((((arg1 & 0xF000) >> 0xC) != 2) || (((arg1 & 0xF00) >> 8) != 3))) {
            Player* player = get_player_actor_withoutCheck((Game_Play*)gamePT);
            UNK_TYPE sp2C;

            if (mCoBG_SearchWaterLimitDistN(&sp2C, player->actor.world.pos, player->actor.shape.rot.y, 100.0f, 0xA) ==
                0) {
                return false;
            }
        }
        return true;
    }

    return false;
}

typedef s32 (*checkProcessFunc)(s32, s32);

checkProcessFunc check_process[INVENTORY_ITEM_LIST_MAX] = {
    NULL,                         // INVENTORY_ITEM_LIST_0
    NULL,                         // INVENTORY_ITEM_LIST_1
    mSM_check_item_for_entrust,   // INVENTORY_ITEM_LIST_ENTRUST
    NULL,                         // INVENTORY_ITEM_LIST_3
    NULL,                         // INVENTORY_ITEM_LIST_4
    mSM_check_item_for_sell,      // INVENTORY_ITEM_LIST_SELL
    mSM_check_item_for_give,      // INVENTORY_ITEM_LIST_GIVE
    NULL,                         // INVENTORY_ITEM_LIST_7
    mSM_check_item_for_take,      // INVENTORY_ITEM_LIST_TAKE
    mSM_check_item_for_furniture, // INVENTORY_ITEM_LIST_FURNITURE
    mSM_check_item_for_minidisk,  // INVENTORY_ITEM_LIST_MINIDISK
    mSM_check_item_for_shrine,    // INVENTORY_ITEM_LIST_SHRINE
    NULL,                         // INVENTORY_ITEM_LIST_C
    mSM_check_item_for_exchange,  // INVENTORY_ITEM_LIST_ECHANGE
    NULL,                         // INVENTORY_ITEM_LIST_E
    NULL,                         // INVENTORY_ITEM_LIST_F
};

u32 mSM_check_open_inventory_itemlist(InventoryItemList itemlist, s32 arg1) {
    checkProcessFunc func = check_process[itemlist];
    s32 index;
    u32 ret;

    if (func == NULL) {
        return 0xFFFF;
    }

    ret = 0;
    for (index = 0; index < mPr_POCKETS_SLOT_COUNT; index++) {
        if (func(index, arg1)) {
            ret |= 1 << index;
        }
    }

    return ret;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/mSM_Object_Exchange_keep_new.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/mSM_Object_Exchange_keep_new_MenuTexAndPallet.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/mSM_Object_Exchange_keep_new_Menu.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/mSM_Get_ground_tex_p.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/mSM_Get_ground_pallet_p.s")
