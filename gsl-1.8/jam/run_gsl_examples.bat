echo off

if not "%2"=="" goto RUN_TESTS
echo Usage:  test_gsl_examples path1 path2
echo         path1 = rel or abs path to example executables
echo         path2 = rel or abs path to example output files
goto EXIT_BAT

:RUN_TESTS

echo Running static library examples in %1...

if exist %1\ex_blas.exe call runtestwithoutput %1\ex_blas.exe %2\blas.out
if exist %1\ex_block.exe call runtestwithoutput %1\ex_block.exe %2\block.out
if exist %1\ex_cblas.exe call runtestwithoutput %1\ex_cblas.exe %2\cblas.out
if exist %1\ex_cdf.exe call runtestwithoutput %1\ex_cdf.exe %2\cdf.out
if exist %1\ex_cheb.exe call runtest %1\ex_cheb.exe
if exist %1\ex_combination.exe call runtestwithoutput %1\ex_combination.exe %2\combination.out
if exist %1\ex_const.exe call runtestwithoutput %1\ex_const.exe %2\const.out
if exist %1\ex_diff.exe call runtestwithoutput %1\ex_diff.exe %2\diff.out
if exist %1\ex_dwt.exe call runtest %1\ex_dwt.exe %2\dwt.dat
if exist %1\ex_eigen.exe call runtest %1\ex_eigen.exe
if exist %1\ex_fft.exe call runtest %1\ex_fft.exe
if exist %1\ex_fftmr.exe call runtest %1\ex_fftmr.exe
if exist %1\ex_fftreal.exe call runtest %1\ex_fftreal.exe
if exist %1\ex_fitting.exe call runtest %1\ex_fitting.exe
if exist %1\ex_fitting2.exe call runtest %1\ex_fitting2.exe
if exist %1\ex_fitting3.exe call runtest %1\ex_fitting3.exe
if exist %1\ex_histogram.exe call runtest %1\ex_histogram.exe
if exist %1\ex_histogram2d.exe call runtest %1\ex_histogram2d.exe
if exist %1\ex_ieee.exe call runtest %1\ex_ieee.exe
if exist %1\ex_ieeeround.exe call runtest %1\ex_ieeeround.exe
if exist %1\ex_integration.exe call runtestwithoutput %1\ex_integration.exe %2\integration.out
if exist %1\ex_interp.exe call runtest %1\ex_interp.exe
if exist %1\ex_interpp.exe call runtest %1\ex_interpp.exe
if exist %1\ex_intro.exe call runtestwithoutput %1\ex_intro.exe %2\intro.out
if exist %1\ex_linalglu.exe call runtestwithoutput %1\ex_linalglu.exe %2\linalglu.out
if exist %1\ex_matrix.exe call runtestwithoutput %1\ex_matrix.exe %2\matrix.out
if exist %1\ex_matrixw.exe call runtestwithoutput %1\ex_matrixw.exe %2\matrixw.out
if exist %1\ex_min.exe call runtestwithoutput %1\ex_min.exe %2\min.out
if exist %1\ex_monte.exe call runtest %1\ex_monte.exe
if exist %1\ex_nlfit.exe call runtest %1\ex_nlfit.exe
if exist %1\ex_ntupler.exe call runtest %1\ex_ntupler.exe
if exist %1\ex_ntuplew.exe call runtest %1\ex_ntuplew.exe
if exist %1\ex_ode-initval.exe call runtest %1\ex_ode-initval.exe
if exist %1\ex_odefixed.exe call runtest %1\ex_odefixed.exe
if exist %1\ex_permseq.exe call runtest %1\ex_permseq.exe
if exist %1\ex_permshuffle.exe call runtest %1\ex_permshuffle.exe
if exist %1\ex_polyroots.exe call runtestwithoutput %1\ex_polyroots.exe %2\polyroots.out
if exist %1\ex_qrng.exe call runtest %1\ex_qrng.exe
if exist %1\ex_randpoisson.exe call runtestwithoutput %1\ex_randpoisson.exe %2\randpoisson.out
if exist %1\ex_randwalk.exe call runtest %1\ex_randwalk.exe
if exist %1\ex_rng.exe call runtestwithoutput %1\ex_rng.exe %2\rng.out
if exist %1\ex_rngunif.exe call runtestwithoutput %1\ex_rngunif.exe %2\rngunif.out
if exist %1\ex_rootnewt.exe call runtest %1\ex_rootnewt.exe
if exist %1\ex_roots.exe call runtest %1\ex_roots.exe
if exist %1\ex_siman.exe call runtest %1\ex_siman.exe
if exist %1\ex_sortsmall.exe call runtestwithoutput %1\ex_sortsmall.exe %2\sortsmall.out
if exist %1\ex_specfun.exe call runtestwithoutput %1\ex_specfun.exe %2\specfun.out
if exist %1\ex_specfun_e.exe call runtestwithoutput %1\ex_specfun_e.exe %2\specfun_e.out
if exist %1\ex_stat.exe call runtestwithoutput %1\ex_stat.exe %2\stat.out
if exist %1\ex_statsort.exe call runtestwithoutput %1\ex_statsort.exe %2\statsort.out
if exist %1\ex_sum.exe call runtestwithoutput %1\ex_sum.exe %2\sum.out
if exist %1\ex_vector.exe call runtest %1\ex_vector.exe
if exist %1\ex_vectorview.exe call runtestwithoutput %1\ex_vectorview.exe %2\vectorview.out
if exist %1\ex_vectorw.exe call runtest %1\ex_vectorw.exe
if exist %1\ex_vectorr.exe call runtest %1\ex_vectorr.exe


