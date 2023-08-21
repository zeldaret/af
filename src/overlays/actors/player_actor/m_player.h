#ifndef M_PLAYER_H
#define M_PLAYER_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Player;

typedef struct Player {
    /* 0x0000 */ Actor actor;
    /* 0x0174 */ UNK_TYPE1 unk_0174[0xC38];
    /* 0x0DAC */ UNK_TYPE unk_0DAC;
    /* 0x0DB0 */ UNK_TYPE unk_0DB0;
    /* 0x0DB4 */ UNK_TYPE1 unk_0DB4[0x8];
    /* 0x0DBC */ UNK_TYPE unk_0DBC[2];
    /* 0x0DC4 */ UNK_TYPE1 unk_0DC4[0x18];
    /* 0x0DDC */ UNK_TYPE unk_0DDC[2];
    /* 0x0DE4 */ UNK_TYPE unk_0DE4[2];
    /* 0x0DEC */ UNK_TYPE1 unk_0DEC[0x4CC];
    /* 0x12B8 */ UNK_TYPE unk_12B8;
    /* 0x12BC */ s32 unk_12BC;
    /* 0x12C0 */ u16 unk_12C0;
    /* 0x12C2 */ UNK_TYPE1 unk_12C2[0x2];
    /* 0x12C4 */ UNK_TYPE1 unk_12C4[0x14];
} Player; // size = 0x12D8

#endif
