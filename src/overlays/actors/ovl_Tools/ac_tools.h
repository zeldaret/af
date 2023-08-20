#ifndef AC_TOOLS_H
#define AC_TOOLS_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Tools;

typedef void (*ToolsActionFunc)(struct Tools*, struct Game_Play*);

typedef struct Tools {
    /* 0x000 */ Actor actor;
} Tools; // size = 0x174

#endif
