#include "game.h"
#include "gfx.h"
#include "m_controller.h"
#include "67E840.h"
#include "speed_meter.h"
#include "graph.h"
#include "debug.h"
#include "malloc.h"
#include "6EDD10.h"
#include "padmgr.h"
#include "69E2C0.h"
#include "gfxalloc.h"
#include "6E0F50.h"
#include "code_variables.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "overlays/gamestates/ovl_famicom_emu/famicom_emu.h"
#include "macros.h"

GameState* gamePT = NULL;

struct_80145020_jp B_80145020_jp;
s16 B_80145040_jp;
GameState* game_class_p;
u8 game_GameFrame;
f32 game_GameFrameF;
f32 game_GameFrame_2F;
f32 game_GameFrame__1F;

void func_800D2E00_jp(GameState* gameState) {
    if (zurumode_flag >= 2) {
        Debug_mode_input(CONTROLLER2(gameState));
    }

    if (debug_mode->unk_0D4 != 0) {
        func_800D88E0_jp(&B_80145020_jp);
    }
}

const u16 RO_80117CE0_jp[0x10] = {
    GPACK_RGBA5551(255, 255, 0, 1),   // R_CBUTTONS
    GPACK_RGBA5551(255, 255, 0, 1),   // L_CBUTTONS
    GPACK_RGBA5551(255, 255, 0, 1),   // D_CBUTTONS
    GPACK_RGBA5551(255, 255, 0, 1),   // U_CBUTTONS
    GPACK_RGBA5551(127, 127, 127, 1), // R_TRIG
    GPACK_RGBA5551(127, 127, 127, 1), // L_TRIG
    GPACK_RGBA5551(0, 255, 255, 1),   //
    GPACK_RGBA5551(255, 0, 255, 1),   //
    GPACK_RGBA5551(127, 127, 127, 1), // R_JPAD
    GPACK_RGBA5551(127, 127, 127, 1), // L_JPAD
    GPACK_RGBA5551(127, 127, 127, 1), // D_JPAD
    GPACK_RGBA5551(127, 127, 127, 1), // U_JPAD
    GPACK_RGBA5551(255, 0, 0, 1),     // START_BUTTON
    GPACK_RGBA5551(127, 127, 127, 1), // Z_TRIG
    GPACK_RGBA5551(0, 255, 0, 1),     // B_BUTTON
    GPACK_RGBA5551(0, 0, 255, 1),     // A_BUTTON
};

void func_800D2E58_jp(u16 button, Gfx** gfxP) {
    Gfx* gfx;
    u32 i;
    u32 j;

    gfx = *gfxP;

    gDPPipeSync(gfx++);
    gDPSetOtherMode(gfx++,
                    G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_CONV | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                        G_TD_CLAMP | G_TP_NONE | G_CYC_FILL | G_PM_NPRIMITIVE,
                    G_AC_NONE | G_ZS_PIXEL | G_RM_NOOP | G_RM_NOOP2);

    for (i = 0; i < ARRAY_COUNT(RO_80117CE0_jp); i++) {
        if (button & (1 << i)) {
            j = i + 1;
            gDPSetFillColor(gfx++, (RO_80117CE0_jp[i] << 0x10) | RO_80117CE0_jp[i]);
            gfx = func_800BE12C_jp(gfx, (i * 4) + 226, 220, (j * 4) + 226, 224);

            gDPPipeSync(gfx++);
        }
    }

    *gfxP = gfx;
}

