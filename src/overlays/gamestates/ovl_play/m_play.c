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
#include "libc64/qrand.h"
#include "m_controller.h"
#include "m_debug_display.h"
#include "6E0F50.h"
#include "6D2720.h"
#include "m_lights.h"
#include "m_skin_matrix.h"
#include "gfxalloc.h"
#include "build.h"
#include "libu64/gfxprint.h"
#include "libc/alloca.h"
#include "z_std_dma.h"
#include "67E840.h"
#include "overlays/gamestates/ovl_famicom_emu/famicom_emu.h"
#include "overlays/gamestates/ovl_trademark/m_trademark.h"

void func_8080407C_jp(GameState* gameState);
void func_80804288_jp(PlayState* play, s16 arg1);
void func_80802C90_jp(PlayState* play);
void func_80802CBC_jp(PlayState* play);
void func_80802E74_jp(PlayState* play);

void func_80084080_jp(void*);
void func_800840AC_jp();
void func_8008418C_jp(void*, u8);
void func_800843C8_jp(void*, Gfx**);
void func_80084480_jp(void*);
void func_800844B0_jp(void*, s32);
void func_800844C8_jp(void*, s32);

void func_80083CBC_jp(void*);
void func_80083D14_jp();
void func_80083E08_jp(void*, u8);
void func_80083C00_jp(void*, Gfx**);
void func_80084018_jp(void*);
void func_80084068_jp(void*, s32);
void func_8008400C_jp(void*, s32);

extern UNK_PTR* B_801458A0_jp[];
extern void* B_801458B0_jp;
extern D_8010EAA0 D_8010EAA0_jp[];

PlayStateUnkFuncsStruct D_80804320_jp = {
    func_80084080_jp, none_proc1, func_800840AC_jp, func_8008418C_jp, func_800843C8_jp, func_80084480_jp,
    func_800844B0_jp, NULL,       func_800844C8_jp,
};

PlayStateUnkFuncsStruct D_80804344_jp = {
    func_80083CBC_jp, none_proc1, func_80083D14_jp, func_80083E08_jp, func_80083C00_jp, func_80084018_jp,
    func_80084068_jp, NULL,       func_8008400C_jp,
};

PlayStateUnkFuncsStruct D_80804368_jp = {
    func_800844E0_jp, none_proc1, func_8008450C_jp, func_800845EC_jp, func_8008468C_jp, func_800846D4_jp,
    func_800846E0_jp, NULL,       func_800846EC_jp,
};

PlayStateUnkFuncsStruct* D_8080438C_jp[] = {
    &D_80804320_jp, &D_80804344_jp, &D_80804368_jp, &D_80804368_jp, &D_80804344_jp, &D_80804344_jp, &D_80804368_jp,
};

typedef void (*PlayStateUnkFunc)(PlayState* play);
PlayStateUnkFunc D_808043A8_jp[] = {
    none_proc1,
    func_80802C90_jp,
    func_80802CBC_jp,
    func_80802E74_jp,
};

Play80804480 B_80804480_jp;
void* B_8080455C_jp;
u16 B_80804560_jp;
u16 B_80804562_jp;

void func_80802AE0_jp(void) {
    CommonData10138_Sub* temp = &common_data.unk_10138->unk_A86;
    u8* one = &common_data.unk_1011F;
    u8* two = &common_data.unk_10121;

    if ((temp->unk_08 != 0) &&
        ((common_data.unk_10122 != temp->unk_06) || (*two != temp->unk_05) || (*one != temp->unk_03))) {
        temp->unk_08 = 0;
    }
}

void func_80802B40_jp(void) {
    if (common_data.unk_107E4 != 0) {
        common_data.unk_10A82 = 1;
    }
}

void func_80802B64_jp(void) {
    if (common_data.unk_107E4 == 2) {
        common_data.unk_107E4 = 0;
        common_data.unk_10A82 = 0;
    }
}

