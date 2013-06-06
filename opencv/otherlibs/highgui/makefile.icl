# Makefile for Intel Proton Compiler 5.0

CXX = icl
LINK = link

!ifdef debug

SUFFIX = d
DR = _Dbg

!else

SUFFIX =
DR = _Rls

!endif    

OUTDLL = ..\..\bin\HighGUI$(SUFFIX).dll
OUTLIB = ..\..\lib\HighGUI$(SUFFIX).lib
OBJS = ..\..\_temp\HighGUI$(DR)\bitstrm.obj ..\..\_temp\HighGUI$(DR)\grfmt_base.obj \
..\..\_temp\HighGUI$(DR)\grfmt_bmp.obj ..\..\_temp\HighGUI$(DR)\grfmt_jpeg.obj \
..\..\_temp\HighGUI$(DR)\grfmt_pxm.obj ..\..\_temp\HighGUI$(DR)\grfmt_sunras.obj \
..\..\_temp\HighGUI$(DR)\grfmt_tiff.obj ..\..\_temp\HighGUI$(DR)\utils.obj \
..\..\_temp\HighGUI$(DR)\image.obj ..\..\_temp\HighGUI$(DR)\loadsave.obj \
..\..\_temp\HighGUI$(DR)\precomp.obj ..\..\_temp\HighGUI$(DR)\window_lnx.obj \
..\..\_temp\HighGUI$(DR)\window_w32.obj 


INC = ./bitstrm.h ./grfmt_base.h ./grfmt_bmp.h ./grfmt_jpeg.h ./grfmt_pxm.h \
./grfmt_sunras.h ./grfmt_tiff.h ./utils.h ./_highgui.h ./grfmts.h ./HighGUI.h 

CXXFLAGS2 = /I"../../cv/include" /I".//" /I"."  /nologo /GX /GB /W4 /I "$(VCHOME)/include"  "/Qwd171,424,981" /Qxi /Qaxi /c /Fo
LINKFLAGS2 = /libpath:..\..\lib /nologo /subsystem:windows /dll /pdb:none /machine:I386 /out:$(OUTDLL) /implib:$(OUTLIB) /nodefaultlib:libm /nodefaultlib:libirc /libpath:"$(VCHOME)/lib"  

!ifdef debug

CXXFLAGS = /D"_MBCS" /D"WIN32" /D"HIGHGUI_EXPORTS" /D"_USRDLL" /D"_WINDOWS" /D"_DEBUG"  /Gm /Zi /Od /FD /GZ $(CXXFLAGS2)
LIBS = cvd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib comctl32.lib 
LINKFLAGS = $(LINKFLAGS2) /debug 

!else

CXXFLAGS = /D"NDEBUG" /D"_MBCS" /D"WIN32" /D"HIGHGUI_EXPORTS" /D"_USRDLL" /D"_WINDOWS"  /O2 /Ob2 $(CXXFLAGS2)
LIBS = cv.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib comctl32.lib 
LINKFLAGS = $(LINKFLAGS2)  

!endif


$(OUTDLL): $(OBJS)
	-mkdir ..\..\bin 2>nul
	-mkdir ..\..\lib 2>nul
	$(LINK)  $(LINKFLAGS) $** $(LIBS) 
	

all: $(OUTDLL)

..\..\_temp\HighGUI$(DR)\bitstrm.obj: .\bitstrm.cpp $(INC)
	@-mkdir ..\..\_temp\HighGUI$(DR) 2>nul
	-$(CXX) $(CXXFLAGS)..\..\_temp\HighGUI$(DR)\bitstrm.obj .\bitstrm.cpp
..\..\_temp\HighGUI$(DR)\grfmt_base.obj: .\grfmt_base.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\HighGUI$(DR)\grfmt_base.obj .\grfmt_base.cpp
..\..\_temp\HighGUI$(DR)\grfmt_bmp.obj: .\grfmt_bmp.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\HighGUI$(DR)\grfmt_bmp.obj .\grfmt_bmp.cpp
..\..\_temp\HighGUI$(DR)\grfmt_jpeg.obj: .\grfmt_jpeg.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\HighGUI$(DR)\grfmt_jpeg.obj .\grfmt_jpeg.cpp
..\..\_temp\HighGUI$(DR)\grfmt_pxm.obj: .\grfmt_pxm.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\HighGUI$(DR)\grfmt_pxm.obj .\grfmt_pxm.cpp
..\..\_temp\HighGUI$(DR)\grfmt_sunras.obj: .\grfmt_sunras.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\HighGUI$(DR)\grfmt_sunras.obj .\grfmt_sunras.cpp
..\..\_temp\HighGUI$(DR)\grfmt_tiff.obj: .\grfmt_tiff.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\HighGUI$(DR)\grfmt_tiff.obj .\grfmt_tiff.cpp
..\..\_temp\HighGUI$(DR)\utils.obj: .\utils.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\HighGUI$(DR)\utils.obj .\utils.cpp
..\..\_temp\HighGUI$(DR)\image.obj: .\image.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\HighGUI$(DR)\image.obj .\image.cpp
..\..\_temp\HighGUI$(DR)\loadsave.obj: .\loadsave.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\HighGUI$(DR)\loadsave.obj .\loadsave.cpp
..\..\_temp\HighGUI$(DR)\precomp.obj: .\precomp.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\HighGUI$(DR)\precomp.obj .\precomp.cpp
..\..\_temp\HighGUI$(DR)\window_lnx.obj: .\window_lnx.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\HighGUI$(DR)\window_lnx.obj .\window_lnx.cpp
..\..\_temp\HighGUI$(DR)\window_w32.obj: .\window_w32.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\HighGUI$(DR)\window_w32.obj .\window_w32.cpp
