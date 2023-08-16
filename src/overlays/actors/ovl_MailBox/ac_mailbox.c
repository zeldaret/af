#include "ac_mailbox.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aMBX_actor_ct(Actor* thisx, PlayState* play);
void aMBX_actor_dt(Actor* thisx, PlayState* play);
void aMBX_actor_init(Actor* thisx, PlayState* play);

#if 0
ActorProfile MailBox_Profile = {
    /* */ ACTOR_MAIL_BOX,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0xA000,
    /* */ OBJECT_26,
    /* */ sizeof(MailBox),
    /* */ aMBX_actor_ct,
    /* */ aMBX_actor_dt,
    /* */ aMBX_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MailBox/ac_mailbox/aMBX_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MailBox/ac_mailbox/aMBX_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MailBox/ac_mailbox/func_8096C8FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MailBox/ac_mailbox/func_8096C970_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MailBox/ac_mailbox/func_8096CA0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MailBox/ac_mailbox/func_8096CB84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MailBox/ac_mailbox/func_8096CC30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MailBox/ac_mailbox/func_8096CC7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MailBox/ac_mailbox/func_8096CCD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MailBox/ac_mailbox/func_8096CDE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MailBox/ac_mailbox/func_8096CE9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MailBox/ac_mailbox/func_8096CF40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MailBox/ac_mailbox/func_8096CFF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MailBox/ac_mailbox/func_8096D070_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MailBox/ac_mailbox/func_8096D0E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MailBox/ac_mailbox/func_8096D194_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MailBox/ac_mailbox/aMBX_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MailBox/ac_mailbox/func_8096D28C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MailBox/ac_mailbox/func_8096D314_jp.s")
