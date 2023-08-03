#include "m_actor_dlftbls.h"
#include "libc/stddef.h"
#include "libc/stdint.h"
#include "unk.h"

extern UNK_TYPE B_8011B890_jp;
extern UNK_TYPE B_8011B8A0_jp;

extern s32 D_801025B0_jp;

struct Actor;
struct PlayState;

typedef void(*ActorFunc)(struct Actor* this, struct PlayState* play);

typedef struct ActorInit {
    /* 0x00 */ s16 id;
    /* 0x02 */ u8 type;
    /* 0x04 */ u32 flags;
    /* 0x08 */ s16 objectId;
    /* 0x0C */ u32 instanceSize;
    /* 0x10 */ ActorFunc init;
    /* 0x14 */ ActorFunc destroy;
    /* 0x18 */ ActorFunc update;
    /* 0x1C */ ActorFunc draw;
} ActorInit; // size = 0x20

typedef struct ActorOverlay {
    /* 0x00 */ uintptr_t vromStart;
    /* 0x04 */ uintptr_t vromEnd;
    /* 0x08 */ void* vramStart;
    /* 0x0C */ void* vramEnd;
    /* 0x10 */ void* loadedRamAddr; // original name: "allocp"
    /* 0x14 */ ActorInit* initInfo;
    /* 0x18 */ char* name;
    /* 0x1C */ u16 allocType; // bit 0: don't allocate memory, use actorContext->0x250? bit 1: Always keep loaded?
    /* 0x1E */ s8 numLoaded; // original name: "clients"
} ActorOverlay; // size = 0x20

extern ActorOverlay actor_dlftbls[];

void stub_80058A10(void) {
}

void func_80058A18_jp(void *arg0, void *arg1) {
    ActorOverlay *var_s0;
    s32 i;
    size_t overlaySize;

    FaultDrawer_SetCharPad(-2, 0);
    FaultDrawer_Printf("actor_dlftbls %u\n", D_801025B0_jp);
    FaultDrawer_Printf("No. RamStart- RamEnd cn  Name\n");

    var_s0 = &actor_dlftbls;
    for (i = 0; i < D_801025B0_jp; i++) {
        overlaySize = (uintptr_t)var_s0->vramEnd - (uintptr_t)var_s0->vramStart;

        if (var_s0->loadedRamAddr != 0) {
            FaultDrawer_Printf("%3d %08x-%08x %3d %s\n", i, var_s0->loadedRamAddr, (uintptr_t)var_s0->loadedRamAddr + overlaySize, var_s0->numLoaded, "");
        }
        var_s0++;
    }
}

uintptr_t func_80058AF0_jp(uintptr_t address, void *param) {
    uintptr_t addr = address; // using uintptr_t doesn't match
    ActorOverlay *var_v0 = actor_dlftbls;
    size_t relocationDiff;
    void *loadedRamAddr;
    size_t overlaySize;
    s32 i;

    for (i = 0; i < D_801025B0_jp; i++, var_v0++) {
        overlaySize = (uintptr_t)var_v0->vramEnd - (uintptr_t)var_v0->vramStart;
        loadedRamAddr = var_v0->loadedRamAddr;
        relocationDiff = (uintptr_t)var_v0->vramStart - (uintptr_t)loadedRamAddr;

        if (loadedRamAddr != NULL) {
            if ((addr >= (uintptr_t) loadedRamAddr) && (addr < ((uintptr_t)loadedRamAddr + overlaySize))) {
                return addr + relocationDiff;
            }
        }
    }

    return 0;
}

void actor_dlftbls_init(void) {
    D_801025B0_jp = 0xC9;
    Fault_AddClient(&B_8011B890_jp, func_80058A18_jp, 0, 0);
    Fault_AddAddrConvClient(&B_8011B8A0_jp, func_80058AF0_jp, 0);
}

void actor_dlftbls_cleanup(void) {
    Fault_RemoveClient(&B_8011B890_jp);
    Fault_RemoveAddrConvClient(&B_8011B8A0_jp);
    D_801025B0_jp = 0;
}
