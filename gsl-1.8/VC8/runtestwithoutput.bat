REM Runs a program and checks the output versus expected output.
REM The comparison ignores whitespace.
REM The gnu 'diff' program is required to be on the path.
REM
REM Parameters
REM      1 Name (and path if necessary) to program to run
REM      2 Name (and path if necessary) to file containing expected output
REM    3-9 Optional parameters to pass to program
REM
if NOT "%2"=="" goto CHECK_PARAM
echo Runs a program and checks its output
echo Usage:  runtestwithoutput prog-to-run file-containing-output [optional params for prog]
goto EXIT_BAT

:CHECK_PARAM
if not exist %1 goto INVALID_EXE
if not exist %2 goto INVALID_OUTPUT_FILE
echo Running ... %1
%1 %3 %4 %5 %6 %7 %8 %9 > temp_file.out
diff -w %2 temp_file.out
if ERRORLEVEL 1 goto RUN_ERROR
goto EXIT_BAT

:RUN_ERROR
echo %1 DID NOT PRODUCE THE OUTPUT IN FILE %2
goto EXIT_BAT

:INVALID_EXE
echo Error - %1 not found.
goto EXIT_BAT

:INVALID_OUTPUT_FILE
echo Error - %2 not found.
goto EXIT_BAT

:EXIT_BAT
