#ifndef AC_DUMP_H
#define AC_DUMP_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Dump;

typedef void (*DumpActionFunc)(struct Dump*, struct Game_Play*);

typedef struct Dump {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} Dump; // size = 0x2D8

#endif
