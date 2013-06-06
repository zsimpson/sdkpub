# Microsoft Developer Studio Project File - Name="blas" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=blas - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "blas.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "blas.mak" CFG="blas - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "blas - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "blas - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "blas - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\f2clibs" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "blas - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\f2clibs" /I "o:\clapack\f2clibs" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
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

# Name "blas - Win32 Release"
# Name "blas - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Src\caxpy.c
# End Source File
# Begin Source File

SOURCE=.\Src\ccopy.c
# End Source File
# Begin Source File

SOURCE=.\Src\cdotc.c
# End Source File
# Begin Source File

SOURCE=.\Src\cdotu.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgbmv.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgemm.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgemv.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgerc.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgeru.c
# End Source File
# Begin Source File

SOURCE=.\Src\chbmv.c
# End Source File
# Begin Source File

SOURCE=.\Src\chemm.c
# End Source File
# Begin Source File

SOURCE=.\Src\chemv.c
# End Source File
# Begin Source File

SOURCE=.\Src\cher.c
# End Source File
# Begin Source File

SOURCE=.\Src\cher2.c
# End Source File
# Begin Source File

SOURCE=.\Src\cher2k.c
# End Source File
# Begin Source File

SOURCE=.\Src\cherk.c
# End Source File
# Begin Source File

SOURCE=.\Src\chpmv.c
# End Source File
# Begin Source File

SOURCE=.\Src\chpr.c
# End Source File
# Begin Source File

SOURCE=.\Src\chpr2.c
# End Source File
# Begin Source File

SOURCE=.\Src\crotg.c
# End Source File
# Begin Source File

SOURCE=.\Src\cscal.c
# End Source File
# Begin Source File

SOURCE=.\Src\csscal.c
# End Source File
# Begin Source File

SOURCE=.\Src\cswap.c
# End Source File
# Begin Source File

SOURCE=.\Src\csymm.c
# End Source File
# Begin Source File

SOURCE=.\Src\csyr2k.c
# End Source File
# Begin Source File

SOURCE=.\Src\csyrk.c
# End Source File
# Begin Source File

SOURCE=.\Src\ctbmv.c
# End Source File
# Begin Source File

SOURCE=.\Src\ctbsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\ctpmv.c
# End Source File
# Begin Source File

SOURCE=.\Src\ctpsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\ctrmm.c
# End Source File
# Begin Source File

SOURCE=.\Src\ctrmv.c
# End Source File
# Begin Source File

SOURCE=.\Src\ctrsm.c
# End Source File
# Begin Source File

SOURCE=.\Src\ctrsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\dasum.c
# End Source File
# Begin Source File

SOURCE=.\Src\daxpy.c
# End Source File
# Begin Source File

SOURCE=.\Src\dcabs1.c
# End Source File
# Begin Source File

SOURCE=.\Src\dcopy.c
# End Source File
# Begin Source File

SOURCE=.\Src\ddot.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgbmv.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgemm.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgemv.c
# End Source File
# Begin Source File

SOURCE=.\Src\dger.c
# End Source File
# Begin Source File

SOURCE=.\Src\dnrm2.c
# End Source File
# Begin Source File

SOURCE=.\Src\drot.c
# End Source File
# Begin Source File

SOURCE=.\Src\drotg.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsbmv.c
# End Source File
# Begin Source File

SOURCE=.\Src\dscal.c
# End Source File
# Begin Source File

SOURCE=.\Src\dspmv.c
# End Source File
# Begin Source File

SOURCE=.\Src\dspr.c
# End Source File
# Begin Source File

SOURCE=.\Src\dspr2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dswap.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsymm.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsymv.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsyr.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsyr2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsyr2k.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsyrk.c
# End Source File
# Begin Source File

SOURCE=.\Src\dtbmv.c
# End Source File
# Begin Source File

SOURCE=.\Src\dtbsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\dtpmv.c
# End Source File
# Begin Source File

SOURCE=.\Src\dtpsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\dtrmm.c
# End Source File
# Begin Source File

SOURCE=.\Src\dtrmv.c
# End Source File
# Begin Source File

SOURCE=.\Src\dtrsm.c
# End Source File
# Begin Source File

SOURCE=.\Src\dtrsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\dzasum.c
# End Source File
# Begin Source File

