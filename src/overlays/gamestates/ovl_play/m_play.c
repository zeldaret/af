#include "global.h"
#include "m_play.h"
#include "6A6E80.h"
#include "m_npc.h"
#include "m_handbill.h"
#include "m_field_make.h"
#include "m_malloc.h"
#include "m_msg_main.h"
#include "m_debug.h"
#include "m_player_lib.h"
#include "6F5550.h"
#include "6EC9E0.h"
#include "6EDD10.h"
#include "69E2C0.h"
#include "683030.h"
#include "6E30B0.h"
#include "6C97F0.h"
#include "6EFC20.h"
#include "67D890.h"
#include "6DA460.h"
#include "6ECD90.h"
#include "6BA500.h"
#include "6D3CB0.h"
#include "libc64/qrand.h"
#include "m_controller.h"
#include "m_debug_display.h"
#include "6E0F50.h"
#include "m_lights.h"
#include "m_private.h"
#include "m_skin_matrix.h"
#include "gfxalloc.h"
#include "version.h"
#include "libu64/gfxprint.h"
#include "libc/alloca.h"
#include "z_std_dma.h"
#include "67E840.h"
#include "overlays/gamestates/ovl_famicom_emu/famicom_emu.h"
#include "overlays/gamestates/ovl_trademark/m_trademark.h"
#include "6A7D20.h"
#include "m_scene_table.h"

void play_main(Game* game);
void Gameplay_Scene_Read(Game_Play* gamePlay, s16 arg1);
void Game_play_fbdemo_wipe_create(Game_Play* gamePlay);
void Game_play_fbdemo_wipe_init(Game_Play* gamePlay);
void Game_play_fbdemo_wipe_move(Game_Play* gamePlay);

Game_PlayUnkFuncsStruct D_80804320_jp = {
    fbdemo_wipe1_init,
    (void*)none_proc1,
    fbdemo_wipe1_move,
    fbdemo_wipe1_draw,
    fbdemo_wipe1_startup,
    fbdemo_wipe1_settype,
    fbdemo_wipe1_setcolor_rgba8888,
    NULL,
    fbdemo_wipe1_is_finish,
};

Game_PlayUnkFuncsStruct D_80804344_jp = {
    fbdemo_triforce_init,
    (void*)none_proc1,
    fbdemo_triforce_move,
    fbdemo_triforce_draw,
    fbdemo_triforce_startup,
    fbdemo_triforce_settype,
    fbdemo_triforce_setcolor_rgba8888,
    NULL,
    fbdemo_triforce_is_finish,
};

Game_PlayUnkFuncsStruct D_80804368_jp = {
    fbdemo_fade_init,
    (void*)none_proc1,
    fbdemo_fade_move,
    fbdemo_fade_draw,
    fbdemo_fade_startup,
    fbdemo_fade_settype,
    fbdemo_fade_setcolor_rgba8888,
    NULL,
    fbdemo_fade_is_finish,
};

Game_PlayUnkFuncsStruct* D_8080438C_jp[] = {
    &D_80804320_jp, &D_80804344_jp, &D_80804368_jp, &D_80804368_jp, &D_80804344_jp, &D_80804344_jp, &D_80804368_jp,
};

typedef void (*Game_PlayUnkFunc)(Game_Play* gamePlay);
Game_PlayUnkFunc D_808043A8_jp[] = {
    (void*)none_proc1,
    Game_play_fbdemo_wipe_create,
    Game_play_fbdemo_wipe_init,
    Game_play_fbdemo_wipe_move,
};

static Play80804480 fbdemo;
static void* B_8080455C_jp;
static u16 sBackTitleTimer;
static u16 sSeEndcheckTimeout;

void Game_play_Reset_destiny(void) {
    Destiny* destiny = &gCommonData.nowPrivate->destiny;
    u8* day = &gCommonData.time.rtcTime.day;
    u8* month = &gCommonData.time.rtcTime.month;

    if ((destiny->type != 0) && ((gCommonData.time.rtcTime.year != destiny->receivedTime.year) ||
                                 (*month != destiny->receivedTime.month) || (*day != destiny->receivedTime.day))) {
        destiny->type = 0;
    }
}

void event_title_flag_on(void) {
    if (gCommonData.unk_107E4 != 0) {
        gCommonData.unk_10A82 = 1;
    }
}

void event_title_flag_off(void) {
    if (gCommonData.unk_107E4 == 2) {
        gCommonData.unk_107E4 = 0;
        gCommonData.unk_10A82 = 0;
    }
}

