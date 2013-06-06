# Microsoft Developer Studio Project File - Name="clapack" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=clapack - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "clapack.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "clapack.mak" CFG="clapack - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "clapack - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "clapack - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "clapack - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "_WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "clapack - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
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

# Name "clapack - Win32 Release"
# Name "clapack - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Src\cbdsqr.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgbbrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgbcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgbequ.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgbrfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgbsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgbsvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgbtf2.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgbtrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgbtrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgebak.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgebal.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgebd2.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgebrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgecon.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgeequ.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgees.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgeesx.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgeev.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgeevx.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgegs.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgegv.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgehd2.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgehrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgelq2.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgelqf.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgels.c
# End Source File
# Begin Source File

SOURCE=.\SRC\cgelsd.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgelss.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgelsx.c
# End Source File
# Begin Source File

SOURCE=.\SRC\cgelsy.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgeql2.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgeqlf.c
# End Source File
# Begin Source File

SOURCE=.\SRC\cgeqp3.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgeqpf.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgeqr2.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgeqrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgerfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgerq2.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgerqf.c
# End Source File
# Begin Source File

SOURCE=.\SRC\cgesc2.c
# End Source File
# Begin Source File

SOURCE=.\SRC\cgesdd.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgesv.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgesvd.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgesvx.c
# End Source File
# Begin Source File

SOURCE=.\SRC\cgetc2.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgetf2.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgetrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgetri.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgetrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\cggbak.c
# End Source File
# Begin Source File

SOURCE=.\Src\cggbal.c
# End Source File
# Begin Source File

SOURCE=.\SRC\cgges.c
# End Source File
# Begin Source File

SOURCE=.\SRC\cggesx.c
# End Source File
# Begin Source File

SOURCE=.\SRC\cggev.c
# End Source File
# Begin Source File

SOURCE=.\SRC\cggevx.c
# End Source File
# Begin Source File

SOURCE=.\Src\cggglm.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgghrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgglse.c
# End Source File
# Begin Source File

SOURCE=.\Src\cggqrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\cggrqf.c
# End Source File
# Begin Source File

SOURCE=.\Src\cggsvd.c
# End Source File
# Begin Source File

SOURCE=.\Src\cggsvp.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgtcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgtrfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgtsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgtsvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgttrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\cgttrs.c
# End Source File
# Begin Source File

SOURCE=.\SRC\cgtts2.c
# End Source File
# Begin Source File

SOURCE=.\Src\chbev.c
# End Source File
# Begin Source File

SOURCE=.\Src\chbevd.c
# End Source File
# Begin Source File

SOURCE=.\Src\chbevx.c
# End Source File
# Begin Source File

SOURCE=.\Src\chbgst.c
# End Source File
# Begin Source File

SOURCE=.\Src\chbgv.c
# End Source File
# Begin Source File

SOURCE=.\SRC\chbgvd.c
# End Source File
# Begin Source File

SOURCE=.\SRC\chbgvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\chbtrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\checon.c
# End Source File
# Begin Source File

SOURCE=.\Src\cheev.c
# End Source File
# Begin Source File

SOURCE=.\Src\cheevd.c
# End Source File
# Begin Source File

SOURCE=.\SRC\cheevr.c
# End Source File
# Begin Source File

SOURCE=.\Src\cheevx.c
# End Source File
# Begin Source File

SOURCE=.\Src\chegs2.c
# End Source File
# Begin Source File

SOURCE=.\Src\chegst.c
# End Source File
# Begin Source File

SOURCE=.\Src\chegv.c
# End Source File
# Begin Source File

SOURCE=.\SRC\chegvd.c
# End Source File
# Begin Source File

SOURCE=.\SRC\chegvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\cherfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\chesv.c
# End Source File
# Begin Source File

SOURCE=.\Src\chesvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\chetd2.c
# End Source File
# Begin Source File

SOURCE=.\Src\chetf2.c
# End Source File
# Begin Source File

SOURCE=.\Src\chetrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\chetrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\chetri.c
# End Source File
# Begin Source File

SOURCE=.\Src\chetrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\chgeqz.c
# End Source File
# Begin Source File

SOURCE=.\Src\chpcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\chpev.c
# End Source File
# Begin Source File

SOURCE=.\Src\chpevd.c
# End Source File
# Begin Source File

SOURCE=.\Src\chpevx.c
# End Source File
# Begin Source File

SOURCE=.\Src\chpgst.c
# End Source File
# Begin Source File

SOURCE=.\Src\chpgv.c
# End Source File
# Begin Source File

SOURCE=.\SRC\chpgvd.c
# End Source File
# Begin Source File

SOURCE=.\SRC\chpgvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\chprfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\chpsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\chpsvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\chptrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\chptrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\chptri.c
# End Source File
# Begin Source File

SOURCE=.\Src\chptrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\chsein.c
# End Source File
# Begin Source File

SOURCE=.\Src\chseqr.c
# End Source File
# Begin Source File

SOURCE=.\Src\clabrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\clacgv.c
# End Source File
# Begin Source File

SOURCE=.\Src\clacon.c
# End Source File
# Begin Source File

SOURCE=.\SRC\clacp2.c
# End Source File
# Begin Source File

SOURCE=.\Src\clacpy.c
# End Source File
# Begin Source File

SOURCE=.\Src\clacrm.c
# End Source File
# Begin Source File

SOURCE=.\Src\clacrt.c
# End Source File
# Begin Source File

SOURCE=.\Src\cladiv.c
# End Source File
# Begin Source File

SOURCE=.\Src\claed0.c
# End Source File
# Begin Source File

SOURCE=.\Src\claed7.c
# End Source File
# Begin Source File

SOURCE=.\Src\claed8.c
# End Source File
# Begin Source File

SOURCE=.\Src\claein.c
# End Source File
# Begin Source File

SOURCE=.\Src\claesy.c
# End Source File
# Begin Source File

SOURCE=.\Src\claev2.c
# End Source File
# Begin Source File

SOURCE=.\Src\clags2.c
# End Source File
# Begin Source File

SOURCE=.\Src\clagtm.c
# End Source File
# Begin Source File

SOURCE=.\Src\clahef.c
# End Source File
# Begin Source File

SOURCE=.\Src\clahqr.c
# End Source File
# Begin Source File

SOURCE=.\Src\clahrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\claic1.c
# End Source File
# Begin Source File

SOURCE=.\SRC\clals0.c
# End Source File
# Begin Source File

SOURCE=.\SRC\clalsa.c
# End Source File
# Begin Source File

SOURCE=.\SRC\clalsd.c
# End Source File
# Begin Source File

SOURCE=.\Src\clangb.c
# End Source File
# Begin Source File

SOURCE=.\Src\clange.c
# End Source File
# Begin Source File

