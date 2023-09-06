#ifndef M_BOARD_OVL_H
#define M_BOARD_OVL_H

#include "ultra64.h"
#include "unk.h"

struct Submenu;

void mBD_board_ovl_construct(struct Submenu* submenu);
void mBD_board_ovl_destruct(struct Submenu* submenu);
void mBD_board_ovl_set_proc(struct Submenu* submenu);

#endif