void Game_play_camera_proc(Game_Play* gamePlay) {
    Camera2_ClearActorTalking_Cull(gamePlay);
    Camera2_process(gamePlay);
}

void Game_play_fbdemo_wipe_destroy(Game_Play* gamePlay) {
    gamePlay->unk_1EE8.unk_21C.unk_04(&gamePlay->unk_1EE8, gamePlay);
    gamePlay->unk_1EE3 = 0;
    gamePlay->unk_1EE8.unk_218 = -1;
}

void Game_play_fbdemo_wipe_create_sub(Game_Play* gamePlay) {
    s32 sp1C = gamePlay->unk_1EE1;

    bzero(&gamePlay->unk_1EE8, sizeof(Game_Play_Unk_1EE8));
    if (sp1C >= 7) {
        sp1C = 1;
    }
    gamePlay->unk_1EE8.unk_218 = sp1C;

    {
        Game_PlayUnkFuncsStruct* temp_v0 = D_8080438C_jp[sp1C];

        gamePlay->unk_1EE8.unk_21C.unk_00 = temp_v0->unk_00;
        gamePlay->unk_1EE8.unk_21C.unk_04 = temp_v0->unk_04;
        gamePlay->unk_1EE8.unk_21C.unk_08 = temp_v0->unk_08;
        gamePlay->unk_1EE8.unk_21C.unk_0C = temp_v0->unk_0C;
        gamePlay->unk_1EE8.unk_21C.unk_10 = temp_v0->unk_10;
        gamePlay->unk_1EE8.unk_21C.unk_14 = temp_v0->unk_14;
        gamePlay->unk_1EE8.unk_21C.unk_18 = temp_v0->unk_18;
        gamePlay->unk_1EE8.unk_21C.unk_20 = temp_v0->unk_20;
    }
}

void Game_play_fbdemo_wipe_create(Game_Play* gamePlay) {
    Game_play_fbdemo_wipe_create_sub(gamePlay);
    Game_play_fbdemo_wipe_init(gamePlay);
}

void Game_play_fbdemo_wipe_init(Game_Play* gamePlay) {
    Game_Play_Unk_1EE8* temp_s0 = &gamePlay->unk_1EE8;
    u8 var_v0;

    gamePlay->unk_1EE8.unk_21C.unk_00(temp_s0);

    gCommonData.unk_1014A = 14;
    gCommonData.unk_10149 = 30;

    temp_s0->unk_21C.unk_18(temp_s0, 0);

    var_v0 = gamePlay->unk_1EE0;
    if (temp_s0->unk_218 == 4) {
        var_v0 |= 0x80;
    } else if (temp_s0->unk_218 == 5) {
        var_v0 |= 0x40;
    }

    temp_s0->unk_21C.unk_14(temp_s0, var_v0);
    temp_s0->unk_21C.unk_10(temp_s0);

    gamePlay->unk_1EE3 = 3;
    sBackTitleTimer = 300;
    sSeEndcheckTimeout = 300;
}

void Game_play_fbdemo_fade_in_move_end(Game_Play* gamePlay) {
    Game_play_fbdemo_wipe_destroy(gamePlay);
    if (gamePlay->unk_1EE2 == 3) {
        fbdemo_cleanup(&fbdemo);
        gamePlay->unk_1EE2 = 0;
        SetGameFrame(3);
    }
}

void Game_play_fbdemo_fade_out_start_emu_move_end(Game_Play* gamePlay) {
    STOP_GAMESTATE(&gamePlay->state);
    SET_NEXT_GAMESTATE(&gamePlay->state, famicom_emu_init, sizeof(Game_FamicomEmu));
}

void Game_play_fbdemo_fade_out_game_end_move_end(Game_Play* gamePlay) {
    STOP_GAMESTATE(&gamePlay->state);
    SET_NEXT_GAMESTATE(&gamePlay->state, trademark_init, sizeof(Game_Trademark));
}

void Game_play_change_scene_move_end(Game_Play* gamePlay) {
    game_goto_next_game_play(&gamePlay->state);
    gCommonData.unk_10004 = gCommonData.save.unk_00014;
    gCommonData.save.unk_00014 = gamePlay->unk_1E18;
}

