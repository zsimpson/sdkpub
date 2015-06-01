# Microsoft Developer Studio Generated NMAKE File, Based on LibMNG.dsp
!IF "$(CFG)" == ""
CFG=LibMNG - Win32 Debug
!MESSAGE No configuration specified. Defaulting to LibMNG - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "LibMNG - Win32 Release" && "$(CFG)" != "LibMNG - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LibMNG.mak" CFG="LibMNG - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LibMNG - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "LibMNG - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "LibMNG - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\LibMNG.lib"


CLEAN :
	-@erase "$(INTDIR)\libmng_callback_xs.obj"
	-@erase "$(INTDIR)\libmng_chunk_descr.obj"
	-@erase "$(INTDIR)\libmng_chunk_io.obj"
	-@erase "$(INTDIR)\libmng_chunk_prc.obj"
	-@erase "$(INTDIR)\libmng_chunk_xs.obj"
	-@erase "$(INTDIR)\libmng_cms.obj"
	-@erase "$(INTDIR)\libmng_display.obj"
	-@erase "$(INTDIR)\libmng_dither.obj"
	-@erase "$(INTDIR)\libmng_error.obj"
	-@erase "$(INTDIR)\libmng_filter.obj"
	-@erase "$(INTDIR)\libmng_hlapi.obj"
	-@erase "$(INTDIR)\libmng_jpeg.obj"
	-@erase "$(INTDIR)\libmng_object_prc.obj"
	-@erase "$(INTDIR)\libmng_pixels.obj"
	-@erase "$(INTDIR)\libmng_prop_xs.obj"
	-@erase "$(INTDIR)\libmng_read.obj"
	-@erase "$(INTDIR)\libmng_trace.obj"
	-@erase "$(INTDIR)\libmng_write.obj"
	-@erase "$(INTDIR)\libmng_zlib.obj"
	-@erase "$(INTDIR)\vc*.idb"
	-@erase "$(OUTDIR)\LibMNG.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O1 /I "..\Zlib" /I "..\libjpeg" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\LibMNG.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LibMNG.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\LibMNG.lib" 
LIB32_OBJS= \
	"$(INTDIR)\libmng_callback_xs.obj" \
	"$(INTDIR)\libmng_chunk_descr.obj" \
	"$(INTDIR)\libmng_chunk_io.obj" \
	"$(INTDIR)\libmng_chunk_prc.obj" \
	"$(INTDIR)\libmng_chunk_xs.obj" \
	"$(INTDIR)\libmng_cms.obj" \
	"$(INTDIR)\libmng_display.obj" \
	"$(INTDIR)\libmng_dither.obj" \
	"$(INTDIR)\libmng_error.obj" \
	"$(INTDIR)\libmng_filter.obj" \
	"$(INTDIR)\libmng_hlapi.obj" \
	"$(INTDIR)\libmng_jpeg.obj" \
	"$(INTDIR)\libmng_object_prc.obj" \
	"$(INTDIR)\libmng_pixels.obj" \
	"$(INTDIR)\libmng_prop_xs.obj" \
	"$(INTDIR)\libmng_read.obj" \
	"$(INTDIR)\libmng_trace.obj" \
	"$(INTDIR)\libmng_write.obj" \
	"$(INTDIR)\libmng_zlib.obj"

"$(OUTDIR)\LibMNG.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "LibMNG - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\LibMNG.lib"


