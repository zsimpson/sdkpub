# Microsoft Developer Studio Project File - Name="CvlA" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=CvlA - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "cvla.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "cvla.mak" CFG="CvlA - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CvlA - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "CvlA - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CvlA - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\_temp\CvlA_Rls"
# PROP Intermediate_Dir "..\..\..\_temp\CvlA_Rls"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE F90 /include:"Release/"
# ADD F90 /include:"..\..\..\..\_temp\CvlA_Rls/"
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W4 /GX /Zi /O2 /Ob2 /I "..\..\..\..\OtherLibs\_Mkl\include" /I "..\..\Ats\include" /I "..\..\Trs\include" /I "..\Include" /I "..\..\..\CV\include" /I "..\..\..\OtherLibs\_Ipl\include" /I "..\..\..\CV\src" /I "..\..\..\OtherLibs\HighGUI" /I "..\..\..\cvaux\Include" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_CVL" /D "WIN32" /D "IPL_WINDOWS" /FR /Yu"cvtest.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 cv.lib kernel32.lib mkl_c.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ipl.lib comctl32.lib HighGUI.lib /nologo /subsystem:console /machine:I386 /out:"..\..\..\Bin\cvlA.exe" /libpath:"..\..\..\OtherLibs\_IPL\LIB\MSVC" /libpath:"..\..\..\OtherLibs\_Mkl\lib\Default\Intel\\" /libpath:"..\..\..\lib"

!ELSEIF  "$(CFG)" == "CvlA - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\_temp\CvlA_Dbg"
# PROP Intermediate_Dir "..\..\..\_temp\CvlA_Dbg"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE F90 /include:"Debug/"
# ADD F90 /include:"..\..\..\..\_temp\CvlA_Dbg/"
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /I "..\..\..\OtherLibs\_Mkl\include" /I "..\..\Ats\include" /I "..\..\Trs\include" /I "..\Include" /I "..\..\..\CV\include" /I "..\..\..\OtherLibs\_Ipl\include" /I "..\..\..\CV\src" /I "..\..\..\OtherLibs\HighGUI" /I "..\..\..\cvaux\Include" /I "\sdk\dx8\include" /I "\sdk\dx8\samples\Multimedia\DirectShow\BaseClasses" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "WIN32" /D "_CVL_DEBUG" /D "_CVL" /D "IPL_WINDOWS" /FR /Yu"cvtest.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 cvd.lib kernel32.lib mkl_c.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ipl.lib comctl32.lib HighGUId.lib /nologo /subsystem:console /profile /debug /machine:I386 /out:"..\..\..\Bin\cvlAd.exe" /libpath:"..\..\..\OtherLibs\_IPL\LIB\MSVC" /libpath:"..\..\..\OtherLibs\_Mkl\lib\Default\Intel\\" /libpath:"..\..\..\lib"

!ENDIF 

# Begin Target

# Name "CvlA - Win32 Release"
# Name "CvlA - Win32 Debug"
# Begin Group "Src"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Contours"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\aApproxPoly.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aContourCollection.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aContourMoments.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aContours.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aContoursMatch.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aCreateContourTree.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aMatchContourTrees.cpp
# End Source File
# End Group
# Begin Group "Pyramids"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\aPyramids.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aPyrSegmentation.cpp
# End Source File
# End Group
# Begin Group "DistanceTransform"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\aDistanceTransform.cpp
# End Source File
# End Group
# Begin Group "Thresholds"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\aAdaptThresh.cpp

!IF  "$(CFG)" == "CvlA - Win32 Release"

!ELSEIF  "$(CFG)" == "CvlA - Win32 Debug"

