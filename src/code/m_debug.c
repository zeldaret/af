#include "m_debug.h"
#include "malloc.h"

Debug_mode* debug_mode;

void new_Debug_mode() {

    s32 i;

    debug_mode = (Debug_mode*)malloc(sizeof(Debug_mode));

    debug_mode->mode = 0;
    debug_mode->type = 0;
    debug_mode->inputR = 0;
    debug_mode->oldKey = 0;
    debug_mode->keyWait = 0;

    for (i = 0; i < DEBUG_REG_COUNT; i++) {
        debug_mode->r[i] = 0;
    }
}
