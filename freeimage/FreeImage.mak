# Microsoft Developer Studio Generated NMAKE File, Based on FreeImage.dsp
!IF "$(CFG)" == ""
CFG=FreeImage - Win32 Debug
!MESSAGE No configuration specified. Defaulting to FreeImage - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "FreeImage - Win32 Release" && "$(CFG)" != "FreeImage - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FreeImage.mak" CFG="FreeImage - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FreeImage - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "FreeImage - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "FreeImage - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\FreeImage.dll"

!ELSE 

ALL : "LibMNG - Win32 Release" "ZLib - Win32 Release" "LibTIFF - Win32 Release" "LibPNG - Win32 Release" "LibJPEG - Win32 Release" "$(OUTDIR)\FreeImage.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"LibJPEG - Win32 ReleaseCLEAN" "LibPNG - Win32 ReleaseCLEAN" "LibTIFF - Win32 ReleaseCLEAN" "ZLib - Win32 ReleaseCLEAN" "LibMNG - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\BitmapAccess.obj"
	-@erase "$(INTDIR)\BSplineRotate.obj"
	-@erase "$(INTDIR)\CacheFile.obj"
	-@erase "$(INTDIR)\Channels.obj"
	-@erase "$(INTDIR)\ClassicRotate.obj"
	-@erase "$(INTDIR)\ColorLookup.obj"
	-@erase "$(INTDIR)\Colors.obj"
	-@erase "$(INTDIR)\Conversion.obj"
	-@erase "$(INTDIR)\Conversion16_555.obj"
	-@erase "$(INTDIR)\Conversion16_565.obj"
	-@erase "$(INTDIR)\Conversion24.obj"
	-@erase "$(INTDIR)\Conversion32.obj"
	-@erase "$(INTDIR)\Conversion4.obj"
	-@erase "$(INTDIR)\Conversion8.obj"
	-@erase "$(INTDIR)\ConversionRGBF.obj"
	-@erase "$(INTDIR)\ConversionType.obj"
	-@erase "$(INTDIR)\CopyPaste.obj"
	-@erase "$(INTDIR)\DeprecationMgr.obj"
	-@erase "$(INTDIR)\Display.obj"
	-@erase "$(INTDIR)\Exif.obj"
	-@erase "$(INTDIR)\FIRational.obj"
	-@erase "$(INTDIR)\Flip.obj"
	-@erase "$(INTDIR)\FreeImage.obj"
	-@erase "$(INTDIR)\FreeImage.res"
	-@erase "$(INTDIR)\FreeImageC.obj"
	-@erase "$(INTDIR)\FreeImageIO.obj"
	-@erase "$(INTDIR)\FreeImageTag.obj"
	-@erase "$(INTDIR)\GetType.obj"
	-@erase "$(INTDIR)\Halftoning.obj"
	-@erase "$(INTDIR)\IPTC.obj"
	-@erase "$(INTDIR)\JPEGTransform.obj"
	-@erase "$(INTDIR)\MemoryIO.obj"
	-@erase "$(INTDIR)\MultiPage.obj"
	-@erase "$(INTDIR)\NNQuantizer.obj"
	-@erase "$(INTDIR)\PixelAccess.obj"
	-@erase "$(INTDIR)\Plugin.obj"
	-@erase "$(INTDIR)\PluginBMP.obj"
	-@erase "$(INTDIR)\PluginCUT.obj"
	-@erase "$(INTDIR)\PluginDDS.obj"
	-@erase "$(INTDIR)\PluginGIF.obj"
	-@erase "$(INTDIR)\PluginHDR.obj"
	-@erase "$(INTDIR)\PluginICO.obj"
	-@erase "$(INTDIR)\PluginIFF.obj"
	-@erase "$(INTDIR)\PluginJPEG.obj"
	-@erase "$(INTDIR)\PluginKOALA.obj"
	-@erase "$(INTDIR)\PluginMNG.obj"
	-@erase "$(INTDIR)\PluginPCD.obj"
	-@erase "$(INTDIR)\PluginPCX.obj"
	-@erase "$(INTDIR)\PluginPNG.obj"
	-@erase "$(INTDIR)\PluginPNM.obj"
	-@erase "$(INTDIR)\PluginPSD.obj"
	-@erase "$(INTDIR)\PluginRAS.obj"
	-@erase "$(INTDIR)\PluginTARGA.obj"
	-@erase "$(INTDIR)\PluginTIFF.obj"
	-@erase "$(INTDIR)\PluginWBMP.obj"
	-@erase "$(INTDIR)\PluginXBM.obj"
	-@erase "$(INTDIR)\PluginXPM.obj"
	-@erase "$(INTDIR)\Rescale.obj"
	-@erase "$(INTDIR)\Resize.obj"
	-@erase "$(INTDIR)\TagConversion.obj"
	-@erase "$(INTDIR)\TagLib.obj"
	-@erase "$(INTDIR)\tmoColorConvert.obj"
	-@erase "$(INTDIR)\tmoDrago03.obj"
	-@erase "$(INTDIR)\tmoReinhard05.obj"
	-@erase "$(INTDIR)\ToneMapping.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WuQuantizer.obj"
	-@erase "$(INTDIR)\XTIFF.obj"
	-@erase "$(INTDIR)\ZLibInterface.obj"
	-@erase "$(OUTDIR)\FreeImage.dll"
	-@erase "$(OUTDIR)\FreeImage.exp"
	-@erase "$(OUTDIR)\FreeImage.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "Source" /I "Source\ZLib" /I "Source\DeprecationManager" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FREEIMAGE_EXPORTS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\FreeImage.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FreeImage.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\FreeImage.pdb" /machine:I386 /out:"$(OUTDIR)\FreeImage.dll" /implib:"$(OUTDIR)\FreeImage.lib" 