void func_80802B8C_jp(PlayState* play) {
    Camera2_ClearActorTalking_Cull(play);
    func_80064FD8_jp(play);
}

void func_80802BB8_jp(PlayState* play) {
    play->unk_1EE8.unk_21C.unk_04(&play->unk_1EE8, play);
    play->unk_1EE3 = 0;
    play->unk_1EE8.unk_218 = -1;
}

void func_80802BF4_jp(PlayState* play) {
    s32 sp1C = play->unk_1EE1;

    bzero(&play->unk_1EE8, sizeof(PlayState_Unk_1EE8));
    if (sp1C >= 7) {
        sp1C = 1;
    }
    play->unk_1EE8.unk_218 = sp1C;

    {
        PlayStateUnkFuncsStruct* temp_v0 = D_8080438C_jp[sp1C];

        play->unk_1EE8.unk_21C.unk_00 = temp_v0->unk_00;
        play->unk_1EE8.unk_21C.unk_04 = temp_v0->unk_04;
        play->unk_1EE8.unk_21C.unk_08 = temp_v0->unk_08;
        play->unk_1EE8.unk_21C.unk_0C = temp_v0->unk_0C;
        play->unk_1EE8.unk_21C.unk_10 = temp_v0->unk_10;
        play->unk_1EE8.unk_21C.unk_14 = temp_v0->unk_14;
        play->unk_1EE8.unk_21C.unk_18 = temp_v0->unk_18;
        play->unk_1EE8.unk_21C.unk_20 = temp_v0->unk_20;
    }
}

void func_80802C90_jp(PlayState* play) {
    func_80802BF4_jp(play);
    func_80802CBC_jp(play);
}

void func_80802CBC_jp(PlayState* play) {
    PlayState_Unk_1EE8* temp_s0 = &play->unk_1EE8;
    u8 var_v0;

    play->unk_1EE8.unk_21C.unk_00(temp_s0);

    common_data.unk_1014A = 14;
    common_data.unk_10149 = 30;

    temp_s0->unk_21C.unk_18(temp_s0, 0);

    var_v0 = play->unk_1EE0;
    if (temp_s0->unk_218 == 4) {
        var_v0 |= 0x80;
    } else if (temp_s0->unk_218 == 5) {
        var_v0 |= 0x40;
    }

    temp_s0->unk_21C.unk_14(temp_s0, var_v0);
    temp_s0->unk_21C.unk_10(temp_s0);

    play->unk_1EE3 = 3;
    B_80804560_jp = 300;
    B_80804562_jp = 300;
}

void func_80802D9C_jp(PlayState* play) {
    func_80802BB8_jp(play);
    if (play->unk_1EE2 == 3) {
        func_8008366C_jp(&B_80804480_jp);
        play->unk_1EE2 = 0;
        SetGameFrame(3);
    }
}

void func_80802DF0_jp(PlayState* play) {
    STOP_GAMESTATE(&play->state);
    SET_NEXT_GAMESTATE(&play->state, famicom_emu_init, sizeof(FamicomEmuState));
}

void func_80802E10_jp(PlayState* play) {
    STOP_GAMESTATE(&play->state);
    SET_NEXT_GAMESTATE(&play->state, trademark_init, sizeof(TrademarkState));
}

void func_80802E34_jp(PlayState* play) {
    game_goto_next_game_play(&play->state);
    common_data.unk_10004 = common_data.unk_00014;
    common_data.unk_00014 = play->unk_1E18;
}

