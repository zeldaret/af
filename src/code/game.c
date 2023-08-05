#include "game.h"
#include "gfx.h"
#include "m_controller.h"
#include "67E840.h"
#include "speed_meter.h"
#include "graph.h"
#include "debug.h"
#include "malloc.h"
#include "code_variables.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "overlays/gamestates/ovl_famicom_emu/famicom_emu.h"

extern struct_80145020_jp B_80145020_jp;
extern GameState* gamePT;

extern u8 B_80145048_jp;

extern f32 B_FLT_8014504C_jp;
extern f32 B_FLT_80145050_jp;
extern f32 B_FLT_80145054_jp;

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/game/func_800D2E00_jp.s")

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

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/game/game_draw_first.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/game/game_draw_last.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/game/game_get_controller.s")

void SetGameFrame(s32 divisor) {
    if (divisor != B_80145048_jp) {
        B_80145048_jp = divisor;
        B_FLT_8014504C_jp = (divisor & 0xFF);
        B_FLT_80145050_jp = B_FLT_8014504C_jp / 2.0f;
        B_FLT_80145054_jp = 1.0f / B_FLT_8014504C_jp;
        debug_mode->unk_110 = divisor;
    }
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/game/game_main.s")

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
    gameState->unk_04 = 0;

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
