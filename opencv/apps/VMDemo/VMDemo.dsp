# Microsoft Developer Studio Project File - Name="VMDemo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=VMDemo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VMDemo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VMDemo.mak" CFG="VMDemo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VMDemo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "VMDemo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VMDemo - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\_temp\vmdemo_Rls"
# PROP Intermediate_Dir "..\..\_temp\vmdemo_Rls"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\CV\Include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /i "..\include" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 cv.lib /nologo /subsystem:windows /machine:I386 /out:"..\..\bin\VMDemo.exe" /libpath:"..\..\lib"
# SUBTRACT LINK32 /incremental:yes

!ELSEIF  "$(CFG)" == "VMDemo - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\_temp\vmdemo_Dbg"
# PROP Intermediate_Dir "..\..\_temp\vmdemo_Dbg"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\CV\Include" /I "\sdk\dx8\include" /I "\sdk\dx8\samples\Multimedia\DirectShow\BaseClasses" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /i "..\include" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 cvd.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\bin\VMDemod.exe" /pdbtype:sept /libpath:"..\..\lib"
# SUBTRACT LINK32 /incremental:no

!ENDIF 

# Begin Target

# Name "VMDemo - Win32 Release"
# Name "VMDemo - Win32 Debug"
# Begin Group "Src"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PixelToPixelMorpher.cpp
# End Source File
# Begin Source File

SOURCE=.\Raster.cpp
# End Source File
# Begin Source File

SOURCE=.\ResultImage.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=.\VirtualImage.cpp
# End Source File
# Begin Source File

SOURCE=.\VMDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\VMDemo.rc
# ADD BASE RSC /l 0x419 /i "\USER\VP\opencv\apps\Src" /i "\USER\VP\opencv\Apps\VMDemo\Src" /i "\Users\smoli\CVL3\Apps\VMDemo\Src" /i "\Mosyagin\Projects\CVL\Apps\VMDemo\Src" /i "\EVer\Project\Apps\VMDemo\Src" /i "\USER\VP\StarTeam\Apps\VMDemo\Src" /i "\_Vadim\Alpha_3\Apps\VMDemo\Src" /i "\Mosyagin\ProjectCVL\Apps\VMDemo\Src" /i "\Users\Oblomov\StarTeam\oblomov\Apps\VMDemo\Src" /i "\Users\Oblomov\StarTeam\oblomov\VMDemo\Src" /i "\Proj\VMDemo\Src" /i "\USERS\VP\StarTeam\IppCV\VMDemo\Src" /i "\Proj\IppCV\VMDemo\Src" /i "\USERS\VP\StarTeam\CV\VMDemo\Src"
# SUBTRACT BASE RSC /i "..\include"
# ADD RSC /l 0x419 /i "\USER\VP\opencv\apps\Src" /i "\USER\VP\opencv\Apps\VMDemo\Src" /i "\Users\smoli\CVL3\Apps\VMDemo\Src" /i "\Mosyagin\Projects\CVL\Apps\VMDemo\Src" /i "\EVer\Project\Apps\VMDemo\Src" /i "\USER\VP\StarTeam\Apps\VMDemo\Src" /i "\_Vadim\Alpha_3\Apps\VMDemo\Src" /i "\Mosyagin\ProjectCVL\Apps\VMDemo\Src" /i "\Users\Oblomov\StarTeam\oblomov\Apps\VMDemo\Src" /i "\Users\Oblomov\StarTeam\oblomov\VMDemo\Src" /i "\Proj\VMDemo\Src" /i "\USERS\VP\StarTeam\IppCV\VMDemo\Src" /i "\Proj\IppCV\VMDemo\Src" /i "..\src\res" /i "\USERS\VP\StarTeam\CV\VMDemo\Src"
# SUBTRACT RSC /i "..\include"
# End Source File
# Begin Source File

SOURCE=.\VMDemoDlg.cpp
# End Source File
# End Group
# Begin Group "Include"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Raster.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\ResultImage.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SubdivMorpher.h
# End Source File
# Begin Source File

SOURCE=.\VirtualImage.h
# End Source File
# Begin Source File

SOURCE=.\VMDemo.h
# End Source File
# Begin Source File

SOURCE=.\VMDemoDlg.h
# End Source File
# End Group
# Begin Group "Resources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\res\VMDemo.ico
# End Source File
# Begin Source File

SOURCE=.\res\VMDemo.rc2
# End Source File
# End Group
# End Target
# End Project
