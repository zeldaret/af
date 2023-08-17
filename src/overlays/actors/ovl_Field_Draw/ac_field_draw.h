#ifndef AC_FIELD_DRAW_H
#define AC_FIELD_DRAW_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Field_Draw;

typedef void (*Field_DrawActionFunc)(struct Field_Draw*, struct Game_Play*);

typedef struct Field_Draw {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x70];
} Field_Draw; // size = 0x1E4

#endif
