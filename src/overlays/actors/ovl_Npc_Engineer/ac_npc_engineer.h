#ifndef AC_NPC_ENGINEER_H
#define AC_NPC_ENGINEER_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Npc_Engineer;

typedef void (*Npc_EngineerActionFunc)(struct Npc_Engineer*, struct Game_Play*);

typedef struct Npc_Engineer {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x64C];
    /* 0x7C0 */ u32 unk7C0;
    /* 0x7C4 */ UNK_TYPE1 unk_7C4[0x10];
    /* 0x7D4 */ u8 unk7D4;
    /* 0x7D5 */ u8 unk7D5;
    /* 0x7D6 */ u8 unk7D6;
    /* 0x174 */ UNK_TYPE1 unk_7D7[0x26];
    /* 0x7FD */ u8 unk7FD;
    /* 0x174 */ UNK_TYPE1 unk_7FE[0xE];
    /* 0x80C */ u32 unk80C;
    /* 0x174 */ UNK_TYPE1 unk_810[0x9C];
    /* 0x8AC */ s32 unk8AC;
    /* 0x174 */ UNK_TYPE1 unk_8B0[0x2C];
    /* 0x8DC */ s16 unk8DC;
    /* 0x8DE */ UNK_TYPE1 unk_8DE[0x5A];
} Npc_Engineer; // size = 0x938

#endif
