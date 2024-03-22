#ifndef GAME_H
#define GAME_H

#include "ultra64.h"
#include "libc/stdbool.h"
#include "TwoHeadArena.h"
#include "other_types.h"
#include "gamealloc.h"
#include "libu64/pad.h"
#include "m_controller.h"
#include "unk.h"

struct Game;
struct GraphicsContext;
struct struct_80145020_jp;


#define DEFINE_GAMESTATE_INTERNAL(typeName, enumName) enumName,
#define DEFINE_GAMESTATE(typeName, enumName, name) DEFINE_GAMESTATE_INTERNAL(typeName, enumName)

typedef enum GameStateId {
#include "tables/gamestate_table.h"
    /* 0x0A */ GAMESTATE_ID_MAX
} GameStateId;

#undef DEFINE_GAMESTATE
#undef DEFINE_GAMESTATE_INTERNAL


typedef void (*GameStateFunc)(struct Game* game);

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

typedef struct Game {
    /* 0x00 */ struct GraphicsContext* gfxCtx;
    /* 0x04 */ GameStateFunc main;
    /* 0x08 */ GameStateFunc destroy;
    /* 0x0C */ GameStateFunc init;
    /* 0x10 */ size_t size;
    /* 0x14 */ Input input[MAXCONTROLLERS];
    /* 0x74 */ s32 unk_74;
    /* 0x78 */ TwoHeadArena heap;
    /* 0x88 */ GameAlloc alloc;
    /* 0x9C */ u8 unk_9C;
    /* 0x9D */ u8 unk_9D;
    /* 0x9E */ UNK_TYPE1 unk9E[0x1];
    /* 0x9F */ u8 running;
    /* 0xA0 */ s32 frameCounter;
    /* 0xA4 */ UNK_TYPE1 unk_A4[0x4];
    /* 0xA8 */ Controller controller;
} Game; // size = 0xE0

void func_800D2E00_jp(Game* game);
void func_800D2E58_jp(u16 button, Gfx** gfxP);
void game_debug_draw_last(Game* game, struct GraphicsContext* gfxCtx);
void game_draw_first(struct GraphicsContext* gfxCtx);
void game_draw_last(struct GraphicsContext* gfxCtx);
void game_get_controller(Game* game);
void SetGameFrame(s32 divisor);
void game_main(Game* game);
void game_init_hyral(Game* game, size_t size);
void game_resize_hyral(Game* game, size_t size);
void game_ct(Game* game, GameStateFunc init, struct GraphicsContext* gfxCtx);
void game_dt(Game* game);
GameStateFunc game_get_next_game_init(Game* game);
size_t game_get_next_game_class_size(Game* game);
s32 game_is_doing(Game* game);
s32 game_getFreeBytes(Game* game);
void game_goto_next_game_play(Game* game);
void game_goto_next_game_name_famicom_emu(Game* game);


// .data

extern Game* gamePT;

// .bss

extern struct struct_80145020_jp B_80145020_jp;
extern s16 B_80145040_jp;
extern Game* game_class_p;
extern u8 game_GameFrame;
extern f32 game_GameFrameF;
extern f32 game_GameFrame_2F;
extern f32 game_GameFrame__1F;


// m_game_dlftbls

extern GameStateOverlay game_dlftbls[GAMESTATE_ID_MAX];
extern GameStateId game_dlftbls_num;


#define CONTROLLER1(game) (&(game)->input[0])
#define CONTROLLER2(game) (&(game)->input[1])
#define CONTROLLER3(game) (&(game)->input[2])
#define CONTROLLER4(game) (&(game)->input[3])

#define STOP_GAMESTATE(curState)     \
    do {                             \
        Game* state = curState; \
                                     \
        state->running = false;      \
    } while(0)

#define SET_NEXT_GAMESTATE(curState, nextInit, nextSize) \
    do {                                                 \
        Game* state = curState;                     \
                                                         \
        (state)->init = nextInit;                        \
        (state)->size = nextSize;                        \
    } while (0)


#endif
