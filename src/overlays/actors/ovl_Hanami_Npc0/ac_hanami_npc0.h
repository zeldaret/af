#ifndef AC_HANAMI_NPC0_H
#define AC_HANAMI_NPC0_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Hanami_Npc0;

typedef void (*Hanami_Npc0ActionFunc)(struct Hanami_Npc0*, struct Game_Play*);

typedef struct Hanami_Npc0 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x64C];
    /* 0x7C0 */ UNK_PTR unk7C0;
    /* 0x7C4 */ UNK_TYPE1 unk_7C4[0x184];
} Hanami_Npc0; // size = 0x948

#endif
