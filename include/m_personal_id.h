#ifndef M_PERSONAL_ID_H
#define M_PERSONAL_ID_H

#include "ultra64.h"
#include "m_land.h"

#define PLAYER_NAME_LEN 6

typedef struct PersonalID_c {
  /* 0x00 */ u8 player_name[PLAYER_NAME_LEN];
  /* 0x06 */ u8 land_name[LAND_NAME_SIZE];
  /* 0x0C */ u16 player_id;
  /* 0x0E */ u16 land_id;
} PersonalID_c; // size = 0x10

#endif
