# Microsoft Developer Studio Project File - Name="CV" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=CV - Win32 Debug Static
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CV.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CV.mak" CFG="CV - Win32 Debug Static"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CV - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CV - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CV - Win32 Release Static" (based on "Win32 (x86) Static Library")
!MESSAGE "CV - Win32 Debug Static" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "CV - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\_temp\CV_Rls"
# PROP Intermediate_Dir "..\..\_temp\CV_Rls"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
F90=df.exe
LIB32=link.exe -lib
CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /G6 /MD /W4 /GX /O2 /Ob2 /I "..\src" /I "..\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "CV_DLL" /FR /Yu"_cv.h" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
RSC=rc.exe
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib /nologo /subsystem:windows /dll /pdb:none /machine:I386 /out:"..\..\bin\CV.dll" /implib:"../../lib/CV.lib"
# SUBTRACT LINK32 /map /debug

!ELSEIF  "$(CFG)" == "CV - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\_temp\CV_Dbg"
# PROP Intermediate_Dir "..\..\_temp\CV_Dbg"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
F90=df.exe
LIB32=link.exe -lib
CPP=cl.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /I "..\src" /I "..\include" /I "\sdk\dx8\include" /I "\sdk\dx8\samples\Multimedia\DirectShow\BaseClasses" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "CV_DLL" /FR /Yu"_cv.h" /FD /GZ /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
RSC=rc.exe
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib /nologo /subsystem:windows /dll /pdb:none /debug /machine:I386 /out:"..\..\bin\CVd.dll" /implib:"../../lib/CVd.lib"

!ELSEIF  "$(CFG)" == "CV - Win32 Release Static"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "CV___Win32_Release_Static"
# PROP BASE Intermediate_Dir "CV___Win32_Release_Static"
# PROP BASE Ignore_Export_Lib 1
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\_temp\CV_Rlsl"
# PROP Intermediate_Dir "..\..\_temp\CV_Rlsl"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
F90=df.exe
LINK32=link.exe
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
CPP=cl.exe
# ADD BASE CPP /nologo /G6 /MT /W4 /GX /Zi /O1 /Ob2 /I "..\src" /I "..\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL_EXPORTS" /FR /YX /FD /c
# ADD CPP /nologo /G6 /MT /W4 /GX /O2 /Ob2 /I "..\src" /I "..\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "CV_STATIC" /FR /Yu"_cv.h" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../../lib/CVl.lib"
# ADD LIB32 /nologo /out:"../../lib/CVl.lib"

!ELSEIF  "$(CFG)" == "CV - Win32 Debug Static"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CV___Win32_Debug_Static"
# PROP BASE Intermediate_Dir "CV___Win32_Debug_Static"
# PROP BASE Ignore_Export_Lib 1
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\_temp\CV_Dbgl"
# PROP Intermediate_Dir "..\..\_temp\CV_Dbgl"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
F90=df.exe
LINK32=link.exe
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
CPP=cl.exe
# ADD BASE CPP /nologo /MTd /W4 /Gm /GX /Zi /Od /I "..\src" /I "..\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL_EXPORTS" /FR /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /Zi /Od /I "..\src" /I "..\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "CV_STATIC" /FR /Yu"_cv.h" /FD /GZ /c
RSC=rc.exe
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../../lib/CVld.lib"
# ADD LIB32 /nologo /out:"../../lib/CVld.lib"

!ENDIF 

# Begin Target

# Name "CV - Win32 Release"
# Name "CV - Win32 Debug"
# Name "CV - Win32 Release Static"
# Name "CV - Win32 Debug Static"
# Begin Group "Src"

# PROP Default_Filter ""
# Begin Group "Geometry"

# PROP Default_Filter ".cpp;.inl"
# Begin Source File

SOURCE=..\src\cvConvHull.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvEllipseFit.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvGeometry.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvGeometryWrap.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CvLineFit.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CvProject.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvRotCalipers.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvSubdivision2D.cpp
# End Source File
# End Group
# Begin Group "Image"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\cvImage.cpp
# End Source File
# End Group
# Begin Group "Trackers"

