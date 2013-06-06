#  Fri 6-Dec-1998 23:33

#  builds an user defined DLL using Intel Performance Library
#  is usually called from Makefile, or may be called, for example
#     >nmake -f userdll.mak Target=P6
#  where 
#     PX=blend, 
#     P6=Pentium(R) Pro, M6=Pentium(R) Pro with MMX(TM) technology
#     A6=Pentium(R) III 

################################################################

# UserName should be defined in tools.ini. Check if tools.ini is used

!IFNDEF UserName
!ERROR UserName is not defined. Check if tools.ini exists
!ENDIF

# check if Target was defined. It may be defined the Makefile
# or you may define it in command line for nmake. 

!IF "$(Target)"==""
!ERROR Target was not defined. May be PCS, PX, P6, M6, A6 ...
!ENDIF

# combain names. They depend on the target name

# build DLL dispatcher, PCS
!IF "$(Target)"=="PCS"
TargetName=$(UserName)
Libs="$(PLDir)\$(StaticPLDir)\iplpxl.lib"
SWITCHFLAGS=-DUSER_W32PCS 

# build cpu-specific DLL, PX, P6, M6, A6 ...
!ELSE
TargetName=$(UserName)$(Target)
Libs="$(PLDir)\$(StaticPLDir)\$(PLName)$(Target)l.lib" 
SWITCHFLAGS=-DUSER_W32DLL 

!ENDIF

ObjFile="$(OutDir)\$(Target).obj"
TargetDLL="$(DllDir)\$(TargetName).dll"

COpt=/c /GB /W3 /O2 $(PLINC) 
CExtra=/D "NDEBUG" /D "WIN32" /D "_WINDOWS" -MD -DCUSTNAME="$(UserName)"

CFLAGS=$(COpt) $(CExtra) $(SWITCHFLAGS)
LFLAGS=/subsystem:windows /dll /def:explist.def /nodefaultlib

################################################################

MakeLib : Init Build

Init :
   @if not exist $(OutDir)   mkdir $(OutDir)
   @if not exist $(DllDir)   mkdir $(DllDir)

Build : $(TargetDLL)

$(TargetDLL): $(ObjFile)
   $(LINK) /nologo @<<
   $(LFLAGS)
   $(ObjFile)
   $(Libs)
   $(VCLIB)
   /out:$(TargetDLL) /IMPLIB:"$(OutDir)\$(TargetName).lib" 
   /map:"$(OutDir)\$(TargetName).map"
<<

$(ObjFile): userdll.c userdll.h explist.def tools.ini
   $(CC) /nologo $(CFLAGS) /Fo$@ userdll.c

