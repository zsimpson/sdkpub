noinst_PROGRAMS = vmdemotk

vmdemotk_SOURCES = CommandConcatenation.cpp DataandMorphing.cpp NewTclCommands.cpp VMDemoTk.cpp VMDemoTkInit.cpp

# here you should add all header files, which contains the functionality
# of your shared lib (published for the users)
include_HEADERS =

# here you should add all header files, which shouldn't be installed
noinst_HEADERS = CommandConcatenation.h DataandMorphing.h Globals.h NewTclCommands.h VMDemoTk.h VMDemoTkInit.h

EXTRA_DIST = iniparse.tcl interface.tcl media

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
vmdemotk_LDADD = 

INCLUDES += -I./include -I./ -I../../cv/include -I../../otherlibs/highgui @DEBUG@ $(X_CFLAGS)

LIBS += -ltcl8.3 -ltk8.3 -L../../cv/src -lopencv -L../../otherlibs/highgui -lhighgui $(X_LIBS)

