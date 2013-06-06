if "%1"=="" goto NO_PARAM
if not exist %1 goto INVALID_EXE
echo Running ... %1
%1
if ERRORLEVEL 0 goto EXIT_BAT
echo Test %1 had errors.
goto EXIT_BAT

:INVALID_EXE
echo Error - %1 not found.
goto EXIT_BAT

:NO_PARAM
:EXIT_BAT
