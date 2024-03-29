#ifndef M_ALL_GROW_H
#define M_ALL_GROW_H

#include "ultra64.h"

struct Foreground;
struct gfxprint;
struct lbRTC_time_c;

#define AGrw_DUMP_WIDTH 4
#define AGrw_DUMP_HEIGHT 4

typedef enum mAGrw_XMAS_PROC {
  /* 0 */ AGrw_XMAS_PROC_CLEAR,
  /* 1 */ AGrw_XMAS_PROC_SET,

  /* 2 */ mAGrw_XMAS_PROC_NUM
} mAGrw_XMAS_PROC;

typedef enum mAGrw_FRUIT {
  /* 0 */ AGrw_FRUIT_APPLE,
  /* 1 */ AGrw_FRUIT_CHERRY,
  /* 2 */ AGrw_FRUIT_PEAR,
  /* 3 */ AGrw_FRUIT_PEACH,
  /* 4 */ AGrw_FRUIT_ORANGE,

  /* 5 */ AGrw_FRUIT_NUM
} mAGrw_FRUIT;

#define AGrw_XMAS_LIGHTS_MAX_BLOCK 3
#define AGrw_CEDAR_BLOCK_Z_MIN 0
#define AGrw_CEDAR_BLOCK_Z_MAX 3 // [min, max)
#define AGrw_FOSSIL_NUM 5
#define AGrw_HANIWA_NUM 3

typedef struct AllGrowBlock {
    /* 0x0 */ u8 blockX;
    /* 0x1 */ u8 blockZ;
} AllGrowBlock; // size 0x2


void mAGrw_ClearDebugData(void);
s32 mAGrw_CheckRegistedData_debug(AllGrowBlock* blockInfo, s32 num, s32 blockX, s32 blockZ);
void mAGrw_SetBlockData_debug(AllGrowBlock* blockInfo, s32 num, s32 blockX, s32 blockZ);
void mAGrw_SetDebugDataBlock(u16* fgItems, u16* deposit, AllGrowBlock* fossilBlockInfo, s32 fossilMax, s32* fossilNum,
                             AllGrowBlock* haniwaBlockInfo, s32 haniwaMax, s32* haniwaNum, s32 blockX, s32 blockZ);
void mAGrw_SetDebugData(void);
void mAGrw_PrintFossilHaniwa_debug(struct gfxprint* gfxprint);
s32 mAGrw_CheckKabuPeddler(void);
void mAGrw_OrderSetHaniwa(void);
u8 func_80055E34_jp(u16* items);
void mAGrw_ChangeItemBlock(u16* blockItems, u16 newItem, u16 targetItem, u8 possibleNum);
void mAGrw_ChangeItemBlock2(u16* blockItems, u16 newItem, u8 possibleNum);
s32 mAGrw_CheckPutXmasTree(struct lbRTC_time_c* time);
void mAGrw_SetXmasTreeBlock(u16* blockItems);
void mAGrw_ClearXmasTreeBlock(u16* blockItems);
void mAGrw_XmasTreeField(s32 type);
void mAGrw_SetXmasTree(void);
void mAGrw_RenewalFgItem(struct lbRTC_time_c* time);
void mAGrw_ChangeTree2OtherBlock(u16* items, u16 other);
void mAGrw_ChangeTree2FruitTreeLine(struct Foreground* fg, u16 fruitTree);
void mAGrw_ChangeTree2FruitTree(void);


#endif
