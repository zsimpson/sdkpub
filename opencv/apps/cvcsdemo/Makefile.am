noinst_PROGRAMS = cvcsdemo
#seance

cvcsdemo_SOURCES = csdemoview.cpp cvcsdemo.cpp

# here you should add all header files, which contains the functionality
# of your shared lib (published for the users)
include_HEADERS =

SUBDIRS = pictures

# here you should add all header files, which shouldn't be installed
noinst_HEADERS = csdemoview.h cvcsdemo.h

EXTRA_DIST = cvcsdemo.tcl

INCLUDES = -O -I../../otherlibs/highgui -I../../otherlibs/cvcam/include -I../../cv/include
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
cvcsdemo_LDADD = -ltcl8.3 -ltk8.3 -L../../cv/src -lopencv -L../../otherlibs/highgui -lhighgui -L../../otherlibs/cvcam/src/unix -lcvvideo
CFLAGS += @DEBUG@
CXXFLAGS += @DEBUG@

#cvcsdemo_LIBS = 
