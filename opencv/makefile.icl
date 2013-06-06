# Master make file for Intel Compiler
!ifdef debug
OPT= debug=1
!else
OPT=
!endif

all:
	cd cv\make
	nmake /fmakefile.icl $(OPT)
	cd ..\..
	cd cvaux\make
	nmake /fmakefile.icl $(OPT)
	cd ..\..
	cd otherlibs\highgui
	nmake /fmakefile.icl $(OPT)
	cd ..\..
