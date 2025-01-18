#include "m_cpk.h"
#include "global.h"

#include "m_flashrom.h"
#include "m_lib.h"
#include "m_malloc.h"

#include "padmgr.h"

#include "6B8F20.h"
#include "6F12E0.h"

extern PakInfo B_80137960_jp;
extern B80137C40Struct B_80137C40_jp;

extern D80104798Struct D_8010EF70_jp;

UNK_TYPE2 D_80104790_jp = 0x3031;
UNK_TYPE D_80104794_jp = 0x4E41464A;
D80104798Struct* D_80104798_jp = &D_8010EF70_jp;
char* D_8010479C_jp[2] = { "\x1A", "\x1B" };
PakInfo* D_801047A4_jp = &B_80137960_jp;
D801047A8Struct D_801047A8_jp = { { 0xD4, 0x8E, 0xA6, 0x90, 0x85, 0x42, 0x00, 0x00 } };

const size_t RO_80116808_jp[2] = { 0x1200, 0x6700 };

UNK_RET mCPk_PakOpen(PakInfo* info, s32 arg1) {
    return func_800CD68C_jp(&info->unk_04, arg1);
}

UNK_RET func_80078EB4_jp(PakInfo* info) {
    return func_800CD8F8_jp(&info->unk_04, &info->unk_74, info->unk_74.unk_00);
}

UNK_RET func_80078EE0_jp(PakInfo* info) {
    return func_800CD990_jp(&info->unk_04, &info->unk_74);
}

