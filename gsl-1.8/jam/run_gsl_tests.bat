echo off

if not "%1"=="" goto RUN_TESTS
echo Usage:  test_gsl path
echo         path = rel or abs path to test executables
goto EXIT_BAT

:RUN_TESTS

echo Running static library tests in %1...

if exist %1\test_block.exe call runtest %1\test_block.exe
if exist %1\test_cblas.exe call runtest %1\test_cblas.exe
if exist %1\test_cdf.exe call runtest %1\test_cdf.exe
if exist %1\test_cheb.exe call runtest %1\test_cheb.exe
if exist %1\test_combination.exe call runtest %1\test_combination.exe
if exist %1\test_complex.exe call runtest %1\test_complex.exe
if exist %1\test_const.exe call runtest %1\test_const.exe
if exist %1\test_deriv.exe call runtest %1\test_deriv.exe
if exist %1\test_dht.exe call runtest %1\test_dht.exe
if exist %1\test_diff.exe call runtest %1\test_diff.exe
if exist %1\test_eigen.exe call runtest %1\test_eigen.exe
if exist %1\test_fft.exe call runtest %1\test_fft.exe
if exist %1\test_fit.exe call runtest %1\test_fit.exe
if exist %1\test_histogram.exe call runtest %1\test_histogram.exe
if exist %1\test_ieee-utils.exe call runtest %1\test_ieee-utils.exe
if exist %1\test_integration.exe call runtest %1\test_integration.exe
if exist %1\test_interpolation.exe call runtest %1\test_interpolation.exe
if exist %1\test_linalg.exe call runtest %1\test_linalg.exe
if exist %1\test_matrix.exe call runtest %1\test_matrix.exe
if exist %1\test_min.exe call runtest %1\test_min.exe
if exist %1\test_monte.exe call runtest %1\test_monte.exe
if exist %1\test_multifit.exe call runtest %1\test_multifit.exe
if exist %1\test_multimin.exe call runtest %1\test_multimin.exe
if exist %1\test_multiroots.exe call runtest %1\test_multiroots.exe
if exist %1\test_ntuple.exe call runtest %1\test_ntuple.exe
if exist %1\test_ode-initval.exe call runtest %1\test_ode-initval.exe
if exist %1\test_permutation.exe call runtest %1\test_permutation.exe
if exist %1\test_poly.exe call runtest %1\test_poly.exe
if exist %1\test_qrng.exe call runtest %1\test_qrng.exe
if exist %1\test_randist.exe call runtest %1\test_randist.exe
if exist %1\test_rng.exe call runtest %1\test_rng.exe
if exist %1\test_roots.exe call runtest %1\test_roots.exe
if exist %1\test_siman.exe call runtest %1\test_siman.exe
if exist %1\test_sort.exe call runtest %1\test_sort.exe
if exist %1\test_specfunc.exe call runtest %1\test_specfunc.exe
if exist %1\test_statistics.exe call runtest %1\test_statistics.exe
if exist %1\test_sum.exe call runtest %1\test_sum.exe
if exist %1\test_sys.exe call runtest %1\test_sys.exe
if exist %1\test_vector.exe call runtest %1\test_vector.exe
if exist %1\test_wavelet.exe call runtest %1\test_wavelet.exe

echo Running dynamic library tests in %1...

if exist %1\test_block_dll.exe call runtest %1\test_block_dll.exe
if exist %1\test_cblas_dll.exe call runtest %1\test_cblas_dll.exe
if exist %1\test_cdf_dll.exe call runtest %1\test_cdf_dll.exe
if exist %1\test_cheb_dll.exe call runtest %1\test_cheb_dll.exe
if exist %1\test_combination_dll.exe call runtest %1\test_combination_dll.exe
if exist %1\test_complex_dll.exe call runtest %1\test_complex_dll.exe
if exist %1\test_const_dll.exe call runtest %1\test_const_dll.exe
if exist %1\test_deriv_dll.exe call runtest %1\test_deriv_dll.exe
if exist %1\test_dht_dll.exe call runtest %1\test_dht_dll.exe
if exist %1\test_diff_dll.exe call runtest %1\test_diff_dll.exe
if exist %1\test_eigen_dll.exe call runtest %1\test_eigen_dll.exe
if exist %1\test_fft_dll.exe call runtest %1\test_fft_dll.exe
if exist %1\test_fit_dll.exe call runtest %1\test_fit_dll.exe
if exist %1\test_histogram_dll.exe call runtest %1\test_histogram_dll.exe
if exist %1\test_ieee-utils_dll.exe call runtest %1\test_ieee-utils_dll.exe
if exist %1\test_integration_dll.exe call runtest %1\test_integration_dll.exe
if exist %1\test_interpolation_dll.exe call runtest %1\test_interpolation_dll.exe
if exist %1\test_linalg_dll.exe call runtest %1\test_linalg_dll.exe
if exist %1\test_matrix_dll.exe call runtest %1\test_matrix_dll.exe
if exist %1\test_min_dll.exe call runtest %1\test_min_dll.exe
if exist %1\test_monte_dll.exe call runtest %1\test_monte_dll.exe
if exist %1\test_multifit_dll.exe call runtest %1\test_multifit_dll.exe
if exist %1\test_multimin_dll.exe call runtest %1\test_multimin_dll.exe
if exist %1\test_multiroots_dll.exe call runtest %1\test_multiroots_dll.exe
if exist %1\test_ntuple_dll.exe call runtest %1\test_ntuple_dll.exe
if exist %1\test_ode-initval_dll.exe call runtest %1\test_ode-initval_dll.exe
if exist %1\test_permutation_dll.exe call runtest %1\test_permutation_dll.exe
if exist %1\test_poly_dll.exe call runtest %1\test_poly_dll.exe
if exist %1\test_qrng_dll.exe call runtest %1\test_qrng_dll.exe
if exist %1\test_randist_dll.exe call runtest %1\test_randist_dll.exe
if exist %1\test_rng_dll.exe call runtest %1\test_rng_dll.exe
if exist %1\test_roots_dll.exe call runtest %1\test_roots_dll.exe
if exist %1\test_siman_dll.exe call runtest %1\test_siman_dll.exe
if exist %1\test_sort_dll.exe call runtest %1\test_sort_dll.exe
if exist %1\test_specfunc_dll.exe call runtest %1\test_specfunc_dll.exe
if exist %1\test_statistics_dll.exe call runtest %1\test_statistics_dll.exe
if exist %1\test_sum_dll.exe call runtest %1\test_sum_dll.exe 
if exist %1\test_sys_dll.exe call runtest %1\test_sys_dll.exe
if exist %1\test_vector_dll.exe call runtest %1\test_vector_dll.exe
if exist %1\test_wavelet_dll.exe call runtest %1\test_wavelet_dll.exe

:EXIT_BAT
echo on

