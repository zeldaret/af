#include "global.h"

#include "s_cpak.h"

#include "padmgr.h"

void func_800CD640_jp(PakInfo74Struct* arg0, s16* arg1, s32* arg2) {
    bcopy(arg1, &arg0->unk_08, 2);
    bcopy(arg2, &arg0->unk_04, 4);
}

s32 func_800CD68C_jp(PakInfo04Struct* arg0, s32 channel) {
    OSMesgQueue* queue;
    s32 sp20;
    s32 sp1C = FALSE;

    queue = padmgr_LockSerialMesgQ();
    sp20 = osPfsInitPak(queue, &arg0->pfs, channel);

    if (sp20 == 0) {
        sp1C = TRUE;
    }

    if (sp20 == PFS_ERR_DEVICE) {
        if (osMotorInit(queue, &arg0->pfs, channel) != 0) {
            if (osGbpakInit(queue, &arg0->pfs, channel) != 0) {
                sp20 = PFS_ERR_ID_FATAL;
            }
        }
    }

    arg0->unk_6C = sp20;
    padmgr_UnlockSerialMesgQ(queue);

    return sp1C;
}

size_t func_800CD730_jp(PakInfo04Struct* arg0) {
    s32 bytes;

    arg0->unk_6C = osPfsFreeBlocks(&arg0->pfs, &bytes);
    return bytes;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/s_cpak/func_800CD760_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/s_cpak/func_800CD82C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/s_cpak/func_800CD8F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/s_cpak/func_800CD990_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/s_cpak/func_800CD9F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/s_cpak/func_800CDA4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/s_cpak/func_800CDA90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/s_cpak/func_800CDAD0_jp.s")