SOURCE=.\Src\clangt.c
# End Source File
# Begin Source File

SOURCE=.\Src\clanhb.c
# End Source File
# Begin Source File

SOURCE=.\Src\clanhe.c
# End Source File
# Begin Source File

SOURCE=.\Src\clanhp.c
# End Source File
# Begin Source File

SOURCE=.\Src\clanhs.c
# End Source File
# Begin Source File

SOURCE=.\Src\clanht.c
# End Source File
# Begin Source File

SOURCE=.\Src\clansb.c
# End Source File
# Begin Source File

SOURCE=.\Src\clansp.c
# End Source File
# Begin Source File

SOURCE=.\Src\clansy.c
# End Source File
# Begin Source File

SOURCE=.\Src\clantb.c
# End Source File
# Begin Source File

SOURCE=.\Src\clantp.c
# End Source File
# Begin Source File

SOURCE=.\Src\clantr.c
# End Source File
# Begin Source File

SOURCE=.\Src\clapll.c
# End Source File
# Begin Source File

SOURCE=.\Src\clapmt.c
# End Source File
# Begin Source File

SOURCE=.\Src\claqgb.c
# End Source File
# Begin Source File

SOURCE=.\Src\claqge.c
# End Source File
# Begin Source File

SOURCE=.\Src\claqhb.c
# End Source File
# Begin Source File

SOURCE=.\Src\claqhe.c
# End Source File
# Begin Source File

SOURCE=.\Src\claqhp.c
# End Source File
# Begin Source File

SOURCE=.\SRC\claqp2.c
# End Source File
# Begin Source File

SOURCE=.\SRC\claqps.c
# End Source File
# Begin Source File

SOURCE=.\Src\claqsb.c
# End Source File
# Begin Source File

SOURCE=.\Src\claqsp.c
# End Source File
# Begin Source File

SOURCE=.\Src\claqsy.c
# End Source File
# Begin Source File

SOURCE=.\SRC\clar1v.c
# End Source File
# Begin Source File

SOURCE=.\Src\clar2v.c
# End Source File
# Begin Source File

SOURCE=.\SRC\clarcm.c
# End Source File
# Begin Source File

SOURCE=.\Src\clarf.c
# End Source File
# Begin Source File

SOURCE=.\Src\clarfb.c
# End Source File
# Begin Source File

SOURCE=.\Src\clarfg.c
# End Source File
# Begin Source File

SOURCE=.\Src\clarft.c
# End Source File
# Begin Source File

SOURCE=.\Src\clarfx.c
# End Source File
# Begin Source File

SOURCE=.\Src\clargv.c
# End Source File
# Begin Source File

SOURCE=.\Src\clarnv.c
# End Source File
# Begin Source File

SOURCE=.\SRC\clarrv.c
# End Source File
# Begin Source File

SOURCE=.\Src\clartg.c
# End Source File
# Begin Source File

SOURCE=.\Src\clartv.c
# End Source File
# Begin Source File

SOURCE=.\SRC\clarz.c
# End Source File
# Begin Source File

SOURCE=.\SRC\clarzb.c
# End Source File
# Begin Source File

SOURCE=.\SRC\clarzt.c
# End Source File
# Begin Source File

SOURCE=.\Src\clascl.c
# End Source File
# Begin Source File

SOURCE=.\Src\claset.c
# End Source File
# Begin Source File

SOURCE=.\Src\clasr.c
# End Source File
# Begin Source File

SOURCE=.\Src\classq.c
# End Source File
# Begin Source File

SOURCE=.\Src\claswp.c
# End Source File
# Begin Source File

SOURCE=.\Src\clasyf.c
# End Source File
# Begin Source File

SOURCE=.\Src\clatbs.c
# End Source File
# Begin Source File

SOURCE=.\SRC\clatdf.c
# End Source File
# Begin Source File

SOURCE=.\Src\clatps.c
# End Source File
# Begin Source File

SOURCE=.\Src\clatrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\clatrs.c
# End Source File
# Begin Source File

SOURCE=.\SRC\clatrz.c
# End Source File
# Begin Source File

SOURCE=.\Src\clatzm.c
# End Source File
# Begin Source File

SOURCE=.\Src\clauu2.c
# End Source File
# Begin Source File

SOURCE=.\Src\clauum.c
# End Source File
# Begin Source File

SOURCE=.\Src\cpbcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\cpbequ.c
# End Source File
# Begin Source File

SOURCE=.\Src\cpbrfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\cpbstf.c
# End Source File
# Begin Source File

SOURCE=.\Src\cpbsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\cpbsvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\cpbtf2.c
# End Source File
# Begin Source File

SOURCE=.\Src\cpbtrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\cpbtrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\cpocon.c
# End Source File
# Begin Source File

SOURCE=.\Src\cpoequ.c
# End Source File
# Begin Source File

SOURCE=.\Src\cporfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\cposv.c
# End Source File
# Begin Source File

SOURCE=.\Src\cposvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\cpotf2.c
# End Source File
# Begin Source File

SOURCE=.\Src\cpotrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\cpotri.c
# End Source File
# Begin Source File

SOURCE=.\Src\cpotrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\cppcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\cppequ.c
# End Source File
# Begin Source File

SOURCE=.\Src\cpprfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\cppsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\cppsvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\cpptrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\cpptri.c
# End Source File
# Begin Source File

SOURCE=.\Src\cpptrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\cptcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\cpteqr.c
# End Source File
# Begin Source File

SOURCE=.\Src\cptrfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\cptsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\cptsvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\cpttrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\cpttrs.c
# End Source File
# Begin Source File

SOURCE=.\SRC\cptts2.c
# End Source File
# Begin Source File

SOURCE=.\Src\crot.c
# End Source File
# Begin Source File

SOURCE=.\Src\cspcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\cspmv.c
# End Source File
# Begin Source File

SOURCE=.\Src\cspr.c
# End Source File
# Begin Source File

SOURCE=.\Src\csprfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\cspsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\cspsvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\csptrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\csptri.c
# End Source File
# Begin Source File

SOURCE=.\Src\csptrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\csrot.c
# End Source File
# Begin Source File

SOURCE=.\Src\csrscl.c
# End Source File
# Begin Source File

SOURCE=.\Src\cstedc.c
# End Source File
# Begin Source File

SOURCE=.\SRC\cstegr.c
# End Source File
# Begin Source File

SOURCE=.\Src\cstein.c
# End Source File
# Begin Source File

SOURCE=.\Src\csteqr.c
# End Source File
# Begin Source File

SOURCE=.\Src\csycon.c
# End Source File
# Begin Source File

SOURCE=.\Src\csymv.c
# End Source File
# Begin Source File

SOURCE=.\Src\csyr.c
# End Source File
# Begin Source File

