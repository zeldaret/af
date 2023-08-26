#ifndef M_PERSONAL_ID_H
#define M_PERSONAL_ID_H

#include "ultra64.h"
#include "m_land.h"

#define PLAYER_NAME_LEN 6

typedef struct PersonalId {
  /* 0x00 */ u8 playerName[PLAYER_NAME_LEN];
  /* 0x06 */ u8 landName[LAND_NAME_SIZE];
  /* 0x0C */ u16 playerId;
  /* 0x0E */ u16 landId;
} PersonalId; // size = 0x10

#endif