LINK32_OBJS= \
	"$(INTDIR)\Plugin.obj" \
	"$(INTDIR)\PluginBMP.obj" \
	"$(INTDIR)\PluginCUT.obj" \
	"$(INTDIR)\PluginDDS.obj" \
	"$(INTDIR)\PluginGIF.obj" \
	"$(INTDIR)\PluginHDR.obj" \
	"$(INTDIR)\PluginICO.obj" \
	"$(INTDIR)\PluginIFF.obj" \
	"$(INTDIR)\PluginJPEG.obj" \
	"$(INTDIR)\PluginKOALA.obj" \
	"$(INTDIR)\PluginMNG.obj" \
	"$(INTDIR)\PluginPCD.obj" \
	"$(INTDIR)\PluginPCX.obj" \
	"$(INTDIR)\PluginPNG.obj" \
	"$(INTDIR)\PluginPNM.obj" \
	"$(INTDIR)\PluginPSD.obj" \
	"$(INTDIR)\PluginRAS.obj" \
	"$(INTDIR)\PluginTARGA.obj" \
	"$(INTDIR)\PluginTIFF.obj" \
	"$(INTDIR)\PluginWBMP.obj" \
	"$(INTDIR)\PluginXBM.obj" \
	"$(INTDIR)\PluginXPM.obj" \
	"$(INTDIR)\Conversion.obj" \
	"$(INTDIR)\Conversion16_555.obj" \
	"$(INTDIR)\Conversion16_565.obj" \
	"$(INTDIR)\Conversion24.obj" \
	"$(INTDIR)\Conversion32.obj" \
	"$(INTDIR)\Conversion4.obj" \
	"$(INTDIR)\Conversion8.obj" \
	"$(INTDIR)\ConversionRGBF.obj" \
	"$(INTDIR)\ConversionType.obj" \
	"$(INTDIR)\Halftoning.obj" \
	"$(INTDIR)\tmoColorConvert.obj" \
	"$(INTDIR)\tmoDrago03.obj" \
	"$(INTDIR)\tmoReinhard05.obj" \
	"$(INTDIR)\ToneMapping.obj" \
	"$(INTDIR)\NNQuantizer.obj" \
	"$(INTDIR)\WuQuantizer.obj" \
	"$(INTDIR)\DeprecationMgr.obj" \
	"$(INTDIR)\CacheFile.obj" \
	"$(INTDIR)\MultiPage.obj" \
	"$(INTDIR)\ZLibInterface.obj" \
	"$(INTDIR)\Exif.obj" \
	"$(INTDIR)\FIRational.obj" \
	"$(INTDIR)\FreeImageTag.obj" \
	"$(INTDIR)\IPTC.obj" \
	"$(INTDIR)\TagConversion.obj" \
	"$(INTDIR)\TagLib.obj" \
	"$(INTDIR)\XTIFF.obj" \
	"$(INTDIR)\BitmapAccess.obj" \
	"$(INTDIR)\ColorLookup.obj" \
	"$(INTDIR)\FreeImage.obj" \
	"$(INTDIR)\FreeImageC.obj" \
	"$(INTDIR)\FreeImageIO.obj" \
	"$(INTDIR)\GetType.obj" \
	"$(INTDIR)\MemoryIO.obj" \
	"$(INTDIR)\PixelAccess.obj" \
	"$(INTDIR)\BSplineRotate.obj" \
	"$(INTDIR)\Channels.obj" \
	"$(INTDIR)\ClassicRotate.obj" \
	"$(INTDIR)\Colors.obj" \
	"$(INTDIR)\CopyPaste.obj" \
	"$(INTDIR)\Display.obj" \
	"$(INTDIR)\Flip.obj" \
	"$(INTDIR)\JPEGTransform.obj" \
	"$(INTDIR)\Rescale.obj" \
	"$(INTDIR)\Resize.obj" \
	"$(INTDIR)\FreeImage.res" \
	".\Source\LibJPEG\Release\LibJPEG.lib" \
	".\Source\LibPNG\Release\LibPNG.lib" \
	".\Source\LibTIFF\Release\LibTIFF.lib" \
	".\Source\ZLib\Release\ZLib.lib" \
	".\Source\LibMNG\Release\LibMNG.lib"

