#include "m_actor_dlftbls.h"
#include "libc/stddef.h"
#include "unk.h"
#include "m_actor.h"
#include "segment_symbols.h"
#include "fault.h"

// Segment and Profile declarations (also used in the table below)
#define DEFINE_ACTOR(name, _enumValue, _allocType) \
    DECLARE_SEGMENT(ovl_##name); \
    extern struct ActorInit name##_Profile;
#define DEFINE_ACTOR_INTERNAL(name, _enumValue, _allocType) \
    extern struct ActorInit name##_Profile;
#define DEFINE_ACTOR_UNSET(_enumValue)

#include "tables/actor_table.h"

#undef DEFINE_ACTOR
#undef DEFINE_ACTOR_INTERNAL
#undef DEFINE_ACTOR_UNSET

// Actor Overlay Table definition
#define DEFINE_ACTOR(name, _enumValue, allocType) \
    { SEGMENT_ROM_START(ovl_##name),                          \
      SEGMENT_ROM_END(ovl_##name),                            \
      SEGMENT_VRAM_START(ovl_##name),                         \
      SEGMENT_VRAM_END(ovl_##name),                           \
      NULL,                                                   \
      &name##_Profile,                                       \
      NULL,                                                   \
      allocType,                                              \
      0 },

#define DEFINE_ACTOR_INTERNAL(name, _enumValue, allocType) \
    { 0, 0, NULL, NULL, NULL, &name##_Profile, NULL, allocType, 0 },

#define DEFINE_ACTOR_UNSET(_enumValue) { 0 },

ActorOverlay actor_dlftbls[] = {
#include "tables/actor_table.h"
};

#undef DEFINE_ACTOR
#undef DEFINE_ACTOR_INTERNAL
#undef DEFINE_ACTOR_UNSET

ActorId actor_dlftbls_num = 0;

void stub_80058A10(void) {
}

void func_80058A18_jp(void *arg0 UNUSED, void *arg1 UNUSED) {
    ActorOverlay *overlayEntry;
    size_t overlaySize;
    ActorId i;

    FaultDrawer_SetCharPad(-2, 0);

    FaultDrawer_Printf("actor_dlftbls %u\n", actor_dlftbls_num);
    FaultDrawer_Printf("No. RamStart- RamEnd cn  Name\n");

    for (i = 0, overlayEntry = actor_dlftbls; i < actor_dlftbls_num; i++, overlayEntry++) {
        overlaySize = (uintptr_t)overlayEntry->vramEnd - (uintptr_t)overlayEntry->vramStart;

        if (overlayEntry->loadedRamAddr != 0) {
            FaultDrawer_Printf("%3d %08x-%08x %3d %s\n", i, overlayEntry->loadedRamAddr, (uintptr_t)overlayEntry->loadedRamAddr + overlaySize, overlayEntry->numLoaded, "");
        }
    }
}

uintptr_t func_80058AF0_jp(uintptr_t address, void *param UNUSED) {
    uintptr_t addr = address; // using uintptr_t doesn't match
    ActorOverlay *overlayEntry = actor_dlftbls;
    size_t relocationDiff;
    void *loadedRamAddr;
    size_t overlaySize;
    ActorId i;

    for (i = 0; i < actor_dlftbls_num; i++, overlayEntry++) {
        overlaySize = (uintptr_t)overlayEntry->vramEnd - (uintptr_t)overlayEntry->vramStart;
        loadedRamAddr = overlayEntry->loadedRamAddr;
        relocationDiff = (uintptr_t)overlayEntry->vramStart - (uintptr_t)loadedRamAddr;

        if (loadedRamAddr != NULL) {
            if ((addr >= (uintptr_t) loadedRamAddr) && (addr < ((uintptr_t)loadedRamAddr + overlaySize))) {
                return addr + relocationDiff;
            }
        }
    }

    return 0;
}

FaultClient B_8011B890_jp;
FaultAddrConvClient B_8011B8A0_jp;

void actor_dlftbls_init(void) {
    actor_dlftbls_num = ACTOR_ID_MAX;
    Fault_AddClient(&B_8011B890_jp, func_80058A18_jp, NULL, NULL);
    Fault_AddAddrConvClient(&B_8011B8A0_jp, func_80058AF0_jp, NULL);
}

void actor_dlftbls_cleanup(void) {
    Fault_RemoveClient(&B_8011B890_jp);
    Fault_RemoveAddrConvClient(&B_8011B8A0_jp);
    actor_dlftbls_num = 0;
}
