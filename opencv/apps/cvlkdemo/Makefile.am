noinst_PROGRAMS = cvlkdemo
#seance

cvlkdemo_SOURCES = cvlkdemo.cpp demoview.cpp tracker.cpp

# here you should add all header files, which contains the functionality
# of your shared lib (published for the users)
include_HEADERS =

SUBDIRS = pictures

# here you should add all header files, which shouldn't be installed
noinst_HEADERS = cvlkdemo.h demoview.h tracker.h

EXTRA_DIST = cvlkdemo.tcl

INCLUDES = -I../../otherlibs/highgui -I../../otherlibs/cvcam/include -I../../cv/include
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
cvlkdemo_LDADD = -ltcl8.3 -ltk8.3 -L../../cv/src -lopencv -L../../otherlibs/highgui -lhighgui -L../../otherlibs/cvcam/src/unix -lcvvideo

CFLAGS += @DEBUG@
CXXFLAGS += @DEBUG@

#cvlkdemo_LIBS = 