"$(OUTDIR)\FreeImage.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "LibMNG - Win32 Release" "ZLib - Win32 Release" "LibTIFF - Win32 Release" "LibPNG - Win32 Release" "LibJPEG - Win32 Release" "$(OUTDIR)\FreeImage.dll"
   copy Release\FreeImage.dll Dist
	copy Release\FreeImage.lib Dist
	copy Source\FreeImage.h Dist
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "FreeImage - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\FreeImaged.dll"

!ELSE 

ALL : "LibMNG - Win32 Debug" "ZLib - Win32 Debug" "LibTIFF - Win32 Debug" "LibPNG - Win32 Debug" "LibJPEG - Win32 Debug" "$(OUTDIR)\FreeImaged.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"LibJPEG - Win32 DebugCLEAN" "LibPNG - Win32 DebugCLEAN" "LibTIFF - Win32 DebugCLEAN" "ZLib - Win32 DebugCLEAN" "LibMNG - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\BitmapAccess.obj"
	-@erase "$(INTDIR)\BSplineRotate.obj"
	-@erase "$(INTDIR)\CacheFile.obj"
	-@erase "$(INTDIR)\Channels.obj"
	-@erase "$(INTDIR)\ClassicRotate.obj"
	-@erase "$(INTDIR)\ColorLookup.obj"
	-@erase "$(INTDIR)\Colors.obj"
	-@erase "$(INTDIR)\Conversion.obj"
	-@erase "$(INTDIR)\Conversion16_555.obj"
	-@erase "$(INTDIR)\Conversion16_565.obj"
	-@erase "$(INTDIR)\Conversion24.obj"
	-@erase "$(INTDIR)\Conversion32.obj"
	-@erase "$(INTDIR)\Conversion4.obj"
	-@erase "$(INTDIR)\Conversion8.obj"
	-@erase "$(INTDIR)\ConversionRGBF.obj"
	-@erase "$(INTDIR)\ConversionType.obj"
	-@erase "$(INTDIR)\CopyPaste.obj"
	-@erase "$(INTDIR)\DeprecationMgr.obj"
	-@erase "$(INTDIR)\Display.obj"
	-@erase "$(INTDIR)\Exif.obj"
	-@erase "$(INTDIR)\FIRational.obj"
	-@erase "$(INTDIR)\Flip.obj"
	-@erase "$(INTDIR)\FreeImage.obj"
	-@erase "$(INTDIR)\FreeImage.res"
	-@erase "$(INTDIR)\FreeImageC.obj"
	-@erase "$(INTDIR)\FreeImageIO.obj"
	-@erase "$(INTDIR)\FreeImageTag.obj"
	-@erase "$(INTDIR)\GetType.obj"
	-@erase "$(INTDIR)\Halftoning.obj"
	-@erase "$(INTDIR)\IPTC.obj"
	-@erase "$(INTDIR)\JPEGTransform.obj"
	-@erase "$(INTDIR)\MemoryIO.obj"
	-@erase "$(INTDIR)\MultiPage.obj"
	-@erase "$(INTDIR)\NNQuantizer.obj"
	-@erase "$(INTDIR)\PixelAccess.obj"
	-@erase "$(INTDIR)\Plugin.obj"
	-@erase "$(INTDIR)\PluginBMP.obj"
	-@erase "$(INTDIR)\PluginCUT.obj"
	-@erase "$(INTDIR)\PluginDDS.obj"
	-@erase "$(INTDIR)\PluginGIF.obj"
	-@erase "$(INTDIR)\PluginHDR.obj"
	-@erase "$(INTDIR)\PluginICO.obj"
	-@erase "$(INTDIR)\PluginIFF.obj"
	-@erase "$(INTDIR)\PluginJPEG.obj"
	-@erase "$(INTDIR)\PluginKOALA.obj"
	-@erase "$(INTDIR)\PluginMNG.obj"
	-@erase "$(INTDIR)\PluginPCD.obj"
	-@erase "$(INTDIR)\PluginPCX.obj"
	-@erase "$(INTDIR)\PluginPNG.obj"
	-@erase "$(INTDIR)\PluginPNM.obj"
	-@erase "$(INTDIR)\PluginPSD.obj"
	-@erase "$(INTDIR)\PluginRAS.obj"
	-@erase "$(INTDIR)\PluginTARGA.obj"
	-@erase "$(INTDIR)\PluginTIFF.obj"
	-@erase "$(INTDIR)\PluginWBMP.obj"
	-@erase "$(INTDIR)\PluginXBM.obj"
	-@erase "$(INTDIR)\PluginXPM.obj"
	-@erase "$(INTDIR)\Rescale.obj"
	-@erase "$(INTDIR)\Resize.obj"
	-@erase "$(INTDIR)\TagConversion.obj"
	-@erase "$(INTDIR)\TagLib.obj"
	-@erase "$(INTDIR)\tmoColorConvert.obj"
	-@erase "$(INTDIR)\tmoDrago03.obj"
	-@erase "$(INTDIR)\tmoReinhard05.obj"
	-@erase "$(INTDIR)\ToneMapping.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WuQuantizer.obj"
	-@erase "$(INTDIR)\XTIFF.obj"
	-@erase "$(INTDIR)\ZLibInterface.obj"
	-@erase "$(OUTDIR)\FreeImaged.dll"
	-@erase "$(OUTDIR)\FreeImaged.exp"
	-@erase "$(OUTDIR)\FreeImaged.ilk"
	-@erase "$(OUTDIR)\FreeImaged.lib"
	-@erase "$(OUTDIR)\FreeImaged.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "Source" /I "Source\ZLib" /I "Source\DeprecationManager" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FREEIMAGE_EXPORTS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\FreeImage.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FreeImage.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\FreeImaged.pdb" /debug /machine:I386 /out:"$(OUTDIR)\FreeImaged.dll" /implib:"$(OUTDIR)\FreeImaged.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\Plugin.obj" \
	"$(INTDIR)\PluginBMP.obj" \
	"$(INTDIR)\PluginCUT.obj" \
	"$(INTDIR)\PluginDDS.obj" \
	"$(INTDIR)\PluginGIF.obj" \
	"$(INTDIR)\PluginHDR.obj" \
	"$(INTDIR)\PluginICO.obj" \
	"$(INTDIR)\PluginIFF.obj" \
	"$(INTDIR)\PluginJPEG.obj" \
	"$(INTDIR)\PluginKOALA.obj" \
	"$(INTDIR)\PluginMNG.obj" \
	"$(INTDIR)\PluginPCD.obj" \
	"$(INTDIR)\PluginPCX.obj" \
	"$(INTDIR)\PluginPNG.obj" \
	"$(INTDIR)\PluginPNM.obj" \
	"$(INTDIR)\PluginPSD.obj" \
	"$(INTDIR)\PluginRAS.obj" \
	"$(INTDIR)\PluginTARGA.obj" \
	"$(INTDIR)\PluginTIFF.obj" \
	"$(INTDIR)\PluginWBMP.obj" \
	"$(INTDIR)\PluginXBM.obj" \
	"$(INTDIR)\PluginXPM.obj" \
	"$(INTDIR)\Conversion.obj" \
	"$(INTDIR)\Conversion16_555.obj" \
	"$(INTDIR)\Conversion16_565.obj" \
	"$(INTDIR)\Conversion24.obj" \
	"$(INTDIR)\Conversion32.obj" \
	"$(INTDIR)\Conversion4.obj" \
	"$(INTDIR)\Conversion8.obj" \
	"$(INTDIR)\ConversionRGBF.obj" \
	"$(INTDIR)\ConversionType.obj" \
	"$(INTDIR)\Halftoning.obj" \
	"$(INTDIR)\tmoColorConvert.obj" \
	"$(INTDIR)\tmoDrago03.obj" \
	"$(INTDIR)\tmoReinhard05.obj" \
	"$(INTDIR)\ToneMapping.obj" \
	"$(INTDIR)\NNQuantizer.obj" \
	"$(INTDIR)\WuQuantizer.obj" \
	"$(INTDIR)\DeprecationMgr.obj" \
	"$(INTDIR)\CacheFile.obj" \
	"$(INTDIR)\MultiPage.obj" \
	"$(INTDIR)\ZLibInterface.obj" \
	"$(INTDIR)\Exif.obj" \
	"$(INTDIR)\FIRational.obj" \
	"$(INTDIR)\FreeImageTag.obj" \
	"$(INTDIR)\IPTC.obj" \
	"$(INTDIR)\TagConversion.obj" \
	"$(INTDIR)\TagLib.obj" \
	"$(INTDIR)\XTIFF.obj" \
	"$(INTDIR)\BitmapAccess.obj" \
	"$(INTDIR)\ColorLookup.obj" \
	"$(INTDIR)\FreeImage.obj" \
	"$(INTDIR)\FreeImageC.obj" \
	"$(INTDIR)\FreeImageIO.obj" \
	"$(INTDIR)\GetType.obj" \
	"$(INTDIR)\MemoryIO.obj" \
	"$(INTDIR)\PixelAccess.obj" \
	"$(INTDIR)\BSplineRotate.obj" \
	"$(INTDIR)\Channels.obj" \
	"$(INTDIR)\ClassicRotate.obj" \
	"$(INTDIR)\Colors.obj" \
	"$(INTDIR)\CopyPaste.obj" \
	"$(INTDIR)\Display.obj" \
	"$(INTDIR)\Flip.obj" \
	"$(INTDIR)\JPEGTransform.obj" \
	"$(INTDIR)\Rescale.obj" \
	"$(INTDIR)\Resize.obj" \
	"$(INTDIR)\FreeImage.res" \
	".\Source\LibJPEG\Debug\LibJPEG.lib" \
	".\Source\LibPNG\Debug\LibPNG.lib" \
	".\Source\LibTIFF\Debug\LibTIFF.lib" \
	".\Source\ZLib\Debug\ZLib.lib" \
	".\Source\LibMNG\Debug\LibMNG.lib"