void Game_play_fbdemo_wipe_move(Game_Play* gamePlay) {
    UNUSED s32 pad[2];
    s16 sp26 = 0;
    s32 sp20 = 1;
    Game_Play_Unk_1EE8* sp18 = &gamePlay->unk_1EE8;

    if (gamePlay->unk_1EE8.unk_21C.unk_20(sp18, gamePlay) != 0) {
        if ((gamePlay->unk_1EE0 != 1) && (gamePlay->unk_1EE0 != 11)) {
            if (sSeEndcheckTimeout != 0) {
                sSeEndcheckTimeout--;
            }

            if ((func_800D2334_jp(sp18, gamePlay) == 0) && (sSeEndcheckTimeout != 0)) {
                sp20 = 0;
            } else {
                func_800D2568_jp(1);
            }
        }

        if (gamePlay->unk_1EE0 == 11) {
            func_800D2568_jp(2);
        }

        if (sp20 == 1) {
            switch (gamePlay->unk_1EE0) {
                case 1:
                    Game_play_fbdemo_fade_in_move_end(gamePlay);
                    break;

                case 3:
                    //! FAKE
                    if (1) {}
                    if (1) {}
                    Game_play_fbdemo_fade_out_start_emu_move_end(gamePlay);
                    break;

                case 4:
                case 6:
                    if (sBackTitleTimer == 300) {
                        mBGMPsComp_make_ps_wipe(0x168, gamePlay);
                    }

                case 5:
                case 10:
                    if (sBackTitleTimer != 0) {
                        sBackTitleTimer--;
                    }

                    if ((sAdo_BgmFadeoutCheck() == 1) || (sBackTitleTimer == 0)) {
                        Game_play_fbdemo_fade_out_game_end_move_end(gamePlay);
                    } else {
                        sp26 = 1;
                    }
                    break;

                case 8:
                    if (gCommonData.unk_100E4 != NULL) {
                        if (*gCommonData.unk_100E4 != NULL) {
                            (*gCommonData.unk_100E4)(gamePlay);
                            Game_play_change_scene_move_end(gamePlay);
                        }
                    }
                    break;

                case 9:
                    if (sBackTitleTimer != 0) {
                        sBackTitleTimer--;
                    }

                    if ((sAdo_BgmFadeoutCheck() == 1) || (sBackTitleTimer == 0)) {
                        Game_play_change_scene_move_end(gamePlay);
                    } else {
                        sp26 = 1;
                    }
                    break;

                default:
                    Game_play_change_scene_move_end(gamePlay);
                    break;
            }

            if (sp26 == 0) {
                gamePlay->unk_1EE0 = 0;
            }
        }
    } else {
        sp18->unk_21C.unk_08(sp18, game_GameFrame);
    }
}

void Game_play_fbdemo_wipe_proc(Game_Play* gamePlay) {
    if ((gamePlay->unk_1EE3 == 0) && (gamePlay->unk_1EE0 != 0)) {
        gamePlay->unk_1EE3 = 1;
    }
    D_808043A8_jp[gamePlay->unk_1EE3](gamePlay);
}

Gfx* game_play_set_fog(Game_Play* gamePlay, Gfx* gfx) {
    return gfx_set_fog_nosync(gfx, gamePlay->glight.fogColor[0], gamePlay->glight.fogColor[1],
                              gamePlay->glight.fogColor[2], 0, gamePlay->glight.fogNear, gamePlay->glight.fogFar);
}

void Game_play_fbdemo_proc(Game_Play* gamePlay) {
    UNUSED s32 pad;
    GraphicsContext* gfxCtx = gamePlay->state.gfxCtx;

    switch (gamePlay->unk_1EE2) {
        case 2:
            if (fbdemo_init(&fbdemo, 10, 7, gamePlay) == 0) {
                gamePlay->unk_1EE2 = 0;
            } else {
                B_8080455C_jp = gfxCtx->unk_008;
                gamePlay->unk_1EE2 = 3;
                SetGameFrame(1);
            }
            break;
        case 3:
            fbdemo_move(&fbdemo);
            break;
    }
}

void play_cleanup(Game* game) {
    Game_Play* gamePlay = (Game_Play*)game;

    func_800A3304_jp(gamePlay);
    gamePlay->state.gfxCtx->unk_2F4 = 0;
    gamePlay->state.gfxCtx->unk_2F8 = 0;
    gamePlay->submenu.unk_00 = 0;
    PreRender_cleanup(&gamePlay->unk_1DC0);
    CollisionCheck_dt(gamePlay, &gamePlay->unk_2138);

    if (gamePlay->unk_1EE2 == 3) {
        fbdemo_cleanup(&fbdemo);
        gamePlay->unk_1EE2 = 0;
    }

    if (gamePlay->unk_1EE3 == 3) {
        Game_play_fbdemo_wipe_destroy(gamePlay);
    }

    Actor_info_dt(&gamePlay->actorInfo, gamePlay);
    mEv_finish(&gamePlay->event);
    func_800AA124_jp();
    mSM_submenu_dt(&gamePlay->submenu);
    gamePlay->unk_1DAC = -1;
    mSM_submenu_ovlptr_cleanup(&gamePlay->submenu);
    mPlib_Object_Exchange_keep_Player_dt(gamePlay);
    mHsRm_GetHuusuiRoom(0, gCommonData.playerNo);
    func_80087280_jp();
    zelda_CleanupArena();
}

