noinst_LIBRARIES = libstdClib.a

libstdClib_a_SOURCES = assert.c ctype.c dirent.c eicfftoa.c errno.c fcntl.c itoa.c math.c printf.c signal.c stat.c stdarg.c stdClib.c stdio.c stdlib.c string.c strrev.c strround.c termios.c time.c unistd.c

# here you should add all header files, which contains the functionality
# of your shared lib (published for the users)
include_HEADERS =

# here you should add all header files, which shouldn't be installed
noinst_HEADERS = assert.h ctype.h dirent.h errno.h fcntl.h float.h iso646.h limits.h math.h setjmp.h signal.h stdarg.h stdClib2eic.h stddef.h stdio.h stdlib.h stdliblocal.h string.h termio.h termios.h time.h unistd.h

INCLUDES := $(INCLUDES) -I.. -I../../include -I-

CFLAGS += -ansi -pedantic -O2 -fsigned-char -Wall -D_LINUX -g3
