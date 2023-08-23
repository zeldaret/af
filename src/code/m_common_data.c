#include "global.h"
#include "m_common_data.h"
#include "m_field_info.h"
#include "68AAF0.h"

CommonData common_data;

void common_data_reinit(void) {
    u8 sp1F = common_data.pad_connected;

    bzero(&common_data, sizeof(CommonData));
    common_data.wipeType = -1;
    common_data.game_started = 1;
    common_data.unk_10004 = -1;
    common_data.demo_profile = 0xC9;
    common_data.pad_connected = sp1F;
    mFRm_ClearSaveCheckData(&common_data);
}

void common_data_init(void) {
    common_data_reinit();
}

void common_data_clear(void) {
    clip_clear();
}