void play_init(Game* game) {
    Game_Play* gamePlay = (Game_Play*)game;
    GraphicsContext* gfxCtx = gamePlay->state.gfxCtx;
    u32 temp_v1;
    u32 temp_v0_2;
    UNUSED s32 pad[2];
    u8 temp;
    s32 sp30;

    //! FAKE
    if (gamePlay && gamePlay && gamePlay) {}

    game_resize_hyral(&gamePlay->state, 0x7D0000);
    func_800D2568_jp(0);
    event_title_flag_on();
    func_800C9010_jp();
    mTM_set_season();
    func_800B594C_jp();
    mSM_submenu_ovlptr_init(gamePlay);
    func_8007CFD8_jp(gamePlay);
    mEv_init(&gamePlay->event);
    initView(&gamePlay->unk_1938, gfxCtx);
    func_80064F48_jp(gamePlay);
    CollisionCheck_ct(gamePlay, &gamePlay->unk_2138);
    func_8006BB64_jp();
    func_8006C8D0_jp();
    gamePlay->unk_1DAC = -1;
    Gameplay_Scene_Read(gamePlay, gCommonData.save.unk_00014);
    mSM_submenu_ct(&gamePlay->submenu);
    gamePlay->submenu.unk_00 = 0;
    PreRender_init(&gamePlay->unk_1DC0);
    PreRender_setup_savebuf(&gamePlay->unk_1DC0, 0x140, 0xF0, 0, 0, 0);
    PreRender_setup_renderbuf(&gamePlay->unk_1DC0, 0x140, 0xF0, NULL, NULL);

    //! FAKE
    if (1) {}
    gamePlay->unk_1EE2 = 0;
    gamePlay->unk_1EE3 = 0;
    gamePlay->unk_1EE0 = 1;

    temp = 1;
    if (gCommonData.unk_1014B != 0xFF) {
        temp = gCommonData.unk_1014B;
        gCommonData.unk_1014B = 0xFF;
    }
    gamePlay->unk_1EE1 = temp;

    Pause_ct(&gamePlay->pause);
    new_Matrix(&gamePlay->state);
    gamePlay->state.main = play_main;
    gamePlay->state.destroy = play_cleanup;
    fbdemo_fade_init(&gamePlay->unk_2128);
    fbdemo_fade_settype(&gamePlay->unk_2128, 7);
    fbdemo_fade_setcolor_rgba8888(&gamePlay->unk_2128, 0xA0A0A0FF);
    fbdemo_fade_startup(&gamePlay->unk_2128);
    gamePlay->unk_220C = 0;
    sp30 = THA_getFreeBytes(&gamePlay->state.heap);
    temp_v0_2 = (u32)THA_alloc16(&gamePlay->state.heap, sp30);
    temp_v1 = ALIGN16(temp_v0_2);
    //! FAKE
    zelda_InitArena((void*)(temp_v1 & 0xFFFFFFFF), (sp30 - temp_v1) + temp_v0_2);
    func_800C2EE0_jp();
    func_80087004_jp();
    Actor_info_ct(gamePlay, &gamePlay->actorInfo, gamePlay->unk_1EA8);
    gamePlay->unk_2208 = (void*)none_proc1;
    mMsg_ct(gamePlay);
    mEv_2nd_init(&gamePlay->event);
    mTD_player_keydata_init(gamePlay);
    Balloon_init(gamePlay);
    func_800A65C4_jp();
    func_80059BF0_jp();
    func_800CBF80_jp();
    event_title_flag_off();
}

