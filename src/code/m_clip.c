#include "m_clip.h"
#include "m_common_data.h"

void clip_clear(void) {
    s32 i;
    void** clip = (void**)&common_data.clip;

    for (i = 0; i < sizeof(Clip) / sizeof(void*); i++) {
        *clip++ = NULL;
    }
}
