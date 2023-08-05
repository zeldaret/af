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
#include "code_variables.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "overlays/gamestates/ovl_famicom_emu/famicom_emu.h"

extern struct_80145020_jp B_80145020_jp;
extern GameState* gamePT;

extern u8 B_80145048_jp;

extern f32 B_FLT_8014504C_jp;
extern f32 B_FLT_80145050_jp;
extern f32 B_FLT_80145054_jp;

extern s32 D_8010FD60_jp;

void func_800D2E00_jp(GameState* gameState) {
    if (D_8010FD60_jp >= 2) {
        Debug_mode_input(CONTROLLER2(gameState));
    }

    if (debug_mode->unk_0D4 != 0) {
        func_800D88E0_jp(&B_80145020_jp);
    }
}

const u16 RO_80117CE0_jp[] = {
    0xFFC1,
    0xFFC1,
    0xFFC1,
    0xFFC1,
    0x7BDF,
    0x7BDF,
    0x07FF,
    0xF83F,
    0x7BDF,
    0x7BDF,
    0x7BDF,
    0x7BDF,
    0xF801,
    0x7BDF,
    0x07C1,
    0x003F,
};

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/game/func_800D2E58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/game/game_debug_draw_last.s")

#if 0
void game_draw_first(GraphicsContext* gfxCtx) {
    s32 temp_v0;
    void* temp_t0;
    void* temp_t0_10;
    void* temp_t0_11;
    void* temp_t0_12;
    void* temp_t0_13;
    void* temp_t0_14;
    void* temp_t0_15;
    void* temp_t0_16;
    void* temp_t0_17;
    void* temp_t0_18;
    void* temp_t0_2;
    void* temp_t0_3;
    void* temp_t0_4;
    void* temp_t0_5;
    void* temp_t0_6;
    void* temp_t0_7;
    void* temp_t0_8;
    void* temp_t0_9;

    temp_v0 = gfxCtx->unk_8;
    temp_t0 = gfxCtx->polyOpa.tha.head;
    gfxCtx->polyOpa.tha.head = temp_t0 + 8;
    temp_t0->unk_4 = 0;
    temp_t0->unk_0 = 0xDB060000;
    temp_t0_2 = gfxCtx->polyOpa.tha.head;
    gfxCtx->polyOpa.tha.head = temp_t0_2 + 8;
    temp_t0_2->unk_0 = 0xDB06003C;
    temp_t0_2->unk_4 = (s32) gfxCtx->unk_2E4;
    temp_t0_3 = gfxCtx->polyOpa.tha.head;
    gfxCtx->polyOpa.tha.head = temp_t0_3 + 8;
    temp_t0_3->unk_4 = temp_v0;
    temp_t0_3->unk_0 = 0xDB060038;
    temp_t0_4 = gfxCtx->polyXlu.tha.head;
    gfxCtx->polyXlu.tha.head = temp_t0_4 + 8;
    temp_t0_4->unk_4 = 0;
    temp_t0_4->unk_0 = 0xDB060000;
    temp_t0_5 = gfxCtx->polyXlu.tha.head;
    gfxCtx->polyXlu.tha.head = temp_t0_5 + 8;
    temp_t0_5->unk_0 = 0xDB06003C;
    temp_t0_5->unk_4 = (s32) gfxCtx->unk_2E4;
    temp_t0_6 = gfxCtx->polyXlu.tha.head;
    gfxCtx->polyXlu.tha.head = temp_t0_6 + 8;
    temp_t0_6->unk_4 = temp_v0;
    temp_t0_6->unk_0 = 0xDB060038;
    temp_t0_7 = gfxCtx->unk_288;
    gfxCtx->unk_288 = (void* ) (temp_t0_7 + 8);
    temp_t0_7->unk_4 = 0;
    temp_t0_7->unk_0 = 0xDB060000;
    temp_t0_8 = gfxCtx->unk_288;
    gfxCtx->unk_288 = (void* ) (temp_t0_8 + 8);
    temp_t0_8->unk_0 = 0xDB06003C;
    temp_t0_8->unk_4 = (s32) gfxCtx->unk_2E4;
    temp_t0_9 = gfxCtx->unk_288;
    gfxCtx->unk_288 = (void* ) (temp_t0_9 + 8);
    temp_t0_9->unk_4 = temp_v0;
    temp_t0_9->unk_0 = 0xDB060038;
    temp_t0_10 = gfxCtx->unk_2B8;
    gfxCtx->unk_2B8 = (void* ) (temp_t0_10 + 8);
    temp_t0_10->unk_4 = 0;
    temp_t0_10->unk_0 = 0xDB060000;
    temp_t0_11 = gfxCtx->unk_2B8;
    gfxCtx->unk_2B8 = (void* ) (temp_t0_11 + 8);
    temp_t0_11->unk_0 = 0xDB06003C;
    temp_t0_11->unk_4 = (s32) gfxCtx->unk_2E4;
    temp_t0_12 = gfxCtx->unk_2B8;
    gfxCtx->unk_2B8 = (void* ) (temp_t0_12 + 8);
    temp_t0_12->unk_4 = temp_v0;
    temp_t0_12->unk_0 = 0xDB060038;
    temp_t0_13 = gfxCtx->unk_2C8;
    gfxCtx->unk_2C8 = (void* ) (temp_t0_13 + 8);
    temp_t0_13->unk_4 = 0;
    temp_t0_13->unk_0 = 0xDB060000;
    temp_t0_14 = gfxCtx->unk_2C8;
    gfxCtx->unk_2C8 = (void* ) (temp_t0_14 + 8);
    temp_t0_14->unk_0 = 0xDB06003C;
    temp_t0_14->unk_4 = (s32) gfxCtx->unk_2E4;
    temp_t0_15 = gfxCtx->unk_2C8;
    gfxCtx->unk_2C8 = (void* ) (temp_t0_15 + 8);
    temp_t0_15->unk_4 = temp_v0;
    temp_t0_15->unk_0 = 0xDB060038;
    temp_t0_16 = gfxCtx->unk_2D8;
    gfxCtx->unk_2D8 = (void* ) (temp_t0_16 + 8);
    temp_t0_16->unk_4 = 0;
    temp_t0_16->unk_0 = 0xDB060000;
    temp_t0_17 = gfxCtx->unk_2D8;
    gfxCtx->unk_2D8 = (void* ) (temp_t0_17 + 8);
    temp_t0_17->unk_0 = 0xDB06003C;
    temp_t0_17->unk_4 = (s32) gfxCtx->unk_2E4;
    temp_t0_18 = gfxCtx->unk_2D8;
    gfxCtx->unk_2D8 = (void* ) (temp_t0_18 + 8);
    temp_t0_18->unk_4 = temp_v0;
    temp_t0_18->unk_0 = 0xDB060038;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/game/game_draw_first.s")
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/game/game_draw_last.s")

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