UNK_RET func_80078F08_jp(PakInfo* info) {
    return func_800CDA90_jp(&info->unk_04, &info->unk_2D8, &info->unk_2DC);
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80078F34_jp.s")

s32 func_80078FE8_jp(PakInfo* info) {
    s32 sp1C = FALSE;

    info->unk_2D4 = func_800CD730_jp(&info->unk_04);
    if (info->unk_04.unk_6C == 0) {
        sp1C = TRUE;
    }
    return sp1C;
}

s32 func_80079030_jp(PakInfo* info) {
    s32 sp1C = FALSE;

    if ((func_80078FE8_jp(info) == TRUE) && (info->unk_2D4 >= info->unk_74.unk_00)) {
        sp1C = TRUE;
    }
    return sp1C;
}

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
    u32 tmp;

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

s32 func_800792FC_jp(PakInfo* info, void* arg1) {
    s32 sp1C;
    u32 tmp;

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

UNK_RET func_800794E4_jp(s32* arg0, s32 arg1, PakInfo* arg2, void* arg3) {
    PakInfo04Struct* unkStruct = &arg2->unk_04;
    void* var_a3;
    s32 sp24 = 0;
    UNUSED s32 pad[2];

    *arg0 = 5;
    B_80137C40_jp.unk_1200 = padmgr_LockSerialMesgQ();
    if ((func_80078EE0_jp(arg2) == 1) || (unkStruct->unk_6C == 9)) {
        var_a3 = (arg1 == 0) ? &B_80137C40_jp : arg3;
        if ((var_a3 != NULL) && (func_800CD82C_jp(unkStruct, 0, arg2->unk_74.unk_00, var_a3) == 1)) {
            if (arg1 == 0) {
                if (!mPr_NullCheckPersonalID(&B_80137C40_jp.unk_0000.priv.playerId)) {
                    B_80137C40_jp.unk_1204 = 1;
                    *arg0 = 0;
                } else {
                    *arg0 = 2;
                }
            } else {
                *arg0 = 2;
            }
            sp24 = 1;
        }
    } else if (unkStruct->unk_6C == 5) {
        if ((func_80078F08_jp(arg2) == 1) && (arg2->unk_2DC >= 0x10)) {
            *arg0 = 4;
            sp24 = 1;
        } else if (func_80079030_jp(arg2) == TRUE) {
            *arg0 = 1;
            sp24 = 1;
        } else if (unkStruct->unk_6C == 0) {
            *arg0 = 3;
            sp24 = 1;
        }
    }
    padmgr_UnlockSerialMesgQ(B_80137C40_jp.unk_1200);
    return sp24;
}

UNK_RET func_8007967C_jp(s32* arg0, s32 arg1, PakInfo* arg2) {
    UNUSED s32 pad;
    s32 sp20;
    void* sp1C;

    if (arg1 == 0) {
        sp1C = &B_80137C40_jp;
    } else {
        sp1C = zelda_malloc(arg2->unk_74.unk_00);
    }

    sp20 = func_800794E4_jp(arg0, arg1, arg2, sp1C);
    if ((arg1 != 0) && (sp1C != NULL)) {
        zelda_free(sp1C);
    }

    return sp20;
}

UNK_RET func_80079708_jp(s32 arg0) {
    s32 var_v1;

    switch (arg0) {
        case 0:
            var_v1 = 4;
            break;

        case 1:
        case 2:
            var_v1 = 3;
            break;

        case 3:
            var_v1 = 2;
            break;

        case 4:
            var_v1 = 6;
            break;

        case 5:
            var_v1 = 5;
            break;

        default:
            var_v1 = 5;
            break;
    }

    return var_v1;
}

s32 func_80079760_jp(void) {
    PakInfo* info = mCPk_get_pkinfo();
    PrivateInfo* iter = &common_data.save.saveFilePrivateInfo[0];
    s32 sp34 = -1;
    s32 temp_v0_2;
    s32 i;

    func_8007919C_jp(info, 0);

    temp_v0_2 = func_800792FC_jp(info, &B_80137C40_jp);

    if (temp_v0_2 == 1) {
        B_80137C40_jp.unk_1204 = 1;
    }

    if ((temp_v0_2 == 1) && !mPr_NullCheckPersonalID(&B_80137C40_jp.unk_0000.priv.playerId)) {
        sp34 = 4;
        for (i = 0; i < ARRAY_COUNT(common_data.save.saveFilePrivateInfo); i++) {
            if (mPr_CheckCmpPrivate(&B_80137C40_jp.unk_0000.priv, iter) == TRUE) {
                sp34 = i;
                break;
            }
            iter++;
        }
    }

    return sp34;
}

void* func_80079838_jp(void) {
    PersonalID_c* var_s0 = NULL;
    PakInfo* info = mCPk_get_pkinfo();
    void* sp24 = &D_801047A8_jp;

    if (B_80137C40_jp.unk_1204 == 0) {
        func_8007919C_jp(info, 0);
        if (func_800792FC_jp(info, &B_80137C40_jp) == 1) {
            B_80137C40_jp.unk_1204 = 1;
            var_s0 = &B_80137C40_jp.unk_0000.priv.playerId;
        }
    } else {
        var_s0 = &B_80137C40_jp.unk_0000.priv.playerId;
    }

    if ((var_s0 != NULL) && !mPr_NullCheckPersonalID(var_s0)) {
        sp24 = var_s0;
    }

    return sp24;
}

s32 func_800798DC_jp(PakInfo* info) {
    UNUSED s32 pad;
    u32 temp_v0;
    s32 sp24 = FALSE;

    if (B_80137C40_jp.unk_1204 == 0) {
        func_8007919C_jp(info, 0);
        if (func_800792FC_jp(info, &B_80137C40_jp) == 1) {
            B_80137C40_jp.unk_1204 = 1;
        }
    }
    if (B_80137C40_jp.unk_1204 == 1) {
        temp_v0 = fqrand() * 65534.0f;
        B_80137C40_jp.unk_1208 = temp_v0;
        B_80137C40_jp.unk_0000.unk_1100 = temp_v0;
        B_80137C40_jp.unk_0000.unk_0000 =
            func_8008EEB4_jp(&B_80137C40_jp, sizeof(B80137C40Unk0000Struct), B_80137C40_jp.unk_0000.unk_0000);

        if (func_8007920C_jp(info, &B_80137C40_jp) == 1) {
            sp24 = TRUE;
        }
    }
    return sp24;
}

s32 func_80079A24_jp(PakInfo* info) {
    s32 sp1C;

    if (B_80137C40_jp.unk_1208 != 0xFFFF) {
        sp1C = FALSE;
        func_8007919C_jp(info, 0);
        if (func_800792FC_jp(info, &B_80137C40_jp) == 1) {
            B_80137C40_jp.unk_1204 = 1;
            if (B_80137C40_jp.unk_1208 == B_80137C40_jp.unk_0000.unk_1100) {
                sp1C = TRUE;
            }
        }
    } else {
        sp1C = TRUE;
    }
    return sp1C;
}

UNK_RET func_80079AAC_jp(void) {
    PakInfo* info = mCPk_get_pkinfo();
    s32 sp20 = 0;
    s32 sp1C;

    func_8007919C_jp(info, 0);

    if (func_80079A24_jp(info) == 1) {
        if (func_8007967C_jp(&sp1C, 0, info) == 1) {
            sp20 = func_80079708_jp(sp1C);
        }
    } else {
        sp20 = 1;
    }

    return sp20;
}

void func_80079B28_jp(UNK_PTR arg0, u32 arg1, PakInfo* arg2) {
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

UNK_RET func_80079BF8_jp(PakInfo* info) {
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

s32 func_80079D50_jp(void*, PakInfo* info, u8*);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80079D50_jp.s")

s32 func_80079E14_jp(void*, PakInfo* info, u8*);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80079E14_jp.s")

typedef s32 (*D801047B0Func)(void*, PakInfo*, u8*);
D801047B0Func D_801047B0_jp[2] = { func_80079D50_jp, func_80079E14_jp };

s32 func_80079E54_jp(void* arg0, PakInfo* arg1) {
    static u8 D_801047B8_jp = 0;

    if (D_801047B8_jp >= ARRAY_COUNT(D_801047B0_jp)) {
        D_801047B8_jp = 0;
    }

    return D_801047B0_jp[D_801047B8_jp](arg0, arg1, &D_801047B8_jp);
}

s32 func_80079EA4_jp(UNK_PTR arg0, PakInfo* info) {
    func_8007919C_jp(info, 1);
    return func_800792FC_jp(info, arg0);
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80079EDC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_80079F44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_8007A008_jp.s")

PakInfo* mCPk_get_pkinfo(void) {
    return D_801047A4_jp;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_cpk/func_8007A080_jp.s")
