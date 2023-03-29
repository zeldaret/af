#
# Makefile for the gu subdirectory
#

include $(ROOT)/usr/include/make/PRdefs

LCINCS = -I. -I../gu -I$(ROOT)/usr/include/PR -I$(ROOT)/usr/include
LASINCS = -I. -I$(ROOT)/usr/include/PR -I$(ROOT)/include
LCOPTS = -G 0 -g -O

CFILES	=	mtxcatl.c	\
		mtxxfml.c	\
		mtxxfmf.c	\
		rotate.c

ASFILES	=	mtxident.s	\
		mtxidentf.s	\
		mtxf2l.s	\
		mtxl2f.s	\
		mtxcatf.s	\
		scale.s		\
		scalef.s	\
		normalize.s	\
		translate.s	\
		translatef.s

OBJECTS = $(CFILES:.c=.o) $(ASFILES:.s=.o)

default: $(OBJECTS)

include $(COMMONRULES)

.s.o:
	cpp $(F_ROM) -DLANG_JAPANESE -E -DMIPSEB -DLANGUAGE_ASSEMBLY -D_MIPS_SIM=1 -D_ULTRA64 -I. -I$(LIBDEPTH)\include $*.s $*.ss2
	as -mips3 -G0 -o $*.o $*.ss2
	del $*.ss?
