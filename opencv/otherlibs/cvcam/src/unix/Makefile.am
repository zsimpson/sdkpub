lib_LTLIBRARIES = libcvvideo.la

libcvvideo_la_SOURCES = convert.cpp cvvideo.cpp dialogs.cpp render.cpp


EXTRA_DIST = 

SOMAJOR = @MMINOR@
SOMINOR = @MMAJOR@
SOSUBMINOR = @MSUBMINOR@

# here you should add all header files, which contains the functionality
# of your shared lib (published for the users)
include_HEADERS =

# here you should add all header files, which shouldn
noinst_HEADERS = convert.h cvvidtypes.h dialogs.h icvvideo.h render.h videodev.h

libcvvideo_la_LDFLAGS = $(all_libraries) -no-undefined -version-info $(SOMAJOR):$(SOMINOR):$(SOSUBMINOR) $(LDFLAGS) $(X_LIBS) -L../../../highgui/.libs -L../../../../cv/src/.libs

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
libcvvideo_la_LIBADD = -lX11 -lXext

INCLUDES = $(all_includes) -I../../include -I../../../../cv/include -I../../../highgui

CFLAGS += @DEBUG@
CXXFLAGS += @DEBUG@
