echo off

echo Running static library examples (Debug) ...
call runallexamplesindir .\gsl_examples\Debug-StaticLib ..\doc\examples _d

echo Running static library examples (Release) ...
call runallexamplesindir .\gsl_examples\Release-StaticLib ..\doc\examples

echo Running dynamic library examples (Debug) ...
call runallexamplesindir .\gsl_examples\Debug-DLL ..\doc\examples _dll_d

echo Running dynamic library examples (Release) ...
call runallexamplesindir .\gsl_examples\Release-DLL ..\doc\examples _dll

:EXIT_BAT
echo on

