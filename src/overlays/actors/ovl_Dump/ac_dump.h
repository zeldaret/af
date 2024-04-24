#ifndef AC_DUMP_H
#define AC_DUMP_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Dump;

typedef enum DumpProcess {
    DUM_PROCESS_WAIT,
};

typedef void (*DumpActionFunc)(struct Dump*, struct Game_Play*);

typedef struct Dump {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x12C];
    /* 0x2A0 */ DumpActionFunc process;
    /* 0x2A4 */ UNK_TYPE1 unk_2A4[0x10];
    /* 0x2B4 */ s32 processNum;
    /* 0x2B8 */ UNK_TYPE1 unk_2B8[0x20];
} Dump; // size = 0x2D8

#endif
