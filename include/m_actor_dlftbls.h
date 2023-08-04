#ifndef M_ACTOR_DLFTBLS_H
#define M_ACTOR_DLFTBLS_H

#include "ultra64.h"
#include "libc/stdint.h"

struct ActorInit;

typedef struct ActorOverlay {
    /* 0x00 */ uintptr_t vromStart;
    /* 0x04 */ uintptr_t vromEnd;
    /* 0x08 */ void* vramStart;
    /* 0x0C */ void* vramEnd;
    /* 0x10 */ void* loadedRamAddr; // original name: "allocp"
    /* 0x14 */ struct ActorInit* initInfo;
    /* 0x18 */ char* name;
    /* 0x1C */ u16 allocType; // bit 0: don't allocate memory, use actorContext->0x250? bit 1: Always keep loaded?
    /* 0x1E */ s8 numLoaded; // original name: "clients"
} ActorOverlay; // size = 0x20

// void stub_80058A10();
// void func_80058A18_jp();
// void func_80058AF0_jp();
// void actor_dlftbls_init();
// void actor_dlftbls_cleanup();

// extern UNK_TYPE actor_dlftbls;
// extern UNK_TYPE actor_dlftbls_num;

#endif
