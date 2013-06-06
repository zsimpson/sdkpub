echo off
if (%1)==() goto syntax

bcc32 -M -DWIN32 -lTpe -lo %1.c ..\cbw32bc.lib > err.log
type err.log | more
goto end

:syntax
echo -
echo -  This batch file compiles links a named .cpp program with the Borland C
echo -  compiler as a 32-bit Windows Console application.
echo -
echo - Syntax:
echo -     MakeBC32 filename
echo -

:end
