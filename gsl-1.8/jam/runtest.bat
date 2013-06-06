echo off
REM Run a program and report if it returned an error condition
REM
REM Parameters
REM      1 Name (and path if necessary) to program to run
REM      2 Optional filename to receive program output ("default" to send to screen)
REM    3-9 Optional parameters to program
REM
if NOT "%1"=="" goto CHECK_PARAM
echo Run a program and report if an error condition occurred.
echo Usage:  runtest program-to-run output-file [optional parameters to prog]
echo         to send output to screen, omit output-file or pass 'default' (no punctuation)
goto EXIT_BAT

:CHECK_PARAM
if not exist %1 goto INVALID_EXE
echo Running ... %1
%1 %2 %3 %4 %5 %6 %7 %8 %9
if ERRORLEVEL 1 goto RUN_ERROR
goto EXIT_BAT

:RUN_ERROR
echo %1 RETURNED AN ERROR CONDITION.
goto EXIT_BAT

:INVALID_EXE
echo Error - %1 not found.
goto EXIT_BAT

:EXIT_BAT



