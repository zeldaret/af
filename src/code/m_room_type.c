#include "m_room_type.h"
#include "m_common_data.h"
#include "game.h"
#include "m_scene_table.h"
#include "m_malloc.h"
#include "m_field_info.h"
#include "m_melody.h"
#include "m_name_table.h"

u8 mRmTp_ftr_size[] = {
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x2,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x2,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x2,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_1x2,
    mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2,
    mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_2x2,
    mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_2x2,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2,
    mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x2,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_2x2,
    mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_2x2,
    mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_1x2,
    mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_2x2,
    mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_2x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
    mRmTp_FTRSIZE_1x2, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1, mRmTp_FTRSIZE_1x1,
};

mRmTp_FtrPlaceData mRmTp_size_s_data[mRmTp_FTR_UNIT_MAX] = {
    { TRUE, 0, 0 }, { FALSE, 0, 0 }, { FALSE, 0, 0 }, { FALSE, 0, 0 }
};

mRmTp_FtrPlaceData mRmTp_size_m_data_south[mRmTp_FTR_UNIT_MAX] = {
    { TRUE, 0, 0 }, { TRUE, 1, 0 }, { FALSE, 0, 0 }, { FALSE, 0, 0 }
};

mRmTp_FtrPlaceData mRmTp_size_m_data_east[mRmTp_FTR_UNIT_MAX] = {
    { TRUE, 0, 0 }, { TRUE, 0, -1 }, { FALSE, 0, 0 }, { FALSE, 0, 0 }
};

mRmTp_FtrPlaceData mRmTp_size_m_data_north[mRmTp_FTR_UNIT_MAX] = {
    { TRUE, 0, 0 }, { TRUE, -1, 0 }, { FALSE, 0, 0 }, { FALSE, 0, 0 }
};

mRmTp_FtrPlaceData mRmTp_size_m_data_west[mRmTp_FTR_UNIT_MAX] = {
    { TRUE, 0, 0 }, { TRUE, 0, 1 }, { FALSE, 0, 0 }, { FALSE, 0, 0 }
};

mRmTp_FtrPlaceData* mRmTp_size_m_data_table[mRmTp_DIRECT_MAX] = {
    mRmTp_size_m_data_south,
    mRmTp_size_m_data_east,
    mRmTp_size_m_data_north,
    mRmTp_size_m_data_west,
};

mRmTp_FtrPlaceData mRmTp_size_l_data[mRmTp_FTR_UNIT_MAX] = {
    { TRUE, 0, 0 }, { TRUE, 1, 0 }, { TRUE, 1, 1 }, { TRUE, 0, 1 }
};

u8 mRmTp_ftr_se_type[] = {
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_BUBU_CHAIR, mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_SOFT_CHAIR, mRmTp_FTR_SE_SOFT_CHAIR,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_SOFT_CHAIR, mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_HARD_CHAIR,   mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_SOFT_CHAIR, mRmTp_FTR_SE_SOFT_CHAIR,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_SOFT_CHAIR, mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_BUBU_CHAIR, mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_SOFT_CHAIR, mRmTp_FTR_SE_SOFT_CHAIR,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_HARD_CHAIR,
    mRmTp_FTR_SE_HARD_CHAIR,   mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_HARD_CHAIR,   mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR,
    mRmTp_FTR_SE_HARD_CHAIR,   mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_TOILET_CHAIR,
    mRmTp_FTR_SE_TOILET_CHAIR, mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR,
    mRmTp_FTR_SE_SOFT_CHAIR,   mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_BUBU_CHAIR, mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_SOFT_CHAIR,   mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR,
    mRmTp_FTR_SE_HARD_CHAIR,   mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_SOFT_CHAIR,   mRmTp_FTR_SE_SOFT_CHAIR, mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_SOFT_CHAIR, mRmTp_FTR_SE_SOFT_CHAIR,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_BUBU_CHAIR,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_BUBU_CHAIR, mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_SOFT_CHAIR, mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_SOFT_CHAIR, mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_SOFT_CHAIR, mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_SOFT_CHAIR,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_HARD_CHAIR,   mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_SOFT_CHAIR, mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
};