"$(OUTDIR)\FreeImaged.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "LibMNG - Win32 Debug" "ZLib - Win32 Debug" "LibTIFF - Win32 Debug" "LibPNG - Win32 Debug" "LibJPEG - Win32 Debug" "$(OUTDIR)\FreeImaged.dll"
   copy Debug\FreeImaged.dll Dist
	copy Debug\FreeImaged.lib Dist
	copy Source\FreeImage.h Dist
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("FreeImage.dep")
!INCLUDE "FreeImage.dep"
!ELSE 
!MESSAGE Warning: cannot find "FreeImage.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "FreeImage - Win32 Release" || "$(CFG)" == "FreeImage - Win32 Debug"
SOURCE=.\Source\FreeImage\Plugin.cpp

"$(INTDIR)\Plugin.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\PluginBMP.cpp

"$(INTDIR)\PluginBMP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\PluginCUT.cpp

"$(INTDIR)\PluginCUT.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\PluginDDS.cpp

"$(INTDIR)\PluginDDS.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\PluginGIF.cpp

"$(INTDIR)\PluginGIF.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\PluginHDR.cpp

"$(INTDIR)\PluginHDR.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\PluginICO.cpp

"$(INTDIR)\PluginICO.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\PluginIFF.cpp

"$(INTDIR)\PluginIFF.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\PluginJPEG.cpp

