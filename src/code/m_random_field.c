#include "global.h"
#include "m_common_data.h"
#include "m_random_field.h"
#include "m_field_make.h"
#include "m_field_info.h"
#include "m_scene_table.h"


#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_random_field/func_800BCC40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_random_field/func_800BCCFC_jp.s")

extern u32 mRF_block_info[];

u32 mRF_Type2BlockInfo(u8 blockType) {
  if (blockType < mFM_BLOCK_TYPE_NUM) {
    return mRF_block_info[blockType];
  }

  return mRF_BLOCKKIND_NONE;
}

/* @unused */
u8 mRF_Info2BlockType(u32 blockInfo) {
    s32 blockType = 0;

    for (blockType = 0; blockType < mFM_BLOCK_TYPE_NUM; blockType += 1) {
        if (blockInfo == mRF_block_info[blockType]) {
            return (u8) blockType;
        }
    }

    return mFM_BLOCK_TYPE_NONE;
}

extern u8 gate_count_table[];
s32 mRF_GateType2GateCount(s32 gateType) {
    // TODO: import data
    // static u8 gate_count_table[mRF_GATE_TYPE_NUM] = {
    //   0, 1, 1, 2, 2, 3
    // };

    if (gateType < mRF_GATE_TYPE_NUM) {
        return gate_count_table[gateType];
    }

    return 0;
}

s32 mRF_SearchPond(s32* utX, s32* utZ, s32 blockX, s32 blockZ) {
  FieldMakeBGSoundSource* soundSourceInfo = mFI_GetSoundSourcePBlockNum(blockX, blockZ);

  if (soundSourceInfo != NULL) {
    s32 i;

    for (i = 0; i < mFI_NUM_SOUND_SOURCES; i++, soundSourceInfo++) {
      if (soundSourceInfo->kind == mFI_SOUND_SOURCE_POND) {
        if (mFI_Wpos2UtNum(utX, utZ, soundSourceInfo->pos)) {
          return TRUE;
        }
      }
    }
  }

  return FALSE;
}

s32 mRF_Attr2BeastRoadAttr(s32 attribute) {
  switch (attribute) {
    case mCoBG_ATTRIBUTE_0:
    case mCoBG_ATTRIBUTE_1:
      return mCoBG_ATTRIBUTE_2;

    case mCoBG_ATTRIBUTE_4:
    case mCoBG_ATTRIBUTE_5:
      return mCoBG_ATTRIBUTE_6;

    default:
      return attribute;
  }
}

extern u8 mRF_gate_info2[mFM_BLOCK_TYPE_NUM][RANDOM_FIELD_DIRECT_NUM];

s32 mRF_BlockTypeDirect2GateType(u8 block_type, s32 direct) {
  return mRF_gate_info2[block_type][direct];
}

extern RandomFieldGate* mRF_gate_correct_info[mRF_GATE_TYPE_NUM][RANDOM_FIELD_DIRECT_NUM];

RandomFieldGate* mRF_BlockTypeDirect2GateData(s32* gateCount, u8 blockType, s32 direct) {
  s32 type = mRF_BlockTypeDirect2GateType(blockType, direct);
  s32 count = mRF_GateType2GateCount(type);

  *gateCount = count;
  return mRF_gate_correct_info[type][direct];
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_random_field/mRF_BlockInf2CheckBeastRoad.s")

void mRF_CheckBeastRoad() {
  if (SAVE_GET(sceneNo) == SCENE_FG) {
    s32 blockXMax = mFI_GetBlockXMax() - 1;
    s32 blockZMax = mFI_GetBlockZMax() - 1;
    s32 blockX;
    s32 blockZ;

    for (blockZ = 1; blockZ < blockZMax; blockZ++) {
      for (blockX = 1; blockX < blockXMax; blockX++) {
        mCoBG_unkStructUnion* collisionData = mFI_GetBkNum2ColTop(blockX, blockZ);
        u8 type = mFI_BkNum2BlockType(blockX, blockZ);

        mRF_BlockInf2CheckBeastRoad(type, collisionData);
      }
    }
  }
}
