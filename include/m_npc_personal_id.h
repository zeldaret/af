#ifndef M_NPC_DEF_H
#define M_NPC_DEF_H

#include "ultra64.h"
#include "m_land.h"

typedef enum NPCLooks {
    /* 0 */ NPC_LOOKS_GIRL,
    /* 1 */ NPC_LOOKS_KO_GIRL,
    /* 2 */ NPC_LOOKS_BOY,
    /* 3 */ NPC_LOOKS_SPORT_MAN,
    /* 4 */ NPC_LOOKS_GRIM_MAN,
    /* 5 */ NPC_LOOKS_NANIWA_LADY,

    /* 6 */ NPC_LOOKS_NUM
} NPCLooks;

typedef struct AnmPersonalId {
    /* 0x00 */ u16 npcId; /* id */
    /* 0x02 */ u16 landId; /* town id */
    /* 0x04 */ u8 landName[LAND_NAME_SIZE]; /* town name */
    /* 0x0A */ u8 nameId; /* lower byte of the id */
    /* 0x0B */ u8 looks; /* internal name for personality */
} AnmPersonalId; // size = 0xC

#endif