"$(INTDIR)\PluginJPEG.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\PluginKOALA.cpp

"$(INTDIR)\PluginKOALA.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\PluginMNG.cpp

"$(INTDIR)\PluginMNG.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\PluginPCD.cpp

"$(INTDIR)\PluginPCD.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\PluginPCX.cpp

"$(INTDIR)\PluginPCX.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\PluginPNG.cpp

"$(INTDIR)\PluginPNG.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\PluginPNM.cpp

"$(INTDIR)\PluginPNM.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\PluginPSD.cpp

"$(INTDIR)\PluginPSD.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\PluginRAS.cpp

"$(INTDIR)\PluginRAS.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\PluginTARGA.cpp

"$(INTDIR)\PluginTARGA.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\PluginTIFF.cpp

"$(INTDIR)\PluginTIFF.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\PluginWBMP.cpp

"$(INTDIR)\PluginWBMP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\PluginXBM.cpp

"$(INTDIR)\PluginXBM.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\PluginXPM.cpp

"$(INTDIR)\PluginXPM.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\Conversion.cpp

"$(INTDIR)\Conversion.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\Conversion16_555.cpp

"$(INTDIR)\Conversion16_555.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\Conversion16_565.cpp

"$(INTDIR)\Conversion16_565.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\Conversion24.cpp