void game_debug_draw_last(GameState* gameState, GraphicsContext* gfxCtx) {
    Gfx* gfx;
    Gfx* gfxHead;

    if (zurumode_flag != 0) {
        OPEN_DISPS(gfxCtx);

        {
            UNUSED s32 requiredScopeTemp;

            gfxHead = POLY_OPA_DISP;
            gfx = gfxopen(gfxHead);

            gSPDisplayList(OVERLAY_DISP++, gfx);
        }

        B_80145040_jp = gameState->input[0].press.button | gameState->input[0].cur.button;

        func_800D2E58_jp(B_80145040_jp, &gfx);

        gSPEndDisplayList(gfx++);

        gfxclose(gfxHead, gfx);
        POLY_OPA_DISP = gfx;

        CLOSE_DISPS(gfxCtx);
    }

    if (zurumode_flag != 0) {
        Debug_mode_output(gfxCtx);
    }

    if (debug_mode->unk_0D4 != 0) {
        func_800D8A54_jp(&B_80145020_jp, gfxCtx);
        func_800D9018_jp(&B_80145020_jp, gfxCtx, gameState);
    }
}

void game_draw_first(GraphicsContext* gfxCtx) {
    void* temp_v0 = gfxCtx->unk_008;

    OPEN_DISPS(gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x00, NULL);
    gSPSegment(POLY_OPA_DISP++, 0x0F, gfxCtx->unk_2E4);
    gSPSegment(POLY_OPA_DISP++, 0x0E, temp_v0);

    gSPSegment(POLY_XLU_DISP++, 0x00, NULL);
    gSPSegment(POLY_XLU_DISP++, 0x0F, gfxCtx->unk_2E4);
    gSPSegment(POLY_XLU_DISP++, 0x0E, temp_v0);

    gSPSegment(OVERLAY_DISP++, 0x00, NULL);
    gSPSegment(OVERLAY_DISP++, 0x0F, gfxCtx->unk_2E4);
    gSPSegment(OVERLAY_DISP++, 0x0E, temp_v0);

    gSPSegment(UNK_2B0_DISP++, 0x00, NULL);
    gSPSegment(UNK_2B0_DISP++, 0x0F, gfxCtx->unk_2E4);
    gSPSegment(UNK_2B0_DISP++, 0x0E, temp_v0);

    gSPSegment(UNK_2C0_DISP++, 0x00, NULL);
    gSPSegment(UNK_2C0_DISP++, 0x0F, gfxCtx->unk_2E4);
    gSPSegment(UNK_2C0_DISP++, 0x0E, temp_v0);

    gSPSegment(UNK_2D0_DISP++, 0x00, NULL);
    gSPSegment(UNK_2D0_DISP++, 0x0F, gfxCtx->unk_2E4);
    gSPSegment(UNK_2D0_DISP++, 0x0E, temp_v0);

    CLOSE_DISPS(gfxCtx);
}

void game_draw_last(GraphicsContext* gfxCtx) {
    Gfx* gfx;
    Gfx* gfxHead;

    OPEN_DISPS(gfxCtx);

    gfx = gfxopen(gfxHead = POLY_OPA_DISP);

    gSPDisplayList(OVERLAY_DISP++, gfx);
    gSPEndDisplayList(gfx++);

    gfxclose(gfxHead, gfx);
    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(gfxCtx);
}

void game_get_controller(GameState* gameState) {
    if (gameState->unk_74 == 1) {
        padmgr_RequestPadData(gameState->input, 1);
    } else {
        padmgr_ClearPadData(gameState->input);
    }
}

void SetGameFrame(s32 divisor) {
    if (divisor != game_GameFrame) {
        game_GameFrame = divisor;
        game_GameFrameF = (divisor & 0xFF);
        game_GameFrame_2F = game_GameFrameF / 2.0f;
        game_GameFrame__1F = 1.0f / game_GameFrameF;
        debug_mode->gameframe = divisor;
    }
}

void game_main(GameState* gameState) {
    GraphicsContext* gfxCtx = gameState->gfxCtx;
    u8 gameframe = game_GameFrame;

    if (debug_mode->gameframe != gameframe) {
        SetGameFrame(debug_mode->gameframe);
    }

    game_draw_first(gfxCtx);
    gfxCtx->unk_2F0 = 5;
    mTM_time();
    gfxCtx->unk_2F0 = 7;

    gameState->main(gameState);

    gfxCtx->unk_2F0 = 9;
    mBGM_main(gameState);
    gfxCtx->unk_2F0 = 0xA;
    func_800D2E00_jp(gameState);

    gameState->unk_A0++;
}

