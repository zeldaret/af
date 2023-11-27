#ifndef M_NPC_BASE_H
#define M_NPC_BASE_H

#include "ultra64.h"

typedef struct AnmPersonalId_c {
    /* 0x00 */ u16 npcId; /* id */
    /* 0x02 */ u16 landId; /* town id */
    /* 0x04 */ char landName[LAND_NAME_SIZE]; /* town name */
    /* 0x0A */ u8 nameId; /* lower byte of the id */
    /* 0x0B */ u8 looks; /* internal name for personality */
} AnmPersonalID_c; // size = 0xC

typedef enum NpcSex {
   /* 0 */ NPC_SEX_MALE,
   /* 1 */ NPC_SEX_FEMALE,
   /* 2 */ NPC_SEX_OTHER
} NpcSex;

typedef enum NpcLooks {
    /* 0 */ NPC_LOOKS_GIRL,
    /* 1 */ NPC_LOOKS_KO_GIRL,
    /* 2 */ NPC_LOOKS_BOY,
    /* 3 */ NPC_LOOKS_SPORT_MAN,
    /* 4 */ NPC_LOOKS_GRIM_MAN,
    /* 5 */ NPC_LOOKS_NANIWA_LADY,
    /* 6 */ NPC_LOOKS_NUM
} NpcLooks;

typedef enum NpcFeels {
    /* 0 */ NPC_FEEL_NORMAL,
    /* 1 */ NPC_FEEL_HAPPY,
    /* 2 */ NPC_FEEL_ANGRY,
    /* 3 */ NPC_FEEL_SAD,
    /* 4 */ NPC_FEEL_SLEEPY,
    /* 5 */ NPC_FEEL_PITFALL,
    /* 6 */ NPC_FEEL_NUM
} NpcFeels;

typedef enum NpcPatience {
    /* 0 */ NPC_PATIENCE_MILDLY_ANNOYED,
    /* 1 */ NPC_PATIENCE_ANNOYED,
    /* 2 */ NPC_PATIENCE_NORMAL,
    /* 3 */ NPC_PATIENCE_NUM
} NpcPatience;

#endif