SOURCE=.\Src\csyrfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\csysv.c
# End Source File
# Begin Source File

SOURCE=.\Src\csysvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\csytf2.c
# End Source File
# Begin Source File

SOURCE=.\Src\csytrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\csytri.c
# End Source File
# Begin Source File

SOURCE=.\Src\csytrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\ctbcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\ctbrfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\ctbtrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\ctgevc.c
# End Source File
# Begin Source File

SOURCE=.\SRC\ctgex2.c
# End Source File
# Begin Source File

SOURCE=.\SRC\ctgexc.c
# End Source File
# Begin Source File

SOURCE=.\SRC\ctgsen.c
# End Source File
# Begin Source File

SOURCE=.\Src\ctgsja.c
# End Source File
# Begin Source File

SOURCE=.\SRC\ctgsna.c
# End Source File
# Begin Source File

SOURCE=.\SRC\ctgsy2.c
# End Source File
# Begin Source File

SOURCE=.\SRC\ctgsyl.c
# End Source File
# Begin Source File

SOURCE=.\Src\ctpcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\ctprfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\ctptri.c
# End Source File
# Begin Source File

SOURCE=.\Src\ctptrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\ctrcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\ctrevc.c
# End Source File
# Begin Source File

SOURCE=.\Src\ctrexc.c
# End Source File
# Begin Source File

SOURCE=.\Src\ctrrfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\ctrsen.c
# End Source File
# Begin Source File

SOURCE=.\Src\ctrsna.c
# End Source File
# Begin Source File

SOURCE=.\Src\ctrsyl.c
# End Source File
# Begin Source File

SOURCE=.\Src\ctrti2.c
# End Source File
# Begin Source File

SOURCE=.\Src\ctrtri.c
# End Source File
# Begin Source File

SOURCE=.\Src\ctrtrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\ctzrqf.c
# End Source File
# Begin Source File

SOURCE=.\SRC\ctzrzf.c
# End Source File
# Begin Source File

SOURCE=.\Src\cung2l.c
# End Source File
# Begin Source File

SOURCE=.\Src\cung2r.c
# End Source File
# Begin Source File

SOURCE=.\Src\cungbr.c
# End Source File
# Begin Source File

SOURCE=.\Src\cunghr.c
# End Source File
# Begin Source File

SOURCE=.\Src\cungl2.c
# End Source File
# Begin Source File

SOURCE=.\Src\cunglq.c
# End Source File
# Begin Source File

SOURCE=.\Src\cungql.c
# End Source File
# Begin Source File

SOURCE=.\Src\cungqr.c
# End Source File
# Begin Source File

SOURCE=.\Src\cungr2.c
# End Source File
# Begin Source File

SOURCE=.\Src\cungrq.c
# End Source File
# Begin Source File

SOURCE=.\Src\cungtr.c
# End Source File
# Begin Source File

SOURCE=.\Src\cunm2l.c
# End Source File
# Begin Source File

SOURCE=.\Src\cunm2r.c
# End Source File
# Begin Source File

SOURCE=.\Src\cunmbr.c
# End Source File
# Begin Source File

SOURCE=.\Src\cunmhr.c
# End Source File
# Begin Source File

SOURCE=.\Src\cunml2.c
# End Source File
# Begin Source File

SOURCE=.\Src\cunmlq.c
# End Source File
# Begin Source File

SOURCE=.\Src\cunmql.c
# End Source File
# Begin Source File

SOURCE=.\Src\cunmqr.c
# End Source File
# Begin Source File

SOURCE=.\Src\cunmr2.c
# End Source File
# Begin Source File

SOURCE=.\SRC\cunmr3.c
# End Source File
# Begin Source File

SOURCE=.\Src\cunmrq.c
# End Source File
# Begin Source File

SOURCE=.\SRC\cunmrz.c
# End Source File
# Begin Source File

SOURCE=.\Src\cunmtr.c
# End Source File
# Begin Source File

SOURCE=.\Src\cupgtr.c
# End Source File
# Begin Source File

SOURCE=.\Src\cupmtr.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dbdsdc.c
# End Source File
# Begin Source File

SOURCE=.\Src\dbdsqr.c
# End Source File
# Begin Source File

SOURCE=.\Src\ddisna.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgbbrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgbcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgbequ.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgbrfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgbsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgbsvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgbtf2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgbtrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgbtrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgebak.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgebal.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgebd2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgebrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgecon.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgeequ.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgees.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgeesx.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgeev.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgeevx.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgegs.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgegv.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgehd2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgehrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgelq2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgelqf.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgels.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dgelsd.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgelss.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgelsx.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dgelsy.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgeql2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgeqlf.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dgeqp3.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgeqpf.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgeqr2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgeqrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgerfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgerq2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgerqf.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dgesc2.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dgesdd.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgesv.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgesvd.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgesvx.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dgetc2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgetf2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgetrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgetri.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgetrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\dggbak.c
# End Source File
# Begin Source File

SOURCE=.\Src\dggbal.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dgges.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dggesx.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dggev.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dggevx.c
# End Source File
# Begin Source File

SOURCE=.\Src\dggglm.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgghrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgglse.c
# End Source File
# Begin Source File

SOURCE=.\Src\dggqrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\dggrqf.c
# End Source File
# Begin Source File

SOURCE=.\Src\dggsvd.c
# End Source File
# Begin Source File

SOURCE=.\Src\dggsvp.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgtcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgtrfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgtsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgtsvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgttrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\dgttrs.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dgtts2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dhgeqz.c
# End Source File
# Begin Source File

SOURCE=.\Src\dhsein.c
# End Source File
# Begin Source File

SOURCE=.\Src\dhseqr.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlabad.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlabrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlacon.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlacpy.c
# End Source File
# Begin Source File

SOURCE=.\Src\dladiv.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlae2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlaebz.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlaed0.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlaed1.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlaed2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlaed3.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlaed4.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlaed5.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlaed6.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlaed7.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlaed8.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlaed9.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlaeda.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlaein.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlaev2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlaexc.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlag2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlags2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlagtf.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlagtm.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlagts.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlagv2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlahqr.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlahrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlaic1.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlaln2.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlals0.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlalsa.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlalsd.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlamch.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlamrg.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlangb.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlange.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlangt.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlanhs.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlansb.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlansp.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlanst.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlansy.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlantb.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlantp.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlantr.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlanv2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlapll.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlapmt.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlapy2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlapy3.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlaqgb.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlaqge.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlaqp2.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlaqps.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlaqsb.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlaqsp.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlaqsy.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlaqtr.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlar1v.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlar2v.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlarf.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlarfb.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlarfg.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlarft.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlarfx.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlargv.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlarnv.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlarrb.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlarre.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlarrf.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlarrv.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlartg.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlartv.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlaruv.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlarz.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlarzb.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlarzt.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlas2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlascl.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlasd0.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlasd1.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlasd2.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlasd3.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlasd4.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlasd5.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlasd6.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlasd7.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlasd8.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlasd9.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlasda.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlasdq.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlasdt.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlaset.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlasq1.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlasq2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlasq3.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlasq4.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlasq5.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlasq6.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlasr.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlasrt.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlassq.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlasv2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlaswp.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlasy2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlasyf.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlatbs.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlatdf.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlatps.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlatrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlatrs.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dlatrz.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlatzm.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlauu2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dlauum.c
# End Source File
# Begin Source File

