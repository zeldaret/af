#ifndef AC_MBG_H
#define AC_MBG_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Mbg;

typedef void (*MbgActionFunc)(struct Mbg*, struct Game_Play*);

typedef struct Mbg {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x28];
    /* 0x19C */ s32 unk_19C;
    /* 0x1A0 */ xyz_t unk_1A0;
    /* 0x1AC */ f32 unk_1AC;
} Mbg; // size = 0x1B0

#endif
