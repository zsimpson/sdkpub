# Microsoft Developer Studio Project File - Name="Kalman" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Kalman - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Kalman.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Kalman.mak" CFG="Kalman - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Kalman - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Kalman - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Kalman - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\_temp\Kalman_Release"
# PROP Intermediate_Dir "..\..\_temp\Kalman_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
LIB32=link.exe -lib
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\CV\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 cv.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib quartz.lib STRMBASE.LIB comctl32.lib winmm.lib /nologo /entry:"DllEntryPoint@12" /subsystem:windows /dll /machine:I386 /out:"..\..\bin\Kalman.ax" /libpath:"..\..\lib"
# Begin Special Build Tool
TargetPath=\sdk\opencv\bin\Kalman.ax
SOURCE="$(InputPath)"
PostBuild_Cmds=regsvr32.exe /s $(TargetPath)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Kalman - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\_temp\Kalman_Debug\"
# PROP Intermediate_Dir "..\..\_temp\Kalman_Debug\"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
LIB32=link.exe -lib
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\CV\include" /I "\sdk\dx8\include" /I "\sdk\dx8\samples\Multimedia\DirectShow\BaseClasses" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 cvd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib quartz.lib STRMBASE.LIB comctl32.lib winmm.lib /nologo /entry:"DllEntryPoint@12" /subsystem:windows /dll /debug /machine:I386 /out:"..\..\bin\Kalmand.ax" /pdbtype:sept /libpath:"..\..\lib"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
TargetPath=\sdk\opencv\bin\Kalmand.ax
SOURCE="$(InputPath)"
PostBuild_Cmds=regsvr32.exe /s $(TargetPath)
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "Kalman - Win32 Release"
# Name "Kalman - Win32 Debug"
# Begin Group "Src"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Kalman.cpp
# End Source File
# Begin Source File

SOURCE=.\Kalman.def

!IF  "$(CFG)" == "Kalman - Win32 Release"

!ELSEIF  "$(CFG)" == "Kalman - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Kalmand.def

!IF  "$(CFG)" == "Kalman - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Kalman - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Kalmanprop.cpp
# End Source File
# End Group
# Begin Group "Include"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\iKalman.h
# End Source File
# Begin Source File

SOURCE=.\Kalman.h
# End Source File
# Begin Source File

SOURCE=.\Kalmanprop.h
# End Source File
# Begin Source File

SOURCE=.\Kalmanuids.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# End Group
# Begin Group "Resource"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Kalmanprop.rc
# End Source File
# End Group
# End Target
# End Project