SOURCE=.\Src\dopgtr.c
# End Source File
# Begin Source File

SOURCE=.\Src\dopmtr.c
# End Source File
# Begin Source File

SOURCE=.\Src\dorg2l.c
# End Source File
# Begin Source File

SOURCE=.\Src\dorg2r.c
# End Source File
# Begin Source File

SOURCE=.\Src\dorgbr.c
# End Source File
# Begin Source File

SOURCE=.\Src\dorghr.c
# End Source File
# Begin Source File

SOURCE=.\Src\dorgl2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dorglq.c
# End Source File
# Begin Source File

SOURCE=.\Src\dorgql.c
# End Source File
# Begin Source File

SOURCE=.\Src\dorgqr.c
# End Source File
# Begin Source File

SOURCE=.\Src\dorgr2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dorgrq.c
# End Source File
# Begin Source File

SOURCE=.\Src\dorgtr.c
# End Source File
# Begin Source File

SOURCE=.\Src\dorm2l.c
# End Source File
# Begin Source File

SOURCE=.\Src\dorm2r.c
# End Source File
# Begin Source File

SOURCE=.\Src\dormbr.c
# End Source File
# Begin Source File

SOURCE=.\Src\dormhr.c
# End Source File
# Begin Source File

SOURCE=.\Src\dorml2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dormlq.c
# End Source File
# Begin Source File

SOURCE=.\Src\dormql.c
# End Source File
# Begin Source File

SOURCE=.\Src\dormqr.c
# End Source File
# Begin Source File

SOURCE=.\Src\dormr2.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dormr3.c
# End Source File
# Begin Source File

SOURCE=.\Src\dormrq.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dormrz.c
# End Source File
# Begin Source File

SOURCE=.\Src\dormtr.c
# End Source File
# Begin Source File

SOURCE=.\Src\dpbcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\dpbequ.c
# End Source File
# Begin Source File

SOURCE=.\Src\dpbrfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\dpbstf.c
# End Source File
# Begin Source File

SOURCE=.\Src\dpbsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\dpbsvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\dpbtf2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dpbtrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\dpbtrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\dpocon.c
# End Source File
# Begin Source File

SOURCE=.\Src\dpoequ.c
# End Source File
# Begin Source File

SOURCE=.\Src\dporfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\dposv.c
# End Source File
# Begin Source File

SOURCE=.\Src\dposvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\dpotf2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dpotrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\dpotri.c
# End Source File
# Begin Source File

SOURCE=.\Src\dpotrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\dppcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\dppequ.c
# End Source File
# Begin Source File

SOURCE=.\Src\dpprfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\dppsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\dppsvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\dpptrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\dpptri.c
# End Source File
# Begin Source File

SOURCE=.\Src\dpptrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\dptcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\dpteqr.c
# End Source File
# Begin Source File

SOURCE=.\Src\dptrfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\dptsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\dptsvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\dpttrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\dpttrs.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dptts2.c
# End Source File
# Begin Source File

SOURCE=.\Src\drscl.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsbev.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsbevd.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsbevx.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsbgst.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsbgv.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dsbgvd.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dsbgvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsbtrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsecnd.c
# End Source File
# Begin Source File

SOURCE=.\Src\dspcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\dspev.c
# End Source File
# Begin Source File

SOURCE=.\Src\dspevd.c
# End Source File
# Begin Source File

SOURCE=.\Src\dspevx.c
# End Source File
# Begin Source File

SOURCE=.\Src\dspgst.c
# End Source File
# Begin Source File

SOURCE=.\Src\dspgv.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dspgvd.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dspgvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsprfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\dspsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\dspsvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsptrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsptrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsptri.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsptrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\dstebz.c
# End Source File
# Begin Source File

SOURCE=.\Src\dstedc.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dstegr.c
# End Source File
# Begin Source File

SOURCE=.\Src\dstein.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsteqr.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsterf.c
# End Source File
# Begin Source File

SOURCE=.\Src\dstev.c
# End Source File
# Begin Source File

SOURCE=.\Src\dstevd.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dstevr.c
# End Source File
# Begin Source File

SOURCE=.\Src\dstevx.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsycon.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsyev.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsyevd.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dsyevr.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsyevx.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsygs2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsygst.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsygv.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dsygvd.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dsygvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsyrfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsysv.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsysvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsytd2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsytf2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsytrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsytrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsytri.c
# End Source File
# Begin Source File

SOURCE=.\Src\dsytrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\dtbcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\dtbrfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\dtbtrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\dtgevc.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dtgex2.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dtgexc.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dtgsen.c
# End Source File
# Begin Source File

SOURCE=.\Src\dtgsja.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dtgsna.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dtgsy2.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dtgsyl.c
# End Source File
# Begin Source File

SOURCE=.\Src\dtpcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\dtprfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\dtptri.c
# End Source File
# Begin Source File

SOURCE=.\Src\dtptrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\dtrcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\dtrevc.c
# End Source File
# Begin Source File

SOURCE=.\Src\dtrexc.c
# End Source File
# Begin Source File

SOURCE=.\Src\dtrrfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\dtrsen.c
# End Source File
# Begin Source File

SOURCE=.\Src\dtrsna.c
# End Source File
# Begin Source File

SOURCE=.\Src\dtrsyl.c
# End Source File
# Begin Source File

SOURCE=.\Src\dtrti2.c
# End Source File
# Begin Source File

SOURCE=.\Src\dtrtri.c
# End Source File
# Begin Source File

SOURCE=.\Src\dtrtrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\dtzrqf.c
# End Source File
# Begin Source File

SOURCE=.\SRC\dtzrzf.c
# End Source File
# Begin Source File

SOURCE=.\Src\dzsum1.c
# End Source File
# Begin Source File

SOURCE=.\Src\icmax1.c
# End Source File
# Begin Source File

SOURCE=.\SRC\ieeeck.c
# End Source File
# Begin Source File

SOURCE=.\Src\ilaenv.c
# End Source File
# Begin Source File

SOURCE=.\Src\izmax1.c
# End Source File
# Begin Source File

SOURCE=.\Src\lsame.c
# End Source File
# Begin Source File

SOURCE=.\Src\lsamen.c
# End Source File
# Begin Source File

SOURCE=.\SRC\sbdsdc.c
# End Source File
# Begin Source File