void mRmTp_InitFtrPlaceInfo(mRmTp_FtrPlaceInfo* info) {
    mRmTp_FtrPlaceInfo* temp = info;
    s32 i;

    for (i = 0; i < mRmTp_FTR_UNIT_MAX; i++) {
        temp->exists = FALSE;
        temp->utX = 0;
        temp->utZ = 0;

        temp++;
    }
}

s32 mRmTp_ItemNo2FtrSize(u16 name) {
    if (name >= 0x1000 && name < 0x1ECD) {
        UNUSED s32 scoped;
        return mRmTp_ftr_size[(name - 0x1000) >> 2];
    }
    return 0;
}

mRmTp_FtrPlaceData* mRmTp_GetFtrUnitPlaceData(s32 size, s32 dir) {
    switch (size) {
        case mRmTp_FTRSIZE_1x1:
            return mRmTp_size_s_data;
        case mRmTp_FTRSIZE_1x2:
            return mRmTp_size_m_data_table[dir];
        case mRmTp_FTRSIZE_2x2:
            return mRmTp_size_l_data;
        default:
            return mRmTp_size_s_data;
    }
}

s32 mRmTp_GetFurnitureData(u16 ftr, s32 ut_x, s32 ut_z, mRmTp_FtrPlaceInfo* info) {
    UNUSED s32 pad;
    mRmTp_FtrPlaceData* unitData;
    UNUSED s32 pad2;
    s32 idx;
    UNUSED s32 pad3;
    s32 i;

    mRmTp_InitFtrPlaceInfo(info);

    if (ftr >= 0x1000 && ftr < 0x1ECD) {
        idx = (ftr - 0x1000) >> 2;
        unitData = mRmTp_GetFtrUnitPlaceData(mRmTp_ftr_size[idx], (ftr - 0x1000) & 3);

        for (i = 0; i < mRmTp_FTR_UNIT_MAX; i++) {
            (&info[i])->exists = (&unitData[i])->exist;
            (&info[i])->utX = (&unitData[i])->ofsX + ut_x;
            (&info[i])->utZ = (&unitData[i])->ofsZ + ut_z;
        }

        return mRmTp_ftr_size[idx];
    }

    return mRmTp_FTRSIZE_MAX;
}

void mRmTp_AssignFtrFgIdx(u16* dst, u16* src, u16* arg2, u16* arg3) {
    UNUSED u16* temp;
    u16* dstValues[2];
    u16* srcValues[2];
    s32 val = 0;
    u16* cur;
    s32 h;
    s32 n;
    UNUSED s32 pad2;
    s32 i;
    s32 j;
    u16 item;
    s32 idx;
    mRmTp_FtrPlaceInfo placeData[mRmTp_FTR_UNIT_MAX];
    u16* item1;
    u16* item2;
    mRmTp_FtrPlaceInfo* dataPtr;
    s32 k;

    dstValues[0] = dst;
    dstValues[1] = arg2;
    srcValues[0] = src;
    srcValues[1] = arg3;

    for (i = 0; i < 2; i++) {
        if (srcValues[i] == 0) {}
        cur = dstValues[i];
        for (h = 0; h < UT_TOTAL_NUM; h++) {
            *(s16*)cur = -1;
        }
    }

    for (i = 0; i < 2; i++) {
        item1 = srcValues[i];
        item2 = dstValues[i];

        if (item1 != NULL && item2 != NULL) {
            for (n = 0; n < UT_Z_NUM; n++) {
                for (j = 0; j < UT_X_NUM; j++) {
                    item = item1[j + n * UT_X_NUM];
                    if (((item >= 0x1000) && (item < 0x1ECD)) &&
                        mRmTp_GetFurnitureData(item, j, n, placeData) != mRmTp_FTRSIZE_MAX) {
                        dataPtr = placeData;

                        for (k = 0; k < mRmTp_FTR_UNIT_MAX; k++) {
                            if (dataPtr->exists) {
                                idx = dataPtr->utX + dataPtr->utZ * UT_X_NUM;
                                item2[idx] = val;
                            }

                            dataPtr++;
                        }

                        val++;
                    }
                }
            }
        }
    }
}

