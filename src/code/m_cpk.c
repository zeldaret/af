#include "m_cpk.h"
#include "global.h"

#include "m_flashrom.h"
#include "m_lib.h"
#include "m_malloc.h"

#include "padmgr.h"

#include "6B8F20.h"
#include "6F12E0.h"

extern UNK_TYPE2 D_80104790_jp;
extern UNK_TYPE D_80104794_jp;
extern D80104798Struct* D_80104798_jp;
extern char* D_8010479C_jp[2];

extern PakInfo* D_801047A4_jp;

extern s32 RO_80116808_jp[2];

extern PakInfo B_80137960_jp;
extern B80137C40Struct B_80137C40_jp;

UNK_RET mCPk_PakOpen(PakInfo* info, s32 arg1) {
    return func_800CD68C_jp(&info->unk_04, arg1);
}

UNK_RET func_80078EB4_jp(PakInfo* info) {
    return func_800CD8F8_jp(&info->unk_04, &info->unk_74, info->unk_74.unk_00);
}

UNK_RET func_80078EE0_jp(PakInfo* info) {
    return func_800CD990_jp(&info->unk_04, &info->unk_74);
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80078F08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80078F34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80078FE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80079030_jp.s")

void func_80079080_jp(B80137C40Struct* arg0) {
    arg0->unk_0000.unk_0000 = 0;
    mPr_ClearPrivateInfo(&arg0->unk_0000.priv);
    mNpc_ClearAnimalInfo(&arg0->unk_0000.animal);
    arg0->unk_0000.unk_1100 = 0xFFFF;
}

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
    B_80137C40_jp.unk_1200 = NULL;
    B_80137C40_jp.unk_1204 = 0;
    B_80137C40_jp.unk_1208 = 0xFFFF;
    return temp_s1;
}

void func_8007919C_jp(PakInfo* info, u8 arg1) {
    PakInfo74Struct* sp20 = &info->unk_74;

    if (arg1 < 2) {
        bcopy(D_8010479C_jp[arg1], sp20->unk_0A, sizeof(sp20->unk_0A));
        sp20->unk_00 = RO_80116808_jp[arg1];
    }
}

UNK_RET func_8007920C_jp(PakInfo* info, B80137C40Struct* arg1) {
    s32 var_v0;
    s32 var_s1;
    s32 tmp;

    for (var_s1 = 0; var_s1 < 1; var_s1++) {
        PakInfo04Struct* temp_s3 = &info->unk_04;

        B_80137C40_jp.unk_1200 = padmgr_LockSerialMesgQ();
        var_v0 = func_80078EE0_jp(info);

        if (temp_s3->unk_6C == 5) {
            var_v0 = func_80078EB4_jp(info);
        }

        if ((var_v0 == 1) || (temp_s3->unk_6C == 9)) {
            tmp = info->unk_74.unk_00;
            var_v0 = func_800CD760_jp(temp_s3, 0, tmp, arg1);
        }
        padmgr_UnlockSerialMesgQ(B_80137C40_jp.unk_1200);
    }

    return var_v0;
}

UNK_RET func_800792FC_jp(PakInfo* info, B80137C40Struct* arg1) {
    s32 sp1C;
    s32 tmp;

    B_80137C40_jp.unk_1200 = padmgr_LockSerialMesgQ();
    sp1C = func_80078EE0_jp(info);

    if (sp1C == 1) {
        tmp = info->unk_74.unk_00;
        sp1C = func_800CD82C_jp(&info->unk_04, 0, tmp, arg1);
        if (sp1C == 0) {
            sp1C = -1;
        }
    }

    padmgr_UnlockSerialMesgQ(B_80137C40_jp.unk_1200);

    return sp1C;
}

void func_80079378_jp(PrivateInfo* priv) {
    if (priv != NULL) {
        mem_copy((void*)&B_80137C40_jp.unk_0000.priv, (void*)priv, sizeof(PrivateInfo));
    }
}

PrivateInfo* func_800793A8_jp(void) {
    return &B_80137C40_jp.unk_0000.priv;
}

