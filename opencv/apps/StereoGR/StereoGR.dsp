# Microsoft Developer Studio Project File - Name="StereoGR" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=StereoGR - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "StereoGR.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "StereoGR.mak" CFG="StereoGR - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "StereoGR - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "StereoGR - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/GR/Apps", CAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "StereoGR - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\_temp\StereoGR_Release"
# PROP Intermediate_Dir "..\..\_temp\StereoGR_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /I "..\..\OtherLibs\PTGrey" /I "..\..\cv\include" /I "..\..\otherlibs\_ipl\include" /I "..\..\OtherLibs\GestRec" /I "..\..\cvaux\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "GR_CONTOUR" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /X
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 cv.lib ipl.lib opengl32.lib glu32.lib triclops.lib GestRec.lib cvaux.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\Bin/StereoGR.exe" /libpath:"..\..\lib" /libpath:"..\..\OtherLibs\_ipl\lib\msvc" /libpath:"..\..\OtherLibs\glut" /libpath:"..\..\OtherLibs\HighGUI"

!ELSEIF  "$(CFG)" == "StereoGR - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\_temp\StereoGR_Debug"
# PROP Intermediate_Dir "..\..\_temp\StereoGR_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\OtherLibs\PTGrey" /I "..\..\cv\include" /I "..\..\otherlibs\_ipl\include" /I "..\..\OtherLibs\glut" /I "..\..\Otherlibs\highgui" /I "..\..\OtherLibs\GestRec" /I "..\..\cvaux\include" /I "\sdk\dx8\include" /I "\sdk\dx8\samples\Multimedia\DirectShow\BaseClasses" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "GR_CONTOUR" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 cvd.lib ipl.lib opengl32.lib glu32.lib triclops.lib GestRec.lib cvauxd.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\Bin/StereoGRd.exe" /pdbtype:sept /libpath:"..\..\lib" /libpath:"..\..\OtherLibs\_ipl\lib\msvc"

!ENDIF 

# Begin Target

# Name "StereoGR - Win32 Release"
# Name "StereoGR - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\DGProp.cpp
# End Source File
# Begin Source File

SOURCE=.\DGStat.cpp
# End Source File
# Begin Source File

SOURCE=.\DynGestServer.cpp
# End Source File
# Begin Source File

SOURCE=.\GestMan.cpp
# End Source File
# Begin Source File

SOURCE=.\GROptions.cpp
# End Source File
# Begin Source File

SOURCE=.\HMMParams.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\OpenGLView.cpp
# End Source File
# Begin Source File

SOURCE=.\PTOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StereoGR.cpp
# End Source File
# Begin Source File

SOURCE=.\StereoGR.rc
# End Source File
# Begin Source File

SOURCE=.\StereoGRDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\StereoGRView.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\DGProp.h
# End Source File
# Begin Source File

SOURCE=.\DGStat.h
# End Source File
# Begin Source File

SOURCE=.\DynGestServer.h
# End Source File
# Begin Source File

SOURCE=.\GestMan.h
# End Source File
# Begin Source File

SOURCE=.\GROptions.h
# End Source File
# Begin Source File

SOURCE=.\HMMParams.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\OpenGLView.h
# End Source File
# Begin Source File

SOURCE=.\PTOffline.h
# End Source File
# Begin Source File

SOURCE=.\PTOptions.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StereoGR.h
# End Source File
# Begin Source File

SOURCE=.\StereoGRDoc.h
# End Source File
# Begin Source File

SOURCE=.\StereoGRView.h
# End Source File
# Begin Source File

SOURCE=.\trackball.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\StereoGR.ico
# End Source File
# Begin Source File

SOURCE=.\res\StereoGR.rc2
# End Source File
# Begin Source File

SOURCE=.\res\StereoGRDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\PTOffline.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
