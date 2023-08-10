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
	/* 5 */ DEBUG_REG_MREG,
 	/* 6 */ DEBUG_REG_SBREG,
	/* 7 */ DEBUG_REG_DREG,
	/* 8 */ DEBUG_REG_UREG,
	/* 9 */ DEBUG_REG_IREG,
	/* 10 */ DEBUG_REG_ZREG,
	/* 11 */ DEBUG_REG_CRV,
	/* 12 */ DEBUG_REG_NS1,
	/* 13 */ DEBUG_REG_SND,
	/* 14 */ DEBUG_REG_XREG,
	/* 15 */ DEBUG_REG_CRV2,
	/* 16 */ DEBUG_REG_DEMOREG,
	/* 17 */ DEBUG_REG_TREG,
	/* 18 */ DEBUG_REG_WREG,
	/* 19 */ DEBUG_REG_AREG,
	/* 20 */ DEBUG_REG_VREG,
	/* 21 */ DEBUG_REG_HREG,
	/* 22 */ DEBUG_REG_GREG,
	/* 23 */ DEBUG_REG_mREG,
	/* 24 */ DEBUG_REG_nREG,
	/* 25 */ DEBUG_REG_BREG,
	/* 26 */ DEBUG_REG_DORO,
	/* 27 */ DEBUG_REG_kREG,
	/* 28 */ DEBUG_REG_BAK,
	/* 29 */ DEBUG_REG_PLAYERREG,
	/* 30 */ DEBUG_REG_NMREG,

	/* 31 */ DEBUG_REG_NIIREG,
	/* 32 */ DEBUG_REG_GENREG,
	/* 33 */ DEBUG_REG_MYKREG,
	/* 34 */ DEBUG_REG_CAMREG,
	/* 35 */ DEBUG_REG_SAKREG,
	/* 36 */ DEBUG_REG_TAKREG,
	/* 37 */ DEBUG_REG_PL2REG,

	/* 38 */ DEBUG_REG_MAX
} DEBUG_REG;

#define DEBUG_REG_SIZE 16
#define DEBUG_REG_GROUP 6

#define DEBUG_REG_COUNT (DEBUG_REG_SIZE * DEBUG_REG_GROUP * DEBUG_REG_MAX)

typedef struct debug_mode_s {
    /* 0x00 */ u8 mode;
	/* 0x01 */ u8 type;
	/* 0x02 */ s8 inputR;
  	/* 0x03 */ s8 keyWait;

  	/* 0x04 */ s32 oldKey;
  	/* 0x08 */ s32 pad[3];

  	/* 0x14 */ s16 r[DEBUG_REG_SIZE * DEBUG_REG_GROUP * DEBUG_REG_MAX];
} Debug_mode; // size = 0x1C94

extern Debug_mode* debug_mode;


#define REGADDR(reg, idx) (debug_mode->r[DEBUG_REG_SIZE * DEBUG_REG_GROUP * DEBUG_REG_##reg + (idx)])

#define GETREG(reg, idx) (REGADDR(reg, idx))

#define REG(r) GETREG(REG,r)
#define SREG(r) GETREG(SREG,r)
#define OREG(r) GETREG(OREG,r)
#define PREG(r) GETREG(PREG,r)
#define QREG(r) GETREG(QREG,r)
#define MREG(r) GETREG(MREG,r)
#define SBREG(r) GETREG(SBREG,r)
#define DREG(r) GETREG(DREG,r)
#define UREG(r) GETREG(UREG,r)
#define IREG(r) GETREG(IREG,r)
#define ZREG(r) GETREG(ZREG,r)
#define CRV(r) GETREG(CRV,r)
#define NS1(r) GETREG(NS1,r)
#define SND(r) GETREG(SND,r)
#define XREG(r) GETREG(XREG,r)
#define CRV2(r) GETREG(CRV2,r)
#define DEMOREG(r) GETREG(DEMOREG,r)
#define TREG(r) GETREG(TREG,r)
#define WREG(r) GETREG(WREG,r)
#define AREG(r) GETREG(AREG,r)
#define VREG(r) GETREG(VREG,r)
#define HREG(r) GETREG(HREG,r)
#define GREG(r) GETREG(GREG,r)
#define mREG(r) GETREG(mREG,r)
#define nREG(r) GETREG(nREG,r)
#define BREG(r) GETREG(BREG,r)
#define DORO(r) GETREG(DORO,r)
#define kREG(r) GETREG(kREG,r)
#define BAK(r) GETREG(BAK,r)
#define PLAYERREG(r) GETREG(PLAYERREG,r)
#define NMREG(r) GETREG(NMREG,r)
#define NIIREG(r) GETREG(NIIREG,r)
#define GENREG(r) GETREG(GENREG,r)
#define MYKREG(r) GETREG(MYKREG,r)
#define CAMREG(r) GETREG(CAMREG,r)
#define SAKKREG(r) GETREG(SAKKREG,r)
#define TAKREG(r) GETREG(TAKREG,r)
#define PL2REG(r) GETREG(PL2REG,r)

extern void new_Debug_mode(void);

#endif
