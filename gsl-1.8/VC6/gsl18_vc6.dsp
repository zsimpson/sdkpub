# Microsoft Developer Studio Project File - Name="gsl18_vc6" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=gsl18_vc6 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gsl18_vc6.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gsl18_vc6.mak" CFG="gsl18_vc6 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gsl18_vc6 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "gsl18_vc6 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Release\*.dll ..\..\..\zlab
# End Special Build Tool

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"Debug/gsl18_vc6D.dll" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Debug\*.dll ..\..\..\zlab
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "gsl18_vc6 - Win32 Release"
# Name "gsl18_vc6 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\gsl18_vc6.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\gsl18_vc6.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "multifit"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\multifit\convergence.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\multifit"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\multifit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\multifit\covar.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\multifit"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\multifit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\multifit\fdfsolver.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\multifit"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\multifit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\multifit\fsolver.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\multifit"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\multifit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\multifit\gradient.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\multifit"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\multifit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\multifit\gsl_multifit.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\multifit"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\multifit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\multifit\gsl_multifit_nlin.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\multifit"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\multifit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\multifit\lmder.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\multifit"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\multifit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\multifit\lmiterate.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\multifit"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\multifit"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\multifit\lmpar.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\multifit"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\multifit"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\multifit\lmset.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\multifit"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\multifit"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\multifit\lmutil.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\multifit"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\multifit"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\multifit\multilinear.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\multifit"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\multifit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\multifit\qrsolv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\multifit"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\multifit"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\multifit\work.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\multifit"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\multifit"

!ENDIF 

# End Source File
# End Group
# Begin Group "err"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\err\error.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\err"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\err"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\err\gsl_errno.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\err"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\err"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\err\gsl_message.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\err"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\err"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\err\message.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\err"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\err"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\err\stream.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\err"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\err"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\err\strerror.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\err"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\err"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\err\test.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\err"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\err"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "vector"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\vector\copy.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\copy_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\file.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\file_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\gsl_vector.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\gsl_vector_char.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\gsl_vector_complex.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\gsl_vector_complex_double.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\gsl_vector_complex_float.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\gsl_vector_complex_long_double.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\gsl_vector_double.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\gsl_vector_float.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\gsl_vector_int.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\gsl_vector_long.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\gsl_vector_long_double.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\gsl_vector_short.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\gsl_vector_uchar.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\gsl_vector_uint.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\gsl_vector_ulong.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\gsl_vector_ushort.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\init.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\init_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\minmax.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\minmax_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\oper.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\oper_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\prop.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\prop_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\reim.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\reim_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\subvector.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\subvector_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\swap.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\swap_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\test.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\test_complex_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\test_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\test_static.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\vector.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\vector_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\view.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\view.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\vector\view_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\vector"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\vector"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "permutation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\permutation\canonical.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\file.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permutation.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permute.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permute_char.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permute_complex_double.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permute_complex_float.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permute_complex_long_double.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permute_double.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permute_float.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permute_int.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permute_long.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permute_long_double.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permute_short.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permute_uchar.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permute_uint.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permute_ulong.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permute_ushort.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permute_vector.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permute_vector_char.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permute_vector_complex_double.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permute_vector_complex_float.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permute_vector_complex_long_double.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permute_vector_double.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permute_vector_float.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permute_vector_int.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permute_vector_long.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permute_vector_long_double.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permute_vector_short.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permute_vector_uchar.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permute_vector_uint.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permute_vector_ulong.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\gsl_permute_vector_ushort.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\init.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\permutation.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\permute.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\permute_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\permutation\test.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\permutation"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\permutation"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "matrix"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\matrix\copy.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\copy_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\file.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\file_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\getset.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\getset_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\gsl_matrix.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\gsl_matrix_char.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\gsl_matrix_complex_double.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\gsl_matrix_complex_float.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\gsl_matrix_complex_long_double.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\gsl_matrix_double.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\gsl_matrix_float.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\gsl_matrix_int.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\gsl_matrix_long.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\gsl_matrix_long_double.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\gsl_matrix_short.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\gsl_matrix_uchar.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\gsl_matrix_uint.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\gsl_matrix_ulong.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\gsl_matrix_ushort.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\init.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\init_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\matrix.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\matrix_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\minmax.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\minmax_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\oper.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\oper_complex_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\oper_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\prop.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\prop_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\rowcol.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\rowcol_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\submatrix.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\submatrix_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\swap.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\swap_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\test.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\test_complex_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\test_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\test_static.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\view.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\view.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\matrix\view_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\matrix"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\matrix"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "linalg"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\linalg\apply_givens.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\linalg"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\linalg"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\linalg\balance.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\linalg"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\linalg"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\linalg\bidiag.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\linalg"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\linalg"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\linalg\cholesky.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\linalg"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\linalg"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\linalg\exponential.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\linalg"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\linalg"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\linalg\givens.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\linalg"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\linalg"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\linalg\gsl_linalg.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\linalg"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\linalg"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\linalg\hermtd.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\linalg"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\linalg"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\linalg\hh.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\linalg"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\linalg"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\linalg\householder.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\linalg"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\linalg"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\linalg\householdercomplex.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\linalg"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\linalg"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\linalg\lq.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\linalg"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\linalg"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\linalg\lu.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\linalg"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\linalg"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\linalg\luc.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\linalg"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\linalg"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\linalg\multiply.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\linalg"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\linalg"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\linalg\ptlq.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\linalg"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\linalg"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\linalg\qr.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\linalg"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\linalg"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\linalg\qrpt.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\linalg"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\linalg"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\linalg\svd.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\linalg"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\linalg"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\linalg\svdstep.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\linalg"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\linalg"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\linalg\symmtd.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\linalg"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\linalg"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\linalg\test.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\linalg"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\linalg"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\linalg\tridiag.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\linalg"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\linalg"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\linalg\tridiag.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\linalg"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\linalg"

