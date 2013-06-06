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
# PROP Output_Dir "lib"
# PROP Intermediate_Dir "..\..\..\_temp\VisEiCL_Release"
# PROP Target_Dir ""
F90=df.exe
LINK32=link.exe
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /w /W0 /GX /Zi /O2 /I "..\..\..\cv\include" /I "..\..\..\OtherLibs\HighGUI" /I "..\..\..\OtherLibs\_ipl\Include" /I "..\\" /I "EiC\src" /I "wrappers" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "__WIN32__" /D "NO_DIRENT" /D "NO_PIPE" /D "NO_STAT" /D "NO_UNISTD" /D "NO_FCNTL" /D "NO_LONG_LONG" /D "_IPPI_UNSAFE_PTR" /D "NO_TERMIOS" /YX /FD /c
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
# PROP Output_Dir "lib"
# PROP Intermediate_Dir "..\..\..\_temp\VisEiCL_Debug"
# PROP Target_Dir ""
F90=df.exe
LINK32=link.exe
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /w /W0 /Gm /GX /Zi /Od /I "..\..\..\cv\include" /I "..\..\..\OtherLibs\HighGUI" /I "..\..\..\OtherLibs\_ipl\Include" /I "EiC\src" /I ".." /I "wrappers" /I "\sdk\dx8\include" /I "\sdk\dx8\samples\Multimedia\DirectShow\BaseClasses" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "__WIN32__" /D "NO_DIRENT" /D "NO_PIPE" /D "NO_STAT" /D "NO_UNISTD" /D "NO_FCNTL" /D "NO_LONG_LONG" /D "_IPPI_UNSAFE_PTR" /D "NO_TERMIOS" /FR /YX /FD /GZ /c
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

SOURCE=.\EiC\module\stdClib\src\assert.c
# End Source File
# Begin Source File

SOURCE=.\EiC\module\stdClib\src\ctype.c
# End Source File
# Begin Source File

SOURCE=.\EiC\module\stdClib\src\dirent.c
# End Source File
# Begin Source File

SOURCE=.\EiC\module\stdClib\src\eicfftoa.c
# End Source File
# Begin Source File

SOURCE=.\EiC\module\stdClib\src\errno.c
# End Source File
# Begin Source File

SOURCE=.\EiC\module\stdClib\src\fcntl.c
# End Source File
# Begin Source File

SOURCE=.\EiC\module\stdClib\src\itoa.c
# End Source File
# Begin Source File

SOURCE=.\EiC\module\stdClib\src\math.c
# End Source File
# Begin Source File

SOURCE=.\EiC\module\stdClib\src\printf.c
# End Source File
# Begin Source File

SOURCE=.\EiC\module\stdClib\src\signal.c
# End Source File
# Begin Source File

SOURCE=.\EiC\module\stdClib\src\stat.c
# End Source File
# Begin Source File

SOURCE=.\EiC\module\stdClib\src\stdarg.c
# End Source File
# Begin Source File

SOURCE=.\EiC\module\stdClib\src\stdClib.c
# End Source File
# Begin Source File

SOURCE=.\EiC\module\stdClib\src\stdio.c
# End Source File
# Begin Source File

SOURCE=.\EiC\module\stdClib\src\stdlib.c
# End Source File
# Begin Source File

SOURCE=.\EiC\module\stdClib\src\string.c
# End Source File
# Begin Source File

SOURCE=.\EiC\module\stdClib\src\strrev.c
# End Source File
# Begin Source File

SOURCE=.\EiC\module\stdClib\src\strround.c
# End Source File
# Begin Source File

SOURCE=.\EiC\module\stdClib\src\time.c
# End Source File
# Begin Source File

SOURCE=.\EiC\module\stdClib\src\unistd.c
# End Source File
# End Group
# Begin Group "HighGUI"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\wrappers\HighGUIwrap.c
# End Source File
# End Group
# Begin Group "ipl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\wrappers\genipl.eic

