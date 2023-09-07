#ifndef AC_KAGO_H
#define AC_KAGO_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Kago;

typedef void (*KagoActionFunc)(struct Kago*, struct Game_Play*);

typedef struct Kago {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} Kago; // size = 0x2D8

#endif