SOURCE=.\Src\sbdsqr.c
# End Source File
# Begin Source File

SOURCE=.\Src\scsum1.c
# End Source File
# Begin Source File

SOURCE=.\Src\sdisna.c
# End Source File
# Begin Source File

SOURCE=.\Src\second.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgbbrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgbcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgbequ.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgbrfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgbsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgbsvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgbtf2.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgbtrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgbtrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgebak.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgebal.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgebd2.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgebrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgecon.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgeequ.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgees.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgeesx.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgeev.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgeevx.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgegs.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgegv.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgehd2.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgehrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgelq2.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgelqf.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgels.c
# End Source File
# Begin Source File

SOURCE=.\SRC\sgelsd.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgelss.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgelsx.c
# End Source File
# Begin Source File

SOURCE=.\SRC\sgelsy.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgeql2.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgeqlf.c
# End Source File
# Begin Source File

SOURCE=.\SRC\sgeqp3.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgeqpf.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgeqr2.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgeqrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgerfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgerq2.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgerqf.c
# End Source File
# Begin Source File

SOURCE=.\SRC\sgesc2.c
# End Source File
# Begin Source File

SOURCE=.\SRC\sgesdd.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgesv.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgesvd.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgesvx.c
# End Source File
# Begin Source File

SOURCE=.\SRC\sgetc2.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgetf2.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgetrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgetri.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgetrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\sggbak.c
# End Source File
# Begin Source File

SOURCE=.\Src\sggbal.c
# End Source File
# Begin Source File

SOURCE=.\SRC\sgges.c
# End Source File
# Begin Source File

SOURCE=.\SRC\sggesx.c
# End Source File
# Begin Source File

SOURCE=.\SRC\sggev.c
# End Source File
# Begin Source File

SOURCE=.\SRC\sggevx.c
# End Source File
# Begin Source File

SOURCE=.\Src\sggglm.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgghrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgglse.c
# End Source File
# Begin Source File

SOURCE=.\Src\sggqrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\sggrqf.c
# End Source File
# Begin Source File

SOURCE=.\Src\sggsvd.c
# End Source File
# Begin Source File

SOURCE=.\Src\sggsvp.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgtcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgtrfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgtsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgtsvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgttrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\sgttrs.c
# End Source File
# Begin Source File

SOURCE=.\SRC\sgtts2.c
# End Source File
# Begin Source File

SOURCE=.\Src\shgeqz.c
# End Source File
# Begin Source File

SOURCE=.\Src\shsein.c
# End Source File
# Begin Source File

SOURCE=.\Src\shseqr.c
# End Source File
# Begin Source File

SOURCE=.\Src\slabad.c
# End Source File
# Begin Source File

SOURCE=.\Src\slabrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\slacon.c
# End Source File
# Begin Source File

SOURCE=.\Src\slacpy.c
# End Source File
# Begin Source File

SOURCE=.\Src\sladiv.c
# End Source File
# Begin Source File

SOURCE=.\Src\slae2.c
# End Source File
# Begin Source File

SOURCE=.\Src\slaebz.c
# End Source File
# Begin Source File

SOURCE=.\Src\slaed0.c
# End Source File
# Begin Source File

SOURCE=.\Src\slaed1.c
# End Source File
# Begin Source File

SOURCE=.\Src\slaed2.c
# End Source File
# Begin Source File

SOURCE=.\Src\slaed3.c
# End Source File
# Begin Source File

SOURCE=.\Src\slaed4.c
# End Source File
# Begin Source File

SOURCE=.\Src\slaed5.c
# End Source File
# Begin Source File

SOURCE=.\Src\slaed6.c
# End Source File
# Begin Source File

SOURCE=.\Src\slaed7.c
# End Source File
# Begin Source File

SOURCE=.\Src\slaed8.c
# End Source File
# Begin Source File

SOURCE=.\Src\slaed9.c
# End Source File
# Begin Source File

SOURCE=.\Src\slaeda.c
# End Source File
# Begin Source File

SOURCE=.\Src\slaein.c
# End Source File
# Begin Source File

SOURCE=.\Src\slaev2.c
# End Source File
# Begin Source File

SOURCE=.\Src\slaexc.c
# End Source File
# Begin Source File

SOURCE=.\Src\slag2.c
# End Source File
# Begin Source File

SOURCE=.\Src\slags2.c
# End Source File
# Begin Source File

SOURCE=.\Src\slagtf.c
# End Source File
# Begin Source File

SOURCE=.\Src\slagtm.c
# End Source File
# Begin Source File

SOURCE=.\Src\slagts.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slagv2.c
# End Source File
# Begin Source File

SOURCE=.\Src\slahqr.c
# End Source File
# Begin Source File

SOURCE=.\Src\slahrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\slaic1.c
# End Source File
# Begin Source File

SOURCE=.\Src\slaln2.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slals0.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slalsa.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slalsd.c
# End Source File
# Begin Source File

SOURCE=.\Src\slamch.c
# End Source File
# Begin Source File

SOURCE=.\Src\slamrg.c
# End Source File
# Begin Source File

SOURCE=.\Src\slangb.c
# End Source File
# Begin Source File

SOURCE=.\Src\slange.c
# End Source File
# Begin Source File

SOURCE=.\Src\slangt.c
# End Source File
# Begin Source File

SOURCE=.\Src\slanhs.c
# End Source File
# Begin Source File

SOURCE=.\Src\slansb.c
# End Source File
# Begin Source File

SOURCE=.\Src\slansp.c
# End Source File
# Begin Source File

SOURCE=.\Src\slanst.c
# End Source File
# Begin Source File

SOURCE=.\Src\slansy.c
# End Source File
# Begin Source File

SOURCE=.\Src\slantb.c
# End Source File
# Begin Source File

SOURCE=.\Src\slantp.c
# End Source File
# Begin Source File

SOURCE=.\Src\slantr.c
# End Source File
# Begin Source File

SOURCE=.\Src\slanv2.c
# End Source File
# Begin Source File

SOURCE=.\Src\slapll.c
# End Source File
# Begin Source File

SOURCE=.\Src\slapmt.c
# End Source File
# Begin Source File

SOURCE=.\Src\slapy2.c
# End Source File
# Begin Source File

SOURCE=.\Src\slapy3.c
# End Source File
# Begin Source File

SOURCE=.\Src\slaqgb.c
# End Source File
# Begin Source File

SOURCE=.\Src\slaqge.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slaqp2.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slaqps.c
# End Source File
# Begin Source File

SOURCE=.\Src\slaqsb.c
# End Source File
# Begin Source File

SOURCE=.\Src\slaqsp.c
# End Source File
# Begin Source File

SOURCE=.\Src\slaqsy.c
# End Source File
# Begin Source File

