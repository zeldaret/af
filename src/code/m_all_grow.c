#include "m_all_grow.h"
#include "m_time.h"
#include "m_field_make.h"
#include "m_field_info.h"
#include "m_common_data.h"
#include "libu64/gfxprint.h"
#include "m_scene_table.h"
#include "sys_math.h"
#include "ovlmgr.h"
#include "m_malloc.h"
#include "segment_symbols.h"

typedef void (*allGrowOvlUnkFunc)(lbRTC_time_c*, s32*);

extern void mAGrw_RenewalFgItem_ovl(lbRTC_time_c* time, s32* haniwaDeposit);

u16 l_tree_max_table[] = {
    0x80C, 0x82C, 0x824, 0x81C, 0x814, 0x804,
};

allGrowOvlUnkFunc D_80100C5C_jp = NULL;

s32 l_fossil_num_debug = 0;
s32 l_haniwa_num_debug = 0;

AllGrowBlock l_fossil_block[AGrw_FOSSIL_NUM];
AllGrowBlock l_haniwa_block[AGrw_HANIWA_NUM];

void mAGrw_ClearDebugData() {
    l_fossil_num_debug = 0;
    l_haniwa_num_debug = 0;

    bzero(l_fossil_block, AGrw_FOSSIL_NUM * sizeof(AllGrowBlock));
    bzero(l_haniwa_block, AGrw_HANIWA_NUM * sizeof(AllGrowBlock));
}

s32 mAGrw_CheckRegistedData_debug(AllGrowBlock* blockInfo, s32 num, s32 blockX, s32 blockZ) {
    s32 res = FALSE;
    s32 i;

    for (i = 0; i < num; i++) {
        if (blockInfo->blockX == blockX && blockInfo->blockZ == blockZ) {
            res = TRUE;
        }

        blockInfo++;
    }

    return res;
}

void mAGrw_SetBlockData_debug(AllGrowBlock* blockInfo, s32 num, s32 blockX, s32 blockZ) {
    if (mAGrw_CheckRegistedData_debug(blockInfo, num, blockX, blockZ) == FALSE) {
        s32 i;

        for (i = 0; i < num; i++) {
            if (blockInfo->blockX == 0 && blockInfo->blockZ == 0) {
                blockInfo->blockX = blockX;
                blockInfo->blockZ = blockZ;
                break;
            }

            blockInfo++;
        }
    }
}

void mAGrw_SetDebugDataBlock(u16* fgItems, u16* deposit, AllGrowBlock* fossilBlockInfo, s32 fossilMax, s32* fossilNum,
                             AllGrowBlock* haniwaBlockInfo, s32 haniwaMax, s32* haniwaNum, s32 blockX, s32 blockZ) {
    s32 ut_z;
    s32 ut_x;
    for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
        for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
            if (mFI_GetLineDeposit(deposit, ut_x) == TRUE) {
                if (*fgItems == 0x2511) {
                    mAGrw_SetBlockData_debug(fossilBlockInfo, fossilMax, blockX, blockZ);
                    (*fossilNum)++;
                } else if ((*fgItems >= 0x15B0 && *fgItems < 0x17AC)) {
                    mAGrw_SetBlockData_debug(haniwaBlockInfo, haniwaMax, blockX, blockZ);
                    (*haniwaNum)++;
                }
            }
            fgItems++;
        }
        deposit++;
    }
}

void mAGrw_SetDebugData() {
    Foreground* fgItems = common_data.save.foreground[0];
    u16* deposit = common_data.save.deposit[0];
    s32 blockZ;

    mAGrw_ClearDebugData();

    for (blockZ = 0; blockZ < FG_BLOCK_Z_NUM; blockZ++) {
        s32 blockX;
        for (blockX = 0; blockX < FG_BLOCK_X_NUM; blockX++) {
            mAGrw_SetDebugDataBlock(fgItems[0].items[0], deposit, l_fossil_block, AGrw_FOSSIL_NUM, &l_fossil_num_debug,
                                    l_haniwa_block, AGrw_HANIWA_NUM, &l_haniwa_num_debug, blockX + 1, blockZ + 1);
            fgItems++;
            deposit += UT_Z_NUM;
        }
    }
}