void func_80802E74_jp(PlayState* play) {
    UNUSED s32 pad[2];
    s16 sp26 = 0;
    s32 sp20 = 1;
    PlayState_Unk_1EE8* sp18 = &play->unk_1EE8;

    if (play->unk_1EE8.unk_21C.unk_20(sp18, play) != 0) {
        if ((play->unk_1EE0 != 1) && (play->unk_1EE0 != 11)) {
            if (B_80804562_jp != 0) {
                B_80804562_jp--;
            }

            if ((func_800D2334_jp(sp18, play) == 0) && (B_80804562_jp != 0)) {
                sp20 = 0;
            } else {
                func_800D2568_jp(1);
            }
        }

        if (play->unk_1EE0 == 11) {
            func_800D2568_jp(2);
        }

        if (sp20 == 1) {
            switch (play->unk_1EE0) {
                case 1:
                    func_80802D9C_jp(play);
                    break;

                case 3:
                    if (1) {}
                    if (1) {}
                    func_80802DF0_jp(play);
                    break;

                case 4:
                case 6:
                    if (B_80804560_jp == 300) {
                        func_8005DDE4_jp(0x168, play);
                    }

                case 5:
                case 10:
                    if (B_80804560_jp != 0) {
                        B_80804560_jp--;
                    }

                    if ((func_800D2314_jp() == 1) || (B_80804560_jp == 0)) {
                        func_80802E10_jp(play);
                    } else {
                        sp26 = 1;
                    }
                    break;

                case 8:
                    if (common_data.unk_100E4 != NULL) {
                        if (*common_data.unk_100E4 != NULL) {
                            (*common_data.unk_100E4)(play);
                            func_80802E34_jp(play);
                        }
                    }
                    break;

                case 9:
                    if (B_80804560_jp != 0) {
                        B_80804560_jp--;
                    }

                    if ((func_800D2314_jp() == 1) || (B_80804560_jp == 0)) {
                        func_80802E34_jp(play);
                    } else {
                        sp26 = 1;
                    }
                    break;

                default:
                    func_80802E34_jp(play);
                    break;
            }

            if (sp26 == 0) {
                play->unk_1EE0 = 0;
            }
        }
    } else {
        sp18->unk_21C.unk_08(sp18, game_GameFrame);
    }
}

void func_808030D0_jp(PlayState* play) {
    if ((play->unk_1EE3 == 0) && (play->unk_1EE0 != 0)) {
        play->unk_1EE3 = 1;
    }
    D_808043A8_jp[play->unk_1EE3](play);
}

Gfx* func_80803124_jp(PlayState* play, Gfx* gfx) {
    return func_800BD37C_jp(gfx, play->unk_1C60.fogColor.r, play->unk_1C60.fogColor.g, play->unk_1C60.fogColor.b, 0,
                            play->unk_1C60.fogNear, play->unk_1C60.zFar);
}

void func_80803174_jp(PlayState* play) {
    UNUSED s32 pad;
    GraphicsContext* gfxCtx = play->state.gfxCtx;

    switch (play->unk_1EE2) {
        case 2:
            if (func_800836F8_jp(&B_80804480_jp, 10, 7, play) == 0) {
                play->unk_1EE2 = 0;
            } else {
                B_8080455C_jp = gfxCtx->unk_008;
                play->unk_1EE2 = 3;
                SetGameFrame(1);
            }
            break;
        case 3:
            func_80083BE4_jp(&B_80804480_jp);
            break;
    }
}

void play_cleanup(GameState* gameState) {
    PlayState* play = (PlayState*)gameState;

    func_800A3304_jp(play);
    play->state.gfxCtx->unk_2F4 = 0;
    play->state.gfxCtx->unk_2F8 = 0;
    play->unk_1CBC.unk_00 = 0;
    PreRender_cleanup(&play->unk_1DC0);
    func_80077640_jp(play, &play->unk_2138);

    if (play->unk_1EE2 == 3) {
        func_8008366C_jp(&B_80804480_jp);
        play->unk_1EE2 = 0;
    }

    if (play->unk_1EE3 == 3) {
        func_80802BB8_jp(play);
    }

    Actor_info_dt(&play->actorInfo, play);
    func_8007FB44_jp(&play->unk_1EBC);
    func_800AA124_jp();
    func_800C4D80_jp(&play->unk_1CBC);
    play->unk_1DAC = -1;
    func_800C4C60_jp(&play->unk_1CBC);
    func_800B1AA0_jp(play);
    func_80092C2C_jp(0, common_data.unk_10003);
    func_80087280_jp();
    zelda_CleanupArena();
}

