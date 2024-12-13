#ifndef M_FIELD_INFO_H
#define M_FIELD_INFO_H

#include "ultra64.h"
#include "z64math.h"
#include "m_collision_bg.h"
#include "unk.h"
#include "m_field_make.h"

struct Actor;
struct Game_Play;
struct FieldMakeBlockInfo;
struct FieldMakeMoveActor;
struct Game;

#define FI_UT_BASE_SIZE 40
#define FI_UT_BASE_SIZE_F ((f32)FI_UT_BASE_SIZE)

#define FI_UT_WORLDSIZE_X FI_UT_BASE_SIZE
#define FI_UT_WORLDSIZE_X_F (f32)FI_UT_WORLDSIZE_X

#define FI_UT_WORLDSIZE_Z FI_UT_BASE_SIZE
#define FI_UT_WORLDSIZE_Z_F (f32)FI_UT_WORLDSIZE_Z

#define FI_UT_WORLDSIZE_HALF_X_F (FI_UT_WORLDSIZE_X_F / 2.0f)
#define FI_UT_WORLDSIZE_HALF_Z_F (FI_UT_WORLDSIZE_X_F / 2.0f)

#define FI_BK_WORLDSIZE_BASE (FI_UT_BASE_SIZE * UT_BASE_NUM)
#define FI_BK_WORLDSIZE_BASE_F ((f32)FI_BK_WORLDSIZE_BASE)

#define FI_BK_WORLDSIZE_X FI_BK_WORLDSIZE_BASE
#define FI_BK_WORLDSIZE_Z FI_BK_WORLDSIZE_BASE

#define FI_BK_WORLDSIZE_X_F FI_BK_WORLDSIZE_BASE_F
#define FI_BK_WORLDSIZE_Z_F FI_BK_WORLDSIZE_BASE_F

#define FI_BK_WORLDSIZE_HALF_X (FI_BK_WORLDSIZE_X / 2)
#define FI_BK_WORLDSIZE_HALF_Z (FI_BK_WORLDSIZE_Z / 2)

#define FI_BK_WORLDSIZE_HALF_X_F (FI_BK_WORLDSIZE_X_F / 2.0f)
#define FI_BK_WORLDSIZE_HALF_Z_F (FI_BK_WORLDSIZE_Z_F / 2.0f)


typedef enum FieldType {
  /* 0 */ FI_FIELDTYPE_FG,
  /* 1 */ FI_FIELDTYPE_1,
  /* 2 */ FI_FIELDTYPE_2,
  /* 3 */ FI_FIELDTYPE_ROOM,
  /* 4 */ FI_FIELDTYPE_NPC_ROOM,
  /* 5 */ FI_FIELDTYPE_DEMO,
  /* 6 */ FI_FIELDTYPE_PLAYER_ROOM,
  /* 7 */ FI_FIELDTYPE_NUM
} FieldType;


#define FI_TO_FIELD_ID(type, index) (((type) << 12) | (index))
#define FI_GET_TYPE(id) ((id) & 0xF000)

typedef enum FieldRoom {
  /* 0x3000 */ FI_FIELD_ROOM0 = FI_TO_FIELD_ID(FI_FIELDTYPE_ROOM, 0),
  /* 0x3001 */ FI_FIELD_ROOM_SHOP0,
  /* 0x3002 */ FI_FIELD_ROOM_UNK_3002,
  /* 0x3003 */ FI_FIELD_ROOM_UNK_3003,
  /* 0x3004 */ FI_FIELD_ROOM_UNK_3004,
  /* 0x3005 */ FI_FIELD_ROOM_UNK_3005,
  /* 0x3006 */ FI_FIELD_ROOM_SHOP1,
  /* 0x3007 */ FI_FIELD_ROOM_SHOP2,
  /* 0x3008 */ FI_FIELD_ROOM_SHOP3_1,
  /* 0x3009 */ FI_FIELD_ROOM_SHOP3_2,
  /* 0x6000 */ FI_FIELD_PLAYER0_ROOM = FI_TO_FIELD_ID(FI_FIELDTYPE_PLAYER_ROOM, 0),
  /* 0x6001 */ FI_FIELD_PLAYER1_ROOM,
  /* 0x6002 */ FI_FIELD_PLAYER2_ROOM,
  /* 0x6003 */ FI_FIELD_PLAYER3_ROOM
} FieldRoom;

typedef enum FieldDirection {
  /* 0 */ FI_MOVEDIR_NONE,
  /* 1 */ FI_MOVEDIR_RIGHT,
  /* 2 */ FI_MOVEDIR_LEFT,
  /* 3 */ FI_MOVEDIR_UP,
  /* 4 */ FI_MOVEDIR_DOWN,

  /* 5 */ FI_MOVEDIR_MAX
} FieldDirection;

