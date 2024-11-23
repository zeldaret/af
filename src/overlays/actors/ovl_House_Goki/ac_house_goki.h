#ifndef AC_HOUSE_GOKI_H
#define AC_HOUSE_GOKI_H

#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct House_Goki;

typedef void (*House_GokiActionFunc)(struct House_Goki*, struct Game_Play*);

typedef struct House_Goki {
    /* 0x000 */ Actor actor;
    /* 0x174 */ House_GokiActionFunc process;
    /* 0x178 */ UNK_TYPE1 unk_1742[0x17C - 0x178];
    /* 0x17C */ s32 processIndex;
    /* 0x180 */ UNK_TYPE4 unk_180;
    /* 0x184 */ u32 unk_184;
    /* 0x188 */ s32 unk_188;
    /* 0x18C */ UNK_TYPE1 unk_18C[0x190 - 0x18C];
    /* 0x190 */ u32 unk_190;
    /* 0x194 */ UNK_TYPE1 unk_194;
    /* 0x195 */ s8 unk_195;
    /* 0x196 */ UNK_TYPE2 unk_196;
    /* 0x198 */ f32 unk_198;
} House_Goki; // size = 0x19C

#endif
