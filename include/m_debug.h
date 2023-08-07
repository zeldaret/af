#ifndef M_DEBUG_H
#define M_DEBUG_H

#include "ultra64.h"

typedef enum {
		/* 0 */	DEBUG_REG_START = 0,
		/* 0 */ DEBUG_REG_REG = DEBUG_REG_START, 
		/* 1 */	DEBUG_REG_SREG,
 		/* 2 */ DEBUG_REG_OREG,
		/* 3 */ DEBUG_REG_PREG,
  		/* 4 */ DEBUG_REG_QREG,
		/* 0 */ DEBUG_REG_MREG,
 		/* 5 */ DEBUG_REG_SBREG,
		/* 6 */ DEBUG_REG_DREG,
		/* 7 */ DEBUG_REG_UREG,
		/* 8 */ DEBUG_REG_IREG,
		/* 9 */ DEBUG_REG_ZREG,
		/* 10 */ DEBUG_REG_CRV,
		/* 11 */ DEBUG_REG_NS1,
		/* 12 */ DEBUG_REG_SND,
		/* 13 */ DEBUG_REG_XREG,
		/* 14 */ DEBUG_REG_CRV2,
		/* 15 */ DEBUG_REG_DEMOREG,
		/* 16 */ DEBUG_REG_TREG,
		/* 17 */ DEBUG_REG_WREG,
		/* 18 */ DEBUG_REG_AREG,
		/* 19 */ DEBUG_REG_VREG,
		/* 20 */ DEBUG_REG_HREG,
		/* 21 */ DEBUG_REG_GREG,
		/* 22 */ DEBUG_REG_mREG,
		/* 23 */ DEBUG_REG_nREG,
		/* 24 */ DEBUG_REG_BREG,
		/* 25 */ DEBUG_REG_DORO,
		/* 26 */ DEBUG_REG_kREG,
		/* 27 */ DEBUG_REG_BAK,
		/* 28 */ DEBUG_REG_PLAYERREG,
		/* 29 */ DEBUG_REG_NMREG,
  
		/* 30 */ DEBUG_REG_NIIREG,
		/* 31 */ DEBUG_REG_GENREG,
		/* 32 */ DEBUG_REG_MYKREG,
		/* 33 */ DEBUG_REG_CAMREG,
		/* 34 */ DEBUG_REG_SAKREG,
		/* 35 */ DEBUG_REG_TAKREG,
		/* 36 */ DEBUG_REG_PL2REG,

		/* 37 */ DEBUG_REG_MAX
} DEBUG_REG;

#define DEBUG_REG_SIZE 16
#define DEBUG_REG_GROUP 6

#define DEBUG_REG_COUNT (DEBUG_REG_SIZE * DEBUG_REG_GROUP * DEBUG_REG_MAX)

typedef struct debug_mode_s {
  u8 mode;
  u8 type;
  s8 inputR;
  s8 keyWait;

  s32 oldKey;
  s32 pad[3];

  s16 r[DEBUG_REG_SIZE * DEBUG_REG_GROUP * DEBUG_REG_MAX];
} Debug_mode;

extern Debug_mode* debug_mode;


#define REGADDR(reg, idx) (debug_mode->r[DEBUG_REG_SIZE * DEBUG_REG_GROUP * DEBUG_REG_##reg + (idx)])

#define GETREG(reg, idx) ((s16)(REGADDR(reg, idx)))

#define REG(r) GETREG(REG,r);
#define SREG(r) GETREG(SREG,r);
#define OREG(r) GETREG(OREG,r);
#define PREG(r) GETREG(PREG,r);
#define QREG(r) GETREG(QREG,r);
#define MREG(r) GETREG(MREG,r);
#define SBREG(r) GETREG(SBREG,r);
#define DREG(r) GETREG(DREG,r);
#define UREG(r) GETREG(UREG,r);
#define IREG(r) GETREG(IREG,r);
#define ZREG(r) GETREG(ZREG,r);
#define CRV(r) GETREG(CRV,r);
#define NS1(r) GETREG(NS1,r);
#define SND(r) GETREG(SND,r);
#define XREG(r) GETREG(XREG,r);
#define CRV2(r) GETREG(CRV2,r);
#define DEMOREG(r) GETREG(DEMOREG,r);
#define TREG(r) GETREG(TREG,r);
#define WREG(r) GETREG(WREG,r);
#define AREG(r) GETREG(AREG,r);
#define VREG(r) GETREG(VREG,r);
#define HREG(r) GETREG(HREG,r);
#define GREG(r) GETREG(GREG,r);
#define mREG(r) GETREG(mREG,r);
#define nREG(r) GETREG(nREG,r);
#define BREG(r) GETREG(BREG,r);
#define DORO(r) GETREG(DORO,r);
#define kREG(r) GETREG(kREG,r);
#define BAK(r) GETREG(BAK,r);
#define PLAYERREG(r) GETREG(PLAYERREG,r);
#define NMREG(r) GETREG(NMREG,r);
#define NIIREG(r) GETREG(NIIREG,r);
#define GENREG(r) GETREG(GENREG,r);
#define MYKREG(r) GETREG(MYKREG,r);
#define CAMREG(r) GETREG(CAMREG,r);
#define SAKKREG(r) GETREG(SAKKREG,r);
#define TAKREG(r) GETREG(TAKREG,r);
#define PL2REG(r) GETREG(PL2REG,r);

extern void new_Debug_mode(void);

#endif
