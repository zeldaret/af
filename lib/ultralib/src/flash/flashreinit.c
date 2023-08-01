#include "ultra64.h"
#include "PR/os_internal_flash.h"

OSPiHandle* osFlashReInit(u8 latency, u8 pulse, u8 page_size, u8 rel_duration, u32 start) {
    __osFlashHandler.baseAddress = PHYS_TO_K1(start);
    __osFlashHandler.type++;
    __osFlashHandler.latency = latency;
    __osFlashHandler.pulse = pulse;
    __osFlashHandler.pageSize = page_size;
    __osFlashHandler.relDuration = rel_duration;
    __osFlashHandler.domain = PI_DOMAIN2;

    return &__osFlashHandler;
}
