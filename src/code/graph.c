#include "global.h"

#include "gfx.h"

#include "6FB340.h"
#include "fault.h"
#include "game.h"
#include "getcurrentms.h"
#include "m_DLF.h"

#include "overlays/gamestates/ovl_first_game/first_game.h"
#include "overlays/gamestates/ovl_select/m_select.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "overlays/gamestates/ovl_second_game/second_game.h"
#include "overlays/gamestates/ovl_cpedit/m_cpedit.h"
#include "overlays/gamestates/ovl_trademark/m_trademark.h"
#include "overlays/gamestates/ovl_player_select/player_select.h"
#include "overlays/gamestates/ovl_save_menu/save_menu.h"
#include "overlays/gamestates/ovl_famicom_emu/famicom_emu.h"
#include "overlays/gamestates/ovl_prenmi/m_prenmi.h"


#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/graph/func_800D38E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/graph/graph_setup_double_buffer.s")

GameStateOverlay* game_get_next_game_dlftbl(Game* game) {
    GameStateFunc init = game_get_next_game_init(game);;

    if (init == first_game_init) {
        return &game_dlftbls[0];
    }
    if (init == select_init) {
        return &game_dlftbls[1];
    }
    if (init == play_init) {
        return &game_dlftbls[2];
    }
    if (init == second_game_init) {
        return &game_dlftbls[3];
    }
    if (init == cpedit_init) {
        return &game_dlftbls[4];
    }
    if (init == trademark_init) {
        return &game_dlftbls[5];
    }
    if (init == player_select_init) {
        return &game_dlftbls[6];
    }
    if (init == save_menu_init) {
        return &game_dlftbls[7];
    }
    if (init == famicom_emu_init) {
        return &game_dlftbls[8];
    }
    if (init == prenmi_init) {
        return &game_dlftbls[9];
    }

    return NULL;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/graph/func_800D3C94_jp.s")

void graph_ct(GraphicsContext* gfxCtx);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/graph/graph_ct.s")

void graph_dt(GraphicsContext* gfxCtx);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/graph/graph_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/graph/func_800D3E14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/graph/func_800D3E40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/graph/graph_task_set00.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/graph/graph_draw_finish.s")

void graph_main(GraphicsContext* gfxCtx, Game* game);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/graph/graph_main.s")

void graph_proc(UNUSED void* arg) {
    s32 state;
    GameStateOverlay* nextOvl = &game_dlftbls[0];
    GameStateOverlay* ovl;
    size_t size;
    Game* game;
    char msg[80];

    graph_ct(&graph_class);

    while (nextOvl != NULL) {
        ovl = nextOvl;

        Overlay_LoadGameState(ovl);

        state = 2;
        size = ovl->instanceSize;
        game = malloc(size);
        game_class_p = game;
        if (game == NULL) {
            sprintf(msg, "CLASS SIZE= %d bytes", size);
            fault_AddHungupAndCrashImpl("GAME CLASS MALLOC FAILED", msg);
        }
        bzero(game, size);
        graph_class.unk_2F0 = state;

        state = 3;
        game_ct(game, ovl->init, &graph_class);
        graph_class.unk_2F0 = state;

        state = 0x12;
        while (game_is_doing(game)) {
            graph_main(&graph_class, game);
            B_80145FF8_jp = GetCurrentMilliseconds();
        }
        nextOvl = game_get_next_game_dlftbl(game);
        graph_class.unk_2F0 = state;

        state = 0x13;
        func_800D79F4_jp();
        graph_class.unk_2F0 = state;

        state = 0x14;
        game_dt(game);
        graph_class.unk_2F0 = state;

        free(game);
        game_class_p = NULL;
        Overlay_FreeGameState(ovl);
    }

    graph_dt(&graph_class);
}