!ENDIF 

# End Source File
# End Group
# Begin Group "block"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\block\block.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\block"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\block"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\block\block_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\block"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\block"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\block\file.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\block"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\block"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\block\fprintf_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\block"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\block"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\block\fwrite_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\block"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\block"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\block\gsl_block.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\block"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\block"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\block\gsl_block_char.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\block"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\block"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\block\gsl_block_complex_double.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\block"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\block"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\block\gsl_block_complex_float.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\block"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\block"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\block\gsl_block_complex_long_double.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\block"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\block"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\block\gsl_block_double.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\block"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\block"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\block\gsl_block_float.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\block"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\block"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\block\gsl_block_int.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\block"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\block"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\block\gsl_block_long.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\block"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\block"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\block\gsl_block_long_double.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\block"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\block"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\block\gsl_block_short.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\block"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\block"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\block\gsl_block_uchar.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\block"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\block"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\block\gsl_block_uint.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\block"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\block"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\block\gsl_block_ulong.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\block"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\block"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\block\gsl_block_ushort.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\block"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\block"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\block\gsl_check_range.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\block"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\block"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\block\init.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\block"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\block"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\block\init_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\block"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\block"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\block\test.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\block"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\block"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\block\test_complex_io.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\block"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\block"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\block\test_complex_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\block"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\block"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\block\test_io.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\block"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\block"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\block\test_source.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\block"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\block"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "blas"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\blas\blas.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\blas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\blas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\blas\gsl_blas.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\blas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\blas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\blas\gsl_blas_types.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\blas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\blas"

!ENDIF 