void Game_play_move_fbdemo_not_move(Game_Play* gamePlay) {
    UNUSED s32 pad[2];

    gamePlay->state.unk_9D = 0x8F;
    gamePlay->state.unk_9C = 1;
    mSM_submenu_ctrl(gamePlay);
    if (gamePlay->submenu.moveProcIndex == MSM_MOVE_PROC_WAIT) {
        gamePlay->state.unk_9C = 2;
        mDemo_Main(gamePlay);
        gamePlay->state.unk_9C = 3;
        mEv_run(&gamePlay->event);
    }
    gamePlay->state.unk_9C = 4;
    mDemo_stock_clear();
    gamePlay->state.unk_9C = 5;
    mSc_dmacopy_data_bank(gamePlay->unk_0110);
    gamePlay->state.unk_9C = 6;
    mSM_submenu_move(&gamePlay->submenu);
    if ((gamePlay->submenu.moveProcIndex == MSM_MOVE_PROC_WAIT) && (REGADDR(IREG, 0x48) == 0)) {
        gamePlay->unk_1EA0++;
        gamePlay->state.unk_9C = 7;
        CollisionCheck_OC(gamePlay, &gamePlay->unk_2138);
        gamePlay->state.unk_9C = 8;
        CollisionCheck_clear(gamePlay, &gamePlay->unk_2138);
        gamePlay->state.unk_9D = 0x90;
        gamePlay->state.unk_9C = 0;
        Actor_info_call_actor(gamePlay, &gamePlay->actorInfo);
        gamePlay->state.unk_9D = 0x91;
        gamePlay->state.unk_9C = 1;
        mCoBG_CalcTimerDecalCircle();
        gamePlay->state.unk_9C = 2;
        mMsg_Main(gamePlay);
    }
    fbdemo_fade_move(&gamePlay->unk_2128, game_GameFrame);
}

void Game_play_move(Game_Play* gamePlay) {
    Game_Play_unk_0110* p = gamePlay->unk_0110;
    s32 var_v1;

    gamePlay->state.unk_9D = 0x8D;
    gamePlay->state.unk_9C = 1;
    Game_play_Reset_destiny();
    gSegments[4] = (uintptr_t)OS_K0_TO_PHYSICAL(p->segment);
    gSegments[2] = (uintptr_t)OS_K0_TO_PHYSICAL(gamePlay->unk_010C);
    gamePlay->state.unk_9C = 2;

    if (zurumode_flag >= 2) {
        var_v1 = Pause_proc(&gamePlay->pause, CONTROLLER2(&gamePlay->state)) == 0;
    } else {
        var_v1 = 0;
    }

    gamePlay->state.unk_9D = 0x8E;
    gamePlay->state.unk_9C = 0;

    if (var_v1 == 0) {
        gamePlay->state.unk_9C = 1;
        Game_play_fbdemo_wipe_proc(gamePlay);
        gamePlay->state.unk_9C = 2;
        Game_play_fbdemo_proc(gamePlay);
        gamePlay->state.unk_9C = 3;
        if (gamePlay->unk_1EE2 != 3) {
            Game_play_move_fbdemo_not_move(gamePlay);
        }
    }

    if (gamePlay->submenu.moveProcIndex == MSM_MOVE_PROC_WAIT) {
        gamePlay->state.unk_9D = 0x92;
        gamePlay->state.unk_9C = 1;
        Game_play_camera_proc(gamePlay);
        gamePlay->state.unk_9C = 2;
        mPO_business_proc(gamePlay);
        gamePlay->state.unk_9C = 3;
        mTRC_move(gamePlay);
        gamePlay->state.unk_9C = 4;
        Balloon_move(gamePlay);
    }

    gamePlay->state.unk_9D = 0x93;
    gamePlay->state.unk_9C = 1;
    Global_kankyo_set(gamePlay, &gamePlay->kankyo, &gamePlay->glight);
    gamePlay->state.unk_9C = 2;
    mEnv_WindMove();
    gamePlay->state.unk_9C = 3;
    watch_my_step_move(gamePlay);
    gamePlay->state.unk_9C = 4;
    banti_move(gamePlay);
    gamePlay->state.unk_9C = 5;
    title_demo_move(gamePlay);
    gamePlay->state.unk_9D = 0x95;
    gamePlay->state.unk_9C = 0;
}

