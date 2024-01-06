#ifndef _00743CD0_H
#define _00743CD0_H

#include "ultra64.h"
#include "game.h"
#include "m_view.h"
#include "unknown_structs.h"
#include "unk.h"

typedef struct Game__00743CD0 {
    /* 0x0000 */ Game state;
    /* 0x00E0 */ Game_Play1938 unk_00E0;
    /* 0x0208 */ UNK_TYPE1 unk_0208[0x2FC-0x208];
    /* 0x02FC */ ObjectExchangeBank unk_02FC;
} Game__00743CD0; // size = 0x1B20

void _00743CD0_init(Game *thisx);
void _00743CD0_cleanup(Game *thisx);

#endif
