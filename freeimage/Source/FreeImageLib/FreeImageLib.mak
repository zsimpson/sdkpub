# Microsoft Developer Studio Generated NMAKE File, Based on FreeImageLib.dsp
!IF "$(CFG)" == ""
CFG=FreeImageLib - Win32 Debug
!MESSAGE No configuration specified. Defaulting to FreeImageLib - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "FreeImageLib - Win32 Release" && "$(CFG)" != "FreeImageLib - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FreeImageLib.mak" CFG="FreeImageLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FreeImageLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "FreeImageLib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "FreeImageLib - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\FreeImage.lib"

!ELSE 

ALL : "ZLib - Win32 Release" "LibTIFF - Win32 Release" "LibPNG - Win32 Release" "LibMNG - Win32 Release" "LibJPEG - Win32 Release" "$(OUTDIR)\FreeImage.lib"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"LibJPEG - Win32 ReleaseCLEAN" "LibMNG - Win32 ReleaseCLEAN" "LibPNG - Win32 ReleaseCLEAN" "LibTIFF - Win32 ReleaseCLEAN" "ZLib - Win32 ReleaseCLEAN" 
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
	-@erase "$(OUTDIR)\FreeImage.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\\" /I "..\ZLib" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "FREEIMAGE_LIB" /Fp"$(INTDIR)\FreeImageLib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FreeImageLib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\FreeImage.lib" 
LIB32_OBJS= \
	"$(INTDIR)\NNQuantizer.obj" \
	"$(INTDIR)\WuQuantizer.obj" \
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
	"..\LibJPEG\Release\LibJPEG.lib" \
	"..\LibMNG\Release\LibMNG.lib" \
	"..\LibPNG\Release\LibPNG.lib" \
	"..\LibTIFF\Release\LibTIFF.lib" \
	"..\ZLib\Release\ZLib.lib"

"$(OUTDIR)\FreeImage.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "ZLib - Win32 Release" "LibTIFF - Win32 Release" "LibPNG - Win32 Release" "LibMNG - Win32 Release" "LibJPEG - Win32 Release" "$(OUTDIR)\FreeImage.lib"
   copy Release\FreeImage.lib ..\..\Dist
	copy ..\FreeImage.h ..\..\Dist
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "FreeImageLib - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\FreeImaged.lib"

!ELSE 

ALL : "ZLib - Win32 Debug" "LibTIFF - Win32 Debug" "LibPNG - Win32 Debug" "LibMNG - Win32 Debug" "LibJPEG - Win32 Debug" "$(OUTDIR)\FreeImaged.lib"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"LibJPEG - Win32 DebugCLEAN" "LibMNG - Win32 DebugCLEAN" "LibPNG - Win32 DebugCLEAN" "LibTIFF - Win32 DebugCLEAN" "ZLib - Win32 DebugCLEAN" 
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
	-@erase "$(OUTDIR)\FreeImaged.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\\" /I "..\ZLib" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "FREEIMAGE_LIB" /Fp"$(INTDIR)\FreeImageLib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FreeImageLib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\FreeImaged.lib" 
LIB32_OBJS= \
	"$(INTDIR)\NNQuantizer.obj" \
	"$(INTDIR)\WuQuantizer.obj" \
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
	"..\LibJPEG\Debug\LibJPEG.lib" \
	"..\LibMNG\Debug\LibMNG.lib" \
	"..\LibPNG\Debug\LibPNG.lib" \
	"..\LibTIFF\Debug\LibTIFF.lib" \
	"..\ZLib\Debug\ZLib.lib"

"$(OUTDIR)\FreeImaged.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "ZLib - Win32 Debug" "LibTIFF - Win32 Debug" "LibPNG - Win32 Debug" "LibMNG - Win32 Debug" "LibJPEG - Win32 Debug" "$(OUTDIR)\FreeImaged.lib"
   copy Debug\FreeImaged.lib ..\..\Dist
	copy ..\FreeImage.h ..\..\Dist
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("FreeImageLib.dep")
!INCLUDE "FreeImageLib.dep"
!ELSE 
!MESSAGE Warning: cannot find "FreeImageLib.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "FreeImageLib - Win32 Release" || "$(CFG)" == "FreeImageLib - Win32 Debug"
SOURCE=..\FreeImage\NNQuantizer.cpp

"$(INTDIR)\NNQuantizer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\WuQuantizer.cpp

"$(INTDIR)\WuQuantizer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\Conversion.cpp

"$(INTDIR)\Conversion.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\Conversion16_555.cpp

"$(INTDIR)\Conversion16_555.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\Conversion16_565.cpp

"$(INTDIR)\Conversion16_565.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\Conversion24.cpp

"$(INTDIR)\Conversion24.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\Conversion32.cpp

"$(INTDIR)\Conversion32.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\Conversion4.cpp

"$(INTDIR)\Conversion4.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\Conversion8.cpp

"$(INTDIR)\Conversion8.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\ConversionRGBF.cpp

"$(INTDIR)\ConversionRGBF.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\ConversionType.cpp

"$(INTDIR)\ConversionType.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\Halftoning.cpp

