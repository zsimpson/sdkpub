# Microsoft Developer Studio Project File - Name="ATS" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ATS - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Ats.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Ats.mak" CFG="ATS - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ATS - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ATS - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ATS - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ATS___Win32_Release"
# PROP BASE Intermediate_Dir "ATS___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\_temp\ATS_Rls"
# PROP Intermediate_Dir "..\..\..\_temp\ATS_Rls"
# PROP Target_Dir ""
F90=df.exe
LINK32=link.exe
MTL=midl.exe
# ADD BASE CPP /nologo /MD /W4 /GX /O2 /I "..\Include" /I "..\..\_Trs\Include" /D "NDEBUG" /D "_CVL_PX" /D "_WINDOWS" /D "WIN32" /D "IPL_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W4 /GX /Zi /O2 /I "..\Include" /I "..\..\trs\Include" /I "..\..\..\CV\Include" /I "..\..\TS\include" /I "..\..\..\OtherLibs\_Ipl\include" /D "NDEBUG" /D "_CVL_PX" /D "_WINDOWS" /D "WIN32" /D "IPL_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x419
# ADD RSC /l 0x419
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Lib\atspX.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\ats.lib"

!ELSEIF  "$(CFG)" == "ATS - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ATS___Win32_Debug"
# PROP BASE Intermediate_Dir "ATS___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\_temp\ATS_Dbg"
# PROP Intermediate_Dir "..\..\..\_temp\ATS_Dbg"
# PROP Target_Dir ""
F90=df.exe
LINK32=link.exe
MTL=midl.exe
# ADD BASE CPP /nologo /MDd /W4 /GX /ZI /Od /I "..\Include" /I "..\..\_Trs\Include" /D "_DEBUG" /D "_CVL_DEBUG" /D "_CVL_PX" /D "_WINDOWS" /D "WIN32" /D "IPL_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W4 /GX /Zi /Od /I "..\Include" /I "..\..\trs\Include" /I "..\..\..\CV\Include" /I "..\..\TS\include" /I "..\..\..\OtherLibs\_Ipl\include" /I "\sdk\dx8\include" /I "\sdk\dx8\samples\Multimedia\DirectShow\BaseClasses" /D "_DEBUG" /D "_CVL_DEBUG" /D "_CVL_PX" /D "_WINDOWS" /D "WIN32" /D "IPL_WINDOWS" /FR /YX /FD /c
# ADD BASE RSC /l 0x419
# ADD RSC /l 0x419
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Lib\atspXd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\atsd.lib"

!ENDIF 

# Begin Target

# Name "ATS - Win32 Release"
# Name "ATS - Win32 Debug"
# Begin Group "Src"

# PROP Default_Filter ""
# Begin Group "Initialization"

# PROP Default_Filter ""
# Begin Group "Randomize"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\initrand.c
# End Source File
# Begin Source File

SOURCE=..\Src\randex.c
# End Source File
# End Group
# Begin Group "Gradient"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\initgrad.c
# End Source File
# End Group
# Begin Group "Figure"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\initFigure.c
# End Source File
# End Group
# Begin Group "System"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\system.c
# End Source File
# End Group
# End Group
# Begin Group "Comparing"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\Comp1D.c
# End Source File
# End Group
# Begin Group "IplImgUtils"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\Common.c
# End Source File
# End Group
# Begin Group "Timer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\timer.c
# End Source File
# End Group
# Begin Group "Persistence"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Src\persistence.c
# End Source File
# End Group
# End Group
# Begin Group "Include"

# PROP Default_Filter ""
# Begin Group "External"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Include\ats.h
# End Source File
# End Group
# Begin Group "Input"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\_Trs\Include\TRSAPI.H
# End Source File
# Begin Source File

SOURCE=..\..\_Trs\Include\TRSERROR.H
# End Source File
# Begin Source File

SOURCE=..\..\_Trs\Include\TRSIPI.H
# End Source File
# End Group
# End Group
# End Target
# End Project