#define FI_GET_PLAYER_ROOM_NO(fieldId) (((fieldId)-FI_FIELD_PLAYER0_ROOM) & 3)
#define FI_IS_PLAYER_ROOM(fieldId) \
  ((fieldId) == FI_FIELD_PLAYER0_ROOM || (fieldId) == FI_FIELD_PLAYER1_ROOM || \
   (fieldId) == FI_FIELD_PLAYER2_ROOM || (fieldId) == FI_FIELD_PLAYER3_ROOM)

void mFI_ClearFieldData(void);
s32 mFI_CheckFieldData(void);
struct FieldMakeBlockInfo* mFI_GetBlockTopP(void);
u16 mFI_GetFieldId(void);
// void func_80087C9C_jp();
// void func_80087D30_jp();
s32 mFI_CheckShopFieldName(u16 fieldName);
s32 mFI_CheckShop(void);
u8 mFI_GetBlockXMax(void);
u8 mFI_GetBlockZMax(void);
// void func_80087ED0_jp();
// void func_80088018_jp();
// s32 mFI_GetBlockNum(s32 blockX, s32 blockZ);
// void func_8008819C_jp();
// s32 mFI_BlockCheck(s32 blockX, s32 blockZ);
// s32 mFI_UtNumCheck(int utX, int utZ, int blockXMax, int blockZMax);
// s32 mFI_WposCheck(xyz_t wpos);
s32 mFI_WposX2UtNumX(f32 wposX);
s32 mFI_WposZ2UtNumZ(f32 wposZ);
s32 mFI_Wpos2UtNum(s32* utX, s32* utZ, xyz_t wpos);
s32 mFI_UtNum2CenterWpos(xyz_t* wpos, int utX, int utZ);
s32 mFI_Wpos2UtCenterWpos(xyz_t* wpos, xyz_t sourcePos);
// s32 mFI_Wpos2UtNum_inBlock(s32* utX, s32* utZ, xyz_t wpos);
s32 mFI_Wpos2BlockNum(s32* blockX, s32* blockZ, xyz_t wpos);
s32 mFI_Wpos2BkandUtNuminBlock(s32* blockX, s32* blockZ, s32* utX, s32* utZ, xyz_t wpos);
// s32 mFI_UtNum2BlockNum(s32* blockX, s32* blockZ, s32 utX, s32 utZ);
// s32 mFI_GetUtNumInBK(s32* blockUtX, s32* blockUtZ, s32 utX, s32 utZ);
// s32 mFI_WpostoLposInBK(xyz_t* lpos, xyz_t wpos);
// s32 mFI_LposInBKtoWpos(xyz_t* wpos, xyz_t lpos, s32 blockX, s32 blockZ);
// s32 mFI_ScrollCheck(xyz_t wpos, u8 dir);
s32 mFI_BkNum2WposXZ(f32* worldPosX, f32* worldPosZ, s32 blockX, s32 blockZ);
void mFI_UtNum2PosXZInBk(f32* posX, f32* posZ, s32 utX, s32 utZ);
// void mFI_BkandUtNum2Wpos(xyz_t* wpos, s32 blockX, s32 blockZ, s32 utX, s32 utZ);
void mFI_BkandUtNum2CenterWpos(xyz_t* wpos, s32 blockX, s32 blockZ, s32 utX, s32 utZ);
// void func_80088CBC_jp();
// void func_80088CD0_jp();
// void func_80088CE4_jp();
// void func_80088D00_jp();
// void func_80088D30_jp();
// void func_80088D78_jp();
// void func_80088D9C_jp();
// void func_80088E08_jp();
// void func_80088E34_jp();
// void func_80088E74_jp();
// void func_80088F14_jp();
// void func_80088F94_jp();
// void func_8008902C_jp();
// void func_8008907C_jp();
// void func_80089114_jp();
// void func_800891AC_jp();
u8 mFI_BkNum2BlockType(s32 blockX, s32 blockZ);
// s32 mFI_GetPuleTypeIdx(u8 type);
s32 mFI_GetPuleIdx(void);
u32 mFI_BkNum2BlockKind(s32 blockX, s32 blockZ);
s32 mFI_CheckBlockKind(s32 blockX, s32 blockZ, u32 blockKind);
s32 mFI_CheckBlockKind_OR(s32 blockX, s32 blockZ, u32 blockKindOr);
s32 mFI_BlockKind2BkNum(s32* blockX, s32* blockZ, u32 kind);
void mFI_GetSpecialBlockNum(s32* blockPos, u32* kinds, s32 count);
mCoBG_unkStructUnion* mFI_GetBkNum2ColTop(s32 blockX, s32 blockZ);
mCoBG_unkStructUnion* mFI_UtNum2UtCol(s32 utX, s32 utZ);
// void func_80089698_jp();
// void func_80089704_jp();
// void func_800897D0_jp();
// void func_80089888_jp();
// void func_800898F4_jp();
// void func_800899CC_jp();
// void func_80089A34_jp();
// void func_80089AAC_jp();
// void func_80089B1C_jp();
// void func_80089B94_jp();
// void func_80089C0C_jp();
// void func_80089CA0_jp();
// void func_80089D18_jp();
// void func_80089D6C_jp();
// void func_80089E84_jp();
// void func_80089EF8_jp();
// void func_8008A000_jp();
u16* mFI_BkNumtoUtFGTop(s32,s32);
// void func_8008A3BC_jp();
// void func_8008A410_jp();
// void func_8008A4F8_jp();
u16* mFI_GetUnitFG(xyz_t);
// void func_8008A608_jp();
// void func_8008A670_jp();
// void func_8008A74C_jp();
// void func_8008A81C_jp();
// void func_8008A960_jp();
UNK_TYPE mFI_SetFG_common(u16 fgName, xyz_t arg1, s32 arg2);
// void func_8008AA98_jp();
// void func_8008AB14_jp();
// void func_8008AC74_jp();
// void func_8008ACA0_jp();
// void func_8008ACBC_jp();
// void func_8008ACD8_jp();
// void func_8008ADCC_jp();
// void func_8008AE70_jp();
// void func_8008B1A0_jp();
// void func_8008B200_jp();
// void func_8008B238_jp();
// void func_8008B26C_jp();
// void func_8008B29C_jp();
// void func_8008B2D0_jp();
// void func_8008B300_jp();
// void func_8008B318_jp();
void mFI_SetBearActor(struct Game_Play* game_play, xyz_t arg1, s32 arg2);
s32 func_8008B3E8_jp(xyz_t* arg0, UNK_TYPE arg1);
// void func_8008B4C0_jp();
// void func_8008B598_jp();
// void func_8008B66C_jp();
s32 func_8008B774_jp(s32,u16*);
// void func_8008B7F4_jp();
// void func_8008B878_jp();
// void func_8008B9F8_jp();
// void func_8008BA74_jp();
// void func_8008BAEC_jp();
// void func_8008BB64_jp();
// void func_8008BBF0_jp();
void mFI_SetMoveActorBitData_ON(s16, u8,u8);
// void func_8008BCFC_jp();
void mFI_MyMoveActorBitData_ON(struct Actor*);
// void func_8008BDCC_jp();
s32 func_8008BE00_jp(struct FieldMakeMoveActor*, s32);
// void func_8008BE38_jp();
// void func_8008BF34_jp();
// void func_8008BFC4_jp();
void mFI_SetPlayerWade(struct Game*);
s32 mFI_CheckPlayerWade(s32);
s32 mFI_GetPlayerWade(void);
s32 mFI_GetNextBlockNum(s32*, s32*);
u16* mFI_GetDepositP(s32,s32);
// void func_8008C344_jp();
// void func_8008C390_jp();
// void func_8008C3B0_jp();
s32 mFI_GetLineDeposit(u16* deposit, s32 utX);
// void func_8008C3E8_jp();
// void func_8008C458_jp();
void mFI_BlockDepositOFF(u16* deposit, s32 utX, s32 utZ);
// void func_8008C498_jp();
// void func_8008C4B8_jp();
// void func_8008C504_jp();
// void func_8008C524_jp();
// void func_8008C548_jp();
// void func_8008C56C_jp();
// void func_8008C5F0_jp();
// void func_8008C610_jp();
// void func_8008C630_jp();
// void func_8008C650_jp();
void mFI_Wpos2DepositOFF(xyz_t);
// void func_8008C708_jp();
// void func_8008C764_jp();
// void func_8008C798_jp();
// void func_8008C830_jp();
// void func_8008C84C_jp();
// void func_8008C8C4_jp();
// void func_8008C938_jp();
// void func_8008C964_jp();
// void func_8008CA14_jp();
// void func_8008CAD8_jp();
// void func_8008CC1C_jp();
// void func_8008CCFC_jp();
// void func_8008CD24_jp();
// void func_8008CD74_jp();
// void func_8008CE00_jp();
// void func_8008CE38_jp();
// void func_8008CEC0_jp();
// void func_8008CFF4_jp();
// void func_8008D12C_jp();
// void func_8008D268_jp();
// void func_8008D3A4_jp();
// void func_8008D574_jp();
u16 mFI_GetOtherFruit(void);
s32 func_8008D7B0_jp(u16);
// void func_8008D884_jp();
s32 mFI_GetWaveUtinBlock(s32* arg0, s32* arg1, s32 arg2, s32 arg3);
// void func_8008DA4C_jp();
void func_8008DCF8_jp(void);
// void func_8008DD0C_jp();
// void func_8008DD3C_jp();
// void func_8008DDC8_jp();
// void func_8008DF04_jp();
// void func_8008E058_jp();
// void func_8008E514_jp();
void func_8008E5F4_jp(xyz_t arg0);
// void mFI_PrintNowBGNum();
// void mFI_PrintFgAttr();
// void func_8008E8E0_jp();
// void func_8008E9C4_jp();
// void func_8008EA5C_jp();

#endif