"$(INTDIR)\Halftoning.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\tmoColorConvert.cpp

"$(INTDIR)\tmoColorConvert.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\tmoDrago03.cpp

"$(INTDIR)\tmoDrago03.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\tmoReinhard05.cpp

"$(INTDIR)\tmoReinhard05.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\ToneMapping.cpp

"$(INTDIR)\ToneMapping.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\Plugin.cpp

"$(INTDIR)\Plugin.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\PluginBMP.cpp

"$(INTDIR)\PluginBMP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\PluginCUT.cpp

"$(INTDIR)\PluginCUT.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\PluginDDS.cpp

"$(INTDIR)\PluginDDS.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\PluginGIF.cpp

"$(INTDIR)\PluginGIF.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\PluginHDR.cpp

"$(INTDIR)\PluginHDR.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\PluginICO.cpp

"$(INTDIR)\PluginICO.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\PluginIFF.cpp

"$(INTDIR)\PluginIFF.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\PluginJPEG.cpp

"$(INTDIR)\PluginJPEG.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\PluginKOALA.cpp

"$(INTDIR)\PluginKOALA.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\PluginMNG.cpp

"$(INTDIR)\PluginMNG.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\PluginPCD.cpp

"$(INTDIR)\PluginPCD.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\PluginPCX.cpp

"$(INTDIR)\PluginPCX.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\PluginPNG.cpp

"$(INTDIR)\PluginPNG.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\PluginPNM.cpp

"$(INTDIR)\PluginPNM.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\PluginPSD.cpp

"$(INTDIR)\PluginPSD.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\PluginRAS.cpp

"$(INTDIR)\PluginRAS.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\PluginTARGA.cpp

"$(INTDIR)\PluginTARGA.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\PluginTIFF.cpp

"$(INTDIR)\PluginTIFF.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\PluginWBMP.cpp

"$(INTDIR)\PluginWBMP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\PluginXBM.cpp

"$(INTDIR)\PluginXBM.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\PluginXPM.cpp

"$(INTDIR)\PluginXPM.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\DeprecationManager\DeprecationMgr.cpp

"$(INTDIR)\DeprecationMgr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\CacheFile.cpp

"$(INTDIR)\CacheFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\MultiPage.cpp

"$(INTDIR)\MultiPage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\ZLibInterface.cpp

"$(INTDIR)\ZLibInterface.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Metadata\Exif.cpp

"$(INTDIR)\Exif.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Metadata\FIRational.cpp

"$(INTDIR)\FIRational.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Metadata\FreeImageTag.cpp

"$(INTDIR)\FreeImageTag.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Metadata\IPTC.cpp

"$(INTDIR)\IPTC.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Metadata\TagConversion.cpp

"$(INTDIR)\TagConversion.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Metadata\TagLib.cpp

"$(INTDIR)\TagLib.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Metadata\XTIFF.cpp

"$(INTDIR)\XTIFF.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\BitmapAccess.cpp

"$(INTDIR)\BitmapAccess.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\ColorLookup.cpp

"$(INTDIR)\ColorLookup.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\FreeImage.cpp

"$(INTDIR)\FreeImage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\FreeImageIO.cpp

"$(INTDIR)\FreeImageIO.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\GetType.cpp

"$(INTDIR)\GetType.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\MemoryIO.cpp

"$(INTDIR)\MemoryIO.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImage\PixelAccess.cpp

"$(INTDIR)\PixelAccess.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImageToolkit\BSplineRotate.cpp

"$(INTDIR)\BSplineRotate.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImageToolkit\Channels.cpp

"$(INTDIR)\Channels.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImageToolkit\ClassicRotate.cpp

"$(INTDIR)\ClassicRotate.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImageToolkit\Colors.cpp

"$(INTDIR)\Colors.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImageToolkit\CopyPaste.cpp

"$(INTDIR)\CopyPaste.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImageToolkit\Display.cpp

"$(INTDIR)\Display.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImageToolkit\Flip.cpp

"$(INTDIR)\Flip.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImageToolkit\JPEGTransform.cpp

"$(INTDIR)\JPEGTransform.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImageToolkit\Rescale.cpp

"$(INTDIR)\Rescale.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FreeImageToolkit\Resize.cpp

"$(INTDIR)\Resize.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!IF  "$(CFG)" == "FreeImageLib - Win32 Release"

"LibJPEG - Win32 Release" : 
   cd "..\LibJPEG"
   $(MAKE) /$(MAKEFLAGS) /F .\LibJPEG.mak CFG="LibJPEG - Win32 Release" 
   cd "..\FreeImageLib"

"LibJPEG - Win32 ReleaseCLEAN" : 
   cd "..\LibJPEG"
   $(MAKE) /$(MAKEFLAGS) /F .\LibJPEG.mak CFG="LibJPEG - Win32 Release" RECURSE=1 CLEAN 
   cd "..\FreeImageLib"

!ELSEIF  "$(CFG)" == "FreeImageLib - Win32 Debug"

"LibJPEG - Win32 Debug" : 
   cd "..\LibJPEG"
   $(MAKE) /$(MAKEFLAGS) /F .\LibJPEG.mak CFG="LibJPEG - Win32 Debug" 
   cd "..\FreeImageLib"

