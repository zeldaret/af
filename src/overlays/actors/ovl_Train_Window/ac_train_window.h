#ifndef AC_TRAIN_WINDOW_H
#define AC_TRAIN_WINDOW_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game;

typedef s32 (*TrainWindowType)(Actor*, struct Game*);

typedef struct Train_Window{
    /* 0x000 */ Actor actor;
    /* 0x174 */ TrainWindowType drawType;
    /* 0x178 */ s16 paletteId;
    /* 0x17C */ UNK_TYPE unk17C; 
    /* 0x180 */ u16* currentPalette;
    /* 0x184 */ u32 singleScrollX;
    /* 0x188 */ u32 singleScrollY;
    /* 0x18C */ u32 twoScrollX1;
    /* 0x190 */ u32 twoScrollY1;
    /* 0x194 */ u32 twoScrollX2;
    /* 0x198 */ u32 twoScrollY2;
    /* 0x19C */ s32 treeScrollX;
    /* 0x1A0 */ s32 treeScrollY;
    /* 0x1A4 */ f32 xluAlpha;
    /* 0x1A8 */ f32 scrollSpeed;
    /* 0x1AC */ s_xyz pos;
    /* 0x1B0 */ UNK_TYPE unk_1B0;
}Train_Window; // size = 0x1B4

#endif
