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
    /* 0x00218 */ UNK_TYPE unk_00218;
    /* 0x0021C */ UNK_TYPE1 unk_0021C[0x40];
    /* 0x0025C */ UNK_TYPE unk_0025C;
    /* 0x00260 */ UNK_TYPE1 unk_00260[0x25800];
    /* 0x25A60 */ u32 unk_25A60;
    /* 0x25A64 */ UNK_TYPE2 unk_25A64;
    /* 0x25A66 */ UNK_TYPE2 unk_25A66;
    /* 0x25A68 */ UNK_TYPE2 unk_25A68;
    /* 0x25A6A */ UNK_TYPE2 unk_25A6A;
    /* 0x25A6C */ UNK_TYPE2 unk_25A6C;
    /* 0x25A6E */ u8 unk_25A6E;
    /* 0x25A6F */ UNK_TYPE1 unk_25A6F;
    /* 0x25A70 */ u8 unk_25A70;
    /* 0x25A71 */ u8 unk_25A71;
    /* 0x25A72 */ UNK_TYPE1 unk_25A72[0x2];
    /* 0x25A74 */ UNK_TYPE1 unk_25A74[0x4];
} Game_Trademark; // size = 0x25A78

void trademark_init(Game *thisx);
void trademark_cleanup(Game *thisx);

#endif
