# Microsoft Developer Studio Project File - Name="VisEiCL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=VisEiCL - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CVEiCL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CVEiCL.mak" CFG="VisEiCL - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VisEiCL - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "VisEiCL - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VisEiCL - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\_temp\VisEiCL_Release"
# PROP Intermediate_Dir "..\..\..\_temp\VisEiCL_Release"
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /I "./" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "__WIN32__" /D "NO_DIRENT" /D "NO_PIPE" /D "NO_STAT" /D "NO_UNISTD" /D "NO_FCNTL" /D "NO_LONG_LONG" /D "_IPPI_UNSAFE_PTR" /D "NO_TERMIOS" /YX /FD /c
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "VisEiCL - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "VisEiCL___Win32_Debug"
# PROP BASE Intermediate_Dir "VisEiCL___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\_temp\VisEiCL_Debug"
# PROP Intermediate_Dir "..\..\..\_temp\VisEiCL_Debug"
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "./" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "__WIN32__" /D "NO_DIRENT" /D "NO_PIPE" /D "NO_STAT" /D "NO_UNISTD" /D "NO_FCNTL" /D "NO_LONG_LONG" /D "_IPPI_UNSAFE_PTR" /D "NO_TERMIOS" /FR /YX /FD /GZ /c
# SUBTRACT CPP /X
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib\CVEiCLd.lib"

!ENDIF 

# Begin Target

# Name "VisEiCL - Win32 Release"
# Name "VisEiCL - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "stdClib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\stdClib\assert.c
# End Source File
# Begin Source File

SOURCE=.\stdClib\ctype.c
# End Source File
# Begin Source File

SOURCE=.\stdClib\dirent.c
# End Source File
# Begin Source File

SOURCE=.\stdClib\eicfftoa.c
# End Source File
# Begin Source File

SOURCE=.\stdClib\errno.c
# End Source File
# Begin Source File

SOURCE=.\stdClib\fcntl.c
# End Source File
# Begin Source File

SOURCE=.\stdClib\itoa.c
# End Source File
# Begin Source File

SOURCE=.\stdClib\math.c
# End Source File
# Begin Source File

SOURCE=.\stdClib\signal.c
# End Source File
# Begin Source File

SOURCE=.\stdClib\stat.c
# End Source File
# Begin Source File

SOURCE=.\stdClib\stdarg.c
# End Source File
# Begin Source File

SOURCE=.\stdClib\stdClib.c
# End Source File
# Begin Source File

SOURCE=.\stdClib\stdio.c
# End Source File
# Begin Source File

SOURCE=.\stdClib\stdlib.c
# End Source File
# Begin Source File

SOURCE=.\stdClib\string.c
# End Source File
# Begin Source File

SOURCE=.\stdClib\strround.c
# End Source File
# Begin Source File

SOURCE=.\stdClib\time.c
# End Source File
# Begin Source File

SOURCE=.\stdClib\unistd.c
# End Source File
# End Group
# Begin Source File

SOURCE=.\callback.c
# End Source File
# Begin Source File

SOURCE=.\cdecl.c
# End Source File
# Begin Source File

SOURCE=.\eicmod.c
# End Source File
# Begin Source File

SOURCE=.\emitter.c
# End Source File
# Begin Source File

SOURCE=.\error.c
# End Source File
# Begin Source File

SOURCE=.\func.c
# End Source File
# Begin Source File

SOURCE=.\interpre.c
# End Source File
# Begin Source File

SOURCE=.\lexer.c
# End Source File
# Begin Source File

SOURCE=.\optomizer.c
# End Source File
# Begin Source File

SOURCE=.\parser.c
# End Source File
# Begin Source File

SOURCE=.\preexpr.c
# End Source File
# Begin Source File

SOURCE=.\preproc.c
# End Source File
# Begin Source File

SOURCE=.\readline.c
# End Source File
# Begin Source File

SOURCE=.\reset.c
# End Source File
# Begin Source File

SOURCE=.\stab.c
# End Source File
# Begin Source File

SOURCE=.\starteic.c
# End Source File
# Begin Source File

SOURCE=.\symbol.c
# End Source File
# Begin Source File

SOURCE=.\typemod.c
# End Source File
# Begin Source File

SOURCE=.\typesets.c
# End Source File
# Begin Source File

SOURCE=.\ymem.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\assertp.h
# End Source File
# Begin Source File

SOURCE=.\cdecl.h
# End Source File
# Begin Source File

SOURCE=.\datastruct.h
# End Source File
# Begin Source File

SOURCE=.\eic.h
# End Source File
# Begin Source File

SOURCE=.\eicval.h
# End Source File
# Begin Source File

SOURCE=.\emitter.h
# End Source File
# Begin Source File

SOURCE=.\error.h
# End Source File
# Begin Source File

SOURCE=.\func.h
# End Source File
# Begin Source File

SOURCE=.\global.h
# End Source File
# Begin Source File

SOURCE=.\lexer.h
# End Source File
# Begin Source File

SOURCE=.\MachSet.h
# End Source File
# Begin Source File

SOURCE=.\metric.h
# End Source File
# Begin Source File

SOURCE=.\parser.h
# End Source File
# Begin Source File

SOURCE=.\preproc.h
# End Source File
# Begin Source File

SOURCE=.\reset.h
# End Source File
# Begin Source File

SOURCE=.\stab.h
# End Source File
# Begin Source File

SOURCE=.\stdClib\stdClib2eic.h
# End Source File
# Begin Source File

SOURCE=.\stdClib\stdliblocal.h
# End Source File
# Begin Source File

SOURCE=.\symbol.h
# End Source File
# Begin Source File

SOURCE=.\typemod.h
# End Source File
# Begin Source File

SOURCE=.\typesets.h
# End Source File
# Begin Source File

SOURCE=.\xalloc.h
# End Source File
# End Group
# End Target
# End Project
