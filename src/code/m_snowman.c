#include "global.h"
#include "m_snowman.h"
#include "m_common_data.h"
#include "m_field_info.h"
#include "m_police_box.h"
#include "m_lib.h"
#include "libc64/qrand.h"

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_snowman/mSN_check_life.s")
// s32 mSN_check_life(u16 *arg0, s32 arg1)
// {
//     s32 var_v1 = 0;

//     // if ((common_data.unk_10008[0x104] == 3) && ((((s32) (*arg0 + 0xFFFF5FF8) % 3) + arg1) < 3))
//     if (common_data.unk_1010C == 3)
//     {
//         s32 temp = (s32) ((*arg0 - 40968) % 3U);
//         if (temp + arg1 < 3) {
//             var_v1 = 1;
//         }
//     }

//     return var_v1;
// }

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_snowman/mSN_ClearSnowmanData.s")
void mSN_ClearSnowmanData(u16 *arg0, s32 arg1)
{
    bzero(&common_data.snowmanData[arg1], sizeof(SnowmanData));
    *arg0 = 0;
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_snowman/mSN_ClearSnowman.s")
s32 mSN_ClearSnowman(u16 *arg0)
{
    s32 var_v1 = 0;

    if ((*arg0 >= 0xA008) && (*arg0 < 0xA011))
    {
        mSN_ClearSnowmanData(arg0, (s32) (*arg0 + 0xFFFF5FF8) / 3);
        var_v1 = 1;
    }

    return var_v1;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_snowman/mSN_MeltSnowman.s")
// s32 mSN_MeltSnowman(u16* actorName, s32 days) {
//     s32 ret = 0; //var_v1
    
//     // s32  var_a1 = days;
//     // u16 snowmanId = *actorName;
    
//     if ((*actorName >= 0xA008) && (*actorName < 0xA011)) {
//         s32 temp_lo = (*actorName - 40968) / SNOWMAN_SAVE_COUNT;
        
//         if (days < 0) {
//             days = 1;
//             common_data.snowmanYear = 0;
//             common_data.snowmanMonth = 0;
//             common_data.snowmanDay = 0;
//             common_data.snowmanHour = 0;
//         }
        
//         if (mSN_check_life(days, temp_lo) == 0) {
//             mSN_ClearSnowmanData(actorName, temp_lo);
            
//         } else {
//             SnowmanData* snowmanDataTemp = &common_data.snowmanData[temp_lo];
            
//             *actorName += days;

//             for(; days != 0; days--)
//             {
//                 snowmanDataTemp->head_size = (u8) (s32) (snowmanDataTemp->head_size * 0.8f);
//                 snowmanDataTemp->body_size = (u8) (s32) (snowmanDataTemp->body_size * 0.8f);
//             }
//         }
//         ret = 1;
//     }
//     return ret;
// }


// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_snowman/mSN_get_free_space.s")
s32 mSN_get_free_space(void)
{
    SnowmanData* var_v0 = common_data.snowmanData;
    s32  var_v1 = 0;

    for (var_v1 = 0; var_v1 != 3; var_v1++)
    {
        if (var_v0->exists == 0)
        {
            return var_v1;
        }
        var_v0++;
    }

    return -1;
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_snowman/func_800C8BC4_jp.s")
// mSN_regist_snowman_society
void func_800C8BC4_jp(SnowmanInfo* snowmanInfo) {
    u16 sp2E = *mFI_GetUnitFG(snowmanInfo->position);
    s32 temp_v0_2 = mSN_get_free_space();
    s32 pad UNUSED;
    
    if (temp_v0_2 != -1) {
        mem_copy((u8*)&common_data.snowmanData[temp_v0_2], (u8*)snowmanInfo, sizeof(SnowmanData));
        if (sp2E != 0) {
            mPB_keep_item(sp2E);
            mFI_Wpos2DepositOFF(snowmanInfo->position);
        }
        mFI_SetFG_common(temp_v0_2 * SNOWMAN_SAVE_COUNT + 0xA008, snowmanInfo->position, 1);
    }
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_snowman/mSN_decide_msg.s")

void mSN_decide_msg(void)
{
    common_data.unk_1074C = (s32) (fqrand() * 3.0f);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_snowman/mSN_snowman_init.s")
void mSN_snowman_init(void)
{
    bzero(common_data.snowmanData, sizeof(SnowmanData[SNOWMAN_SAVE_COUNT]));
    mSN_decide_msg();
}