# PROP Default_Filter ""
# Begin Group "Camshift"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\camshift.cpp
# End Source File
# End Group
# End Group
# Begin Group "Filters"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\cvConDens.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvKalman.cpp
# End Source File
# End Group
# Begin Group "Thresholds"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\cvAdapThresh.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvThresh.cpp
# End Source File
# End Group
# Begin Group "Matrix"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\cvCalcCovarMatrix.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvJacobiEigens.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvmathfuncs.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvmatmul.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvMatrix.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvMatrix64d.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvSvd.cpp
# End Source File
# End Group
# Begin Group "ImageStatistics"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\cvMean.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvMeanSdv.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvMinMaxLoc.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvMoments.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvNorm.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvSumPixels.cpp
# End Source File
# End Group
# Begin Group "CamShift_"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\cvCamShift.cpp
# End Source File
# End Group
# Begin Group "Histograms"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\cvCalcContrastHistogram.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvEMD.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvHistogram.cpp
# End Source File
# End Group
# Begin Group "Contours"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\cvApprox.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvContourArea.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvContours.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvContoursMoments.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvContourTree.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvDominants.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvMatchContours.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvPGH.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvShapeDescr.cpp
# End Source File
# End Group
# Begin Group "MotionTemplates"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\cvMoTempl.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvMotSeg.cpp
# End Source File
# End Group
# Begin Group "Drawing"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\cvDrawing.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvOutText.cpp
# End Source File
# End Group
# Begin Group "Utilities"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\cvAlloc.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cverror.cpp

!IF  "$(CFG)" == "CV - Win32 Release"

!ELSEIF  "$(CFG)" == "CV - Win32 Debug"

!ELSEIF  "$(CFG)" == "CV - Win32 Release Static"

!ELSEIF  "$(CFG)" == "CV - Win32 Debug Static"

# ADD CPP /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\src\cvprecomp.cpp
# ADD CPP /Yc"_cv.h"
# End Source File
# Begin Source File

SOURCE=..\src\cvSamplers.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvtables.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvTemplMatch.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvUtilitiesWrap.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvutils.cpp
# End Source File
# End Group
# Begin Group "DistanceTransform"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\cvDisTransform.cpp
# End Source File
# End Group
# Begin Group "HoughTransform"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\cvHough.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvHoughDiv.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvHoughP.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvHoughWrap.cpp
# End Source File
# End Group
# Begin Group "POSIT"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\cvPOSIT.cpp
# End Source File
# End Group
# Begin Group "Snakes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\cvSnakes.cpp
# End Source File
# End Group
# Begin Group "OpticalFlow"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\cvLkPyramid.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvOptFlowBM.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvOptFlowHS.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvOptFlowLK.cpp
# End Source File
# End Group
# Begin Group "DataStructures"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\cvDataStructs.cpp
# End Source File
# End Group
# Begin Group "EigenObjects"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\cvCalcCovarMatrixEx.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvCalcEigenObjects.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvEigenDecomposite.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvEigenObjectsWrap.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvEigenProjection.cpp
# End Source File
# End Group
# Begin Group "Morphology"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\cvMorph.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvMorphWrap.cpp
# End Source File
# End Group
# Begin Group "Pyramids"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\cvpyramids.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvPyrSegmentation.cpp
# End Source File
# End Group
# Begin Group "FloodFill"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\cvFloodFill.cpp
# End Source File
# End Group
# Begin Group "GestureRecognition"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\cvCalcImageHomography.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvCalcProbDensity.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvCreateHandMask.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvFindHandRegion.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvGestureRecognition.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvMaxRect.cpp
# End Source File
# End Group
# Begin Group "ViewMorphing"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\cvCorrespond.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvFundam.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvLines.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvLMedS.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvMorphing.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvPrewarp.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvScanlines.cpp
# End Source File
# End Group
# Begin Group "FixFilt"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\cvBlur.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvConvGen.cpp