void play_init(GameState* gameState) {
    PlayState* play = (PlayState*)gameState;
    GraphicsContext* sp48 = play->state.gfxCtx;
    u32 temp_v1;
    u32 temp_v0_2;
    UNUSED s32 pad[2];
    u8 temp;
    s32 sp30;

    if (play && play && play) {}

    game_resize_hyral(&play->state, 0x7D0000);
    func_800D2568_jp(0);
    func_80802B40_jp();
    func_800C9010_jp();
    mTM_set_season();
    func_800B594C_jp();
    func_800C49D4_jp(play);
    func_8007CFD8_jp(play);
    func_8007F858_jp(&play->unk_1EBC);
    initView(&play->unk_1938, sp48);
    func_80064F48_jp(play);
    func_80077620_jp(play, &play->unk_2138);
    func_8006BB64_jp();
    func_8006C8D0_jp();
    play->unk_1DAC = -1;
    func_80804288_jp(play, common_data.unk_00014);
    func_800C4D1C_jp(&play->unk_1CBC);
    play->unk_1CBC.unk_00 = 0;
    PreRender_init(&play->unk_1DC0);
    PreRender_setup_savebuf(&play->unk_1DC0, 0x140, 0xF0, 0, 0, 0);
    PreRender_setup_renderbuf(&play->unk_1DC0, 0x140, 0xF0, NULL, NULL);

    if (1) {}
    play->unk_1EE2 = 0;
    play->unk_1EE3 = 0;
    play->unk_1EE0 = 1;

    temp = 1;
    if (common_data.unk_1014B != 0xFF) {
        temp = common_data.unk_1014B;
        common_data.unk_1014B = 0xFF;
    }
    play->unk_1EE1 = temp;

    Pause_ct(&play->unk_1C70);
    new_Matrix(&play->state);
    play->state.main = func_8080407C_jp;
    play->state.destroy = play_cleanup;
    func_800844E0_jp(&play->unk_2128);
    func_800846D4_jp(&play->unk_2128, 7);
    func_800846E0_jp(&play->unk_2128, 0xA0A0A0FF);
    func_8008468C_jp(&play->unk_2128);
    play->unk_220C = 0;
    sp30 = THA_getFreeBytes(&play->state.heap);
    temp_v0_2 = (u32)THA_alloc16(&play->state.heap, sp30);
    temp_v1 = ALIGN16(temp_v0_2);
    zelda_InitArena((void*)(temp_v1 & 0xFFFFFFFF), (sp30 - temp_v1) + temp_v0_2);
    func_800C2EE0_jp();
    func_80087004_jp();
    Actor_info_ct(play, &play->actorInfo, play->unk_1EA8);
    play->unk_2208 = none_proc1;
    func_800A32D0_jp(play);
    func_8007F8DC_jp(&play->unk_1EBC);
    func_800C8E50_jp(play);
    func_800928C0_jp(play);
    func_800A65C4_jp();
    func_80059BF0_jp();
    func_800CBF80_jp();
    func_80802B64_jp();
}