void func_80803810_jp(Game_Play* gamePlay, GraphicsContext* gfxCtx) {
    void* temp_v0 = gamePlay->unk_0110[0].segment;

    gSegments[4] = (uintptr_t)OS_K0_TO_PHYSICAL(temp_v0);
    gSegments[2] = (uintptr_t)OS_K0_TO_PHYSICAL(gamePlay->unk_010C);

    OPEN_DISPS(gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x00, NULL);
    gSPSegment(POLY_XLU_DISP++, 0x00, NULL);
    gSPSegment(OVERLAY_DISP++, 0x00, NULL);
    gSPSegment(UNK_2B0_DISP++, 0x00, NULL);
    gSPSegment(UNK_2C0_DISP++, 0x00, NULL);
    gSPSegment(LIGHT_DISP++, 0x00, NULL);

    gSPSegment(POLY_OPA_DISP++, 0x04, temp_v0);
    gSPSegment(POLY_XLU_DISP++, 0x04, temp_v0);
    gSPSegment(OVERLAY_DISP++, 0x04, temp_v0);
    gSPSegment(UNK_2B0_DISP++, 0x04, temp_v0);
    gSPSegment(UNK_2C0_DISP++, 0x04, temp_v0);
    gSPSegment(LIGHT_DISP++, 0x04, temp_v0);

    gSPSegment(POLY_OPA_DISP++, 0x02, gamePlay->unk_010C);
    gSPSegment(POLY_XLU_DISP++, 0x02, gamePlay->unk_010C);
    gSPSegment(OVERLAY_DISP++, 0x02, gamePlay->unk_010C);
    gSPSegment(UNK_2B0_DISP++, 0x02, gamePlay->unk_010C);
    gSPSegment(UNK_2C0_DISP++, 0x02, gamePlay->unk_010C);
    gSPSegment(LIGHT_DISP++, 0x02, gamePlay->unk_010C);

    CLOSE_DISPS(gfxCtx);
}

void setupFog(Game_Play* gamePlay, GraphicsContext* gfxCtx) {
    OPEN_DISPS(gfxCtx);

    POLY_OPA_DISP = game_play_set_fog(gamePlay, POLY_OPA_DISP);
    POLY_XLU_DISP = game_play_set_fog(gamePlay, POLY_XLU_DISP);

    CLOSE_DISPS(gfxCtx);
}

void setupViewer(Game_Play* gamePlay) {
    showView(&gamePlay->unk_1938, 0xF, gamePlay);
}

void setupViewMatrix(Game_Play* gamePlay, GraphicsContext* __gfxCtx, GraphicsContext* gfxCtx2) {
    // TODO: A way to fit OPEN_DISPS/CLOSE_DISPS on the stack
    Matrix_MtxtoMtxF(&gamePlay->unk_1938.unk_0A0, &gamePlay->billboardMtxF);
    Matrix_MtxtoMtxF(&gamePlay->unk_1938.unk_060, &gamePlay->viewProjectionMtxF);
    Skin_Matrix_MulMatrix(&gamePlay->viewProjectionMtxF, &gamePlay->billboardMtxF, &gamePlay->viewProjectionMtxF);

    gamePlay->billboardMtxF.mf[0][3] = 0.0f;
    gamePlay->billboardMtxF.mf[1][3] = 0.0f;
    gamePlay->billboardMtxF.mf[2][3] = 0.0f;
    gamePlay->billboardMtxF.mf[3][0] = 0.0f;
    gamePlay->billboardMtxF.mf[3][1] = 0.0f;
    gamePlay->billboardMtxF.mf[3][2] = 0.0f;

    Matrix_reverse(&gamePlay->billboardMtxF);

    gamePlay->unk_1E9C = _MtxF_to_Mtx(&gamePlay->billboardMtxF, GRAPH_ALLOC(gfxCtx2, sizeof(MtxF) * 1));

    gSPSegment(POLY_OPA_DISP++, 0x01, gamePlay->unk_1E9C);
}

