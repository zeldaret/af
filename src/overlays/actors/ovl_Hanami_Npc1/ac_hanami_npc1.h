#ifndef AC_HANAMI_NPC1_H
#define AC_HANAMI_NPC1_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Hanami_Npc1;

typedef void (*Hanami_Npc1ActionFunc)(struct Hanami_Npc1*, struct Game_Play*);
typedef void (*Hanami_Npc1_unk_93C)(struct Actor*); // verify type signature

typedef struct Hanami_Npc1 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x630]; // unreferenced in actor file
    /* 0x7A4 */ UNK_PTR unk_7A4; // TODO: make typedef
    /* 0x7A8 */ UNK_TYPE4 unk_7A8;
    /* 0x7AC */ UNK_TYPE1 unk_7AC[0x14]; // unreferenced in actor file
    /* 0x7C0 */ UNK_PTR unk_7C0;
    /* 0x7C4 */ UNK_TYPE1 unk_7C4; // inferred from alignment
    /* 0x7C5 */ u8 unk_7C5; // unsigned
    /* 0x7C6 */ u8 unk_7C6; // unsigned
    /* 0x7C7 */ UNK_TYPE1 unk_7C7; // inferred from alignment (could be auto padding)
    /* 0x7C8 */ UNK_TYPE1 unk_7C8; // inferred from alignment
    /* 0x7C9 */ UNK_TYPE1 unk_7C9;
    /* 0x7CA */ UNK_TYPE1 unk_7CA[6]; // unreferenced in actor file
    /* 0x7D0 */ UNK_PTR unk_7D0;
    /* 0x7D4 */ UNK_TYPE1 unk_7D4;
    /* 0x7D5 */ UNK_TYPE1 unk_7D5;
    /* 0x7D6 */ UNK_TYPE1 unk_7D6;
    /* 0x7D7 */ UNK_TYPE1 unk_7D7; // inferred from alignment (could be auto padding)
    /* 0x7D8 */ UNK_TYPE1 unk_7D8[0x24]; // unreferenced in actor file
    /* 0x7FC */ UNK_TYPE1 unk_7FC; // inferred from alignment
    /* 0x7FD */ UNK_TYPE1 unk_7FD;
    /* 0x7FE */ UNK_TYPE1 unk_7FE[0xE]; // unreferenced in actor file
    /* 0x80C */ UNK_TYPE4 unk_80C;
    /* 0x810 */ UNK_TYPE1 unk_810[0x9C]; // unreferenced in actor file
    /* 0x8AC */ UNK_TYPE4 unk_8AC;
    /* 0x8B0 */ f32 unk_8B0;
    /* 0x8B4 */ f32 unk_8B4;
    /* 0x8B8 */ f32 unk_8B8;
    /* 0x8BC */ UNK_TYPE1 unk_8BC[0x10]; // unreferenced in actor file
    /* 0x8CC */ UNK_TYPE2 unk_8CC;
    /* 0X8D0 */ UNK_TYPE1 unk_8D0[0x4]; // unreferenced in actor file
    /* 0x8DC */ UNK_TYPE2 unk_8DC;
    /* 0x8DE */ UNK_TYPE1 unk_8DE[0x32]; // unreferenced in actor file
    /* 0x910 */ u8 unk_910;
    /* 0x911 */ UNK_TYPE1 unk_911[0x27];  // unreferenced in actor file
    /* 0x938 */ UNK_TYPE4 unk_938;
    /* 0x93C */ Hanami_Npc1_unk_93C unk_93C;
    /* 0x940 */ UNK_TYPE4 unk_940;
} Hanami_Npc1; // size = 0x944

#endif