s32 mCPk_SavePak(PrivateInfo* priv, Animal_c* animal, PakInfo* info) {
    func_8007919C_jp(info, 0);
    func_80079378_jp(priv);
    mem_copy((void*)&B_80137C40_jp.unk_0000.animal, (void*)animal, sizeof(Animal_c));
    B_80137C40_jp.unk_0000.unk_0000 =
        func_8008EEB4_jp(&B_80137C40_jp.unk_0000, sizeof(B80137C40Unk0000Struct), B_80137C40_jp.unk_0000.unk_0000);

    return func_8007920C_jp(info, &B_80137C40_jp);
}

s32 func_8007942C_jp(PrivateInfo* priv, Animal_c* animal, PakInfo* info) {
    s32 sp1C;

    func_8007919C_jp(info, 0);
    sp1C = func_800792FC_jp(info, &B_80137C40_jp);

    if (sp1C == 1) {
        B_80137C40_jp.unk_1204 = 1;
    }

    if (sp1C == 1) {
        if (mPr_CheckPrivate(&B_80137C40_jp.unk_0000.priv) == TRUE) {
            mem_copy((void*)priv, (void*)&B_80137C40_jp.unk_0000.priv, sizeof(PrivateInfo));
            mem_copy((void*)animal, (void*)&B_80137C40_jp.unk_0000.animal, sizeof(Animal_c));
        } else {
            sp1C = 0;
        }
    } else {
        sp1C = 0;
    }

    return sp1C;
}

s32 func_800794E4_jp(s32*, s32, PakInfo*, void*);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_800794E4_jp.s")

s32 func_8007967C_jp(s32*, s32, PakInfo*);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_8007967C_jp.s")

s32 func_80079708_jp(s32);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80079708_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80079760_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80079838_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_800798DC_jp.s")

UNK_RET func_80079A24_jp(PakInfo* info);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80079A24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80079AAC_jp.s")

void func_80079B28_jp(UNK_PTR arg0, s32 arg1, PakInfo* arg2) {
    UNUSED s32 pad[2];
    s32 temp_v0;
    OSMesgQueue* sp20;
    PakInfo* sp1C;

    temp_v0 = func_80079EA4_jp(arg0, arg2);
    if (temp_v0 == 1) {
        if (func_8008EE7C_jp(arg0, arg1) != 0) {
            func_8007919C_jp(arg2, 1);
            sp20 = padmgr_LockSerialMesgQ();
            func_800CD9F0_jp(&arg2->unk_04, &arg2->unk_74);
            padmgr_UnlockSerialMesgQ(sp20);
        }
    } else if (temp_v0 == -1) {
        sp1C = mCPk_get_pkinfo();
        func_8007919C_jp(sp1C, 1);
        B_80137C40_jp.unk_1200 = padmgr_LockSerialMesgQ();
        func_800CD9F0_jp(&sp1C->unk_04, &sp1C->unk_74);
        padmgr_UnlockSerialMesgQ(B_80137C40_jp.unk_1200);
    }
}

s32 func_80079BF8_jp(PakInfo* info) {
    UNUSED s32 pad;
    s32 sp28;
    s32 sp24 = 0;
    UNK_PTR sp20;

    if (!mLd_PlayerManKindCheck()) {
        func_8007919C_jp(info, 1);
        sp20 = zelda_malloc(info->unk_74.unk_00);
        if (sp20 != NULL) {
            func_80079B28_jp(sp20, info->unk_74.unk_00, info);
        }
        if (func_800794E4_jp(&sp28, 1, info, sp20) == 1) {
            sp24 = func_80079708_jp(sp28);
        }
        if (sp20 != NULL) {
            zelda_free(sp20);
        }
    } else if (func_800966E0_jp() == 1) {
        func_8007919C_jp(info, 0);
        if (func_80079A24_jp(info) == 1) {
            if (func_8007967C_jp(&sp28, 0, info) == 1) {
                sp24 = func_80079708_jp(sp28);
            }
        } else {
            sp24 = 1;
        }
    }

    return sp24;
}

UNK_RET func_80079D00_jp(void) {
    PakInfo* sp1C = mCPk_get_pkinfo();
    s32 sp18 = 0;

    if (mCPk_PakOpen(sp1C, 0) == 1) {
        sp18 = func_80079BF8_jp(sp1C);
    }

    return sp18;
}

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

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/RO_STR_80116800_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/RO_STR_80116804_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/RO_80116808_jp.s")