s32 makeBumpTexture(Game_Play* gamePlay, GraphicsContext* __gfxCtx, GraphicsContext* gfxCtx2) {
    // TODO: A way to fit OPEN_DISPS/CLOSE_DISPS on the stack
    {
        Gfx* sp194;
        Gfx* sp190;
        sp190 = POLY_OPA_DISP;
        sp194 = gfxopen(sp190);

        gSPDisplayList(OVERLAY_DISP++, sp194);

        if (gamePlay->unk_1EE3 == 3) {
            Game_Play1938 sp60;
            ScissorViewArg1 sp50;

            initView(&sp60, gfxCtx2);
            {
                sp60.unk_120 = 10;
            //! FAKE
            label2:;
            }
            sp50.unk_04 = 0xF0, sp50.unk_0C = 0x140;
            sp50.unk_00 = 0;
            sp50.unk_08 = 0;
            setScissorView(&sp60, &sp50);
            showView1(&sp60, 0xF, &sp194);
            gamePlay->unk_1EE8.unk_21C.unk_0C(&gamePlay->unk_1EE8, &sp194);
        }

        fbdemo_fade_draw(&gamePlay->unk_2128, &sp194);
        fade_rgba8888_draw(&sp194, gamePlay->unk_220C);

        gSPEndDisplayList(sp194++);

        gfxclose(sp190, sp194);
        POLY_OPA_DISP = sp194;
    }

    if (gamePlay->unk_1EE2 == 3) {
        Gfx* sp48 = POLY_OPA_DISP;

        fbdemo_draw(&fbdemo, &sp48);
        POLY_OPA_DISP = sp48;
        return 1;
    }

    PreRender_setup_renderbuf(&gamePlay->unk_1DC0, 0x140, 0xF0, gfxCtx2->unk_2E4, gfxCtx2->unk_008);
    if (gamePlay->submenu.unk_00 == 2) {
        func_800B0010_jp();
        PreRender_ConvertFrameBuffer_fg(&gamePlay->unk_1DC0);
        gamePlay->submenu.unk_00 = 3;
    } else if (gamePlay->submenu.unk_00 >= 5) {
        gamePlay->submenu.unk_00 = 0;
    }

    if (gamePlay->submenu.unk_00 == 3) {
        Gfx* sp44 = POLY_OPA_DISP;

        PreRender_loadFrameBufferCopy(&gamePlay->unk_1DC0, &sp44);
        POLY_OPA_DISP = sp44;
        return 1;
    }

    {
        LightsN* sp40 = Global_light_read(&gamePlay->glight, gfxCtx2);

        LightsN_list_check(sp40, gamePlay->glight.list, NULL);
        LightsN_disp(sp40, gfxCtx2);
    }

    Actor_info_draw_actor(gamePlay, &gamePlay->actorInfo);
    Camera2_draw(gamePlay);
    mMsg_Draw(gamePlay);
    Debug_Display_output(gamePlay);

    if ((gamePlay->submenu.unk_00 == 1) || (gamePlay->unk_1EE2 == 1)) {
        Gfx* sp3C;
        Gfx* sp38;

        sp38 = POLY_OPA_DISP;
        sp3C = gfxopen(sp38);

        gSPDisplayList(OVERLAY_DISP++, sp3C);

        gamePlay->unk_1DC0.unk_10 = gfxCtx2->unk_2E4;
        gamePlay->unk_1DC0.unk_14 = gfxCtx2->unk_008;
        PreRender_saveFrameBuffer(&gamePlay->unk_1DC0, &sp3C);

        if (gamePlay->submenu.unk_00 == 1) {
            gamePlay->unk_1DC0.unk_18 = gfxCtx2->unk_2E4;
            PreRender_saveCVG(&gamePlay->unk_1DC0, &sp3C);
            gamePlay->submenu.unk_00 = 2;
        } else {
            gamePlay->unk_1EE2 = 2;
        }

        gSPEndDisplayList(sp3C++);

        gfxclose(sp38, sp3C);
        POLY_OPA_DISP = sp3C;

        REGADDR(SREG, 0x21) |= 1;
        return 0;
    }
    return 1;
}

void draw_version(GraphicsContext* gfxCtx) {
    Gfx* temp_s0;
    gfxprint* printer;

    OPEN_DISPS(gfxCtx);

    temp_s0 = func_800BD720_jp(OVERLAY_DISP);
    printer = alloca(sizeof(gfxprint));

    gfxprint_init(printer);
    gfxprint_open(printer, temp_s0);
    gfxprint_color(printer, 255, 155, 255, 255);
    gfxprint_color(printer, 255, 255, 255, 255);
    if (temp_s0 && temp_s0 && temp_s0) {}
    gfxprint_locate8x8(printer, 7, 0x1A);
    gfxprint_printf(printer, "[Creator:%s]", __Creator__);
    gfxprint_locate8x8(printer, 7, 0x1B);
    gfxprint_printf(printer, "[Date:%s]", __DateTime__);
    temp_s0 = gfxprint_close(printer);
    gfxprint_cleanup(printer);
    OVERLAY_DISP = temp_s0;

    CLOSE_DISPS(gfxCtx);
}