# End Source File
# End Group
# Begin Group "cblas"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\cblas\caxpy.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\cblas.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\ccopy.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\cdotc_sub.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\cdotu_sub.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\cgbmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\cgemm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\cgemv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\cgerc.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\cgeru.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\chbmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\chemm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\chemv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\cher.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\cher2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\cher2k.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\cherk.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\chpmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\chpr.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\chpr2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\cscal.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\csscal.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\cswap.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\csymm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\csyr2k.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\csyrk.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\ctbmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\ctbsv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\ctpmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\ctpsv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\ctrmm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\ctrmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\ctrsm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\ctrsv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\dasum.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\daxpy.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\dcopy.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\ddot.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\dgbmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\dgemm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\dgemv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\dger.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\dnrm2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\drot.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\drotg.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\drotm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\drotmg.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\dsbmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\dscal.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\dsdot.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\dspmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\dspr.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\dspr2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\dswap.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\dsymm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\dsymv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\dsyr.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\dsyr2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\dsyr2k.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\dsyrk.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\dtbmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\dtbsv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\dtpmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\dtpsv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\dtrmm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\dtrmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\dtrsm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\dtrsv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\dzasum.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\dznrm2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\gsl_cblas.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\hypot.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\icamax.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\idamax.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\isamax.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\izamax.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\sasum.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\saxpy.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\scasum.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\scnrm2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\scopy.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\sdot.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\sdsdot.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\sgbmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\sgemm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\sgemv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\sger.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\snrm2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_asum_c.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_asum_r.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_axpy_c.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_axpy_r.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_copy_c.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_copy_r.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_dot_c.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_dot_r.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_gbmv_c.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_gbmv_r.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_gemm_c.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_gemm_r.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_gemv_c.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_gemv_r.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_ger.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_gerc.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_geru.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_hbmv.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_hemm.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_hemv.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_her.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_her2.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_her2k.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_herk.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_hpmv.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_hpr.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_hpr2.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_iamax_c.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_iamax_r.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_nrm2_c.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_nrm2_r.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_rot.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_rotg.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_rotm.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_rotmg.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_sbmv.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_scal_c.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_scal_c_s.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_scal_r.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_spmv.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_spr.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_spr2.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_swap_c.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_swap_r.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_symm_c.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_symm_r.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_symv.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_syr.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_syr2.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_syr2k_c.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_syr2k_r.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_syrk_c.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_syrk_r.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_tbmv_c.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_tbmv_r.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_tbsv_c.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_tbsv_r.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_tpmv_c.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_tpmv_r.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_tpsv_c.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_tpsv_r.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_trmm_c.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_trmm_r.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_trmv_c.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_trmv_r.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_trsm_c.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_trsm_r.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_trsv_c.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\source_trsv_r.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\srot.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\srotg.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\srotm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\srotmg.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\ssbmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\sscal.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\sspmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\sspr.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\sspr2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\sswap.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\ssymm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\ssymv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\ssyr.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\ssyr2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\ssyr2k.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\ssyrk.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\stbmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\stbsv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\stpmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\stpsv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\strmm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\strmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\strsm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\strsv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_amax.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_asum.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_axpy.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_copy.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_dot.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_gbmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_gemm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_gemv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_ger.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_hbmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_hemm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_hemv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_her.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_her2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_her2k.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_herk.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_hpmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_hpr.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_hpr2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_nrm2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_rot.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_rotg.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_rotm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_rotmg.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_sbmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_scal.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_spmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_spr.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_spr2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_swap.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_symm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_symv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_syr.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_syr2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_syr2k.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_syrk.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_tbmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_tbsv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_tpmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_tpsv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_trmm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_trmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_trsm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\test_trsv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\tests.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\tests.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\xerbla.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\zaxpy.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\zcopy.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\zdotc_sub.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\zdotu_sub.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\zdscal.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\zgbmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\zgemm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\zgemv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\zgerc.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\zgeru.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\zhbmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\zhemm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\zhemv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\zher.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\zher2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\zher2k.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\zherk.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\zhpmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\zhpr.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\zhpr2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\zscal.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\zswap.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\zsymm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\zsyr2k.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\zsyrk.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\ztbmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\ztbsv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\ztpmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\ztpsv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\ztrmm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\ztrmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\ztrsm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cblas\ztrsv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cblas"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cblas"

!ENDIF 

# End Source File
# End Group
# Begin Group "sys"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\sys\coerce.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\sys"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\sys"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\sys\expm1.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\sys"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\sys"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\sys\fcmp.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\sys"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\sys"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\sys\fdiv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\sys"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\sys"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\sys\gsl_sys.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\sys"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\sys"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\sys\hypot.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\sys"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\sys"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\sys\infnan.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\sys"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\sys"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\sys\invhyp.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\sys"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\sys"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\sys\ldfrexp.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\sys"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\sys"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\sys\log1p.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\sys"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\sys"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\sys\minmax.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\sys"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\sys"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\sys\pow_int.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\sys"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\sys"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\sys\prec.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\sys"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\sys"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\sys\test.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\sys"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\sys"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "complex"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\complex\gsl_complex.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\complex"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\complex"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\complex\gsl_complex_math.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\complex"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\complex"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\complex\math.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\complex"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\complex"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\complex\results.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\complex"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\complex"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\complex\results1.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\complex"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\complex"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\complex\results_real.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\complex"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\complex"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\complex\test.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\complex"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\complex"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "ode-initval"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\ode-initval\bsimp.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\ode-initval"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\ode-initval"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\ode-initval\control.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\ode-initval"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\ode-initval"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\ode-initval\cscal.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\ode-initval"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\ode-initval"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\ode-initval\cstd.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\ode-initval"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\ode-initval"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\ode-initval\evolve.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\ode-initval"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\ode-initval"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\ode-initval\gear1.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\ode-initval"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\ode-initval"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\ode-initval\gear2.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\ode-initval"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\ode-initval"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\ode-initval\gsl_odeiv.h"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\ode-initval"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\ode-initval"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\ode-initval\odeiv_util.h"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\ode-initval"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\ode-initval"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\ode-initval\rk2.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\ode-initval"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\ode-initval"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\ode-initval\rk2imp.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\ode-initval"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\ode-initval"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\ode-initval\rk2simp.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\ode-initval"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\ode-initval"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\ode-initval\rk4.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\ode-initval"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\ode-initval"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\ode-initval\rk4imp.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\ode-initval"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\ode-initval"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\ode-initval\rk8pd.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\ode-initval"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\ode-initval"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\ode-initval\rkck.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\ode-initval"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\ode-initval"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\ode-initval\rkf45.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\ode-initval"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\ode-initval"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\ode-initval\step.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\ode-initval"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\ode-initval"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\ode-initval\test.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\ode-initval"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\ode-initval"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "randist"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\randist\bernoulli.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\beta.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\bigauss.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\binomial.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\binomial_tpe.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\cauchy.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\chisq.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\dirichlet.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\discrete.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\erlang.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\exponential.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\exppow.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\fdist.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\flat.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\gamma.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\gauss.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\gausstail.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\gausszig.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\geometric.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\gsl_randist.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\gumbel.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\hyperg.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\landau.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\laplace.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\levy.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\logarithmic.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\logistic.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\lognormal.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\multinomial.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\nbinomial.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\pareto.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\pascal.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\poisson.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\rayleigh.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\shuffle.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\sphere.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\tdist.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\test.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\randist\weibull.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\randist"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\randist"

