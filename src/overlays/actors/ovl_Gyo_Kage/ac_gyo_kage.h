#ifndef AC_GYO_KAGE_H
#define AC_GYO_KAGE_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Gyo_Kage;

typedef void (*Gyo_KageActionFunc)(struct Gyo_Kage*, struct Game_Play*);

typedef struct Gyo_Kage {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x38];
} Gyo_Kage; // size = 0x1AC

#endif
