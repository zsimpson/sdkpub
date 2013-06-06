# Microsoft Developer Studio Project File - Name="Hawk" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=HAWK - WIN32 DEBUG
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Hawk.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Hawk.mak" CFG="HAWK - WIN32 DEBUG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Hawk - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Hawk - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Hawk - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\_temp\Hawk_Release"
# PROP Intermediate_Dir "..\..\_temp\Hawk_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /I "..\..\Cv\Include" /I "..\..\OtherLibs\HighGUI" /I "CVEiCL\EiC\src" /I "..\..\Filters\ProxyTrans" /I "CVEiCL\wrappers" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_CVL_SPECIFIC" /D "NO_LONG_LONG" /D "_IPPI_UNSAFE_PTR" /Fr /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 HighGUI.lib CVEiCL.lib ipl.lib strmbasd.lib strmiids.lib quartz.lib cv.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc" /out:"..\..\Bin\Hawk\Release/Hawk.exe" /libpath:"..\..\lib" /libpath:"..\..\OtherLibs\HighGUI\Release" /libpath:"..\..\OtherLibs\_ipl\lib\msvc" /libpath:"CVEiCL\lib"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Copying wrapper headers
PostBuild_Cmds=del /S /Q ..\..\bin\Hawk\release\wrappers\*.*	if not exist ..\..\bin\Hawk\release\wrappers md ..\..\bin\Hawk\release\wrappers	copy ..\..\CV\include\*.h ..\..\bin\Hawk\release\wrappers\*.*	copy ..\..\OtherLibs\_Ipl\Include\*.h ..\..\bin\Hawk\release\wrappers\*.*	copy convert.h ..\..\bin\Hawk\release\wrappers\*.*	copy ..\..\OtherLibs\HighGUI\HighGUI.h ..\..\bin\Hawk\release\wrappers\*.*	if not exist ..\..\bin\Hawk\release\wrappers\std md ..\..\bin\Hawk\release\wrappers\std	xcopy /s CVEiCL\EiC\src\win32\*.h ..\..\bin\Hawk\release\wrappers\std\*.*	del ..\..\bin\Hawk\release\wrappers\std\signal.h	copy wrappers.in ..\..\bin\Hawk\Release\wrappers	copy ..\..\CVaux\include\*.h ..\..\bin\Hawk\release\wrappers\*.*
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Hawk - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\_temp\Hawk_Debug"
# PROP Intermediate_Dir "..\..\_temp\Hawk_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\..\Cv\Include" /I "..\..\OtherLibs\HighGUI" /I "CVEiCL\EiC\src" /I "..\..\Filters\ProxyTrans" /I "CVEiCL\wrappers" /I "\sdk\dx8\include" /I "\sdk\dx8\samples\Multimedia\DirectShow\BaseClasses" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_CVL_SPECIFIC" /D "_AFXDLL" /D "NO_LONG_LONG" /D "_IPPI_UNSAFE_PTR" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 CVEiCLd.lib ipl.lib strmbasd.lib strmiids.lib quartz.lib cvd.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386 /nodefaultlib:"libc" /out:"..\..\Bin\Hawk\Debug/Hawkd.exe" /pdbtype:sept /libpath:"..\..\lib" /libpath:"..\..\OtherLibs\HighGUI\Debug" /libpath:"..\..\OtherLibs\_ipl\lib\msvc" /libpath:"CVEiCL\lib"
# SUBTRACT LINK32 /verbose /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Copying wrapper headers
PostBuild_Cmds=if not exist ..\..\bin\Hawk\Debug\wrappers md ..\..\bin\Hawk\Debug\wrappers	del /S /Q ..\..\bin\Hawk\Debug\wrappers\*.*	copy ..\..\CV\include\*.* ..\..\bin\Hawk\debug\wrappers	copy ..\..\OtherLibs\_Ipl\Include\*.h ..\..\bin\Hawk\debug\wrappers\*.*	copy convert.h ..\..\bin\Hawk\debug\wrappers\*.*	copy ..\..\OtherLibs\HighGUI\HighGUI.h ..\..\bin\Hawk\debug\wrappers\*.*	if not exist ..\..\bin\Hawk\debug\wrappers\std md ..\..\bin\Hawk\debug\wrappers\std	xcopy /s CVEiCL\EiC\src\win32\*.h ..\..\bin\Hawk\debug\wrappers\std\*.*	del ..\..\bin\Hawk\debug\wrappers\std\signal.h	copy wrappers.in ..\..\bin\Hawk\Debug\wrappers	copy ..\..\CVaux\include\*.h ..\..\bin\Hawk\debug\wrappers\*.*
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "Hawk - Win32 Release"
# Name "Hawk - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AviSource.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\convertwrap.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\DSWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\eicio.cpp
# End Source File
# Begin Source File

SOURCE=.\FuncDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GotoLine.cpp
# End Source File
# Begin Source File

SOURCE=.\Hawk.cpp

!IF  "$(CFG)" == "Hawk - Win32 Release"

# ADD CPP /O2

!ELSEIF  "$(CFG)" == "Hawk - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Hawk.rc
# End Source File
# Begin Source File

SOURCE=.\HawkDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\HawkOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\HawkView.cpp
# End Source File
# Begin Source File

SOURCE=.\HeadBand.cpp
# End Source File
# Begin Source File

SOURCE=.\lexer.cpp
# End Source File
# Begin Source File

SOURCE=.\LogView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\QuickWatch.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\WordColors.cpp
# End Source File
# Begin Source File

SOURCE=.\wrap.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\convert.h
# End Source File
# Begin Source File

SOURCE=.\DSWnd.h
# End Source File
# Begin Source File

SOURCE=.\eicio.h
# End Source File
# Begin Source File

SOURCE=.\FuncDialog.h
# End Source File
# Begin Source File

SOURCE=.\GotoLine.h
# End Source File
# Begin Source File

SOURCE=.\Hawk.h
# End Source File
# Begin Source File

SOURCE=.\HawkDoc.h
# End Source File
# Begin Source File

SOURCE=.\HawkOptions.h
# End Source File
# Begin Source File

SOURCE=.\HawkView.h
# End Source File
# Begin Source File

SOURCE=.\HeadBand.h
# End Source File
# Begin Source File

SOURCE=.\lexer.h
# End Source File
# Begin Source File

SOURCE=.\LogView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\QuickWatch.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\WordColors.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Hawk.ico
# End Source File
# Begin Source File

SOURCE=.\res\Hawk.rc2
# End Source File
# Begin Source File

SOURCE=.\res\HawkDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\headband.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
