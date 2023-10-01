#ifndef M_INVENTORY_OVL_H
#define M_INVENTORY_OVL_H

#include "ultra64.h"
#include "unk.h"

struct Submenu;

void mIV_inventory_ovl_construct(struct Submenu* submenu);
void mIV_inventory_ovl_destruct(struct Submenu* submenu);
void mIV_inventory_ovl_set_proc(struct Submenu* submenu);

#endif
