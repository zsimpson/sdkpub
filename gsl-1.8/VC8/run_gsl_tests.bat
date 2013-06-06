echo off

if "%1"=="dll" goto TEST_DYNAMIC

echo Testing static library (Debug).
call runalltestsindir .\test_gsl\Debug-StaticLib _d

echo Testing static library (Release).
call runalltestsindir .\test_gsl\Release-StaticLib


:TEST_DYNAMIC

echo Testing dynamic library (Debug).
if not exist .\test_gsl\Debug-DLL\libgsl_d.dll goto NO_LIBGSL_D
if not exist .\test_gsl\Debug-DLL\libgslcblas_d.dll goto NO_LIBGSLCBLAS_D
call runalltestsindir .\test_gsl\Debug-DLL _dll_d
goto TEST_DYNAMIC_RELEASE

:NO_LIBGSL_D
echo Dynamic library tests (Debug) could not be run - no libgsl_d.dll
goto TEST_DYNAMIC_RELEASE

:NO_LIBGSLCBLAS_D
echo Dynamic library tests (Debug) could not be run - no libgslcblas_d.dll
goto TEST_DYNAMIC_RELEASE


:TEST_DYNAMIC_RELEASE
echo Testing dynamic library (Release).
if not exist .\test_gsl\Release-DLL\libgsl.dll goto NO_LIBGSL
if not exist .\test_gsl\Release-DLL\libgslcblas.dll goto NO_LIBGSLCBLAS
call runalltestsindir .\test_gsl\Release-DLL _dll
goto EXIT_BAT

:NO_LIBGSL
echo Dynamic library tests (Release) could not be run - no libgsl.dll
goto EXIT_BAT

:NO_LIBGSLCBLAS
echo Dynamic library tests (Release) could not be run - no libgslcblas.dll
goto EXIT_BAT

:EXIT_BAT
echo on

