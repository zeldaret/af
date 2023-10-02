#include "global.h"
#include "m_common_data.h"
#include "m_flashrom.h"
#include "68AAF0.h"

CommonData common_data;

void common_data_reinit(void) {
    u8 sp1F = common_data.unk_10AB0;

    bzero(&common_data, sizeof(CommonData));
    common_data.unk_1014B = -1;
    common_data.unk_10000 = 1;
    common_data.unk_10004 = -1;
    common_data.unk_107B6 = 0xC9;
    common_data.unk_10AB0 = sp1F;
    mFRm_ClearSaveCheckData(&common_data);
}

void common_data_init(void) {
    common_data_reinit();
}

void common_data_clear(void) {
    clip_clear();
}
