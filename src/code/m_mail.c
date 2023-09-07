#include "m_mail.h"
#include "m_common_data.h"
#include "m_lib.h"
#include "m_npc.h"
#include "6B8A70.h"
#include "unknown_structs.h"
#include "macros.h"

#if 0
s32 func_8009C1C0_jp(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_v1;
    s32 var_a1;
    u8* var_a0;
    u8* temp_a0;

    var_a1 = arg1;
    temp_a2 = arg2 & 0xFF;
    var_a0 = (arg0 + var_a1) - 1;
    if (var_a1 != 0) {
        temp_a3 = -(var_a1 & 3);
        temp_v1 = temp_a3 + var_a1;
        if (temp_a3 != 0) {
loop_3:
            if (temp_a2 != *var_a0) {
                return var_a1;
            }
            var_a1 -= 1;
            var_a0 -= 1;
            if (temp_v1 == var_a1) {
                if (var_a1 != 0) {
                    goto block_7;
                }
                /* Duplicate return node #17. Try simplifying control flow for better match */
                return 0;
            }
            goto loop_3;
        }
block_7:
        do {
            if (temp_a2 != var_a0[0]) {
                return var_a1;
            }
            temp_a0 = var_a0 - 1;
            if (temp_a2 != var_a0[-1]) {
                return var_a1 - 1;
            }
            if (temp_a2 != var_a0[-2]) {
                return var_a1 - 2;
            }
            if (temp_a2 != temp_a0[-2]) {
                return var_a1 - 3;
            }
            var_a1 -= 4;
            var_a0 = ((temp_a0 - 1) - 1) - 1;
        } while (var_a1 != 0);
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/func_8009C1C0_jp.s")
#endif

s32 func_8009C284_jp(s32* arg0, u8 arg1[], s32 size, u8 c) {
    s32 count = 0;

    if (arg0 != NULL) {
        *arg0 = false;
    }

    while (size != 0) {
        count++;
        size--;
        if (c == *arg1) {
            if (arg0 != NULL) {
                *arg0 = true;
            }
            break;
        }

        arg1++;
    }

    return count;
}

#if 0
void func_8009C2D8_jp(void* arg0, u8* arg1, s32 arg2) {
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a2;
    u8 temp_t6;
    u8 temp_t8;
    u8* var_a1;
    void* var_a0;

    var_a0 = arg0;
    var_a1 = arg1;
    var_a2 = arg2;
    if (var_a2 != 0) {
        temp_v1 = -(var_a2 & 3);
        temp_v0 = temp_v1 + var_a2;
        if (temp_v1 != 0) {
            do {
                temp_t6 = *var_a1;
                var_a2 -= 1;
                var_a0 -= 1;
                var_a1 -= 1;
                var_a0->unk_1 = temp_t6;
            } while (temp_v0 != var_a2);
            if (var_a2 != 0) {
                goto loop_4;
            }
        } else {
            do {
loop_4:
                var_a2 -= 4;
                var_a0 -= 4;
                var_a0->unk_4 = (u8) var_a1->unk_0;
                temp_t8 = var_a1->unk_-1;
                var_a1 -= 4;
                var_a0->unk_3 = temp_t8;
                var_a0->unk_2 = (u8) var_a1->unk_2;
                var_a0->unk_1 = (u8) var_a1->unk_1;
            } while (var_a2 != 0);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/func_8009C2D8_jp.s")
#endif

void mMl_clear_mail_header(mMl* arg0) {
    mPr_ClearPersonalID(&arg0->unk_00.unk_00);
    arg0->unk_00.unk_10 = 0xFF;
    mPr_ClearPersonalID(&arg0->unk_12.unk_00);
    arg0->unk_12.unk_10 = 0xFF;
}

void mMl_clear_mail(mMl* arg0) {
    bzero(arg0, sizeof(mMl));
    mMl_clear_mail_header(arg0);
    mem_clear(&arg0->unk_2A, sizeof(mMl_unk_2A), 0x20);
    arg0->unk_26 = 0xFF;
}

void mMl_clear_mail_box(mMl* arg0, s32 arg1) {
    while (arg1 != 0) {
        arg1--;
        mMl_clear_mail(arg0);
        arg0++;
    }
}

s32 mMl_check_not_used_mail(mMl* arg0) {
    s32 ret = 0;

    if (arg0->unk_26 == 0xFF) {
        ret = 1;
    }
    return ret;
}

void mMl_copy_header_name(mMl_unk_00* arg0, mMl_unk_00* arg1) {
    arg0->unk_10 = arg1->unk_10;
    mPr_CopyPersonalID(&arg0->unk_00, &arg1->unk_00);
}

void mMl_set_from_name(mMl* arg0, mMl* arg1) {
    mMl_copy_header_name(&arg0->unk_12, &arg1->unk_00);
}

void mMl_set_to_name(mMl* arg0, mMl* arg1) {
    mMl_copy_header_name(&arg0->unk_00, &arg1->unk_00);
}

void mMl_set_to_plname(mMl* arg0, mMl* arg1) {
    mPr_CopyPersonalID(&arg0->unk_00.unk_00, &arg1->unk_00.unk_00);
    arg0->unk_00.unk_10 = 0;
}

void mMl_set_playername(mMl* arg0, PersonalID* arg1) {
    mPr_CopyPersonalID(&arg0->unk_12.unk_00, arg1);
    arg0->unk_12.unk_10 = 0;
}

void mMl_init_mail(mMl* arg0, PersonalID* arg1) {
    mMl_clear_mail(arg0);
    mMl_set_playername(arg0, arg1);
    arg0->unk_26 = 1;
    arg0->unk_28 = 0;
    arg0->unk_29 = 0;
}

s32 mMl_chk_mail_free_space(mMl arg0[], s32 arg1) {
    s32 i;

    for (i = 0; i < arg1; i++) {
        if (mMl_check_not_used_mail(arg0) == 1) {
            return i;
        }
        arg0++;
    }
    return -1;
}

s32 mMl_use_mail_space(mMl arg0[], s32 arg1, PersonalID* arg2) {
    s32 index = mMl_chk_mail_free_space(arg0, arg1);

    if (index != -1) {
        mMl_init_mail(&arg0[index], arg2);
    }
    return index;
}

s32 mMl_count_use_mail_space(mMl arg0[], s32 arg1) {
    s32 i;
    s32 ret = 0;

    for (i = 0; i < arg1; i++) {
        if (mMl_check_not_used_mail(arg0) != 1) {
            ret++;
        }
        arg0++;
    }
    return ret;
}

void mMl_copy_mail(mMl* arg0, mMl* arg1) {
    mem_copy(arg0, arg1, sizeof(mMl));
}

void mMl_clear_mail_header_common(MailHeaderCommon* arg0) {
    arg0->unk_00 = -1;
    arg0->unk_01 = 0;
    mem_clear(arg0->unk_02, 0xA, 0x20);
    mem_clear(arg0->unk_0C, 0x10, 0x20);
}

void mMl_copy_mail_header_common(MailHeaderCommon* arg0, MailHeaderCommon* arg1) {
    mem_copy(arg0, arg1, sizeof(MailHeaderCommon));
}

void mMl_set_mail_name_npcinfo(mMl_unk_00* arg0, mMl_get_npcinfo_from_mail_name_arg0* arg1) {
    PlayerName sp20;

    arg0->unk_10 = 1;
    mNpc_GetNpcWorldNameAnm(&sp20, arg1);
    mPr_CopyPlayerName(&arg0->unk_00.unk_0, &sp20);
    arg0->unk_00.unk_E = arg1->unk_2;
    mLd_CopyLandName(&arg0->unk_00.unk_6, &arg1->unk_4);
    arg0->unk_00.unk_C = ((arg1->unk_0 & 0xFF) << 8) | (arg1->unk_A & 0xFF);
}

s32 mMl_get_npcinfo_from_mail_name(mMl_get_npcinfo_from_mail_name_arg0* arg0, mMl_unk_00* arg1) {
    s32 var_v1 = 0;

    if (arg1->unk_10 == 1) {
        arg0->unk_0 = (((arg1->unk_00.unk_C & 0xFF00) >> 8) | 0xE000);
        arg0->unk_2 = arg1->unk_00.unk_E;
        mLd_CopyLandName(&arg0->unk_4, &arg1->unk_00.unk_6);
        arg0->unk_A = arg1->unk_00.unk_C & 0xFFFF;
        arg0->unk_B = mNpc_GetLooks(arg0->unk_0);
        var_v1 = 1;
    }
    return var_v1;
}

s32 mMl_hunt_for_send_address(mMl* arg0) {
    s32 var_s0;

    if (arg0->unk_00.unk_10 != 0) {
        return -1;
    }

    for (var_s0 = 0; var_s0 < ARRAY_COUNT(common_data.homes); var_s0++) {
        if (mPr_CheckCmpPersonalID(&common_data.homes[var_s0].unk_000, &arg0->unk_00.unk_00) == 1) {
            return var_s0;
        }
    }

    return -1;
}

s32 mMl_check_send_mail(struct_func_8085CE18_jp_arg4* arg0) {
    switch (arg0->unk_26) {
        case 1:
            return 1;

        default:
            return 0;
    }
}

s32 mMl_check_set_present_myself(mMl* arg0) {
    switch (arg0->unk_26) {
        case 1:
        case 3:
        case 4:
            return 1;

        default:
            return 0;
    }
}
