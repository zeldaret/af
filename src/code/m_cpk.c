#include "m_cpk.h"
#include "global.h"

#include "6F12E0.h"

extern UNK_TYPE2 D_80104790_jp;
extern UNK_TYPE D_80104794_jp;
extern D80104798Struct* D_80104798_jp;

extern PakInfo* D_801047A4_jp;

extern PakInfo B_80137960_jp;
extern B80137C40Struct B_80137C40_jp;

UNK_RET mCPk_PakOpen(PakInfo* info, s32 arg1) {
    return func_800CD68C_jp(&info->pfs, arg1);
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80078EB4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80078EE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80078F08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80078F34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80078FE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80079030_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80079080_jp.s")

UNK_RET mCPk_InitPak(UNK_TYPE arg0) {
    PakInfo* sp2C;
    PakInfo74Struct* sp28;
    PakInfo94Struct* tmp;
    s32 i;
    s32 temp_s1;

    sp2C = mCPk_get_pkinfo();
    sp2C->unk_00 = 0;

    sp28 = &sp2C->unk_74;
    bzero(sp28, sizeof(PakInfo74Struct));

    tmp = sp2C->unk_94;
    for (i = 0; i < ARRAY_COUNT(sp2C->unk_94); i++) {
        bzero(tmp, sizeof(PakInfo94Struct));
        tmp++;
    }

    func_800CD640_jp(sp28, &D_80104790_jp, &D_80104794_jp);
    bcopy(D_80104798_jp, &sp28->unk_0E, sizeof(D80104798Struct));
    temp_s1 = mCPk_PakOpen(sp2C, arg0);
    func_80079080_jp(&B_80137C40_jp);
    B_80137C40_jp.unk_1200 = 0;
    B_80137C40_jp.unk_1204 = 0;
    B_80137C40_jp.unk_1208 = 0xFFFF;
    return temp_s1;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_8007919C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_8007920C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_800792FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80079378_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_800793A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/mCPk_SavePak.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_8007942C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_800794E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_8007967C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80079708_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80079760_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80079838_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_800798DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80079A24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80079AAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80079B28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80079BF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80079D00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80079D50_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80079E14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80079E54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80079EA4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80079EDC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80079F44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_8007A008_jp.s")

PakInfo* mCPk_get_pkinfo(void) {
    return D_801047A4_jp;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_8007A080_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/RO_80116800_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/RO_STR_80116804_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/RO_80116808_jp.s")
