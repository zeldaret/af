#ifndef AC_BIRTH_CONTROL_H
#define AC_BIRTH_CONTROL_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Birth_Control;

typedef void (*Birth_ControlActionFunc)(struct Birth_Control*, struct Game_Play*);

typedef struct Birth_Control {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0xC];
} Birth_Control; // size = 0x180

#endif
