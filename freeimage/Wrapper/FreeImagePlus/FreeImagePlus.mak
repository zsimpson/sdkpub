# Microsoft Developer Studio Generated NMAKE File, Based on FreeImagePlus.dsp
!IF "$(CFG)" == ""
CFG=FreeImagePlus - Win32 Debug
!MESSAGE No configuration specified. Defaulting to FreeImagePlus - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "FreeImagePlus - Win32 Release" && "$(CFG)" != "FreeImagePlus - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FreeImagePlus.mak" CFG="FreeImagePlus - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FreeImagePlus - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "FreeImagePlus - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "FreeImagePlus - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\FreeImagePlus.dll"

!ELSE 

ALL : "FreeImage - Win32 Release" "$(OUTDIR)\FreeImagePlus.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"FreeImage - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\fipImage.obj"
	-@erase "$(INTDIR)\fipMemoryIO.obj"
	-@erase "$(INTDIR)\fipMultiPage.obj"
	-@erase "$(INTDIR)\fipWinImage.obj"
	-@erase "$(INTDIR)\FreeImagePlus.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\FreeImagePlus.dll"
	-@erase "$(OUTDIR)\FreeImagePlus.exp"
	-@erase "$(OUTDIR)\FreeImagePlus.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "." /I "../../Source" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FIP_EXPORTS" /Fp"$(INTDIR)\FreeImagePlus.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FreeImagePlus.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=../../Dist/FreeImage.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\FreeImagePlus.pdb" /machine:I386 /out:"$(OUTDIR)\FreeImagePlus.dll" /implib:"$(OUTDIR)\FreeImagePlus.lib" 
LINK32_OBJS= \
	"$(INTDIR)\fipImage.obj" \
	"$(INTDIR)\fipMemoryIO.obj" \
	"$(INTDIR)\fipMultiPage.obj" \
	"$(INTDIR)\fipWinImage.obj" \
	"$(INTDIR)\FreeImagePlus.obj" \
	"..\..\Release\FreeImage.lib"

"$(OUTDIR)\FreeImagePlus.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "FreeImage - Win32 Release" "$(OUTDIR)\FreeImagePlus.dll"
   copy         Release\FreeImagePlus.lib         dist\
	copy         Release\FreeImagePlus.dll         dist\
	copy         FreeImagePlus.h         dist\
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "FreeImagePlus - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\FreeImagePlusd.dll"

!ELSE 

ALL : "FreeImage - Win32 Debug" "$(OUTDIR)\FreeImagePlusd.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"FreeImage - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\fipImage.obj"
	-@erase "$(INTDIR)\fipMemoryIO.obj"
	-@erase "$(INTDIR)\fipMultiPage.obj"
	-@erase "$(INTDIR)\fipWinImage.obj"
	-@erase "$(INTDIR)\FreeImagePlus.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\FreeImagePlusd.dll"
	-@erase "$(OUTDIR)\FreeImagePlusd.exp"
	-@erase "$(OUTDIR)\FreeImagePlusd.ilk"
	-@erase "$(OUTDIR)\FreeImagePlusd.lib"
	-@erase "$(OUTDIR)\FreeImagePlusd.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "." /I "../../Source" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FIP_EXPORTS" /Fp"$(INTDIR)\FreeImagePlus.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FreeImagePlus.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=../../Dist/FreeImaged.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\FreeImagePlusd.pdb" /debug /machine:I386 /out:"$(OUTDIR)\FreeImagePlusd.dll" /implib:"$(OUTDIR)\FreeImagePlusd.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\fipImage.obj" \
	"$(INTDIR)\fipMemoryIO.obj" \
	"$(INTDIR)\fipMultiPage.obj" \
	"$(INTDIR)\fipWinImage.obj" \
	"$(INTDIR)\FreeImagePlus.obj" \
	"..\..\Debug\FreeImaged.lib"

"$(OUTDIR)\FreeImagePlusd.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "FreeImage - Win32 Debug" "$(OUTDIR)\FreeImagePlusd.dll"
   copy         Debug\FreeImagePlusd.lib         dist\
	copy         Debug\FreeImagePlusd.dll         dist\
	copy         FreeImagePlus.h         dist\
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("FreeImagePlus.dep")
!INCLUDE "FreeImagePlus.dep"
!ELSE 
!MESSAGE Warning: cannot find "FreeImagePlus.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "FreeImagePlus - Win32 Release" || "$(CFG)" == "FreeImagePlus - Win32 Debug"
SOURCE=.\src\fipImage.cpp

"$(INTDIR)\fipImage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\fipMemoryIO.cpp

"$(INTDIR)\fipMemoryIO.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\fipMultiPage.cpp

"$(INTDIR)\fipMultiPage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\fipWinImage.cpp

"$(INTDIR)\fipWinImage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\FreeImagePlus.cpp

"$(INTDIR)\FreeImagePlus.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!IF  "$(CFG)" == "FreeImagePlus - Win32 Release"

"FreeImage - Win32 Release" : 
   cd "\prj\sdkpub\freeimage"
   $(MAKE) /$(MAKEFLAGS) /F .\FreeImage.mak CFG="FreeImage - Win32 Release" 
   cd ".\Wrapper\FreeImagePlus"

"FreeImage - Win32 ReleaseCLEAN" : 
   cd "\prj\sdkpub\freeimage"
   $(MAKE) /$(MAKEFLAGS) /F .\FreeImage.mak CFG="FreeImage - Win32 Release" RECURSE=1 CLEAN 
   cd ".\Wrapper\FreeImagePlus"

!ELSEIF  "$(CFG)" == "FreeImagePlus - Win32 Debug"

"FreeImage - Win32 Debug" : 
   cd "\prj\sdkpub\freeimage"
   $(MAKE) /$(MAKEFLAGS) /F .\FreeImage.mak CFG="FreeImage - Win32 Debug" 
   cd ".\Wrapper\FreeImagePlus"

"FreeImage - Win32 DebugCLEAN" : 
   cd "\prj\sdkpub\freeimage"
   $(MAKE) /$(MAKEFLAGS) /F .\FreeImage.mak CFG="FreeImage - Win32 Debug" RECURSE=1 CLEAN 
   cd ".\Wrapper\FreeImagePlus"

!ENDIF 


!ENDIF 