SOURCE=.\Src\dznrm2.c
# End Source File
# Begin Source File

SOURCE=.\Src\icamax.c
# End Source File
# Begin Source File

SOURCE=.\Src\idamax.c
# End Source File
# Begin Source File

SOURCE=.\Src\isamax.c
# End Source File
# Begin Source File

SOURCE=.\Src\izamax.c
# End Source File
# Begin Source File

SOURCE=.\Src\lsame.c
# End Source File
# Begin Source File

SOURCE=.\Src\sasum.c
# End Source File
# Begin Source File

SOURCE=.\Src\saxpy.c
# End Source File
# Begin Source File

SOURCE=.\Src\scasum.c
# End Source File
# Begin Source File

SOURCE=.\Src\scnrm2.c
# End Source File
# Begin Source File

SOURCE=.\Src\scopy.c
# End Source File
# Begin Source File

SOURCE=.\Src\sdot.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgbmv.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgemm.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgemv.c
# End Source File
# Begin Source File

SOURCE=.\Src\sger.c
# End Source File
# Begin Source File

SOURCE=.\Src\snrm2.c
# End Source File
# Begin Source File

SOURCE=.\Src\srot.c
# End Source File
# Begin Source File

SOURCE=.\Src\srotg.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssbmv.c
# End Source File
# Begin Source File

SOURCE=.\Src\sscal.c
# End Source File
# Begin Source File

SOURCE=.\Src\sspmv.c
# End Source File
# Begin Source File

SOURCE=.\Src\sspr.c
# End Source File
# Begin Source File

SOURCE=.\Src\sspr2.c
# End Source File
# Begin Source File

SOURCE=.\Src\sswap.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssymm.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssymv.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssyr.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssyr2.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssyr2k.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssyrk.c
# End Source File
# Begin Source File

SOURCE=.\Src\stbmv.c
# End Source File
# Begin Source File

SOURCE=.\Src\stbsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\stpmv.c
# End Source File
# Begin Source File

SOURCE=.\Src\stpsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\strmm.c
# End Source File
# Begin Source File

SOURCE=.\Src\strmv.c
# End Source File
# Begin Source File

SOURCE=.\Src\strsm.c
# End Source File
# Begin Source File

SOURCE=.\Src\strsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\xerbla.c
# End Source File
# Begin Source File

SOURCE=.\Src\zaxpy.c
# End Source File
# Begin Source File

SOURCE=.\Src\zcopy.c
# End Source File
# Begin Source File

SOURCE=.\Src\zdotc.c
# End Source File
# Begin Source File

SOURCE=.\Src\zdotu.c
# End Source File
# Begin Source File

SOURCE=.\Src\zdscal.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgbmv.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgemm.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgemv.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgerc.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgeru.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhbmv.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhemm.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhemv.c
# End Source File
# Begin Source File

SOURCE=.\Src\zher.c
# End Source File
# Begin Source File

SOURCE=.\Src\zher2.c
# End Source File
# Begin Source File

SOURCE=.\Src\zher2k.c
# End Source File
# Begin Source File

SOURCE=.\Src\zherk.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhpmv.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhpr.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhpr2.c
# End Source File
# Begin Source File

SOURCE=.\Src\zrotg.c
# End Source File
# Begin Source File

SOURCE=.\Src\zscal.c
# End Source File
# Begin Source File

SOURCE=.\Src\zswap.c
# End Source File
# Begin Source File

SOURCE=.\Src\zsymm.c
# End Source File
# Begin Source File

SOURCE=.\Src\zsyr2k.c
# End Source File
# Begin Source File

SOURCE=.\Src\zsyrk.c
# End Source File
# Begin Source File

SOURCE=.\Src\ztbmv.c
# End Source File
# Begin Source File

SOURCE=.\Src\ztbsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\ztpmv.c
# End Source File
# Begin Source File

SOURCE=.\Src\ztpsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\ztrmm.c
# End Source File
# Begin Source File

SOURCE=.\Src\ztrmv.c
# End Source File
# Begin Source File

SOURCE=.\Src\ztrsm.c
# End Source File
# Begin Source File

SOURCE=.\Src\ztrsv.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\SRC\blaswrap.h
# End Source File
# Begin Source File

SOURCE=.\SRC\f2c.h
# End Source File
# End Group
# End Target
# End Project