SOURCE=.\Src\slaqtr.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slar1v.c
# End Source File
# Begin Source File

SOURCE=.\Src\slar2v.c
# End Source File
# Begin Source File

SOURCE=.\Src\slarf.c
# End Source File
# Begin Source File

SOURCE=.\Src\slarfb.c
# End Source File
# Begin Source File

SOURCE=.\Src\slarfg.c
# End Source File
# Begin Source File

SOURCE=.\Src\slarft.c
# End Source File
# Begin Source File

SOURCE=.\Src\slarfx.c
# End Source File
# Begin Source File

SOURCE=.\Src\slargv.c
# End Source File
# Begin Source File

SOURCE=.\Src\slarnv.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slarrb.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slarre.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slarrf.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slarrv.c
# End Source File
# Begin Source File

SOURCE=.\Src\slartg.c
# End Source File
# Begin Source File

SOURCE=.\Src\slartv.c
# End Source File
# Begin Source File

SOURCE=.\Src\slaruv.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slarz.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slarzb.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slarzt.c
# End Source File
# Begin Source File

SOURCE=.\Src\slas2.c
# End Source File
# Begin Source File

SOURCE=.\Src\slascl.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slasd0.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slasd1.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slasd2.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slasd3.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slasd4.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slasd5.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slasd6.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slasd7.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slasd8.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slasd9.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slasda.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slasdq.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slasdt.c
# End Source File
# Begin Source File

SOURCE=.\Src\slaset.c
# End Source File
# Begin Source File

SOURCE=.\Src\slasq1.c
# End Source File
# Begin Source File

SOURCE=.\Src\slasq2.c
# End Source File
# Begin Source File

SOURCE=.\Src\slasq3.c
# End Source File
# Begin Source File

SOURCE=.\Src\slasq4.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slasq5.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slasq6.c
# End Source File
# Begin Source File

SOURCE=.\Src\slasr.c
# End Source File
# Begin Source File

SOURCE=.\Src\slasrt.c
# End Source File
# Begin Source File

SOURCE=.\Src\slassq.c
# End Source File
# Begin Source File

SOURCE=.\Src\slasv2.c
# End Source File
# Begin Source File

SOURCE=.\Src\slaswp.c
# End Source File
# Begin Source File

SOURCE=.\Src\slasy2.c
# End Source File
# Begin Source File

SOURCE=.\Src\slasyf.c
# End Source File
# Begin Source File

SOURCE=.\Src\slatbs.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slatdf.c
# End Source File
# Begin Source File

SOURCE=.\Src\slatps.c
# End Source File
# Begin Source File

SOURCE=.\Src\slatrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\slatrs.c
# End Source File
# Begin Source File

SOURCE=.\SRC\slatrz.c
# End Source File
# Begin Source File

SOURCE=.\Src\slatzm.c
# End Source File
# Begin Source File

SOURCE=.\Src\slauu2.c
# End Source File
# Begin Source File

SOURCE=.\Src\slauum.c
# End Source File
# Begin Source File

SOURCE=.\Src\sopgtr.c
# End Source File
# Begin Source File

SOURCE=.\Src\sopmtr.c
# End Source File
# Begin Source File

SOURCE=.\Src\sorg2l.c
# End Source File
# Begin Source File

SOURCE=.\Src\sorg2r.c
# End Source File
# Begin Source File

SOURCE=.\Src\sorgbr.c
# End Source File
# Begin Source File

SOURCE=.\Src\sorghr.c
# End Source File
# Begin Source File

SOURCE=.\Src\sorgl2.c
# End Source File
# Begin Source File

SOURCE=.\Src\sorglq.c
# End Source File
# Begin Source File

SOURCE=.\Src\sorgql.c
# End Source File
# Begin Source File

SOURCE=.\Src\sorgqr.c
# End Source File
# Begin Source File

SOURCE=.\Src\sorgr2.c
# End Source File
# Begin Source File

SOURCE=.\Src\sorgrq.c
# End Source File
# Begin Source File

SOURCE=.\Src\sorgtr.c
# End Source File
# Begin Source File

SOURCE=.\Src\sorm2l.c
# End Source File
# Begin Source File

SOURCE=.\Src\sorm2r.c
# End Source File
# Begin Source File

SOURCE=.\Src\sormbr.c
# End Source File
# Begin Source File

SOURCE=.\Src\sormhr.c
# End Source File
# Begin Source File

SOURCE=.\Src\sorml2.c
# End Source File
# Begin Source File

SOURCE=.\Src\sormlq.c
# End Source File
# Begin Source File

SOURCE=.\Src\sormql.c
# End Source File
# Begin Source File

SOURCE=.\Src\sormqr.c
# End Source File
# Begin Source File

SOURCE=.\Src\sormr2.c
# End Source File
# Begin Source File

SOURCE=.\SRC\sormr3.c
# End Source File
# Begin Source File

SOURCE=.\Src\sormrq.c
# End Source File
# Begin Source File

SOURCE=.\SRC\sormrz.c
# End Source File
# Begin Source File

SOURCE=.\Src\sormtr.c
# End Source File
# Begin Source File

SOURCE=.\Src\spbcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\spbequ.c
# End Source File
# Begin Source File

SOURCE=.\Src\spbrfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\spbstf.c
# End Source File
# Begin Source File

SOURCE=.\Src\spbsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\spbsvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\spbtf2.c
# End Source File
# Begin Source File

SOURCE=.\Src\spbtrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\spbtrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\spocon.c
# End Source File
# Begin Source File

SOURCE=.\Src\spoequ.c
# End Source File
# Begin Source File

SOURCE=.\Src\sporfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\sposv.c
# End Source File
# Begin Source File

SOURCE=.\Src\sposvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\spotf2.c
# End Source File
# Begin Source File

SOURCE=.\Src\spotrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\spotri.c
# End Source File
# Begin Source File

SOURCE=.\Src\spotrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\sppcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\sppequ.c
# End Source File
# Begin Source File

SOURCE=.\Src\spprfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\sppsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\sppsvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\spptrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\spptri.c
# End Source File
# Begin Source File

SOURCE=.\Src\spptrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\sptcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\spteqr.c
# End Source File
# Begin Source File

SOURCE=.\Src\sptrfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\sptsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\sptsvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\spttrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\spttrs.c
# End Source File
# Begin Source File

SOURCE=.\SRC\sptts2.c
# End Source File
# Begin Source File

SOURCE=.\Src\srscl.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssbev.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssbevd.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssbevx.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssbgst.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssbgv.c
# End Source File
# Begin Source File

SOURCE=.\SRC\ssbgvd.c
# End Source File
# Begin Source File

SOURCE=.\SRC\ssbgvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssbtrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\sspcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\sspev.c
# End Source File
# Begin Source File

