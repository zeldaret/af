#include "global.h"
#include "game.h"

extern UNK_TYPE B_80145020_jp;
extern UNK_PTR gamePT;

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

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/game/SetGameFrame.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/game/game_main.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/game/game_init_hyral.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/game/game_resize_hyral.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/game/game_ct.s")

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

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/game/game_get_next_game_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/game/game_get_next_game_class_size.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/game/game_is_doing.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/game/game_getFreeBytes.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/game/game_goto_next_game_play.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/game/game_goto_next_game_name_famicom_emu.s")