"$(INTDIR)\Conversion24.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\Conversion32.cpp

"$(INTDIR)\Conversion32.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\Conversion4.cpp

"$(INTDIR)\Conversion4.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\Conversion8.cpp

"$(INTDIR)\Conversion8.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\ConversionRGBF.cpp

"$(INTDIR)\ConversionRGBF.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\ConversionType.cpp

"$(INTDIR)\ConversionType.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\Halftoning.cpp

"$(INTDIR)\Halftoning.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\tmoColorConvert.cpp

"$(INTDIR)\tmoColorConvert.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\tmoDrago03.cpp

"$(INTDIR)\tmoDrago03.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\tmoReinhard05.cpp

"$(INTDIR)\tmoReinhard05.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\ToneMapping.cpp

"$(INTDIR)\ToneMapping.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\NNQuantizer.cpp

"$(INTDIR)\NNQuantizer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\WuQuantizer.cpp

"$(INTDIR)\WuQuantizer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\DeprecationManager\DeprecationMgr.cpp

"$(INTDIR)\DeprecationMgr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\CacheFile.cpp

"$(INTDIR)\CacheFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\MultiPage.cpp

"$(INTDIR)\MultiPage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\ZLibInterface.cpp

"$(INTDIR)\ZLibInterface.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\Metadata\Exif.cpp

