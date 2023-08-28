#include "libu64/mtxconv.h"

void MtxConv_F2L(Mtx* mtx, MtxF* mf) {
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            s32 value = (mf->mf[i][j] * 0x10000);
            u16(*intPart)[4] = (u16(*)[4])mtx->m;
            u16(*fracPart)[4] = (u16(*)[4])mtx->m[2];

            intPart[i][j] = value >> 16;
            fracPart[i][j] = value;
        }
    }
}

void MtxConv_L2F(MtxF* mf, Mtx* mtx) {
    guMtxL2F(mf->mf, mtx);
}