void Game_play_draw(Game_Play* gamePlay) {
    GraphicsContext* gfxCtx = gamePlay->state.gfxCtx;
    u8 sp2B = 0;
    u8 sp2A = 0;
    u8 sp29 = 0;

    //! FAKE
label:;
    func_80803810_jp(gamePlay, gfxCtx);
    if (gCommonData.unk_10001 == 0) {
        if (mEv_CheckTitleDemo() != -9) {
            sp2B = gamePlay->kankyo.unk_AE;
            sp2A = gamePlay->kankyo.unk_AF;
            sp29 = gamePlay->kankyo.unk_B0;
        }
    }

    DisplayList_initialize(gfxCtx, sp2B, sp2A, sp29, gamePlay);
    setupFog(gamePlay, gfxCtx);
    setupViewer(gamePlay);
    setupViewMatrix(gamePlay, gfxCtx, gfxCtx);

    //! FAKE
    if (1) {}
    if (1) {}
    if (1) {}

    if (makeBumpTexture(gamePlay, gfxCtx, gfxCtx) == 1) {
        watch_my_step_draw(gamePlay);
        banti_draw(gamePlay);
        mSM_submenu_draw(&gamePlay->submenu, gamePlay);
    }

    if (zurumode_flag != 0) {
        switch (mEv_CheckTitleDemo()) {
            case -9:
            case -1:
            default:
                draw_version(gfxCtx);
                break;

            case 0:
                break;
        }
    }
}

void play_main(Game* game) {
    Game_Play* gamePlay = (Game_Play*)game;

    gamePlay->state.unk_9D = 0x6E;
    gamePlay->state.unk_9C = 0;
    fqrand();
    gamePlay->state.unk_9D = 0x78;
    gamePlay->state.unk_9C = 0;
    mCon_main(&gamePlay->state);
    gamePlay->state.unk_9D = 0x82;
    gamePlay->state.unk_9C = 0;
    Debug_Display_init();
    gamePlay->state.unk_9D = 0x8C;
    gamePlay->state.unk_9C = 0;
    Game_play_move(gamePlay);
    gamePlay->state.unk_9D = 0xAA;
    gamePlay->state.unk_9C = 0;
    Game_play_draw(gamePlay);
    gamePlay->state.unk_9D = 0xB4;
    gamePlay->state.unk_9C = 0;
    if (gamePlay->submenu.unk_00 != 2) {
        GraphicsContext* gfxCtx = gamePlay->state.gfxCtx;

        game_debug_draw_last(&gamePlay->state, gfxCtx);
        game_draw_last(gfxCtx);
        gamePlay->state.unk_9C = 0;
    }
    gamePlay->state.unk_9D = 0xBE;
}

void* func_80804138_jp(Game_Play* gamePlay, Struct_8010EAA0* arg1) {
    u32 sp24 = arg1->unk_04 - arg1->unk_00;
    void* sp20 = THA_alloc16(&gamePlay->state.heap, sp24);

    DmaMgr_RequestSyncDebug(sp20, arg1->unk_00, sp24, "../m_play.c", 2302);
    return sp20;
}

void func_808041A4_jp(Game_Play* gamePlay) {
    Global_kankyo_ct(gamePlay, &gamePlay->kankyo);
}

void Gameplay_Scene_Init(Game_Play* gamePlay) {
    gamePlay->unk_1EA8 = NULL;
    gamePlay->unk_1EA5 = 0;
    gamePlay->unk_1EA6 = 0;
    gamePlay->unk_1EA7 = 0;
    gamePlay->unk_1EB8 = 0;
    mSc_data_bank_ct(gamePlay, gamePlay->unk_0110);
    Global_light_ct(&gamePlay->glight);
    Door_info_ct(&gamePlay->unk_1E10);
    common_data_clear();
    Scene_ct(gamePlay, gamePlay->unk_010C);
    mSc_decide_exchange_bank(gamePlay->unk_0110);
    func_808041A4_jp(gamePlay);
}

s32 mPl_SceneNo2SoundRoomType(s32 arg0) {
    switch (arg0) {
        case 20:
            return 1;
        case 6:
        case 9:
        case 12:
        case 14:
        case 18:
        case 21:
        case 31:
            return 2;
        case 17:
        case 22:
        case 23:
        case 24:
        case 25:
        case 29:
            return 3;
        default:
            return 0;
    }
}

void Gameplay_Scene_Read(Game_Play* gamePlay, s16 arg1) {
    Struct_8010EAA0* sp1C = &scene_data_status[arg1];

    sp1C->unk_13 = 0;
    gamePlay->unk_2210 = sp1C;
    gamePlay->unk_00E0 = arg1;
    gamePlay->unk_010C = func_80804138_jp(gamePlay, sp1C);
    sp1C->unk_13 = 0;
    gSegments[2] = (uintptr_t)OS_K0_TO_PHYSICAL(gamePlay->unk_010C);
    Gameplay_Scene_Init(gamePlay);
    sAdo_RoomType(mPl_SceneNo2SoundRoomType(gCommonData.save.unk_00014));
}