void mRmTp_MakeFtrNoTable(u16* dst, u16* src) {
    s32 i;
    s32 j;
    s32 h;
    UNUSED s32 pad;

    for (h = 0; h < UT_TOTAL_NUM; h++) {
        dst[h] = 0;
    }

    for (i = 0; i < UT_Z_NUM; i++) {
        for (j = 0; j < UT_X_NUM; j++) {
            mRmTp_FtrPlaceInfo placeData[mRmTp_FTR_UNIT_MAX];
            u16 item = src[i * UT_X_NUM + j];

            if (((item >= 0x1000) && (item < 0x1ECD)) &&
                mRmTp_GetFurnitureData(item, j, i, placeData) != mRmTp_FTRSIZE_MAX) {
                mRmTp_FtrPlaceInfo* data_p = placeData;
                s32 k;

                for (k = 0; k < mRmTp_FTR_UNIT_MAX; k++) {
                    if (data_p->exists) {
                        s32 idx = data_p->utX + data_p->utZ * UT_X_NUM;
                        dst[idx] = item;
                    }

                    data_p++;
                }
            }
        }
    }
}

void* mRmTp_MallocRam(Game* game, size_t size) {
    if (game != NULL) {
        GameAlloc* alloc = &game->alloc;
        return gamealloc_malloc(alloc, ALIGN16(size));
    }

    return zelda_malloc(ALIGN16(size));
}

void mRmTp_FreeRam(Game* game, void* ptr) {
    if (ptr != NULL) {
        if (game != NULL) {
            GameAlloc* alloc = &game->alloc;
            gamealloc_free(alloc, ptr);
        } else {
            zelda_free(ptr);
        }
    }
}

s32 mRmTp_CharVacRight2Left(u8* str, s32 len) {
    s32 i;
    s32 pre = len;

    for (i = 0; i < len; i++) {
        if (str[i] == ' ') {
            pre = i;
            break;
        }
    }

    if (pre != len) {
        s32 ofs = len - pre;

        for (i = 0; i < pre; i++) {
            str[ofs + i] = str[i];
            str[i] = ' ';
        }
    }
}

s32 mRmTp_GetFtrActionSE(s32 ftr_idx, s32 mode) {
    static s32 soft_chair_se_table[] = { 0x41F, 0x422 };
    static s32 hard_chair_se_table[] = { 0x420, 0x423 };
    static s32 bubu_chair_se_table[] = { 0x421, 0x429 };
    static s32 toile_chair_se_table[] = { 0x410, 0x072 };

    if (ftr_idx >= 0 && ftr_idx < FTR_NUM) {
        switch (mRmTp_ftr_se_type[ftr_idx]) {
            case mRmTp_FTR_SE_NONE:
                return -1;
            case mRmTp_FTR_SE_SOFT_CHAIR:
                if (mode >= mRmTp_CHAIR_ACTION_SIT && mode < mRmTp_CHAIR_ACTION_MAX) {
                    return soft_chair_se_table[mode];
                }

                return -1;
            case mRmTp_FTR_SE_HARD_CHAIR:
                if (mode >= mRmTp_CHAIR_ACTION_SIT && mode < mRmTp_CHAIR_ACTION_MAX) {
                    return hard_chair_se_table[mode];
                }

                return -1;
            case mRmTp_FTR_SE_BUBU_CHAIR:
                if (mode >= mRmTp_CHAIR_ACTION_SIT && mode < mRmTp_CHAIR_ACTION_MAX) {
                    return bubu_chair_se_table[mode];
                }

                return -1;
            case mRmTp_FTR_SE_TOILET_CHAIR:
                if (mode >= mRmTp_CHAIR_ACTION_SIT && mode < mRmTp_CHAIR_ACTION_MAX) {
                    return toile_chair_se_table[mode];
                }

                return -1;
            default:
                return -1;
        }
    }

    return -1;
}