"$(INTDIR)\Exif.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\Metadata\FIRational.cpp

"$(INTDIR)\FIRational.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\Metadata\FreeImageTag.cpp

"$(INTDIR)\FreeImageTag.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\Metadata\IPTC.cpp

"$(INTDIR)\IPTC.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\Metadata\TagConversion.cpp

"$(INTDIR)\TagConversion.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\Metadata\TagLib.cpp

"$(INTDIR)\TagLib.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\Metadata\XTIFF.cpp

"$(INTDIR)\XTIFF.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\BitmapAccess.cpp

"$(INTDIR)\BitmapAccess.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\ColorLookup.cpp

"$(INTDIR)\ColorLookup.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\FreeImage.cpp

"$(INTDIR)\FreeImage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\FreeImage.rc

"$(INTDIR)\FreeImage.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\FreeImageC.c

"$(INTDIR)\FreeImageC.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\FreeImageIO.cpp

"$(INTDIR)\FreeImageIO.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\GetType.cpp

"$(INTDIR)\GetType.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\MemoryIO.cpp

"$(INTDIR)\MemoryIO.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImage\PixelAccess.cpp

"$(INTDIR)\PixelAccess.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImageToolkit\BSplineRotate.cpp

"$(INTDIR)\BSplineRotate.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImageToolkit\Channels.cpp

"$(INTDIR)\Channels.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImageToolkit\ClassicRotate.cpp

"$(INTDIR)\ClassicRotate.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImageToolkit\Colors.cpp

"$(INTDIR)\Colors.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImageToolkit\CopyPaste.cpp

"$(INTDIR)\CopyPaste.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImageToolkit\Display.cpp

"$(INTDIR)\Display.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImageToolkit\Flip.cpp

"$(INTDIR)\Flip.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImageToolkit\JPEGTransform.cpp

"$(INTDIR)\JPEGTransform.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImageToolkit\Rescale.cpp

"$(INTDIR)\Rescale.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Source\FreeImageToolkit\Resize.cpp

"$(INTDIR)\Resize.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!IF  "$(CFG)" == "FreeImage - Win32 Release"

"LibJPEG - Win32 Release" : 
   cd ".\Source\LibJPEG"
   $(MAKE) /$(MAKEFLAGS) /F .\LibJPEG.mak CFG="LibJPEG - Win32 Release" 
   cd "..\.."

"LibJPEG - Win32 ReleaseCLEAN" : 
   cd ".\Source\LibJPEG"
   $(MAKE) /$(MAKEFLAGS) /F .\LibJPEG.mak CFG="LibJPEG - Win32 Release" RECURSE=1 CLEAN 
   cd "..\.."

!ELSEIF  "$(CFG)" == "FreeImage - Win32 Debug"

"LibJPEG - Win32 Debug" : 
   cd ".\Source\LibJPEG"
   $(MAKE) /$(MAKEFLAGS) /F .\LibJPEG.mak CFG="LibJPEG - Win32 Debug" 
   cd "..\.."

"LibJPEG - Win32 DebugCLEAN" : 
   cd ".\Source\LibJPEG"
   $(MAKE) /$(MAKEFLAGS) /F .\LibJPEG.mak CFG="LibJPEG - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\.."

!ENDIF 

!IF  "$(CFG)" == "FreeImage - Win32 Release"

"LibPNG - Win32 Release" : 
   cd ".\Source\LibPNG"
   $(MAKE) /$(MAKEFLAGS) /F .\LibPNG.mak CFG="LibPNG - Win32 Release" 
   cd "..\.."

"LibPNG - Win32 ReleaseCLEAN" : 
   cd ".\Source\LibPNG"
   $(MAKE) /$(MAKEFLAGS) /F .\LibPNG.mak CFG="LibPNG - Win32 Release" RECURSE=1 CLEAN 
   cd "..\.."

!ELSEIF  "$(CFG)" == "FreeImage - Win32 Debug"

