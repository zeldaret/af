#ifndef C_6BFE60_H
#define C_6BFE60_H

#include "ultra64.h"
#include "unk.h"

struct Mail_c;
struct Mail_nm_c;
struct AnmPersonalID_c;

// void func_8009C1C0_jp();
// void func_8009C284_jp();
// void func_8009C2D8_jp();
// void func_8009C344_jp();
void mMl_clear_mail(struct Mail_c* mail);
// void mMl_clear_mail_box();
// void func_8009C414_jp();
// void func_8009C438_jp();
// void func_8009C45C_jp();
// void func_8009C480_jp();
// void func_8009C4A0_jp();
// void func_8009C4C8_jp();
// void func_8009C4F4_jp();
s32 func_8009C534_jp(struct Mail_c* mail, s32 count);
// void func_8009C5A4_jp();
// void func_8009C608_jp();
void func_8009C67C_jp(struct Mail_c* mail1, struct Mail_c* mail2);
// void func_8009C69C_jp();
// void func_8009C6EC_jp();
void mMl_set_mail_name_npcinfo(struct Mail_nm_c* name, struct AnmPersonalID_c* anm_pid);
s32 mMl_get_npcinfo_from_mail_name(struct AnmPersonalID_c* anm_pid, struct Mail_nm_c* name);
// void mMl_hunt_for_send_address();
// void func_8009C89C_jp();
// void func_8009C8C0_jp();

#endif
