#ifndef AC_RADIO_H
#define AC_RADIO_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Radio;

typedef void (*RadioActionFunc)(struct Radio*, struct Game_Play*);

typedef struct Radio {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x2A0 - 0x174];
    /* 0x2A0 */ RadioActionFunc unk_2A0;
    /* 0x174 */ UNK_TYPE1 unk_2A4[0x2B4 - 0x2A4];
    /* 0x2B4 */ s32 unk_2B4;
    /* 0x2B8 */ UNK_TYPE4 unk_2B8;
    /* 0x2BC */ UNK_TYPE1 unk_2BC[0x2D8 - 0x2BC];
} Radio; // size = 0x2D8

#endif
