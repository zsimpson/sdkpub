# Microsoft Developer Studio Project File - Name="CamShift" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=CamShift - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CamShift.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CamShift.mak" CFG="CamShift - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CamShift - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CamShift - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CamShift - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\_temp\CamShift_Rls"
# PROP Intermediate_Dir "..\..\_temp\CamShift_Rls"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
LIB32=link.exe -lib
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\CV\Include" /I "." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 cv.lib kernel32.lib user32.lib gdi32.lib advapi32.lib comdlg32.lib shell32.lib ole32.lib uuid.lib quartz.lib winmm.lib oleaut32.lib STRMBASE.LIB comctl32.lib /nologo /entry:"DllEntryPoint@12" /subsystem:windows /dll /machine:I386 /out:"..\..\Bin\CamShift.ax" /libpath:"..\..\lib"
# SUBTRACT LINK32 /incremental:yes
# Begin Special Build Tool
TargetPath=\sdk\opencv\Bin\CamShift.ax
SOURCE="$(InputPath)"
PostBuild_Cmds=regsvr32 /s $(TargetPath)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "CamShift - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\_temp\CamShift_Dbg"
# PROP Intermediate_Dir "..\..\_temp\CamShift_Dbg"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
LIB32=link.exe -lib
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\..\CV\Include" /I "." /I "\sdk\dx8\include" /I "\sdk\dx8\samples\Multimedia\DirectShow\BaseClasses" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 cvd.lib kernel32.lib user32.lib gdi32.lib advapi32.lib comdlg32.lib shell32.lib ole32.lib uuid.lib quartz.lib winmm.lib oleaut32.lib STRMBASE.LIB comctl32.lib /nologo /entry:"DllEntryPoint@12" /subsystem:windows /dll /debug /machine:I386 /out:"..\..\Bin\CamShiftd.ax" /pdbtype:sept /libpath:"..\..\lib"
# SUBTRACT LINK32 /incremental:no /nodefaultlib
# Begin Special Build Tool
TargetPath=\sdk\opencv\Bin\CamShiftd.ax
SOURCE="$(InputPath)"
PostBuild_Cmds=regsvr32 /s $(TargetPath)
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "CamShift - Win32 Release"
# Name "CamShift - Win32 Debug"
# Begin Group "Src"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CamShift.def

!IF  "$(CFG)" == "CamShift - Win32 Release"

!ELSEIF  "$(CFG)" == "CamShift - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CamShiftD.def

!IF  "$(CFG)" == "CamShift - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "CamShift - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CamShiftF.cpp

!IF  "$(CFG)" == "CamShift - Win32 Release"

!ELSEIF  "$(CFG)" == "CamShift - Win32 Debug"

# SUBTRACT CPP /YX

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CamShiftProp.cpp
# End Source File
# End Group
# Begin Group "Include"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CamShiftF.h
# End Source File
# Begin Source File

SOURCE=.\CamShiftProp.h
# End Source File
# Begin Source File

SOURCE=.\CamShiftUIDs.h
# End Source File
# Begin Source File

SOURCE=.\iCamShift.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\utils.h
# End Source File
# End Group
# Begin Group "Resource"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\CamShiftProp.rc
# ADD BASE RSC /l 0x409 /i "\USER\VP\opencv\Filters\CamShift\Include" /i "\Users\Neo\StarTeam\Neo\Filters\CamShift\Include" /i "\_Vadim\Alpha_3\Filters\CamShift\Include" /i "\Users\Oblomov\StarTeam\oblomov\Filters\CamShift\Include" /i "\Users\Oblomov\StarTeam\oblomov\CamShift\Include" /i "\USERS\VP\StarTeam\IppCV\CamShift\Include" /i "\Users\Oblomov\StarTeam\oblomov\CV\CamShift\Include"
# ADD RSC /l 0x409 /i "\USER\VP\opencv\Filters\CamShift\Include" /i "\Users\Neo\StarTeam\Neo\Filters\CamShift\Include" /i "\_Vadim\Alpha_3\Filters\CamShift\Include" /i "\Users\Oblomov\StarTeam\oblomov\Filters\CamShift\Include" /i "\Users\Oblomov\StarTeam\oblomov\CamShift\Include" /i "\USERS\VP\StarTeam\IppCV\CamShift\Include" /i "." /i "\Users\Oblomov\StarTeam\oblomov\CV\CamShift\Include"
# End Source File
# End Group
# End Target
# End Project
