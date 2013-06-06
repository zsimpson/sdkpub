# Microsoft Developer Studio Project File - Name="libF77" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libF77 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libF77.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libF77.mak" CFG="libF77 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libF77 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libF77 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libF77 - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /I "O:\CLAPACK\F2clibs" /D "NDEBUG" /D "WIN32" /D "_WIN32" /D "MSDOS" /D "Allow_TYQUAD" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WIN32" /D "MSDOS" /D "Allow_TYQUAD" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
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

# Name "libF77 - Win32 Release"
# Name "libF77 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\libF77\abort_.c
# End Source File
# Begin Source File

SOURCE=.\libF77\c_abs.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\c_cos.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\c_div.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\c_exp.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\c_log.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\c_sin.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\c_sqrt.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\cabs.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\d_abs.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\d_acos.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\d_asin.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\d_atan.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\d_atn2.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\d_cnjg.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\d_cos.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\d_cosh.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\d_dim.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\d_exp.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\d_imag.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\d_int.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\d_lg10.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\d_log.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\d_mod.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\d_nint.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\d_prod.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\d_sign.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\d_sin.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\d_sinh.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\d_sqrt.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\d_tan.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\d_tanh.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\derf_.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\derfc_.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\dtime_.c
# End Source File
# Begin Source File

SOURCE=.\libF77\ef1asc_.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\ef1cmc_.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\erf_.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\erfc_.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\etime_.c
# End Source File
# Begin Source File

SOURCE=.\libF77\exit_.c
# End Source File
# Begin Source File

SOURCE=.\libF77\F77_aloc.c
# End Source File
# Begin Source File

SOURCE=.\libF77\getarg_.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\getenv_.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\h_abs.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\h_dim.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\h_dnnt.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\h_indx.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\h_len.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\h_mod.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\h_nint.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\h_sign.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\hl_ge.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\hl_gt.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\hl_le.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\hl_lt.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\i_abs.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\i_dim.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\i_dnnt.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\i_indx.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\i_len.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\i_mod.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\i_nint.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\i_sign.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\iargc_.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\l_ge.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\l_gt.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\l_le.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\l_lt.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\lbitbits.c
# End Source File
# Begin Source File

SOURCE=.\libF77\lbitshft.c
# End Source File
# Begin Source File

SOURCE=.\libF77\main.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\pow_ci.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\pow_dd.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\pow_di.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\pow_hh.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\pow_ii.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\pow_qq.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\pow_ri.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\pow_zi.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\pow_zz.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\qbitbits.c
# End Source File
# Begin Source File

SOURCE=.\libF77\qbitshft.c
# End Source File
# Begin Source File

SOURCE=.\libF77\r_abs.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\r_acos.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\r_asin.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\r_atan.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\r_atn2.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\r_cnjg.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\r_cos.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\r_cosh.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\r_dim.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\r_exp.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\r_imag.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\r_int.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\r_lg10.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\r_log.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\r_mod.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\r_nint.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\r_sign.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\r_sin.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\r_sinh.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\r_sqrt.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\r_tan.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\r_tanh.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\s_cat.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\s_cmp.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\s_copy.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\s_paus.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\s_rnge.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\s_stop.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\sig_die.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\signal_.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\system_.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\Version.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\z_abs.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\z_cos.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\z_div.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\z_exp.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\z_log.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\z_sin.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\libF77\z_sqrt.c

!IF  "$(CFG)" == "libF77 - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "libF77 - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\f2c.h
# End Source File
# End Group
# End Target
# End Project