CLEAN :
	-@erase "$(INTDIR)\libmng_callback_xs.obj"
	-@erase "$(INTDIR)\libmng_chunk_descr.obj"
	-@erase "$(INTDIR)\libmng_chunk_io.obj"
	-@erase "$(INTDIR)\libmng_chunk_prc.obj"
	-@erase "$(INTDIR)\libmng_chunk_xs.obj"
	-@erase "$(INTDIR)\libmng_cms.obj"
	-@erase "$(INTDIR)\libmng_display.obj"
	-@erase "$(INTDIR)\libmng_dither.obj"
	-@erase "$(INTDIR)\libmng_error.obj"
	-@erase "$(INTDIR)\libmng_filter.obj"
	-@erase "$(INTDIR)\libmng_hlapi.obj"
	-@erase "$(INTDIR)\libmng_jpeg.obj"
	-@erase "$(INTDIR)\libmng_object_prc.obj"
	-@erase "$(INTDIR)\libmng_pixels.obj"
	-@erase "$(INTDIR)\libmng_prop_xs.obj"
	-@erase "$(INTDIR)\libmng_read.obj"
	-@erase "$(INTDIR)\libmng_trace.obj"
	-@erase "$(INTDIR)\libmng_write.obj"
	-@erase "$(INTDIR)\libmng_zlib.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\LibMNG.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\ZLib" /I "..\LibJPEG" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "MNG_BUILD_SO" /Fp"$(INTDIR)\LibMNG.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LibMNG.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\LibMNG.lib" 
LIB32_OBJS= \
	"$(INTDIR)\libmng_callback_xs.obj" \
	"$(INTDIR)\libmng_chunk_descr.obj" \
	"$(INTDIR)\libmng_chunk_io.obj" \
	"$(INTDIR)\libmng_chunk_prc.obj" \
	"$(INTDIR)\libmng_chunk_xs.obj" \
	"$(INTDIR)\libmng_cms.obj" \
	"$(INTDIR)\libmng_display.obj" \
	"$(INTDIR)\libmng_dither.obj" \
	"$(INTDIR)\libmng_error.obj" \
	"$(INTDIR)\libmng_filter.obj" \
	"$(INTDIR)\libmng_hlapi.obj" \
	"$(INTDIR)\libmng_jpeg.obj" \
	"$(INTDIR)\libmng_object_prc.obj" \
	"$(INTDIR)\libmng_pixels.obj" \
	"$(INTDIR)\libmng_prop_xs.obj" \
	"$(INTDIR)\libmng_read.obj" \
	"$(INTDIR)\libmng_trace.obj" \
	"$(INTDIR)\libmng_write.obj" \
	"$(INTDIR)\libmng_zlib.obj"

"$(OUTDIR)\LibMNG.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("LibMNG.dep")
!INCLUDE "LibMNG.dep"
!ELSE 
!MESSAGE Warning: cannot find "LibMNG.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "LibMNG - Win32 Release" || "$(CFG)" == "LibMNG - Win32 Debug"
SOURCE=.\libmng_callback_xs.c

"$(INTDIR)\libmng_callback_xs.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\libmng_chunk_descr.c

"$(INTDIR)\libmng_chunk_descr.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\libmng_chunk_io.c

"$(INTDIR)\libmng_chunk_io.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\libmng_chunk_prc.c

"$(INTDIR)\libmng_chunk_prc.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\libmng_chunk_xs.c

"$(INTDIR)\libmng_chunk_xs.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\libmng_cms.c

"$(INTDIR)\libmng_cms.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\libmng_display.c

"$(INTDIR)\libmng_display.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\libmng_dither.c

"$(INTDIR)\libmng_dither.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\libmng_error.c

"$(INTDIR)\libmng_error.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\libmng_filter.c

"$(INTDIR)\libmng_filter.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\libmng_hlapi.c

"$(INTDIR)\libmng_hlapi.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\libmng_jpeg.c

"$(INTDIR)\libmng_jpeg.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\libmng_object_prc.c

"$(INTDIR)\libmng_object_prc.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\libmng_pixels.c

"$(INTDIR)\libmng_pixels.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\libmng_prop_xs.c

"$(INTDIR)\libmng_prop_xs.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\libmng_read.c

"$(INTDIR)\libmng_read.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\libmng_trace.c

"$(INTDIR)\libmng_trace.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\libmng_write.c

"$(INTDIR)\libmng_write.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\libmng_zlib.c

"$(INTDIR)\libmng_zlib.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

