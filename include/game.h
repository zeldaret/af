#ifndef GAME_H
#define GAME_H

#include "ultra64.h"
#include "TwoHeadArena.h"
#include "gamealloc.h"
#include "padutils.h"
#include "unk.h"

struct GameState;
struct GraphicsContext;
struct struct_80145020_jp;


typedef void (*GameStateFunc)(struct GameState* gameState);

typedef struct GameState {
    /* 0x00 */ struct GraphicsContext* gfxCtx;
    /* 0x04 */ GameStateFunc main;
    /* 0x08 */ GameStateFunc destroy;
    /* 0x0C */ GameStateFunc init;
    /* 0x10 */ size_t size;
    /* 0x14 */ Input input[MAXCONTROLLERS];
    /* 0x74 */ s32 unk_74;
    /* 0x78 */ TwoHeadArena heap;
    /* 0x88 */ GameAlloc alloc;
    /* 0x9C */ UNK_TYPE1 unk_9C[0x3];
    /* 0x9F */ u8 running;
    /* 0xA0 */ s32 unk_A0;
} GameState; // size >= 0xA4

void func_800D2E00_jp(GameState* gameState);
void func_800D2E58_jp(u16 arg0, Gfx **gfxP);
void game_debug_draw_last(GameState* gameState, struct GraphicsContext* gfxCtx);
void game_draw_first(struct GraphicsContext* gfxCtx);
void game_draw_last(struct GraphicsContext* gfxCtx);
void game_get_controller(GameState* gameState);
void SetGameFrame(s32 divisor);
void game_main(GameState* gameState);
void game_init_hyral(GameState* gameState, size_t size);
void game_resize_hyral(GameState* gameState, size_t size);
void game_ct(GameState* gameState, GameStateFunc init, struct GraphicsContext* gfxCtx);
void game_dt(GameState* gameState);
GameStateFunc game_get_next_game_init(GameState* gameState);
size_t game_get_next_game_class_size(GameState* gameState);
s32 game_is_doing(GameState* gameState);
s32 game_getFreeBytes(GameState* gameState);
void game_goto_next_game_play(GameState* gameState);
void game_goto_next_game_name_famicom_emu(GameState* gameState);


// .data

extern GameState* gamePT;

// .bss

extern struct struct_80145020_jp B_80145020_jp;
extern s16 B_80145040_jp;
extern UNK_TYPE4 B_80145044_jp;
extern u8 B_80145048_jp;
extern f32 B_FLT_8014504C_jp;
extern f32 B_FLT_80145050_jp;
extern f32 B_FLT_80145054_jp;


#define CONTROLLER1(gameState) (&(gameState)->input[0])
#define CONTROLLER2(gameState) (&(gameState)->input[1])
#define CONTROLLER3(gameState) (&(gameState)->input[2])
#define CONTROLLER4(gameState) (&(gameState)->input[3])

#define STOP_GAMESTATE(curState)     \
    do {                             \
        GameState* state = curState; \
                                     \
        state->running = false;      \
    } while(0)

#define SET_NEXT_GAMESTATE(curState, nextInit, nextSize) \
    do {                                                 \
        GameState* state = curState;                     \
                                                         \
        (state)->init = nextInit;                        \
        (state)->size = nextSize;                        \
    } while (0)


#endif