void game_init_hyral(GameState* gameState, size_t size) {
    void* buf = gamealloc_malloc(&gameState->alloc, size);

    if (buf != NULL) {
        THA_ct(&gameState->heap, buf, size);
        return;
    }

    THA_ct(&gameState->heap, NULL, 0);
    _dbg_hungup("../game.c", 462);
}

void game_resize_hyral(GameState* gameState, size_t size) {
    GameAlloc* alloc = &gameState->alloc;
    void* gameArena;
    size_t maxFree;
    size_t bytesFree;
    size_t bytesAllocated;
    void* heapStart = gameState->heap.start;

    THA_dt(&gameState->heap);

    gamealloc_free(alloc, heapStart);

    GetFreeArena(&maxFree, &bytesFree, &bytesAllocated);
    if (size == 0x7D0000) {
        size = maxFree - sizeof(GameAllocEntry);
    } else {
        size = (maxFree - sizeof(GameAllocEntry) < size) ? maxFree - sizeof(GameAllocEntry) : size;
    }

    gameArena = gamealloc_malloc(alloc, size);
    if (gameArena != NULL) {
        THA_ct(&gameState->heap, gameArena, size);
        return;
    }

    THA_ct(&gameState->heap, NULL, 0);
    _dbg_hungup("../game.c", 508);
}

void game_ct(GameState* gameState, GameStateFunc init, GraphicsContext* gfxCtx) {
    gamePT = gameState;

    gfxCtx->unk_2F2 = 1;
    gfxCtx->unk_25C = &osViModeNtscLan1;
    gfxCtx->unk_2EC = 0x42;
    gfxCtx->unk_2FC = 1.0f;
    gfxCtx->unk_300 = 1.0f;

    mCon_ct(gameState);

    gameState->unk_A0 = 0;
    gameState->main = NULL;
    gameState->destroy = NULL;
    gameState->running = true;
    gameState->unk_74 = 1;

    {
        s32 requiredScopeTemp UNUSED;

        gameState->gfxCtx = gfxCtx;
        gameState->init = NULL;
        gameState->size = 0;
    }

    gamealloc_init(&gameState->alloc);

    game_init_hyral(gameState, 0x100000); // 1 MiB
    SetGameFrame(2);

    init(gameState);

    func_8005F020_jp();
    func_800D88B0_jp(&B_80145020_jp);
    func_800D3E14_jp(gameState->gfxCtx);
}

void game_dt(GameState* gameState) {
    mCon_dt(gameState);
    func_800D3E40_jp(gameState->gfxCtx);
    mBGM_cleanup();

    if (gameState->destroy != NULL) {
        gameState->destroy(gameState);
    }

    func_800D88D4_jp(&B_80145020_jp);
    THA_dt(&gameState->heap);
    gamealloc_cleanup(&gameState->alloc);
    gamePT = NULL;
}

GameStateFunc game_get_next_game_init(GameState* gameState) {
    return gameState->init;
}

size_t game_get_next_game_class_size(GameState* gameState) {
    return gameState->size;
}

s32 game_is_doing(GameState* gameState) {
    return gameState->running;
}

s32 game_getFreeBytes(GameState* gameState) {
    return THA_getFreeBytes(&gameState->heap);
}

void game_goto_next_game_play(GameState* gameState) {
    STOP_GAMESTATE(gameState);
    SET_NEXT_GAMESTATE(gameState, play_init, sizeof(PlayState));
}

void game_goto_next_game_name_famicom_emu(GameState* gameState) {
    STOP_GAMESTATE(gameState);
    SET_NEXT_GAMESTATE(gameState, famicom_emu_init, sizeof(FamicomEmuState));
}
