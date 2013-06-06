# Fri 6-Nov-1998 19:23

# The main make-file. It can be used
# "nmake"           - [builds library[, test] and] runs test
# "nmake clean"     - removes directories created 
# "nmake run"       - [builds and] executes test
# "nmake buildtest" - builds [library and] test
# "nmake buildlib"  - builds library
# "nmake hint"      - hint


################################################################################

# check if tools.ini file is used

!IFNDEF UserName
!ERROR UserName is not defined. Check if tools.ini exists
!ENDIF

TestObj="$(OutDir)\$(TestName).obj"
TestExe="$(DllDir)\$(TestName).exe"
UserLib="$(OutDir)\$(UserName).lib"

COpt=/c /GB /W3 /O2 $(PLINC) 
CExtra=/D "NDEBUG" /D "WIN32" /D "_WINDOWS" -MD

CFLAGS=$(COpt) $(CExtra)

################################################################

BuildAndTest : $(UserLib) buildtest run

$(UserLib) : buildlib

buildlib :
   nmake /nologo -f userdll.mak Target=PCS
   nmake /nologo -f userdll.mak Target=PX
   nmake /nologo -f userdll.mak Target=P6
   nmake /nologo -f userdll.mak Target=M6
   nmake /nologo -f userdll.mak Target=A6
   nmake /nologo -f userdll.mak Target=W7

# only test application, no assumptions about User DLL
buildtest : $(TestExe)

$(TestObj) : $(TestName).c 
   $(CC) /nologo $(CFLAGS) /Fo$@ $(TestName).c

$(TestExe) : $(TestObj)
   $(LINK) /nologo @<<
   $(TestObj)
   $(UserLib)
   $(VCLIB)
   /out:$(TestExe)
<<

# assumes that User DDL and test application are built
run : $(UserLib) $(TestExe)
   @cd $(DllDir)
   @$(TestName).exe

# does Win98's rd and del know /q options?
clean:
   @echo Cleaning ... 
   @if exist $(OutDir) rd /s /q $(OutDir)
   @if exist $(DllDir) rd /s /q $(DllDir)
   @if exist 0 del /q 0

hint:
   @echo Usage of this Makefile:
   @echo "nmake"           - [builds library[, test] and] runs test
   @echo "nmake clean"     - removes directories created 
   @echo "nmake run"       - [builds and] executes test
   @echo "nmake buildtest" - builds [library and] test
   @echo "nmake buildlib"  - builds library
   @echo "nmake hint"      - hint
