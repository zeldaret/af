#!smake
#
# Makefile for the gt subdirectory
#

include $(ROOT)/usr/include/make/PRdefs


# LCOPTS = -mips2 -non_shared -fullwarn -G 0

LCINCS = -I. -I$(ROOT)/usr/include/PR -I$(ROOT)/usr/include

CFILES  = dumpturbo.c gt.c

OBJECTS = $(CFILES:.c=.o)

default: $(OBJECTS)

include $(COMMONRULES)