void func_80803544_jp(PlayState* play) {
    UNUSED s32 pad[2];

    play->state.unk_9D = 0x8F;
    play->state.unk_9C = 1;
    func_800C4E58_jp(play);
    if (play->unk_1CBC.unk_0C == 0) {
        play->state.unk_9C = 2;
        func_8007CFB4_jp(play);
        play->state.unk_9C = 3;
        func_8007F988_jp(&play->unk_1EBC);
    }
    play->state.unk_9C = 4;
    func_8007CDB8_jp();
    play->state.unk_9C = 5;
    func_800C5F64_jp(play->unk_0110);
    play->state.unk_9C = 6;
    func_800C5328_jp(&play->unk_1CBC);
    if ((play->unk_1CBC.unk_0C == 0) && (REGADDR(IREG, 0x48) == 0)) {
        play->unk_1EA0++;
        play->state.unk_9C = 7;
        func_80078070_jp(play, &play->unk_2138);
        play->state.unk_9C = 8;
        func_80077650_jp(play, &play->unk_2138);
        play->state.unk_9D = 0x90;
        play->state.unk_9C = 0;
        Actor_info_call_actor(play, &play->actorInfo);
        play->state.unk_9D = 0x91;
        play->state.unk_9C = 1;
        func_8006C740_jp();
        play->state.unk_9C = 2;
        func_800A339C_jp(play);
    }
    func_8008450C_jp(&play->unk_2128, game_GameFrame);
}

void func_8080367C_jp(PlayState* play) {
    s32 var_v1;

    play->state.unk_9D = 0x8D;
    play->state.unk_9C = 1;
    func_80802AE0_jp();
    B_801458B0_jp = (void*)VIRTUAL_TO_PHYSICAL(play->unk_0110[0].unk_04);
    B_801458A0_jp[2] = (void*)VIRTUAL_TO_PHYSICAL(play->unk_010C);
    play->state.unk_9C = 2;

    if (zurumode_flag >= 2) {
        var_v1 = Pause_proc(&play->unk_1C70, &play->state.input[1]) == 0;
    } else {
        var_v1 = 0;
    }

    play->state.unk_9D = 0x8E;
    play->state.unk_9C = 0;

    if (var_v1 == 0) {
        play->state.unk_9C = 1;
        func_808030D0_jp(play);
        play->state.unk_9C = 2;
        func_80803174_jp(play);
        play->state.unk_9C = 3;
        if (play->unk_1EE2 != 3) {
            func_80803544_jp(play);
        }
    }

    if (play->unk_1CBC.unk_0C == 0) {
        play->state.unk_9D = 0x92;
        play->state.unk_9C = 1;
        func_80802B8C_jp(play);
        play->state.unk_9C = 2;
        func_800B7624_jp(play);
        play->state.unk_9C = 3;
        func_800CA008_jp(play);
        play->state.unk_9C = 4;
        func_800928E8_jp(play);
    }

    play->state.unk_9D = 0x93;
    play->state.unk_9C = 1;
    func_800984CC_jp(play, &play->kankyo, &play->unk_1C60);
    play->state.unk_9C = 2;
    func_80098B50_jp();
    play->state.unk_9C = 3;
    func_800CBFBC_jp(play);
    play->state.unk_9C = 4;
    func_80059C24_jp(play);
    play->state.unk_9C = 5;
    func_800C8FB8_jp(play);
    play->state.unk_9D = 0x95;
    play->state.unk_9C = 0;
}

