noinst_LIBRARIES = libeic.a

libeic_a_SOURCES = callback.c cdecl.c eicmod.c emitter.c error.c func.c interpre.c lexer.c optomizer.c parser.c preexpr.c preproc.c readline.c reset.c signal.c stab.c starteic.c symbol.c typemod.c typesets.c ymem.c

# here you should add all header files, which contains the functionality
# of your shared lib (published for the users)
include_HEADERS =

# here you should add all header files, which shouldn't be installed
noinst_HEADERS = assertp.h cdecl.h datastruct.h eic.h eicval.h emitter.h error.h func.h global.h lexer.h MachSet.h metric.h modules.h parser.h preproc.h reset.h stab.h symbol.h symentry.h typemod.h typesets.h xalloc.h

EXTRA_DIST = 

SUBDIRS = stdClib

INCLUDES := $(INCLUDES) -I../../include -I-

#CFLAGS += -traditional -ansi -pedantic -O2 -fsigned-char -Wall -D_LINUX -g3
