#ifndef M_LAND_H_H
#define M_LAND_H_H

#include "ultra64.h"

// Town name character count
#define LAND_NAME_SIZE 8
#define LAND_NAME_MURA_SIZE (LAND_NAME_SIZE + 2)

typedef struct mLd_land_info_c {
    char unk00[0xA];
} mLd_land_info_c; // size >= 0xA

#endif
