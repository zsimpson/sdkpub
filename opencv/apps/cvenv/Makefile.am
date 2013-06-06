noinst_PROGRAMS = cvenv
#seance

cvenv_SOURCES = colorer.cpp cvenv2.cpp filelist.cpp main.cpp initeic.cpp add.cpp

# here you should add all header files, which contains the functionality
# of your shared lib (published for the users)
include_HEADERS = 


SUBDIRS = pictures EiC include samples

# here you should add all header files, which shouldn't be installed
noinst_HEADERS = colorer.h cvenv.h filelist.h initeic.h

EXTRA_DIST = cvenv.tcl plugins.conf cvenv.dsp seance.dsp

INCLUDES = -I EiC
# add here the libraries which have to be include
# for building the shared lib
#
#  please consider also the usage of the make environment variables
#  like
#  $(LIB_KDEUI), $(LIB_QT), $(LIB_HTML), etc.
#  instead of the hardcoded entries, which have placed
#  in here.
#  The following line is only a suggestion!
#
cvenv_LDADD = @TCLTKLIB@ -lpthread -LEiC -LEiC/stdClib -leic -lstdClib -ldl

CFLAGS += @DEBUG@
