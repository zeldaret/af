#ifndef AC_TRAIN_WINDOW_H
#define AC_TRAIN_WINDOW_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Train_Window;

typedef void (*Train_WindowActionFunc)(struct Train_Window*, struct Game_Play*);

typedef struct Train_Window {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x40];
} Train_Window; // size = 0x1B4

#endif
