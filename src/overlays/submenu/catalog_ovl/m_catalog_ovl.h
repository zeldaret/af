#ifndef M_CATALOG_OVL_H
#define M_CATALOG_OVL_H

#include "ultra64.h"
#include "unk.h"

struct Submenu;

void mCL_catalog_ovl_construct(struct Submenu* submenu);
void mCL_catalog_ovl_destruct(struct Submenu* submenu);
void mCL_catalog_ovl_set_proc(struct Submenu* submenu);

#endif
