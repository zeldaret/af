#ifndef SELECT_H
#define SELECT_H

#include "ultra64.h"
#include "game.h"
#include "unk.h"
#include "m_view.h"
#include "m_private_internals.h"

typedef enum SelectCheck {
    /* 0 */ SELECT_CHECK_A_BUTTON_RTC,
    /* 1 */ SELECT_CHECK_A_BUTTON_TIME,
    /* 2 */ SELECT_CHECK_A_BUTTON_STEP,
    /* 3 */ SELECT_CHECK_A_BUTTON_WEATHER,
    /* 4 */ SELECT_CHECK_A_BUTTON_SEX,
    /* 5 */ SELECT_CHECK_A_BUTTON_FACE_TYPE,
    /* 6 */ SELECT_CHECK_A_BUTTON_SWELL,
    /* 7 */ SELECT_CHECK_A_BUTTON_DECOY,
    /* 8 */ SELECT_CHECK_A_BUTTON_CLOTH,
    /* 9 */ SELECT_CHECK_A_BUTTON_EVENT,
    /* 10 */ SELECT_CHECK_A_BUTTON_NUM
} SelectCheck;

struct lbRTC_time_c; 
struct gfxprint;

typedef struct Game_Select {
    /* 0x000 */ Game state;
    /* 0x0E0 */ Game_Play1938 view;
    /* 0x208 */ s32 status; 
    /* 0x20C */ s32 cursorX;
    /* 0x210 */ s32 cursorY;
    /* 0x214 */ s32 step;
    /* 0x218 */ s32 stepAdd;
    /* 0x21C */ s32 selectedScene;
    /* 0x220 */ s32 topScene;
    /* 0x224 */ s32 unk224;
    /* 0x228 */ s32 buttonStep;
    /* 0x22C */ char name[PLAYER_NAME_LEN]; 
    /* 0x234 */ UNK_TYPE unk_234;
    /* 0x238 */ UNK_TYPE unk_238;
    /* 0x23C */ UNK_TYPE unk_23C;
} Game_Select; // size = 0x240

typedef void (*GameProc)(Game*, s32);
    
typedef struct NameFunction {
    /* 0x0 */ const char* name;
    /* 0x4 */ GameProc nextProc;
    /* 0x8 */ s32 sceneNo;
} NameFunction; // size = 0xC

void game_next_play(Game* game, s32 scene);
char data2fcode(char data);
char fcode2data(char fcode);
void select_pass(Game_Select* select);
s32 select_start_proc(Game_Select* select);
s32 select_check_start(Game_Select* select);
s32 select_check_A_button_rtc(Game_Select* select);
s32 select_check_A_button_time(Game_Select* select);
s32 select_check_A_buttonStep(Game_Select* select);
s32 select_check_A_button_weather(Game_Select* select);
s32 select_check_A_button_sex(Game_Select* select);
s32 select_check_A_button_face_type(Game_Select* select);
s32 select_check_A_button_swell(Game_Select* select);
s32 select_check_A_button_decoy(Game_Select* select);
s32 select_check_A_button_cloth(Game_Select* select);
s32 select_check_A_button_event(Game_Select* select);
s32 select_check_A_button(Game_Select* select);
s32 select_move_cursol(Game_Select* select);
s32 select_course_step_sub(s32 course);
void select_adjust_top_no(Game_Select* select, s32 course, s32 adjust);
void select_course_step(Game_Select* select, s32 addend);
void select_course(Game_Select* select);
void select_move_main(Game_Select* select);
void select_move_setup(Game_Select* select);
void select_move_time_year_set(s32 adjust);
void select_move_time_month_set(s32 adjust);
void select_move_time_day_set(s32 adjust);
void select_move_time_hour_set(s32 adjust);
void select_move_time_min_set(s32 adjust);
void select_move_time_week_set(s32 adjust);
void select_move_time_set(Game_Select* select);
void select_move_cloth_sel(Game_Select* select);
void select_move(Game_Select* select);
void select_print_wait(struct gfxprint* gfxprint);
void select_print_course_name(Game_Select* select, struct gfxprint* gfxprint);
void select_print_rtc(struct gfxprint* gfxprint, Game_Select* select);
void select_print_time_sub(struct gfxprint* gfxprint, Game_Select* select, struct lbRTC_time_c* time);
void select_print_time(struct gfxprint* gfxprint, Game_Select* select);
void select_print_step_sub2(struct gfxprint* gfxprint);
void select_print_step(struct gfxprint* gfxprint, Game_Select* select);
void select_print_weather(struct gfxprint* gfxprint, Game_Select* select);
void select_print_sex(struct gfxprint* gfxprint, Game_Select* select);
void select_print_cloth(struct gfxprint* gfxprint, Game_Select* select);
void select_print_swell(struct gfxprint* gfxprint, Game_Select* select);
void select_print_decoy(struct gfxprint* gfxprint, Game_Select* select);
void select_print_face_type(struct gfxprint* gfxprint, Game_Select* select);
void select_print_event(struct gfxprint* gfxprint, Game_Select* select);
void select_draw_main(Game_Select* select);
void select_draw_wait(Game_Select* select);
void select_draw(Game_Select* select);
void select_main(Game* game);
void select_cleanup(Game* game);
void select_init(Game* game);


#endif
