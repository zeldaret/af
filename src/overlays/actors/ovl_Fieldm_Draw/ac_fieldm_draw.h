#ifndef AC_FIELDM_DRAW_H
#define AC_FIELDM_DRAW_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Fieldm_Draw;

typedef void (*Fieldm_DrawActionFunc)(struct Fieldm_Draw*, struct Game_Play*);

typedef struct Fieldm_Draw {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x10];
} Fieldm_Draw; // size = 0x184

#endif
