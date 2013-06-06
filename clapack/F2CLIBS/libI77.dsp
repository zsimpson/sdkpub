# Microsoft Developer Studio Project File - Name="libI77" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libI77 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libI77.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libI77.mak" CFG="libI77 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libI77 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libI77 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libI77 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "O:\CLAPACK\F2clibs" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "MSDOS" /D "Allow_TYQUAD" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "libI77 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_WIN32" /D "MSDOS" /D "_DEBUG" /D "Allow_TYQUAD" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "libI77 - Win32 Release"
# Name "libI77 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\libI77\backspace.c
# End Source File
# Begin Source File

SOURCE=.\libI77\close.c
# End Source File
# Begin Source File

SOURCE=.\libI77\dfe.c
# End Source File
# Begin Source File

SOURCE=.\libI77\dolio.c
# End Source File
# Begin Source File

SOURCE=.\libI77\due.c
# End Source File
# Begin Source File

SOURCE=.\libI77\endfile.c
# End Source File
# Begin Source File

SOURCE=.\libI77\err.c
# End Source File
# Begin Source File

SOURCE=.\libI77\fmt.c
# End Source File
# Begin Source File

SOURCE=.\libI77\fmtlib.c
# End Source File
# Begin Source File

SOURCE=.\libI77\ftell_.c
# End Source File
# Begin Source File

SOURCE=.\libI77\iio.c
# End Source File
# Begin Source File

SOURCE=.\libI77\ilnw.c
# End Source File
# Begin Source File

SOURCE=.\libI77\inquire.c
# End Source File
# Begin Source File

SOURCE=.\libI77\lread.c
# End Source File
# Begin Source File

SOURCE=.\libI77\lwrite.c
# End Source File
# Begin Source File

SOURCE=.\libI77\open.c
# End Source File
# Begin Source File

SOURCE=.\libI77\rdfmt.c
# End Source File
# Begin Source File

SOURCE=.\libI77\rewind.c
# End Source File
# Begin Source File

SOURCE=.\libI77\rsfe.c
# End Source File
# Begin Source File

SOURCE=.\libI77\rsli.c
# End Source File
# Begin Source File

SOURCE=.\libI77\rsne.c
# End Source File
# Begin Source File

SOURCE=.\libI77\sfe.c
# End Source File
# Begin Source File

SOURCE=.\libI77\sue.c
# End Source File
# Begin Source File

SOURCE=.\libI77\typesize.c
# End Source File
# Begin Source File

SOURCE=.\libI77\uio.c
# End Source File
# Begin Source File

SOURCE=.\libI77\util.c
# End Source File
# Begin Source File

SOURCE=.\libI77\Version.c
# End Source File
# Begin Source File

SOURCE=.\libI77\wref.c
# End Source File
# Begin Source File

SOURCE=.\libI77\wrtfmt.c
# End Source File
# Begin Source File

SOURCE=.\libI77\wsfe.c
# End Source File
# Begin Source File

SOURCE=.\libI77\wsle.c
# End Source File
# Begin Source File

SOURCE=.\libI77\wsne.c
# End Source File
# Begin Source File

SOURCE=.\libI77\xwsne.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\libI77\f2c.h
# End Source File
# Begin Source File

SOURCE=.\libI77\fio.h
# End Source File
# Begin Source File

SOURCE=.\libI77\fmt.h
# End Source File
# Begin Source File

SOURCE=.\libI77\fp.h
# End Source File
# Begin Source File

SOURCE=.\libI77\lio.h
# End Source File
# Begin Source File

SOURCE=.\libI77\rawio.h
# End Source File
# End Group
# End Target
# End Project
