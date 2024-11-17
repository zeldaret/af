#ifndef AC_HANAMI_NPC0_H
#define AC_HANAMI_NPC0_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Hanami_Npc0;

typedef void (*Hanami_Npc0ActionFunc)(struct Hanami_Npc0*, struct Game_Play*);

typedef struct Hanami_Npc0 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x14];
    /* 0x188 */ UNK_TYPE unk_188;
    /* 0x18C */ UNK_TYPE1 unk_18C[0x59E];
    /* 0x72A */ UNK_TYPE1 unk_72A; // inferred from alignment
    /* 0x72B */ u8 unk_72B; // unsigned
    /* 0x72C */ UNK_TYPE1 unk_72C[0x78]; // unreferenced in actor file
    /* 0x7A4 */ UNK_PTR unk_7A4;
    /* 0x7A8 */ UNK_TYPE unk_7A8;
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
    /* 0x80C */ UNK_TYPE unk_80C;
    /* 0x810 */ UNK_TYPE1 unk_810[0x50]; // unreferenced in actor file
    /* 0x860 */ UNK_TYPE unk_860;
    /* 0x864 */ UNK_TYPE1 unk_864[0x48]; // unreferenced in actor file
    /* 0x8AC */ UNK_TYPE unk_8AC;
    /* 0x8B0 */ UNK_TYPE1 unk_8B0[0x2C]; // unreferenced in actor file
    /* 0x8DC */ UNK_TYPE2 unk_8DC;
    /* 0x8DE */ UNK_TYPE1 unk_8DE[0x32]; // unreferenced in actor file
    /* 0x910 */ UNK_TYPE1 unk_910; // inferred from alignment
    /* 0x911 */ UNK_TYPE1 unk_911;
    /* 0x912 */ UNK_TYPE1 unk_912[0x19]; // unreferenced in actor file
    /* 0x92B */ UNK_TYPE1 unk_92B;
    /* 0x92C */ UNK_TYPE2 unk_92C;
    /* 0x92E */ UNK_TYPE1 unk_92E[0xA];
    /* 0x938 */ UNK_TYPE unk_938;
    /* 0x93C */ UNK_TYPE unk_93C;
    /* 0x940 */ UNK_TYPE unk_940;
    /* 0x944 */ u8 unk_944; // unsigned
} Hanami_Npc0; // size = 0x948

#endif