u8 mRmTp_birth_type[FTR_NUM] = {
    mRmTp_BIRTH_TYPE_HALLOWEEN,     mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_SANTA,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_SANTA,         mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_HALLOWEEN,
    mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,  mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,  mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_XMAS,          mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_LOTTERY,       mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_LOTTERY,       mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_LOTTERY,       mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_LOTTERY,       mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,  mRmTp_BIRTH_TYPE_BIRTHDAY,      mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_XMAS,          mRmTp_BIRTH_TYPE_XMAS,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_LOTTERY,       mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_LOTTERY,       mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_LOTTERY,       mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_LOTTERY,       mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_LOTTERY,       mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_LOTTERY,       mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_HALLOWEEN,     mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_HALLOWEEN,     mRmTp_BIRTH_TYPE_HALLOWEEN,
    mRmTp_BIRTH_TYPE_HALLOWEEN,     mRmTp_BIRTH_TYPE_UNOBTAINABLE,  mRmTp_BIRTH_TYPE_HALLOWEEN,
    mRmTp_BIRTH_TYPE_HALLOWEEN,     mRmTp_BIRTH_TYPE_HALLOWEEN,     mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_LOTTERY,       mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_HALLOWEEN,     mRmTp_BIRTH_TYPE_HALLOWEEN,     mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_LOTTERY,       mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_LOTTERY,       mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_HALLOWEEN,     mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_LOTTERY,       mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_HANIWA,        mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_CLOTH,     mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,    mRmTp_BIRTH_TYPE_FTR_INSECT,    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,    mRmTp_BIRTH_TYPE_FTR_INSECT,    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,    mRmTp_BIRTH_TYPE_FTR_INSECT,    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,    mRmTp_BIRTH_TYPE_FTR_INSECT,    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,    mRmTp_BIRTH_TYPE_FTR_INSECT,    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,    mRmTp_BIRTH_TYPE_FTR_INSECT,    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,    mRmTp_BIRTH_TYPE_FTR_INSECT,    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,    mRmTp_BIRTH_TYPE_FTR_INSECT,    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,    mRmTp_BIRTH_TYPE_FTR_INSECT,    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,    mRmTp_BIRTH_TYPE_FTR_INSECT,    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,    mRmTp_BIRTH_TYPE_FTR_FISH,      mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,      mRmTp_BIRTH_TYPE_FTR_FISH,      mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,      mRmTp_BIRTH_TYPE_FTR_FISH,      mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,      mRmTp_BIRTH_TYPE_FTR_FISH,      mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,      mRmTp_BIRTH_TYPE_FTR_FISH,      mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,      mRmTp_BIRTH_TYPE_FTR_FISH,      mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,      mRmTp_BIRTH_TYPE_FTR_FISH,      mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,      mRmTp_BIRTH_TYPE_FTR_FISH,      mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,      mRmTp_BIRTH_TYPE_FTR_FISH,      mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,      mRmTp_BIRTH_TYPE_FTR_FISH,      mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,      mRmTp_BIRTH_TYPE_FTR_FISH,      mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,  mRmTp_BIRTH_TYPE_FTR_UMBRELLA,  mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,  mRmTp_BIRTH_TYPE_FTR_UMBRELLA,  mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,  mRmTp_BIRTH_TYPE_FTR_UMBRELLA,  mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,  mRmTp_BIRTH_TYPE_FTR_UMBRELLA,  mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,  mRmTp_BIRTH_TYPE_FTR_UMBRELLA,  mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,  mRmTp_BIRTH_TYPE_FTR_UMBRELLA,  mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,  mRmTp_BIRTH_TYPE_FTR_UMBRELLA,  mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,  mRmTp_BIRTH_TYPE_FTR_UMBRELLA,  mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,  mRmTp_BIRTH_TYPE_FTR_UMBRELLA,  mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,  mRmTp_BIRTH_TYPE_FTR_UMBRELLA,  mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,  mRmTp_BIRTH_TYPE_FTR_UMBRELLA,  mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_LOTTERY,       mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_LOTTERY,       mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_LOTTERY,       mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_SANTA,         mRmTp_BIRTH_TYPE_SANTA,         mRmTp_BIRTH_TYPE_SANTA,
    mRmTp_BIRTH_TYPE_SANTA,         mRmTp_BIRTH_TYPE_SANTA,         mRmTp_BIRTH_TYPE_SANTA,
    mRmTp_BIRTH_TYPE_SANTA,         mRmTp_BIRTH_TYPE_SANTA,         mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_LOTTERY,       mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_XMAS,          mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_XMAS,          mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_LOTTERY,       mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_LOTTERY,       mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_XMAS,
    mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_EVENT,         mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_LOTTERY,       mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,         mRmTp_BIRTH_TYPE_GRP_A,         mRmTp_BIRTH_TYPE_MULTI_FOSSIL,
    mRmTp_BIRTH_TYPE_MULTI_FOSSIL,  mRmTp_BIRTH_TYPE_MULTI_FOSSIL,  mRmTp_BIRTH_TYPE_MULTI_FOSSIL,
    mRmTp_BIRTH_TYPE_MULTI_FOSSIL,  mRmTp_BIRTH_TYPE_MULTI_FOSSIL,  mRmTp_BIRTH_TYPE_MULTI_FOSSIL,
    mRmTp_BIRTH_TYPE_MULTI_FOSSIL,  mRmTp_BIRTH_TYPE_MULTI_FOSSIL,  mRmTp_BIRTH_TYPE_MULTI_FOSSIL,
    mRmTp_BIRTH_TYPE_MULTI_FOSSIL,  mRmTp_BIRTH_TYPE_MULTI_FOSSIL,  mRmTp_BIRTH_TYPE_MULTI_FOSSIL,
    mRmTp_BIRTH_TYPE_MULTI_FOSSIL,  mRmTp_BIRTH_TYPE_MULTI_FOSSIL,  mRmTp_BIRTH_TYPE_MULTI_FOSSIL,
    mRmTp_BIRTH_TYPE_MULTI_FOSSIL,  mRmTp_BIRTH_TYPE_MULTI_FOSSIL,  mRmTp_BIRTH_TYPE_MULTI_FOSSIL,
    mRmTp_BIRTH_TYPE_MULTI_FOSSIL,  mRmTp_BIRTH_TYPE_SINGLE_FOSSIL, mRmTp_BIRTH_TYPE_SINGLE_FOSSIL,
    mRmTp_BIRTH_TYPE_SINGLE_FOSSIL, mRmTp_BIRTH_TYPE_SINGLE_FOSSIL, mRmTp_BIRTH_TYPE_SINGLE_FOSSIL,
    mRmTp_BIRTH_TYPE_GRP_B,         mRmTp_BIRTH_TYPE_SNOWMAN,       mRmTp_BIRTH_TYPE_SNOWMAN,
    mRmTp_BIRTH_TYPE_SNOWMAN,       mRmTp_BIRTH_TYPE_SNOWMAN,       mRmTp_BIRTH_TYPE_SNOWMAN,
    mRmTp_BIRTH_TYPE_SNOWMAN,       mRmTp_BIRTH_TYPE_SNOWMAN,       mRmTp_BIRTH_TYPE_SNOWMAN,
    mRmTp_BIRTH_TYPE_SNOWMAN,       mRmTp_BIRTH_TYPE_SNOWMAN,
};

