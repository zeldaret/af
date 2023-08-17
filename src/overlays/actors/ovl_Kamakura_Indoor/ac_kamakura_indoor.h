#ifndef AC_KAMAKURA_INDOOR_H
#define AC_KAMAKURA_INDOOR_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Kamakura_Indoor;

typedef void (*Kamakura_IndoorActionFunc)(struct Kamakura_Indoor*, struct Game_Play*);

typedef struct Kamakura_Indoor {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x8C];
} Kamakura_Indoor; // size = 0x200

#endif
