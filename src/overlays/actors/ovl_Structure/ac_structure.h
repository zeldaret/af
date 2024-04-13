#ifndef AC_STRUCTURE_H
#define AC_STRUCTURE_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Structure;

typedef void (*StructureActionFunc)(struct Structure*, struct Game_Play*);

typedef struct StructureActor {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x13C];
    /* 0x2B0 */ s32 unk_2B0;
    /* 0x2B4 */ UNK_TYPE1 unk_2B4[0x24];
} StructureActor; // size = 0x2D8

typedef struct Structure {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x4];
    /* 0x178 */ u16 unk_178;
    /* 0x17A */ u8 unk_17A;
    /* 0x17B */ UNK_TYPE1 unk_17B;
} Structure; // size = 0x17C

#endif
