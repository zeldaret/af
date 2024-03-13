#ifndef C_6EDD10_H
#define C_6EDD10_H

#include "ultra64.h"

struct lbRTC_ymd_t;
struct lbRTC_time_c;

// void func_800CA070_jp();
void mTM_set_season(void);
// void func_800CA230_jp();
s32 mTM_check_renew_time(u8);
void mTM_off_renew_time(u8);
// void func_800CA2A8_jp();
void mTM_set_renew_time(struct lbRTC_ymd_t*, struct lbRTC_time_c*);
void mTM_renewal_renew_time(void);
// void func_800CA350_jp();
// void func_800CA570_jp();
void mTM_time(void);

#endif
