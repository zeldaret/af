#ifndef M_EVENT_H
#define M_EVENT_H

#include "ultra64.h"
#include "unk.h"

typedef struct EventSaveInfo {
    /* 0x00 */ char unk00[0x9C];
} EventSaveInfo; // size >= 0x9C

typedef struct Event {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} Event; // size = 0x10

// void func_8007D140_jp();
// void func_8007D180_jp();
void mEv_ClearEventSaveInfo(EventSaveInfo* eventSaveInfo);
void mEv_ClearEventInfo(void);
// void func_8007D25C_jp();
// void func_8007D2B8_jp();
// void func_8007D318_jp();
// void func_8007D36C_jp();
// void func_8007D3F0_jp();
// void func_8007D408_jp();
// void func_8007D418_jp();
// void func_8007D42C_jp();
// void func_8007D43C_jp();
// void func_8007D44C_jp();
// void func_8007D460_jp();
// void func_8007D470_jp();
// void func_8007D490_jp();
// void func_8007D4A0_jp();
// void func_8007D4C4_jp();
// void func_8007D4D0_jp();
// void func_8007D4F4_jp();
// void func_8007D52C_jp();
// void func_8007D554_jp();
// void func_8007D578_jp();
// void func_8007D58C_jp();
// void func_8007D59C_jp();
// void func_8007D5D4_jp();
// void func_8007D650_jp();
s32 mEv_CheckFirstJob(void);
// void func_8007D734_jp();
// void func_8007D784_jp();
UNK_RET mEv_CheckFirstIntro(void);
// void func_8007D810_jp();
void mEv_SetGateway(void);
// void func_8007D880_jp();
void mEv_UnSetGateway(void);
s32 mEv_CheckTitleDemo(void);
// void func_8007D91C_jp();
// void func_8007D930_jp();
// void func_8007D9C8_jp();
// void func_8007DA64_jp();
// void func_8007DA6C_jp();
// void func_8007DACC_jp();
// void func_8007DB20_jp();
// void func_8007DBB0_jp();
// void func_8007DD84_jp();
// void func_8007DDE8_jp();
// void func_8007DE2C_jp();
// void func_8007DF04_jp();
// void func_8007DF98_jp();
// void func_8007E0FC_jp();
// void func_8007E140_jp();
// void func_8007E184_jp();
// void func_8007E1D8_jp();
// void func_8007E22C_jp();
// void func_8007E264_jp();
// void func_8007E3E8_jp();
// void func_8007E518_jp();
// void func_8007E60C_jp();
// void func_8007E690_jp();
// void func_8007E714_jp();
// void func_8007E780_jp();
// void func_8007EB6C_jp();
// void func_8007EC28_jp();
// void func_8007EC54_jp();
// void func_8007ECA0_jp();
// void func_8007ECD4_jp();
// void func_8007ED08_jp();
// void func_8007ED70_jp();
// void func_8007EED4_jp();
// void func_8007EF18_jp();
// void func_8007F1A8_jp();
// void func_8007F28C_jp();
// void func_8007F2D8_jp();
// void func_8007F318_jp();
// void func_8007F358_jp();
// void func_8007F6A0_jp();
// void func_8007F764_jp();
void mEv_init(Event* event);
void mEv_init_force(void*);
void mEv_2nd_init(Event* event);
// void func_8007F950_jp();
void mEv_run(Event* event);
void mEv_finish(Event* event);
// void func_8007FCB8_jp();
// void func_8007FD40_jp();
// void func_8007FDA8_jp();
// void func_8007FE0C_jp();
void mEv_clear_status(s32, s16);
// void func_8007FEBC_jp();
s32 mEv_check_status(s32, s16);
// void func_8007FF8C_jp();
// void func_8007FFC4_jp();
// void func_80080000_jp();
// void func_80080040_jp();
// void func_80080080_jp();
// void func_80080200_jp();
u8* func_8008033C_jp(s32,s32);
// void func_800804AC_jp();
// void func_800806A0_jp();
// void func_800807E0_jp();
// void func_800808E0_jp();
// void func_80080A50_jp();
// void func_80080C68_jp();
// void func_80080D68_jp();
// void func_80080F0C_jp();
// void func_8008114C_jp();
// void func_80081360_jp();
// void func_80081424_jp();
// void func_80081434_jp();
// void func_80081460_jp();
// void func_800814B8_jp();
// void func_800815F0_jp();
// void func_800816C0_jp();
// void func_8008172C_jp();
// void func_80081800_jp();
// void func_8008180C_jp();
// void func_80081818_jp();
// void mEv_debug_print4f();
// void mEv_sp_debug_print4f();
// void func_80081B98_jp();
// void func_80081BA4_jp();
// void func_80081D24_jp();
// void func_80081E38_jp();
// void func_80081E48_jp();

#endif