s32 mRmTp_CheckShopFtr(u16 item) {
    if ((item >= 0x1000 && item < 0x1ECD)) {
        s32 ftr_idx = (item - 0x1000) >> 2;

        switch (mRmTp_birth_type[ftr_idx]) {
            case mRmTp_BIRTH_TYPE_GRP_A:
            case mRmTp_BIRTH_TYPE_GRP_B:
            case mRmTp_BIRTH_TYPE_GRP_C:
            case mRmTp_BIRTH_TYPE_EVENT:
                return TRUE;
            default:
                break;
        }
    }

    return FALSE;
}

u8* mRmTp_CheckFtrBirthInfoTop() {
    return mRmTp_birth_type;
}

s32 mRmTp_GetFloorIdx(void) {
    s32 sceneNo;

    sceneNo = common_data.save.sceneNo;
    if ((sceneNo == SCENE_MY_ROOM_S) || (sceneNo == SCENE_MY_ROOM_M) || (sceneNo == SCENE_MY_ROOM_L)) {
        s32 id = mFI_GetFieldId() - 0x6000;
        mHm_hs_c* home = &common_data.save.homes[id];
        s32 idx = home->roomId & 0x3F;
        return idx;
    }
    if (sceneNo == SCENE_NPC_HOUSE) {
        return mNpc_GetNpcFloorNo() & 0x3F;
    }
    switch (sceneNo) {
        case SCENE_SHOP0:
            return 0x40;
        case SCENE_CONVENI:
            return 0x41;
        case SCENE_SUPER:
            return 0x42;
        case SCENE_DEPART:
        case SCENE_DEPART_2:
            return 0x43;
        case SCENE_POST_OFFICE:
            return 0x44;
        case SCENE_POLICE_BOX:
            return 0x45;
        case SCENE_BUGGY:
            return 0x46;
        case SCENE_BROKER_SHOP:
            return 0x47;
        case SCENE_KAMAKURA:
            return 0x48;
        default:
            return -1;
    }
}

