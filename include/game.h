#ifndef GAME_H
#define GAME_H

#include "ultra64.h"
#include "TwoHeadArena.h"

struct GameState;
struct GraphicsContext;


typedef void (*GameStateFunc)(struct GameState* gameState);

typedef struct GameAlloc {
    /* 0x00 */ UNK_TYPE1 unk_00[UNK_SIZE];
} GameAlloc; // size >= 0

typedef struct GameState {
    /* 0x00 */ struct GraphicsContext* gfxCtx;
    /* 0x04 */ UNK_TYPE1 unk_04[0x4];
    /* 0x08 */ GameStateFunc destroy;
    /* 0x0C */ UNK_TYPE1 unk_0C[0x6C];
    /* 0x78 */ TwoHeadArena heap;
    /* 0x88 */ GameAlloc alloc;
} GameState; // size >= 0x88

// void func_800D2E00_jp();
// void func_800D2E58_jp();
// void game_debug_draw_last();
// void game_draw_first();
// void game_draw_last();
// void game_get_controller();
// void SetGameFrame();
// void game_main();
// void game_init_hyral();
// void game_resize_hyral();
// void game_ct();
void game_dt(GameState* gameState);
// void game_get_next_game_init();
// void game_get_next_game_class_size();
// void game_is_doing();
// void game_getFreeBytes();
// void game_goto_next_game_play();
// void game_goto_next_game_name_famicom_emu();

#endif