"LibJPEG - Win32 DebugCLEAN" : 
   cd "..\LibJPEG"
   $(MAKE) /$(MAKEFLAGS) /F .\LibJPEG.mak CFG="LibJPEG - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\FreeImageLib"

!ENDIF 

!IF  "$(CFG)" == "FreeImageLib - Win32 Release"

"LibMNG - Win32 Release" : 
   cd "..\LibMNG"
   $(MAKE) /$(MAKEFLAGS) /F .\LibMNG.mak CFG="LibMNG - Win32 Release" 
   cd "..\FreeImageLib"

"LibMNG - Win32 ReleaseCLEAN" : 
   cd "..\LibMNG"
   $(MAKE) /$(MAKEFLAGS) /F .\LibMNG.mak CFG="LibMNG - Win32 Release" RECURSE=1 CLEAN 
   cd "..\FreeImageLib"

!ELSEIF  "$(CFG)" == "FreeImageLib - Win32 Debug"

"LibMNG - Win32 Debug" : 
   cd "..\LibMNG"
   $(MAKE) /$(MAKEFLAGS) /F .\LibMNG.mak CFG="LibMNG - Win32 Debug" 
   cd "..\FreeImageLib"

"LibMNG - Win32 DebugCLEAN" : 
   cd "..\LibMNG"
   $(MAKE) /$(MAKEFLAGS) /F .\LibMNG.mak CFG="LibMNG - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\FreeImageLib"

!ENDIF 

!IF  "$(CFG)" == "FreeImageLib - Win32 Release"

"LibPNG - Win32 Release" : 
   cd "..\LibPNG"
   $(MAKE) /$(MAKEFLAGS) /F .\LibPNG.mak CFG="LibPNG - Win32 Release" 
   cd "..\FreeImageLib"

"LibPNG - Win32 ReleaseCLEAN" : 
   cd "..\LibPNG"
   $(MAKE) /$(MAKEFLAGS) /F .\LibPNG.mak CFG="LibPNG - Win32 Release" RECURSE=1 CLEAN 
   cd "..\FreeImageLib"

!ELSEIF  "$(CFG)" == "FreeImageLib - Win32 Debug"

"LibPNG - Win32 Debug" : 
   cd "..\LibPNG"
   $(MAKE) /$(MAKEFLAGS) /F .\LibPNG.mak CFG="LibPNG - Win32 Debug" 
   cd "..\FreeImageLib"

"LibPNG - Win32 DebugCLEAN" : 
   cd "..\LibPNG"
   $(MAKE) /$(MAKEFLAGS) /F .\LibPNG.mak CFG="LibPNG - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\FreeImageLib"

!ENDIF 

!IF  "$(CFG)" == "FreeImageLib - Win32 Release"

"LibTIFF - Win32 Release" : 
   cd "..\LibTIFF"
   $(MAKE) /$(MAKEFLAGS) /F .\LibTIFF.mak CFG="LibTIFF - Win32 Release" 
   cd "..\FreeImageLib"

"LibTIFF - Win32 ReleaseCLEAN" : 
   cd "..\LibTIFF"
   $(MAKE) /$(MAKEFLAGS) /F .\LibTIFF.mak CFG="LibTIFF - Win32 Release" RECURSE=1 CLEAN 
   cd "..\FreeImageLib"

!ELSEIF  "$(CFG)" == "FreeImageLib - Win32 Debug"

"LibTIFF - Win32 Debug" : 
   cd "..\LibTIFF"
   $(MAKE) /$(MAKEFLAGS) /F .\LibTIFF.mak CFG="LibTIFF - Win32 Debug" 
   cd "..\FreeImageLib"

"LibTIFF - Win32 DebugCLEAN" : 
   cd "..\LibTIFF"
   $(MAKE) /$(MAKEFLAGS) /F .\LibTIFF.mak CFG="LibTIFF - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\FreeImageLib"

!ENDIF 

!IF  "$(CFG)" == "FreeImageLib - Win32 Release"

"ZLib - Win32 Release" : 
   cd "..\ZLib"
   $(MAKE) /$(MAKEFLAGS) /F .\ZLib.mak CFG="ZLib - Win32 Release" 
   cd "..\FreeImageLib"

"ZLib - Win32 ReleaseCLEAN" : 
   cd "..\ZLib"
   $(MAKE) /$(MAKEFLAGS) /F .\ZLib.mak CFG="ZLib - Win32 Release" RECURSE=1 CLEAN 
   cd "..\FreeImageLib"

!ELSEIF  "$(CFG)" == "FreeImageLib - Win32 Debug"

"ZLib - Win32 Debug" : 
   cd "..\ZLib"
   $(MAKE) /$(MAKEFLAGS) /F .\ZLib.mak CFG="ZLib - Win32 Debug" 
   cd "..\FreeImageLib"

"ZLib - Win32 DebugCLEAN" : 
   cd "..\ZLib"
   $(MAKE) /$(MAKEFLAGS) /F .\ZLib.mak CFG="ZLib - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\FreeImageLib"

!ENDIF 


!ENDIF 

