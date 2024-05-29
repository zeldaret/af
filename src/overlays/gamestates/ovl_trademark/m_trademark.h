#ifndef TRADEMARK_H
#define TRADEMARK_H

#include "ultra64.h"
#include "game.h"
#include "m_view.h"
#include "unk.h"

typedef struct Game_Trademark {
    /* 0x00000 */ Game state;
    /* 0x000E0 */ View view;
    /* 0x00208 */ f32 unk_00208;
    /* 0x0020C */ f32 unk_0020C;
    /* 0x00210 */ f32 unk_00210;
    /* 0x00214 */ f32 unk_00214;
    /* 0x00218 */ UNK_TYPE4 unk_00218; // unused
    /* 0x0021C */ UNK_TYPE1 unk_0021C[0x40]; // unused
    /* 0x0025C */ UNK_TYPE4 unk_0025C; // unused
    /* 0x00260 */ UNK_TYPE1 unk_00260[0x25800]; // unused
    /* 0x25A60 */ u32 fadeColor;
    /* 0x25A64 */ s16 unk_25A64; // timer?
    /* 0x25A66 */ s16 alpha;
    /* 0x25A68 */ s16 unk_25A68;
    /* 0x25A6A */ s16 unk_25A6A;
    /* 0x25A6C */ s16 unk_25A6C;
    /* 0x25A6E */ u8 curState;
    /* 0x25A6F */ u8 unk_25A6F;
    /* 0x25A70 */ u8 unk_25A70;
    /* 0x25A71 */ u8 unk_25A71;
} Game_Trademark; // size = 0x25A78

void trademark_init(Game *thisx);
void trademark_cleanup(Game *thisx);

#endif
