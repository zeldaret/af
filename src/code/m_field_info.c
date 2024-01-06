#include "global.h"
#include "m_field_info.h"
#include "m_collision_bg.h"
#include "libc64/qrand.h"

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80087C30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80087C40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_GetBlockTopP.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_GetFieldId.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80087C9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80087D30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80087DC8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80087E14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80087E58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80087E94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80087ED0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088018_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088160_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008819C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_800881AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088270_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_800882AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_800882FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088320_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088344_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088458_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_800884E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_800885A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_Wpos2BlockNum.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_Wpos2BkandUtNuminBlock.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008883C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_800888AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088938_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_800889D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088A58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088B3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_UtNum2PosXZInBk.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088BFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088C74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088CBC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088CD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088CE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088D00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088D30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088D78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088D9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088E08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088E34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088E74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088F14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80088F94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008902C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008907C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80089114_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_800891AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_BkNum2BlockType.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_800892CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008930C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80089348_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_800893C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80089404_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_BlockKind2BkNum.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_800894D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_GetBkNum2ColTop.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_800895B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80089698_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80089704_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_800897D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80089888_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_800898F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_800899CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80089A34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80089AAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80089B1C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80089B94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80089C0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80089CA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80089D18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80089D6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80089E84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_80089EF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008A000_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_BkNumtoUtFGTop.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008A3BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008A410_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008A4F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_GetUnitFG.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008A608_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008A670_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008A74C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008A81C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008A960_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_SetFG_common.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008AA98_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008AB14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008AC74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008ACA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008ACBC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008ACD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008ADCC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008AE70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B1A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B200_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B238_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B26C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B29C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B2D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B300_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B318_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_SetBearActor.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B3E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B4C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B598_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B66C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B774_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B7F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B878_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008B9F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008BA74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008BAEC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008BB64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008BBF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_SetMoveActorBitData_ON.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008BCFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_MyMoveActorBitData_ON.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008BDCC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008BE00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008BE38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008BF34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008BFC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C058_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_CheckPlayerWade.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C120_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C130_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_GetDepositP.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C344_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C390_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C3B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C3D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C3E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C458_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_BlockDepositOFF.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C498_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C4B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C504_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C524_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C548_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C56C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C5F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C610_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C630_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C650_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_Wpos2DepositOFF.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C708_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C764_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C798_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C830_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C84C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C8C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C938_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008C964_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008CA14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008CAD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008CC1C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008CCFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008CD24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008CD74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008CE00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008CE38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008CEC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008CFF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008D12C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008D268_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008D3A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008D574_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008D6E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008D7B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008D884_jp.s")

s32 mFI_GetWaveUtinBlock(s32* arg0, s32* arg1, s32 arg2, s32 arg3) {
    UNUSED s32 pad[4];
    s32 i;
    s32 ret = 0;
    s32 var_s2;
    s32 var_s3 = 0;
    mCoBG_unkStructUnion* temp_v0;
    mCoBG_unkStructUnion* var_s1;

    arg0[0] = 0;
    arg1[0] = 0;

    temp_v0 = var_s1 = mFI_GetBkNum2ColTop(arg2, arg3);

    if (temp_v0 != NULL) {

        for (i = 0; i < 0x100; i++) {

            if (func_80076358_jp(var_s1->data.unk6) == 1) {
                var_s3 += 1;
            }

            var_s1++;
        }

        if (var_s3 > 0) {
            var_s1 = temp_v0;
            var_s2 = fqrand() * var_s3;

            for (i = 0; i < 0x100; i++) {

                if (func_80076358_jp(var_s1->data.unk6) == 1) {

                    if (var_s2 <= 0) {
                        arg0[0] = i & 0xF;
                        arg1[0] = i >> 4;
                        ret = 1;
                        break;
                    }

                    var_s2 -= 1;
                }

                var_s1++;
            }
        }
    }

    return ret;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008DA4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008DCF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008DD0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008DD3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008DDC8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008DF04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008E058_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008E514_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008E5F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_PrintNowBGNum.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/mFI_PrintFgAttr.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008E8E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008E9C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_field_info/func_8008EA5C_jp.s")
