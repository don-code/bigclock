#
# Created by gmakemake (Ubuntu Jul 25 2014) on Sat Aug  2 20:37:57 2014
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:      .a .o .c .C .cpp .s .S
.c.o:
                $(COMPILE.c) $<
.C.o:
                $(COMPILE.cc) $<
.cpp.o:
                $(COMPILE.cc) $<
.S.s:
                $(CPP) -o $*.s $<
.s.o:
                $(COMPILE.cc) $<
.c.a:
                $(COMPILE.c) -o $% $<
                $(AR) $(ARFLAGS) $@ $%
                $(RM) $%
.C.a:
                $(COMPILE.cc) -o $% $<
                $(AR) $(ARFLAGS) $@ $%
                $(RM) $%
.cpp.a:
                $(COMPILE.cc) -o $% $<
                $(AR) $(ARFLAGS) $@ $%
                $(RM) $%

CC =            gcc
CXX =           g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Default flags (redefine these with a header.mak file if desired)
CXXFLAGS =      -ggdb
CFLAGS =        -ggdb
CLIBFLAGS =     -lm
CCLIBFLAGS =
########## End of default flags


CPP_FILES =
C_FILES =       charset.c clock.c
PS_FILES =
S_FILES =
H_FILES =       charset.h display.h
SOURCEFILES =   $(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:      $(SOURCEFILES)
OBJFILES =      charset.o

#
# Main targets
#

all:    clock

clock:  clock.o $(OBJFILES)
        $(CC) $(CFLAGS) -o clock clock.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

charset.o:      charset.h
clock.o:        charset.h display.h

#
# Housekeeping
#

Archive:        archive.tgz

archive.tgz:    $(SOURCEFILES) Makefile
        tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
        -/bin/rm -f $(OBJFILES) clock.o core

realclean:        clean
        -/bin/rm -f clock