# Microsoft Developer Studio Project File - Name="seance" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=seance - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "seance.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "seance.mak" CFG="seance - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "seance - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "seance - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "seance - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../_temp/seance"
# PROP Intermediate_Dir "../../_temp/seance"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W4 /GX /Od /I "./" /I "eic" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "NO_DIRENT" /D "NO_PIPE" /D "NO_STAT" /D "NO_UNISTD" /D "NO_FCNTL" /D "NO_LONG_LONG" /D "_IPPI_UNSAFE_PTR" /D "NO_TERMIOS" /YX /FD /c
# SUBTRACT CPP /Z<none> /Fr
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib cvEiC.lib /nologo /entry:"mainCRTStartup" /subsystem:windows /map /machine:I386 /out:"../../bin/cvenv/seance.exe" /libpath:"EiC/Lib"
# SUBTRACT LINK32 /pdb:none /debug
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy plugins.cfg ..\..\bin\cvenv\plugins.cfg	if not exist ..\..\bin\cvenv\plugins md ..\..\bin\cvenv\plugins	del /S /Q ..\..\bin\cvenv\plugins\*.*	copy ..\..\bin\cv.dll ..\..\bin\cvenv\plugins\cv.dll	copy ..\..\bin\cvcam.dll ..\..\bin\cvenv\plugins\cvcam.dll	copy ..\..\bin\highgui.dll ..\..\bin\cvenv\plugins\highgui.dll	copy ..\..\otherlibs\_Ipl\bin\ipl.dll ..\..\bin\cvenv\plugins\ipl.dll	copy ..\..\otherlibs\_Ipl\bin\iplA6.dll ..\..\bin\cvenv\plugins\iplA6.dll	copy ..\..\cv\include\*.h ..\..\bin\cvenv\plugins\*.*	copy ..\..\otherlibs\highgui\highgui.h ..\..\bin\cvenv\plugins\highgui.h	copy ..\..\otherlibs\cvcam\include\cvcam.h ..\..\bin\cvenv\plugins\cvcam.h	if not exist ..\..\bin\cvenv\std md ..\..\bin\cvenv\std	del /S /Q ..\..\bin\cvenv\std\*.*	copy include\*.h ..\..\bin\cvenv\std\*.*	if not exist ..\..\bin\cvenv\std\sys md ..\..\bin\cvenv\std\sys	del /S /Q ..\..\bin\cvenv\std\sys\*.*	copy include\sys\*.h ..\..\bin\cvenv\std\sys\*.*
# End Special Build Tool

!ELSEIF  "$(CFG)" == "seance - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../_temp/seanced"
# PROP Intermediate_Dir "../../_temp/seanced"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "./" /I "eic" /D "_DEBUG" /D "NO_DIRENT" /D "NO_PIPE" /D "NO_STAT" /D "NO_UNISTD" /D "NO_FCNTL" /D "NO_LONG_LONG" /D "_IPPI_UNSAFE_PTR" /D "NO_TERMIOS" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib cvEiCd.lib /nologo /entry:"mainCRTStartup" /subsystem:console /debug /machine:I386 /out:"../../bin/cvenvd/seance.exe" /pdbtype:sept /libpath:"EiC/Lib"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy pluginsd.cfg ..\..\bin\cvenvd\plugins.cfg	if not exist ..\..\bin\cvenvd\plugins md ..\..\bin\cvenvd\plugins	del /S /Q ..\..\bin\cvenvd\plugins\*.*	copy ..\..\bin\cvd.dll ..\..\bin\cvenvd\plugins\cvd.dll	copy ..\..\bin\cvcamd.dll ..\..\bin\cvenvd\plugins\cvcamd.dll	copy ..\..\bin\highguid.dll ..\..\bin\cvenvd\plugins\highguid.dll	copy ..\..\otherlibs\_Ipl\bin\ipl.dll ..\..\bin\cvenvd\plugins\ipl.dll	copy ..\..\otherlibs\_Ipl\bin\iplA6.dll ..\..\bin\cvenvd\plugins\iplA6.dll	copy ..\..\cv\include\*.h ..\..\bin\cvenvd\plugins\*.*	copy ..\..\otherlibs\highgui\highgui.h ..\..\bin\cvenvd\plugins\highgui.h	copy ..\..\otherlibs\cvcam\include\cvcam.h ..\..\bin\cvenvd\plugins\cvcam.h	if not exist ..\..\bin\cvenvd\std md ..\..\bin\cvenvd\std	del /S /Q ..\..\bin\cvenvd\std\*.*	copy include\*.h ..\..\bin\cvenvd\std\*.*	if not exist ..\..\bin\cvenvd\std\sys md ..\..\bin\cvenvd\std\sys	del /S /Q ..\..\bin\cvenvd\std\sys\*.*	copy include\sys\*.h ..\..\bin\cvenvd\std\sys\*.*
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "seance - Win32 Release"
# Name "seance - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\add.cpp
# End Source File
# Begin Source File

SOURCE=.\filelist.cpp
# End Source File
# Begin Source File

SOURCE=.\initeic.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\filelist.h
# End Source File
# Begin Source File

SOURCE=.\initeic.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