void func_80803810_jp(PlayState* play, GraphicsContext* gfxCtx) {
    void* temp_v0 = play->unk_0110[0].unk_04;

    B_801458A0_jp[4] = (void*)VIRTUAL_TO_PHYSICAL(temp_v0);
    B_801458A0_jp[2] = (void*)VIRTUAL_TO_PHYSICAL(play->unk_010C);

    OPEN_DISPS(gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x00, NULL);
    gSPSegment(POLY_XLU_DISP++, 0x00, NULL);
    gSPSegment(OVERLAY_DISP++, 0x00, NULL);
    gSPSegment(UNK_2B0_DISP++, 0x00, NULL);
    gSPSegment(UNK_2C0_DISP++, 0x00, NULL);
    gSPSegment(UNK_2D0_DISP++, 0x00, NULL);

    gSPSegment(POLY_OPA_DISP++, 0x04, temp_v0);
    gSPSegment(POLY_XLU_DISP++, 0x04, temp_v0);
    gSPSegment(OVERLAY_DISP++, 0x04, temp_v0);
    gSPSegment(UNK_2B0_DISP++, 0x04, temp_v0);
    gSPSegment(UNK_2C0_DISP++, 0x04, temp_v0);
    gSPSegment(UNK_2D0_DISP++, 0x04, temp_v0);

    gSPSegment(POLY_OPA_DISP++, 0x02, play->unk_010C);
    gSPSegment(POLY_XLU_DISP++, 0x02, play->unk_010C);
    gSPSegment(OVERLAY_DISP++, 0x02, play->unk_010C);
    gSPSegment(UNK_2B0_DISP++, 0x02, play->unk_010C);
    gSPSegment(UNK_2C0_DISP++, 0x02, play->unk_010C);
    gSPSegment(UNK_2D0_DISP++, 0x02, play->unk_010C);

    CLOSE_DISPS(gfxCtx);
}

void func_808039D0_jp(PlayState* play, GraphicsContext* __gfxCtx) {
    POLY_OPA_DISP = func_80803124_jp(play, POLY_OPA_DISP);
    POLY_XLU_DISP = func_80803124_jp(play, POLY_XLU_DISP);
}

void func_80803A18_jp(PlayState* play) {
    showView(&play->unk_1938, 0xF, play);
}

void func_80803A40_jp(PlayState* play, GraphicsContext* __gfxCtx, GraphicsContext* gfxCtx2) {
    Matrix_MtxtoMtxF(&play->unk_1938.unk_0A0, &play->unk_1E5C);
    Matrix_MtxtoMtxF(&play->unk_1938.unk_060, &play->unk_1E1C);
    Skin_Matrix_MulMatrix(&play->unk_1E1C, &play->unk_1E5C, &play->unk_1E1C);

    play->unk_1E5C.mf[0][3] = 0.0f;
    play->unk_1E5C.mf[1][3] = 0.0f;
    play->unk_1E5C.mf[2][3] = 0.0f;
    play->unk_1E5C.mf[3][0] = 0.0f;
    play->unk_1E5C.mf[3][1] = 0.0f;
    play->unk_1E5C.mf[3][2] = 0.0f;

    Matrix_reverse(&play->unk_1E5C);

    play->unk_1E9C = _MtxF_to_Mtx(&play->unk_1E5C, (Mtx*)GRAPH_ALLOC(gfxCtx2, sizeof(MtxF) * 1));

    gSPSegment(POLY_OPA_DISP++, 0x01, play->unk_1E9C);
}