echo Running dynamic library examples in %1...

if exist %1\ex_blas_dll.exe call runtestwithoutput %1\ex_blas_dll.exe %2\blas.out
if exist %1\ex_block_dll.exe call runtestwithoutput %1\ex_block_dll.exe %2\block.out
if exist %1\ex_cblas_dll.exe call runtestwithoutput %1\ex_cblas_dll.exe %2\cblas.out
if exist %1\ex_cdf_dll.exe call runtestwithoutput %1\ex_cdf_dll.exe %2\cdf.out
if exist %1\ex_cheb_dll.exe call runtest %1\ex_cheb_dll.exe
if exist %1\ex_combination_dll.exe call runtestwithoutput %1\ex_combination_dll.exe %2\combination.out
if exist %1\ex_const_dll.exe call runtestwithoutput %1\ex_const_dll.exe %2\const.out
if exist %1\ex_diff_dll.exe call runtestwithoutput %1\ex_diff_dll.exe %2\diff.out
if exist %1\ex_dwt_dll.exe call runtest %1\ex_dwt_dll.exe %2\dwt.dat
if exist %1\ex_eigen_dll.exe call runtest %1\ex_eigen_dll.exe
if exist %1\ex_fft_dll.exe call runtest %1\ex_fft_dll.exe
if exist %1\ex_fftmr_dll.exe call runtest %1\ex_fftmr_dll.exe
if exist %1\ex_fftreal_dll.exe call runtest %1\ex_fftreal_dll.exe
if exist %1\ex_fitting_dll.exe call runtest %1\ex_fitting_dll.exe
if exist %1\ex_fitting2_dll.exe call runtest %1\ex_fitting2_dll.exe
if exist %1\ex_fitting3_dll.exe call runtest %1\ex_fitting3_dll.exe
if exist %1\ex_histogram_dll.exe call runtest %1\ex_histogram_dll.exe
if exist %1\ex_histogram2d_dll.exe call runtest %1\ex_histogram2d_dll.exe
if exist %1\ex_ieee_dll.exe call runtest %1\ex_ieee_dll.exe
if exist %1\ex_ieeeround_dll.exe call runtest %1\ex_ieeeround_dll.exe
if exist %1\ex_integration_dll.exe call runtestwithoutput %1\ex_integration_dll.exe %2\integration.out
if exist %1\ex_interp_dll.exe call runtest %1\ex_interp_dll.exe
if exist %1\ex_interpp_dll.exe call runtest %1\ex_interpp_dll.exe
if exist %1\ex_intro_dll.exe call runtestwithoutput %1\ex_intro_dll.exe %2\intro.out
if exist %1\ex_linalglu_dll.exe call runtestwithoutput %1\ex_linalglu_dll.exe %2\linalglu.out
if exist %1\ex_matrix_dll.exe call runtestwithoutput %1\ex_matrix_dll.exe %2\matrix.out
if exist %1\ex_matrixw_dll.exe call runtestwithoutput %1\ex_matrixw_dll.exe %2\matrixw.out
if exist %1\ex_min_dll.exe call runtestwithoutput %1\ex_min_dll.exe %2\min.out
if exist %1\ex_monte_dll.exe call runtest %1\ex_monte_dll.exe
if exist %1\ex_nlfit_dll.exe call runtest %1\ex_nlfit_dll.exe
if exist %1\ex_ntupler_dll.exe call runtest %1\ex_ntupler_dll.exe
if exist %1\ex_ntuplew_dll.exe call runtest %1\ex_ntuplew_dll.exe
if exist %1\ex_ode-initval_dll.exe call runtest %1\ex_ode-initval_dll.exe
if exist %1\ex_odefixed_dll.exe call runtest %1\ex_odefixed_dll.exe
if exist %1\ex_permseq_dll.exe call runtest %1\ex_permseq_dll.exe
if exist %1\ex_permshuffle_dll.exe call runtest %1\ex_permshuffle_dll.exe
if exist %1\ex_polyroots_dll.exe call runtestwithoutput %1\ex_polyroots_dll.exe %2\polyroots.out
if exist %1\ex_qrng_dll.exe call runtest %1\ex_qrng_dll.exe
if exist %1\ex_randpoisson_dll.exe call runtestwithoutput %1\ex_randpoisson_dll.exe %2\randpoisson.out
if exist %1\ex_randwalk_dll.exe call runtest %1\ex_randwalk_dll.exe
if exist %1\ex_rng_dll.exe call runtestwithoutput %1\ex_rng_dll.exe %2\rng.out
if exist %1\ex_rngunif_dll.exe call runtestwithoutput %1\ex_rngunif_dll.exe %2\rngunif.out
if exist %1\ex_rootnewt_dll.exe call runtest %1\ex_rootnewt_dll.exe
if exist %1\ex_roots_dll.exe call runtest %1\ex_roots_dll.exe
if exist %1\ex_siman_dll.exe call runtest %1\ex_siman_dll.exe
if exist %1\ex_sortsmall_dll.exe call runtestwithoutput %1\ex_sortsmall_dll.exe %2\sortsmall.out
if exist %1\ex_specfun_dll.exe call runtestwithoutput %1\ex_specfun_dll.exe %2\specfun.out
if exist %1\ex_specfun_e_dll.exe call runtestwithoutput %1\ex_specfun_e_dll.exe %2\specfun_e.out
if exist %1\ex_stat_dll.exe call runtestwithoutput %1\ex_stat_dll.exe %2\stat.out
if exist %1\ex_statsort_dll.exe call runtestwithoutput %1\ex_statsort_dll.exe %2\statsort.out
if exist %1\ex_sum_dll.exe call runtestwithoutput %1\ex_sum_dll.exe %2\sum.out
if exist %1\ex_vector_dll.exe call runtest %1\ex_vector_dll.exe
if exist %1\ex_vectorview_dll.exe call runtestwithoutput %1\ex_vectorview_dll.exe %2\vectorview.out
if exist %1\ex_vectorw_dll.exe call runtest %1\ex_vectorw_dll.exe
if exist %1\ex_vectorr_dll.exe call runtest %1\ex_vectorr_dll.exe

:EXIT_BAT
echo on

