#ifndef M_PLAY_H
#define M_PLAY_H

#include "ultra64.h"
#include "game.h"
#include "m_actor.h"
#include "m_kankyo.h"
#include "m_lights.h"
#include "z64math.h"
#include "unknown_structs.h"
#include "unk.h"

struct Actor;
struct ActorEntry;
struct PlayState;

typedef void (*PlayState_unk_1C58)(struct Actor*);
typedef UNK_RET (*PlayState_unk_2208)(struct Actor*, struct PlayState*);

typedef struct PlayState {
    /* 0x0000 */ GameState state;
    /* 0x00E0 */ s16 unk_00E0;
    /* 0x00E2 */ UNK_TYPE1 unk_00E2[0x2];
    /* 0x00E4 */ s8 unk_00E4;
    /* 0x00E5 */ s8 unk_00E5;
    /* 0x00E6 */ UNK_TYPE1 unk_00E6[0x2];
    /* 0x00E8 */ UNK_TYPE1 unk_00E8[0x28];
    /* 0x0110 */ PlayState_unk_0110 unk_0110[UNK_SIZE];
    /* 0x0164 */ UNK_TYPE1 unk_0164[0x17A8];
    /* 0x190C */ s32 unk_190C;
    /* 0x1910 */ UNK_TYPE1 unk_1910[0x50];
    /* 0x1960 */ Vec3f unk_1960;
    /* 0x196C */ UNK_TYPE1 unk_196C[0x22C];
    /* 0x1B98 */ Kankyo kankyo;
    /* 0x1C60 */ LightContext lightCtx;
    /* 0x1C64 */ UNK_TYPE1 unk_1C64[0x14];
    /* 0x1C78 */ ActorInfo actorInfo;
    /* 0x1CBC */ UNK_TYPE1 unk_1CBC[0x160];
    /* 0x1E1C */ MtxF viewProjectionMtxF;
    /* 0x1E5C */ MtxF billboardMtxF;
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
