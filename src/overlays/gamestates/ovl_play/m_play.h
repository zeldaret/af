#ifndef M_PLAY_H
#define M_PLAY_H

#include "ultra64.h"
#include "game.h"
#include "m_actor.h"
#include "unk.h"

struct Actor;
struct ActorEntry;
struct PlayState;

typedef UNK_RET (*PlayState_unk_2208)(struct Actor*, struct PlayState*);

typedef struct PlayState {
    /* 0x0000 */ GameState state;
    /* 0x00A4 */ UNK_TYPE1 unk_00A4[0x6C];
    /* 0x0110 */ UNK_TYPE unk_0110;
    /* 0x0114 */ UNK_TYPE1 unk_0114[0x1B64];
    /* 0x1C78 */ ActorInfo actorInfo;
    /* 0x1CBC */ UNK_TYPE1 unk_1CBC[0x160];
    /* 0x1E1C */ MtxF unk_1E1C; // viewProjectionMtxF
    /* 0x1E5C */ MtxF unk_1E5C; // billboardMtxF
    /* 0x1E9C */ UNK_TYPE1 unk_1E9C[0x8];
    /* 0x1EA4 */ UNK_TYPE1 unk_1EA4[0x1];
    /* 0x1EA5 */ u8 unk_1EA5;
    /* 0x1EA6 */ u8 unk_1EA6;
    /* 0x1EA7 */ UNK_TYPE1 unk_1EA7[0x1];
    /* 0x1EA8 */ UNK_TYPE1 unk_1EA8[0x4];
    /* 0x1EAC */ struct ActorEntry *unk_1EAC;
    /* 0x1EB0 */ s16 *unk_1EB0;
    /* 0x1EB4 */ UNK_TYPE1 unk_1EB4[0x354];
    /* 0x2208 */ PlayState_unk_2208 unk_2208;
    /* 0x220C */ UNK_TYPE1 unk_220C[0x204];
} PlayState; // size = 0x2410

void play_init(GameState *thisx);
void play_cleanup(GameState *thisx);

#endif
