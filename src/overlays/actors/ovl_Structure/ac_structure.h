#ifndef AC_STRUCTURE_H
#define AC_STRUCTURE_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Structure;

typedef void (*StructureActionFunc)(struct Structure*, struct PlayState*);

typedef struct Structure {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x8];
} Structure; // size = 0x17C

#endif