u16 mRmTp_Item1ItemNo2FtrItemNo_AtPlayerRoom(u16 item) {
    s32 value;
    if (item >= 0x2400 && item < 0x2500) {

        value = item >= 0x2400 && item < 0x2500 ? (item - 0x2400) : 0;

        return 0x17AC + ((u16)value * mRmTp_DIRECT_MAX);
    }
    if (item >= 0x2D00 && item < 0x2D21) {
        value = item >= 0x2D00 && item < 0x2D21 ? (item - 0x2D00) : 0;

        return 0x1BA8 + (value * mRmTp_DIRECT_MAX);
    }
    if (item >= 0x2300 && item < 0x2321) {
        value = item >= 0x2300 && item < 0x2321 ? (item - 0x2300) : 0;

        return 0x1C28 + value * mRmTp_DIRECT_MAX;
    }
    if (item >= 0x2204 && item < 0x2224) {
        value = item >= 0x2204 && item < 0x2224 ? (item - 0x2204) : 0;

        return 0x1ca8 + value * mRmTp_DIRECT_MAX;
    }

    return item;
}
u16 mRmTp_FtrItemNo2Item1ItemNo(u16 item) {

    if (item >= 0x17AC && item < 0x1BA8) {
        s32 value = item >= 0x17AC && item < 0x1BA8 ? (item - 0x17AC) >> 2 : 0;

        return 0x2400 + (u16)value;
    }
    if (item >= 0x1BA8 && item < 0x1C28) {
        s32 value = item >= 0x1BA8 && item < 0x1C28 ? (item - 0x1BA8) >> 2 : 0;

        return 0x2D00 + value;
    }
    if (item >= 0x1C28 && item < 0x1CA8) {
        s32 value = item >= 0x1C28 && item < 0x1CA8 ? (item - 0x1C28) >> 2 : 0;

        return mNT_FishIdx2FishItemNo(value);
    }
    if (item >= 0x1CA8 && item < 0x1D28) {

        s32 value = (item - 0x1CA8) >> 2;

        return 0x2204 + value;
    }

    return item;
}

u8 mRmTp_melody[16];

void mRmTp_MakeMelodyData() {
    u64 melody = common_data.save.melody;

    mMld_TransformMelodyData_u64_2_u8(mRmTp_melody, melody);
}

u8* mRmTp_GetMelodyData() {
    return mRmTp_melody;
}

s32 mRmTp_famicom_idx = 0;

void mRmTp_DrawFamicomInfo(gfxprint* gfxprint) {
    if ((gamePT->input[1].press.button & START_BUTTON) == START_BUTTON) {
        mRmTp_famicom_idx++;
    }

    if (mRmTp_famicom_idx < 0) {
        mRmTp_famicom_idx = 7;
    }

    if (mRmTp_famicom_idx >= 8) {
        mRmTp_famicom_idx = 0;
    }

    gfxprint_color(gfxprint, 200, 200, 250, 255);
    gfxprint_locate8x8(gfxprint, 3, 26);
    gfxprint_printf(gfxprint, "ﾌｧﾐｺﾝ %d", mRmTp_famicom_idx); // "Famicom %d"
}

void mRmTp_MakeFamicom_Fdebug() {
    Game* game = gamePT;
    u16 ftr;
    s32 utX;
    s32 utZ;
    u16 direct;
    s32 ofs;
    s32 layer;
    s32 res;

    if ((gamePT->input[1].press.button & Z_TRIG) == Z_TRIG && game != NULL) {

        if (common_data.clip.myRoomClip != NULL) {

            ftr = mRmTp_famicom_idx + 0x34A;

            res = common_data.clip.myRoomClip->unk_04(game, ftr, &utX, &utZ, &direct, &ofs, &layer);

            if (res >= 0) {
                common_data.clip.myRoomClip->unk_28(game, ftr, res, utX, utZ, direct, ofs, layer);
            }
        }
    }
}
