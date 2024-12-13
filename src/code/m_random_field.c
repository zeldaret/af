#include "global.h"
#include "m_common_data.h"
#include "m_random_field.h"
#include "m_field_make.h"
#include "m_field_info.h"

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_random_field/func_800BCC40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_random_field/func_800BCCFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_random_field/mRF_Type2BlockInfo.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_random_field/func_800BCDFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_random_field/mRF_GateType2GateCount.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_random_field/mRF_SearchPond.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_random_field/mRF_Attr2BeastRoadAttr.s")

extern u8 mRF_gate_info2[mFM_BLOCK_TYPE_NUM][RANDOM_FIELD_DIRECT_NUM];

s32 mRF_BlockTypeDirect2GateType(u8 block_type, s32 direct) {
  return mRF_gate_info2[block_type][direct];
}

extern RandomFieldGate* mRF_gate_correct_info[mRF_GATE_TYPE_NUM][RANDOM_FIELD_DIRECT_NUM];

RandomFieldGate* mRF_BlockTypeDirect2GateData(s32* gateCount, u8 block_type, s32 direct) {
  s32 type = mRF_BlockTypeDirect2GateType(block_type, direct);
  s32 count = mRF_GateType2GateCount(type);

  *gateCount = count;
  return mRF_gate_correct_info[type][direct];
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_random_field/mRF_BlockInf2CheckBeastRoad.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_random_field/mRF_CheckBeastRoad.s")
