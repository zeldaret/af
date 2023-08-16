#ifndef M_OBJECT_H
#define M_OBJECT_H

#include "ultra64.h"
#include "other_types.h"


#define DEFINE_OBJECT(_name, enumValue) enumValue,
#define DEFINE_OBJECT_UNSET(enumValue) enumValue,

typedef enum ObjectId {
    #include "tables/object_table.h"
    /* 0x19A */ OBJECT_ID_MAX // TODO: Figure out this value properly. This value was guessed, it may be smaller
} ObjectId;

#undef DEFINE_OBJECT
#undef DEFINE_OBJECT_UNSET

typedef struct ObjectOverlay {
    /* 0x00 */ RomOffset vromStart;
    /* 0x04 */ RomOffset vromEnd;
} ObjectOverlay; // size = 0x8

extern ObjectOverlay gObjectTable[OBJECT_ID_MAX];

#endif
