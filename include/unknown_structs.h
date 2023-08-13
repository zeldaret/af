#ifndef UNKNOWN_STRUCTS_H
#define UNKNOWN_STRUCTS_H

#include "ultra64.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "unk.h"
#include "other_types.h"

typedef struct D_8010EAA0 {
    /* 0x00 */ RomOffset unk_00;
    /* 0x04 */ RomOffset unk_04;
    /* 0x08 */ char unk08[0xB];
    /* 0x13 */ u8 unk_13;
} D_8010EAA0;  // size = 0x14

#endif
