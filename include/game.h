#ifndef GAME_H
#define GAME_H

#include "ultra64.h"
#include "TwoHeadArena.h"
#include "other_types.h"
#include "unk.h"

struct GraphicsContext;


typedef void (*GameStateFunc)(struct GameState* gameState);

typedef struct {
    /* 0x00 */ void*         loadedRamAddr;
    /* 0x04 */ RomOffset     vromStart;
    /* 0x08 */ RomOffset     vromEnd;
    /* 0x0C */ void*         vramStart;
    /* 0x10 */ void*         vramEnd;
    /* 0x14 */ UNK_PTR       unk_14;
    /* 0x18 */ GameStateFunc init;    // initializes and executes the given context
    /* 0x1C */ GameStateFunc destroy; // deconstructs the context, and sets the next context to load
    /* 0x20 */ UNK_PTR       unk_20;
    /* 0x24 */ UNK_PTR       unk_24;
    /* 0x28 */ UNK_TYPE      unk_28;
    /* 0x2C */ size_t        instanceSize;
} GameStateOverlay; // size = 0x30

typedef struct GameState {
    /* 0x00 */ struct GraphicsContext* gfxCtx;
    /* 0x04 */ UNK_TYPE1 unk_04[0x74];
    /* 0x78 */ TwoHeadArena heap;
    /* 0x88 */ UNK_TYPE1 unk_88[0x1C];
} GameState; // size >= 0xA4

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
// void game_dt();
// void game_get_next_game_init();
// void game_get_next_game_class_size();
// void game_is_doing();
// void game_getFreeBytes();
// void game_goto_next_game_play();
// void game_goto_next_game_name_famicom_emu();

#endif