s32 func_80803B08_jp(PlayState* play, GraphicsContext* __gfxCtx, GraphicsContext* gfxCtx2) {
    {
        Gfx* sp194;
        Gfx* sp190;
        sp190 = POLY_OPA_DISP;
        sp194 = gfxopen(sp190);

        gSPDisplayList(OVERLAY_DISP++, sp194);

        if (play->unk_1EE3 == 3) {
            PlayState1938 sp60;
            ScissorViewArg1 sp50;

            initView(&sp60, gfxCtx2);
            {
                sp60.unk_120 = 10;
            label2:;
            }
            sp50.unk_04 = 0xF0, sp50.unk_0C = 0x140;
            sp50.unk_00 = 0;
            sp50.unk_08 = 0;
            setScissorView(&sp60, &sp50);
            showView1(&sp60, 0xF, &sp194);
            play->unk_1EE8.unk_21C.unk_0C(&play->unk_1EE8, &sp194);
        }

        func_800845EC_jp(&play->unk_2128, &sp194);
        func_800BDF90_jp(&sp194, play->unk_220C);

        gSPEndDisplayList(sp194++);

        gfxclose(sp190, sp194);
        POLY_OPA_DISP = sp194;
    }

    if (play->unk_1EE2 == 3) {
        Gfx* sp48 = POLY_OPA_DISP;

        func_80083984_jp(&B_80804480_jp, &sp48);
        POLY_OPA_DISP = sp48;
        return 1;
    }

    PreRender_setup_renderbuf(&play->unk_1DC0, 0x140, 0xF0, gfxCtx2->unk_2E4, gfxCtx2->unk_008);
    if (play->unk_1CBC.unk_00 == 2) {
        func_800B0010_jp();
        PreRender_ConvertFrameBuffer_fg(&play->unk_1DC0);
        play->unk_1CBC.unk_00 = 3;
    } else if (play->unk_1CBC.unk_00 >= 5) {
        play->unk_1CBC.unk_00 = 0;
    }

    if (play->unk_1CBC.unk_00 == 3) {
        Gfx* sp44 = POLY_OPA_DISP;

        PreRender_loadFrameBufferCopy(&play->unk_1DC0, &sp44);
        POLY_OPA_DISP = sp44;
        return 1;
    }

    {
        LightsN* sp40 = Global_light_read(&play->unk_1C60, gfxCtx2);

        func_8009B884_jp(sp40, play->unk_1C60.listHead, 0);
        LightsN_disp(sp40, gfxCtx2);
    }

    Actor_info_draw_actor(play, &play->actorInfo);
    func_80065028_jp(play);
    func_800A33D8_jp(play);
    Debug_Display_output(play);

    if ((play->unk_1CBC.unk_00 == 1) || (play->unk_1EE2 == 1)) {
        Gfx* sp3C;
        Gfx* sp38;

        sp38 = POLY_OPA_DISP;
        sp3C = gfxopen(sp38);

        gSPDisplayList(OVERLAY_DISP++, sp3C);

        play->unk_1DC0.fbuf = (u16*)gfxCtx2->unk_2E4;
        play->unk_1DC0.fbufSave = (u16*)gfxCtx2->unk_008;
        PreRender_saveFrameBuffer(&play->unk_1DC0, &sp3C);

        if (play->unk_1CBC.unk_00 == 1) {
            play->unk_1DC0.cvgSave = (u8*)gfxCtx2->unk_2E4;
            PreRender_saveCVG(&play->unk_1DC0, &sp3C);
            play->unk_1CBC.unk_00 = 2;
        } else {
            play->unk_1EE2 = 2;
        }

        gSPEndDisplayList(sp3C++);

        gfxclose(sp38, sp3C);
        POLY_OPA_DISP = sp3C;

        REGADDR(SREG, 0x21) |= 1;
        return 0;
    }
    return 1;
}

void func_80803E40_jp(GraphicsContext* __gfxCtx) {
    Gfx* temp_s0 = func_800BD720_jp(OVERLAY_DISP);
    gfxprint* printer = (gfxprint*)alloca(sizeof(gfxprint));

    gfxprint_init(printer);
    gfxprint_open(printer, temp_s0);
    gfxprint_color(printer, 255, 155, 255, 255);
    gfxprint_color(printer, 255, 255, 255, 255);
    if (temp_s0 && temp_s0 && temp_s0) {}
    gfxprint_locate8x8(printer, 7, 0x1A);
    gfxprint_printf(printer, "[Creator:%s]", &gBuildTeam);
    gfxprint_locate8x8(printer, 7, 0x1B);
    gfxprint_printf(printer, "[Date:%s]", &gBuildDate);
    temp_s0 = gfxprint_close(printer);
    gfxprint_cleanup(printer);
    OVERLAY_DISP = temp_s0;
}

