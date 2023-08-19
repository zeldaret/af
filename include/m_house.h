#ifndef M_HOUSE_H
#define M_HOUSE_H

#include "ultra64.h"

/**
 * House arrangement byte breakdown
 * 
 * PX = player x
 * HX = house x
 * 
 * xx xx xx xx
 * P3 P2 P1 P0
 * 
 * Example:
 * 01 11 10 00
 * P3 P2 P1 P0
 * H1 H3 H2 H0
 **/

typedef enum mHS_HOUSE {
  /* 0 */ mHS_HOUSE0, /* Top-left house */
  /* 1 */ mHS_HOUSE1, /* Top-right house */
  /* 2 */ mHS_HOUSE2, /* Bottom-left house */
  /* 3 */ mHS_HOUSE3, /* Bottom-right house */

  /* 4 */ mHS_HOUSE_NUM
} mHS_HOUSE;

#endif