!ENDIF 

# End Source File
# End Group
# Begin Group "specfunc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\specfunc\airy.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\airy_der.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\airy_zero.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\atanint.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\bessel.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\bessel.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\bessel_amp_phase.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\bessel_amp_phase.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\bessel_i.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\bessel_I0.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\bessel_I1.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\bessel_In.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\bessel_Inu.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\bessel_j.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\bessel_J0.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\bessel_J1.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\bessel_Jn.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\bessel_Jnu.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\bessel_k.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\bessel_K0.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\bessel_K1.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\bessel_Kn.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\bessel_Knu.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\bessel_olver.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\bessel_olver.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\bessel_sequence.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\bessel_temme.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\bessel_temme.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\bessel_y.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\bessel_Y0.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\bessel_Y1.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\bessel_Yn.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\bessel_Ynu.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\bessel_zero.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\beta.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\beta_inc.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\cheb_eval.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\cheb_eval_mode.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\chebyshev.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\check.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\clausen.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\coulomb.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\coulomb_bound.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\coupling.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\dawson.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\debye.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\dilog.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\elementary.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\ellint.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\elljac.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\erfc.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\error.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\eval.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\exp.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\expint.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\expint3.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\fermi_dirac.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gamma.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gamma_inc.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gegenbauer.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_sf.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_sf_airy.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_sf_bessel.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_sf_clausen.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_sf_coulomb.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_sf_coupling.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_sf_dawson.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_sf_debye.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_sf_dilog.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_sf_elementary.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_sf_ellint.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_sf_elljac.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_sf_erf.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_sf_exp.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_sf_expint.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_sf_fermi_dirac.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_sf_gamma.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_sf_gegenbauer.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_sf_hyperg.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_sf_laguerre.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_sf_lambert.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_sf_legendre.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_sf_log.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_sf_pow_int.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_sf_psi.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_sf_result.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_sf_synchrotron.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_sf_transport.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_sf_trig.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_sf_zeta.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\gsl_specfunc.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\hyperg.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\hyperg.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\hyperg_0F1.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\hyperg_1F1.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\hyperg_2F0.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\hyperg_2F1.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\hyperg_U.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\laguerre.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\lambert.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\legendre.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\legendre_con.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\legendre_H3d.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\legendre_poly.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\legendre_Qn.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\log.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\poch.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\pow_int.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\psi.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\recurse.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\result.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\shint.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\sinint.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\synchrotron.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\test_airy.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\test_bessel.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\test_coulomb.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\test_dilog.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\test_gamma.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\test_hyperg.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\test_legendre.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\test_sf.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\test_sf.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\transport.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\trig.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\specfunc\zeta.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\specfunc"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\specfunc"

!ENDIF 

# End Source File
# End Group
# Begin Group "rng"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\rng\borosh13.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\cmrg.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\coveyou.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\default.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\file.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\fishman18.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\fishman20.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\fishman2x.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\gfsr4.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\gsl_rng.h

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\knuthran.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\knuthran2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\lecuyer21.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\minstd.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\mrg.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\mt.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\r250.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\ran0.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\ran1.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\ran2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\ran3.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\rand.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\rand48.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\random.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\randu.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\ranf.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\ranlux.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\ranlxd.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\ranlxs.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\ranmar.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\rng.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\schrage.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\slatec.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\taus.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\taus113.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\test.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\transputer.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\tt.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\types.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\uni.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\uni32.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\vax.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\waterman14.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\rng\zuf.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

# PROP Intermediate_Dir "Release\rng"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\rng"

!ENDIF 

# End Source File
# End Group
# Begin Group "fft"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\fft\fft.c
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