# ADD CPP /W4

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Src\aThresh.cpp
# End Source File
# End Group
# Begin Group "CamShift"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\aCamShift.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aMeanShift.cpp
# End Source File
# End Group
# Begin Group "Pixel Access"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\aPixelAccess.cpp
# End Source File
# End Group
# Begin Group "Histograms(C)"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\aCalcContrastHist.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aEMD.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aHistograms.cpp
# End Source File
# End Group
# Begin Group "FloodFill"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=..\Src\aFloodFill.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aFloodFill8.cpp
# End Source File
# End Group
# Begin Group "Common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\uContours.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\uIplUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\uReadFile.cpp
# End Source File
# End Group
# Begin Group "Morphology"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\aMorphology.cpp
# End Source File
# End Group
# Begin Group "ImageStatistics"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\aImageStatistics.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aMoments.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aNorm.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aNormMask.cpp
# End Source File
# End Group
# Begin Group "HoughTransform"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\aHoughTransform.cpp
# End Source File
# End Group
# Begin Group "Geometry"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\aconvhull.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\afitellipse.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aFitLines.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aminarearect.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aSubdivisions.cpp
# End Source File
# End Group
# Begin Group "EigenObjects"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=..\Src\aEigenObjects.cpp
# End Source File
# End Group
# Begin Group "BkGround"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\aAbsDiff.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aAccum.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aMaskAccum.cpp
# End Source File
# End Group
# Begin Group "Utilities"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\aConvert.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\akmeans.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aMathUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aSamplers.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aTemplMatch.cpp
# End Source File
# End Group
# Begin Group "DataStructures"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\aSequence.cpp
# End Source File
# End Group
# Begin Group "Drawing"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\aDrawing.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\adrawing_regress.cpp
# End Source File
# End Group
# Begin Group "MotionTemplates"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\aMotionTemplates.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aMotSeg.cpp
# End Source File
# End Group
# Begin Group "OpticalFlow"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\aOptFlowHS.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aOptFlowLK.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aOptFlowPyrLK.cpp
# End Source File
# End Group
# Begin Group "GestureRecognition"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\aGestureRecognition.cpp
# End Source File
# End Group
# Begin Group "FixFilt"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\aLaplace.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aScharr.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aSobel.cpp
# End Source File
# End Group
# Begin Group "Matrix"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\aMatrix.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aMatrix2.cpp
# End Source File
# Begin Source File

SOURCE=..\src\asvd.cpp
# End Source File
# End Group
# Begin Group "Detection"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\aCanny.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aCorner.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aMinEVal.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aPreCorner.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\canny.cpp
# End Source File
# End Group
# Begin Group "Image"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\aarithm.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aimage.cpp
# End Source File
# Begin Source File

SOURCE=..\src\alogic.cpp
# End Source File
# End Group
# Begin Group "POSIT"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\aposit.cpp
# End Source File
# End Group
# Begin Group "Filters"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\aCondens.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aKalman.cpp
# End Source File
# End Group
# Begin Group "Snakes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\asnakes.cpp
# End Source File
# End Group
# Begin Group "Calibration"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=..\Src\aCameraCalibration.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aChessCorners.cpp
# End Source File
# Begin Source File

SOURCE=..\Src\aUnDistort.cpp
# End Source File
# End Group
# Begin Group "HMM"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\aHMMObs.cpp
# End Source File
# End Group
# Begin Group "HistogramsHPP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\aarrayiterator.cpp
# End Source File
# Begin Source File

SOURCE=..\src\abackproject.cpp
# End Source File
# Begin Source File

SOURCE=..\src\acalculate.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ahistogram.cpp
# End Source File
# Begin Source File

SOURCE=..\src\anodeiterator.cpp
# End Source File
# Begin Source File

SOURCE=..\src\aoperations.cpp
# End Source File
# Begin Source File

SOURCE=..\src\astoragearray.cpp
# End Source File
# Begin Source File

SOURCE=..\src\atree.cpp
# End Source File
# Begin Source File

SOURCE=..\src\atreeiterator.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\Src\tsysA.cpp
# ADD CPP /Yc"cvtest.h"
# End Source File
# End Group
# Begin Group "Include"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\_ATS\Include\ats.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CV\Include\CV.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CV\Include\CV.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\cvaux\include\cvaux.h
# End Source File
# Begin Source File

SOURCE=..\..\..\cv\include\cvcompat.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CV\include\Cverror.h
# End Source File
# Begin Source File

SOURCE=..\Include\CvmTest.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CV\Include\CvPixelAccess.h
# End Source File
# Begin Source File

SOURCE=..\Include\CvTest.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CV\Include\CVTypes.h
# End Source File
# End Group
# End Target
# End Project