void func_80803F48_jp(PlayState* play) {
    GraphicsContext* gfxCtx = play->state.gfxCtx;
    u8 sp2B = 0;
    u8 sp2A = 0;
    u8 sp29 = 0;

label:;
    func_80803810_jp(play, gfxCtx);
    if (common_data.unk_10001 == 0) {
        if (mEv_CheckTitleDemo() != -9) {
            sp2B = play->kankyo.unk_AE;
            sp2A = play->kankyo.unk_AF;
            sp29 = play->kankyo.unk_B0;
        }
    }

    DisplayList_initialize(gfxCtx, sp2B, sp2A, sp29, play);
    func_808039D0_jp(play, gfxCtx);
    func_80803A18_jp(play);
    func_80803A40_jp(play, gfxCtx, gfxCtx);

    if (1) {}
    if (1) {}
    if (1) {}
    if (1) {}

    if (func_80803B08_jp(play, gfxCtx, gfxCtx) == 1) {
        func_800CC3EC_jp(play);
        func_8005A2FC_jp(play);
        func_800C535C_jp(&play->unk_1CBC, play);
    }

    if (zurumode_flag != 0) {
        s32 temp_v0 = mEv_CheckTitleDemo();

        if ((temp_v0 == -9) || (temp_v0 == -1) || (temp_v0 != 0)) {
            func_80803E40_jp(gfxCtx);
        }
    }
}

void func_8080407C_jp(GameState* gameState) {
    PlayState* play = (PlayState*)gameState;

    play->state.unk_9D = 0x6E;
    play->state.unk_9C = 0;
    fqrand();
    play->state.unk_9D = 0x78;
    play->state.unk_9C = 0;
    mCon_main(&play->state);
    play->state.unk_9D = 0x82;
    play->state.unk_9C = 0;
    Debug_Display_init();
    play->state.unk_9D = 0x8C;
    play->state.unk_9C = 0;
    func_8080367C_jp(play);
    play->state.unk_9D = 0xAA;
    play->state.unk_9C = 0;
    func_80803F48_jp(play);
    play->state.unk_9D = 0xB4;
    play->state.unk_9C = 0;
    if (play->unk_1CBC.unk_00 != 2) {
        GraphicsContext* gfxCtx = play->state.gfxCtx;

        game_debug_draw_last(&play->state, gfxCtx);
        game_draw_last(gfxCtx);
        play->state.unk_9C = 0;
    }
    play->state.unk_9D = 0xBE;
}

void* func_80804138_jp(PlayState* play, D_8010EAA0* arg1) {
    u32 sp24 = arg1->unk_04 - arg1->unk_00;
    void* sp20 = THA_alloc16(&play->state.heap, sp24);

    func_80026E10_jp(sp20, arg1->unk_00, sp24, "../m_play.c", 2302);
    return sp20;
}

void func_808041A4_jp(PlayState* play) {
    func_80097108_jp(play, &play->kankyo);
}

void func_808041C4_jp(PlayState* play) {
    play->unk_1EA8 = NULL;
    play->unk_1EA5 = 0;
    play->unk_1EA6 = 0;
    play->unk_1EA7 = 0;
    play->unk_1EB8 = 0;
    func_800C65E4_jp(play, play->unk_0110);
    func_8009BA28_jp(&play->unk_1C60);
    func_800C6AC4_jp(&play->unk_1E10);
    common_data_clear();
    func_800C68C8_jp(play, play->unk_010C);
    func_800C6678_jp(play->unk_0110);
    func_808041A4_jp(play);
}

s32 func_80804240_jp(s32 arg0) {
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

void func_80804288_jp(PlayState* play, s16 arg1) {
    D_8010EAA0* sp1C = &D_8010EAA0_jp[arg1];

    sp1C->unk_13 = 0;
    play->unk_2210 = sp1C;
    play->unk_00E0 = arg1;
    play->unk_010C = func_80804138_jp(play, sp1C);
    sp1C->unk_13 = 0;
    B_801458A0_jp[2] = (void*)VIRTUAL_TO_PHYSICAL(play->unk_010C);
    func_808041C4_jp(play);
    func_800D236C_jp(func_80804240_jp(common_data.unk_00014));
}