void mAGrw_PrintFossilHaniwa_debug(gfxprint* gfxprint) {
    gfxprint_color(gfxprint, 240, 50, 50, 255);
    gfxprint_locate8x8(gfxprint, 3, 17);

    gfxprint_printf(gfxprint, "%4d %1d%1d %1d%1d %1d%1d %1d%1d ", l_fossil_num_debug, l_fossil_block[0].blockX,
                    l_fossil_block[0].blockZ, l_fossil_block[1].blockX, l_fossil_block[1].blockZ,
                    l_fossil_block[2].blockX, l_fossil_block[2].blockZ, l_fossil_block[3].blockX,
                    l_fossil_block[3].blockZ);

    gfxprint_locate8x8(gfxprint, 20, 17);

    gfxprint_printf(gfxprint, "%1d%1d %4d %1d%1d %1d%1d %1d%1d", l_fossil_block[4].blockX, l_fossil_block[4].blockZ,
                    l_haniwa_num_debug, l_haniwa_block[0].blockX, l_haniwa_block[0].blockZ, l_haniwa_block[1].blockX,
                    l_haniwa_block[1].blockZ, l_haniwa_block[2].blockX, l_haniwa_block[2].blockZ);
}

s32 mAGrw_CheckKabuPeddler() {
    lbRTC_time_c* rtcTime = &common_data.time.rtcTime;
    lbRTC_time_c* renewTime = &common_data.save.allGrowRenewTime;
    lbRTC_time_c peddlerSpawnTime;
    s32 res = FALSE;

    if (rtcTime->weekday == lbRTC_SUNDAY) {
        lbRTC_TimeCopy(&peddlerSpawnTime, rtcTime);
        peddlerSpawnTime.hour = 6;
        peddlerSpawnTime.min = 0;
        peddlerSpawnTime.sec = 0;

        if (lbRTC_IsOverTime(&peddlerSpawnTime, renewTime) == lbRTC_OVER ||
            lbRTC_IsEqualTime(&mTM_rtcTime_clear_code, renewTime, lbRTC_CHECK_ALL) == TRUE) {
            res = TRUE;
        }
    }

    return res;
}

void mAGrw_OrderSetHaniwa() {
    common_data.save.haniwaScheduled = TRUE;
}

u8 func_80055E34_jp(u16* items) {
    return func_8008B774_jp(0x804, items);
}

void mAGrw_ChangeItemBlock(u16* blockItems, u16 newItem, u16 targetItem, u8 possibleNum) {
    s32 selected = RANDOM(possibleNum);
    s32 i;

    for (i = 0; i < UT_TOTAL_NUM; i++) {
        if (targetItem == *blockItems) {
            if (selected <= 0) {
                *blockItems = newItem;
                break;
            }
            selected--;
        }
        blockItems++;
    }
}

void mAGrw_ChangeItemBlock2(u16* blockItems, u16 newItem, u8 possibleNum) {
    mAGrw_ChangeItemBlock(blockItems, newItem, 0x804, possibleNum);
}

s32 mAGrw_CheckPutXmasTree(lbRTC_time_c* time) {
    s32 res = 0;

    if (time->month == lbRTC_DECEMBER && time->day >= 10 && time->day < 25) {
        res = 1;
    }

    return res;
}

