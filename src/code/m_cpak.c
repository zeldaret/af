#include "m_cpak.h"
#include "global.h"

#include "m_flashrom.h"
#include "m_lib.h"
#include "m_malloc.h"

#include "padmgr.h"

#include "6B8F20.h"
#include "s_cpak.h"

extern PakInfo l_paks_info;
extern B80137C40Struct B_80137C40_jp;

extern char D_8010EF70_jp[];

u16 D_80104790_jp = 0x3031;
u32 D_80104794_jp = 0x4E41464A;
char* D_80104798_jp = D_8010EF70_jp;
char* D_8010479C_jp[2] = { "\x1A", "\x1B" };
PakInfo* g_paks_info_p = &l_paks_info;
D801047A8Struct D_801047A8_jp = { { 0xD4, 0x8E, 0xA6, 0x90, 0x85, 0x42, 0x00, 0x00 } };

const size_t RO_80116808_jp[2] = { sizeof(B80137C40Unk0000Struct), sizeof(D801047B0Struct) };

s32 mCPk_PakOpen(PakInfo* info, s32 channel) {
    return func_800CD68C_jp(&info->pfsInfo, channel);
}

s32 func_80078EB4_jp(PakInfo* info) {
    return func_800CD8F8_jp(&info->pfsInfo, &info->pfsState, info->pfsState.file_size);
}

s32 func_80078EE0_jp(PakInfo* info) {
    return func_800CD990_jp(&info->pfsInfo, &info->pfsState);
}

s32 func_80078F08_jp(PakInfo* info) {
    return func_800CDA90_jp(&info->pfsInfo, &info->max_files, &info->files_used);
}

s32 func_80078F34_jp(PakInfo* info) {
    OSPfsInfo* pfsInfo = &info->pfsInfo;
    OSPfsState* pfsStates = info->unk_94;
    s32* var_s1 = info->unk_294;
    s32 i;
    u32 file_size;

    for (i = 0; i < ARRAY_COUNT(info->unk_94); i++) {
        var_s1[i] = 0;
        pfsInfo->file_no = i;
        file_size = func_800CDA4C_jp(pfsInfo, &pfsStates[i]);
        if (file_size == 0) {
            if (pfsInfo->err == PFS_ERR_INVALID) {
                var_s1[i] = -1;
                continue;
            }

            return file_size;
        }
    }

    return file_size;
}

s32 func_80078FE8_jp(PakInfo* info) {
    s32 sp1C = FALSE;

    info->unk_2D4 = func_800CD730_jp(&info->pfsInfo);
    if (info->pfsInfo.err == 0) {
        sp1C = TRUE;
    }
    return sp1C;
}

