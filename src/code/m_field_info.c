#include "global.h"
#include "m_field_info.h"
#include "m_random_field.h"
#include "m_collision_bg.h"
#include "libc64/qrand.h"

s32 mFI_BlockCheck(s32 blockX, s32 blockZ);

// mCoBG_unkStructUnion l_edge_ut = { { 0, 31, 31, 31, 31, 31, mCoBG_ATTRIBUTE_0 } };
extern mCoBG_unkStructUnion l_edge_ut;

extern FieldMakeInfo* g_fdinfo;

void mFI_ClearFieldData(void) {
    g_fdinfo = NULL;
}

s32 mFI_CheckFieldData(void) {
    s32 result = FALSE;

    if (g_fdinfo != 0) {
        result = TRUE;
    }

    return result;
}

FieldMakeBlockInfo* mFI_GetBlockTopP() {
    FieldMakeBlockInfo* blockInfo = NULL;

    if (g_fdinfo != NULL) {
        blockInfo = g_fdinfo->blockInfo;
    }

    return blockInfo;
}

u16 mFI_GetFieldId(void) {
    /* @BUG - check for null pointer omitted (fixed by AC at latest) */
    return g_fdinfo->fieldId;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80087C9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80087D30_jp.s")

s32 mFI_CheckShopFieldName(u16 fieldName) {
    s32 result = FALSE;

    if (FI_GET_TYPE(fieldName) == FI_FIELD_ROOM0) {
        switch (fieldName) {
            case FI_FIELD_ROOM_SHOP0:
            case FI_FIELD_ROOM_SHOP1:
            case FI_FIELD_ROOM_SHOP2:
            case FI_FIELD_ROOM_SHOP3_1:
            case FI_FIELD_ROOM_SHOP3_2:
                result = TRUE;
                break;
        }
    }

    return result;
}

s32 mFI_CheckShop(void) {
    s32 result = FALSE;

    if (mFI_CheckFieldData() == TRUE) {
        result = mFI_CheckShopFieldName(mFI_GetFieldId());
    }
    return result;
}

u8 mFI_GetBlockXMax() {
    u8 blockXMax = 0;

    if (mFI_CheckFieldData() == TRUE) {
        blockXMax = g_fdinfo->blockXMax;
    }

    return blockXMax;
}

u8 mFI_GetBlockZMax() {
    u8 blockZMax = 0;

    if (mFI_CheckFieldData() == TRUE) {
        blockZMax = g_fdinfo->blockZMax;
    }

    return blockZMax;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80087ED0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088018_jp.s")

s32 mFI_GetBlockNum(s32 blockX, s32 blockZ) {
    s32 blockNum = blockX + blockZ * mFI_GetBlockXMax();

    return blockNum;
}

s32 mFI_GetUtNum(s32 utX, s32 utZ) {
    return utX + utZ * UT_X_NUM;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_BlockCheck.s")

s32 mFI_UtNumCheck(int utX, int utZ, int blockXMax, int blockZMax) {
    int result = TRUE;
    int maxUtX = (blockXMax * UT_X_NUM);
    int maxUtZ = (blockZMax * UT_Z_NUM);

    if ((utX < 0) || (utX >= maxUtX) || (utZ < 0) || (utZ >= maxUtZ)) {
        result = FALSE;
    }

    return result;
}

s32 mFI_WposCheck(xyz_t wpos) {
    s32 blockX UNUSED;
    s32 blockZ;

    // Passing &blockZ twice is required to match. Since only the return value
    // is used and not the block numbers, there is no practical difference.
    return mFI_Wpos2BlockNum(&blockZ, &blockZ, wpos);
}

s32 mFI_WposX2UtNumX(f32 wposX) {
    return (s32)(wposX / FI_UT_WORLDSIZE_X_F);
}

s32 mFI_WposZ2UtNumZ(f32 wposZ) {
    return (s32)(wposZ / FI_UT_WORLDSIZE_Z_F);
}

s32 mFI_Wpos2UtNum(s32* utX, s32* utZ, xyz_t wpos) {
    *utX = (s32)(wpos.x / FI_UT_WORLDSIZE_X_F);
    *utZ = (s32)(wpos.z / FI_UT_WORLDSIZE_Z_F);

    if ((wpos.x < 0.0f) || (wpos.x > (mFI_GetBlockXMax() * FI_BK_WORLDSIZE_X_F)) || (wpos.z < 0.0f) ||
        (wpos.z > (mFI_GetBlockZMax() * FI_BK_WORLDSIZE_Z_F))) {
        return FALSE;
    }

    return TRUE;
}

s32 mFI_UtNum2CenterWpos(xyz_t* wpos, int utX, int utZ) {
    s32 pad UNUSED;

    wpos->x = (f32)utX * FI_UT_WORLDSIZE_X_F;
    wpos->z = (f32)utZ * FI_UT_WORLDSIZE_Z_F;

    wpos->x += FI_UT_WORLDSIZE_HALF_X_F;
    wpos->z += FI_UT_WORLDSIZE_HALF_Z_F;

    return mFI_UtNumCheck(utX, utZ, mFI_GetBlockXMax(), mFI_GetBlockZMax());
}

s32 mFI_Wpos2UtCenterWpos(xyz_t* wpos, xyz_t sourcePos) {
    f32 x = (s32)(sourcePos.x / FI_UT_WORLDSIZE_X_F) * FI_UT_WORLDSIZE_X;
    f32 z = (s32)(sourcePos.z / FI_UT_WORLDSIZE_Z_F) * FI_UT_WORLDSIZE_Z;

    wpos->x = x + FI_UT_WORLDSIZE_HALF_Z_F;
    wpos->y = sourcePos.y;
    wpos->z = z + FI_UT_WORLDSIZE_HALF_Z_F;

    return mFI_WposCheck(sourcePos);
}

s32 mFI_Wpos2UtNum_inBlock(s32* utX, s32* utZ, xyz_t wpos) {
    s32 result = FALSE;

    if ((wpos.x >= 0.0f) && (wpos.x < ((f32)mFI_GetBlockXMax() * FI_BK_WORLDSIZE_X_F)) && (wpos.z >= 0.0f) &&
        (wpos.z < ((f32)mFI_GetBlockZMax() * FI_BK_WORLDSIZE_Z_F))) {
        *utX = (s32)(wpos.x / FI_UT_WORLDSIZE_X_F);
        *utZ = (s32)(wpos.z / FI_UT_WORLDSIZE_Z_F);

        *utX &= 0xF;
        *utZ &= 0xF;

        result = TRUE;
    } else {
        *utX = 0;
        *utZ = 0;
    }

    return result;
}

s32 mFI_Wpos2BlockNum(s32* blockX, s32* blockZ, xyz_t wpos) {
    *blockX = (s32)(wpos.x / FI_BK_WORLDSIZE_X_F);
    *blockZ = (s32)(wpos.z / FI_BK_WORLDSIZE_Z_F);

    return mFI_BlockCheck(*blockX, *blockZ);
}

s32 mFI_Wpos2BkandUtNuminBlock(s32* blockX, s32* blockZ, s32* utX, s32* utZ, xyz_t wpos) {
    *blockX = (s32)(wpos.x / FI_BK_WORLDSIZE_X_F);
    *blockZ = (s32)(wpos.z / FI_BK_WORLDSIZE_Z_F);
    *utX = (s32)(wpos.x / FI_UT_WORLDSIZE_X_F);
    *utZ = (s32)(wpos.z / FI_UT_WORLDSIZE_Z_F);

    *utX &= 0xF;
    *utZ &= 0xF;

    return mFI_BlockCheck(*blockX, *blockZ);
}

s32 mFI_UtNum2BlockNum(s32* blockX, s32* blockZ, s32 utX, s32 utZ) {
    if (utX < 0) {
        utX -= (UT_X_NUM - 1);
    }

    if (utZ < 0) {
        utZ -= (UT_Z_NUM - 1);
    }

    *blockX = utX / UT_X_NUM;
    *blockZ = utZ / UT_Z_NUM;

    return mFI_BlockCheck(*blockX, *blockZ);
}

s32 mFI_GetUtNumInBK(s32* blockUtX, s32* blockUtZ, s32 utX, s32 utZ) {
    s32 result = mFI_UtNumCheck(utX, utZ, mFI_GetBlockXMax(), mFI_GetBlockZMax());

    if (result) {
        *blockUtX = utX & 0xF;
        *blockUtZ = utZ & 0xF;
    } else {
        *blockUtX = 0;
        *blockUtZ = 0;
    }

    return result;
}

s32 mFI_WpostoLposInBK(xyz_t* lpos, xyz_t wpos) {
    s32 blockX;
    s32 blockZ;
    s32 result = mFI_Wpos2BlockNum(&blockX, &blockZ, wpos);

    lpos->x = wpos.x - ((f32)blockX * FI_BK_WORLDSIZE_X_F);
    lpos->y = wpos.y;
    lpos->z = wpos.z - ((f32)blockZ * FI_BK_WORLDSIZE_Z_F);

    return result;
}

s32 mFI_LposInBKtoWpos(xyz_t* wpos, xyz_t lpos, s32 blockX, s32 blockZ) {
    wpos->x = lpos.x + (f32)(blockX * FI_BK_WORLDSIZE_X);
    wpos->y = lpos.y;
    wpos->z = lpos.z + (f32)(blockZ * FI_BK_WORLDSIZE_Z);

    return mFI_BlockCheck(blockX, blockZ);
}

s32 mFI_ScrollCheck(xyz_t wpos, u8 dir) {
    s32 blockX;
    s32 blockZ;

    if (mFI_Wpos2BlockNum(&blockX, &blockZ, wpos) == FALSE) {
        return FALSE;
    }

    switch (dir) {
        case FI_MOVEDIR_RIGHT:
            blockX++;
            break;
        case FI_MOVEDIR_LEFT:
            blockX--;
            break;
        case FI_MOVEDIR_UP:
            blockZ--;
            break;
        case FI_MOVEDIR_DOWN:
            blockZ++;
            break;
        default:
            return FALSE;
    }

    return mFI_BlockCheck(blockX, blockZ);
}

s32 mFI_BkNum2WposXZ(f32* worldPosX, f32* worldPosZ, s32 blockX, s32 blockZ) {
    s32 result;

    *worldPosX = (f32)(blockX * FI_BK_WORLDSIZE_X);
    *worldPosZ = (f32)(blockZ * FI_BK_WORLDSIZE_Z);
    result = FALSE;

    if (mFI_CheckFieldData() == TRUE) {
        result = mFI_BlockCheck(blockX, blockZ);
    }

    return result;
}

void mFI_UtNum2PosXZInBk(f32* posX, f32* posZ, s32 utX, s32 utZ) {
    *posX = (f32)(utX * FI_UT_WORLDSIZE_X);
    *posZ = (f32)(utZ * FI_UT_WORLDSIZE_Z);
}

void mFI_BkandUtNum2Wpos(xyz_t* wpos, s32 blockX, s32 blockZ, s32 utX, s32 utZ) {
    f32 wposX;
    f32 wposZ;
    f32 bposX;
    f32 bposZ;

    mFI_BkNum2WposXZ(&wposX, &wposZ, blockX, blockZ);
    mFI_UtNum2PosXZInBk(&bposX, &bposZ, utX, utZ);

    wpos->x = wposX + bposX;
    wpos->y = 0.0f;
    wpos->z = wposZ + bposZ;
}

void mFI_BkandUtNum2CenterWpos(xyz_t* wpos, s32 blockX, s32 blockZ, s32 utX, s32 utZ) {
    mFI_BkandUtNum2Wpos(wpos, blockX, blockZ, utX, utZ);

    wpos->x += FI_UT_WORLDSIZE_HALF_X_F;
    wpos->z += FI_UT_WORLDSIZE_HALF_Z_F;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088CBC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088CD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088CE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088D00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088D30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088D78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088D9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088E08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088E34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088E74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088F14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088F94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008902C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008907C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80089114_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_800891AC_jp.s")

u8 mFI_BkNum2BlockType(s32 blockX, s32 blockZ) {
    s32 blockNum;
    u8 type = 39;

    if (mFI_CheckFieldData() && mFI_BlockCheck(blockX, blockZ)) {
        blockNum = mFI_GetBlockNum(blockX, blockZ);
        type = g_block_type_p[blockNum];
    }

    return type;
}

s32 mFI_GetPuleTypeIdx(u8 type) {
    u32 kind = mRF_Type2BlockInfo(type);
    s32 idx = -1;

    if ((kind & mRF_BLOCKKIND_POOL) == mRF_BLOCKKIND_POOL) {
        idx = type - 69;
    }

    return idx;
}

s32 mFI_GetPuleIdx(void) {
    u32 kindPool = mRF_BLOCKKIND_POOL;
    s32 blockX;
    s32 blockZ;
    u8 type;
    s32 result;

    mFI_BlockKind2BkNum(&blockX, &blockZ, kindPool);
    type = mFI_BkNum2BlockType(blockX, blockZ);
    result = mFI_GetPuleTypeIdx(type);

    return result;
}

u32 mFI_BkNum2BlockKind(s32 blockX, s32 blockZ) {
    s32 blockNum;
    u32 kind = mRF_BLOCKKIND_NONE;

    if (mFI_CheckFieldData() && mFI_BlockCheck(blockX, blockZ)) {
        blockNum = mFI_GetBlockNum(blockX, blockZ);

        kind = g_fdinfo->blockInfo[blockNum].bgInfo.blockKind;
    }

    return kind;
}

s32 mFI_CheckBlockKind(s32 blockX, s32 blockZ, u32 blockKind) {
    s32 isBlockKind = FALSE;
    u32 kind = mFI_BkNum2BlockKind(blockX, blockZ);

    kind &= blockKind;

    if (blockKind == kind) {
        isBlockKind = TRUE;
    }

    return isBlockKind;
}

s32 mFI_CheckBlockKind_OR(s32 blockX, s32 blockZ, u32 blockKindOr) {
    s32 result = FALSE;
    u32 kind = mFI_BkNum2BlockKind(blockX, blockZ);

    kind &= blockKindOr;

    if (kind != mRF_BLOCKKIND_NONE) {
        result = TRUE;
    }

    return result;
}

s32 mFI_BlockKind2BkNum(s32* blockX, s32* blockZ, u32 kind) {
    s32 i;
    s32 succeeded = FALSE;
    u32* kindP = g_block_kind_p;

    *blockX = 0;
    *blockZ = 0;

    if (kindP != NULL) {
        for (i = 0; i < BLOCK_TOTAL_NUM; i++) {
            if (kind == (*kindP & kind)) {
                *blockX = i % 7;
                *blockZ = i / 7;
                succeeded = TRUE;

                break;
            } else {
                kindP++;
            }
        }
    }

    return succeeded;
}

void mFI_GetSpecialBlockNum(s32* blockPos, u32* kinds, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        mFI_BlockKind2BkNum(blockPos + 0, blockPos + 1, *kinds);
        kinds++;
        blockPos += 2;
    }
}

mCoBG_unkStructUnion* mFI_GetBkNum2ColTop(s32 blockX, s32 blockZ) {
    mCoBG_unkStructUnion* col = NULL;

    if (mFI_CheckFieldData() && mFI_BlockCheck(blockX, blockZ)) {
        s32 blockNum = mFI_GetBlockNum(blockX, blockZ);

        col = (mCoBG_unkStructUnion*)g_fdinfo->blockInfo[blockNum].bgInfo.collision;
    }

    return col;
}

mCoBG_unkStructUnion* mFI_UtNum2UtCol(s32 utX, s32 utZ) {
    mCoBG_unkStructUnion* collision;
    s32 blockUtX;
    s32 blockUtZ;
    s32 blockX;
    s32 blockZ;

    if (mFI_UtNumCheck(utX, utZ, mFI_GetBlockXMax(), mFI_GetBlockZMax()) == FALSE) {
        return &l_edge_ut;
    } else if (mFI_UtNum2BlockNum(&blockX, &blockZ, utX, utZ) == FALSE) {
        return &l_edge_ut;
    } else {
        s32 blockNum;

        mFI_GetUtNumInBK(&blockUtX, &blockUtZ, utX, utZ);
        blockNum = mFI_GetBlockNum(blockX, blockZ);
        collision = (mCoBG_unkStructUnion*)g_fdinfo->blockInfo[blockNum].bgInfo.collision;
        collision += blockUtZ * UT_X_NUM + blockUtX;

        return collision;
    }
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80089698_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80089704_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_800897D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80089888_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_800898F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_800899CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_GetSoundSourcePBlockNum.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80089AAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80089B1C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80089B94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80089C0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80089CA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80089D18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80089D6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80089E84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80089EF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008A000_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_BkNumtoUtFGTop.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008A3BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008A410_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008A4F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_GetUnitFG.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008A608_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008A670_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008A74C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008A81C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008A960_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_SetFG_common.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008AA98_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008AB14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008AC74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008ACA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008ACBC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008ACD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008ADCC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008AE70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B1A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B200_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B238_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B26C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B29C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B2D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B300_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B318_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_SetBearActor.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B3E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B4C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B598_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B66C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B774_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B7F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B878_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B9F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008BA74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008BAEC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008BB64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008BBF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_SetMoveActorBitData_ON.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008BCFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_MyMoveActorBitData_ON.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008BDCC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008BE00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008BE38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008BF34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008BFC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_SetPlayerWade.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_CheckPlayerWade.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_GetPlayerWade.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_GetNextBlockNum.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_GetDepositP.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C344_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C390_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C3B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_GetLineDeposit.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C3E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C458_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_BlockDepositOFF.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C498_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C4B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C504_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C524_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C548_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C56C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C5F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C610_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C630_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C650_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_Wpos2DepositOFF.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C708_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C764_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C798_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C830_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C84C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C8C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C938_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C964_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008CA14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008CAD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008CC1C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008CCFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008CD24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008CD74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008CE00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008CE38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008CEC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008CFF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008D12C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008D268_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008D3A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008D574_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_GetOtherFruit.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008D7B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008D884_jp.s")

s32 mFI_GetWaveUtinBlock(s32* arg0, s32* arg1, s32 arg2, s32 arg3) {
    UNUSED s32 pad[4];
    s32 i;
    s32 ret = 0;
    s32 var_s2;
    s32 var_s3 = 0;
    mCoBG_unkStructUnion* temp_v0;
    mCoBG_unkStructUnion* var_s1;

    arg0[0] = 0;
    arg1[0] = 0;

    temp_v0 = var_s1 = mFI_GetBkNum2ColTop(arg2, arg3);

    if (temp_v0 != NULL) {

        for (i = 0; i < 0x100; i++) {

            if (func_80076358_jp(var_s1->data.unk6) == 1) {
                var_s3 += 1;
            }

            var_s1++;
        }

        if (var_s3 > 0) {
            var_s1 = temp_v0;
            var_s2 = fqrand() * var_s3;

            for (i = 0; i < 0x100; i++) {

                if (func_80076358_jp(var_s1->data.unk6) == 1) {

                    if (var_s2 <= 0) {
                        arg0[0] = i & 0xF;
                        arg1[0] = i >> 4;
                        ret = 1;
                        break;
                    }

                    var_s2 -= 1;
                }

                var_s1++;
            }
        }
    }

    return ret;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008DA4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008DCF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008DD0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008DD3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008DDC8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008DF04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008E058_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008E514_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008E5F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_PrintNowBGNum.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_PrintFgAttr.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008E8E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008E9C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008EA5C_jp.s")
