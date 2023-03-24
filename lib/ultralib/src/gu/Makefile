#!smake
#
# Makefile for the gu subdirectory
#

include $(ROOT)/usr/include/make/PRdefs


# LCOPTS = -mips2 -non_shared -fullwarn -G 0
LCINCS = -I. -I$(ROOT)/usr/include/PR -I$(ROOT)/usr/include
LCOPTS = -G 0 -g -O

CFILES	=			\
	align.c			\
	cosf.c			\
	coss.c			\
	frustum.c		\
	guloadtile_bug.c	\
	loadtextureblockmipmap.c\
	lookat.c		\
	lookathil.c		\
	lookatref.c		\
	lookatstereo.c		\
	mtxcatf.c		\
	mtxcatl.c		\
	mtxutil.c		\
	normalize.c		\
	ortho.c			\
	perspective.c		\
	position.c		\
	poslight.c		\
	poslighthil.c		\
	random.c		\
	rotate.c		\
	rotaterpy.c		\
	scale.c			\
	sinf.c			\
	sins.c			\
	translate.c		\
	us2dex.c		\
	us2dex_emu.c		\
	us2dex2_emu.c		\
	usprite.c

ASFILES	=			\
	libm_vals.s		\
	sqrtf.s
OBJECTS =	$(CFILES:.c=.o)

default: $(OBJECTS)

include $(COMMONRULES)
