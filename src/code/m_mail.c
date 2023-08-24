#include "m_mail.h"
#include "m_lib.h"

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/func_8009C1C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/func_8009C284_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/func_8009C2D8_jp.s")

//? func_800B795C_jp(mMl*);                           /* extern */

#if 0
void func_8009C344_jp(mMl* arg0) {
    func_800B795C_jp(arg0);
    arg0->unk_00[0x10] = -1;
    func_800B795C_jp((mMl* ) &arg0->unk_00[0x12]);
    arg0->unk_00[0x22] = -1;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/func_8009C344_jp.s")
#endif

//void func_8009C344_jp(mMl*);

void mMl_clear_mail(mMl* arg0) {
    bzero(arg0, sizeof(mMl));
    func_8009C344_jp(arg0);
    mem_clear(&arg0->unk_2A, sizeof(mMl_unk_2A), 0x20);
    arg0->unk_26 = 0xFF;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/mMl_clear_mail_box.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/func_8009C414_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/func_8009C438_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/func_8009C45C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/func_8009C480_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/func_8009C4A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/func_8009C4C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/func_8009C4F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/func_8009C534_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/func_8009C5A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/func_8009C608_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/func_8009C67C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/func_8009C69C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/func_8009C6EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/mMl_set_mail_name_npcinfo.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/mMl_get_npcinfo_from_mail_name.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/mMl_hunt_for_send_address.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/func_8009C89C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/func_8009C8C0_jp.s")
