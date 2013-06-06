REM Runs all gsl test programs in a given directory
REM
REM Parameters:
REM    1 Path to test program executables
REM    2 Suffix appended to program names (e.g. _d or _dll or _dll_d)
REM

if "%1"=="" goto EXIT_BAT

if exist %1\test_block%2.exe call runtest %1\test_block%2.exe
if exist %1\test_cblas%2.exe call runtest %1\test_cblas%2.exe
if exist %1\test_cdf%2.exe call runtest %1\test_cdf%2.exe
if exist %1\test_cheb%2.exe call runtest %1\test_cheb%2.exe
if exist %1\test_combination%2.exe call runtest %1\test_combination%2.exe
if exist %1\test_complex%2.exe call runtest %1\test_complex%2.exe
if exist %1\test_const%2.exe call runtest %1\test_const%2.exe
if exist %1\test_deriv%2.exe call runtest %1\test_deriv%2.exe
if exist %1\test_dht%2.exe call runtest %1\test_dht%2.exe
if exist %1\test_diff%2.exe call runtest %1\test_diff%2.exe
if exist %1\test_eigen%2.exe call runtest %1\test_eigen%2.exe
if exist %1\test_err%2.exe call runtest %1\test_err%2.exe
if exist %1\test_fft%2.exe call runtest %1\test_fft%2.exe
if exist %1\test_fit%2.exe call runtest %1\test_fit%2.exe
if exist %1\test_histogram%2.exe call runtest %1\test_histogram%2.exe
if exist %1\test_ieee-utils%2.exe call runtest %1\test_ieee-utils%2.exe
if exist %1\test_integration%2.exe call runtest %1\test_integration%2.exe
if exist %1\test_interpolation%2.exe call runtest %1\test_interpolation%2.exe
if exist %1\test_linalg%2.exe call runtest %1\test_linalg%2.exe
if exist %1\test_matrix%2.exe call runtest %1\test_matrix%2.exe
if exist %1\test_min%2.exe call runtest %1\test_min%2.exe
if exist %1\test_monte%2.exe call runtest %1\test_monte%2.exe
if exist %1\test_multifit%2.exe call runtest %1\test_multifit%2.exe
if exist %1\test_multimin%2.exe call runtest %1\test_multimin%2.exe
if exist %1\test_multiroot%2.exe call runtest %1\test_multiroot%2.exe
if exist %1\test_ntuple%2.exe call runtest %1\test_ntuple%2.exe
if exist %1\test_ode-initval%2.exe call runtest %1\test_ode-initval%2.exe
if exist %1\test_permutation%2.exe call runtest %1\test_permutation%2.exe
if exist %1\test_poly%2.exe call runtest %1\test_poly%2.exe
if exist %1\test_qrng%2.exe call runtest %1\test_qrng%2.exe
if exist %1\test_randist%2.exe call runtest %1\test_randist%2.exe
if exist %1\test_rng%2.exe call runtest %1\test_rng%2.exe
if exist %1\test_roots%2.exe call runtest %1\test_roots%2.exe
if exist %1\test_siman%2.exe call runtest %1\test_siman%2.exe
if exist %1\test_sort%2.exe call runtest %1\test_sort%2.exe
if exist %1\test_specfunc%2.exe call runtest %1\test_specfunc%2.exe
if exist %1\test_statistics%2.exe call runtest %1\test_statistics%2.exe
if exist %1\test_sum%2.exe call runtest %1\test_sum%2.exe
if exist %1\test_sys%2.exe call runtest %1\test_sys%2.exe
if exist %1\test_vector%2.exe call runtest %1\test_vector%2.exe
if exist %1\test_wavelet%2.exe call runtest %1\test_wavelet%2.exe

:EXIT_BAT