void mAGrw_SetXmasTreeBlock(u16* blockItems) {
    u8 existNum = 0;
    u8 possibleNum = 0;
    s32 i;

    for (i = 0; i < UT_TOTAL_NUM; i++) {
        if (*blockItems == 0x804) {
            possibleNum++;
        } else if (*blockItems == 0x60) {
            existNum++;
        }

        blockItems++;
    }

    blockItems = blockItems - UT_TOTAL_NUM;

    if (possibleNum > 0) {

        s32 spawnNum = 3 - existNum;

        if (spawnNum > 0) {
            if (possibleNum < spawnNum) {
                spawnNum = possibleNum;
            }

            for (i = 0; i < spawnNum; i++, possibleNum--) {
                mAGrw_ChangeItemBlock2(blockItems, 0x60, possibleNum);
            }
        }
    }
}

void mAGrw_ClearXmasTreeBlock(u16* blockItems) {
    s32 i;

    for (i = 0; i < UT_TOTAL_NUM; i++) {
        if (*blockItems == 0x60) {
            *blockItems = 0x804;
        }

        blockItems++;
    }
}

typedef void (*xmasProcFunc)(u16*);

void mAGrw_XmasTreeField(s32 type) {
    static xmasProcFunc xmas_proc[] = { &mAGrw_ClearXmasTreeBlock, &mAGrw_SetXmasTreeBlock };

    Foreground* block = common_data.save.foreground[0];
    s32 i;

    for (i = 0; i < FG_BLOCK_TOTAL_NUM; i++) {
        (*xmas_proc[type])(block[0].items[0]);
        block++;
    }
}

void mAGrw_SetXmasTree() {
    if (common_data.save.sceneNo == SCENE_FG) {
        s32 type = mAGrw_CheckPutXmasTree(&common_data.time.rtcTime);
        mAGrw_XmasTreeField(type);
    }
}

void mAGrw_RenewalFgItem(lbRTC_time_c* time) {
    u32 ovlSize = SEGMENT_VRAM_SIZE(m_all_grow_ovl);
    allGrowOvlUnkFunc func;

    if (common_data.save.sceneNo == SCENE_FG) {
        s32 schedHaniwa = common_data.save.haniwaScheduled;
        D_80100C5C_jp = zelda_malloc(ovlSize);

        if (D_80100C5C_jp != NULL) {
            ovlmgr_Load(SEGMENT_ROM_START(m_all_grow_ovl), SEGMENT_ROM_END(m_all_grow_ovl),
                        SEGMENT_VRAM_START(m_all_grow_ovl), SEGMENT_VRAM_END(m_all_grow_ovl), D_80100C5C_jp);
            func = (allGrowOvlUnkFunc)SEGMENT_VRAM_RESOLVE_ADDR(m_all_grow_ovl, D_80100C5C_jp, mAGrw_RenewalFgItem_ovl);
            (*func)(time, &schedHaniwa);
            common_data.save.haniwaScheduled = schedHaniwa;
            zelda_free(D_80100C5C_jp);
        }

        mAGrw_SetDebugData();
    }
}

void mAGrw_ChangeTree2OtherBlock(u16* items, u16 other) {
    u8 count = func_80055E34_jp(items);

    if (count > 0) {
        mAGrw_ChangeItemBlock2(items, other, count);
    }
}

void mAGrw_ChangeTree2FruitTreeLine(Foreground* fg, u16 fruitTree) {
    s32 block0;
    s32 block1;

    block0 = RANDOM(FG_BLOCK_X_NUM);
    block1 = RANDOM(FG_BLOCK_X_NUM - 1);

    if (block0 == block1) {
        block1++;
    }

    mAGrw_ChangeTree2OtherBlock((fg + block0)->items[0], fruitTree);
    mAGrw_ChangeTree2OtherBlock((fg + block1)->items[0], fruitTree);
}

void mAGrw_ChangeTree2FruitTree() {
    s32 fruit = common_data.save.fruit - 0x2800;
    u16 fruitTree;
    s32 blockZ;

    fruitTree = l_tree_max_table[fruit];
    for (blockZ = 0; blockZ < FG_BLOCK_Z_NUM; blockZ++) {
        mAGrw_ChangeTree2FruitTreeLine(common_data.save.foreground[blockZ], fruitTree);
    }
}
