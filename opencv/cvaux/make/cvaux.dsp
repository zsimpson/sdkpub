# Microsoft Developer Studio Project File - Name="cvaux" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=cvaux - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "cvaux.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "cvaux.mak" CFG="cvaux - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cvaux - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "cvaux - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "cvaux - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\_temp\cvaux_Rls"
# PROP Intermediate_Dir "..\..\_temp\cvaux_Rls"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
LIB32=link.exe -lib
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "cvaux_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /Ob2 /I "../include" /I "../../cv/include" /I "../../cv/src" /D "NDEBUG" /D "CVAUX_DLL" /D "WIN32" /D "_WINDOWS" /Yu"_cvaux.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 cv.lib kernel32.lib user32.lib gdi32.lib /nologo /dll /machine:I386 /out:"..\..\bin/cvaux.dll" /implib:"..\..\lib/cvaux.lib" /libpath:"..\..\lib"
# SUBTRACT LINK32 /pdb:none /debug

!ELSEIF  "$(CFG)" == "cvaux - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\_temp\cvaux_Dbg"
# PROP Intermediate_Dir "..\..\_temp\cvaux_Dbg"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
LIB32=link.exe -lib
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "cvaux_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /I "../include" /I "../../cv/include" /I "../../cv/src" /I "\sdk\dx8\include" /I "\sdk\dx8\samples\Multimedia\DirectShow\BaseClasses" /D "_DEBUG" /D "CVAUX_DLL" /D "WIN32" /D "_WINDOWS" /FR /Yu"_cvaux.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 cvd.lib kernel32.lib user32.lib gdi32.lib /nologo /dll /debug /machine:I386 /out:"..\..\bin/cvauxd.dll" /implib:"..\..\lib/cvauxd.lib" /pdbtype:sept /libpath:"..\..\lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "cvaux - Win32 Release"
# Name "cvaux - Win32 Debug"
# Begin Group "Src"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\correspond.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvaux.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvBilateralFiltering.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvcalibfilter.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvclique.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvcontourex.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvepilines.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvgraphex.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvhmm1d.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvsegment.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvsubdiv2.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvtexture.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvvideo.cpp
# End Source File
# Begin Source File

SOURCE=..\src\decomppoly.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ExtendedEdges.cpp
# End Source File
# Begin Source File

SOURCE=..\src\precomp.cpp
# ADD CPP /Yc"_cvaux.h"
# End Source File
# End Group
# Begin Group "Include"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Internal"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\_cvaux.h
# End Source File
# End Group
# Begin Group "External"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\cvaux.h
# End Source File
# End Group
# End Group
# End Target
# End Project
