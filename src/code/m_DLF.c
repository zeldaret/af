#include "m_DLF.h"

// Function names taken from Zelda64 Decompilation

void Overlay_LoadGameState(GameStateOverlay* overlayEntry) {
    void* vramStart;

    if (overlayEntry->loadedRamAddr != NULL) {
        return;
    }

    vramStart = overlayEntry->vramStart;
    if (vramStart == NULL) {
        overlayEntry->unk_28 = 0;
        return;
    }

    overlayEntry->loadedRamAddr = malloc_r((uintptr_t)overlayEntry->vramEnd - (uintptr_t)vramStart);

    if (overlayEntry->loadedRamAddr != NULL) {
        ovlmgr_Load(overlayEntry->vromStart, overlayEntry->vromEnd, overlayEntry->vramStart, overlayEntry->vramEnd,
                    overlayEntry->loadedRamAddr);
        overlayEntry->unk_14 =
            (void*)((overlayEntry->unk_14 != NULL)
                        ? (void*)((uintptr_t)overlayEntry->unk_14 - (intptr_t)((uintptr_t)overlayEntry->vramStart -
                                                                               (uintptr_t)overlayEntry->loadedRamAddr))
                        : NULL);

        overlayEntry->init =
            (void*)((overlayEntry->init != NULL)
                        ? (void*)((uintptr_t)overlayEntry->init - (intptr_t)((uintptr_t)overlayEntry->vramStart -
                                                                             (uintptr_t)overlayEntry->loadedRamAddr))
                        : NULL);

        overlayEntry->destroy =
            (void*)((overlayEntry->destroy != NULL)
                        ? (void*)((uintptr_t)overlayEntry->destroy - (intptr_t)((uintptr_t)overlayEntry->vramStart -
                                                                                (uintptr_t)overlayEntry->loadedRamAddr))
                        : NULL);

        overlayEntry->unk_20 =
            (void*)((overlayEntry->unk_20 != NULL)
                        ? (void*)((uintptr_t)overlayEntry->unk_20 - (intptr_t)((uintptr_t)overlayEntry->vramStart -
                                                                               (uintptr_t)overlayEntry->loadedRamAddr))
                        : NULL);

        overlayEntry->unk_24 =
            (void*)((overlayEntry->unk_24 != NULL)
                        ? (void*)((uintptr_t)overlayEntry->unk_24 - (intptr_t)((uintptr_t)overlayEntry->vramStart -
                                                                               (uintptr_t)overlayEntry->loadedRamAddr))
                        : NULL);

        overlayEntry->unk_28 = 0;
    }
}

void Overlay_FreeGameState(GameStateOverlay* overlayEntry) {
    s32 var_v0;

    if (overlayEntry->loadedRamAddr != NULL) {
        var_v0 = (overlayEntry->unk_28 != 0) ? -1 : 0;
        if (var_v0 == 0) {
            overlayEntry->unk_14 =
                (void*)((overlayEntry->unk_14 != NULL) ? (void*)((uintptr_t)overlayEntry->unk_14 +
                                                                 (intptr_t)((uintptr_t)overlayEntry->vramStart -
                                                                            (uintptr_t)overlayEntry->loadedRamAddr))
                                                       : NULL);

            overlayEntry->init =
                (void*)((overlayEntry->init != NULL) ? (void*)((uintptr_t)overlayEntry->init +
                                                               (intptr_t)((uintptr_t)overlayEntry->vramStart -
                                                                          (uintptr_t)overlayEntry->loadedRamAddr))
                                                     : NULL);

            overlayEntry->destroy =
                (void*)((overlayEntry->destroy != NULL) ? (void*)((uintptr_t)overlayEntry->destroy +
                                                                  (intptr_t)((uintptr_t)overlayEntry->vramStart -
                                                                             (uintptr_t)overlayEntry->loadedRamAddr))
                                                        : NULL);

            overlayEntry->unk_20 =
                (void*)((overlayEntry->unk_20 != NULL) ? (void*)((uintptr_t)overlayEntry->unk_20 +
                                                                 (intptr_t)((uintptr_t)overlayEntry->vramStart -
                                                                            (uintptr_t)overlayEntry->loadedRamAddr))
                                                       : NULL);

            overlayEntry->unk_24 =
                (void*)((overlayEntry->unk_24 != NULL) ? (void*)((uintptr_t)overlayEntry->unk_24 +
                                                                 (intptr_t)((uintptr_t)overlayEntry->vramStart -
                                                                            (uintptr_t)overlayEntry->loadedRamAddr))
                                                       : NULL);

            free(overlayEntry->loadedRamAddr);
            overlayEntry->loadedRamAddr = NULL;
        }
    }
}
