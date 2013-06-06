# Microsoft Developer Studio Project File - Name="Lua51" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Lua51 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Lua51.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Lua51.mak" CFG="Lua51 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Lua51 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Lua51 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Lua51 - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Lua51 - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
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

# Name "Lua51 - Win32 Release"
# Name "Lua51 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\lapi.c
# End Source File
# Begin Source File

SOURCE=.\src\lauxlib.c
# End Source File
# Begin Source File

SOURCE=.\src\lbaselib.c
# End Source File
# Begin Source File

SOURCE=.\src\lcode.c
# End Source File
# Begin Source File

SOURCE=.\src\ldblib.c
# End Source File
# Begin Source File

SOURCE=.\src\ldebug.c
# End Source File
# Begin Source File

SOURCE=.\src\ldo.c
# End Source File
# Begin Source File

SOURCE=.\src\ldump.c
# End Source File
# Begin Source File

SOURCE=.\src\lfunc.c
# End Source File
# Begin Source File

SOURCE=.\src\lgc.c
# End Source File
# Begin Source File

SOURCE=.\src\linit.c
# End Source File
# Begin Source File

SOURCE=.\src\liolib.c
# End Source File
# Begin Source File

SOURCE=.\src\llex.c
# End Source File
# Begin Source File

SOURCE=.\src\lmathlib.c
# End Source File
# Begin Source File

SOURCE=.\src\lmem.c
# End Source File
# Begin Source File

SOURCE=.\src\loadlib.c
# End Source File
# Begin Source File

SOURCE=.\src\lobject.c
# End Source File
# Begin Source File

SOURCE=.\src\lopcodes.c
# End Source File
# Begin Source File

SOURCE=.\src\loslib.c
# End Source File
# Begin Source File

SOURCE=.\src\lparser.c
# End Source File
# Begin Source File

SOURCE=.\src\lstate.c
# End Source File
# Begin Source File

SOURCE=.\src\lstring.c
# End Source File
# Begin Source File

SOURCE=.\src\lstrlib.c
# End Source File
# Begin Source File

SOURCE=.\src\ltable.c
# End Source File
# Begin Source File

SOURCE=.\src\ltablib.c
# End Source File
# Begin Source File

SOURCE=.\src\ltm.c
# End Source File
# Begin Source File

SOURCE=.\src\luac.c
# End Source File
# Begin Source File

SOURCE=.\src\lundump.c
# End Source File
# Begin Source File

SOURCE=.\src\lvm.c
# End Source File
# Begin Source File

SOURCE=.\src\lzio.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\src\lapi.h
# End Source File
# Begin Source File

SOURCE=.\src\lauxlib.h
# End Source File
# Begin Source File

SOURCE=.\src\lcode.h
# End Source File
# Begin Source File

SOURCE=.\src\ldebug.h
# End Source File
# Begin Source File

SOURCE=.\src\ldo.h
# End Source File
# Begin Source File

SOURCE=.\src\lfunc.h
# End Source File
# Begin Source File

SOURCE=.\src\lgc.h
# End Source File
# Begin Source File

SOURCE=.\src\llex.h
# End Source File
# Begin Source File

SOURCE=.\src\llimits.h
# End Source File
# Begin Source File

SOURCE=.\src\lmem.h
# End Source File
# Begin Source File

SOURCE=.\src\lobject.h
# End Source File
# Begin Source File

SOURCE=.\src\lopcodes.h
# End Source File
# Begin Source File

SOURCE=.\src\lparser.h
# End Source File
# Begin Source File

SOURCE=.\src\lstate.h
# End Source File
# Begin Source File

SOURCE=.\src\lstring.h
# End Source File
# Begin Source File

SOURCE=.\src\ltable.h
# End Source File
# Begin Source File

SOURCE=.\src\ltm.h
# End Source File
# Begin Source File

SOURCE=.\src\lua.h
# End Source File
# Begin Source File

SOURCE=.\src\luaconf.h
# End Source File
# Begin Source File

SOURCE=.\src\lualib.h
# End Source File
# Begin Source File

SOURCE=.\src\lundump.h
# End Source File
# Begin Source File

SOURCE=.\src\lvm.h
# End Source File
# Begin Source File

SOURCE=.\src\lzio.h
# End Source File
# End Group
# End Target
# End Project