SOURCE=.\Src\sspevd.c
# End Source File
# Begin Source File

SOURCE=.\Src\sspevx.c
# End Source File
# Begin Source File

SOURCE=.\Src\sspgst.c
# End Source File
# Begin Source File

SOURCE=.\Src\sspgv.c
# End Source File
# Begin Source File

SOURCE=.\SRC\sspgvd.c
# End Source File
# Begin Source File

SOURCE=.\SRC\sspgvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssprfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\sspsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\sspsvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssptrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssptrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssptri.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssptrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\sstebz.c
# End Source File
# Begin Source File

SOURCE=.\Src\sstedc.c
# End Source File
# Begin Source File

SOURCE=.\SRC\sstegr.c
# End Source File
# Begin Source File

SOURCE=.\Src\sstein.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssteqr.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssterf.c
# End Source File
# Begin Source File

SOURCE=.\Src\sstev.c
# End Source File
# Begin Source File

SOURCE=.\Src\sstevd.c
# End Source File
# Begin Source File

SOURCE=.\SRC\sstevr.c
# End Source File
# Begin Source File

SOURCE=.\Src\sstevx.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssycon.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssyev.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssyevd.c
# End Source File
# Begin Source File

SOURCE=.\SRC\ssyevr.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssyevx.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssygs2.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssygst.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssygv.c
# End Source File
# Begin Source File

SOURCE=.\SRC\ssygvd.c
# End Source File
# Begin Source File

SOURCE=.\SRC\ssygvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssyrfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssysv.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssysvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssytd2.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssytf2.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssytrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssytrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssytri.c
# End Source File
# Begin Source File

SOURCE=.\Src\ssytrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\stbcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\stbrfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\stbtrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\stgevc.c
# End Source File
# Begin Source File

SOURCE=.\SRC\stgex2.c
# End Source File
# Begin Source File

SOURCE=.\SRC\stgexc.c
# End Source File
# Begin Source File

SOURCE=.\SRC\stgsen.c
# End Source File
# Begin Source File

SOURCE=.\Src\stgsja.c
# End Source File
# Begin Source File

SOURCE=.\SRC\stgsna.c
# End Source File
# Begin Source File

SOURCE=.\SRC\stgsy2.c
# End Source File
# Begin Source File

SOURCE=.\SRC\stgsyl.c
# End Source File
# Begin Source File

SOURCE=.\Src\stpcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\stprfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\stptri.c
# End Source File
# Begin Source File

SOURCE=.\Src\stptrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\strcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\strevc.c
# End Source File
# Begin Source File

SOURCE=.\Src\strexc.c
# End Source File
# Begin Source File

SOURCE=.\Src\strrfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\strsen.c
# End Source File
# Begin Source File

SOURCE=.\Src\strsna.c
# End Source File
# Begin Source File

SOURCE=.\Src\strsyl.c
# End Source File
# Begin Source File

SOURCE=.\Src\strti2.c
# End Source File
# Begin Source File

SOURCE=.\Src\strtri.c
# End Source File
# Begin Source File

SOURCE=.\Src\strtrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\stzrqf.c
# End Source File
# Begin Source File

SOURCE=.\SRC\stzrzf.c
# End Source File
# Begin Source File

SOURCE=.\Src\xerbla.c
# End Source File
# Begin Source File

SOURCE=.\Src\zbdsqr.c
# End Source File
# Begin Source File

SOURCE=.\Src\zdrot.c
# End Source File
# Begin Source File

SOURCE=.\Src\zdrscl.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgbbrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgbcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgbequ.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgbrfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgbsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgbsvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgbtf2.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgbtrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgbtrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgebak.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgebal.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgebd2.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgebrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgecon.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgeequ.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgees.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgeesx.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgeev.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgeevx.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgegs.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgegv.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgehd2.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgehrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgelq2.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgelqf.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgels.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zgelsd.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgelss.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgelsx.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zgelsy.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgeql2.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgeqlf.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zgeqp3.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgeqpf.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgeqr2.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgeqrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgerfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgerq2.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgerqf.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zgesc2.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zgesdd.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgesv.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgesvd.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgesvx.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zgetc2.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgetf2.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgetrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgetri.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgetrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\zggbak.c
# End Source File
# Begin Source File

SOURCE=.\Src\zggbal.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zgges.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zggesx.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zggev.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zggevx.c
# End Source File
# Begin Source File

SOURCE=.\Src\zggglm.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgghrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgglse.c
# End Source File
# Begin Source File

SOURCE=.\Src\zggqrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\zggrqf.c
# End Source File
# Begin Source File

SOURCE=.\Src\zggsvd.c
# End Source File
# Begin Source File

SOURCE=.\Src\zggsvp.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgtcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgtrfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgtsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgtsvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgttrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\zgttrs.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zgtts2.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhbev.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhbevd.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhbevx.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhbgst.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhbgv.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zhbgvd.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zhbgvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhbtrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhecon.c
# End Source File
# Begin Source File

SOURCE=.\Src\zheev.c
# End Source File
# Begin Source File

SOURCE=.\Src\zheevd.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zheevr.c
# End Source File
# Begin Source File

SOURCE=.\Src\zheevx.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhegs2.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhegst.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhegv.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zhegvd.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zhegvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\zherfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhesv.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhesvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhetd2.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhetf2.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhetrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhetrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhetri.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhetrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhgeqz.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhpcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhpev.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhpevd.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhpevx.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhpgst.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhpgv.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zhpgvd.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zhpgvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhprfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhpsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhpsvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhptrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhptrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhptri.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhptrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhsein.c
# End Source File
# Begin Source File

SOURCE=.\Src\zhseqr.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlabrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlacgv.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlacon.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zlacp2.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlacpy.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlacrm.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlacrt.c
# End Source File
# Begin Source File

SOURCE=.\Src\zladiv.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlaed0.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlaed7.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlaed8.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlaein.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlaesy.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlaev2.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlags2.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlagtm.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlahef.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlahqr.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlahrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlaic1.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zlals0.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zlalsa.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zlalsd.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlangb.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlange.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlangt.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlanhb.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlanhe.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlanhp.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlanhs.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlanht.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlansb.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlansp.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlansy.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlantb.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlantp.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlantr.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlapll.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlapmt.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlaqgb.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlaqge.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlaqhb.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlaqhe.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlaqhp.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zlaqp2.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zlaqps.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlaqsb.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlaqsp.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlaqsy.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zlar1v.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlar2v.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zlarcm.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlarf.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlarfb.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlarfg.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlarft.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlarfx.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlargv.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlarnv.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zlarrv.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlartg.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlartv.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zlarz.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zlarzb.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zlarzt.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlascl.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlaset.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlasr.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlassq.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlaswp.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlasyf.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlatbs.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zlatdf.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlatps.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlatrd.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlatrs.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zlatrz.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlatzm.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlauu2.c
# End Source File
# Begin Source File