"LibPNG - Win32 Debug" : 
   cd ".\Source\LibPNG"
   $(MAKE) /$(MAKEFLAGS) /F .\LibPNG.mak CFG="LibPNG - Win32 Debug" 
   cd "..\.."

"LibPNG - Win32 DebugCLEAN" : 
   cd ".\Source\LibPNG"
   $(MAKE) /$(MAKEFLAGS) /F .\LibPNG.mak CFG="LibPNG - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\.."

!ENDIF 

!IF  "$(CFG)" == "FreeImage - Win32 Release"

"LibTIFF - Win32 Release" : 
   cd ".\Source\LibTIFF"
   $(MAKE) /$(MAKEFLAGS) /F .\LibTIFF.mak CFG="LibTIFF - Win32 Release" 
   cd "..\.."

"LibTIFF - Win32 ReleaseCLEAN" : 
   cd ".\Source\LibTIFF"
   $(MAKE) /$(MAKEFLAGS) /F .\LibTIFF.mak CFG="LibTIFF - Win32 Release" RECURSE=1 CLEAN 
   cd "..\.."

!ELSEIF  "$(CFG)" == "FreeImage - Win32 Debug"

"LibTIFF - Win32 Debug" : 
   cd ".\Source\LibTIFF"
   $(MAKE) /$(MAKEFLAGS) /F .\LibTIFF.mak CFG="LibTIFF - Win32 Debug" 
   cd "..\.."

"LibTIFF - Win32 DebugCLEAN" : 
   cd ".\Source\LibTIFF"
   $(MAKE) /$(MAKEFLAGS) /F .\LibTIFF.mak CFG="LibTIFF - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\.."

!ENDIF 

!IF  "$(CFG)" == "FreeImage - Win32 Release"

"ZLib - Win32 Release" : 
   cd ".\Source\ZLib"
   $(MAKE) /$(MAKEFLAGS) /F .\ZLib.mak CFG="ZLib - Win32 Release" 
   cd "..\.."

"ZLib - Win32 ReleaseCLEAN" : 
   cd ".\Source\ZLib"
   $(MAKE) /$(MAKEFLAGS) /F .\ZLib.mak CFG="ZLib - Win32 Release" RECURSE=1 CLEAN 
   cd "..\.."

!ELSEIF  "$(CFG)" == "FreeImage - Win32 Debug"

"ZLib - Win32 Debug" : 
   cd ".\Source\ZLib"
   $(MAKE) /$(MAKEFLAGS) /F .\ZLib.mak CFG="ZLib - Win32 Debug" 
   cd "..\.."

"ZLib - Win32 DebugCLEAN" : 
   cd ".\Source\ZLib"
   $(MAKE) /$(MAKEFLAGS) /F .\ZLib.mak CFG="ZLib - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\.."

!ENDIF 

!IF  "$(CFG)" == "FreeImage - Win32 Release"

"LibMNG - Win32 Release" : 
   cd ".\Source\LibMNG"
   $(MAKE) /$(MAKEFLAGS) /F .\LibMNG.mak CFG="LibMNG - Win32 Release" 
   cd "..\.."

"LibMNG - Win32 ReleaseCLEAN" : 
   cd ".\Source\LibMNG"
   $(MAKE) /$(MAKEFLAGS) /F .\LibMNG.mak CFG="LibMNG - Win32 Release" RECURSE=1 CLEAN 
   cd "..\.."

!ELSEIF  "$(CFG)" == "FreeImage - Win32 Debug"

"LibMNG - Win32 Debug" : 
   cd ".\Source\LibMNG"
   $(MAKE) /$(MAKEFLAGS) /F .\LibMNG.mak CFG="LibMNG - Win32 Debug" 
   cd "..\.."

"LibMNG - Win32 DebugCLEAN" : 
   cd ".\Source\LibMNG"
   $(MAKE) /$(MAKEFLAGS) /F .\LibMNG.mak CFG="LibMNG - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\.."

!ENDIF 


!ENDIF 

