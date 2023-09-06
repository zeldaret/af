#ifndef M_MAP_OVL_H
#define M_MAP_OVL_H

#include "ultra64.h"
#include "unk.h"

struct Submenu;

void mMP_map_ovl_construct(struct Submenu* submenu);
void mMP_map_ovl_destruct(struct Submenu* submenu);
void mMP_map_ovl_set_proc(struct Submenu* submenu);

#endif
