#ifndef M_LAND_H_H
#define M_LAND_H_H

#include "ultra64.h"

// Town name character count
#define LAND_NAME_SIZE 6
#define LAND_NAME_MURA_SIZE (LAND_NAME_SIZE + 2)

typedef struct LandInfo {
    /* 0x00 */ u8 name[LAND_NAME_SIZE];
    /* 0x06 */ s8 exists;
    /* 0x08 */ u16 landId;
} LandInfo; // size >= 0xA



#endif
