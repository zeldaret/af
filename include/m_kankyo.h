#ifndef M_KANKYO_H
#define M_KANKYO_H

#include "ultra64.h"
#include "unk.h"

struct Actor;

typedef void (*Kankyo_unk_C0)(struct Actor*);

typedef struct Kankyo {
    /* 0x00 */ UNK_TYPE1 unk_00[0xC0];
    /* 0xC0 */ Kankyo_unk_C0 unk_C0;
    /* 0xC4 */ UNK_TYPE1 unk_C4[0x4];
} Kankyo; // size = 0xC8

#endif
