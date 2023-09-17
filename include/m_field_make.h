#ifndef M_FIELD_MAKE_H
#define M_FIELD_MAKE_H

#include "ultra64.h"

struct Game;

#define BLOCK_X_NUM 7
#define BLOCK_Z_NUM 10
#define BLOCK_TOTAL_NUM (BLOCK_X_NUM * BLOCK_Z_NUM)

#define FG_BLOCK_X_NUM (BLOCK_X_NUM - 2) /* 5 */
#define FG_BLOCK_Z_NUM (BLOCK_Z_NUM - 4) /* 6 */
#define FG_BLOCK_TOTAL_NUM (FG_BLOCK_X_NUM * FG_BLOCK_Z_NUM)

#define UT_BASE_NUM 16
#define UT_X_NUM UT_BASE_NUM /* Spaces per block (acre) in x direction */
#define UT_Z_NUM UT_BASE_NUM /* Spaces per block (acre) in z direction */
#define UT_TOTAL_NUM (UT_X_NUM * UT_Z_NUM)

typedef struct mFM_fg_c {
  /* 0x000 */ u16 items[UT_Z_NUM][UT_X_NUM];
} mFM_fg_c; // size = 0x200

// void func_80084ED0_jp();
// void func_80084FAC_jp();
// void func_800850E4_jp();
// void func_80085178_jp();
// void func_800851C8_jp();
// void func_800853CC_jp();
// void func_80085490_jp();
// void func_8008557C_jp();
// void func_800855D0_jp();
// void func_80085918_jp();
// void func_800859F4_jp();
// void func_80085A84_jp();
// void func_80085B40_jp();
// void func_80085CC0_jp();
// void func_80085D44_jp();
// void func_80085D64_jp();
// void func_80085D94_jp();
// void func_80085FF0_jp();
// void func_8008609C_jp();
// void func_800862DC_jp();
// void func_8008640C_jp();
// void func_800865D0_jp();
// void func_800867F0_jp();
// void func_80086BD0_jp();
// void func_80086CA4_jp();
// void func_80086D44_jp();
// void func_80086DE0_jp();
// void func_80086E30_jp();
// void func_80086F08_jp();
// void func_80086FA8_jp();
// void func_80086FEC_jp();
void func_80087004_jp(void);
void func_80087280_jp(void);
// void func_80087380_jp();
void mFM_SetBlockKindLoadCombi(struct Game* game);
void mFM_InitFgCombiSaveData(struct Game* game);
// void func_80087754_jp();
// void func_8008775C_jp();
// void func_80087788_jp();
// void func_800877CC_jp();
void mFM_RenewalReserve(void);
// void func_800879B0_jp();

#endif
