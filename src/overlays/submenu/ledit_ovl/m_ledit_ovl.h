#ifndef M_LEDIT_OVL_H
#define M_LEDIT_OVL_H

#include "ultra64.h"
#include "unk.h"

struct Submenu;

void mLE_ledit_ovl_construct(struct Submenu* submenu);
void mLE_ledit_ovl_destruct(struct Submenu* submenu);
void mLE_ledit_ovl_set_proc(struct Submenu* submenu);

#endif
