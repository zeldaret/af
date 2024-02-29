#ifndef C_69E2C0_H
#define C_69E2C0_H

#include "ultra64.h"
#include "color.h"

struct Input;
struct GraphicsContext;
struct Game_Play;
struct Actor;

// void func_8007A620_jp();
// void func_8007A630_jp();
// void Debug_Print_output();
// void func_8007A74C_jp();
// void Debug_Print2_output();
void Debug_mode_input(struct Input *input);
// void Debug_mode_output_sub();
// void Debug_mode_zelda_malloc_info_output();
void Debug_mode_output(struct GraphicsContext* gfxCtx);
// void func_8007B410_jp();
// void func_8007B44C_jp();
// void func_8007B49C_jp();
// void func_8007B4EC_jp();
void mDemo_Set_msg_num(s32 arg0); 
// void func_8007B5F4_jp();
// void func_8007B650_jp();
// void func_8007B670_jp();
// void func_8007B684_jp();
// void func_8007B6A4_jp();
// void func_8007B724_jp();
// void func_8007B760_jp();
void mDemo_Set_talk_display_name(s8 arg0);
// void func_8007B7DC_jp();
// void func_8007B818_jp();
// void func_8007B854_jp();
// void func_8007B890_jp();
// void func_8007B8CC_jp();
// void func_8007B908_jp();
// void func_8007B944_jp();
void mDemo_Set_talk_window_color(Color_RGBA8* color);
// void func_8007B9E0_jp();
void mDemo_Set_camera(s32 arg0);
// void func_8007BA38_jp();
// void func_8007BA4C_jp();
// void func_8007BA84_jp();
// void func_8007BC28_jp();
// void func_8007BCE4_jp();
// void func_8007BD9C_jp();
// void func_8007BE58_jp();
// void func_8007C00C_jp();
// void func_8007C0B4_jp();
// void func_8007C0C0_jp();
// void func_8007C104_jp();
// void func_8007C24C_jp();
// void func_8007C290_jp();
// void func_8007C3D8_jp();
// void func_8007C484_jp();
// void func_8007C570_jp();
// void func_8007C5EC_jp();
// void weight_of_talk_position();
// void func_8007C808_jp();
// void func_8007C814_jp();
// void func_8007C820_jp();
// void func_8007C844_jp();
// void func_8007C868_jp();
// void func_8007C88C_jp();
// void func_8007C8B0_jp();
// void func_8007C8D4_jp();
// void func_8007C8FC_jp();
// void func_8007C924_jp();
// void func_8007CB28_jp();
// void func_8007CB50_jp();
// void func_8007CBEC_jp();
// void func_8007CC9C_jp();
void mDemo_stock_clear(void);
void mDemo_Request(s32 arg0, struct Actor* actor, void* arg2);
s32 mDemo_Check(s32 arg0, struct Actor* actor);
// void func_8007CF34_jp();
// void func_8007CF44_jp();
// void func_8007CF84_jp();
void mDemo_Main(struct Game_Play* game_play);
void func_8007CFD8_jp(struct Game_Play* game_play);
// void func_8007D030_jp();
// void func_8007D048_jp();
// void func_8007D080_jp();
void mDemo_Set_ListenAble(void);
// void func_8007D0B0_jp();
// void func_8007D0C4_jp();
// void func_8007D0D8_jp();
s32 mDemo_Check_ListenAble(void);
s32 mDemo_Check_DiffAngle_forTalk(s16 angle);
// void func_8007D128_jp();

#endif
