#ifndef GAME_H
#define GAME_H

#include "ultra64.h"
#include "TwoHeadArena.h"
#include "gamealloc.h"
#include "unk.h"

struct GameState;
struct GraphicsContext;


typedef void (*GameStateFunc)(struct GameState* gameState);

typedef struct GameState {
    /* 0x00 */ struct GraphicsContext* gfxCtx;
    /* 0x04 */ UNK_TYPE unk_04;
    /* 0x08 */ GameStateFunc destroy;
    /* 0x0C */ UNK_TYPE unk_0C;
    /* 0x10 */ UNK_TYPE unk_10;
    /* 0x14 */ UNK_TYPE1 unk_14[0x60];
    /* 0x74 */ u32 unk_74;
    /* 0x78 */ TwoHeadArena heap;
    /* 0x88 */ GameAlloc alloc;
    /* 0x9C */ UNK_TYPE1 unk_9C[0x3];
    /* 0x9F */ UNK_TYPE1 unk_9F;
    /* 0xA0 */ UNK_TYPE unk_A0;
} GameState; // size >= 0xA4

// void func_800D2E00_jp();
// void func_800D2E58_jp();
// void game_debug_draw_last();
// void game_draw_first();
// void game_draw_last();
// void game_get_controller();
void SetGameFrame(s32 divisor);
// void game_main();
void game_init_hyral(GameState* gameState, size_t size);
void game_resize_hyral(GameState* gameState, size_t size);
void game_ct(GameState* gameState, GameStateFunc init, struct GraphicsContext* gfxCtx);
void game_dt(GameState* gameState);
// void game_get_next_game_init();
// void game_get_next_game_class_size();
// void game_is_doing();
// void game_getFreeBytes();
// void game_goto_next_game_play();
// void game_goto_next_game_name_famicom_emu();

#endif