s32 func_80079030_jp(PakInfo* info) {
    s32 sp1C = FALSE;

    if ((func_80078FE8_jp(info) == TRUE) && (info->unk_2D4 >= info->pfsState.file_size)) {
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

s32 mCPk_InitPak(s32 channel) {
    PakInfo* info = mCPk_get_pkinfo();
    OSPfsState* pfsState;
    OSPfsState* iter;
    s32 i;
    s32 ret;

    info->unk_00 = 0;

    pfsState = &info->pfsState;
    bzero(pfsState, sizeof(OSPfsState));

    iter = info->unk_94;
    for (i = 0; i < ARRAY_COUNT(info->unk_94); i++) {
        bzero(iter, sizeof(OSPfsState));
        iter++;
    }

    func_800CD640_jp(pfsState, &D_80104790_jp, &D_80104794_jp);

    bcopy(D_80104798_jp, &pfsState->game_name, sizeof(pfsState->game_name));

    ret = mCPk_PakOpen(info, channel);

    func_80079080_jp(&B_80137C40_jp);

    B_80137C40_jp.unk_1200 = NULL;
    B_80137C40_jp.unk_1204 = 0;
    B_80137C40_jp.unk_1208 = 0xFFFF;

    return ret;
}

void func_8007919C_jp(PakInfo* info, u8 arg1) {
    OSPfsState* pfsState = &info->pfsState;

    if (arg1 < ARRAY_COUNT(D_8010479C_jp)) {
        bcopy(D_8010479C_jp[arg1], pfsState->ext_name, sizeof(pfsState->ext_name));
        pfsState->file_size = RO_80116808_jp[arg1];
    }
}

UNK_RET func_8007920C_jp(PakInfo* info, void* arg1) {
    s32 var_v0;
    s32 var_s1;
    u32 file_size;

    for (var_s1 = 0; var_s1 < 1; var_s1++) {
        OSPfsInfo* pfsInfo = &info->pfsInfo;

        B_80137C40_jp.unk_1200 = padmgr_LockSerialMesgQ();
        var_v0 = func_80078EE0_jp(info);

        if (pfsInfo->err == PFS_ERR_INVALID) {
            var_v0 = func_80078EB4_jp(info);
        }

        if ((var_v0 == 1) || (pfsInfo->err == PFS_ERR_EXIST)) {
            file_size = info->pfsState.file_size;
            var_v0 = func_800CD760_jp(pfsInfo, 0, file_size, arg1);
        }
        padmgr_UnlockSerialMesgQ(B_80137C40_jp.unk_1200);
    }

    return var_v0;
}

s32 func_800792FC_jp(PakInfo* info, void* arg1) {
    s32 sp1C;
    u32 file_size;

    B_80137C40_jp.unk_1200 = padmgr_LockSerialMesgQ();
    sp1C = func_80078EE0_jp(info);

    if (sp1C == 1) {
        file_size = info->pfsState.file_size;
        sp1C = func_800CD82C_jp(&info->pfsInfo, 0, file_size, arg1);
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

s32 func_800794E4_jp(s32* arg0, s32 arg1, PakInfo* info, void* arg3) {
    OSPfsInfo* pfsInfo = &info->pfsInfo;
    void* var_a3;
    s32 sp24 = FALSE;
    UNUSED s32 pad[2];

    *arg0 = 5;
    B_80137C40_jp.unk_1200 = padmgr_LockSerialMesgQ();
    if ((func_80078EE0_jp(info) == 1) || (pfsInfo->err == PFS_ERR_EXIST)) {
        var_a3 = (arg1 == 0) ? &B_80137C40_jp : arg3;
        if ((var_a3 != NULL) && (func_800CD82C_jp(pfsInfo, 0, info->pfsState.file_size, var_a3) == 1)) {
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
            sp24 = TRUE;
        }
    } else if (pfsInfo->err == PFS_ERR_INVALID) {
        if ((func_80078F08_jp(info) == 1) && (info->files_used >= 0x10)) {
            *arg0 = 4;
            sp24 = TRUE;
        } else if (func_80079030_jp(info) == TRUE) {
            *arg0 = 1;
            sp24 = TRUE;
        } else if (pfsInfo->err == 0) {
            *arg0 = 3;
            sp24 = TRUE;
        }
    }
    padmgr_UnlockSerialMesgQ(B_80137C40_jp.unk_1200);
    return sp24;
}

s32 func_8007967C_jp(s32* arg0, s32 arg1, PakInfo* info) {
    UNUSED s32 pad;
    s32 sp20;
    void* sp1C;

    if (arg1 == 0) {
        sp1C = &B_80137C40_jp;
    } else {
        sp1C = zelda_malloc(info->pfsState.file_size);
    }

    sp20 = func_800794E4_jp(arg0, arg1, info, sp1C);
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
    PersonalID_c* id = NULL;
    PakInfo* info = mCPk_get_pkinfo();
    void* sp24 = &D_801047A8_jp;

    if (B_80137C40_jp.unk_1204 == 0) {
        func_8007919C_jp(info, 0);
        if (func_800792FC_jp(info, &B_80137C40_jp) == 1) {
            B_80137C40_jp.unk_1204 = 1;
            id = &B_80137C40_jp.unk_0000.priv.playerId;
        }
    } else {
        id = &B_80137C40_jp.unk_0000.priv.playerId;
    }

    if ((id != NULL) && !mPr_NullCheckPersonalID(id)) {
        sp24 = id;
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

void func_80079B28_jp(UNK_PTR arg0, u32 arg1, PakInfo* info) {
    UNUSED s32 pad[2];
    s32 temp_v0 = func_80079EA4_jp(arg0, info);
    OSMesgQueue* queue;
    PakInfo* info2;

    if (temp_v0 == 1) {
        if (func_8008EE7C_jp(arg0, arg1) != 0) {
            func_8007919C_jp(info, 1);
            queue = padmgr_LockSerialMesgQ();
            func_800CD9F0_jp(&info->pfsInfo, &info->pfsState);
            padmgr_UnlockSerialMesgQ(queue);
        }
    } else if (temp_v0 == -1) {
        info2 = mCPk_get_pkinfo();
        func_8007919C_jp(info2, 1);
        B_80137C40_jp.unk_1200 = padmgr_LockSerialMesgQ();
        func_800CD9F0_jp(&info2->pfsInfo, &info2->pfsState);
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
        sp20 = zelda_malloc(info->pfsState.file_size);
        if (sp20 != NULL) {
            func_80079B28_jp(sp20, info->pfsState.file_size, info);
        }
        if (func_800794E4_jp(&sp28, 1, info, sp20) == TRUE) {
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
    PakInfo* info = mCPk_get_pkinfo();
    s32 sp18 = 0;

    if (mCPk_PakOpen(info, 0) == TRUE) {
        sp18 = func_80079BF8_jp(info);
    }

    return sp18;
}

s32 func_80079D50_jp(D801047B0Struct* arg0, PakInfo* info, u8* index) {
    func_8007919C_jp(info, 1);
    arg0->unk_0000 = func_8008EEB4_jp(arg0, sizeof(D801047B0Struct), arg0->unk_0000);
    if (func_8007920C_jp(info, arg0) == 1) {
        if (mLd_PlayerManKindCheck()) {
            if (mCPk_SavePak(common_data.privateInfo, mNpc_GetInAnimalP(), info) == 1) {
                *index = 1;
                return 0;
            }
            return -1;
        }

        *index = 1;
        return 0;
    }

    *index = 0;
    return -1;
}

s32 func_80079E14_jp(UNUSED D801047B0Struct* arg0, UNUSED PakInfo* info, u8* arg2) {
    s32 temp_v0 = func_80090044_jp();

    if (temp_v0 != 0) {
        *arg2 = 0;
    }

    return temp_v0;
}

typedef s32 (*D801047B0Func)(D801047B0Struct*, PakInfo*, u8*);
D801047B0Func D_801047B0_jp[2] = { func_80079D50_jp, func_80079E14_jp };

s32 func_80079E54_jp(D801047B0Struct* arg0, PakInfo* info) {
    static u8 D_801047B8_jp = 0;

    if (D_801047B8_jp >= ARRAY_COUNT(D_801047B0_jp)) {
        D_801047B8_jp = 0;
    }

    return D_801047B0_jp[D_801047B8_jp](arg0, info, &D_801047B8_jp);
}

s32 func_80079EA4_jp(UNK_PTR arg0, PakInfo* info) {
    func_8007919C_jp(info, 1);
    return func_800792FC_jp(info, arg0);
}

void func_80079EDC_jp(void) {
    PakInfo* info = mCPk_get_pkinfo();

    func_80079080_jp(&B_80137C40_jp);
    func_8007919C_jp(info, 0);
    B_80137C40_jp.unk_0000.unk_0000 =
        func_8008EEB4_jp(&B_80137C40_jp, sizeof(B80137C40Unk0000Struct), B_80137C40_jp.unk_0000.unk_0000);
    func_8007920C_jp(info, &B_80137C40_jp);
}

s32 func_80079F44_jp(void) {
    PakInfo* info = mCPk_get_pkinfo();
    u16 sp2A = 0;
    s32 sp24;
    s32 var_s0 = 0;

    func_8007919C_jp(info, 0);

    sp24 = func_800792FC_jp(info, &B_80137C40_jp);

    if (sp24 == 1) {
        B_80137C40_jp.unk_1204 = 1;
        sp2A = func_8008EE7C_jp(&B_80137C40_jp, sizeof(B80137C40Unk0000Struct));
    } else if (sp24 == -1) {
        var_s0 = -2;
    } else {
        var_s0 = -1;
    }

    if ((sp24 == 1) && (sp2A == 0)) {
        var_s0 = 1;
    } else {
        B_80137C40_jp.unk_1204 = 0;
        func_80079080_jp(&B_80137C40_jp);
    }

    return var_s0;
}

void func_8007A008_jp(void) {
    PakInfo* info = mCPk_get_pkinfo();
    s32 temp_v0 = func_80079F44_jp();
    OSMesgQueue* queue;

    if ((temp_v0 == 0) || (temp_v0 == -2)) {
        func_8007919C_jp(info, 0);
        queue = padmgr_LockSerialMesgQ();
        func_800CD9F0_jp(&info->pfsInfo, &info->pfsState);
        padmgr_UnlockSerialMesgQ(queue);
    }
}

PakInfo* mCPk_get_pkinfo(void) {
    return g_paks_info_p;
}

s32 func_8007A080_jp(void) {
    PakInfo* info = mCPk_get_pkinfo();
    s32 var_v1 = TRUE;

    if ((info != NULL) && (info->pfsInfo.err == PFS_ERR_ID_FATAL)) {
        var_v1 = FALSE;
    }

    return var_v1;
}