SOURCE=.\Src\zlauum.c
# End Source File
# Begin Source File

SOURCE=.\Src\zpbcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\zpbequ.c
# End Source File
# Begin Source File

SOURCE=.\Src\zpbrfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\zpbstf.c
# End Source File
# Begin Source File

SOURCE=.\Src\zpbsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\zpbsvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\zpbtf2.c
# End Source File
# Begin Source File

SOURCE=.\Src\zpbtrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\zpbtrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\zpocon.c
# End Source File
# Begin Source File

SOURCE=.\Src\zpoequ.c
# End Source File
# Begin Source File

SOURCE=.\Src\zporfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\zposv.c
# End Source File
# Begin Source File

SOURCE=.\Src\zposvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\zpotf2.c
# End Source File
# Begin Source File

SOURCE=.\Src\zpotrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\zpotri.c
# End Source File
# Begin Source File

SOURCE=.\Src\zpotrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\zppcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\zppequ.c
# End Source File
# Begin Source File

SOURCE=.\Src\zpprfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\zppsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\zppsvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\zpptrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\zpptri.c
# End Source File
# Begin Source File

SOURCE=.\Src\zpptrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\zptcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\zpteqr.c
# End Source File
# Begin Source File

SOURCE=.\Src\zptrfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\zptsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\zptsvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\zpttrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\zpttrs.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zptts2.c
# End Source File
# Begin Source File

SOURCE=.\Src\zrot.c
# End Source File
# Begin Source File

SOURCE=.\Src\zspcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\zspmv.c
# End Source File
# Begin Source File

SOURCE=.\Src\zspr.c
# End Source File
# Begin Source File

SOURCE=.\Src\zsprfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\zspsv.c
# End Source File
# Begin Source File

SOURCE=.\Src\zspsvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\zsptrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\zsptri.c
# End Source File
# Begin Source File

SOURCE=.\Src\zsptrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\zstedc.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zstegr.c
# End Source File
# Begin Source File

SOURCE=.\Src\zstein.c
# End Source File
# Begin Source File

SOURCE=.\Src\zsteqr.c
# End Source File
# Begin Source File

SOURCE=.\Src\zsycon.c
# End Source File
# Begin Source File

SOURCE=.\Src\zsymv.c
# End Source File
# Begin Source File

SOURCE=.\Src\zsyr.c
# End Source File
# Begin Source File

SOURCE=.\Src\zsyrfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\zsysv.c
# End Source File
# Begin Source File

SOURCE=.\Src\zsysvx.c
# End Source File
# Begin Source File

SOURCE=.\Src\zsytf2.c
# End Source File
# Begin Source File

SOURCE=.\Src\zsytrf.c
# End Source File
# Begin Source File

SOURCE=.\Src\zsytri.c
# End Source File
# Begin Source File

SOURCE=.\Src\zsytrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\ztbcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\ztbrfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\ztbtrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\ztgevc.c
# End Source File
# Begin Source File

SOURCE=.\SRC\ztgex2.c
# End Source File
# Begin Source File

SOURCE=.\SRC\ztgexc.c
# End Source File
# Begin Source File

SOURCE=.\SRC\ztgsen.c
# End Source File
# Begin Source File

SOURCE=.\Src\ztgsja.c
# End Source File
# Begin Source File

SOURCE=.\SRC\ztgsna.c
# End Source File
# Begin Source File

SOURCE=.\SRC\ztgsy2.c
# End Source File
# Begin Source File

SOURCE=.\SRC\ztgsyl.c
# End Source File
# Begin Source File

SOURCE=.\Src\ztpcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\ztprfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\ztptri.c
# End Source File
# Begin Source File

SOURCE=.\Src\ztptrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\ztrcon.c
# End Source File
# Begin Source File

SOURCE=.\Src\ztrevc.c
# End Source File
# Begin Source File

SOURCE=.\Src\ztrexc.c
# End Source File
# Begin Source File

SOURCE=.\Src\ztrrfs.c
# End Source File
# Begin Source File

SOURCE=.\Src\ztrsen.c
# End Source File
# Begin Source File

SOURCE=.\Src\ztrsna.c
# End Source File
# Begin Source File

SOURCE=.\Src\ztrsyl.c
# End Source File
# Begin Source File

SOURCE=.\Src\ztrti2.c
# End Source File
# Begin Source File

SOURCE=.\Src\ztrtri.c
# End Source File
# Begin Source File

SOURCE=.\Src\ztrtrs.c
# End Source File
# Begin Source File

SOURCE=.\Src\ztzrqf.c
# End Source File
# Begin Source File

SOURCE=.\SRC\ztzrzf.c
# End Source File
# Begin Source File

SOURCE=.\Src\zung2l.c
# End Source File
# Begin Source File

SOURCE=.\Src\zung2r.c
# End Source File
# Begin Source File

SOURCE=.\Src\zungbr.c
# End Source File
# Begin Source File

SOURCE=.\Src\zunghr.c
# End Source File
# Begin Source File

SOURCE=.\Src\zungl2.c
# End Source File
# Begin Source File

SOURCE=.\Src\zunglq.c
# End Source File
# Begin Source File

SOURCE=.\Src\zungql.c
# End Source File
# Begin Source File

SOURCE=.\Src\zungqr.c
# End Source File
# Begin Source File

SOURCE=.\Src\zungr2.c
# End Source File
# Begin Source File

SOURCE=.\Src\zungrq.c
# End Source File
# Begin Source File

SOURCE=.\Src\zungtr.c
# End Source File
# Begin Source File

SOURCE=.\Src\zunm2l.c
# End Source File
# Begin Source File

SOURCE=.\Src\zunm2r.c
# End Source File
# Begin Source File

SOURCE=.\Src\zunmbr.c
# End Source File
# Begin Source File

SOURCE=.\Src\zunmhr.c
# End Source File
# Begin Source File

SOURCE=.\Src\zunml2.c
# End Source File
# Begin Source File

SOURCE=.\Src\zunmlq.c
# End Source File
# Begin Source File

SOURCE=.\Src\zunmql.c
# End Source File
# Begin Source File

SOURCE=.\Src\zunmqr.c
# End Source File
# Begin Source File

SOURCE=.\Src\zunmr2.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zunmr3.c
# End Source File
# Begin Source File

SOURCE=.\Src\zunmrq.c
# End Source File
# Begin Source File

SOURCE=.\SRC\zunmrz.c
# End Source File
# Begin Source File

SOURCE=.\Src\zunmtr.c
# End Source File
# Begin Source File

SOURCE=.\Src\zupgtr.c
# End Source File
# Begin Source File

SOURCE=.\Src\zupmtr.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# End Target
# End Project