!IF  "$(CFG)" == "VisEiCL - Win32 Release"

!ELSEIF  "$(CFG)" == "VisEiCL - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\EiC\src\callback.c
# End Source File
# Begin Source File

SOURCE=.\EiC\src\cdecl.c
# End Source File
# Begin Source File

SOURCE=.\EiC\src\eicmod.c
# End Source File
# Begin Source File

SOURCE=.\EiC\src\emitter.c
# End Source File
# Begin Source File

SOURCE=.\EiC\src\error.c
# End Source File
# Begin Source File

SOURCE=.\EiC\src\func.c
# End Source File
# Begin Source File

SOURCE=.\EiC\src\interpre.c
# End Source File
# Begin Source File

SOURCE=.\EiC\src\lexer.c
# End Source File
# Begin Source File

SOURCE=.\EiC\src\optomizer.c
# End Source File
# Begin Source File

SOURCE=.\EiC\src\parser.c
# End Source File
# Begin Source File

SOURCE=.\EiC\src\preexpr.c
# End Source File
# Begin Source File

SOURCE=.\EiC\src\preproc.c
# End Source File
# Begin Source File

SOURCE=.\EiC\src\readline.c
# End Source File
# Begin Source File

SOURCE=.\EiC\src\reset.c
# End Source File
# Begin Source File

SOURCE=.\EiC\src\stab.c
# End Source File
# Begin Source File

SOURCE=.\EiC\src\starteic.c
# End Source File
# Begin Source File

SOURCE=.\EiC\src\symbol.c
# End Source File
# Begin Source File

SOURCE=.\EiC\src\typemod.c
# End Source File
# Begin Source File

SOURCE=.\EiC\src\typesets.c
# End Source File
# Begin Source File

SOURCE=.\EiC\src\ymem.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\EiC\src\assertp.h
# End Source File
# Begin Source File

SOURCE=.\EiC\src\cdecl.h
# End Source File
# Begin Source File

SOURCE=.\EiC\src\datastruct.h
# End Source File
# Begin Source File

SOURCE=.\EiC\src\eic.h
# End Source File
# Begin Source File

SOURCE=.\EiC\src\eicval.h
# End Source File
# Begin Source File

SOURCE=..\..\..\ScriptLangs\EiC\EiC_src\EiC\src\eicval.h
# End Source File
# Begin Source File

SOURCE=.\EiC\src\emitter.h
# End Source File
# Begin Source File

SOURCE=.\EiC\src\error.h
# End Source File
# Begin Source File

SOURCE=.\EiC\src\func.h
# End Source File
# Begin Source File

SOURCE=.\EiC\src\global.h
# End Source File
# Begin Source File

SOURCE=.\EiC\src\lexer.h
# End Source File
# Begin Source File

SOURCE=.\EiC\src\MachSet.h
# End Source File
# Begin Source File

SOURCE=.\EiC\src\metric.h
# End Source File
# Begin Source File

SOURCE=.\EiC\src\modules.h
# End Source File
# Begin Source File

SOURCE=.\EiC\src\parser.h
# End Source File
# Begin Source File

SOURCE=.\EiC\src\preproc.h
# End Source File
# Begin Source File

SOURCE=.\EiC\src\stab.h
# End Source File
# Begin Source File

SOURCE=.\EiC\module\stdClib\src\stdlib.h
# End Source File
# Begin Source File

SOURCE=.\EiC\src\symbol.h
# End Source File
# Begin Source File

SOURCE=.\EiC\src\symentry.h
# End Source File
# Begin Source File

SOURCE=.\EiC\src\typemod.h
# End Source File
# Begin Source File

SOURCE=.\EiC\src\typesets.h
# End Source File
# Begin Source File

SOURCE=.\EiC\src\xalloc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\ScriptLangs\EiC\EiC_src\EiC\src\xalloc.h
# End Source File
# End Group
# End Target
# End Project
