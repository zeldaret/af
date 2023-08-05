#ifndef SYS_ROMCHECK_H
#define SYS_ROMCHECK_H

#include "ultra64.h"
#include "game.h"
#include "unk.h"

typedef struct SysRomcheckState {
    /* 0x00 */ GameState state;
    /* 0xA4 */ UNK_TYPE1 unk_00[0x1B20-0xA4];
} SysRomcheckState; // size = 0x1B20

void sys_romcheck_init(GameState *thisx);
void sys_romcheck_cleanup(GameState *thisx);

#endif
