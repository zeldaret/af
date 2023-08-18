#ifndef M_NPC_DEF_H
#define M_NPC_DEF_H

#include "ultra64.h"
#include "m_land.h"

typedef enum mNpc_LOOKS {
    /* 0 */ mNpc_LOOKS_GIRL,
    /* 1 */ mNpc_LOOKS_KO_GIRL,
    /* 2 */ mNpc_LOOKS_BOY,
    /* 3 */ mNpc_LOOKS_SPORT_MAN,
    /* 4 */ mNpc_LOOKS_GRIM_MAN,
    /* 5 */ mNpc_LOOKS_NANIWA_LADY,

    /* 6 */ mNpc_LOOKS_NUM
} mNpc_LOOKS;

typedef struct AnmPersonalID_c {
    /* 0x00 */ u16 npc_id; /* id */
    /* 0x02 */ u16 land_id; /* town id */
    /* 0x04 */ u8 land_name[LAND_NAME_SIZE]; /* town name */
    /* 0x0A */ u8 name_id; /* lower byte of the id */
    /* 0x0B */ u8 looks; /* internal name for personality */
} AnmPersonalID_c; // size = 0xC

#endif
