#ifndef AC_TUNAHIKI_CONTROL_H
#define AC_TUNAHIKI_CONTROL_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Tunahiki_Control;

typedef void (*Tunahiki_ControlActionFunc)(struct Tunahiki_Control*, struct PlayState*);

typedef struct Tunahiki_Control {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x8];
} Tunahiki_Control; // size = 0x17C

#endif
