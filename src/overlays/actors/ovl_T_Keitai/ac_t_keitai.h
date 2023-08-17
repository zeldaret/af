#ifndef AC_T_KEITAI_H
#define AC_T_KEITAI_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct T_Keitai;

typedef void (*T_KeitaiActionFunc)(struct T_Keitai*, struct PlayState*);

typedef struct T_Keitai {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x100];
} T_Keitai; // size = 0x274

#endif
