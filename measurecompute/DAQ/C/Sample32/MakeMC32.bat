echo off
if (%1)==() goto syntax

cl /W3 /GA /DWIN32 /c %1.c > err.log
link /LIBPATH:..\ %1 kernel32.lib user32.lib cbw32.lib >> err.log
type err.log|more
goto end

:syntax
echo -
echo -  This batch file compiles links a named .c program with the Microsoft C
echo -  compiler as a 32-bit Windows Console application.
echo -
echo - Syntax:
echo -     MakeMC32 filename
echo -

:end