!IF  "$(CFG)" == "CV - Win32 Release"

# ADD CPP /O2

!ELSEIF  "$(CFG)" == "CV - Win32 Debug"

!ELSEIF  "$(CFG)" == "CV - Win32 Release Static"

!ELSEIF  "$(CFG)" == "CV - Win32 Debug Static"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\src\cvFilterWr.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvInitConvol.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvLaplace.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvScharr.cpp
# End Source File
# End Group
# Begin Group "BkGround"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\cvAbsDiff.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvAccum.cpp
# End Source File
# End Group
# Begin Group "FeatureDetection"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\cvCanny.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvCorner.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvCornerSubPix.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvDetectWr.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvfeatureselect.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvMinEVal.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvPreCorner.cpp
# End Source File
# End Group
# Begin Group "Calibration"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\cvCalibInit.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvCalibration.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvUnDistort.cpp
# End Source File
# End Group
# Begin Group "HMM"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\cvHMM.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvHMMObs.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvHMMWrap.cpp
# End Source File
# End Group
# Begin Group "Switcher"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\cvSwitcher.cpp

!IF  "$(CFG)" == "CV - Win32 Release"

# ADD CPP /O2 /Ob2 /Yu

!ELSEIF  "$(CFG)" == "CV - Win32 Debug"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "CV - Win32 Release Static"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "CV - Win32 Debug Static"

# ADD CPP /Yu

!ENDIF 

# End Source File
# End Group
# Begin Group "Array"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\cvaffine.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvarithm.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvarray.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvcolor.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvconvert.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvcopy.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvlogic.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvrand.cpp
# End Source File
# End Group
# End Group
# Begin Group "Include"

# PROP Default_Filter ""
# Begin Group "External"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Include\CV.h
# End Source File
# Begin Source File

SOURCE=..\Include\CV.hpp
# End Source File
# Begin Source File

SOURCE=..\include\cvcompat.h
# End Source File
# Begin Source File

SOURCE=..\include\Cverror.h
# End Source File
# Begin Source File

SOURCE=..\Include\CvPixelAccess.h
# End Source File
# Begin Source File

SOURCE=..\Include\CvStorage.hpp
# End Source File
# Begin Source File

SOURCE=..\Include\CVTypes.h
# End Source File
# Begin Source File

SOURCE=..\include\ipl.h
# End Source File
# Begin Source File

SOURCE=..\include\iplerror.h
# End Source File
# Begin Source File

SOURCE=..\include\iplmisc.h
# End Source File
# End Group
# Begin Group "Internal"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\_CV.h
# End Source File
# Begin Source File

SOURCE=..\src\_cvarr.h
# End Source File
# Begin Source File

SOURCE=..\src\_cvDataStructs.h
# End Source File
# Begin Source File

SOURCE=..\src\_CvError.h
# End Source File
# Begin Source File

SOURCE=..\src\_cvfuncn.h
# End Source File
# Begin Source File

SOURCE=..\src\_cvGeom.h
# End Source File
# Begin Source File

SOURCE=..\src\_cvList.h
# End Source File
# Begin Source File

SOURCE=..\src\_cvmatrix.h
# End Source File
# Begin Source File

SOURCE=..\src\_cvMorphology.h
# End Source File
# Begin Source File

SOURCE=..\src\_cvoptions.h
# End Source File
# Begin Source File

SOURCE=..\src\_cvtables.h
# End Source File
# Begin Source File

SOURCE=..\src\_cvUtils.h
# End Source File
# Begin Source File

SOURCE=..\src\_cvVM.h
# End Source File
# Begin Source File

SOURCE=..\src\_cvWrap.h
# End Source File
# Begin Source File

SOURCE=..\src\_ipcv.h
# End Source File
# Begin Source File

SOURCE=..\src\_optcv.h
# End Source File
# End Group
# End Group
# End Target
# End Project
