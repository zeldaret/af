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

extern struct_80145020_jp B_80145020_jp;
extern GameState* gamePT;

extern u8 B_80145048_jp;

extern f32 B_FLT_8014504C_jp;
extern f32 B_FLT_80145050_jp;
extern f32 B_FLT_80145054_jp;

extern s32 zurumode_flag;

extern s16 B_80145040_jp;

void func_800D2E00_jp(GameState* gameState) {
    if (zurumode_flag >= 2) {
        Debug_mode_input(CONTROLLER2(gameState));
    }

    if (debug_mode->unk_0D4 != 0) {
        func_800D88E0_jp(&B_80145020_jp);
    }
}

const u16 RO_80117CE0_jp[0x10] = {
    GPACK_RGBA5551(255, 255, 0, 1), // R_CBUTTONS
    GPACK_RGBA5551(255, 255, 0, 1), // L_CBUTTONS
    GPACK_RGBA5551(255, 255, 0, 1), // D_CBUTTONS
    GPACK_RGBA5551(255, 255, 0, 1), // U_CBUTTONS
    GPACK_RGBA5551(127, 127, 127, 1), // R_TRIG
    GPACK_RGBA5551(127, 127, 127, 1), // L_TRIG
    GPACK_RGBA5551(0, 255, 255, 1),
    GPACK_RGBA5551(255, 0, 255, 1),
    GPACK_RGBA5551(127, 127, 127, 1), // R_JPAD
    GPACK_RGBA5551(127, 127, 127, 1), // L_JPAD
    GPACK_RGBA5551(127, 127, 127, 1), // D_JPAD
    GPACK_RGBA5551(127, 127, 127, 1), // U_JPAD
    GPACK_RGBA5551(255, 0, 0, 1), // START_BUTTON
    GPACK_RGBA5551(127, 127, 127, 1), // Z_TRIG
    GPACK_RGBA5551(0, 255, 0, 1), // B_BUTTON
    GPACK_RGBA5551(0, 0, 255, 1), // A_BUTTON
};

#ifdef NON_EQUIVALENT
void func_800D2E58_jp(u16 button, Gfx** gfxP) {
    Gfx* gfx; // var_s0
    s32 var_s1;
    s32 var_v0;

    gfx = *gfxP;

    gDPPipeSync(gfx++);
    gDPSetOtherMode(gfx++, G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_CONV | G_TF_POINT | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_NONE | G_CYC_FILL | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PIXEL | G_RM_NOOP | G_RM_NOOP2);

    for (var_v0 = 0, var_s1 = 1; var_s1 < 0x10; var_v0 = var_s1++) {
        if (button & (1 << var_v0)) {
            gDPSetFillColor(gfx++, RO_80117CE0_jp[var_v0] | (RO_80117CE0_jp[var_v0] << 0x10));

            gfx = func_800BE12C_jp(gfx, (var_v0 * 4) + 0xE2, 0xDC, (var_s1 * 4) + 0xE2, 0xE0);

            gDPPipeSync(gfx++);
        }
    }

    *gfxP = gfx;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/game/func_800D2E58_jp.s")
#endif

#ifdef NON_MATCHING
void game_debug_draw_last(GameState* gameState, GraphicsContext* gfxCtx) {
    Gfx* sp3C;
    Gfx* temp_a0; // sp38

    if (zurumode_flag != 0) {
        OPEN_DISPS(gfxCtx);

        temp_a0 = POLY_OPA_DISP;
        sp3C = gfxopen(temp_a0);

        gSPDisplayList(OVERLAY_DISP++, sp3C);

        B_80145040_jp = gameState->input[0].press.button | gameState->input[0].cur.button;

        func_800D2E58_jp(B_80145040_jp, &sp3C);

        gSPEndDisplayList(sp3C++);

        gfxclose(temp_a0, sp3C);
        POLY_OPA_DISP = sp3C;

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
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/game/game_debug_draw_last.s")
#endif

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
    Gfx* temp_a1;
    Gfx* temp_a3;

    OPEN_DISPS(gfxCtx);
    temp_a1 = gfxopen(temp_a3 = POLY_OPA_DISP);

    gSPDisplayList(OVERLAY_DISP++, temp_a1);
    gSPEndDisplayList(temp_a1++);

    gfxclose(temp_a3, temp_a1);
    POLY_OPA_DISP = temp_a1;

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
    if (divisor != B_80145048_jp) {
        B_80145048_jp = divisor;
        B_FLT_8014504C_jp = (divisor & 0xFF);
        B_FLT_80145050_jp = B_FLT_8014504C_jp / 2.0f;
        B_FLT_80145054_jp = 1.0f / B_FLT_8014504C_jp;
        debug_mode->unk_110 = divisor;
    }
}

void game_main(GameState* gameState) {
    GraphicsContext* gfxCtx = gameState->gfxCtx;
    u8 temp = B_80145048_jp;

    if (debug_mode->unk_110 != temp) {
        SetGameFrame(debug_mode->unk_110);
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
    GameAlloc *alloc = &gameState->alloc;
    void* gameArena;
    size_t maxFree;
    size_t bytesFree;
    size_t bytesAllocated;
    void* heapStart = gameState->heap.start;

    THA_dt(&gameState->heap);

    gamealloc_free(alloc, heapStart);

    // TODO: This seems like it was wrongly named
    DisplayArena(&maxFree, &bytesFree, &bytesAllocated);
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

    THA_ct(&gameState->heap, NULL, 0U);
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
