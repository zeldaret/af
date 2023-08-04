#include "m_actor_dlftbls.h"
#include "libc/stddef.h"
#include "unk.h"
#include "m_actor.h"
#include "segment_symbols.h"

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

extern ActorOverlay actor_dlftbls[];
// ActorOverlay actor_dlftbls[] = {
// #include "tables/actor_table.h"
// };

#undef DEFINE_ACTOR
#undef DEFINE_ACTOR_INTERNAL
#undef DEFINE_ACTOR_UNSET

extern ActorId actor_dlftbls_num;

extern UNK_TYPE B_8011B890_jp;
extern UNK_TYPE B_8011B8A0_jp;

void stub_80058A10(void) {
}

void func_80058A18_jp(void *arg0, void *arg1) {
    ActorOverlay *var_s0;
    ActorId i;
    size_t overlaySize;

    FaultDrawer_SetCharPad(-2, 0);
    FaultDrawer_Printf("actor_dlftbls %u\n", actor_dlftbls_num);
    FaultDrawer_Printf("No. RamStart- RamEnd cn  Name\n");

    var_s0 = &actor_dlftbls;
    for (i = 0; i < actor_dlftbls_num; i++) {
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
    ActorId i;

    for (i = 0; i < actor_dlftbls_num; i++, var_v0++) {
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
    actor_dlftbls_num = ACTOR_ID_MAX;
    Fault_AddClient(&B_8011B890_jp, func_80058A18_jp, 0, 0);
    Fault_AddAddrConvClient(&B_8011B8A0_jp, func_80058AF0_jp, 0);
}

void actor_dlftbls_cleanup(void) {
    Fault_RemoveClient(&B_8011B890_jp);
    Fault_RemoveAddrConvClient(&B_8011B8A0_jp);
    actor_dlftbls_num = 0;
}
