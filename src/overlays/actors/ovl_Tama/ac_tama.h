#ifndef AC_TAMA_H
#define AC_TAMA_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"
#include "c_keyframe.h"
#include "overlays/actors/ovl_Structure/ac_structure.h"

struct Game_Play;
struct Tama;

typedef enum TamaProcess {
    TAM_PROCESS_WAIT,
} TamaProcess;

typedef void (*TamaActionFunc)(struct Tama*, struct Game_Play*);

typedef struct Tama {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x12C];
    /* 0x2A0 */ TamaActionFunc process;
    /* 0x2A4 */ UNK_TYPE1 unk_2A4[0x4];
    /* 0x2A8 */ s32 structureType;
    /* 0x2AC */ s32 structurePalette;
    /* 0x2B0 */ UNK_TYPE1 unk_2B0[0x4];
    /* 0x2B4 */ s32 type;
    /* 0x2B8 */ s32 processNum;
    /* 0x2BC */ UNK_TYPE1 unk_2BC[0x1C];
} Tama; // size = 0x2D8

#endif
