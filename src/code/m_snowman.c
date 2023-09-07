#include "global.h"
#include "m_snowman.h"
#include "m_common_data.h"
#include "m_field_info.h"
#include "m_police_box.h"
#include "m_lib.h"
#include "libc64/qrand.h"
#include "m_name_table.h"

s32 mSN_check_life(u16* name, s32 daysElapsed)
{
    s32 ret = 0;
    
    if (common_data.time.season == 3)
    {
        s32 snowmanAge = (*name - SNOWMAN0) % SNOWMAN_SAVE_COUNT;
        
        if (snowmanAge + daysElapsed < 3) {
            ret = 1;
        }
    }

    return ret;
}

void mSN_ClearSnowmanData(u16* name, s32 snowmanIndex)
{
    bzero(&common_data.snowmanData[snowmanIndex], sizeof(SnowmanData));
    *name = 0;
}

s32 mSN_ClearSnowman(u16* name)
{
    s32 ret = 0;

    if ((*name >= SNOWMAN0) && (*name <= SNOWMAN8))
    {
        s32 snowmanIndex = (*name - SNOWMAN0) / SNOWMAN_SAVE_COUNT;

        mSN_ClearSnowmanData(name, snowmanIndex);
        ret = 1;
    }

    return ret;
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_snowman/mSN_MeltSnowman.s")
s32 mSN_MeltSnowman(u16* name, s32 daysElapsed) {
    s32 ret = 0; //var_v1
    
    if ((*name >= SNOWMAN0) && (*name <= SNOWMAN8)) {
        s32 snowmanIndex = (*name - SNOWMAN0) / SNOWMAN_SAVE_COUNT;
        
        if (daysElapsed < 0) {
            daysElapsed = 1;
            common_data.snowmanYear = 0;
            common_data.snowmanMonth = 0;
            common_data.snowmanDay = 0;
            common_data.snowmanHour = 0;
        }
        
        if (!mSN_check_life(snowmanIndex, daysElapsed)) {
            mSN_ClearSnowmanData(name, snowmanIndex);
            
        } else {
            SnowmanData* snowmanData = &common_data.snowmanData[snowmanIndex];
            
            *name += daysElapsed;

            for(; daysElapsed != 0; daysElapsed--)
            {
                snowmanData->headSize = (u8) (s32) (snowmanData->headSize * 0.8f);
                snowmanData->bodySize = (u8) (s32) (snowmanData->bodySize * 0.8f);
            }
        }

        ret = 1;
    }

    return ret;
}

s32 mSN_get_free_space(void)
{
    SnowmanData* snowmanData = common_data.snowmanData;
    s32  snowmanIndex = 0;

    for (snowmanIndex = 0; snowmanIndex < SNOWMAN_SAVE_COUNT; snowmanIndex++)
    {
        if (!snowmanData[snowmanIndex].exists)
        {
            return snowmanIndex;
        }
    }

    return -1;
}

// mSN_regist_snowman_society
void func_800C8BC4_jp(SnowmanInfo* snowmanInfo) {
    u16 sp2E = *mFI_GetUnitFG(snowmanInfo->position);
    s32 snowmanIndex = mSN_get_free_space();
    u16 name;
    
    if (snowmanIndex != -1) {
        mem_copy((u8*)&common_data.snowmanData[snowmanIndex], (u8*)snowmanInfo, sizeof(SnowmanData));

        if (sp2E != 0) {
            mPB_keep_item(sp2E);
            mFI_Wpos2DepositOFF(snowmanInfo->position);
        }

        name = snowmanIndex * SNOWMAN_SAVE_COUNT + SNOWMAN0;
        mFI_SetFG_common(name, snowmanInfo->position, 1);
    }
}

void mSN_decide_msg(void)
{
    common_data.unk_1074C = fqrand() * 3.0f;
}

void mSN_snowman_init(void)
{
    bzero(common_data.snowmanData, sizeof(SnowmanData[SNOWMAN_SAVE_COUNT]));
    mSN_decide_msg();
}
