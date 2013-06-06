REM  This batch file builds gsl 1.8 from source using MinGW gcc 3.4.2.
REM  It runs on Windows XP and (hopefully - not tested) previous versions.
REM  This batch script has not been heavily tested - use at your own risk.
REM
REM  A limited amount of flexibility is afforded by making the compile and
REM  archive commands variables.  This allows modifying the compiler and
REM  librarian if needed, as well as modifying the options passed to these.
REM
REM  This script was generated using a modified version of jam, then manually
REM  edited to provide better organization and the aforementioned parameterization.

REM Modify appropriately for your compiler, etc.
SET _COMPILE=gcc
SET _COMP_OUTPUT_FLAG=-o
SET _OPT_DEBUG=-c -D_X86_=1 -Dtry=__try -Dexcept=__except -DWIN32 -D_WIN32 -g -O0 -W -Wall -I.. -I..\cblas
SET _OPT_RELEASE=-c -D_X86_=1 -Dtry=__try -Dexcept=__except -DWIN32 -D_WIN32 -O3 -W -Wall -I.. -I..\cblas
SET _OPT_DLL=-DGSL_DLL -DDLL_EXPORT
SET _DLL_LINK_FLAG=-shared -Wl,--out-implib,
SET _ARC=ar
SET _ARC_OPTS=-ru
SET _MKDIR=mkdir
SET _COPY=copy
SET _PATH_INSTALL=.\install
SET _VERSION_STRING=gsl-1.8-1

REM %_COPY% gsl headers to gsl subdirectory
%_COPY%  config.h.mingw ..\config.h
%_COPY% ..\.\gsl_math.h ..\gsl\gsl_math.h
%_COPY% ..\.\gsl_pow_int.h ..\gsl\gsl_pow_int.h
%_COPY% ..\.\gsl_nan.h ..\gsl\gsl_nan.h
%_COPY% ..\.\gsl_machine.h ..\gsl\gsl_machine.h
%_COPY% ..\.\gsl_mode.h ..\gsl\gsl_mode.h
%_COPY% ..\.\gsl_precision.h ..\gsl\gsl_precision.h
%_COPY% ..\.\gsl_types.h ..\gsl\gsl_types.h
%_COPY% ..\.\gsl_version.h ..\gsl\gsl_version.h
%_COPY% ..\blas\gsl_blas.h ..\gsl\gsl_blas.h
%_COPY% ..\blas\gsl_blas_types.h ..\gsl\gsl_blas_types.h
%_COPY% ..\block\gsl_block.h ..\gsl\gsl_block.h
%_COPY% ..\block\gsl_block_char.h ..\gsl\gsl_block_char.h
%_COPY% ..\block\gsl_block_complex_double.h ..\gsl\gsl_block_complex_double.h
%_COPY% ..\block\gsl_block_complex_float.h ..\gsl\gsl_block_complex_float.h
%_COPY% ..\block\gsl_block_complex_long_double.h ..\gsl\gsl_block_complex_long_double.h
%_COPY% ..\block\gsl_block_double.h ..\gsl\gsl_block_double.h
%_COPY% ..\block\gsl_block_float.h ..\gsl\gsl_block_float.h
%_COPY% ..\block\gsl_block_int.h ..\gsl\gsl_block_int.h
%_COPY% ..\block\gsl_block_long.h ..\gsl\gsl_block_long.h
%_COPY% ..\block\gsl_block_long_double.h ..\gsl\gsl_block_long_double.h
%_COPY% ..\block\gsl_block_short.h ..\gsl\gsl_block_short.h
%_COPY% ..\block\gsl_block_uchar.h ..\gsl\gsl_block_uchar.h
%_COPY% ..\block\gsl_block_uint.h ..\gsl\gsl_block_uint.h
%_COPY% ..\block\gsl_block_ulong.h ..\gsl\gsl_block_ulong.h
%_COPY% ..\block\gsl_block_ushort.h ..\gsl\gsl_block_ushort.h
%_COPY% ..\block\gsl_check_range.h ..\gsl\gsl_check_range.h
%_COPY% ..\cblas\gsl_cblas.h ..\gsl\gsl_cblas.h
%_COPY% ..\cdf\gsl_cdf.h ..\gsl\gsl_cdf.h
%_COPY% ..\cheb\gsl_chebyshev.h ..\gsl\gsl_chebyshev.h
%_COPY% ..\combination\gsl_combination.h ..\gsl\gsl_combination.h
%_COPY% ..\complex\gsl_complex.h ..\gsl\gsl_complex.h
%_COPY% ..\complex\gsl_complex_math.h ..\gsl\gsl_complex_math.h
%_COPY% ..\const\gsl_const.h ..\gsl\gsl_const.h
%_COPY% ..\const\gsl_const_cgs.h ..\gsl\gsl_const_cgs.h
%_COPY% ..\const\gsl_const_mks.h ..\gsl\gsl_const_mks.h
%_COPY% ..\const\gsl_const_cgsm.h ..\gsl\gsl_const_cgsm.h
%_COPY% ..\const\gsl_const_mksa.h ..\gsl\gsl_const_mksa.h
%_COPY% ..\const\gsl_const_num.h ..\gsl\gsl_const_num.h
%_COPY% ..\deriv\gsl_deriv.h ..\gsl\gsl_deriv.h
%_COPY% ..\dht\gsl_dht.h ..\gsl\gsl_dht.h
%_COPY% ..\diff\gsl_diff.h ..\gsl\gsl_diff.h
%_COPY% ..\eigen\gsl_eigen.h ..\gsl\gsl_eigen.h
%_COPY% ..\err\gsl_errno.h ..\gsl\gsl_errno.h
%_COPY% ..\err\gsl_message.h ..\gsl\gsl_message.h
%_COPY% ..\fft\gsl_fft.h ..\gsl\gsl_fft.h
%_COPY% ..\fft\gsl_fft_complex.h ..\gsl\gsl_fft_complex.h
%_COPY% ..\fft\gsl_fft_halfcomplex.h ..\gsl\gsl_fft_halfcomplex.h
%_COPY% ..\fft\gsl_fft_real.h ..\gsl\gsl_fft_real.h
%_COPY% ..\fft\gsl_dft_complex.h ..\gsl\gsl_dft_complex.h
%_COPY% ..\fft\gsl_dft_complex_float.h ..\gsl\gsl_dft_complex_float.h
%_COPY% ..\fft\gsl_fft_complex_float.h ..\gsl\gsl_fft_complex_float.h
%_COPY% ..\fft\gsl_fft_halfcomplex_float.h ..\gsl\gsl_fft_halfcomplex_float.h
%_COPY% ..\fft\gsl_fft_real_float.h ..\gsl\gsl_fft_real_float.h
%_COPY% ..\fit\gsl_fit.h ..\gsl\gsl_fit.h
%_COPY% ..\histogram\gsl_histogram.h ..\gsl\gsl_histogram.h
%_COPY% ..\histogram\gsl_histogram2d.h ..\gsl\gsl_histogram2d.h
%_COPY% ..\ieee-utils\gsl_ieee_utils.h ..\gsl\gsl_ieee_utils.h
%_COPY% ..\integration\gsl_integration.h ..\gsl\gsl_integration.h
%_COPY% ..\interpolation\gsl_interp.h ..\gsl\gsl_interp.h
%_COPY% ..\interpolation\gsl_spline.h ..\gsl\gsl_spline.h
%_COPY% ..\linalg\gsl_linalg.h ..\gsl\gsl_linalg.h
%_COPY% ..\matrix\gsl_matrix.h ..\gsl\gsl_matrix.h
%_COPY% ..\matrix\gsl_matrix_char.h ..\gsl\gsl_matrix_char.h
%_COPY% ..\matrix\gsl_matrix_complex_double.h ..\gsl\gsl_matrix_complex_double.h
%_COPY% ..\matrix\gsl_matrix_complex_float.h ..\gsl\gsl_matrix_complex_float.h
%_COPY% ..\matrix\gsl_matrix_complex_long_double.h ..\gsl\gsl_matrix_complex_long_double.h
%_COPY% ..\matrix\gsl_matrix_double.h ..\gsl\gsl_matrix_double.h
%_COPY% ..\matrix\gsl_matrix_float.h ..\gsl\gsl_matrix_float.h
%_COPY% ..\matrix\gsl_matrix_int.h ..\gsl\gsl_matrix_int.h
%_COPY% ..\matrix\gsl_matrix_long.h ..\gsl\gsl_matrix_long.h
%_COPY% ..\matrix\gsl_matrix_long_double.h ..\gsl\gsl_matrix_long_double.h
%_COPY% ..\matrix\gsl_matrix_short.h ..\gsl\gsl_matrix_short.h
%_COPY% ..\matrix\gsl_matrix_uchar.h ..\gsl\gsl_matrix_uchar.h
%_COPY% ..\matrix\gsl_matrix_uint.h ..\gsl\gsl_matrix_uint.h
%_COPY% ..\matrix\gsl_matrix_ulong.h ..\gsl\gsl_matrix_ulong.h
%_COPY% ..\matrix\gsl_matrix_ushort.h ..\gsl\gsl_matrix_ushort.h
%_COPY% ..\min\gsl_min.h ..\gsl\gsl_min.h
%_COPY% ..\monte\gsl_monte.h ..\gsl\gsl_monte.h
%_COPY% ..\monte\gsl_monte_vegas.h ..\gsl\gsl_monte_vegas.h
%_COPY% ..\monte\gsl_monte_miser.h ..\gsl\gsl_monte_miser.h
%_COPY% ..\monte\gsl_monte_plain.h ..\gsl\gsl_monte_plain.h
%_COPY% ..\multifit\gsl_multifit.h ..\gsl\gsl_multifit.h
%_COPY% ..\multifit\gsl_multifit_nlin.h ..\gsl\gsl_multifit_nlin.h
%_COPY% ..\multimin\gsl_multimin.h ..\gsl\gsl_multimin.h
%_COPY% ..\multiroots\gsl_multiroots.h ..\gsl\gsl_multiroots.h
%_COPY% ..\ntuple\gsl_ntuple.h ..\gsl\gsl_ntuple.h
%_COPY% ..\ode-initval\gsl_odeiv.h ..\gsl\gsl_odeiv.h
%_COPY% ..\permutation\gsl_permutation.h ..\gsl\gsl_permutation.h
%_COPY% ..\permutation\gsl_permute.h ..\gsl\gsl_permute.h
%_COPY% ..\permutation\gsl_permute_char.h ..\gsl\gsl_permute_char.h
%_COPY% ..\permutation\gsl_permute_complex_double.h ..\gsl\gsl_permute_complex_double.h
%_COPY% ..\permutation\gsl_permute_complex_float.h ..\gsl\gsl_permute_complex_float.h
%_COPY% ..\permutation\gsl_permute_complex_long_double.h ..\gsl\gsl_permute_complex_long_double.h
%_COPY% ..\permutation\gsl_permute_double.h ..\gsl\gsl_permute_double.h
%_COPY% ..\permutation\gsl_permute_float.h ..\gsl\gsl_permute_float.h
%_COPY% ..\permutation\gsl_permute_int.h ..\gsl\gsl_permute_int.h
%_COPY% ..\permutation\gsl_permute_long.h ..\gsl\gsl_permute_long.h
%_COPY% ..\permutation\gsl_permute_long_double.h ..\gsl\gsl_permute_long_double.h
%_COPY% ..\permutation\gsl_permute_short.h ..\gsl\gsl_permute_short.h
%_COPY% ..\permutation\gsl_permute_uchar.h ..\gsl\gsl_permute_uchar.h
%_COPY% ..\permutation\gsl_permute_uint.h ..\gsl\gsl_permute_uint.h
%_COPY% ..\permutation\gsl_permute_ulong.h ..\gsl\gsl_permute_ulong.h
%_COPY% ..\permutation\gsl_permute_ushort.h ..\gsl\gsl_permute_ushort.h
%_COPY% ..\permutation\gsl_permute_vector.h ..\gsl\gsl_permute_vector.h
%_COPY% ..\permutation\gsl_permute_vector_char.h ..\gsl\gsl_permute_vector_char.h
%_COPY% ..\permutation\gsl_permute_vector_complex_double.h ..\gsl\gsl_permute_vector_complex_double.h
%_COPY% ..\permutation\gsl_permute_vector_complex_float.h ..\gsl\gsl_permute_vector_complex_float.h
%_COPY% ..\permutation\gsl_permute_vector_complex_long_double.h ..\gsl\gsl_permute_vector_complex_long_double.h
%_COPY% ..\permutation\gsl_permute_vector_double.h ..\gsl\gsl_permute_vector_double.h
%_COPY% ..\permutation\gsl_permute_vector_float.h ..\gsl\gsl_permute_vector_float.h
%_COPY% ..\permutation\gsl_permute_vector_int.h ..\gsl\gsl_permute_vector_int.h
%_COPY% ..\permutation\gsl_permute_vector_long.h ..\gsl\gsl_permute_vector_long.h
%_COPY% ..\permutation\gsl_permute_vector_long_double.h ..\gsl\gsl_permute_vector_long_double.h
%_COPY% ..\permutation\gsl_permute_vector_short.h ..\gsl\gsl_permute_vector_short.h
%_COPY% ..\permutation\gsl_permute_vector_uchar.h ..\gsl\gsl_permute_vector_uchar.h
%_COPY% ..\permutation\gsl_permute_vector_uint.h ..\gsl\gsl_permute_vector_uint.h
%_COPY% ..\permutation\gsl_permute_vector_ulong.h ..\gsl\gsl_permute_vector_ulong.h
%_COPY% ..\permutation\gsl_permute_vector_ushort.h ..\gsl\gsl_permute_vector_ushort.h
%_COPY% ..\poly\gsl_poly.h ..\gsl\gsl_poly.h
%_COPY% ..\qrng\gsl_qrng.h ..\gsl\gsl_qrng.h
%_COPY% ..\randist\gsl_randist.h ..\gsl\gsl_randist.h
%_COPY% ..\rng\gsl_rng.h ..\gsl\gsl_rng.h
%_COPY% ..\roots\gsl_roots.h ..\gsl\gsl_roots.h
%_COPY% ..\siman\gsl_siman.h ..\gsl\gsl_siman.h
%_COPY% ..\sort\gsl_heapsort.h ..\gsl\gsl_heapsort.h
%_COPY% ..\sort\gsl_sort.h ..\gsl\gsl_sort.h
%_COPY% ..\sort\gsl_sort_char.h ..\gsl\gsl_sort_char.h
%_COPY% ..\sort\gsl_sort_double.h ..\gsl\gsl_sort_double.h
%_COPY% ..\sort\gsl_sort_float.h ..\gsl\gsl_sort_float.h
%_COPY% ..\sort\gsl_sort_int.h ..\gsl\gsl_sort_int.h
%_COPY% ..\sort\gsl_sort_long.h ..\gsl\gsl_sort_long.h
%_COPY% ..\sort\gsl_sort_long_double.h ..\gsl\gsl_sort_long_double.h
%_COPY% ..\sort\gsl_sort_short.h ..\gsl\gsl_sort_short.h
%_COPY% ..\sort\gsl_sort_uchar.h ..\gsl\gsl_sort_uchar.h
%_COPY% ..\sort\gsl_sort_uint.h ..\gsl\gsl_sort_uint.h
%_COPY% ..\sort\gsl_sort_ulong.h ..\gsl\gsl_sort_ulong.h
%_COPY% ..\sort\gsl_sort_ushort.h ..\gsl\gsl_sort_ushort.h
%_COPY% ..\sort\gsl_sort_vector.h ..\gsl\gsl_sort_vector.h
%_COPY% ..\sort\gsl_sort_vector_char.h ..\gsl\gsl_sort_vector_char.h
%_COPY% ..\sort\gsl_sort_vector_double.h ..\gsl\gsl_sort_vector_double.h
%_COPY% ..\sort\gsl_sort_vector_float.h ..\gsl\gsl_sort_vector_float.h
%_COPY% ..\sort\gsl_sort_vector_int.h ..\gsl\gsl_sort_vector_int.h
%_COPY% ..\sort\gsl_sort_vector_long.h ..\gsl\gsl_sort_vector_long.h
%_COPY% ..\sort\gsl_sort_vector_long_double.h ..\gsl\gsl_sort_vector_long_double.h
%_COPY% ..\sort\gsl_sort_vector_short.h ..\gsl\gsl_sort_vector_short.h
%_COPY% ..\sort\gsl_sort_vector_uchar.h ..\gsl\gsl_sort_vector_uchar.h
%_COPY% ..\sort\gsl_sort_vector_uint.h ..\gsl\gsl_sort_vector_uint.h
%_COPY% ..\sort\gsl_sort_vector_ulong.h ..\gsl\gsl_sort_vector_ulong.h
%_COPY% ..\sort\gsl_sort_vector_ushort.h ..\gsl\gsl_sort_vector_ushort.h
%_COPY% ..\specfunc\gsl_sf.h ..\gsl\gsl_sf.h
%_COPY% ..\specfunc\gsl_sf_airy.h ..\gsl\gsl_sf_airy.h
%_COPY% ..\specfunc\gsl_sf_bessel.h ..\gsl\gsl_sf_bessel.h
%_COPY% ..\specfunc\gsl_sf_clausen.h ..\gsl\gsl_sf_clausen.h
%_COPY% ..\specfunc\gsl_sf_coulomb.h ..\gsl\gsl_sf_coulomb.h
%_COPY% ..\specfunc\gsl_sf_coupling.h ..\gsl\gsl_sf_coupling.h
%_COPY% ..\specfunc\gsl_sf_dawson.h ..\gsl\gsl_sf_dawson.h
%_COPY% ..\specfunc\gsl_sf_debye.h ..\gsl\gsl_sf_debye.h
%_COPY% ..\specfunc\gsl_sf_dilog.h ..\gsl\gsl_sf_dilog.h
%_COPY% ..\specfunc\gsl_sf_elementary.h ..\gsl\gsl_sf_elementary.h
%_COPY% ..\specfunc\gsl_sf_ellint.h ..\gsl\gsl_sf_ellint.h
%_COPY% ..\specfunc\gsl_sf_elljac.h ..\gsl\gsl_sf_elljac.h
%_COPY% ..\specfunc\gsl_sf_erf.h ..\gsl\gsl_sf_erf.h
%_COPY% ..\specfunc\gsl_sf_exp.h ..\gsl\gsl_sf_exp.h
%_COPY% ..\specfunc\gsl_sf_expint.h ..\gsl\gsl_sf_expint.h
%_COPY% ..\specfunc\gsl_sf_fermi_dirac.h ..\gsl\gsl_sf_fermi_dirac.h
%_COPY% ..\specfunc\gsl_sf_gamma.h ..\gsl\gsl_sf_gamma.h
%_COPY% ..\specfunc\gsl_sf_gegenbauer.h ..\gsl\gsl_sf_gegenbauer.h
%_COPY% ..\specfunc\gsl_sf_hyperg.h ..\gsl\gsl_sf_hyperg.h
%_COPY% ..\specfunc\gsl_sf_laguerre.h ..\gsl\gsl_sf_laguerre.h
%_COPY% ..\specfunc\gsl_sf_lambert.h ..\gsl\gsl_sf_lambert.h
%_COPY% ..\specfunc\gsl_sf_legendre.h ..\gsl\gsl_sf_legendre.h
%_COPY% ..\specfunc\gsl_sf_log.h ..\gsl\gsl_sf_log.h
%_COPY% ..\specfunc\gsl_sf_pow_int.h ..\gsl\gsl_sf_pow_int.h
%_COPY% ..\specfunc\gsl_sf_psi.h ..\gsl\gsl_sf_psi.h
%_COPY% ..\specfunc\gsl_sf_result.h ..\gsl\gsl_sf_result.h
%_COPY% ..\specfunc\gsl_sf_synchrotron.h ..\gsl\gsl_sf_synchrotron.h
%_COPY% ..\specfunc\gsl_sf_transport.h ..\gsl\gsl_sf_transport.h
%_COPY% ..\specfunc\gsl_sf_trig.h ..\gsl\gsl_sf_trig.h
%_COPY% ..\specfunc\gsl_sf_zeta.h ..\gsl\gsl_sf_zeta.h
%_COPY% ..\specfunc\gsl_specfunc.h ..\gsl\gsl_specfunc.h
%_COPY% ..\statistics\gsl_statistics.h ..\gsl\gsl_statistics.h
%_COPY% ..\statistics\gsl_statistics_char.h ..\gsl\gsl_statistics_char.h
%_COPY% ..\statistics\gsl_statistics_double.h ..\gsl\gsl_statistics_double.h
%_COPY% ..\statistics\gsl_statistics_float.h ..\gsl\gsl_statistics_float.h
%_COPY% ..\statistics\gsl_statistics_int.h ..\gsl\gsl_statistics_int.h
%_COPY% ..\statistics\gsl_statistics_long.h ..\gsl\gsl_statistics_long.h
%_COPY% ..\statistics\gsl_statistics_long_double.h ..\gsl\gsl_statistics_long_double.h
%_COPY% ..\statistics\gsl_statistics_short.h ..\gsl\gsl_statistics_short.h
%_COPY% ..\statistics\gsl_statistics_uchar.h ..\gsl\gsl_statistics_uchar.h
%_COPY% ..\statistics\gsl_statistics_uint.h ..\gsl\gsl_statistics_uint.h
%_COPY% ..\statistics\gsl_statistics_ulong.h ..\gsl\gsl_statistics_ulong.h
%_COPY% ..\statistics\gsl_statistics_ushort.h ..\gsl\gsl_statistics_ushort.h
%_COPY% ..\sum\gsl_sum.h ..\gsl\gsl_sum.h
%_COPY% ..\sys\gsl_sys.h ..\gsl\gsl_sys.h
%_COPY% ..\test\gsl_test.h ..\gsl\gsl_test.h
%_COPY% ..\vector\gsl_vector.h ..\gsl\gsl_vector.h
%_COPY% ..\vector\gsl_vector_char.h ..\gsl\gsl_vector_char.h
%_COPY% ..\vector\gsl_vector_complex.h ..\gsl\gsl_vector_complex.h
%_COPY% ..\vector\gsl_vector_complex_double.h ..\gsl\gsl_vector_complex_double.h
%_COPY% ..\vector\gsl_vector_complex_float.h ..\gsl\gsl_vector_complex_float.h
%_COPY% ..\vector\gsl_vector_complex_long_double.h ..\gsl\gsl_vector_complex_long_double.h
%_COPY% ..\vector\gsl_vector_double.h ..\gsl\gsl_vector_double.h
%_COPY% ..\vector\gsl_vector_float.h ..\gsl\gsl_vector_float.h
%_COPY% ..\vector\gsl_vector_int.h ..\gsl\gsl_vector_int.h
%_COPY% ..\vector\gsl_vector_long.h ..\gsl\gsl_vector_long.h
%_COPY% ..\vector\gsl_vector_long_double.h ..\gsl\gsl_vector_long_double.h
%_COPY% ..\vector\gsl_vector_short.h ..\gsl\gsl_vector_short.h
%_COPY% ..\vector\gsl_vector_uchar.h ..\gsl\gsl_vector_uchar.h
%_COPY% ..\vector\gsl_vector_uint.h ..\gsl\gsl_vector_uint.h
%_COPY% ..\vector\gsl_vector_ulong.h ..\gsl\gsl_vector_ulong.h
%_COPY% ..\vector\gsl_vector_ushort.h ..\gsl\gsl_vector_ushort.h
%_COPY% ..\wavelet\gsl_wavelet.h ..\gsl\gsl_wavelet.h
%_COPY% ..\wavelet\gsl_wavelet2d.h ..\gsl\gsl_wavelet2d.h

%_MKDIR% .\Debug
%_MKDIR% .\Debug\mingw
%_MKDIR% .\Debug\mingw\temp

REM Compile libgsl (debug) sources
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\version.o ..\version.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\blas_blas.o ..\blas\blas.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\block_init.o ..\block\init.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\block_file.o ..\block\file.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\block_block.o ..\block\block.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_beta.o ..\cdf\beta.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_betainv.o ..\cdf\betainv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_cauchy.o ..\cdf\cauchy.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_cauchyinv.o ..\cdf\cauchyinv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_chisq.o ..\cdf\chisq.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_chisqinv.o ..\cdf\chisqinv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_exponential.o ..\cdf\exponential.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_exponentialinv.o ..\cdf\exponentialinv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_exppow.o ..\cdf\exppow.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_fdist.o ..\cdf\fdist.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_fdistinv.o ..\cdf\fdistinv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_flat.o ..\cdf\flat.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_flatinv.o ..\cdf\flatinv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_gamma.o ..\cdf\gamma.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_gammainv.o ..\cdf\gammainv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_gauss.o ..\cdf\gauss.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_gaussinv.o ..\cdf\gaussinv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_gumbel1.o ..\cdf\gumbel1.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_gumbel1inv.o ..\cdf\gumbel1inv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_gumbel2.o ..\cdf\gumbel2.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_gumbel2inv.o ..\cdf\gumbel2inv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_laplace.o ..\cdf\laplace.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_laplaceinv.o ..\cdf\laplaceinv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_logistic.o ..\cdf\logistic.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_logisticinv.o ..\cdf\logisticinv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_lognormal.o ..\cdf\lognormal.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_lognormalinv.o ..\cdf\lognormalinv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_pareto.o ..\cdf\pareto.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_paretoinv.o ..\cdf\paretoinv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_rayleigh.o ..\cdf\rayleigh.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_rayleighinv.o ..\cdf\rayleighinv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_tdist.o ..\cdf\tdist.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_tdistinv.o ..\cdf\tdistinv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_weibull.o ..\cdf\weibull.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_weibullinv.o ..\cdf\weibullinv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_binomial.o ..\cdf\binomial.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_poisson.o ..\cdf\poisson.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_geometric.o ..\cdf\geometric.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_nbinomial.o ..\cdf\nbinomial.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_pascal.o ..\cdf\pascal.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_hypergeometric.o ..\cdf\hypergeometric.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cheb_deriv.o ..\cheb\deriv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cheb_eval.o ..\cheb\eval.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cheb_init.o ..\cheb\init.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cheb_integ.o ..\cheb\integ.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\combination_init.o ..\combination\init.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\combination_file.o ..\combination\file.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\combination_combination.o ..\combination\combination.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\complex_math.o ..\complex\math.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\deriv_deriv.o ..\deriv\deriv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dht_dht.o ..\dht\dht.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\diff_diff.o ..\diff\diff.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\eigen_jacobi.o ..\eigen\jacobi.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\eigen_symm.o ..\eigen\symm.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\eigen_symmv.o ..\eigen\symmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\eigen_herm.o ..\eigen\herm.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\eigen_hermv.o ..\eigen\hermv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\eigen_sort.o ..\eigen\sort.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\err_error.o ..\err\error.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\err_stream.o ..\err\stream.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\err_message.o ..\err\message.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\err_strerror.o ..\err\strerror.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\fft_dft.o ..\fft\dft.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\fft_fft.o ..\fft\fft.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\fit_linear.o ..\fit\linear.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_add.o ..\histogram\add.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_get.o ..\histogram\get.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_init.o ..\histogram\init.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_params.o ..\histogram\params.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_reset.o ..\histogram\reset.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_file.o ..\histogram\file.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_pdf.o ..\histogram\pdf.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_add2d.o ..\histogram\add2d.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_get2d.o ..\histogram\get2d.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_init2d.o ..\histogram\init2d.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_params2d.o ..\histogram\params2d.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_reset2d.o ..\histogram\reset2d.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_file2d.o ..\histogram\file2d.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_pdf2d.o ..\histogram\pdf2d.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_calloc_range.o ..\histogram\calloc_range.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_calloc_range2d.o ..\histogram\calloc_range2d.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_copy.o ..\histogram\copy.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_copy2d.o ..\histogram\copy2d.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_maxval.o ..\histogram\maxval.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_maxval2d.o ..\histogram\maxval2d.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_oper.o ..\histogram\oper.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_oper2d.o ..\histogram\oper2d.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_stat.o ..\histogram\stat.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_stat2d.o ..\histogram\stat2d.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ieee-utils_print.o ..\ieee-utils\print.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ieee-utils_make_rep.o ..\ieee-utils\make_rep.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ieee-utils_env.o ..\ieee-utils\env.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ieee-utils_fp.o ..\ieee-utils\fp.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ieee-utils_read.o ..\ieee-utils\read.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\integration_qk15.o ..\integration\qk15.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\integration_qk21.o ..\integration\qk21.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\integration_qk31.o ..\integration\qk31.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\integration_qk41.o ..\integration\qk41.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\integration_qk51.o ..\integration\qk51.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\integration_qk61.o ..\integration\qk61.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\integration_qk.o ..\integration\qk.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\integration_qng.o ..\integration\qng.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\integration_qag.o ..\integration\qag.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\integration_qags.o ..\integration\qags.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\integration_qagp.o ..\integration\qagp.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\integration_workspace.o ..\integration\workspace.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\integration_qcheb.o ..\integration\qcheb.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\integration_qawc.o ..\integration\qawc.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\integration_qmomo.o ..\integration\qmomo.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\integration_qaws.o ..\integration\qaws.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\integration_qmomof.o ..\integration\qmomof.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\integration_qawo.o ..\integration\qawo.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\integration_qawf.o ..\integration\qawf.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\interpolation_accel.o ..\interpolation\accel.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\interpolation_akima.o ..\interpolation\akima.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\interpolation_bsearch.o ..\interpolation\bsearch.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\interpolation_cspline.o ..\interpolation\cspline.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\interpolation_interp.o ..\interpolation\interp.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\interpolation_linear.o ..\interpolation\linear.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\interpolation_spline.o ..\interpolation\spline.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\interpolation_poly.o ..\interpolation\poly.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\linalg_multiply.o ..\linalg\multiply.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\linalg_exponential.o ..\linalg\exponential.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\linalg_tridiag.o ..\linalg\tridiag.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\linalg_lu.o ..\linalg\lu.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\linalg_luc.o ..\linalg\luc.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\linalg_hh.o ..\linalg\hh.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\linalg_qr.o ..\linalg\qr.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\linalg_qrpt.o ..\linalg\qrpt.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\linalg_lq.o ..\linalg\lq.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\linalg_ptlq.o ..\linalg\ptlq.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\linalg_svd.o ..\linalg\svd.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\linalg_householder.o ..\linalg\householder.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\linalg_householdercomplex.o ..\linalg\householdercomplex.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\linalg_cholesky.o ..\linalg\cholesky.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\linalg_symmtd.o ..\linalg\symmtd.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\linalg_hermtd.o ..\linalg\hermtd.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\linalg_bidiag.o ..\linalg\bidiag.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\linalg_balance.o ..\linalg\balance.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\matrix_init.o ..\matrix\init.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\matrix_matrix.o ..\matrix\matrix.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\matrix_file.o ..\matrix\file.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\matrix_rowcol.o ..\matrix\rowcol.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\matrix_swap.o ..\matrix\swap.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\matrix_copy.o ..\matrix\copy.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\matrix_minmax.o ..\matrix\minmax.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\matrix_prop.o ..\matrix\prop.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\matrix_oper.o ..\matrix\oper.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\matrix_getset.o ..\matrix\getset.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\matrix_view.o ..\matrix\view.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\matrix_submatrix.o ..\matrix\submatrix.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\min_fsolver.o ..\min\fsolver.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\min_golden.o ..\min\golden.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\min_brent.o ..\min\brent.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\min_convergence.o ..\min\convergence.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\min_bracketing.o ..\min\bracketing.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\monte_miser.o ..\monte\miser.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\monte_plain.o ..\monte\plain.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\monte_vegas.o ..\monte\vegas.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multifit_multilinear.o ..\multifit\multilinear.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multifit_work.o ..\multifit\work.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multifit_lmder.o ..\multifit\lmder.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multifit_fsolver.o ..\multifit\fsolver.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multifit_fdfsolver.o ..\multifit\fdfsolver.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multifit_convergence.o ..\multifit\convergence.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multifit_gradient.o ..\multifit\gradient.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multifit_covar.o ..\multifit\covar.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multimin_fdfminimizer.o ..\multimin\fdfminimizer.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multimin_steepest_descent.o ..\multimin\steepest_descent.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multimin_conjugate_fr.o ..\multimin\conjugate_fr.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multimin_conjugate_pr.o ..\multimin\conjugate_pr.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multimin_convergence.o ..\multimin\convergence.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multimin_diff.o ..\multimin\diff.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multimin_vector_bfgs.o ..\multimin\vector_bfgs.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multimin_fminimizer.o ..\multimin\fminimizer.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multimin_simplex.o ..\multimin\simplex.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multiroots_fdjac.o ..\multiroots\fdjac.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multiroots_fsolver.o ..\multiroots\fsolver.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multiroots_fdfsolver.o ..\multiroots\fdfsolver.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multiroots_convergence.o ..\multiroots\convergence.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multiroots_newton.o ..\multiroots\newton.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multiroots_gnewton.o ..\multiroots\gnewton.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multiroots_dnewton.o ..\multiroots\dnewton.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multiroots_broyden.o ..\multiroots\broyden.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multiroots_hybrid.o ..\multiroots\hybrid.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multiroots_hybridj.o ..\multiroots\hybridj.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ntuple_ntuple.o ..\ntuple\ntuple.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ode-initval_control.o ..\ode-initval\control.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ode-initval_cstd.o ..\ode-initval\cstd.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ode-initval_cscal.o ..\ode-initval\cscal.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ode-initval_evolve.o ..\ode-initval\evolve.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ode-initval_step.o ..\ode-initval\step.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ode-initval_rk2.o ..\ode-initval\rk2.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ode-initval_rk2imp.o ..\ode-initval\rk2imp.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ode-initval_rk2simp.o ..\ode-initval\rk2simp.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ode-initval_rk4.o ..\ode-initval\rk4.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ode-initval_rk4imp.o ..\ode-initval\rk4imp.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ode-initval_rkf45.o ..\ode-initval\rkf45.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ode-initval_rk8pd.o ..\ode-initval\rk8pd.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ode-initval_rkck.o ..\ode-initval\rkck.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ode-initval_bsimp.o ..\ode-initval\bsimp.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ode-initval_gear1.o ..\ode-initval\gear1.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ode-initval_gear2.o ..\ode-initval\gear2.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\permutation_init.o ..\permutation\init.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\permutation_file.o ..\permutation\file.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\permutation_permutation.o ..\permutation\permutation.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\permutation_permute.o ..\permutation\permute.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\permutation_canonical.o ..\permutation\canonical.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\poly_dd.o ..\poly\dd.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\poly_eval.o ..\poly\eval.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\poly_solve_quadratic.o ..\poly\solve_quadratic.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\poly_solve_cubic.o ..\poly\solve_cubic.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\poly_zsolve_quadratic.o ..\poly\zsolve_quadratic.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\poly_zsolve_cubic.o ..\poly\zsolve_cubic.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\poly_zsolve.o ..\poly\zsolve.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\poly_zsolve_init.o ..\poly\zsolve_init.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\qrng_qrng.o ..\qrng\qrng.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\qrng_niederreiter-2.o ..\qrng\niederreiter-2.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\qrng_sobol.o ..\qrng\sobol.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_bernoulli.o ..\randist\bernoulli.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_beta.o ..\randist\beta.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_bigauss.o ..\randist\bigauss.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_binomial.o ..\randist\binomial.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_cauchy.o ..\randist\cauchy.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_chisq.o ..\randist\chisq.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_dirichlet.o ..\randist\dirichlet.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_discrete.o ..\randist\discrete.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_erlang.o ..\randist\erlang.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_exponential.o ..\randist\exponential.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_exppow.o ..\randist\exppow.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_fdist.o ..\randist\fdist.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_flat.o ..\randist\flat.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_gamma.o ..\randist\gamma.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_gauss.o ..\randist\gauss.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_gausszig.o ..\randist\gausszig.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_gausstail.o ..\randist\gausstail.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_geometric.o ..\randist\geometric.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_gumbel.o ..\randist\gumbel.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_hyperg.o ..\randist\hyperg.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_laplace.o ..\randist\laplace.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_levy.o ..\randist\levy.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_logarithmic.o ..\randist\logarithmic.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_logistic.o ..\randist\logistic.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_lognormal.o ..\randist\lognormal.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_multinomial.o ..\randist\multinomial.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_nbinomial.o ..\randist\nbinomial.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_pareto.o ..\randist\pareto.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_pascal.o ..\randist\pascal.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_poisson.o ..\randist\poisson.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_rayleigh.o ..\randist\rayleigh.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_shuffle.o ..\randist\shuffle.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_sphere.o ..\randist\sphere.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_tdist.o ..\randist\tdist.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_weibull.o ..\randist\weibull.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_landau.o ..\randist\landau.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_binomial_tpe.o ..\randist\binomial_tpe.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_borosh13.o ..\rng\borosh13.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_cmrg.o ..\rng\cmrg.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_coveyou.o ..\rng\coveyou.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_default.o ..\rng\default.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_file.o ..\rng\file.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_fishman18.o ..\rng\fishman18.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_fishman20.o ..\rng\fishman20.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_fishman2x.o ..\rng\fishman2x.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_gfsr4.o ..\rng\gfsr4.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_knuthran2.o ..\rng\knuthran2.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_knuthran.o ..\rng\knuthran.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_lecuyer21.o ..\rng\lecuyer21.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_minstd.o ..\rng\minstd.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_mrg.o ..\rng\mrg.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_mt.o ..\rng\mt.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_r250.o ..\rng\r250.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_ran0.o ..\rng\ran0.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_ran1.o ..\rng\ran1.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_ran2.o ..\rng\ran2.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_ran3.o ..\rng\ran3.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_rand48.o ..\rng\rand48.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_rand.o ..\rng\rand.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_random.o ..\rng\random.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_randu.o ..\rng\randu.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_ranf.o ..\rng\ranf.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_ranlux.o ..\rng\ranlux.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_ranlxd.o ..\rng\ranlxd.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_ranlxs.o ..\rng\ranlxs.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_ranmar.o ..\rng\ranmar.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_rng.o ..\rng\rng.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_slatec.o ..\rng\slatec.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_taus.o ..\rng\taus.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_taus113.o ..\rng\taus113.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_transputer.o ..\rng\transputer.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_tt.o ..\rng\tt.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_types.o ..\rng\types.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_uni32.o ..\rng\uni32.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_uni.o ..\rng\uni.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_vax.o ..\rng\vax.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_waterman14.o ..\rng\waterman14.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_zuf.o ..\rng\zuf.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\roots_bisection.o ..\roots\bisection.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\roots_brent.o ..\roots\brent.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\roots_falsepos.o ..\roots\falsepos.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\roots_newton.o ..\roots\newton.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\roots_secant.o ..\roots\secant.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\roots_steffenson.o ..\roots\steffenson.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\roots_convergence.o ..\roots\convergence.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\roots_fsolver.o ..\roots\fsolver.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\roots_fdfsolver.o ..\roots\fdfsolver.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\siman_siman.o ..\siman\siman.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\sort_sort.o ..\sort\sort.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\sort_sortind.o ..\sort\sortind.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\sort_sortvec.o ..\sort\sortvec.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\sort_sortvecind.o ..\sort\sortvecind.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\sort_subset.o ..\sort\subset.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\sort_subsetind.o ..\sort\subsetind.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_airy.o ..\specfunc\airy.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_airy_der.o ..\specfunc\airy_der.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_airy_zero.o ..\specfunc\airy_zero.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_atanint.o ..\specfunc\atanint.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_bessel.o ..\specfunc\bessel.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_bessel_I0.o ..\specfunc\bessel_I0.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_bessel_I1.o ..\specfunc\bessel_I1.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_bessel_In.o ..\specfunc\bessel_In.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_bessel_Inu.o ..\specfunc\bessel_Inu.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_bessel_J0.o ..\specfunc\bessel_J0.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_bessel_J1.o ..\specfunc\bessel_J1.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_bessel_Jn.o ..\specfunc\bessel_Jn.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_bessel_Jnu.o ..\specfunc\bessel_Jnu.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_bessel_K0.o ..\specfunc\bessel_K0.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_bessel_K1.o ..\specfunc\bessel_K1.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_bessel_Kn.o ..\specfunc\bessel_Kn.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_bessel_Knu.o ..\specfunc\bessel_Knu.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_bessel_Y0.o ..\specfunc\bessel_Y0.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_bessel_Y1.o ..\specfunc\bessel_Y1.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_bessel_Yn.o ..\specfunc\bessel_Yn.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_bessel_Ynu.o ..\specfunc\bessel_Ynu.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_bessel_amp_phase.o ..\specfunc\bessel_amp_phase.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_bessel_i.o ..\specfunc\bessel_i.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_bessel_j.o ..\specfunc\bessel_j.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_bessel_k.o ..\specfunc\bessel_k.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_bessel_olver.o ..\specfunc\bessel_olver.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_bessel_temme.o ..\specfunc\bessel_temme.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_bessel_y.o ..\specfunc\bessel_y.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_bessel_zero.o ..\specfunc\bessel_zero.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_bessel_sequence.o ..\specfunc\bessel_sequence.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_beta.o ..\specfunc\beta.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_beta_inc.o ..\specfunc\beta_inc.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_clausen.o ..\specfunc\clausen.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_coulomb.o ..\specfunc\coulomb.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_coupling.o ..\specfunc\coupling.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_coulomb_bound.o ..\specfunc\coulomb_bound.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_dawson.o ..\specfunc\dawson.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_debye.o ..\specfunc\debye.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_dilog.o ..\specfunc\dilog.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_elementary.o ..\specfunc\elementary.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_ellint.o ..\specfunc\ellint.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_elljac.o ..\specfunc\elljac.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_erfc.o ..\specfunc\erfc.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_exp.o ..\specfunc\exp.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_expint.o ..\specfunc\expint.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_expint3.o ..\specfunc\expint3.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_fermi_dirac.o ..\specfunc\fermi_dirac.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_gegenbauer.o ..\specfunc\gegenbauer.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_gamma.o ..\specfunc\gamma.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_gamma_inc.o ..\specfunc\gamma_inc.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_hyperg_0F1.o ..\specfunc\hyperg_0F1.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_hyperg_2F0.o ..\specfunc\hyperg_2F0.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_hyperg_1F1.o ..\specfunc\hyperg_1F1.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_hyperg_2F1.o ..\specfunc\hyperg_2F1.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_hyperg_U.o ..\specfunc\hyperg_U.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_hyperg.o ..\specfunc\hyperg.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_laguerre.o ..\specfunc\laguerre.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_lambert.o ..\specfunc\lambert.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_legendre_H3d.o ..\specfunc\legendre_H3d.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_legendre_Qn.o ..\specfunc\legendre_Qn.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_legendre_con.o ..\specfunc\legendre_con.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_legendre_poly.o ..\specfunc\legendre_poly.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_log.o ..\specfunc\log.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_poch.o ..\specfunc\poch.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_pow_int.o ..\specfunc\pow_int.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_psi.o ..\specfunc\psi.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_result.o ..\specfunc\result.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_shint.o ..\specfunc\shint.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_sinint.o ..\specfunc\sinint.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_synchrotron.o ..\specfunc\synchrotron.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_transport.o ..\specfunc\transport.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_trig.o ..\specfunc\trig.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_zeta.o ..\specfunc\zeta.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\statistics_mean.o ..\statistics\mean.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\statistics_variance.o ..\statistics\variance.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\statistics_absdev.o ..\statistics\absdev.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\statistics_skew.o ..\statistics\skew.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\statistics_kurtosis.o ..\statistics\kurtosis.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\statistics_lag1.o ..\statistics\lag1.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\statistics_p_variance.o ..\statistics\p_variance.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\statistics_minmax.o ..\statistics\minmax.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\statistics_ttest.o ..\statistics\ttest.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\statistics_median.o ..\statistics\median.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\statistics_covariance.o ..\statistics\covariance.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\statistics_quantiles.o ..\statistics\quantiles.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\statistics_wmean.o ..\statistics\wmean.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\statistics_wvariance.o ..\statistics\wvariance.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\statistics_wabsdev.o ..\statistics\wabsdev.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\statistics_wskew.o ..\statistics\wskew.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\statistics_wkurtosis.o ..\statistics\wkurtosis.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\sum_levin_u.o ..\sum\levin_u.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\sum_levin_utrunc.o ..\sum\levin_utrunc.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\sum_work_u.o ..\sum\work_u.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\sum_work_utrunc.o ..\sum\work_utrunc.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\sys_minmax.o ..\sys\minmax.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\sys_prec.o ..\sys\prec.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\sys_hypot.o ..\sys\hypot.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\sys_log1p.o ..\sys\log1p.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\sys_expm1.o ..\sys\expm1.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\sys_coerce.o ..\sys\coerce.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\sys_invhyp.o ..\sys\invhyp.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\sys_pow_int.o ..\sys\pow_int.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\sys_infnan.o ..\sys\infnan.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\sys_fdiv.o ..\sys\fdiv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\sys_fcmp.o ..\sys\fcmp.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\sys_ldfrexp.o ..\sys\ldfrexp.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\test_results.o ..\test\results.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\vector_init.o ..\vector\init.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\vector_file.o ..\vector\file.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\vector_vector.o ..\vector\vector.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\vector_copy.o ..\vector\copy.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\vector_swap.o ..\vector\swap.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\vector_prop.o ..\vector\prop.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\vector_minmax.o ..\vector\minmax.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\vector_oper.o ..\vector\oper.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\vector_reim.o ..\vector\reim.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\vector_subvector.o ..\vector\subvector.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\vector_view.o ..\vector\view.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\wavelet_dwt.o ..\wavelet\dwt.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\wavelet_wavelet.o ..\wavelet\wavelet.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\wavelet_bspline.o ..\wavelet\bspline.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\wavelet_daubechies.o ..\wavelet\daubechies.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\wavelet_haar.o ..\wavelet\haar.c

REM Make libgsl debug library
cd .\Debug\mingw\temp
%_ARC% %_ARC_OPTS% ..\libgsl_d.a version.o blas_blas.o block_init.o block_file.o block_block.o cdf_beta.o cdf_betainv.o cdf_cauchy.o cdf_cauchyinv.o cdf_chisq.o cdf_chisqinv.o cdf_exponential.o cdf_exponentialinv.o cdf_exppow.o cdf_fdist.o cdf_fdistinv.o cdf_flat.o cdf_flatinv.o cdf_gamma.o cdf_gammainv.o cdf_gauss.o cdf_gaussinv.o cdf_gumbel1.o cdf_gumbel1inv.o cdf_gumbel2.o cdf_gumbel2inv.o cdf_laplace.o cdf_laplaceinv.o cdf_logistic.o cdf_logisticinv.o cdf_lognormal.o cdf_lognormalinv.o cdf_pareto.o cdf_paretoinv.o cdf_rayleigh.o cdf_rayleighinv.o cdf_tdist.o cdf_tdistinv.o cdf_weibull.o cdf_weibullinv.o cdf_binomial.o cdf_poisson.o cdf_geometric.o cdf_nbinomial.o cdf_pascal.o cdf_hypergeometric.o cheb_deriv.o cheb_eval.o cheb_init.o cheb_integ.o combination_init.o combination_file.o combination_combination.o complex_math.o deriv_deriv.o dht_dht.o diff_diff.o eigen_jacobi.o eigen_symm.o eigen_symmv.o eigen_herm.o eigen_hermv.o eigen_sort.o err_error.o err_stream.o err_message.o err_strerror.o fft_dft.o fft_fft.o fit_linear.o histogram_add.o histogram_get.o histogram_init.o histogram_params.o histogram_reset.o histogram_file.o histogram_pdf.o histogram_add2d.o histogram_get2d.o histogram_init2d.o histogram_params2d.o histogram_reset2d.o histogram_file2d.o histogram_pdf2d.o histogram_calloc_range.o histogram_calloc_range2d.o histogram_copy.o histogram_copy2d.o histogram_maxval.o histogram_maxval2d.o histogram_oper.o histogram_oper2d.o histogram_stat.o histogram_stat2d.o ieee-utils_print.o ieee-utils_make_rep.o ieee-utils_env.o ieee-utils_fp.o ieee-utils_read.o integration_qk15.o integration_qk21.o integration_qk31.o integration_qk41.o integration_qk51.o integration_qk61.o integration_qk.o integration_qng.o integration_qag.o integration_qags.o integration_qagp.o integration_workspace.o integration_qcheb.o integration_qawc.o integration_qmomo.o integration_qaws.o integration_qmomof.o integration_qawo.o integration_qawf.o interpolation_accel.o interpolation_akima.o interpolation_bsearch.o interpolation_cspline.o interpolation_interp.o interpolation_linear.o interpolation_spline.o interpolation_poly.o linalg_multiply.o linalg_exponential.o linalg_tridiag.o linalg_lu.o linalg_luc.o linalg_hh.o linalg_qr.o linalg_qrpt.o linalg_lq.o linalg_ptlq.o linalg_svd.o linalg_householder.o linalg_householdercomplex.o linalg_cholesky.o linalg_symmtd.o linalg_hermtd.o linalg_bidiag.o linalg_balance.o matrix_init.o matrix_matrix.o matrix_file.o matrix_rowcol.o matrix_swap.o matrix_copy.o matrix_minmax.o matrix_prop.o matrix_oper.o matrix_getset.o matrix_view.o matrix_submatrix.o min_fsolver.o min_golden.o min_brent.o min_convergence.o min_bracketing.o monte_miser.o monte_plain.o monte_vegas.o multifit_multilinear.o multifit_work.o multifit_lmder.o multifit_fsolver.o multifit_fdfsolver.o multifit_convergence.o multifit_gradient.o multifit_covar.o multimin_fdfminimizer.o multimin_steepest_descent.o multimin_conjugate_fr.o multimin_conjugate_pr.o multimin_convergence.o multimin_diff.o multimin_vector_bfgs.o multimin_fminimizer.o multimin_simplex.o multiroots_fdjac.o multiroots_fsolver.o multiroots_fdfsolver.o multiroots_convergence.o multiroots_newton.o multiroots_gnewton.o multiroots_dnewton.o multiroots_broyden.o multiroots_hybrid.o multiroots_hybridj.o ntuple_ntuple.o ode-initval_control.o ode-initval_cstd.o ode-initval_cscal.o ode-initval_evolve.o ode-initval_step.o ode-initval_rk2.o ode-initval_rk2imp.o ode-initval_rk2simp.o ode-initval_rk4.o ode-initval_rk4imp.o ode-initval_rkf45.o ode-initval_rk8pd.o ode-initval_rkck.o ode-initval_bsimp.o ode-initval_gear1.o ode-initval_gear2.o permutation_init.o permutation_file.o permutation_permutation.o permutation_permute.o permutation_canonical.o poly_dd.o poly_eval.o poly_solve_quadratic.o poly_solve_cubic.o poly_zsolve_quadratic.o poly_zsolve_cubic.o poly_zsolve.o poly_zsolve_init.o qrng_qrng.o qrng_niederreiter-2.o qrng_sobol.o randist_bernoulli.o randist_beta.o randist_bigauss.o randist_binomial.o randist_cauchy.o randist_chisq.o randist_dirichlet.o randist_discrete.o randist_erlang.o randist_exponential.o randist_exppow.o randist_fdist.o randist_flat.o randist_gamma.o randist_gauss.o randist_gausszig.o randist_gausstail.o randist_geometric.o randist_gumbel.o randist_hyperg.o randist_laplace.o randist_levy.o randist_logarithmic.o randist_logistic.o randist_lognormal.o randist_multinomial.o randist_nbinomial.o randist_pareto.o randist_pascal.o randist_poisson.o randist_rayleigh.o randist_shuffle.o randist_sphere.o randist_tdist.o randist_weibull.o randist_landau.o randist_binomial_tpe.o rng_borosh13.o rng_cmrg.o rng_coveyou.o rng_default.o rng_file.o rng_fishman18.o rng_fishman20.o rng_fishman2x.o rng_gfsr4.o rng_knuthran2.o rng_knuthran.o rng_lecuyer21.o rng_minstd.o rng_mrg.o rng_mt.o rng_r250.o rng_ran0.o rng_ran1.o rng_ran2.o rng_ran3.o rng_rand48.o rng_rand.o rng_random.o rng_randu.o rng_ranf.o rng_ranlux.o rng_ranlxd.o rng_ranlxs.o rng_ranmar.o rng_rng.o rng_slatec.o rng_taus.o rng_taus113.o rng_transputer.o rng_tt.o rng_types.o rng_uni32.o rng_uni.o rng_vax.o rng_waterman14.o rng_zuf.o roots_bisection.o roots_brent.o roots_falsepos.o roots_newton.o roots_secant.o roots_steffenson.o roots_convergence.o roots_fsolver.o roots_fdfsolver.o siman_siman.o sort_sort.o sort_sortind.o sort_sortvec.o sort_sortvecind.o sort_subset.o sort_subsetind.o specfunc_airy.o specfunc_airy_der.o specfunc_airy_zero.o specfunc_atanint.o specfunc_bessel.o specfunc_bessel_I0.o specfunc_bessel_I1.o specfunc_bessel_In.o specfunc_bessel_Inu.o specfunc_bessel_J0.o specfunc_bessel_J1.o specfunc_bessel_Jn.o specfunc_bessel_Jnu.o specfunc_bessel_K0.o specfunc_bessel_K1.o specfunc_bessel_Kn.o specfunc_bessel_Knu.o specfunc_bessel_Y0.o specfunc_bessel_Y1.o specfunc_bessel_Yn.o specfunc_bessel_Ynu.o specfunc_bessel_amp_phase.o specfunc_bessel_i.o specfunc_bessel_j.o specfunc_bessel_k.o specfunc_bessel_olver.o specfunc_bessel_temme.o specfunc_bessel_y.o specfunc_bessel_zero.o specfunc_bessel_sequence.o specfunc_beta.o specfunc_beta_inc.o specfunc_clausen.o specfunc_coulomb.o specfunc_coupling.o specfunc_coulomb_bound.o specfunc_dawson.o specfunc_debye.o specfunc_dilog.o specfunc_elementary.o specfunc_ellint.o specfunc_elljac.o specfunc_erfc.o specfunc_exp.o specfunc_expint.o specfunc_expint3.o specfunc_fermi_dirac.o specfunc_gegenbauer.o specfunc_gamma.o specfunc_gamma_inc.o specfunc_hyperg_0F1.o specfunc_hyperg_2F0.o specfunc_hyperg_1F1.o specfunc_hyperg_2F1.o specfunc_hyperg_U.o specfunc_hyperg.o specfunc_laguerre.o specfunc_lambert.o specfunc_legendre_H3d.o specfunc_legendre_Qn.o specfunc_legendre_con.o specfunc_legendre_poly.o specfunc_log.o specfunc_poch.o specfunc_pow_int.o specfunc_psi.o specfunc_result.o specfunc_shint.o specfunc_sinint.o specfunc_synchrotron.o specfunc_transport.o specfunc_trig.o specfunc_zeta.o statistics_mean.o statistics_variance.o statistics_absdev.o statistics_skew.o statistics_kurtosis.o statistics_lag1.o statistics_p_variance.o statistics_minmax.o statistics_ttest.o statistics_median.o statistics_covariance.o statistics_quantiles.o statistics_wmean.o statistics_wvariance.o statistics_wabsdev.o statistics_wskew.o statistics_wkurtosis.o sum_levin_u.o sum_levin_utrunc.o sum_work_u.o sum_work_utrunc.o sys_minmax.o sys_prec.o sys_hypot.o sys_log1p.o sys_expm1.o sys_coerce.o sys_invhyp.o sys_pow_int.o sys_infnan.o sys_fdiv.o sys_fcmp.o sys_ldfrexp.o test_results.o vector_init.o vector_file.o vector_vector.o vector_copy.o vector_swap.o vector_prop.o vector_minmax.o vector_oper.o vector_reim.o vector_subvector.o vector_view.o wavelet_dwt.o wavelet_wavelet.o wavelet_bspline.o wavelet_daubechies.o wavelet_haar.o
cd ..\..\..

REM Compile cblas (debug) sources
%_MKDIR% .\Debug\mingw\cblas
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\sasum.o ..\cblas\sasum.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\saxpy.o ..\cblas\saxpy.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\scasum.o ..\cblas\scasum.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\scnrm2.o ..\cblas\scnrm2.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\scopy.o ..\cblas\scopy.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\sdot.o ..\cblas\sdot.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\sdsdot.o ..\cblas\sdsdot.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\sgbmv.o ..\cblas\sgbmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\sgemm.o ..\cblas\sgemm.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\sgemv.o ..\cblas\sgemv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\sger.o ..\cblas\sger.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\snrm2.o ..\cblas\snrm2.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\srot.o ..\cblas\srot.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\srotg.o ..\cblas\srotg.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\srotm.o ..\cblas\srotm.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\srotmg.o ..\cblas\srotmg.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\ssbmv.o ..\cblas\ssbmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\sscal.o ..\cblas\sscal.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\sspmv.o ..\cblas\sspmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\sspr.o ..\cblas\sspr.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\sspr2.o ..\cblas\sspr2.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\sswap.o ..\cblas\sswap.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\ssymm.o ..\cblas\ssymm.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\ssymv.o ..\cblas\ssymv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\ssyr.o ..\cblas\ssyr.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\ssyr2.o ..\cblas\ssyr2.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\ssyr2k.o ..\cblas\ssyr2k.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\ssyrk.o ..\cblas\ssyrk.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\stbmv.o ..\cblas\stbmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\stbsv.o ..\cblas\stbsv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\stpmv.o ..\cblas\stpmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\stpsv.o ..\cblas\stpsv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\strmm.o ..\cblas\strmm.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\strmv.o ..\cblas\strmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\strsm.o ..\cblas\strsm.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\strsv.o ..\cblas\strsv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\dasum.o ..\cblas\dasum.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\daxpy.o ..\cblas\daxpy.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\dcopy.o ..\cblas\dcopy.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\ddot.o ..\cblas\ddot.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\dgbmv.o ..\cblas\dgbmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\dgemm.o ..\cblas\dgemm.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\dgemv.o ..\cblas\dgemv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\dger.o ..\cblas\dger.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\dnrm2.o ..\cblas\dnrm2.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\drot.o ..\cblas\drot.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\drotg.o ..\cblas\drotg.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\drotm.o ..\cblas\drotm.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\drotmg.o ..\cblas\drotmg.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\dsbmv.o ..\cblas\dsbmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\dscal.o ..\cblas\dscal.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\dsdot.o ..\cblas\dsdot.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\dspmv.o ..\cblas\dspmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\dspr.o ..\cblas\dspr.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\dspr2.o ..\cblas\dspr2.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\dswap.o ..\cblas\dswap.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\dsymm.o ..\cblas\dsymm.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\dsymv.o ..\cblas\dsymv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\dsyr.o ..\cblas\dsyr.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\dsyr2.o ..\cblas\dsyr2.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\dsyr2k.o ..\cblas\dsyr2k.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\dsyrk.o ..\cblas\dsyrk.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\dtbmv.o ..\cblas\dtbmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\dtbsv.o ..\cblas\dtbsv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\dtpmv.o ..\cblas\dtpmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\dtpsv.o ..\cblas\dtpsv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\dtrmm.o ..\cblas\dtrmm.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\dtrmv.o ..\cblas\dtrmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\dtrsm.o ..\cblas\dtrsm.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\dtrsv.o ..\cblas\dtrsv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\dzasum.o ..\cblas\dzasum.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\dznrm2.o ..\cblas\dznrm2.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\caxpy.o ..\cblas\caxpy.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\ccopy.o ..\cblas\ccopy.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cdotc_sub.o ..\cblas\cdotc_sub.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cdotu_sub.o ..\cblas\cdotu_sub.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cgbmv.o ..\cblas\cgbmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cgemm.o ..\cblas\cgemm.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cgemv.o ..\cblas\cgemv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cgerc.o ..\cblas\cgerc.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cgeru.o ..\cblas\cgeru.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\chbmv.o ..\cblas\chbmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\chemm.o ..\cblas\chemm.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\chemv.o ..\cblas\chemv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cher.o ..\cblas\cher.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cher2.o ..\cblas\cher2.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cher2k.o ..\cblas\cher2k.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cherk.o ..\cblas\cherk.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\chpmv.o ..\cblas\chpmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\chpr.o ..\cblas\chpr.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\chpr2.o ..\cblas\chpr2.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cscal.o ..\cblas\cscal.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\csscal.o ..\cblas\csscal.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cswap.o ..\cblas\cswap.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\csymm.o ..\cblas\csymm.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\csyr2k.o ..\cblas\csyr2k.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\csyrk.o ..\cblas\csyrk.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\ctbmv.o ..\cblas\ctbmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\ctbsv.o ..\cblas\ctbsv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\ctpmv.o ..\cblas\ctpmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\ctpsv.o ..\cblas\ctpsv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\ctrmm.o ..\cblas\ctrmm.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\ctrmv.o ..\cblas\ctrmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\ctrsm.o ..\cblas\ctrsm.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\ctrsv.o ..\cblas\ctrsv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\zaxpy.o ..\cblas\zaxpy.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\zcopy.o ..\cblas\zcopy.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\zdotc_sub.o ..\cblas\zdotc_sub.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\zdotu_sub.o ..\cblas\zdotu_sub.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\zdscal.o ..\cblas\zdscal.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\zgbmv.o ..\cblas\zgbmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\zgemm.o ..\cblas\zgemm.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\zgemv.o ..\cblas\zgemv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\zgerc.o ..\cblas\zgerc.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\zgeru.o ..\cblas\zgeru.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\zhbmv.o ..\cblas\zhbmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\zhemm.o ..\cblas\zhemm.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\zhemv.o ..\cblas\zhemv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\zher.o ..\cblas\zher.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\zher2.o ..\cblas\zher2.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\zher2k.o ..\cblas\zher2k.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\zherk.o ..\cblas\zherk.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\zhpmv.o ..\cblas\zhpmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\zhpr.o ..\cblas\zhpr.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\zhpr2.o ..\cblas\zhpr2.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\zscal.o ..\cblas\zscal.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\zswap.o ..\cblas\zswap.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\zsymm.o ..\cblas\zsymm.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\zsyr2k.o ..\cblas\zsyr2k.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\zsyrk.o ..\cblas\zsyrk.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\ztbmv.o ..\cblas\ztbmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\ztbsv.o ..\cblas\ztbsv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\ztpmv.o ..\cblas\ztpmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\ztpsv.o ..\cblas\ztpsv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\ztrmm.o ..\cblas\ztrmm.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\ztrmv.o ..\cblas\ztrmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\ztrsm.o ..\cblas\ztrsm.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\ztrsv.o ..\cblas\ztrsv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\icamax.o ..\cblas\icamax.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\idamax.o ..\cblas\idamax.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\isamax.o ..\cblas\isamax.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\izamax.o ..\cblas\izamax.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\xerbla.o ..\cblas\xerbla.c

REM Make cblas (debug) library
cd .\Debug\mingw\cblas
%_ARC% %_ARC_OPTS% libgslcblas_d.a sasum.o saxpy.o scasum.o scnrm2.o scopy.o sdot.o sdsdot.o sgbmv.o sgemm.o sgemv.o sger.o snrm2.o srot.o srotg.o srotm.o srotmg.o ssbmv.o sscal.o sspmv.o sspr.o sspr2.o sswap.o ssymm.o ssymv.o ssyr.o ssyr2.o ssyr2k.o ssyrk.o stbmv.o stbsv.o stpmv.o stpsv.o strmm.o strmv.o strsm.o strsv.o dasum.o daxpy.o dcopy.o ddot.o dgbmv.o dgemm.o dgemv.o dger.o dnrm2.o drot.o drotg.o drotm.o drotmg.o dsbmv.o dscal.o dsdot.o dspmv.o dspr.o dspr2.o dswap.o dsymm.o dsymv.o dsyr.o dsyr2.o dsyr2k.o dsyrk.o dtbmv.o dtbsv.o dtpmv.o dtpsv.o dtrmm.o dtrmv.o dtrsm.o dtrsv.o dzasum.o dznrm2.o caxpy.o ccopy.o cdotc_sub.o cdotu_sub.o cgbmv.o cgemm.o cgemv.o cgerc.o cgeru.o chbmv.o chemm.o chemv.o cher.o cher2.o cher2k.o cherk.o chpmv.o chpr.o chpr2.o cscal.o csscal.o cswap.o csymm.o csyr2k.o csyrk.o ctbmv.o ctbsv.o ctpmv.o ctpsv.o ctrmm.o ctrmv.o ctrsm.o ctrsv.o zaxpy.o zcopy.o zdotc_sub.o zdotu_sub.o zdscal.o zgbmv.o zgemm.o zgemv.o zgerc.o zgeru.o zhbmv.o zhemm.o zhemv.o zher.o zher2.o zher2k.o zherk.o zhpmv.o zhpr.o zhpr2.o zscal.o zswap.o zsymm.o zsyr2k.o zsyrk.o ztbmv.o ztbsv.o ztpmv.o ztpsv.o ztrmm.o ztrmv.o ztrsm.o ztrsv.o icamax.o idamax.o isamax.o izamax.o xerbla.o
cd ..\..\..

REM Compile libgsl dll (debug) sources
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dversion.o ..\version.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dblasblas.o ..\blas\blas.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dblockinit.o ..\block\init.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dblockfile.o ..\block\file.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dblockblock.o ..\block\block.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfbeta.o ..\cdf\beta.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfbetainv.o ..\cdf\betainv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfcauchy.o ..\cdf\cauchy.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfcauchyinv.o ..\cdf\cauchyinv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfchisq.o ..\cdf\chisq.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfchisqinv.o ..\cdf\chisqinv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfexponential.o ..\cdf\exponential.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfexponentialinv.o ..\cdf\exponentialinv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfexppow.o ..\cdf\exppow.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdffdist.o ..\cdf\fdist.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdffdistinv.o ..\cdf\fdistinv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfflat.o ..\cdf\flat.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfflatinv.o ..\cdf\flatinv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfgamma.o ..\cdf\gamma.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfgammainv.o ..\cdf\gammainv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfgauss.o ..\cdf\gauss.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfgaussinv.o ..\cdf\gaussinv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfgumbel1.o ..\cdf\gumbel1.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfgumbel1inv.o ..\cdf\gumbel1inv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfgumbel2.o ..\cdf\gumbel2.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfgumbel2inv.o ..\cdf\gumbel2inv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdflaplace.o ..\cdf\laplace.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdflaplaceinv.o ..\cdf\laplaceinv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdflogistic.o ..\cdf\logistic.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdflogisticinv.o ..\cdf\logisticinv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdflognormal.o ..\cdf\lognormal.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdflognormalinv.o ..\cdf\lognormalinv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfpareto.o ..\cdf\pareto.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfparetoinv.o ..\cdf\paretoinv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfrayleigh.o ..\cdf\rayleigh.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfrayleighinv.o ..\cdf\rayleighinv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdftdist.o ..\cdf\tdist.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdftdistinv.o ..\cdf\tdistinv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfweibull.o ..\cdf\weibull.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfweibullinv.o ..\cdf\weibullinv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfbinomial.o ..\cdf\binomial.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfpoisson.o ..\cdf\poisson.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfgeometric.o ..\cdf\geometric.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfnbinomial.o ..\cdf\nbinomial.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfpascal.o ..\cdf\pascal.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcdfhypergeometric.o ..\cdf\hypergeometric.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dchebderiv.o ..\cheb\deriv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dchebeval.o ..\cheb\eval.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dchebinit.o ..\cheb\init.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dchebinteg.o ..\cheb\integ.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcombinationinit.o ..\combination\init.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcombinationfile.o ..\combination\file.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcombinationcombination.o ..\combination\combination.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dcomplexmath.o ..\complex\math.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dderivderiv.o ..\deriv\deriv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ddhtdht.o ..\dht\dht.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ddiffdiff.o ..\diff\diff.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\deigenjacobi.o ..\eigen\jacobi.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\deigensymm.o ..\eigen\symm.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\deigensymmv.o ..\eigen\symmv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\deigenherm.o ..\eigen\herm.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\deigenhermv.o ..\eigen\hermv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\deigensort.o ..\eigen\sort.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\derrerror.o ..\err\error.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\derrstream.o ..\err\stream.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\derrmessage.o ..\err\message.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\derrstrerror.o ..\err\strerror.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dfftdft.o ..\fft\dft.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dfftfft.o ..\fft\fft.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dfitlinear.o ..\fit\linear.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dhistogramadd.o ..\histogram\add.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dhistogramget.o ..\histogram\get.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dhistograminit.o ..\histogram\init.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dhistogramparams.o ..\histogram\params.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dhistogramreset.o ..\histogram\reset.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dhistogramfile.o ..\histogram\file.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dhistogrampdf.o ..\histogram\pdf.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dhistogramadd2d.o ..\histogram\add2d.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dhistogramget2d.o ..\histogram\get2d.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dhistograminit2d.o ..\histogram\init2d.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dhistogramparams2d.o ..\histogram\params2d.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dhistogramreset2d.o ..\histogram\reset2d.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dhistogramfile2d.o ..\histogram\file2d.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dhistogrampdf2d.o ..\histogram\pdf2d.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dhistogramcalloc_range.o ..\histogram\calloc_range.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dhistogramcalloc_range2d.o ..\histogram\calloc_range2d.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dhistogramcopy.o ..\histogram\copy.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dhistogramcopy2d.o ..\histogram\copy2d.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dhistogrammaxval.o ..\histogram\maxval.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dhistogrammaxval2d.o ..\histogram\maxval2d.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dhistogramoper.o ..\histogram\oper.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dhistogramoper2d.o ..\histogram\oper2d.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dhistogramstat.o ..\histogram\stat.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dhistogramstat2d.o ..\histogram\stat2d.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dieee-utilsprint.o ..\ieee-utils\print.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dieee-utilsmake_rep.o ..\ieee-utils\make_rep.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dieee-utilsenv.o ..\ieee-utils\env.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dieee-utilsfp.o ..\ieee-utils\fp.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dieee-utilsread.o ..\ieee-utils\read.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dintegrationqk15.o ..\integration\qk15.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dintegrationqk21.o ..\integration\qk21.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dintegrationqk31.o ..\integration\qk31.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dintegrationqk41.o ..\integration\qk41.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dintegrationqk51.o ..\integration\qk51.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dintegrationqk61.o ..\integration\qk61.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dintegrationqk.o ..\integration\qk.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dintegrationqng.o ..\integration\qng.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dintegrationqag.o ..\integration\qag.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dintegrationqags.o ..\integration\qags.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dintegrationqagp.o ..\integration\qagp.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dintegrationworkspace.o ..\integration\workspace.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dintegrationqcheb.o ..\integration\qcheb.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dintegrationqawc.o ..\integration\qawc.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dintegrationqmomo.o ..\integration\qmomo.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dintegrationqaws.o ..\integration\qaws.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dintegrationqmomof.o ..\integration\qmomof.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dintegrationqawo.o ..\integration\qawo.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dintegrationqawf.o ..\integration\qawf.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dinterpolationaccel.o ..\interpolation\accel.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dinterpolationakima.o ..\interpolation\akima.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dinterpolationbsearch.o ..\interpolation\bsearch.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dinterpolationcspline.o ..\interpolation\cspline.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dinterpolationinterp.o ..\interpolation\interp.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dinterpolationlinear.o ..\interpolation\linear.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dinterpolationspline.o ..\interpolation\spline.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dinterpolationpoly.o ..\interpolation\poly.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dlinalgmultiply.o ..\linalg\multiply.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dlinalgexponential.o ..\linalg\exponential.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dlinalgtridiag.o ..\linalg\tridiag.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dlinalglu.o ..\linalg\lu.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dlinalgluc.o ..\linalg\luc.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dlinalghh.o ..\linalg\hh.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dlinalgqr.o ..\linalg\qr.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dlinalgqrpt.o ..\linalg\qrpt.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dlinalglq.o ..\linalg\lq.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dlinalgptlq.o ..\linalg\ptlq.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dlinalgsvd.o ..\linalg\svd.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dlinalghouseholder.o ..\linalg\householder.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dlinalghouseholdercomplex.o ..\linalg\householdercomplex.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dlinalgcholesky.o ..\linalg\cholesky.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dlinalgsymmtd.o ..\linalg\symmtd.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dlinalghermtd.o ..\linalg\hermtd.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dlinalgbidiag.o ..\linalg\bidiag.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dlinalgbalance.o ..\linalg\balance.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmatrixinit.o ..\matrix\init.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmatrixmatrix.o ..\matrix\matrix.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmatrixfile.o ..\matrix\file.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmatrixrowcol.o ..\matrix\rowcol.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmatrixswap.o ..\matrix\swap.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmatrixcopy.o ..\matrix\copy.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmatrixminmax.o ..\matrix\minmax.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmatrixprop.o ..\matrix\prop.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmatrixoper.o ..\matrix\oper.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmatrixgetset.o ..\matrix\getset.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmatrixview.o ..\matrix\view.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmatrixsubmatrix.o ..\matrix\submatrix.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dminfsolver.o ..\min\fsolver.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmingolden.o ..\min\golden.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dminbrent.o ..\min\brent.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dminconvergence.o ..\min\convergence.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dminbracketing.o ..\min\bracketing.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmontemiser.o ..\monte\miser.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmonteplain.o ..\monte\plain.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmontevegas.o ..\monte\vegas.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmultifitmultilinear.o ..\multifit\multilinear.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmultifitwork.o ..\multifit\work.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmultifitlmder.o ..\multifit\lmder.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmultifitfsolver.o ..\multifit\fsolver.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmultifitfdfsolver.o ..\multifit\fdfsolver.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmultifitconvergence.o ..\multifit\convergence.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmultifitgradient.o ..\multifit\gradient.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmultifitcovar.o ..\multifit\covar.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmultiminfdfminimizer.o ..\multimin\fdfminimizer.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmultiminsteepest_descent.o ..\multimin\steepest_descent.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmultiminconjugate_fr.o ..\multimin\conjugate_fr.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmultiminconjugate_pr.o ..\multimin\conjugate_pr.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmultiminconvergence.o ..\multimin\convergence.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmultimindiff.o ..\multimin\diff.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmultiminvector_bfgs.o ..\multimin\vector_bfgs.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmultiminfminimizer.o ..\multimin\fminimizer.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmultiminsimplex.o ..\multimin\simplex.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmultirootsfdjac.o ..\multiroots\fdjac.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmultirootsfsolver.o ..\multiroots\fsolver.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmultirootsfdfsolver.o ..\multiroots\fdfsolver.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmultirootsconvergence.o ..\multiroots\convergence.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmultirootsnewton.o ..\multiroots\newton.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmultirootsgnewton.o ..\multiroots\gnewton.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmultirootsdnewton.o ..\multiroots\dnewton.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmultirootsbroyden.o ..\multiroots\broyden.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmultirootshybrid.o ..\multiroots\hybrid.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dmultirootshybridj.o ..\multiroots\hybridj.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dntuplentuple.o ..\ntuple\ntuple.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dode-initvalcontrol.o ..\ode-initval\control.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dode-initvalcstd.o ..\ode-initval\cstd.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dode-initvalcscal.o ..\ode-initval\cscal.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dode-initvalevolve.o ..\ode-initval\evolve.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dode-initvalstep.o ..\ode-initval\step.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dode-initvalrk2.o ..\ode-initval\rk2.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dode-initvalrk2imp.o ..\ode-initval\rk2imp.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dode-initvalrk2simp.o ..\ode-initval\rk2simp.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dode-initvalrk4.o ..\ode-initval\rk4.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dode-initvalrk4imp.o ..\ode-initval\rk4imp.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dode-initvalrkf45.o ..\ode-initval\rkf45.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dode-initvalrk8pd.o ..\ode-initval\rk8pd.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dode-initvalrkck.o ..\ode-initval\rkck.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dode-initvalbsimp.o ..\ode-initval\bsimp.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dode-initvalgear1.o ..\ode-initval\gear1.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dode-initvalgear2.o ..\ode-initval\gear2.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dpermutationinit.o ..\permutation\init.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dpermutationfile.o ..\permutation\file.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dpermutationpermutation.o ..\permutation\permutation.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dpermutationpermute.o ..\permutation\permute.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dpermutationcanonical.o ..\permutation\canonical.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dpolydd.o ..\poly\dd.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dpolyeval.o ..\poly\eval.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dpolysolve_quadratic.o ..\poly\solve_quadratic.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dpolysolve_cubic.o ..\poly\solve_cubic.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dpolyzsolve_quadratic.o ..\poly\zsolve_quadratic.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dpolyzsolve_cubic.o ..\poly\zsolve_cubic.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dpolyzsolve.o ..\poly\zsolve.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dpolyzsolve_init.o ..\poly\zsolve_init.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dqrngqrng.o ..\qrng\qrng.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dqrngniederreiter-2.o ..\qrng\niederreiter-2.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dqrngsobol.o ..\qrng\sobol.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistbernoulli.o ..\randist\bernoulli.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistbeta.o ..\randist\beta.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistbigauss.o ..\randist\bigauss.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistbinomial.o ..\randist\binomial.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistcauchy.o ..\randist\cauchy.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistchisq.o ..\randist\chisq.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistdirichlet.o ..\randist\dirichlet.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistdiscrete.o ..\randist\discrete.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandisterlang.o ..\randist\erlang.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistexponential.o ..\randist\exponential.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistexppow.o ..\randist\exppow.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistfdist.o ..\randist\fdist.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistflat.o ..\randist\flat.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistgamma.o ..\randist\gamma.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistgauss.o ..\randist\gauss.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistgausszig.o ..\randist\gausszig.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistgausstail.o ..\randist\gausstail.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistgeometric.o ..\randist\geometric.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistgumbel.o ..\randist\gumbel.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandisthyperg.o ..\randist\hyperg.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistlaplace.o ..\randist\laplace.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistlevy.o ..\randist\levy.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistlogarithmic.o ..\randist\logarithmic.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistlogistic.o ..\randist\logistic.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistlognormal.o ..\randist\lognormal.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistmultinomial.o ..\randist\multinomial.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistnbinomial.o ..\randist\nbinomial.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistpareto.o ..\randist\pareto.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistpascal.o ..\randist\pascal.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistpoisson.o ..\randist\poisson.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistrayleigh.o ..\randist\rayleigh.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistshuffle.o ..\randist\shuffle.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistsphere.o ..\randist\sphere.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandisttdist.o ..\randist\tdist.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistweibull.o ..\randist\weibull.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistlandau.o ..\randist\landau.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drandistbinomial_tpe.o ..\randist\binomial_tpe.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngborosh13.o ..\rng\borosh13.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngcmrg.o ..\rng\cmrg.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngcoveyou.o ..\rng\coveyou.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngdefault.o ..\rng\default.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngfile.o ..\rng\file.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngfishman18.o ..\rng\fishman18.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngfishman20.o ..\rng\fishman20.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngfishman2x.o ..\rng\fishman2x.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drnggfsr4.o ..\rng\gfsr4.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngknuthran2.o ..\rng\knuthran2.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngknuthran.o ..\rng\knuthran.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drnglecuyer21.o ..\rng\lecuyer21.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngminstd.o ..\rng\minstd.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngmrg.o ..\rng\mrg.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngmt.o ..\rng\mt.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngr250.o ..\rng\r250.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngran0.o ..\rng\ran0.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngran1.o ..\rng\ran1.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngran2.o ..\rng\ran2.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngran3.o ..\rng\ran3.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngrand48.o ..\rng\rand48.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngrand.o ..\rng\rand.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngrandom.o ..\rng\random.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngrandu.o ..\rng\randu.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngranf.o ..\rng\ranf.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngranlux.o ..\rng\ranlux.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngranlxd.o ..\rng\ranlxd.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngranlxs.o ..\rng\ranlxs.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngranmar.o ..\rng\ranmar.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngrng.o ..\rng\rng.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngslatec.o ..\rng\slatec.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngtaus.o ..\rng\taus.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngtaus113.o ..\rng\taus113.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngtransputer.o ..\rng\transputer.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngtt.o ..\rng\tt.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngtypes.o ..\rng\types.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drnguni32.o ..\rng\uni32.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drnguni.o ..\rng\uni.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngvax.o ..\rng\vax.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngwaterman14.o ..\rng\waterman14.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drngzuf.o ..\rng\zuf.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drootsbisection.o ..\roots\bisection.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drootsbrent.o ..\roots\brent.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drootsfalsepos.o ..\roots\falsepos.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drootsnewton.o ..\roots\newton.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drootssecant.o ..\roots\secant.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drootssteffenson.o ..\roots\steffenson.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drootsconvergence.o ..\roots\convergence.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drootsfsolver.o ..\roots\fsolver.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\drootsfdfsolver.o ..\roots\fdfsolver.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dsimansiman.o ..\siman\siman.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dsortsort.o ..\sort\sort.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dsortsortind.o ..\sort\sortind.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dsortsortvec.o ..\sort\sortvec.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dsortsortvecind.o ..\sort\sortvecind.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dsortsubset.o ..\sort\subset.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dsortsubsetind.o ..\sort\subsetind.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncairy.o ..\specfunc\airy.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncairy_der.o ..\specfunc\airy_der.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncairy_zero.o ..\specfunc\airy_zero.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncatanint.o ..\specfunc\atanint.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncbessel.o ..\specfunc\bessel.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncbessel_I0.o ..\specfunc\bessel_I0.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncbessel_I1.o ..\specfunc\bessel_I1.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncbessel_In.o ..\specfunc\bessel_In.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncbessel_Inu.o ..\specfunc\bessel_Inu.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncbessel_J0.o ..\specfunc\bessel_J0.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncbessel_J1.o ..\specfunc\bessel_J1.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncbessel_Jn.o ..\specfunc\bessel_Jn.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncbessel_Jnu.o ..\specfunc\bessel_Jnu.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncbessel_K0.o ..\specfunc\bessel_K0.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncbessel_K1.o ..\specfunc\bessel_K1.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncbessel_Kn.o ..\specfunc\bessel_Kn.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncbessel_Knu.o ..\specfunc\bessel_Knu.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncbessel_Y0.o ..\specfunc\bessel_Y0.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncbessel_Y1.o ..\specfunc\bessel_Y1.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncbessel_Yn.o ..\specfunc\bessel_Yn.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncbessel_Ynu.o ..\specfunc\bessel_Ynu.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncbessel_amp_phase.o ..\specfunc\bessel_amp_phase.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncbessel_i.o ..\specfunc\bessel_i.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncbessel_j.o ..\specfunc\bessel_j.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncbessel_k.o ..\specfunc\bessel_k.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncbessel_olver.o ..\specfunc\bessel_olver.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncbessel_temme.o ..\specfunc\bessel_temme.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncbessel_y.o ..\specfunc\bessel_y.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncbessel_zero.o ..\specfunc\bessel_zero.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncbessel_sequence.o ..\specfunc\bessel_sequence.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncbeta.o ..\specfunc\beta.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncbeta_inc.o ..\specfunc\beta_inc.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncclausen.o ..\specfunc\clausen.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfunccoulomb.o ..\specfunc\coulomb.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfunccoupling.o ..\specfunc\coupling.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfunccoulomb_bound.o ..\specfunc\coulomb_bound.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncdawson.o ..\specfunc\dawson.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncdebye.o ..\specfunc\debye.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncdilog.o ..\specfunc\dilog.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncelementary.o ..\specfunc\elementary.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncellint.o ..\specfunc\ellint.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncelljac.o ..\specfunc\elljac.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncerfc.o ..\specfunc\erfc.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncexp.o ..\specfunc\exp.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncexpint.o ..\specfunc\expint.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncexpint3.o ..\specfunc\expint3.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncfermi_dirac.o ..\specfunc\fermi_dirac.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncgegenbauer.o ..\specfunc\gegenbauer.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncgamma.o ..\specfunc\gamma.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncgamma_inc.o ..\specfunc\gamma_inc.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfunchyperg_0F1.o ..\specfunc\hyperg_0F1.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfunchyperg_2F0.o ..\specfunc\hyperg_2F0.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfunchyperg_1F1.o ..\specfunc\hyperg_1F1.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfunchyperg_2F1.o ..\specfunc\hyperg_2F1.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfunchyperg_U.o ..\specfunc\hyperg_U.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfunchyperg.o ..\specfunc\hyperg.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfunclaguerre.o ..\specfunc\laguerre.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfunclambert.o ..\specfunc\lambert.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfunclegendre_H3d.o ..\specfunc\legendre_H3d.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfunclegendre_Qn.o ..\specfunc\legendre_Qn.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfunclegendre_con.o ..\specfunc\legendre_con.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfunclegendre_poly.o ..\specfunc\legendre_poly.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfunclog.o ..\specfunc\log.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncpoch.o ..\specfunc\poch.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncpow_int.o ..\specfunc\pow_int.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncpsi.o ..\specfunc\psi.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncresult.o ..\specfunc\result.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncshint.o ..\specfunc\shint.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncsinint.o ..\specfunc\sinint.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfuncsynchrotron.o ..\specfunc\synchrotron.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfunctransport.o ..\specfunc\transport.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfunctrig.o ..\specfunc\trig.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dspecfunczeta.o ..\specfunc\zeta.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dstatisticsmean.o ..\statistics\mean.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dstatisticsvariance.o ..\statistics\variance.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dstatisticsabsdev.o ..\statistics\absdev.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dstatisticsskew.o ..\statistics\skew.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dstatisticskurtosis.o ..\statistics\kurtosis.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dstatisticslag1.o ..\statistics\lag1.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dstatisticsp_variance.o ..\statistics\p_variance.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dstatisticsminmax.o ..\statistics\minmax.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dstatisticsttest.o ..\statistics\ttest.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dstatisticsmedian.o ..\statistics\median.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dstatisticscovariance.o ..\statistics\covariance.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dstatisticsquantiles.o ..\statistics\quantiles.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dstatisticswmean.o ..\statistics\wmean.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dstatisticswvariance.o ..\statistics\wvariance.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dstatisticswabsdev.o ..\statistics\wabsdev.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dstatisticswskew.o ..\statistics\wskew.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dstatisticswkurtosis.o ..\statistics\wkurtosis.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dsumlevin_u.o ..\sum\levin_u.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dsumlevin_utrunc.o ..\sum\levin_utrunc.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dsumwork_u.o ..\sum\work_u.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dsumwork_utrunc.o ..\sum\work_utrunc.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dsysminmax.o ..\sys\minmax.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dsysprec.o ..\sys\prec.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dsyshypot.o ..\sys\hypot.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dsyslog1p.o ..\sys\log1p.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dsysexpm1.o ..\sys\expm1.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dsyscoerce.o ..\sys\coerce.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dsysinvhyp.o ..\sys\invhyp.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dsyspow_int.o ..\sys\pow_int.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dsysinfnan.o ..\sys\infnan.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dsysfdiv.o ..\sys\fdiv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dsysfcmp.o ..\sys\fcmp.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dsysldfrexp.o ..\sys\ldfrexp.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dtestresults.o ..\test\results.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dvectorinit.o ..\vector\init.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dvectorfile.o ..\vector\file.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dvectorvector.o ..\vector\vector.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dvectorcopy.o ..\vector\copy.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dvectorswap.o ..\vector\swap.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dvectorprop.o ..\vector\prop.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dvectorminmax.o ..\vector\minmax.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dvectoroper.o ..\vector\oper.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dvectorreim.o ..\vector\reim.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dvectorsubvector.o ..\vector\subvector.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dvectorview.o ..\vector\view.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dwaveletdwt.o ..\wavelet\dwt.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dwaveletwavelet.o ..\wavelet\wavelet.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dwaveletbspline.o ..\wavelet\bspline.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dwaveletdaubechies.o ..\wavelet\daubechies.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dwavelethaar.o ..\wavelet\haar.c

REM Compile cblas dll (debug) sources
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_sasum_dll.o ..\cblas\sasum.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_saxpy_dll.o ..\cblas\saxpy.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_scasum_dll.o ..\cblas\scasum.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_scnrm2_dll.o ..\cblas\scnrm2.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_scopy_dll.o ..\cblas\scopy.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_sdot_dll.o ..\cblas\sdot.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_sdsdot_dll.o ..\cblas\sdsdot.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_sgbmv_dll.o ..\cblas\sgbmv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_sgemm_dll.o ..\cblas\sgemm.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_sgemv_dll.o ..\cblas\sgemv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_sger_dll.o ..\cblas\sger.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_snrm2_dll.o ..\cblas\snrm2.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_srot_dll.o ..\cblas\srot.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_srotg_dll.o ..\cblas\srotg.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_srotm_dll.o ..\cblas\srotm.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_srotmg_dll.o ..\cblas\srotmg.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_ssbmv_dll.o ..\cblas\ssbmv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_sscal_dll.o ..\cblas\sscal.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_sspmv_dll.o ..\cblas\sspmv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_sspr_dll.o ..\cblas\sspr.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_sspr2_dll.o ..\cblas\sspr2.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_sswap_dll.o ..\cblas\sswap.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_ssymm_dll.o ..\cblas\ssymm.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_ssymv_dll.o ..\cblas\ssymv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_ssyr_dll.o ..\cblas\ssyr.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_ssyr2_dll.o ..\cblas\ssyr2.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_ssyr2k_dll.o ..\cblas\ssyr2k.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_ssyrk_dll.o ..\cblas\ssyrk.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_stbmv_dll.o ..\cblas\stbmv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_stbsv_dll.o ..\cblas\stbsv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_stpmv_dll.o ..\cblas\stpmv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_stpsv_dll.o ..\cblas\stpsv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_strmm_dll.o ..\cblas\strmm.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_strmv_dll.o ..\cblas\strmv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_strsm_dll.o ..\cblas\strsm.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_strsv_dll.o ..\cblas\strsv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_dasum_dll.o ..\cblas\dasum.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_daxpy_dll.o ..\cblas\daxpy.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_dcopy_dll.o ..\cblas\dcopy.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_ddot_dll.o ..\cblas\ddot.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_dgbmv_dll.o ..\cblas\dgbmv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_dgemm_dll.o ..\cblas\dgemm.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_dgemv_dll.o ..\cblas\dgemv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_dger_dll.o ..\cblas\dger.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_dnrm2_dll.o ..\cblas\dnrm2.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_drot_dll.o ..\cblas\drot.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_drotg_dll.o ..\cblas\drotg.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_drotm_dll.o ..\cblas\drotm.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_drotmg_dll.o ..\cblas\drotmg.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_dsbmv_dll.o ..\cblas\dsbmv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_dscal_dll.o ..\cblas\dscal.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_dsdot_dll.o ..\cblas\dsdot.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_dspmv_dll.o ..\cblas\dspmv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_dspr_dll.o ..\cblas\dspr.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_dspr2_dll.o ..\cblas\dspr2.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_dswap_dll.o ..\cblas\dswap.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_dsymm_dll.o ..\cblas\dsymm.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_dsymv_dll.o ..\cblas\dsymv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_dsyr_dll.o ..\cblas\dsyr.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_dsyr2_dll.o ..\cblas\dsyr2.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_dsyr2k_dll.o ..\cblas\dsyr2k.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_dsyrk_dll.o ..\cblas\dsyrk.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_dtbmv_dll.o ..\cblas\dtbmv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_dtbsv_dll.o ..\cblas\dtbsv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_dtpmv_dll.o ..\cblas\dtpmv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_dtpsv_dll.o ..\cblas\dtpsv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_dtrmm_dll.o ..\cblas\dtrmm.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_dtrmv_dll.o ..\cblas\dtrmv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_dtrsm_dll.o ..\cblas\dtrsm.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_dtrsv_dll.o ..\cblas\dtrsv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_dzasum_dll.o ..\cblas\dzasum.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_dznrm2_dll.o ..\cblas\dznrm2.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_caxpy_dll.o ..\cblas\caxpy.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_ccopy_dll.o ..\cblas\ccopy.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_cdotc_sub_dll.o ..\cblas\cdotc_sub.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_cdotu_sub_dll.o ..\cblas\cdotu_sub.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_cgbmv_dll.o ..\cblas\cgbmv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_cgemm_dll.o ..\cblas\cgemm.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_cgemv_dll.o ..\cblas\cgemv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_cgerc_dll.o ..\cblas\cgerc.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_cgeru_dll.o ..\cblas\cgeru.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_chbmv_dll.o ..\cblas\chbmv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_chemm_dll.o ..\cblas\chemm.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_chemv_dll.o ..\cblas\chemv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_cher_dll.o ..\cblas\cher.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_cher2_dll.o ..\cblas\cher2.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_cher2k_dll.o ..\cblas\cher2k.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_cherk_dll.o ..\cblas\cherk.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_chpmv_dll.o ..\cblas\chpmv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_chpr_dll.o ..\cblas\chpr.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_chpr2_dll.o ..\cblas\chpr2.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_cscal_dll.o ..\cblas\cscal.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_csscal_dll.o ..\cblas\csscal.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_cswap_dll.o ..\cblas\cswap.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_csymm_dll.o ..\cblas\csymm.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_csyr2k_dll.o ..\cblas\csyr2k.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_csyrk_dll.o ..\cblas\csyrk.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_ctbmv_dll.o ..\cblas\ctbmv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_ctbsv_dll.o ..\cblas\ctbsv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_ctpmv_dll.o ..\cblas\ctpmv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_ctpsv_dll.o ..\cblas\ctpsv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_ctrmm_dll.o ..\cblas\ctrmm.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_ctrmv_dll.o ..\cblas\ctrmv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_ctrsm_dll.o ..\cblas\ctrsm.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_ctrsv_dll.o ..\cblas\ctrsv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_zaxpy_dll.o ..\cblas\zaxpy.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_zcopy_dll.o ..\cblas\zcopy.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_zdotc_sub_dll.o ..\cblas\zdotc_sub.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_zdotu_sub_dll.o ..\cblas\zdotu_sub.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_zdscal_dll.o ..\cblas\zdscal.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_zgbmv_dll.o ..\cblas\zgbmv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_zgemm_dll.o ..\cblas\zgemm.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_zgemv_dll.o ..\cblas\zgemv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_zgerc_dll.o ..\cblas\zgerc.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_zgeru_dll.o ..\cblas\zgeru.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_zhbmv_dll.o ..\cblas\zhbmv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_zhemm_dll.o ..\cblas\zhemm.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_zhemv_dll.o ..\cblas\zhemv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_zher_dll.o ..\cblas\zher.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_zher2_dll.o ..\cblas\zher2.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_zher2k_dll.o ..\cblas\zher2k.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_zherk_dll.o ..\cblas\zherk.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_zhpmv_dll.o ..\cblas\zhpmv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_zhpr_dll.o ..\cblas\zhpr.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_zhpr2_dll.o ..\cblas\zhpr2.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_zscal_dll.o ..\cblas\zscal.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_zswap_dll.o ..\cblas\zswap.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_zsymm_dll.o ..\cblas\zsymm.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_zsyr2k_dll.o ..\cblas\zsyr2k.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_zsyrk_dll.o ..\cblas\zsyrk.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_ztbmv_dll.o ..\cblas\ztbmv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_ztbsv_dll.o ..\cblas\ztbsv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_ztpmv_dll.o ..\cblas\ztpmv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_ztpsv_dll.o ..\cblas\ztpsv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_ztrmm_dll.o ..\cblas\ztrmm.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_ztrmv_dll.o ..\cblas\ztrmv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_ztrsm_dll.o ..\cblas\ztrsm.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_ztrsv_dll.o ..\cblas\ztrsv.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_icamax_dll.o ..\cblas\icamax.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_idamax_dll.o ..\cblas\idamax.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_isamax_dll.o ..\cblas\isamax.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_izamax_dll.o ..\cblas\izamax.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_xerbla_dll.o ..\cblas\xerbla.c

REM Make the cblas dll (debug) library
cd .\Debug\mingw\cblas
%_COMPILE% %_DLL_LINK_FLAG%..\libgslcblas_d_dll.a %_COMP_OUTPUT_FLAG% ..\libgslcblas_d.dll cblas_sasum_dll.o cblas_saxpy_dll.o cblas_scasum_dll.o cblas_scnrm2_dll.o cblas_scopy_dll.o cblas_sdot_dll.o cblas_sdsdot_dll.o cblas_sgbmv_dll.o cblas_sgemm_dll.o cblas_sgemv_dll.o cblas_sger_dll.o cblas_snrm2_dll.o cblas_srot_dll.o cblas_srotg_dll.o cblas_srotm_dll.o cblas_srotmg_dll.o cblas_ssbmv_dll.o cblas_sscal_dll.o cblas_sspmv_dll.o cblas_sspr_dll.o cblas_sspr2_dll.o cblas_sswap_dll.o cblas_ssymm_dll.o cblas_ssymv_dll.o cblas_ssyr_dll.o cblas_ssyr2_dll.o cblas_ssyr2k_dll.o cblas_ssyrk_dll.o cblas_stbmv_dll.o cblas_stbsv_dll.o cblas_stpmv_dll.o cblas_stpsv_dll.o cblas_strmm_dll.o cblas_strmv_dll.o cblas_strsm_dll.o cblas_strsv_dll.o cblas_dasum_dll.o cblas_daxpy_dll.o cblas_dcopy_dll.o cblas_ddot_dll.o cblas_dgbmv_dll.o cblas_dgemm_dll.o cblas_dgemv_dll.o cblas_dger_dll.o cblas_dnrm2_dll.o cblas_drot_dll.o cblas_drotg_dll.o cblas_drotm_dll.o cblas_drotmg_dll.o cblas_dsbmv_dll.o cblas_dscal_dll.o cblas_dsdot_dll.o cblas_dspmv_dll.o cblas_dspr_dll.o cblas_dspr2_dll.o cblas_dswap_dll.o cblas_dsymm_dll.o cblas_dsymv_dll.o cblas_dsyr_dll.o cblas_dsyr2_dll.o cblas_dsyr2k_dll.o cblas_dsyrk_dll.o cblas_dtbmv_dll.o cblas_dtbsv_dll.o cblas_dtpmv_dll.o cblas_dtpsv_dll.o cblas_dtrmm_dll.o cblas_dtrmv_dll.o cblas_dtrsm_dll.o cblas_dtrsv_dll.o cblas_dzasum_dll.o cblas_dznrm2_dll.o cblas_caxpy_dll.o cblas_ccopy_dll.o cblas_cdotc_sub_dll.o cblas_cdotu_sub_dll.o cblas_cgbmv_dll.o cblas_cgemm_dll.o cblas_cgemv_dll.o cblas_cgerc_dll.o cblas_cgeru_dll.o cblas_chbmv_dll.o cblas_chemm_dll.o cblas_chemv_dll.o cblas_cher_dll.o cblas_cher2_dll.o cblas_cher2k_dll.o cblas_cherk_dll.o cblas_chpmv_dll.o cblas_chpr_dll.o cblas_chpr2_dll.o cblas_cscal_dll.o cblas_csscal_dll.o cblas_cswap_dll.o cblas_csymm_dll.o cblas_csyr2k_dll.o cblas_csyrk_dll.o cblas_ctbmv_dll.o cblas_ctbsv_dll.o cblas_ctpmv_dll.o cblas_ctpsv_dll.o cblas_ctrmm_dll.o cblas_ctrmv_dll.o cblas_ctrsm_dll.o cblas_ctrsv_dll.o cblas_zaxpy_dll.o cblas_zcopy_dll.o cblas_zdotc_sub_dll.o cblas_zdotu_sub_dll.o cblas_zdscal_dll.o cblas_zgbmv_dll.o cblas_zgemm_dll.o cblas_zgemv_dll.o cblas_zgerc_dll.o cblas_zgeru_dll.o cblas_zhbmv_dll.o cblas_zhemm_dll.o cblas_zhemv_dll.o cblas_zher_dll.o cblas_zher2_dll.o cblas_zher2k_dll.o cblas_zherk_dll.o cblas_zhpmv_dll.o cblas_zhpr_dll.o cblas_zhpr2_dll.o cblas_zscal_dll.o cblas_zswap_dll.o cblas_zsymm_dll.o cblas_zsyr2k_dll.o cblas_zsyrk_dll.o cblas_ztbmv_dll.o cblas_ztbsv_dll.o cblas_ztpmv_dll.o cblas_ztpsv_dll.o cblas_ztrmm_dll.o cblas_ztrmv_dll.o cblas_ztrsm_dll.o cblas_ztrsv_dll.o cblas_icamax_dll.o cblas_idamax_dll.o cblas_isamax_dll.o cblas_izamax_dll.o cblas_xerbla_dll.o
cd ..\..\..

REM Make the libgsl dll (debug) library
cd .\Debug\mingw\temp
%_COMPILE% %_DLL_LINK_FLAG%..\libgsl_d_dll.a ..\libgslcblas_d.dll %_COMP_OUTPUT_FLAG% ..\libgsl_d.dll dversion.o dblasblas.o dblockinit.o dblockfile.o dblockblock.o dcdfbeta.o dcdfbetainv.o dcdfcauchy.o dcdfcauchyinv.o dcdfchisq.o dcdfchisqinv.o dcdfexponential.o dcdfexponentialinv.o dcdfexppow.o dcdffdist.o dcdffdistinv.o dcdfflat.o dcdfflatinv.o dcdfgamma.o dcdfgammainv.o dcdfgauss.o dcdfgaussinv.o dcdfgumbel1.o dcdfgumbel1inv.o dcdfgumbel2.o dcdfgumbel2inv.o dcdflaplace.o dcdflaplaceinv.o dcdflogistic.o dcdflogisticinv.o dcdflognormal.o dcdflognormalinv.o dcdfpareto.o dcdfparetoinv.o dcdfrayleigh.o dcdfrayleighinv.o dcdftdist.o dcdftdistinv.o dcdfweibull.o dcdfweibullinv.o dcdfbinomial.o dcdfpoisson.o dcdfgeometric.o dcdfnbinomial.o dcdfpascal.o dcdfhypergeometric.o dchebderiv.o dchebeval.o dchebinit.o dchebinteg.o dcombinationinit.o dcombinationfile.o dcombinationcombination.o dcomplexmath.o dderivderiv.o ddhtdht.o ddiffdiff.o deigenjacobi.o deigensymm.o deigensymmv.o deigenherm.o deigenhermv.o deigensort.o derrerror.o derrstream.o derrmessage.o derrstrerror.o dfftdft.o dfftfft.o dfitlinear.o dhistogramadd.o dhistogramget.o dhistograminit.o dhistogramparams.o dhistogramreset.o dhistogramfile.o dhistogrampdf.o dhistogramadd2d.o dhistogramget2d.o dhistograminit2d.o dhistogramparams2d.o dhistogramreset2d.o dhistogramfile2d.o dhistogrampdf2d.o dhistogramcalloc_range.o dhistogramcalloc_range2d.o dhistogramcopy.o dhistogramcopy2d.o dhistogrammaxval.o dhistogrammaxval2d.o dhistogramoper.o dhistogramoper2d.o dhistogramstat.o dhistogramstat2d.o dieee-utilsprint.o dieee-utilsmake_rep.o dieee-utilsenv.o dieee-utilsfp.o dieee-utilsread.o dintegrationqk15.o dintegrationqk21.o dintegrationqk31.o dintegrationqk41.o dintegrationqk51.o dintegrationqk61.o dintegrationqk.o dintegrationqng.o dintegrationqag.o dintegrationqags.o dintegrationqagp.o dintegrationworkspace.o dintegrationqcheb.o dintegrationqawc.o dintegrationqmomo.o dintegrationqaws.o dintegrationqmomof.o dintegrationqawo.o dintegrationqawf.o dinterpolationaccel.o dinterpolationakima.o dinterpolationbsearch.o dinterpolationcspline.o dinterpolationinterp.o dinterpolationlinear.o dinterpolationspline.o dinterpolationpoly.o dlinalgmultiply.o dlinalgexponential.o dlinalgtridiag.o dlinalglu.o dlinalgluc.o dlinalghh.o dlinalgqr.o dlinalgqrpt.o dlinalglq.o dlinalgptlq.o dlinalgsvd.o dlinalghouseholder.o dlinalghouseholdercomplex.o dlinalgcholesky.o dlinalgsymmtd.o dlinalghermtd.o dlinalgbidiag.o dlinalgbalance.o dmatrixinit.o dmatrixmatrix.o dmatrixfile.o dmatrixrowcol.o dmatrixswap.o dmatrixcopy.o dmatrixminmax.o dmatrixprop.o dmatrixoper.o dmatrixgetset.o dmatrixview.o dmatrixsubmatrix.o dminfsolver.o dmingolden.o dminbrent.o dminconvergence.o dminbracketing.o dmontemiser.o dmonteplain.o dmontevegas.o dmultifitmultilinear.o dmultifitwork.o dmultifitlmder.o dmultifitfsolver.o dmultifitfdfsolver.o dmultifitconvergence.o dmultifitgradient.o dmultifitcovar.o dmultiminfdfminimizer.o dmultiminsteepest_descent.o dmultiminconjugate_fr.o dmultiminconjugate_pr.o dmultiminconvergence.o dmultimindiff.o dmultiminvector_bfgs.o dmultiminfminimizer.o dmultiminsimplex.o dmultirootsfdjac.o dmultirootsfsolver.o dmultirootsfdfsolver.o dmultirootsconvergence.o dmultirootsnewton.o dmultirootsgnewton.o dmultirootsdnewton.o dmultirootsbroyden.o dmultirootshybrid.o dmultirootshybridj.o dntuplentuple.o dode-initvalcontrol.o dode-initvalcstd.o dode-initvalcscal.o dode-initvalevolve.o dode-initvalstep.o dode-initvalrk2.o dode-initvalrk2imp.o dode-initvalrk2simp.o dode-initvalrk4.o dode-initvalrk4imp.o dode-initvalrkf45.o dode-initvalrk8pd.o dode-initvalrkck.o dode-initvalbsimp.o dode-initvalgear1.o dode-initvalgear2.o dpermutationinit.o dpermutationfile.o dpermutationpermutation.o dpermutationpermute.o dpermutationcanonical.o dpolydd.o dpolyeval.o dpolysolve_quadratic.o dpolysolve_cubic.o dpolyzsolve_quadratic.o dpolyzsolve_cubic.o dpolyzsolve.o dpolyzsolve_init.o dqrngqrng.o dqrngniederreiter-2.o dqrngsobol.o drandistbernoulli.o drandistbeta.o drandistbigauss.o drandistbinomial.o drandistcauchy.o drandistchisq.o drandistdirichlet.o drandistdiscrete.o drandisterlang.o drandistexponential.o drandistexppow.o drandistfdist.o drandistflat.o drandistgamma.o drandistgauss.o drandistgausszig.o drandistgausstail.o drandistgeometric.o drandistgumbel.o drandisthyperg.o drandistlaplace.o drandistlevy.o drandistlogarithmic.o drandistlogistic.o drandistlognormal.o drandistmultinomial.o drandistnbinomial.o drandistpareto.o drandistpascal.o drandistpoisson.o drandistrayleigh.o drandistshuffle.o drandistsphere.o drandisttdist.o drandistweibull.o drandistlandau.o drandistbinomial_tpe.o drngborosh13.o drngcmrg.o drngcoveyou.o drngdefault.o drngfile.o drngfishman18.o drngfishman20.o drngfishman2x.o drnggfsr4.o drngknuthran2.o drngknuthran.o drnglecuyer21.o drngminstd.o drngmrg.o drngmt.o drngr250.o drngran0.o drngran1.o drngran2.o drngran3.o drngrand48.o drngrand.o drngrandom.o drngrandu.o drngranf.o drngranlux.o drngranlxd.o drngranlxs.o drngranmar.o drngrng.o drngslatec.o drngtaus.o drngtaus113.o drngtransputer.o drngtt.o drngtypes.o drnguni32.o drnguni.o drngvax.o drngwaterman14.o drngzuf.o drootsbisection.o drootsbrent.o drootsfalsepos.o drootsnewton.o drootssecant.o drootssteffenson.o drootsconvergence.o drootsfsolver.o drootsfdfsolver.o dsimansiman.o dsortsort.o dsortsortind.o dsortsortvec.o dsortsortvecind.o dsortsubset.o dsortsubsetind.o dspecfuncairy.o dspecfuncairy_der.o dspecfuncairy_zero.o dspecfuncatanint.o dspecfuncbessel.o dspecfuncbessel_I0.o dspecfuncbessel_I1.o dspecfuncbessel_In.o dspecfuncbessel_Inu.o dspecfuncbessel_J0.o dspecfuncbessel_J1.o dspecfuncbessel_Jn.o dspecfuncbessel_Jnu.o dspecfuncbessel_K0.o dspecfuncbessel_K1.o dspecfuncbessel_Kn.o dspecfuncbessel_Knu.o dspecfuncbessel_Y0.o dspecfuncbessel_Y1.o dspecfuncbessel_Yn.o dspecfuncbessel_Ynu.o dspecfuncbessel_amp_phase.o dspecfuncbessel_i.o dspecfuncbessel_j.o dspecfuncbessel_k.o dspecfuncbessel_olver.o dspecfuncbessel_temme.o dspecfuncbessel_y.o dspecfuncbessel_zero.o dspecfuncbessel_sequence.o dspecfuncbeta.o dspecfuncbeta_inc.o dspecfuncclausen.o dspecfunccoulomb.o dspecfunccoupling.o dspecfunccoulomb_bound.o dspecfuncdawson.o dspecfuncdebye.o dspecfuncdilog.o dspecfuncelementary.o dspecfuncellint.o dspecfuncelljac.o dspecfuncerfc.o dspecfuncexp.o dspecfuncexpint.o dspecfuncexpint3.o dspecfuncfermi_dirac.o dspecfuncgegenbauer.o dspecfuncgamma.o dspecfuncgamma_inc.o dspecfunchyperg_0F1.o dspecfunchyperg_2F0.o dspecfunchyperg_1F1.o dspecfunchyperg_2F1.o dspecfunchyperg_U.o dspecfunchyperg.o dspecfunclaguerre.o dspecfunclambert.o dspecfunclegendre_H3d.o dspecfunclegendre_Qn.o dspecfunclegendre_con.o dspecfunclegendre_poly.o dspecfunclog.o dspecfuncpoch.o dspecfuncpow_int.o dspecfuncpsi.o dspecfuncresult.o dspecfuncshint.o dspecfuncsinint.o dspecfuncsynchrotron.o dspecfunctransport.o dspecfunctrig.o dspecfunczeta.o dstatisticsmean.o dstatisticsvariance.o dstatisticsabsdev.o dstatisticsskew.o dstatisticskurtosis.o dstatisticslag1.o dstatisticsp_variance.o dstatisticsminmax.o dstatisticsttest.o dstatisticsmedian.o dstatisticscovariance.o dstatisticsquantiles.o dstatisticswmean.o dstatisticswvariance.o dstatisticswabsdev.o dstatisticswskew.o dstatisticswkurtosis.o dsumlevin_u.o dsumlevin_utrunc.o dsumwork_u.o dsumwork_utrunc.o dsysminmax.o dsysprec.o dsyshypot.o dsyslog1p.o dsysexpm1.o dsyscoerce.o dsysinvhyp.o dsyspow_int.o dsysinfnan.o dsysfdiv.o dsysfcmp.o dsysldfrexp.o dtestresults.o dvectorinit.o dvectorfile.o dvectorvector.o dvectorcopy.o dvectorswap.o dvectorprop.o dvectorminmax.o dvectoroper.o dvectorreim.o dvectorsubvector.o dvectorview.o dwaveletdwt.o dwaveletwavelet.o dwaveletbspline.o dwaveletdaubechies.o dwavelethaar.o
cd ..\..\..

REM Compile cblas test (debug) sources
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test.o ..\cblas\test.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_amax.o ..\cblas\test_amax.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_asum.o ..\cblas\test_asum.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_axpy.o ..\cblas\test_axpy.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_copy.o ..\cblas\test_copy.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_dot.o ..\cblas\test_dot.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_gbmv.o ..\cblas\test_gbmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_gemm.o ..\cblas\test_gemm.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_gemv.o ..\cblas\test_gemv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_ger.o ..\cblas\test_ger.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_hbmv.o ..\cblas\test_hbmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_hemm.o ..\cblas\test_hemm.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_hemv.o ..\cblas\test_hemv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_her.o ..\cblas\test_her.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_her2.o ..\cblas\test_her2.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_her2k.o ..\cblas\test_her2k.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_herk.o ..\cblas\test_herk.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_hpmv.o ..\cblas\test_hpmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_hpr.o ..\cblas\test_hpr.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_hpr2.o ..\cblas\test_hpr2.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_nrm2.o ..\cblas\test_nrm2.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_rot.o ..\cblas\test_rot.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_rotg.o ..\cblas\test_rotg.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_rotm.o ..\cblas\test_rotm.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_rotmg.o ..\cblas\test_rotmg.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_sbmv.o ..\cblas\test_sbmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_scal.o ..\cblas\test_scal.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_spmv.o ..\cblas\test_spmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_spr.o ..\cblas\test_spr.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_spr2.o ..\cblas\test_spr2.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_swap.o ..\cblas\test_swap.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_symm.o ..\cblas\test_symm.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_symv.o ..\cblas\test_symv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_syr.o ..\cblas\test_syr.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_syr2.o ..\cblas\test_syr2.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_syr2k.o ..\cblas\test_syr2k.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_syrk.o ..\cblas\test_syrk.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_tbmv.o ..\cblas\test_tbmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_tbsv.o ..\cblas\test_tbsv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_tpmv.o ..\cblas\test_tpmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_tpsv.o ..\cblas\test_tpsv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_trmm.o ..\cblas\test_trmm.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_trmv.o ..\cblas\test_trmv.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_trsm.o ..\cblas\test_trsm.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\cblas\cblas_test_trsv.o ..\cblas\test_trsv.c

REM Make cblas test (debug) executables
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_cblas.exe .\Debug\mingw\cblas\cblas_test.o .\Debug\mingw\cblas\cblas_test_amax.o .\Debug\mingw\cblas\cblas_test_asum.o .\Debug\mingw\cblas\cblas_test_axpy.o .\Debug\mingw\cblas\cblas_test_copy.o .\Debug\mingw\cblas\cblas_test_dot.o .\Debug\mingw\cblas\cblas_test_gbmv.o .\Debug\mingw\cblas\cblas_test_gemm.o .\Debug\mingw\cblas\cblas_test_gemv.o .\Debug\mingw\cblas\cblas_test_ger.o .\Debug\mingw\cblas\cblas_test_hbmv.o .\Debug\mingw\cblas\cblas_test_hemm.o .\Debug\mingw\cblas\cblas_test_hemv.o .\Debug\mingw\cblas\cblas_test_her.o .\Debug\mingw\cblas\cblas_test_her2.o .\Debug\mingw\cblas\cblas_test_her2k.o .\Debug\mingw\cblas\cblas_test_herk.o .\Debug\mingw\cblas\cblas_test_hpmv.o .\Debug\mingw\cblas\cblas_test_hpr.o .\Debug\mingw\cblas\cblas_test_hpr2.o .\Debug\mingw\cblas\cblas_test_nrm2.o .\Debug\mingw\cblas\cblas_test_rot.o .\Debug\mingw\cblas\cblas_test_rotg.o .\Debug\mingw\cblas\cblas_test_rotm.o .\Debug\mingw\cblas\cblas_test_rotmg.o .\Debug\mingw\cblas\cblas_test_sbmv.o .\Debug\mingw\cblas\cblas_test_scal.o .\Debug\mingw\cblas\cblas_test_spmv.o .\Debug\mingw\cblas\cblas_test_spr.o .\Debug\mingw\cblas\cblas_test_spr2.o .\Debug\mingw\cblas\cblas_test_swap.o .\Debug\mingw\cblas\cblas_test_symm.o .\Debug\mingw\cblas\cblas_test_symv.o .\Debug\mingw\cblas\cblas_test_syr.o .\Debug\mingw\cblas\cblas_test_syr2.o .\Debug\mingw\cblas\cblas_test_syr2k.o .\Debug\mingw\cblas\cblas_test_syrk.o .\Debug\mingw\cblas\cblas_test_tbmv.o .\Debug\mingw\cblas\cblas_test_tbsv.o .\Debug\mingw\cblas\cblas_test_tpmv.o .\Debug\mingw\cblas\cblas_test_tpsv.o .\Debug\mingw\cblas\cblas_test_trmm.o .\Debug\mingw\cblas\cblas_test_trmv.o .\Debug\mingw\cblas\cblas_test_trsm.o .\Debug\mingw\cblas\cblas_test_trsv.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_cblas_dll.exe .\Debug\mingw\cblas\cblas_test.o .\Debug\mingw\cblas\cblas_test_amax.o .\Debug\mingw\cblas\cblas_test_asum.o .\Debug\mingw\cblas\cblas_test_axpy.o .\Debug\mingw\cblas\cblas_test_copy.o .\Debug\mingw\cblas\cblas_test_dot.o .\Debug\mingw\cblas\cblas_test_gbmv.o .\Debug\mingw\cblas\cblas_test_gemm.o .\Debug\mingw\cblas\cblas_test_gemv.o .\Debug\mingw\cblas\cblas_test_ger.o .\Debug\mingw\cblas\cblas_test_hbmv.o .\Debug\mingw\cblas\cblas_test_hemm.o .\Debug\mingw\cblas\cblas_test_hemv.o .\Debug\mingw\cblas\cblas_test_her.o .\Debug\mingw\cblas\cblas_test_her2.o .\Debug\mingw\cblas\cblas_test_her2k.o .\Debug\mingw\cblas\cblas_test_herk.o .\Debug\mingw\cblas\cblas_test_hpmv.o .\Debug\mingw\cblas\cblas_test_hpr.o .\Debug\mingw\cblas\cblas_test_hpr2.o .\Debug\mingw\cblas\cblas_test_nrm2.o .\Debug\mingw\cblas\cblas_test_rot.o .\Debug\mingw\cblas\cblas_test_rotg.o .\Debug\mingw\cblas\cblas_test_rotm.o .\Debug\mingw\cblas\cblas_test_rotmg.o .\Debug\mingw\cblas\cblas_test_sbmv.o .\Debug\mingw\cblas\cblas_test_scal.o .\Debug\mingw\cblas\cblas_test_spmv.o .\Debug\mingw\cblas\cblas_test_spr.o .\Debug\mingw\cblas\cblas_test_spr2.o .\Debug\mingw\cblas\cblas_test_swap.o .\Debug\mingw\cblas\cblas_test_symm.o .\Debug\mingw\cblas\cblas_test_symv.o .\Debug\mingw\cblas\cblas_test_syr.o .\Debug\mingw\cblas\cblas_test_syr2.o .\Debug\mingw\cblas\cblas_test_syr2k.o .\Debug\mingw\cblas\cblas_test_syrk.o .\Debug\mingw\cblas\cblas_test_tbmv.o .\Debug\mingw\cblas\cblas_test_tbsv.o .\Debug\mingw\cblas\cblas_test_tpmv.o .\Debug\mingw\cblas\cblas_test_tpsv.o .\Debug\mingw\cblas\cblas_test_trmm.o .\Debug\mingw\cblas\cblas_test_trmv.o .\Debug\mingw\cblas\cblas_test_trsm.o .\Debug\mingw\cblas\cblas_test_trsv.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

REM Make libgsl test (debug) executables
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\block_test.o ..\block\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_block.exe .\Debug\mingw\temp\block_test.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_block_dll.exe .\Debug\mingw\temp\block_test.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cdf_test.o ..\cdf\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_cdf.exe .\Debug\mingw\temp\cdf_test.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_cdf_dll.exe .\Debug\mingw\temp\cdf_test.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\cheb_test.o ..\cheb\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_cheb.exe .\Debug\mingw\temp\cheb_test.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_cheb_dll.exe .\Debug\mingw\temp\cheb_test.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\combination_test.o ..\combination\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_combination.exe .\Debug\mingw\temp\combination_test.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_combination_dll.exe .\Debug\mingw\temp\combination_test.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\complex_test.o ..\complex\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_complex.exe .\Debug\mingw\temp\complex_test.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_complex_dll.exe .\Debug\mingw\temp\complex_test.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\const_test.o ..\const\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_const.exe .\Debug\mingw\temp\const_test.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_const_dll.exe .\Debug\mingw\temp\const_test.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\deriv_test.o ..\deriv\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_deriv.exe .\Debug\mingw\temp\deriv_test.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_deriv_dll.exe .\Debug\mingw\temp\deriv_test.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\dht_test.o ..\dht\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_dht.exe .\Debug\mingw\temp\dht_test.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_dht_dll.exe .\Debug\mingw\temp\dht_test.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\diff_test.o ..\diff\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_diff.exe .\Debug\mingw\temp\diff_test.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_diff_dll.exe .\Debug\mingw\temp\diff_test.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\eigen_test.o ..\eigen\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_eigen.exe .\Debug\mingw\temp\eigen_test.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_eigen_dll.exe .\Debug\mingw\temp\eigen_test.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\fft_test.o ..\fft\test.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\fft_signals.o ..\fft\signals.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_fft.exe .\Debug\mingw\temp\fft_test.o .\Debug\mingw\temp\fft_signals.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_fft_dll.exe .\Debug\mingw\temp\fft_test.o .\Debug\mingw\temp\fft_signals.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\fit_test.o ..\fit\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_fit.exe .\Debug\mingw\temp\fit_test.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_fit_dll.exe .\Debug\mingw\temp\fit_test.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_test.o ..\histogram\test.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_test1d.o ..\histogram\test1d.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_test2d.o ..\histogram\test2d.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_test1d_resample.o ..\histogram\test1d_resample.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_test2d_resample.o ..\histogram\test2d_resample.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_test1d_trap.o ..\histogram\test1d_trap.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\histogram_test2d_trap.o ..\histogram\test2d_trap.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_histogram.exe .\Debug\mingw\temp\histogram_test.o .\Debug\mingw\temp\histogram_test1d.o .\Debug\mingw\temp\histogram_test2d.o .\Debug\mingw\temp\histogram_test1d_resample.o .\Debug\mingw\temp\histogram_test2d_resample.o .\Debug\mingw\temp\histogram_test1d_trap.o .\Debug\mingw\temp\histogram_test2d_trap.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_histogram_dll.exe .\Debug\mingw\temp\histogram_test.o .\Debug\mingw\temp\histogram_test1d.o .\Debug\mingw\temp\histogram_test2d.o .\Debug\mingw\temp\histogram_test1d_resample.o .\Debug\mingw\temp\histogram_test2d_resample.o .\Debug\mingw\temp\histogram_test1d_trap.o .\Debug\mingw\temp\histogram_test2d_trap.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ieee-utils_test.o ..\ieee-utils\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_ieee-utils.exe .\Debug\mingw\temp\ieee-utils_test.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_ieee-utils_dll.exe .\Debug\mingw\temp\ieee-utils_test.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\integration_test.o ..\integration\test.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\integration_tests.o ..\integration\tests.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_integration.exe .\Debug\mingw\temp\integration_test.o .\Debug\mingw\temp\integration_tests.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_integration_dll.exe .\Debug\mingw\temp\integration_test.o .\Debug\mingw\temp\integration_tests.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\interpolation_test.o ..\interpolation\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_interpolation.exe .\Debug\mingw\temp\interpolation_test.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_interpolation_dll.exe .\Debug\mingw\temp\interpolation_test.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\linalg_test.o ..\linalg\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_linalg.exe .\Debug\mingw\temp\linalg_test.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_linalg_dll.exe .\Debug\mingw\temp\linalg_test.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\matrix_test.o ..\matrix\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_matrix.exe .\Debug\mingw\temp\matrix_test.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_matrix_dll.exe .\Debug\mingw\temp\matrix_test.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\min_test.o ..\min\test.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\min_test_funcs.o ..\min\test_funcs.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_min.exe .\Debug\mingw\temp\min_test.o .\Debug\mingw\temp\min_test_funcs.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_min_dll.exe .\Debug\mingw\temp\min_test.o .\Debug\mingw\temp\min_test_funcs.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\monte_test.o ..\monte\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_monte.exe .\Debug\mingw\temp\monte_test.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_monte_dll.exe .\Debug\mingw\temp\monte_test.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multifit_test.o ..\multifit\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_multifit.exe .\Debug\mingw\temp\multifit_test.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_multifit_dll.exe .\Debug\mingw\temp\multifit_test.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multimin_test.o ..\multimin\test.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multimin_test_funcs.o ..\multimin\test_funcs.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_multimin.exe .\Debug\mingw\temp\multimin_test.o .\Debug\mingw\temp\multimin_test_funcs.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_multimin_dll.exe .\Debug\mingw\temp\multimin_test.o .\Debug\mingw\temp\multimin_test_funcs.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multiroots_test.o ..\multiroots\test.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\multiroots_test_funcs.o ..\multiroots\test_funcs.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_multiroots.exe .\Debug\mingw\temp\multiroots_test.o .\Debug\mingw\temp\multiroots_test_funcs.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_multiroots_dll.exe .\Debug\mingw\temp\multiroots_test.o .\Debug\mingw\temp\multiroots_test_funcs.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ntuple_test.o ..\ntuple\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_ntuple.exe .\Debug\mingw\temp\ntuple_test.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_ntuple_dll.exe .\Debug\mingw\temp\ntuple_test.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ode-initval_test.o ..\ode-initval\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_ode-initval.exe .\Debug\mingw\temp\ode-initval_test.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_ode-initval_dll.exe .\Debug\mingw\temp\ode-initval_test.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\permutation_test.o ..\permutation\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_permutation.exe .\Debug\mingw\temp\permutation_test.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_permutation_dll.exe .\Debug\mingw\temp\permutation_test.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\poly_test.o ..\poly\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_poly.exe .\Debug\mingw\temp\poly_test.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_poly_dll.exe .\Debug\mingw\temp\poly_test.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\qrng_test.o ..\qrng\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_qrng.exe .\Debug\mingw\temp\qrng_test.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_qrng_dll.exe .\Debug\mingw\temp\qrng_test.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\randist_test.o ..\randist\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_randist.exe .\Debug\mingw\temp\randist_test.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_randist_dll.exe .\Debug\mingw\temp\randist_test.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\rng_test.o ..\rng\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_rng.exe .\Debug\mingw\temp\rng_test.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_rng_dll.exe .\Debug\mingw\temp\rng_test.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\roots_test.o ..\roots\test.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\roots_test_funcs.o ..\roots\test_funcs.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_roots.exe .\Debug\mingw\temp\roots_test.o .\Debug\mingw\temp\roots_test_funcs.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_roots_dll.exe .\Debug\mingw\temp\roots_test.o .\Debug\mingw\temp\roots_test_funcs.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\siman_test.o ..\siman\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_siman.exe .\Debug\mingw\temp\siman_test.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_siman_dll.exe .\Debug\mingw\temp\siman_test.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\sort_test.o ..\sort\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_sort.exe .\Debug\mingw\temp\sort_test.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_sort_dll.exe .\Debug\mingw\temp\sort_test.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_test_sf.o ..\specfunc\test_sf.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_test_airy.o ..\specfunc\test_airy.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_test_bessel.o ..\specfunc\test_bessel.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_test_coulomb.o ..\specfunc\test_coulomb.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_test_dilog.o ..\specfunc\test_dilog.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_test_gamma.o ..\specfunc\test_gamma.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_test_hyperg.o ..\specfunc\test_hyperg.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\specfunc_test_legendre.o ..\specfunc\test_legendre.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_specfunc.exe .\Debug\mingw\temp\specfunc_test_sf.o .\Debug\mingw\temp\specfunc_test_airy.o .\Debug\mingw\temp\specfunc_test_bessel.o .\Debug\mingw\temp\specfunc_test_coulomb.o .\Debug\mingw\temp\specfunc_test_dilog.o .\Debug\mingw\temp\specfunc_test_gamma.o .\Debug\mingw\temp\specfunc_test_hyperg.o .\Debug\mingw\temp\specfunc_test_legendre.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_specfunc_dll.exe .\Debug\mingw\temp\specfunc_test_sf.o .\Debug\mingw\temp\specfunc_test_airy.o .\Debug\mingw\temp\specfunc_test_bessel.o .\Debug\mingw\temp\specfunc_test_coulomb.o .\Debug\mingw\temp\specfunc_test_dilog.o .\Debug\mingw\temp\specfunc_test_gamma.o .\Debug\mingw\temp\specfunc_test_hyperg.o .\Debug\mingw\temp\specfunc_test_legendre.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\statistics_test.o ..\statistics\test.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\statistics_test_nist.o ..\statistics\test_nist.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_statistics.exe .\Debug\mingw\temp\statistics_test.o .\Debug\mingw\temp\statistics_test_nist.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_statistics_dll.exe .\Debug\mingw\temp\statistics_test.o .\Debug\mingw\temp\statistics_test_nist.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\sum_test.o ..\sum\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_sum.exe .\Debug\mingw\temp\sum_test.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_sum_dll.exe .\Debug\mingw\temp\sum_test.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\sys_test.o ..\sys\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_sys.exe .\Debug\mingw\temp\sys_test.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_sys_dll.exe .\Debug\mingw\temp\sys_test.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\vector_test.o ..\vector\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_vector.exe .\Debug\mingw\temp\vector_test.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_vector_dll.exe .\Debug\mingw\temp\vector_test.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\wavelet_test.o ..\wavelet\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_wavelet.exe .\Debug\mingw\temp\wavelet_test.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\test_wavelet_dll.exe .\Debug\mingw\temp\wavelet_test.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

REM Make special (debug) executables
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\gsl-randist.o ..\gsl-randist.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\gsl-randist.exe .\Debug\mingw\temp\gsl-randist.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\gsl-histogram.o ..\gsl-histogram.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\gsl-histogram.exe .\Debug\mingw\temp\gsl-histogram.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a

REM Make example (Debug) executables
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_blas.o ..\doc\examples\blas.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_blas.exe .\Debug\mingw\temp\ex_blas.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_blas_dll.exe .\Debug\mingw\temp\ex_blas.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_block.o ..\doc\examples\block.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_block.exe .\Debug\mingw\temp\ex_block.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_block_dll.exe .\Debug\mingw\temp\ex_block.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_cblas.o ..\doc\examples\cblas.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_cblas.exe .\Debug\mingw\temp\ex_cblas.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_cblas_dll.exe .\Debug\mingw\temp\ex_cblas.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_cdf.o ..\doc\examples\cdf.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_cdf.exe .\Debug\mingw\temp\ex_cdf.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_cdf_dll.exe .\Debug\mingw\temp\ex_cdf.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_cheb.o ..\doc\examples\cheb.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_cheb.exe .\Debug\mingw\temp\ex_cheb.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_cheb_dll.exe .\Debug\mingw\temp\ex_cheb.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_combination.o ..\doc\examples\combination.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_combination.exe .\Debug\mingw\temp\ex_combination.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_combination_dll.exe .\Debug\mingw\temp\ex_combination.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_const.o ..\doc\examples\const.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_const.exe .\Debug\mingw\temp\ex_const.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_const_dll.exe .\Debug\mingw\temp\ex_const.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_diff.o ..\doc\examples\diff.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_diff.exe .\Debug\mingw\temp\ex_diff.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_diff_dll.exe .\Debug\mingw\temp\ex_diff.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_dwt.o ..\doc\examples\dwt.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_dwt.exe .\Debug\mingw\temp\ex_dwt.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_dwt_dll.exe .\Debug\mingw\temp\ex_dwt.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_eigen.o ..\doc\examples\eigen.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_eigen.exe .\Debug\mingw\temp\ex_eigen.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_eigen_dll.exe .\Debug\mingw\temp\ex_eigen.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_fft.o ..\doc\examples\fft.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_fft.exe .\Debug\mingw\temp\ex_fft.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_fft_dll.exe .\Debug\mingw\temp\ex_fft.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_fftmr.o ..\doc\examples\fftmr.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_fftmr.exe .\Debug\mingw\temp\ex_fftmr.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_fftmr_dll.exe .\Debug\mingw\temp\ex_fftmr.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_fftreal.o ..\doc\examples\fftreal.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_fftreal.exe .\Debug\mingw\temp\ex_fftreal.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_fftreal_dll.exe .\Debug\mingw\temp\ex_fftreal.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_fitting.o ..\doc\examples\fitting.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_fitting.exe .\Debug\mingw\temp\ex_fitting.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_fitting_dll.exe .\Debug\mingw\temp\ex_fitting.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_fitting2.o ..\doc\examples\fitting2.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_fitting2.exe .\Debug\mingw\temp\ex_fitting2.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_fitting2_dll.exe .\Debug\mingw\temp\ex_fitting2.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_fitting3.o ..\doc\examples\fitting3.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_fitting3.exe .\Debug\mingw\temp\ex_fitting3.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_fitting3_dll.exe .\Debug\mingw\temp\ex_fitting3.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_histogram.o ..\doc\examples\histogram.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_histogram.exe .\Debug\mingw\temp\ex_histogram.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_histogram_dll.exe .\Debug\mingw\temp\ex_histogram.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_histogram2d.o ..\doc\examples\histogram2d.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_histogram2d.exe .\Debug\mingw\temp\ex_histogram2d.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_histogram2d_dll.exe .\Debug\mingw\temp\ex_histogram2d.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_ieee.o ..\doc\examples\ieee.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_ieee.exe .\Debug\mingw\temp\ex_ieee.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_ieee_dll.exe .\Debug\mingw\temp\ex_ieee.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_ieeeround.o ..\doc\examples\ieeeround.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_ieeeround.exe .\Debug\mingw\temp\ex_ieeeround.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_ieeeround_dll.exe .\Debug\mingw\temp\ex_ieeeround.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_integration.o ..\doc\examples\integration.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_integration.exe .\Debug\mingw\temp\ex_integration.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_integration_dll.exe .\Debug\mingw\temp\ex_integration.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_interp.o ..\doc\examples\interp.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_interp.exe .\Debug\mingw\temp\ex_interp.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_interp_dll.exe .\Debug\mingw\temp\ex_interp.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_interpp.o ..\doc\examples\interpp.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_interpp.exe .\Debug\mingw\temp\ex_interpp.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_interpp_dll.exe .\Debug\mingw\temp\ex_interpp.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_intro.o ..\doc\examples\intro.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_intro.exe .\Debug\mingw\temp\ex_intro.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_intro_dll.exe .\Debug\mingw\temp\ex_intro.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_linalglu.o ..\doc\examples\linalglu.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_linalglu.exe .\Debug\mingw\temp\ex_linalglu.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_linalglu_dll.exe .\Debug\mingw\temp\ex_linalglu.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_matrix.o ..\doc\examples\matrix.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_matrix.exe .\Debug\mingw\temp\ex_matrix.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_matrix_dll.exe .\Debug\mingw\temp\ex_matrix.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_matrixw.o ..\doc\examples\matrixw.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_matrixw.exe .\Debug\mingw\temp\ex_matrixw.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_matrixw_dll.exe .\Debug\mingw\temp\ex_matrixw.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_min.o ..\doc\examples\min.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_min.exe .\Debug\mingw\temp\ex_min.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_min_dll.exe .\Debug\mingw\temp\ex_min.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_monte.o ..\doc\examples\monte.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_monte.exe .\Debug\mingw\temp\ex_monte.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_monte_dll.exe .\Debug\mingw\temp\ex_monte.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_nlfit.o ..\doc\examples\nlfit.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_nlfit.exe .\Debug\mingw\temp\ex_nlfit.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_nlfit_dll.exe .\Debug\mingw\temp\ex_nlfit.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_ntupler.o ..\doc\examples\ntupler.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_ntupler.exe .\Debug\mingw\temp\ex_ntupler.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_ntupler_dll.exe .\Debug\mingw\temp\ex_ntupler.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_ntuplew.o ..\doc\examples\ntuplew.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_ntuplew.exe .\Debug\mingw\temp\ex_ntuplew.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_ntuplew_dll.exe .\Debug\mingw\temp\ex_ntuplew.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_ode-initval.o ..\doc\examples\ode-initval.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_ode-initval.exe .\Debug\mingw\temp\ex_ode-initval.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_ode-initval_dll.exe .\Debug\mingw\temp\ex_ode-initval.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

REM odefixed.c is not functional at this time (4-Jul-2006)
REM %_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_odefixed.o ..\doc\examples\odefixed.c
REM %_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_odefixed.exe .\Debug\mingw\temp\ex_odefixed.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
REM %_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_odefixed_dll.exe .\Debug\mingw\temp\ex_odefixed.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_permseq.o ..\doc\examples\permseq.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_permseq.exe .\Debug\mingw\temp\ex_permseq.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_permseq_dll.exe .\Debug\mingw\temp\ex_permseq.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_permshuffle.o ..\doc\examples\permshuffle.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_permshuffle.exe .\Debug\mingw\temp\ex_permshuffle.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_permshuffle_dll.exe .\Debug\mingw\temp\ex_permshuffle.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_polyroots.o ..\doc\examples\polyroots.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_polyroots.exe .\Debug\mingw\temp\ex_polyroots.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_polyroots_dll.exe .\Debug\mingw\temp\ex_polyroots.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_qrng.o ..\doc\examples\qrng.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_qrng.exe .\Debug\mingw\temp\ex_qrng.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_qrng_dll.exe .\Debug\mingw\temp\ex_qrng.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_randpoisson.o ..\doc\examples\randpoisson.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_randpoisson.exe .\Debug\mingw\temp\ex_randpoisson.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_randpoisson_dll.exe .\Debug\mingw\temp\ex_randpoisson.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_randwalk.o ..\doc\examples\randwalk.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_randwalk.exe .\Debug\mingw\temp\ex_randwalk.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_randwalk_dll.exe .\Debug\mingw\temp\ex_randwalk.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_rng.o ..\doc\examples\rng.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_rng.exe .\Debug\mingw\temp\ex_rng.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_rng_dll.exe .\Debug\mingw\temp\ex_rng.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_rngunif.o ..\doc\examples\rngunif.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_rngunif.exe .\Debug\mingw\temp\ex_rngunif.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_rngunif_dll.exe .\Debug\mingw\temp\ex_rngunif.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_rootnewt.o ..\doc\examples\rootnewt.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_rootnewt.exe .\Debug\mingw\temp\ex_rootnewt.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_rootnewt_dll.exe .\Debug\mingw\temp\ex_rootnewt.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_roots.o ..\doc\examples\roots.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_roots.exe .\Debug\mingw\temp\ex_roots.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_roots_dll.exe .\Debug\mingw\temp\ex_roots.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_siman.o ..\doc\examples\siman.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_siman.exe .\Debug\mingw\temp\ex_siman.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_siman_dll.exe .\Debug\mingw\temp\ex_siman.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_sortsmall.o ..\doc\examples\sortsmall.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_sortsmall.exe .\Debug\mingw\temp\ex_sortsmall.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_sortsmall_dll.exe .\Debug\mingw\temp\ex_sortsmall.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_specfun.o ..\doc\examples\specfun.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_specfun.exe .\Debug\mingw\temp\ex_specfun.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_specfun_dll.exe .\Debug\mingw\temp\ex_specfun.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_specfun_e.o ..\doc\examples\specfun_e.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_specfun_e.exe .\Debug\mingw\temp\ex_specfun_e.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_specfun_e_dll.exe .\Debug\mingw\temp\ex_specfun_e.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_stat.o ..\doc\examples\stat.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_stat.exe .\Debug\mingw\temp\ex_stat.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_stat_dll.exe .\Debug\mingw\temp\ex_stat.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_statsort.o ..\doc\examples\statsort.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_statsort.exe .\Debug\mingw\temp\ex_statsort.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_statsort_dll.exe .\Debug\mingw\temp\ex_statsort.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_sum.o ..\doc\examples\sum.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_sum.exe .\Debug\mingw\temp\ex_sum.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_sum_dll.exe .\Debug\mingw\temp\ex_sum.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_vector.o ..\doc\examples\vector.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_vector.exe .\Debug\mingw\temp\ex_vector.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_vector_dll.exe .\Debug\mingw\temp\ex_vector.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_vectorr.o ..\doc\examples\vectorr.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_vectorr.exe .\Debug\mingw\temp\ex_vectorr.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_vectorr_dll.exe .\Debug\mingw\temp\ex_vectorr.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_vectorview.o ..\doc\examples\vectorview.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_vectorview.exe .\Debug\mingw\temp\ex_vectorview.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_vectorview_dll.exe .\Debug\mingw\temp\ex_vectorview.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Debug\mingw\temp\ex_vectorw.o ..\doc\examples\vectorw.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_vectorw.exe .\Debug\mingw\temp\ex_vectorw.o .\Debug\mingw\libgsl_d.a .\Debug\mingw\cblas\libgslcblas_d.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Debug\mingw\ex_vectorw_dll.exe .\Debug\mingw\temp\ex_vectorw.o .\Debug\mingw\libgsl_d_dll.a .\Debug\mingw\libgslcblas_d_dll.a

REM Compile for Release

%_MKDIR% .\Release
%_MKDIR% .\Release\mingw
%_MKDIR% .\Release\mingw\temp

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\version.o ..\version.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\blas_blas.o ..\blas\blas.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\block_init.o ..\block\init.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\block_file.o ..\block\file.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\block_block.o ..\block\block.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_beta.o ..\cdf\beta.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_betainv.o ..\cdf\betainv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_cauchy.o ..\cdf\cauchy.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_cauchyinv.o ..\cdf\cauchyinv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_chisq.o ..\cdf\chisq.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_chisqinv.o ..\cdf\chisqinv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_exponential.o ..\cdf\exponential.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_exponentialinv.o ..\cdf\exponentialinv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_exppow.o ..\cdf\exppow.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_fdist.o ..\cdf\fdist.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_fdistinv.o ..\cdf\fdistinv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_flat.o ..\cdf\flat.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_flatinv.o ..\cdf\flatinv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_gamma.o ..\cdf\gamma.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_gammainv.o ..\cdf\gammainv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_gauss.o ..\cdf\gauss.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_gaussinv.o ..\cdf\gaussinv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_gumbel1.o ..\cdf\gumbel1.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_gumbel1inv.o ..\cdf\gumbel1inv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_gumbel2.o ..\cdf\gumbel2.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_gumbel2inv.o ..\cdf\gumbel2inv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_laplace.o ..\cdf\laplace.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_laplaceinv.o ..\cdf\laplaceinv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_logistic.o ..\cdf\logistic.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_logisticinv.o ..\cdf\logisticinv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_lognormal.o ..\cdf\lognormal.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_lognormalinv.o ..\cdf\lognormalinv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_pareto.o ..\cdf\pareto.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_paretoinv.o ..\cdf\paretoinv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_rayleigh.o ..\cdf\rayleigh.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_rayleighinv.o ..\cdf\rayleighinv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_tdist.o ..\cdf\tdist.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_tdistinv.o ..\cdf\tdistinv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_weibull.o ..\cdf\weibull.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_weibullinv.o ..\cdf\weibullinv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_binomial.o ..\cdf\binomial.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_poisson.o ..\cdf\poisson.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_geometric.o ..\cdf\geometric.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_nbinomial.o ..\cdf\nbinomial.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_pascal.o ..\cdf\pascal.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_hypergeometric.o ..\cdf\hypergeometric.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cheb_deriv.o ..\cheb\deriv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cheb_eval.o ..\cheb\eval.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cheb_init.o ..\cheb\init.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cheb_integ.o ..\cheb\integ.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\combination_init.o ..\combination\init.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\combination_file.o ..\combination\file.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\combination_combination.o ..\combination\combination.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\complex_math.o ..\complex\math.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\deriv_deriv.o ..\deriv\deriv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dht_dht.o ..\dht\dht.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\diff_diff.o ..\diff\diff.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\eigen_jacobi.o ..\eigen\jacobi.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\eigen_symm.o ..\eigen\symm.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\eigen_symmv.o ..\eigen\symmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\eigen_herm.o ..\eigen\herm.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\eigen_hermv.o ..\eigen\hermv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\eigen_sort.o ..\eigen\sort.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\err_error.o ..\err\error.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\err_stream.o ..\err\stream.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\err_message.o ..\err\message.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\err_strerror.o ..\err\strerror.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\fft_dft.o ..\fft\dft.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\fft_fft.o ..\fft\fft.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\fit_linear.o ..\fit\linear.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_add.o ..\histogram\add.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_get.o ..\histogram\get.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_init.o ..\histogram\init.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_params.o ..\histogram\params.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_reset.o ..\histogram\reset.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_file.o ..\histogram\file.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_pdf.o ..\histogram\pdf.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_add2d.o ..\histogram\add2d.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_get2d.o ..\histogram\get2d.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_init2d.o ..\histogram\init2d.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_params2d.o ..\histogram\params2d.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_reset2d.o ..\histogram\reset2d.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_file2d.o ..\histogram\file2d.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_pdf2d.o ..\histogram\pdf2d.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_calloc_range.o ..\histogram\calloc_range.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_calloc_range2d.o ..\histogram\calloc_range2d.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_copy.o ..\histogram\copy.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_copy2d.o ..\histogram\copy2d.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_maxval.o ..\histogram\maxval.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_maxval2d.o ..\histogram\maxval2d.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_oper.o ..\histogram\oper.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_oper2d.o ..\histogram\oper2d.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_stat.o ..\histogram\stat.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_stat2d.o ..\histogram\stat2d.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ieee-utils_print.o ..\ieee-utils\print.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ieee-utils_make_rep.o ..\ieee-utils\make_rep.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ieee-utils_env.o ..\ieee-utils\env.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ieee-utils_fp.o ..\ieee-utils\fp.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ieee-utils_read.o ..\ieee-utils\read.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\integration_qk15.o ..\integration\qk15.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\integration_qk21.o ..\integration\qk21.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\integration_qk31.o ..\integration\qk31.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\integration_qk41.o ..\integration\qk41.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\integration_qk51.o ..\integration\qk51.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\integration_qk61.o ..\integration\qk61.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\integration_qk.o ..\integration\qk.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\integration_qng.o ..\integration\qng.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\integration_qag.o ..\integration\qag.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\integration_qags.o ..\integration\qags.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\integration_qagp.o ..\integration\qagp.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\integration_workspace.o ..\integration\workspace.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\integration_qcheb.o ..\integration\qcheb.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\integration_qawc.o ..\integration\qawc.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\integration_qmomo.o ..\integration\qmomo.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\integration_qaws.o ..\integration\qaws.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\integration_qmomof.o ..\integration\qmomof.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\integration_qawo.o ..\integration\qawo.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\integration_qawf.o ..\integration\qawf.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\interpolation_accel.o ..\interpolation\accel.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\interpolation_akima.o ..\interpolation\akima.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\interpolation_bsearch.o ..\interpolation\bsearch.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\interpolation_cspline.o ..\interpolation\cspline.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\interpolation_interp.o ..\interpolation\interp.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\interpolation_linear.o ..\interpolation\linear.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\interpolation_spline.o ..\interpolation\spline.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\interpolation_poly.o ..\interpolation\poly.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\linalg_multiply.o ..\linalg\multiply.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\linalg_exponential.o ..\linalg\exponential.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\linalg_tridiag.o ..\linalg\tridiag.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\linalg_lu.o ..\linalg\lu.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\linalg_luc.o ..\linalg\luc.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\linalg_hh.o ..\linalg\hh.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\linalg_qr.o ..\linalg\qr.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\linalg_qrpt.o ..\linalg\qrpt.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\linalg_lq.o ..\linalg\lq.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\linalg_ptlq.o ..\linalg\ptlq.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\linalg_svd.o ..\linalg\svd.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\linalg_householder.o ..\linalg\householder.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\linalg_householdercomplex.o ..\linalg\householdercomplex.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\linalg_cholesky.o ..\linalg\cholesky.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\linalg_symmtd.o ..\linalg\symmtd.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\linalg_hermtd.o ..\linalg\hermtd.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\linalg_bidiag.o ..\linalg\bidiag.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\linalg_balance.o ..\linalg\balance.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\matrix_init.o ..\matrix\init.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\matrix_matrix.o ..\matrix\matrix.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\matrix_file.o ..\matrix\file.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\matrix_rowcol.o ..\matrix\rowcol.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\matrix_swap.o ..\matrix\swap.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\matrix_copy.o ..\matrix\copy.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\matrix_minmax.o ..\matrix\minmax.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\matrix_prop.o ..\matrix\prop.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\matrix_oper.o ..\matrix\oper.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\matrix_getset.o ..\matrix\getset.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\matrix_view.o ..\matrix\view.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\matrix_submatrix.o ..\matrix\submatrix.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\min_fsolver.o ..\min\fsolver.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\min_golden.o ..\min\golden.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\min_brent.o ..\min\brent.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\min_convergence.o ..\min\convergence.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\min_bracketing.o ..\min\bracketing.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\monte_miser.o ..\monte\miser.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\monte_plain.o ..\monte\plain.c
%_COMPILE% %_OPT_DEBUG% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\monte_vegas.o ..\monte\vegas.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multifit_multilinear.o ..\multifit\multilinear.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multifit_work.o ..\multifit\work.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multifit_lmder.o ..\multifit\lmder.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multifit_fsolver.o ..\multifit\fsolver.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multifit_fdfsolver.o ..\multifit\fdfsolver.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multifit_convergence.o ..\multifit\convergence.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multifit_gradient.o ..\multifit\gradient.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multifit_covar.o ..\multifit\covar.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multimin_fdfminimizer.o ..\multimin\fdfminimizer.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multimin_steepest_descent.o ..\multimin\steepest_descent.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multimin_conjugate_fr.o ..\multimin\conjugate_fr.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multimin_conjugate_pr.o ..\multimin\conjugate_pr.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multimin_convergence.o ..\multimin\convergence.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multimin_diff.o ..\multimin\diff.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multimin_vector_bfgs.o ..\multimin\vector_bfgs.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multimin_fminimizer.o ..\multimin\fminimizer.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multimin_simplex.o ..\multimin\simplex.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multiroots_fdjac.o ..\multiroots\fdjac.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multiroots_fsolver.o ..\multiroots\fsolver.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multiroots_fdfsolver.o ..\multiroots\fdfsolver.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multiroots_convergence.o ..\multiroots\convergence.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multiroots_newton.o ..\multiroots\newton.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multiroots_gnewton.o ..\multiroots\gnewton.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multiroots_dnewton.o ..\multiroots\dnewton.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multiroots_broyden.o ..\multiroots\broyden.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multiroots_hybrid.o ..\multiroots\hybrid.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multiroots_hybridj.o ..\multiroots\hybridj.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ntuple_ntuple.o ..\ntuple\ntuple.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ode-initval_control.o ..\ode-initval\control.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ode-initval_cstd.o ..\ode-initval\cstd.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ode-initval_cscal.o ..\ode-initval\cscal.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ode-initval_evolve.o ..\ode-initval\evolve.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ode-initval_step.o ..\ode-initval\step.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ode-initval_rk2.o ..\ode-initval\rk2.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ode-initval_rk2imp.o ..\ode-initval\rk2imp.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ode-initval_rk2simp.o ..\ode-initval\rk2simp.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ode-initval_rk4.o ..\ode-initval\rk4.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ode-initval_rk4imp.o ..\ode-initval\rk4imp.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ode-initval_rkf45.o ..\ode-initval\rkf45.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ode-initval_rk8pd.o ..\ode-initval\rk8pd.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ode-initval_rkck.o ..\ode-initval\rkck.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ode-initval_bsimp.o ..\ode-initval\bsimp.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ode-initval_gear1.o ..\ode-initval\gear1.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ode-initval_gear2.o ..\ode-initval\gear2.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\permutation_init.o ..\permutation\init.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\permutation_file.o ..\permutation\file.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\permutation_permutation.o ..\permutation\permutation.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\permutation_permute.o ..\permutation\permute.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\permutation_canonical.o ..\permutation\canonical.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\poly_dd.o ..\poly\dd.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\poly_eval.o ..\poly\eval.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\poly_solve_quadratic.o ..\poly\solve_quadratic.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\poly_solve_cubic.o ..\poly\solve_cubic.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\poly_zsolve_quadratic.o ..\poly\zsolve_quadratic.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\poly_zsolve_cubic.o ..\poly\zsolve_cubic.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\poly_zsolve.o ..\poly\zsolve.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\poly_zsolve_init.o ..\poly\zsolve_init.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\qrng_qrng.o ..\qrng\qrng.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\qrng_niederreiter-2.o ..\qrng\niederreiter-2.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\qrng_sobol.o ..\qrng\sobol.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_bernoulli.o ..\randist\bernoulli.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_beta.o ..\randist\beta.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_bigauss.o ..\randist\bigauss.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_binomial.o ..\randist\binomial.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_cauchy.o ..\randist\cauchy.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_chisq.o ..\randist\chisq.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_dirichlet.o ..\randist\dirichlet.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_discrete.o ..\randist\discrete.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_erlang.o ..\randist\erlang.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_exponential.o ..\randist\exponential.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_exppow.o ..\randist\exppow.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_fdist.o ..\randist\fdist.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_flat.o ..\randist\flat.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_gamma.o ..\randist\gamma.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_gauss.o ..\randist\gauss.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_gausszig.o ..\randist\gausszig.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_gausstail.o ..\randist\gausstail.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_geometric.o ..\randist\geometric.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_gumbel.o ..\randist\gumbel.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_hyperg.o ..\randist\hyperg.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_laplace.o ..\randist\laplace.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_levy.o ..\randist\levy.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_logarithmic.o ..\randist\logarithmic.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_logistic.o ..\randist\logistic.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_lognormal.o ..\randist\lognormal.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_multinomial.o ..\randist\multinomial.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_nbinomial.o ..\randist\nbinomial.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_pareto.o ..\randist\pareto.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_pascal.o ..\randist\pascal.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_poisson.o ..\randist\poisson.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_rayleigh.o ..\randist\rayleigh.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_shuffle.o ..\randist\shuffle.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_sphere.o ..\randist\sphere.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_tdist.o ..\randist\tdist.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_weibull.o ..\randist\weibull.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_landau.o ..\randist\landau.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_binomial_tpe.o ..\randist\binomial_tpe.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_borosh13.o ..\rng\borosh13.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_cmrg.o ..\rng\cmrg.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_coveyou.o ..\rng\coveyou.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_default.o ..\rng\default.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_file.o ..\rng\file.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_fishman18.o ..\rng\fishman18.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_fishman20.o ..\rng\fishman20.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_fishman2x.o ..\rng\fishman2x.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_gfsr4.o ..\rng\gfsr4.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_knuthran2.o ..\rng\knuthran2.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_knuthran.o ..\rng\knuthran.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_lecuyer21.o ..\rng\lecuyer21.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_minstd.o ..\rng\minstd.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_mrg.o ..\rng\mrg.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_mt.o ..\rng\mt.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_r250.o ..\rng\r250.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_ran0.o ..\rng\ran0.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_ran1.o ..\rng\ran1.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_ran2.o ..\rng\ran2.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_ran3.o ..\rng\ran3.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_rand48.o ..\rng\rand48.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_rand.o ..\rng\rand.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_random.o ..\rng\random.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_randu.o ..\rng\randu.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_ranf.o ..\rng\ranf.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_ranlux.o ..\rng\ranlux.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_ranlxd.o ..\rng\ranlxd.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_ranlxs.o ..\rng\ranlxs.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_ranmar.o ..\rng\ranmar.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_rng.o ..\rng\rng.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_slatec.o ..\rng\slatec.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_taus.o ..\rng\taus.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_taus113.o ..\rng\taus113.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_transputer.o ..\rng\transputer.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_tt.o ..\rng\tt.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_types.o ..\rng\types.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_uni32.o ..\rng\uni32.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_uni.o ..\rng\uni.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_vax.o ..\rng\vax.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_waterman14.o ..\rng\waterman14.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_zuf.o ..\rng\zuf.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\roots_bisection.o ..\roots\bisection.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\roots_brent.o ..\roots\brent.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\roots_falsepos.o ..\roots\falsepos.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\roots_newton.o ..\roots\newton.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\roots_secant.o ..\roots\secant.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\roots_steffenson.o ..\roots\steffenson.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\roots_convergence.o ..\roots\convergence.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\roots_fsolver.o ..\roots\fsolver.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\roots_fdfsolver.o ..\roots\fdfsolver.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\siman_siman.o ..\siman\siman.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\sort_sort.o ..\sort\sort.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\sort_sortind.o ..\sort\sortind.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\sort_sortvec.o ..\sort\sortvec.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\sort_sortvecind.o ..\sort\sortvecind.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\sort_subset.o ..\sort\subset.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\sort_subsetind.o ..\sort\subsetind.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_airy.o ..\specfunc\airy.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_airy_der.o ..\specfunc\airy_der.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_airy_zero.o ..\specfunc\airy_zero.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_atanint.o ..\specfunc\atanint.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_bessel.o ..\specfunc\bessel.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_bessel_I0.o ..\specfunc\bessel_I0.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_bessel_I1.o ..\specfunc\bessel_I1.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_bessel_In.o ..\specfunc\bessel_In.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_bessel_Inu.o ..\specfunc\bessel_Inu.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_bessel_J0.o ..\specfunc\bessel_J0.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_bessel_J1.o ..\specfunc\bessel_J1.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_bessel_Jn.o ..\specfunc\bessel_Jn.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_bessel_Jnu.o ..\specfunc\bessel_Jnu.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_bessel_K0.o ..\specfunc\bessel_K0.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_bessel_K1.o ..\specfunc\bessel_K1.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_bessel_Kn.o ..\specfunc\bessel_Kn.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_bessel_Knu.o ..\specfunc\bessel_Knu.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_bessel_Y0.o ..\specfunc\bessel_Y0.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_bessel_Y1.o ..\specfunc\bessel_Y1.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_bessel_Yn.o ..\specfunc\bessel_Yn.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_bessel_Ynu.o ..\specfunc\bessel_Ynu.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_bessel_amp_phase.o ..\specfunc\bessel_amp_phase.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_bessel_i.o ..\specfunc\bessel_i.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_bessel_j.o ..\specfunc\bessel_j.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_bessel_k.o ..\specfunc\bessel_k.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_bessel_olver.o ..\specfunc\bessel_olver.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_bessel_temme.o ..\specfunc\bessel_temme.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_bessel_y.o ..\specfunc\bessel_y.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_bessel_zero.o ..\specfunc\bessel_zero.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_bessel_sequence.o ..\specfunc\bessel_sequence.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_beta.o ..\specfunc\beta.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_beta_inc.o ..\specfunc\beta_inc.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_clausen.o ..\specfunc\clausen.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_coulomb.o ..\specfunc\coulomb.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_coupling.o ..\specfunc\coupling.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_coulomb_bound.o ..\specfunc\coulomb_bound.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_dawson.o ..\specfunc\dawson.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_debye.o ..\specfunc\debye.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_dilog.o ..\specfunc\dilog.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_elementary.o ..\specfunc\elementary.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_ellint.o ..\specfunc\ellint.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_elljac.o ..\specfunc\elljac.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_erfc.o ..\specfunc\erfc.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_exp.o ..\specfunc\exp.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_expint.o ..\specfunc\expint.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_expint3.o ..\specfunc\expint3.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_fermi_dirac.o ..\specfunc\fermi_dirac.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_gegenbauer.o ..\specfunc\gegenbauer.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_gamma.o ..\specfunc\gamma.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_gamma_inc.o ..\specfunc\gamma_inc.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_hyperg_0F1.o ..\specfunc\hyperg_0F1.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_hyperg_2F0.o ..\specfunc\hyperg_2F0.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_hyperg_1F1.o ..\specfunc\hyperg_1F1.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_hyperg_2F1.o ..\specfunc\hyperg_2F1.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_hyperg_U.o ..\specfunc\hyperg_U.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_hyperg.o ..\specfunc\hyperg.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_laguerre.o ..\specfunc\laguerre.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_lambert.o ..\specfunc\lambert.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_legendre_H3d.o ..\specfunc\legendre_H3d.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_legendre_Qn.o ..\specfunc\legendre_Qn.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_legendre_con.o ..\specfunc\legendre_con.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_legendre_poly.o ..\specfunc\legendre_poly.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_log.o ..\specfunc\log.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_poch.o ..\specfunc\poch.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_pow_int.o ..\specfunc\pow_int.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_psi.o ..\specfunc\psi.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_result.o ..\specfunc\result.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_shint.o ..\specfunc\shint.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_sinint.o ..\specfunc\sinint.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_synchrotron.o ..\specfunc\synchrotron.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_transport.o ..\specfunc\transport.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_trig.o ..\specfunc\trig.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_zeta.o ..\specfunc\zeta.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\statistics_mean.o ..\statistics\mean.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\statistics_variance.o ..\statistics\variance.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\statistics_absdev.o ..\statistics\absdev.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\statistics_skew.o ..\statistics\skew.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\statistics_kurtosis.o ..\statistics\kurtosis.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\statistics_lag1.o ..\statistics\lag1.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\statistics_p_variance.o ..\statistics\p_variance.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\statistics_minmax.o ..\statistics\minmax.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\statistics_ttest.o ..\statistics\ttest.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\statistics_median.o ..\statistics\median.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\statistics_covariance.o ..\statistics\covariance.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\statistics_quantiles.o ..\statistics\quantiles.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\statistics_wmean.o ..\statistics\wmean.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\statistics_wvariance.o ..\statistics\wvariance.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\statistics_wabsdev.o ..\statistics\wabsdev.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\statistics_wskew.o ..\statistics\wskew.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\statistics_wkurtosis.o ..\statistics\wkurtosis.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\sum_levin_u.o ..\sum\levin_u.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\sum_levin_utrunc.o ..\sum\levin_utrunc.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\sum_work_u.o ..\sum\work_u.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\sum_work_utrunc.o ..\sum\work_utrunc.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\sys_minmax.o ..\sys\minmax.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\sys_prec.o ..\sys\prec.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\sys_hypot.o ..\sys\hypot.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\sys_log1p.o ..\sys\log1p.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\sys_expm1.o ..\sys\expm1.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\sys_coerce.o ..\sys\coerce.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\sys_invhyp.o ..\sys\invhyp.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\sys_pow_int.o ..\sys\pow_int.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\sys_infnan.o ..\sys\infnan.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\sys_fdiv.o ..\sys\fdiv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\sys_fcmp.o ..\sys\fcmp.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\sys_ldfrexp.o ..\sys\ldfrexp.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\test_results.o ..\test\results.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\vector_init.o ..\vector\init.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\vector_file.o ..\vector\file.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\vector_vector.o ..\vector\vector.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\vector_copy.o ..\vector\copy.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\vector_swap.o ..\vector\swap.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\vector_prop.o ..\vector\prop.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\vector_minmax.o ..\vector\minmax.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\vector_oper.o ..\vector\oper.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\vector_reim.o ..\vector\reim.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\vector_subvector.o ..\vector\subvector.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\vector_view.o ..\vector\view.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\wavelet_dwt.o ..\wavelet\dwt.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\wavelet_wavelet.o ..\wavelet\wavelet.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\wavelet_bspline.o ..\wavelet\bspline.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\wavelet_daubechies.o ..\wavelet\daubechies.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\wavelet_haar.o ..\wavelet\haar.c

REM Make libgsl (Release) library
cd .\Release\mingw\temp
%_ARC% %_ARC_OPTS% ..\libgsl.a version.o blas_blas.o block_init.o block_file.o block_block.o cdf_beta.o cdf_betainv.o cdf_cauchy.o cdf_cauchyinv.o cdf_chisq.o cdf_chisqinv.o cdf_exponential.o cdf_exponentialinv.o cdf_exppow.o cdf_fdist.o cdf_fdistinv.o cdf_flat.o cdf_flatinv.o cdf_gamma.o cdf_gammainv.o cdf_gauss.o cdf_gaussinv.o cdf_gumbel1.o cdf_gumbel1inv.o cdf_gumbel2.o cdf_gumbel2inv.o cdf_laplace.o cdf_laplaceinv.o cdf_logistic.o cdf_logisticinv.o cdf_lognormal.o cdf_lognormalinv.o cdf_pareto.o cdf_paretoinv.o cdf_rayleigh.o cdf_rayleighinv.o cdf_tdist.o cdf_tdistinv.o cdf_weibull.o cdf_weibullinv.o cdf_binomial.o cdf_poisson.o cdf_geometric.o cdf_nbinomial.o cdf_pascal.o cdf_hypergeometric.o cheb_deriv.o cheb_eval.o cheb_init.o cheb_integ.o combination_init.o combination_file.o combination_combination.o complex_math.o deriv_deriv.o dht_dht.o diff_diff.o eigen_jacobi.o eigen_symm.o eigen_symmv.o eigen_herm.o eigen_hermv.o eigen_sort.o err_error.o err_stream.o err_message.o err_strerror.o fft_dft.o fft_fft.o fit_linear.o histogram_add.o histogram_get.o histogram_init.o histogram_params.o histogram_reset.o histogram_file.o histogram_pdf.o histogram_add2d.o histogram_get2d.o histogram_init2d.o histogram_params2d.o histogram_reset2d.o histogram_file2d.o histogram_pdf2d.o histogram_calloc_range.o histogram_calloc_range2d.o histogram_copy.o histogram_copy2d.o histogram_maxval.o histogram_maxval2d.o histogram_oper.o histogram_oper2d.o histogram_stat.o histogram_stat2d.o ieee-utils_print.o ieee-utils_make_rep.o ieee-utils_env.o ieee-utils_fp.o ieee-utils_read.o integration_qk15.o integration_qk21.o integration_qk31.o integration_qk41.o integration_qk51.o integration_qk61.o integration_qk.o integration_qng.o integration_qag.o integration_qags.o integration_qagp.o integration_workspace.o integration_qcheb.o integration_qawc.o integration_qmomo.o integration_qaws.o integration_qmomof.o integration_qawo.o integration_qawf.o interpolation_accel.o interpolation_akima.o interpolation_bsearch.o interpolation_cspline.o interpolation_interp.o interpolation_linear.o interpolation_spline.o interpolation_poly.o linalg_multiply.o linalg_exponential.o linalg_tridiag.o linalg_lu.o linalg_luc.o linalg_hh.o linalg_qr.o linalg_qrpt.o linalg_lq.o linalg_ptlq.o linalg_svd.o linalg_householder.o linalg_householdercomplex.o linalg_cholesky.o linalg_symmtd.o linalg_hermtd.o linalg_bidiag.o linalg_balance.o matrix_init.o matrix_matrix.o matrix_file.o matrix_rowcol.o matrix_swap.o matrix_copy.o matrix_minmax.o matrix_prop.o matrix_oper.o matrix_getset.o matrix_view.o matrix_submatrix.o min_fsolver.o min_golden.o min_brent.o min_convergence.o min_bracketing.o monte_miser.o monte_plain.o monte_vegas.o multifit_multilinear.o multifit_work.o multifit_lmder.o multifit_fsolver.o multifit_fdfsolver.o multifit_convergence.o multifit_gradient.o multifit_covar.o multimin_fdfminimizer.o multimin_steepest_descent.o multimin_conjugate_fr.o multimin_conjugate_pr.o multimin_convergence.o multimin_diff.o multimin_vector_bfgs.o multimin_fminimizer.o multimin_simplex.o multiroots_fdjac.o multiroots_fsolver.o multiroots_fdfsolver.o multiroots_convergence.o multiroots_newton.o multiroots_gnewton.o multiroots_dnewton.o multiroots_broyden.o multiroots_hybrid.o multiroots_hybridj.o ntuple_ntuple.o ode-initval_control.o ode-initval_cstd.o ode-initval_cscal.o ode-initval_evolve.o ode-initval_step.o ode-initval_rk2.o ode-initval_rk2imp.o ode-initval_rk2simp.o ode-initval_rk4.o ode-initval_rk4imp.o ode-initval_rkf45.o ode-initval_rk8pd.o ode-initval_rkck.o ode-initval_bsimp.o ode-initval_gear1.o ode-initval_gear2.o permutation_init.o permutation_file.o permutation_permutation.o permutation_permute.o permutation_canonical.o poly_dd.o poly_eval.o poly_solve_quadratic.o poly_solve_cubic.o poly_zsolve_quadratic.o poly_zsolve_cubic.o poly_zsolve.o poly_zsolve_init.o qrng_qrng.o qrng_niederreiter-2.o qrng_sobol.o randist_bernoulli.o randist_beta.o randist_bigauss.o randist_binomial.o randist_cauchy.o randist_chisq.o randist_dirichlet.o randist_discrete.o randist_erlang.o randist_exponential.o randist_exppow.o randist_fdist.o randist_flat.o randist_gamma.o randist_gauss.o randist_gausszig.o randist_gausstail.o randist_geometric.o randist_gumbel.o randist_hyperg.o randist_laplace.o randist_levy.o randist_logarithmic.o randist_logistic.o randist_lognormal.o randist_multinomial.o randist_nbinomial.o randist_pareto.o randist_pascal.o randist_poisson.o randist_rayleigh.o randist_shuffle.o randist_sphere.o randist_tdist.o randist_weibull.o randist_landau.o randist_binomial_tpe.o rng_borosh13.o rng_cmrg.o rng_coveyou.o rng_default.o rng_file.o rng_fishman18.o rng_fishman20.o rng_fishman2x.o rng_gfsr4.o rng_knuthran2.o rng_knuthran.o rng_lecuyer21.o rng_minstd.o rng_mrg.o rng_mt.o rng_r250.o rng_ran0.o rng_ran1.o rng_ran2.o rng_ran3.o rng_rand48.o rng_rand.o rng_random.o rng_randu.o rng_ranf.o rng_ranlux.o rng_ranlxd.o rng_ranlxs.o rng_ranmar.o rng_rng.o rng_slatec.o rng_taus.o rng_taus113.o rng_transputer.o rng_tt.o rng_types.o rng_uni32.o rng_uni.o rng_vax.o rng_waterman14.o rng_zuf.o roots_bisection.o roots_brent.o roots_falsepos.o roots_newton.o roots_secant.o roots_steffenson.o roots_convergence.o roots_fsolver.o roots_fdfsolver.o siman_siman.o sort_sort.o sort_sortind.o sort_sortvec.o sort_sortvecind.o sort_subset.o sort_subsetind.o specfunc_airy.o specfunc_airy_der.o specfunc_airy_zero.o specfunc_atanint.o specfunc_bessel.o specfunc_bessel_I0.o specfunc_bessel_I1.o specfunc_bessel_In.o specfunc_bessel_Inu.o specfunc_bessel_J0.o specfunc_bessel_J1.o specfunc_bessel_Jn.o specfunc_bessel_Jnu.o specfunc_bessel_K0.o specfunc_bessel_K1.o specfunc_bessel_Kn.o specfunc_bessel_Knu.o specfunc_bessel_Y0.o specfunc_bessel_Y1.o specfunc_bessel_Yn.o specfunc_bessel_Ynu.o specfunc_bessel_amp_phase.o specfunc_bessel_i.o specfunc_bessel_j.o specfunc_bessel_k.o specfunc_bessel_olver.o specfunc_bessel_temme.o specfunc_bessel_y.o specfunc_bessel_zero.o specfunc_bessel_sequence.o specfunc_beta.o specfunc_beta_inc.o specfunc_clausen.o specfunc_coulomb.o specfunc_coupling.o specfunc_coulomb_bound.o specfunc_dawson.o specfunc_debye.o specfunc_dilog.o specfunc_elementary.o specfunc_ellint.o specfunc_elljac.o specfunc_erfc.o specfunc_exp.o specfunc_expint.o specfunc_expint3.o specfunc_fermi_dirac.o specfunc_gegenbauer.o specfunc_gamma.o specfunc_gamma_inc.o specfunc_hyperg_0F1.o specfunc_hyperg_2F0.o specfunc_hyperg_1F1.o specfunc_hyperg_2F1.o specfunc_hyperg_U.o specfunc_hyperg.o specfunc_laguerre.o specfunc_lambert.o specfunc_legendre_H3d.o specfunc_legendre_Qn.o specfunc_legendre_con.o specfunc_legendre_poly.o specfunc_log.o specfunc_poch.o specfunc_pow_int.o specfunc_psi.o specfunc_result.o specfunc_shint.o specfunc_sinint.o specfunc_synchrotron.o specfunc_transport.o specfunc_trig.o specfunc_zeta.o statistics_mean.o statistics_variance.o statistics_absdev.o statistics_skew.o statistics_kurtosis.o statistics_lag1.o statistics_p_variance.o statistics_minmax.o statistics_ttest.o statistics_median.o statistics_covariance.o statistics_quantiles.o statistics_wmean.o statistics_wvariance.o statistics_wabsdev.o statistics_wskew.o statistics_wkurtosis.o sum_levin_u.o sum_levin_utrunc.o sum_work_u.o sum_work_utrunc.o sys_minmax.o sys_prec.o sys_hypot.o sys_log1p.o sys_expm1.o sys_coerce.o sys_invhyp.o sys_pow_int.o sys_infnan.o sys_fdiv.o sys_fcmp.o sys_ldfrexp.o test_results.o vector_init.o vector_file.o vector_vector.o vector_copy.o vector_swap.o vector_prop.o vector_minmax.o vector_oper.o vector_reim.o vector_subvector.o vector_view.o wavelet_dwt.o wavelet_wavelet.o wavelet_bspline.o wavelet_daubechies.o wavelet_haar.o
cd ..\..\..

REM Compile cblas (Release) sources
%_MKDIR% .\Release\mingw\cblas
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\sasum.o ..\cblas\sasum.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\saxpy.o ..\cblas\saxpy.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\scasum.o ..\cblas\scasum.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\scnrm2.o ..\cblas\scnrm2.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\scopy.o ..\cblas\scopy.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\sdot.o ..\cblas\sdot.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\sdsdot.o ..\cblas\sdsdot.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\sgbmv.o ..\cblas\sgbmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\sgemm.o ..\cblas\sgemm.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\sgemv.o ..\cblas\sgemv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\sger.o ..\cblas\sger.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\snrm2.o ..\cblas\snrm2.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\srot.o ..\cblas\srot.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\srotg.o ..\cblas\srotg.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\srotm.o ..\cblas\srotm.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\srotmg.o ..\cblas\srotmg.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\ssbmv.o ..\cblas\ssbmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\sscal.o ..\cblas\sscal.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\sspmv.o ..\cblas\sspmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\sspr.o ..\cblas\sspr.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\sspr2.o ..\cblas\sspr2.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\sswap.o ..\cblas\sswap.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\ssymm.o ..\cblas\ssymm.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\ssymv.o ..\cblas\ssymv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\ssyr.o ..\cblas\ssyr.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\ssyr2.o ..\cblas\ssyr2.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\ssyr2k.o ..\cblas\ssyr2k.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\ssyrk.o ..\cblas\ssyrk.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\stbmv.o ..\cblas\stbmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\stbsv.o ..\cblas\stbsv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\stpmv.o ..\cblas\stpmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\stpsv.o ..\cblas\stpsv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\strmm.o ..\cblas\strmm.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\strmv.o ..\cblas\strmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\strsm.o ..\cblas\strsm.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\strsv.o ..\cblas\strsv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\dasum.o ..\cblas\dasum.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\daxpy.o ..\cblas\daxpy.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\dcopy.o ..\cblas\dcopy.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\ddot.o ..\cblas\ddot.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\dgbmv.o ..\cblas\dgbmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\dgemm.o ..\cblas\dgemm.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\dgemv.o ..\cblas\dgemv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\dger.o ..\cblas\dger.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\dnrm2.o ..\cblas\dnrm2.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\drot.o ..\cblas\drot.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\drotg.o ..\cblas\drotg.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\drotm.o ..\cblas\drotm.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\drotmg.o ..\cblas\drotmg.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\dsbmv.o ..\cblas\dsbmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\dscal.o ..\cblas\dscal.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\dsdot.o ..\cblas\dsdot.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\dspmv.o ..\cblas\dspmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\dspr.o ..\cblas\dspr.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\dspr2.o ..\cblas\dspr2.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\dswap.o ..\cblas\dswap.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\dsymm.o ..\cblas\dsymm.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\dsymv.o ..\cblas\dsymv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\dsyr.o ..\cblas\dsyr.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\dsyr2.o ..\cblas\dsyr2.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\dsyr2k.o ..\cblas\dsyr2k.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\dsyrk.o ..\cblas\dsyrk.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\dtbmv.o ..\cblas\dtbmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\dtbsv.o ..\cblas\dtbsv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\dtpmv.o ..\cblas\dtpmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\dtpsv.o ..\cblas\dtpsv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\dtrmm.o ..\cblas\dtrmm.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\dtrmv.o ..\cblas\dtrmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\dtrsm.o ..\cblas\dtrsm.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\dtrsv.o ..\cblas\dtrsv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\dzasum.o ..\cblas\dzasum.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\dznrm2.o ..\cblas\dznrm2.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\caxpy.o ..\cblas\caxpy.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\ccopy.o ..\cblas\ccopy.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cdotc_sub.o ..\cblas\cdotc_sub.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cdotu_sub.o ..\cblas\cdotu_sub.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cgbmv.o ..\cblas\cgbmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cgemm.o ..\cblas\cgemm.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cgemv.o ..\cblas\cgemv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cgerc.o ..\cblas\cgerc.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cgeru.o ..\cblas\cgeru.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\chbmv.o ..\cblas\chbmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\chemm.o ..\cblas\chemm.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\chemv.o ..\cblas\chemv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cher.o ..\cblas\cher.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cher2.o ..\cblas\cher2.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cher2k.o ..\cblas\cher2k.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cherk.o ..\cblas\cherk.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\chpmv.o ..\cblas\chpmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\chpr.o ..\cblas\chpr.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\chpr2.o ..\cblas\chpr2.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cscal.o ..\cblas\cscal.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\csscal.o ..\cblas\csscal.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cswap.o ..\cblas\cswap.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\csymm.o ..\cblas\csymm.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\csyr2k.o ..\cblas\csyr2k.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\csyrk.o ..\cblas\csyrk.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\ctbmv.o ..\cblas\ctbmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\ctbsv.o ..\cblas\ctbsv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\ctpmv.o ..\cblas\ctpmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\ctpsv.o ..\cblas\ctpsv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\ctrmm.o ..\cblas\ctrmm.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\ctrmv.o ..\cblas\ctrmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\ctrsm.o ..\cblas\ctrsm.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\ctrsv.o ..\cblas\ctrsv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\zaxpy.o ..\cblas\zaxpy.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\zcopy.o ..\cblas\zcopy.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\zdotc_sub.o ..\cblas\zdotc_sub.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\zdotu_sub.o ..\cblas\zdotu_sub.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\zdscal.o ..\cblas\zdscal.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\zgbmv.o ..\cblas\zgbmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\zgemm.o ..\cblas\zgemm.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\zgemv.o ..\cblas\zgemv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\zgerc.o ..\cblas\zgerc.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\zgeru.o ..\cblas\zgeru.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\zhbmv.o ..\cblas\zhbmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\zhemm.o ..\cblas\zhemm.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\zhemv.o ..\cblas\zhemv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\zher.o ..\cblas\zher.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\zher2.o ..\cblas\zher2.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\zher2k.o ..\cblas\zher2k.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\zherk.o ..\cblas\zherk.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\zhpmv.o ..\cblas\zhpmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\zhpr.o ..\cblas\zhpr.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\zhpr2.o ..\cblas\zhpr2.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\zscal.o ..\cblas\zscal.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\zswap.o ..\cblas\zswap.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\zsymm.o ..\cblas\zsymm.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\zsyr2k.o ..\cblas\zsyr2k.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\zsyrk.o ..\cblas\zsyrk.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\ztbmv.o ..\cblas\ztbmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\ztbsv.o ..\cblas\ztbsv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\ztpmv.o ..\cblas\ztpmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\ztpsv.o ..\cblas\ztpsv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\ztrmm.o ..\cblas\ztrmm.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\ztrmv.o ..\cblas\ztrmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\ztrsm.o ..\cblas\ztrsm.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\ztrsv.o ..\cblas\ztrsv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\icamax.o ..\cblas\icamax.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\idamax.o ..\cblas\idamax.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\isamax.o ..\cblas\isamax.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\izamax.o ..\cblas\izamax.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\xerbla.o ..\cblas\xerbla.c

REM Make cblas (Release) library
cd .\Release\mingw\cblas
%_ARC% %_ARC_OPTS%  libgslcblas.a sasum.o saxpy.o scasum.o scnrm2.o scopy.o sdot.o sdsdot.o sgbmv.o sgemm.o sgemv.o sger.o snrm2.o srot.o srotg.o srotm.o srotmg.o ssbmv.o sscal.o sspmv.o sspr.o sspr2.o sswap.o ssymm.o ssymv.o ssyr.o ssyr2.o ssyr2k.o ssyrk.o stbmv.o stbsv.o stpmv.o stpsv.o strmm.o strmv.o strsm.o strsv.o dasum.o daxpy.o dcopy.o ddot.o dgbmv.o dgemm.o dgemv.o dger.o dnrm2.o drot.o drotg.o drotm.o drotmg.o dsbmv.o dscal.o dsdot.o dspmv.o dspr.o dspr2.o dswap.o dsymm.o dsymv.o dsyr.o dsyr2.o dsyr2k.o dsyrk.o dtbmv.o dtbsv.o dtpmv.o dtpsv.o dtrmm.o dtrmv.o dtrsm.o dtrsv.o dzasum.o dznrm2.o caxpy.o ccopy.o cdotc_sub.o cdotu_sub.o cgbmv.o cgemm.o cgemv.o cgerc.o cgeru.o chbmv.o chemm.o chemv.o cher.o cher2.o cher2k.o cherk.o chpmv.o chpr.o chpr2.o cscal.o csscal.o cswap.o csymm.o csyr2k.o csyrk.o ctbmv.o ctbsv.o ctpmv.o ctpsv.o ctrmm.o ctrmv.o ctrsm.o ctrsv.o zaxpy.o zcopy.o zdotc_sub.o zdotu_sub.o zdscal.o zgbmv.o zgemm.o zgemv.o zgerc.o zgeru.o zhbmv.o zhemm.o zhemv.o zher.o zher2.o zher2k.o zherk.o zhpmv.o zhpr.o zhpr2.o zscal.o zswap.o zsymm.o zsyr2k.o zsyrk.o ztbmv.o ztbsv.o ztpmv.o ztpsv.o ztrmm.o ztrmv.o ztrsm.o ztrsv.o icamax.o idamax.o isamax.o izamax.o xerbla.o
cd ..\..\..

REM Compile libgsl dll (Release) sources
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dversion.o ..\version.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dblasblas.o ..\blas\blas.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dblockinit.o ..\block\init.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dblockfile.o ..\block\file.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dblockblock.o ..\block\block.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfbeta.o ..\cdf\beta.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfbetainv.o ..\cdf\betainv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfcauchy.o ..\cdf\cauchy.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfcauchyinv.o ..\cdf\cauchyinv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfchisq.o ..\cdf\chisq.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfchisqinv.o ..\cdf\chisqinv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfexponential.o ..\cdf\exponential.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfexponentialinv.o ..\cdf\exponentialinv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfexppow.o ..\cdf\exppow.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdffdist.o ..\cdf\fdist.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdffdistinv.o ..\cdf\fdistinv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfflat.o ..\cdf\flat.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfflatinv.o ..\cdf\flatinv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfgamma.o ..\cdf\gamma.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfgammainv.o ..\cdf\gammainv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfgauss.o ..\cdf\gauss.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfgaussinv.o ..\cdf\gaussinv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfgumbel1.o ..\cdf\gumbel1.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfgumbel1inv.o ..\cdf\gumbel1inv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfgumbel2.o ..\cdf\gumbel2.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfgumbel2inv.o ..\cdf\gumbel2inv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdflaplace.o ..\cdf\laplace.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdflaplaceinv.o ..\cdf\laplaceinv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdflogistic.o ..\cdf\logistic.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdflogisticinv.o ..\cdf\logisticinv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdflognormal.o ..\cdf\lognormal.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdflognormalinv.o ..\cdf\lognormalinv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfpareto.o ..\cdf\pareto.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfparetoinv.o ..\cdf\paretoinv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfrayleigh.o ..\cdf\rayleigh.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfrayleighinv.o ..\cdf\rayleighinv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdftdist.o ..\cdf\tdist.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdftdistinv.o ..\cdf\tdistinv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfweibull.o ..\cdf\weibull.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfweibullinv.o ..\cdf\weibullinv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfbinomial.o ..\cdf\binomial.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfpoisson.o ..\cdf\poisson.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfgeometric.o ..\cdf\geometric.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfnbinomial.o ..\cdf\nbinomial.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfpascal.o ..\cdf\pascal.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcdfhypergeometric.o ..\cdf\hypergeometric.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dchebderiv.o ..\cheb\deriv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dchebeval.o ..\cheb\eval.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dchebinit.o ..\cheb\init.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dchebinteg.o ..\cheb\integ.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcombinationinit.o ..\combination\init.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcombinationfile.o ..\combination\file.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcombinationcombination.o ..\combination\combination.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dcomplexmath.o ..\complex\math.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dderivderiv.o ..\deriv\deriv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ddhtdht.o ..\dht\dht.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ddiffdiff.o ..\diff\diff.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\deigenjacobi.o ..\eigen\jacobi.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\deigensymm.o ..\eigen\symm.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\deigensymmv.o ..\eigen\symmv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\deigenherm.o ..\eigen\herm.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\deigenhermv.o ..\eigen\hermv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\deigensort.o ..\eigen\sort.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\derrerror.o ..\err\error.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\derrstream.o ..\err\stream.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\derrmessage.o ..\err\message.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\derrstrerror.o ..\err\strerror.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dfftdft.o ..\fft\dft.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dfftfft.o ..\fft\fft.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dfitlinear.o ..\fit\linear.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dhistogramadd.o ..\histogram\add.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dhistogramget.o ..\histogram\get.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dhistograminit.o ..\histogram\init.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dhistogramparams.o ..\histogram\params.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dhistogramreset.o ..\histogram\reset.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dhistogramfile.o ..\histogram\file.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dhistogrampdf.o ..\histogram\pdf.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dhistogramadd2d.o ..\histogram\add2d.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dhistogramget2d.o ..\histogram\get2d.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dhistograminit2d.o ..\histogram\init2d.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dhistogramparams2d.o ..\histogram\params2d.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dhistogramreset2d.o ..\histogram\reset2d.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dhistogramfile2d.o ..\histogram\file2d.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dhistogrampdf2d.o ..\histogram\pdf2d.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dhistogramcalloc_range.o ..\histogram\calloc_range.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dhistogramcalloc_range2d.o ..\histogram\calloc_range2d.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dhistogramcopy.o ..\histogram\copy.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dhistogramcopy2d.o ..\histogram\copy2d.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dhistogrammaxval.o ..\histogram\maxval.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dhistogrammaxval2d.o ..\histogram\maxval2d.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dhistogramoper.o ..\histogram\oper.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dhistogramoper2d.o ..\histogram\oper2d.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dhistogramstat.o ..\histogram\stat.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dhistogramstat2d.o ..\histogram\stat2d.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dieee-utilsprint.o ..\ieee-utils\print.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dieee-utilsmake_rep.o ..\ieee-utils\make_rep.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dieee-utilsenv.o ..\ieee-utils\env.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dieee-utilsfp.o ..\ieee-utils\fp.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dieee-utilsread.o ..\ieee-utils\read.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dintegrationqk15.o ..\integration\qk15.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dintegrationqk21.o ..\integration\qk21.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dintegrationqk31.o ..\integration\qk31.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dintegrationqk41.o ..\integration\qk41.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dintegrationqk51.o ..\integration\qk51.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dintegrationqk61.o ..\integration\qk61.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dintegrationqk.o ..\integration\qk.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dintegrationqng.o ..\integration\qng.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dintegrationqag.o ..\integration\qag.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dintegrationqags.o ..\integration\qags.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dintegrationqagp.o ..\integration\qagp.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dintegrationworkspace.o ..\integration\workspace.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dintegrationqcheb.o ..\integration\qcheb.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dintegrationqawc.o ..\integration\qawc.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dintegrationqmomo.o ..\integration\qmomo.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dintegrationqaws.o ..\integration\qaws.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dintegrationqmomof.o ..\integration\qmomof.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dintegrationqawo.o ..\integration\qawo.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dintegrationqawf.o ..\integration\qawf.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dinterpolationaccel.o ..\interpolation\accel.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dinterpolationakima.o ..\interpolation\akima.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dinterpolationbsearch.o ..\interpolation\bsearch.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dinterpolationcspline.o ..\interpolation\cspline.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dinterpolationinterp.o ..\interpolation\interp.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dinterpolationlinear.o ..\interpolation\linear.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dinterpolationspline.o ..\interpolation\spline.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dinterpolationpoly.o ..\interpolation\poly.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dlinalgmultiply.o ..\linalg\multiply.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dlinalgexponential.o ..\linalg\exponential.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dlinalgtridiag.o ..\linalg\tridiag.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dlinalglu.o ..\linalg\lu.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dlinalgluc.o ..\linalg\luc.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dlinalghh.o ..\linalg\hh.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dlinalgqr.o ..\linalg\qr.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dlinalgqrpt.o ..\linalg\qrpt.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dlinalglq.o ..\linalg\lq.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dlinalgptlq.o ..\linalg\ptlq.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dlinalgsvd.o ..\linalg\svd.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dlinalghouseholder.o ..\linalg\householder.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dlinalghouseholdercomplex.o ..\linalg\householdercomplex.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dlinalgcholesky.o ..\linalg\cholesky.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dlinalgsymmtd.o ..\linalg\symmtd.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dlinalghermtd.o ..\linalg\hermtd.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dlinalgbidiag.o ..\linalg\bidiag.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dlinalgbalance.o ..\linalg\balance.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmatrixinit.o ..\matrix\init.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmatrixmatrix.o ..\matrix\matrix.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmatrixfile.o ..\matrix\file.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmatrixrowcol.o ..\matrix\rowcol.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmatrixswap.o ..\matrix\swap.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmatrixcopy.o ..\matrix\copy.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmatrixminmax.o ..\matrix\minmax.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmatrixprop.o ..\matrix\prop.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmatrixoper.o ..\matrix\oper.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmatrixgetset.o ..\matrix\getset.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmatrixview.o ..\matrix\view.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmatrixsubmatrix.o ..\matrix\submatrix.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dminfsolver.o ..\min\fsolver.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmingolden.o ..\min\golden.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dminbrent.o ..\min\brent.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dminconvergence.o ..\min\convergence.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dminbracketing.o ..\min\bracketing.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmontemiser.o ..\monte\miser.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmonteplain.o ..\monte\plain.c
%_COMPILE% %_OPT_DEBUG% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmontevegas.o ..\monte\vegas.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmultifitmultilinear.o ..\multifit\multilinear.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmultifitwork.o ..\multifit\work.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmultifitlmder.o ..\multifit\lmder.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmultifitfsolver.o ..\multifit\fsolver.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmultifitfdfsolver.o ..\multifit\fdfsolver.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmultifitconvergence.o ..\multifit\convergence.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmultifitgradient.o ..\multifit\gradient.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmultifitcovar.o ..\multifit\covar.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmultiminfdfminimizer.o ..\multimin\fdfminimizer.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmultiminsteepest_descent.o ..\multimin\steepest_descent.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmultiminconjugate_fr.o ..\multimin\conjugate_fr.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmultiminconjugate_pr.o ..\multimin\conjugate_pr.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmultiminconvergence.o ..\multimin\convergence.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmultimindiff.o ..\multimin\diff.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmultiminvector_bfgs.o ..\multimin\vector_bfgs.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmultiminfminimizer.o ..\multimin\fminimizer.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmultiminsimplex.o ..\multimin\simplex.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmultirootsfdjac.o ..\multiroots\fdjac.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmultirootsfsolver.o ..\multiroots\fsolver.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmultirootsfdfsolver.o ..\multiroots\fdfsolver.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmultirootsconvergence.o ..\multiroots\convergence.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmultirootsnewton.o ..\multiroots\newton.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmultirootsgnewton.o ..\multiroots\gnewton.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmultirootsdnewton.o ..\multiroots\dnewton.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmultirootsbroyden.o ..\multiroots\broyden.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmultirootshybrid.o ..\multiroots\hybrid.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dmultirootshybridj.o ..\multiroots\hybridj.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dntuplentuple.o ..\ntuple\ntuple.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dode-initvalcontrol.o ..\ode-initval\control.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dode-initvalcstd.o ..\ode-initval\cstd.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dode-initvalcscal.o ..\ode-initval\cscal.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dode-initvalevolve.o ..\ode-initval\evolve.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dode-initvalstep.o ..\ode-initval\step.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dode-initvalrk2.o ..\ode-initval\rk2.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dode-initvalrk2imp.o ..\ode-initval\rk2imp.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dode-initvalrk2simp.o ..\ode-initval\rk2simp.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dode-initvalrk4.o ..\ode-initval\rk4.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dode-initvalrk4imp.o ..\ode-initval\rk4imp.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dode-initvalrkf45.o ..\ode-initval\rkf45.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dode-initvalrk8pd.o ..\ode-initval\rk8pd.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dode-initvalrkck.o ..\ode-initval\rkck.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dode-initvalbsimp.o ..\ode-initval\bsimp.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dode-initvalgear1.o ..\ode-initval\gear1.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dode-initvalgear2.o ..\ode-initval\gear2.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dpermutationinit.o ..\permutation\init.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dpermutationfile.o ..\permutation\file.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dpermutationpermutation.o ..\permutation\permutation.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dpermutationpermute.o ..\permutation\permute.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dpermutationcanonical.o ..\permutation\canonical.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dpolydd.o ..\poly\dd.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dpolyeval.o ..\poly\eval.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dpolysolve_quadratic.o ..\poly\solve_quadratic.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dpolysolve_cubic.o ..\poly\solve_cubic.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dpolyzsolve_quadratic.o ..\poly\zsolve_quadratic.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dpolyzsolve_cubic.o ..\poly\zsolve_cubic.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dpolyzsolve.o ..\poly\zsolve.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dpolyzsolve_init.o ..\poly\zsolve_init.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dqrngqrng.o ..\qrng\qrng.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dqrngniederreiter-2.o ..\qrng\niederreiter-2.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dqrngsobol.o ..\qrng\sobol.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistbernoulli.o ..\randist\bernoulli.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistbeta.o ..\randist\beta.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistbigauss.o ..\randist\bigauss.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistbinomial.o ..\randist\binomial.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistcauchy.o ..\randist\cauchy.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistchisq.o ..\randist\chisq.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistdirichlet.o ..\randist\dirichlet.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistdiscrete.o ..\randist\discrete.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandisterlang.o ..\randist\erlang.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistexponential.o ..\randist\exponential.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistexppow.o ..\randist\exppow.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistfdist.o ..\randist\fdist.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistflat.o ..\randist\flat.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistgamma.o ..\randist\gamma.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistgauss.o ..\randist\gauss.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistgausszig.o ..\randist\gausszig.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistgausstail.o ..\randist\gausstail.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistgeometric.o ..\randist\geometric.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistgumbel.o ..\randist\gumbel.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandisthyperg.o ..\randist\hyperg.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistlaplace.o ..\randist\laplace.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistlevy.o ..\randist\levy.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistlogarithmic.o ..\randist\logarithmic.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistlogistic.o ..\randist\logistic.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistlognormal.o ..\randist\lognormal.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistmultinomial.o ..\randist\multinomial.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistnbinomial.o ..\randist\nbinomial.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistpareto.o ..\randist\pareto.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistpascal.o ..\randist\pascal.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistpoisson.o ..\randist\poisson.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistrayleigh.o ..\randist\rayleigh.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistshuffle.o ..\randist\shuffle.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistsphere.o ..\randist\sphere.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandisttdist.o ..\randist\tdist.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistweibull.o ..\randist\weibull.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistlandau.o ..\randist\landau.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drandistbinomial_tpe.o ..\randist\binomial_tpe.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngborosh13.o ..\rng\borosh13.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngcmrg.o ..\rng\cmrg.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngcoveyou.o ..\rng\coveyou.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngdefault.o ..\rng\default.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngfile.o ..\rng\file.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngfishman18.o ..\rng\fishman18.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngfishman20.o ..\rng\fishman20.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngfishman2x.o ..\rng\fishman2x.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drnggfsr4.o ..\rng\gfsr4.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngknuthran2.o ..\rng\knuthran2.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngknuthran.o ..\rng\knuthran.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drnglecuyer21.o ..\rng\lecuyer21.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngminstd.o ..\rng\minstd.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngmrg.o ..\rng\mrg.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngmt.o ..\rng\mt.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngr250.o ..\rng\r250.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngran0.o ..\rng\ran0.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngran1.o ..\rng\ran1.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngran2.o ..\rng\ran2.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngran3.o ..\rng\ran3.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngrand48.o ..\rng\rand48.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngrand.o ..\rng\rand.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngrandom.o ..\rng\random.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngrandu.o ..\rng\randu.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngranf.o ..\rng\ranf.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngranlux.o ..\rng\ranlux.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngranlxd.o ..\rng\ranlxd.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngranlxs.o ..\rng\ranlxs.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngranmar.o ..\rng\ranmar.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngrng.o ..\rng\rng.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngslatec.o ..\rng\slatec.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngtaus.o ..\rng\taus.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngtaus113.o ..\rng\taus113.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngtransputer.o ..\rng\transputer.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngtt.o ..\rng\tt.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngtypes.o ..\rng\types.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drnguni32.o ..\rng\uni32.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drnguni.o ..\rng\uni.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngvax.o ..\rng\vax.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngwaterman14.o ..\rng\waterman14.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drngzuf.o ..\rng\zuf.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drootsbisection.o ..\roots\bisection.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drootsbrent.o ..\roots\brent.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drootsfalsepos.o ..\roots\falsepos.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drootsnewton.o ..\roots\newton.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drootssecant.o ..\roots\secant.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drootssteffenson.o ..\roots\steffenson.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drootsconvergence.o ..\roots\convergence.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drootsfsolver.o ..\roots\fsolver.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\drootsfdfsolver.o ..\roots\fdfsolver.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dsimansiman.o ..\siman\siman.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dsortsort.o ..\sort\sort.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dsortsortind.o ..\sort\sortind.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dsortsortvec.o ..\sort\sortvec.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dsortsortvecind.o ..\sort\sortvecind.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dsortsubset.o ..\sort\subset.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dsortsubsetind.o ..\sort\subsetind.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncairy.o ..\specfunc\airy.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncairy_der.o ..\specfunc\airy_der.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncairy_zero.o ..\specfunc\airy_zero.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncatanint.o ..\specfunc\atanint.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncbessel.o ..\specfunc\bessel.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncbessel_I0.o ..\specfunc\bessel_I0.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncbessel_I1.o ..\specfunc\bessel_I1.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncbessel_In.o ..\specfunc\bessel_In.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncbessel_Inu.o ..\specfunc\bessel_Inu.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncbessel_J0.o ..\specfunc\bessel_J0.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncbessel_J1.o ..\specfunc\bessel_J1.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncbessel_Jn.o ..\specfunc\bessel_Jn.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncbessel_Jnu.o ..\specfunc\bessel_Jnu.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncbessel_K0.o ..\specfunc\bessel_K0.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncbessel_K1.o ..\specfunc\bessel_K1.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncbessel_Kn.o ..\specfunc\bessel_Kn.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncbessel_Knu.o ..\specfunc\bessel_Knu.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncbessel_Y0.o ..\specfunc\bessel_Y0.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncbessel_Y1.o ..\specfunc\bessel_Y1.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncbessel_Yn.o ..\specfunc\bessel_Yn.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncbessel_Ynu.o ..\specfunc\bessel_Ynu.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncbessel_amp_phase.o ..\specfunc\bessel_amp_phase.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncbessel_i.o ..\specfunc\bessel_i.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncbessel_j.o ..\specfunc\bessel_j.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncbessel_k.o ..\specfunc\bessel_k.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncbessel_olver.o ..\specfunc\bessel_olver.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncbessel_temme.o ..\specfunc\bessel_temme.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncbessel_y.o ..\specfunc\bessel_y.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncbessel_zero.o ..\specfunc\bessel_zero.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncbessel_sequence.o ..\specfunc\bessel_sequence.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncbeta.o ..\specfunc\beta.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncbeta_inc.o ..\specfunc\beta_inc.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncclausen.o ..\specfunc\clausen.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfunccoulomb.o ..\specfunc\coulomb.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfunccoupling.o ..\specfunc\coupling.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfunccoulomb_bound.o ..\specfunc\coulomb_bound.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncdawson.o ..\specfunc\dawson.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncdebye.o ..\specfunc\debye.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncdilog.o ..\specfunc\dilog.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncelementary.o ..\specfunc\elementary.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncellint.o ..\specfunc\ellint.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncelljac.o ..\specfunc\elljac.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncerfc.o ..\specfunc\erfc.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncexp.o ..\specfunc\exp.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncexpint.o ..\specfunc\expint.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncexpint3.o ..\specfunc\expint3.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncfermi_dirac.o ..\specfunc\fermi_dirac.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncgegenbauer.o ..\specfunc\gegenbauer.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncgamma.o ..\specfunc\gamma.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncgamma_inc.o ..\specfunc\gamma_inc.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfunchyperg_0F1.o ..\specfunc\hyperg_0F1.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfunchyperg_2F0.o ..\specfunc\hyperg_2F0.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfunchyperg_1F1.o ..\specfunc\hyperg_1F1.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfunchyperg_2F1.o ..\specfunc\hyperg_2F1.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfunchyperg_U.o ..\specfunc\hyperg_U.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfunchyperg.o ..\specfunc\hyperg.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfunclaguerre.o ..\specfunc\laguerre.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfunclambert.o ..\specfunc\lambert.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfunclegendre_H3d.o ..\specfunc\legendre_H3d.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfunclegendre_Qn.o ..\specfunc\legendre_Qn.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfunclegendre_con.o ..\specfunc\legendre_con.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfunclegendre_poly.o ..\specfunc\legendre_poly.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfunclog.o ..\specfunc\log.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncpoch.o ..\specfunc\poch.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncpow_int.o ..\specfunc\pow_int.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncpsi.o ..\specfunc\psi.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncresult.o ..\specfunc\result.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncshint.o ..\specfunc\shint.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncsinint.o ..\specfunc\sinint.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfuncsynchrotron.o ..\specfunc\synchrotron.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfunctransport.o ..\specfunc\transport.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfunctrig.o ..\specfunc\trig.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dspecfunczeta.o ..\specfunc\zeta.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dstatisticsmean.o ..\statistics\mean.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dstatisticsvariance.o ..\statistics\variance.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dstatisticsabsdev.o ..\statistics\absdev.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dstatisticsskew.o ..\statistics\skew.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dstatisticskurtosis.o ..\statistics\kurtosis.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dstatisticslag1.o ..\statistics\lag1.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dstatisticsp_variance.o ..\statistics\p_variance.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dstatisticsminmax.o ..\statistics\minmax.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dstatisticsttest.o ..\statistics\ttest.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dstatisticsmedian.o ..\statistics\median.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dstatisticscovariance.o ..\statistics\covariance.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dstatisticsquantiles.o ..\statistics\quantiles.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dstatisticswmean.o ..\statistics\wmean.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dstatisticswvariance.o ..\statistics\wvariance.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dstatisticswabsdev.o ..\statistics\wabsdev.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dstatisticswskew.o ..\statistics\wskew.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dstatisticswkurtosis.o ..\statistics\wkurtosis.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dsumlevin_u.o ..\sum\levin_u.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dsumlevin_utrunc.o ..\sum\levin_utrunc.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dsumwork_u.o ..\sum\work_u.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dsumwork_utrunc.o ..\sum\work_utrunc.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dsysminmax.o ..\sys\minmax.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dsysprec.o ..\sys\prec.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dsyshypot.o ..\sys\hypot.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dsyslog1p.o ..\sys\log1p.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dsysexpm1.o ..\sys\expm1.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dsyscoerce.o ..\sys\coerce.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dsysinvhyp.o ..\sys\invhyp.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dsyspow_int.o ..\sys\pow_int.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dsysinfnan.o ..\sys\infnan.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dsysfdiv.o ..\sys\fdiv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dsysfcmp.o ..\sys\fcmp.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dsysldfrexp.o ..\sys\ldfrexp.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dtestresults.o ..\test\results.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dvectorinit.o ..\vector\init.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dvectorfile.o ..\vector\file.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dvectorvector.o ..\vector\vector.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dvectorcopy.o ..\vector\copy.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dvectorswap.o ..\vector\swap.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dvectorprop.o ..\vector\prop.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dvectorminmax.o ..\vector\minmax.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dvectoroper.o ..\vector\oper.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dvectorreim.o ..\vector\reim.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dvectorsubvector.o ..\vector\subvector.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dvectorview.o ..\vector\view.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dwaveletdwt.o ..\wavelet\dwt.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dwaveletwavelet.o ..\wavelet\wavelet.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dwaveletbspline.o ..\wavelet\bspline.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dwaveletdaubechies.o ..\wavelet\daubechies.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dwavelethaar.o ..\wavelet\haar.c

REM Compile cblas dll (Release) sources
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_sasum_dll.o ..\cblas\sasum.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_saxpy_dll.o ..\cblas\saxpy.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_scasum_dll.o ..\cblas\scasum.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_scnrm2_dll.o ..\cblas\scnrm2.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_scopy_dll.o ..\cblas\scopy.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_sdot_dll.o ..\cblas\sdot.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_sdsdot_dll.o ..\cblas\sdsdot.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_sgbmv_dll.o ..\cblas\sgbmv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_sgemm_dll.o ..\cblas\sgemm.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_sgemv_dll.o ..\cblas\sgemv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_sger_dll.o ..\cblas\sger.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_snrm2_dll.o ..\cblas\snrm2.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_srot_dll.o ..\cblas\srot.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_srotg_dll.o ..\cblas\srotg.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_srotm_dll.o ..\cblas\srotm.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_srotmg_dll.o ..\cblas\srotmg.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_ssbmv_dll.o ..\cblas\ssbmv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_sscal_dll.o ..\cblas\sscal.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_sspmv_dll.o ..\cblas\sspmv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_sspr_dll.o ..\cblas\sspr.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_sspr2_dll.o ..\cblas\sspr2.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_sswap_dll.o ..\cblas\sswap.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_ssymm_dll.o ..\cblas\ssymm.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_ssymv_dll.o ..\cblas\ssymv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_ssyr_dll.o ..\cblas\ssyr.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_ssyr2_dll.o ..\cblas\ssyr2.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_ssyr2k_dll.o ..\cblas\ssyr2k.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_ssyrk_dll.o ..\cblas\ssyrk.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_stbmv_dll.o ..\cblas\stbmv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_stbsv_dll.o ..\cblas\stbsv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_stpmv_dll.o ..\cblas\stpmv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_stpsv_dll.o ..\cblas\stpsv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_strmm_dll.o ..\cblas\strmm.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_strmv_dll.o ..\cblas\strmv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_strsm_dll.o ..\cblas\strsm.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_strsv_dll.o ..\cblas\strsv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_dasum_dll.o ..\cblas\dasum.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_daxpy_dll.o ..\cblas\daxpy.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_dcopy_dll.o ..\cblas\dcopy.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_ddot_dll.o ..\cblas\ddot.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_dgbmv_dll.o ..\cblas\dgbmv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_dgemm_dll.o ..\cblas\dgemm.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_dgemv_dll.o ..\cblas\dgemv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_dger_dll.o ..\cblas\dger.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_dnrm2_dll.o ..\cblas\dnrm2.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_drot_dll.o ..\cblas\drot.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_drotg_dll.o ..\cblas\drotg.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_drotm_dll.o ..\cblas\drotm.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_drotmg_dll.o ..\cblas\drotmg.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_dsbmv_dll.o ..\cblas\dsbmv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_dscal_dll.o ..\cblas\dscal.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_dsdot_dll.o ..\cblas\dsdot.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_dspmv_dll.o ..\cblas\dspmv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_dspr_dll.o ..\cblas\dspr.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_dspr2_dll.o ..\cblas\dspr2.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_dswap_dll.o ..\cblas\dswap.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_dsymm_dll.o ..\cblas\dsymm.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_dsymv_dll.o ..\cblas\dsymv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_dsyr_dll.o ..\cblas\dsyr.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_dsyr2_dll.o ..\cblas\dsyr2.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_dsyr2k_dll.o ..\cblas\dsyr2k.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_dsyrk_dll.o ..\cblas\dsyrk.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_dtbmv_dll.o ..\cblas\dtbmv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_dtbsv_dll.o ..\cblas\dtbsv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_dtpmv_dll.o ..\cblas\dtpmv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_dtpsv_dll.o ..\cblas\dtpsv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_dtrmm_dll.o ..\cblas\dtrmm.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_dtrmv_dll.o ..\cblas\dtrmv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_dtrsm_dll.o ..\cblas\dtrsm.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_dtrsv_dll.o ..\cblas\dtrsv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_dzasum_dll.o ..\cblas\dzasum.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_dznrm2_dll.o ..\cblas\dznrm2.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_caxpy_dll.o ..\cblas\caxpy.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_ccopy_dll.o ..\cblas\ccopy.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_cdotc_sub_dll.o ..\cblas\cdotc_sub.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_cdotu_sub_dll.o ..\cblas\cdotu_sub.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_cgbmv_dll.o ..\cblas\cgbmv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_cgemm_dll.o ..\cblas\cgemm.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_cgemv_dll.o ..\cblas\cgemv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_cgerc_dll.o ..\cblas\cgerc.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_cgeru_dll.o ..\cblas\cgeru.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_chbmv_dll.o ..\cblas\chbmv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_chemm_dll.o ..\cblas\chemm.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_chemv_dll.o ..\cblas\chemv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_cher_dll.o ..\cblas\cher.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_cher2_dll.o ..\cblas\cher2.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_cher2k_dll.o ..\cblas\cher2k.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_cherk_dll.o ..\cblas\cherk.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_chpmv_dll.o ..\cblas\chpmv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_chpr_dll.o ..\cblas\chpr.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_chpr2_dll.o ..\cblas\chpr2.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_cscal_dll.o ..\cblas\cscal.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_csscal_dll.o ..\cblas\csscal.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_cswap_dll.o ..\cblas\cswap.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_csymm_dll.o ..\cblas\csymm.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_csyr2k_dll.o ..\cblas\csyr2k.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_csyrk_dll.o ..\cblas\csyrk.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_ctbmv_dll.o ..\cblas\ctbmv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_ctbsv_dll.o ..\cblas\ctbsv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_ctpmv_dll.o ..\cblas\ctpmv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_ctpsv_dll.o ..\cblas\ctpsv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_ctrmm_dll.o ..\cblas\ctrmm.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_ctrmv_dll.o ..\cblas\ctrmv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_ctrsm_dll.o ..\cblas\ctrsm.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_ctrsv_dll.o ..\cblas\ctrsv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_zaxpy_dll.o ..\cblas\zaxpy.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_zcopy_dll.o ..\cblas\zcopy.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_zdotc_sub_dll.o ..\cblas\zdotc_sub.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_zdotu_sub_dll.o ..\cblas\zdotu_sub.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_zdscal_dll.o ..\cblas\zdscal.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_zgbmv_dll.o ..\cblas\zgbmv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_zgemm_dll.o ..\cblas\zgemm.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_zgemv_dll.o ..\cblas\zgemv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_zgerc_dll.o ..\cblas\zgerc.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_zgeru_dll.o ..\cblas\zgeru.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_zhbmv_dll.o ..\cblas\zhbmv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_zhemm_dll.o ..\cblas\zhemm.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_zhemv_dll.o ..\cblas\zhemv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_zher_dll.o ..\cblas\zher.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_zher2_dll.o ..\cblas\zher2.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_zher2k_dll.o ..\cblas\zher2k.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_zherk_dll.o ..\cblas\zherk.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_zhpmv_dll.o ..\cblas\zhpmv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_zhpr_dll.o ..\cblas\zhpr.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_zhpr2_dll.o ..\cblas\zhpr2.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_zscal_dll.o ..\cblas\zscal.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_zswap_dll.o ..\cblas\zswap.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_zsymm_dll.o ..\cblas\zsymm.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_zsyr2k_dll.o ..\cblas\zsyr2k.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_zsyrk_dll.o ..\cblas\zsyrk.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_ztbmv_dll.o ..\cblas\ztbmv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_ztbsv_dll.o ..\cblas\ztbsv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_ztpmv_dll.o ..\cblas\ztpmv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_ztpsv_dll.o ..\cblas\ztpsv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_ztrmm_dll.o ..\cblas\ztrmm.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_ztrmv_dll.o ..\cblas\ztrmv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_ztrsm_dll.o ..\cblas\ztrsm.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_ztrsv_dll.o ..\cblas\ztrsv.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_icamax_dll.o ..\cblas\icamax.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_idamax_dll.o ..\cblas\idamax.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_isamax_dll.o ..\cblas\isamax.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_izamax_dll.o ..\cblas\izamax.c
%_COMPILE% %_OPT_RELEASE% %_OPT_DLL% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_xerbla_dll.o ..\cblas\xerbla.c

REM Make cblas dll (Release) library
cd .\Release\mingw\cblas
%_COMPILE% %_DLL_LINK_FLAG%..\libgslcblas_dll.a %_COMP_OUTPUT_FLAG% ..\libgslcblas.dll cblas_sasum_dll.o cblas_saxpy_dll.o cblas_scasum_dll.o cblas_scnrm2_dll.o cblas_scopy_dll.o cblas_sdot_dll.o cblas_sdsdot_dll.o cblas_sgbmv_dll.o cblas_sgemm_dll.o cblas_sgemv_dll.o cblas_sger_dll.o cblas_snrm2_dll.o cblas_srot_dll.o cblas_srotg_dll.o cblas_srotm_dll.o cblas_srotmg_dll.o cblas_ssbmv_dll.o cblas_sscal_dll.o cblas_sspmv_dll.o cblas_sspr_dll.o cblas_sspr2_dll.o cblas_sswap_dll.o cblas_ssymm_dll.o cblas_ssymv_dll.o cblas_ssyr_dll.o cblas_ssyr2_dll.o cblas_ssyr2k_dll.o cblas_ssyrk_dll.o cblas_stbmv_dll.o cblas_stbsv_dll.o cblas_stpmv_dll.o cblas_stpsv_dll.o cblas_strmm_dll.o cblas_strmv_dll.o cblas_strsm_dll.o cblas_strsv_dll.o cblas_dasum_dll.o cblas_daxpy_dll.o cblas_dcopy_dll.o cblas_ddot_dll.o cblas_dgbmv_dll.o cblas_dgemm_dll.o cblas_dgemv_dll.o cblas_dger_dll.o cblas_dnrm2_dll.o cblas_drot_dll.o cblas_drotg_dll.o cblas_drotm_dll.o cblas_drotmg_dll.o cblas_dsbmv_dll.o cblas_dscal_dll.o cblas_dsdot_dll.o cblas_dspmv_dll.o cblas_dspr_dll.o cblas_dspr2_dll.o cblas_dswap_dll.o cblas_dsymm_dll.o cblas_dsymv_dll.o cblas_dsyr_dll.o cblas_dsyr2_dll.o cblas_dsyr2k_dll.o cblas_dsyrk_dll.o cblas_dtbmv_dll.o cblas_dtbsv_dll.o cblas_dtpmv_dll.o cblas_dtpsv_dll.o cblas_dtrmm_dll.o cblas_dtrmv_dll.o cblas_dtrsm_dll.o cblas_dtrsv_dll.o cblas_dzasum_dll.o cblas_dznrm2_dll.o cblas_caxpy_dll.o cblas_ccopy_dll.o cblas_cdotc_sub_dll.o cblas_cdotu_sub_dll.o cblas_cgbmv_dll.o cblas_cgemm_dll.o cblas_cgemv_dll.o cblas_cgerc_dll.o cblas_cgeru_dll.o cblas_chbmv_dll.o cblas_chemm_dll.o cblas_chemv_dll.o cblas_cher_dll.o cblas_cher2_dll.o cblas_cher2k_dll.o cblas_cherk_dll.o cblas_chpmv_dll.o cblas_chpr_dll.o cblas_chpr2_dll.o cblas_cscal_dll.o cblas_csscal_dll.o cblas_cswap_dll.o cblas_csymm_dll.o cblas_csyr2k_dll.o cblas_csyrk_dll.o cblas_ctbmv_dll.o cblas_ctbsv_dll.o cblas_ctpmv_dll.o cblas_ctpsv_dll.o cblas_ctrmm_dll.o cblas_ctrmv_dll.o cblas_ctrsm_dll.o cblas_ctrsv_dll.o cblas_zaxpy_dll.o cblas_zcopy_dll.o cblas_zdotc_sub_dll.o cblas_zdotu_sub_dll.o cblas_zdscal_dll.o cblas_zgbmv_dll.o cblas_zgemm_dll.o cblas_zgemv_dll.o cblas_zgerc_dll.o cblas_zgeru_dll.o cblas_zhbmv_dll.o cblas_zhemm_dll.o cblas_zhemv_dll.o cblas_zher_dll.o cblas_zher2_dll.o cblas_zher2k_dll.o cblas_zherk_dll.o cblas_zhpmv_dll.o cblas_zhpr_dll.o cblas_zhpr2_dll.o cblas_zscal_dll.o cblas_zswap_dll.o cblas_zsymm_dll.o cblas_zsyr2k_dll.o cblas_zsyrk_dll.o cblas_ztbmv_dll.o cblas_ztbsv_dll.o cblas_ztpmv_dll.o cblas_ztpsv_dll.o cblas_ztrmm_dll.o cblas_ztrmv_dll.o cblas_ztrsm_dll.o cblas_ztrsv_dll.o cblas_icamax_dll.o cblas_idamax_dll.o cblas_isamax_dll.o cblas_izamax_dll.o cblas_xerbla_dll.o
cd ..\..\..

REM Make libgsl dll (Release) library
cd .\Release\mingw\temp
%_COMPILE% %_DLL_LINK_FLAG%..\libgsl_dll.a ..\libgslcblas.dll %_COMP_OUTPUT_FLAG% ..\libgsl.dll dversion.o dblasblas.o dblockinit.o dblockfile.o dblockblock.o dcdfbeta.o dcdfbetainv.o dcdfcauchy.o dcdfcauchyinv.o dcdfchisq.o dcdfchisqinv.o dcdfexponential.o dcdfexponentialinv.o dcdfexppow.o dcdffdist.o dcdffdistinv.o dcdfflat.o dcdfflatinv.o dcdfgamma.o dcdfgammainv.o dcdfgauss.o dcdfgaussinv.o dcdfgumbel1.o dcdfgumbel1inv.o dcdfgumbel2.o dcdfgumbel2inv.o dcdflaplace.o dcdflaplaceinv.o dcdflogistic.o dcdflogisticinv.o dcdflognormal.o dcdflognormalinv.o dcdfpareto.o dcdfparetoinv.o dcdfrayleigh.o dcdfrayleighinv.o dcdftdist.o dcdftdistinv.o dcdfweibull.o dcdfweibullinv.o dcdfbinomial.o dcdfpoisson.o dcdfgeometric.o dcdfnbinomial.o dcdfpascal.o dcdfhypergeometric.o dchebderiv.o dchebeval.o dchebinit.o dchebinteg.o dcombinationinit.o dcombinationfile.o dcombinationcombination.o dcomplexmath.o dderivderiv.o ddhtdht.o ddiffdiff.o deigenjacobi.o deigensymm.o deigensymmv.o deigenherm.o deigenhermv.o deigensort.o derrerror.o derrstream.o derrmessage.o derrstrerror.o dfftdft.o dfftfft.o dfitlinear.o dhistogramadd.o dhistogramget.o dhistograminit.o dhistogramparams.o dhistogramreset.o dhistogramfile.o dhistogrampdf.o dhistogramadd2d.o dhistogramget2d.o dhistograminit2d.o dhistogramparams2d.o dhistogramreset2d.o dhistogramfile2d.o dhistogrampdf2d.o dhistogramcalloc_range.o dhistogramcalloc_range2d.o dhistogramcopy.o dhistogramcopy2d.o dhistogrammaxval.o dhistogrammaxval2d.o dhistogramoper.o dhistogramoper2d.o dhistogramstat.o dhistogramstat2d.o dieee-utilsprint.o dieee-utilsmake_rep.o dieee-utilsenv.o dieee-utilsfp.o dieee-utilsread.o dintegrationqk15.o dintegrationqk21.o dintegrationqk31.o dintegrationqk41.o dintegrationqk51.o dintegrationqk61.o dintegrationqk.o dintegrationqng.o dintegrationqag.o dintegrationqags.o dintegrationqagp.o dintegrationworkspace.o dintegrationqcheb.o dintegrationqawc.o dintegrationqmomo.o dintegrationqaws.o dintegrationqmomof.o dintegrationqawo.o dintegrationqawf.o dinterpolationaccel.o dinterpolationakima.o dinterpolationbsearch.o dinterpolationcspline.o dinterpolationinterp.o dinterpolationlinear.o dinterpolationspline.o dinterpolationpoly.o dlinalgmultiply.o dlinalgexponential.o dlinalgtridiag.o dlinalglu.o dlinalgluc.o dlinalghh.o dlinalgqr.o dlinalgqrpt.o dlinalglq.o dlinalgptlq.o dlinalgsvd.o dlinalghouseholder.o dlinalghouseholdercomplex.o dlinalgcholesky.o dlinalgsymmtd.o dlinalghermtd.o dlinalgbidiag.o dlinalgbalance.o dmatrixinit.o dmatrixmatrix.o dmatrixfile.o dmatrixrowcol.o dmatrixswap.o dmatrixcopy.o dmatrixminmax.o dmatrixprop.o dmatrixoper.o dmatrixgetset.o dmatrixview.o dmatrixsubmatrix.o dminfsolver.o dmingolden.o dminbrent.o dminconvergence.o dminbracketing.o dmontemiser.o dmonteplain.o dmontevegas.o dmultifitmultilinear.o dmultifitwork.o dmultifitlmder.o dmultifitfsolver.o dmultifitfdfsolver.o dmultifitconvergence.o dmultifitgradient.o dmultifitcovar.o dmultiminfdfminimizer.o dmultiminsteepest_descent.o dmultiminconjugate_fr.o dmultiminconjugate_pr.o dmultiminconvergence.o dmultimindiff.o dmultiminvector_bfgs.o dmultiminfminimizer.o dmultiminsimplex.o dmultirootsfdjac.o dmultirootsfsolver.o dmultirootsfdfsolver.o dmultirootsconvergence.o dmultirootsnewton.o dmultirootsgnewton.o dmultirootsdnewton.o dmultirootsbroyden.o dmultirootshybrid.o dmultirootshybridj.o dntuplentuple.o dode-initvalcontrol.o dode-initvalcstd.o dode-initvalcscal.o dode-initvalevolve.o dode-initvalstep.o dode-initvalrk2.o dode-initvalrk2imp.o dode-initvalrk2simp.o dode-initvalrk4.o dode-initvalrk4imp.o dode-initvalrkf45.o dode-initvalrk8pd.o dode-initvalrkck.o dode-initvalbsimp.o dode-initvalgear1.o dode-initvalgear2.o dpermutationinit.o dpermutationfile.o dpermutationpermutation.o dpermutationpermute.o dpermutationcanonical.o dpolydd.o dpolyeval.o dpolysolve_quadratic.o dpolysolve_cubic.o dpolyzsolve_quadratic.o dpolyzsolve_cubic.o dpolyzsolve.o dpolyzsolve_init.o dqrngqrng.o dqrngniederreiter-2.o dqrngsobol.o drandistbernoulli.o drandistbeta.o drandistbigauss.o drandistbinomial.o drandistcauchy.o drandistchisq.o drandistdirichlet.o drandistdiscrete.o drandisterlang.o drandistexponential.o drandistexppow.o drandistfdist.o drandistflat.o drandistgamma.o drandistgauss.o drandistgausszig.o drandistgausstail.o drandistgeometric.o drandistgumbel.o drandisthyperg.o drandistlaplace.o drandistlevy.o drandistlogarithmic.o drandistlogistic.o drandistlognormal.o drandistmultinomial.o drandistnbinomial.o drandistpareto.o drandistpascal.o drandistpoisson.o drandistrayleigh.o drandistshuffle.o drandistsphere.o drandisttdist.o drandistweibull.o drandistlandau.o drandistbinomial_tpe.o drngborosh13.o drngcmrg.o drngcoveyou.o drngdefault.o drngfile.o drngfishman18.o drngfishman20.o drngfishman2x.o drnggfsr4.o drngknuthran2.o drngknuthran.o drnglecuyer21.o drngminstd.o drngmrg.o drngmt.o drngr250.o drngran0.o drngran1.o drngran2.o drngran3.o drngrand48.o drngrand.o drngrandom.o drngrandu.o drngranf.o drngranlux.o drngranlxd.o drngranlxs.o drngranmar.o drngrng.o drngslatec.o drngtaus.o drngtaus113.o drngtransputer.o drngtt.o drngtypes.o drnguni32.o drnguni.o drngvax.o drngwaterman14.o drngzuf.o drootsbisection.o drootsbrent.o drootsfalsepos.o drootsnewton.o drootssecant.o drootssteffenson.o drootsconvergence.o drootsfsolver.o drootsfdfsolver.o dsimansiman.o dsortsort.o dsortsortind.o dsortsortvec.o dsortsortvecind.o dsortsubset.o dsortsubsetind.o dspecfuncairy.o dspecfuncairy_der.o dspecfuncairy_zero.o dspecfuncatanint.o dspecfuncbessel.o dspecfuncbessel_I0.o dspecfuncbessel_I1.o dspecfuncbessel_In.o dspecfuncbessel_Inu.o dspecfuncbessel_J0.o dspecfuncbessel_J1.o dspecfuncbessel_Jn.o dspecfuncbessel_Jnu.o dspecfuncbessel_K0.o dspecfuncbessel_K1.o dspecfuncbessel_Kn.o dspecfuncbessel_Knu.o dspecfuncbessel_Y0.o dspecfuncbessel_Y1.o dspecfuncbessel_Yn.o dspecfuncbessel_Ynu.o dspecfuncbessel_amp_phase.o dspecfuncbessel_i.o dspecfuncbessel_j.o dspecfuncbessel_k.o dspecfuncbessel_olver.o dspecfuncbessel_temme.o dspecfuncbessel_y.o dspecfuncbessel_zero.o dspecfuncbessel_sequence.o dspecfuncbeta.o dspecfuncbeta_inc.o dspecfuncclausen.o dspecfunccoulomb.o dspecfunccoupling.o dspecfunccoulomb_bound.o dspecfuncdawson.o dspecfuncdebye.o dspecfuncdilog.o dspecfuncelementary.o dspecfuncellint.o dspecfuncelljac.o dspecfuncerfc.o dspecfuncexp.o dspecfuncexpint.o dspecfuncexpint3.o dspecfuncfermi_dirac.o dspecfuncgegenbauer.o dspecfuncgamma.o dspecfuncgamma_inc.o dspecfunchyperg_0F1.o dspecfunchyperg_2F0.o dspecfunchyperg_1F1.o dspecfunchyperg_2F1.o dspecfunchyperg_U.o dspecfunchyperg.o dspecfunclaguerre.o dspecfunclambert.o dspecfunclegendre_H3d.o dspecfunclegendre_Qn.o dspecfunclegendre_con.o dspecfunclegendre_poly.o dspecfunclog.o dspecfuncpoch.o dspecfuncpow_int.o dspecfuncpsi.o dspecfuncresult.o dspecfuncshint.o dspecfuncsinint.o dspecfuncsynchrotron.o dspecfunctransport.o dspecfunctrig.o dspecfunczeta.o dstatisticsmean.o dstatisticsvariance.o dstatisticsabsdev.o dstatisticsskew.o dstatisticskurtosis.o dstatisticslag1.o dstatisticsp_variance.o dstatisticsminmax.o dstatisticsttest.o dstatisticsmedian.o dstatisticscovariance.o dstatisticsquantiles.o dstatisticswmean.o dstatisticswvariance.o dstatisticswabsdev.o dstatisticswskew.o dstatisticswkurtosis.o dsumlevin_u.o dsumlevin_utrunc.o dsumwork_u.o dsumwork_utrunc.o dsysminmax.o dsysprec.o dsyshypot.o dsyslog1p.o dsysexpm1.o dsyscoerce.o dsysinvhyp.o dsyspow_int.o dsysinfnan.o dsysfdiv.o dsysfcmp.o dsysldfrexp.o dtestresults.o dvectorinit.o dvectorfile.o dvectorvector.o dvectorcopy.o dvectorswap.o dvectorprop.o dvectorminmax.o dvectoroper.o dvectorreim.o dvectorsubvector.o dvectorview.o dwaveletdwt.o dwaveletwavelet.o dwaveletbspline.o dwaveletdaubechies.o dwavelethaar.o
cd ..\..\..

REM Compile cblas test (debug) sources
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test.o ..\cblas\test.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_amax.o ..\cblas\test_amax.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_asum.o ..\cblas\test_asum.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_axpy.o ..\cblas\test_axpy.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_copy.o ..\cblas\test_copy.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_dot.o ..\cblas\test_dot.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_gbmv.o ..\cblas\test_gbmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_gemm.o ..\cblas\test_gemm.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_gemv.o ..\cblas\test_gemv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_ger.o ..\cblas\test_ger.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_hbmv.o ..\cblas\test_hbmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_hemm.o ..\cblas\test_hemm.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_hemv.o ..\cblas\test_hemv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_her.o ..\cblas\test_her.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_her2.o ..\cblas\test_her2.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_her2k.o ..\cblas\test_her2k.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_herk.o ..\cblas\test_herk.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_hpmv.o ..\cblas\test_hpmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_hpr.o ..\cblas\test_hpr.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_hpr2.o ..\cblas\test_hpr2.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_nrm2.o ..\cblas\test_nrm2.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_rot.o ..\cblas\test_rot.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_rotg.o ..\cblas\test_rotg.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_rotm.o ..\cblas\test_rotm.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_rotmg.o ..\cblas\test_rotmg.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_sbmv.o ..\cblas\test_sbmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_scal.o ..\cblas\test_scal.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_spmv.o ..\cblas\test_spmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_spr.o ..\cblas\test_spr.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_spr2.o ..\cblas\test_spr2.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_swap.o ..\cblas\test_swap.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_symm.o ..\cblas\test_symm.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_symv.o ..\cblas\test_symv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_syr.o ..\cblas\test_syr.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_syr2.o ..\cblas\test_syr2.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_syr2k.o ..\cblas\test_syr2k.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_syrk.o ..\cblas\test_syrk.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_tbmv.o ..\cblas\test_tbmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_tbsv.o ..\cblas\test_tbsv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_tpmv.o ..\cblas\test_tpmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_tpsv.o ..\cblas\test_tpsv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_trmm.o ..\cblas\test_trmm.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_trmv.o ..\cblas\test_trmv.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_trsm.o ..\cblas\test_trsm.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\cblas\cblas_test_trsv.o ..\cblas\test_trsv.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_cblas.exe .\Release\mingw\cblas\cblas_test.o .\Release\mingw\cblas\cblas_test_amax.o .\Release\mingw\cblas\cblas_test_asum.o .\Release\mingw\cblas\cblas_test_axpy.o .\Release\mingw\cblas\cblas_test_copy.o .\Release\mingw\cblas\cblas_test_dot.o .\Release\mingw\cblas\cblas_test_gbmv.o .\Release\mingw\cblas\cblas_test_gemm.o .\Release\mingw\cblas\cblas_test_gemv.o .\Release\mingw\cblas\cblas_test_ger.o .\Release\mingw\cblas\cblas_test_hbmv.o .\Release\mingw\cblas\cblas_test_hemm.o .\Release\mingw\cblas\cblas_test_hemv.o .\Release\mingw\cblas\cblas_test_her.o .\Release\mingw\cblas\cblas_test_her2.o .\Release\mingw\cblas\cblas_test_her2k.o .\Release\mingw\cblas\cblas_test_herk.o .\Release\mingw\cblas\cblas_test_hpmv.o .\Release\mingw\cblas\cblas_test_hpr.o .\Release\mingw\cblas\cblas_test_hpr2.o .\Release\mingw\cblas\cblas_test_nrm2.o .\Release\mingw\cblas\cblas_test_rot.o .\Release\mingw\cblas\cblas_test_rotg.o .\Release\mingw\cblas\cblas_test_rotm.o .\Release\mingw\cblas\cblas_test_rotmg.o .\Release\mingw\cblas\cblas_test_sbmv.o .\Release\mingw\cblas\cblas_test_scal.o .\Release\mingw\cblas\cblas_test_spmv.o .\Release\mingw\cblas\cblas_test_spr.o .\Release\mingw\cblas\cblas_test_spr2.o .\Release\mingw\cblas\cblas_test_swap.o .\Release\mingw\cblas\cblas_test_symm.o .\Release\mingw\cblas\cblas_test_symv.o .\Release\mingw\cblas\cblas_test_syr.o .\Release\mingw\cblas\cblas_test_syr2.o .\Release\mingw\cblas\cblas_test_syr2k.o .\Release\mingw\cblas\cblas_test_syrk.o .\Release\mingw\cblas\cblas_test_tbmv.o .\Release\mingw\cblas\cblas_test_tbsv.o .\Release\mingw\cblas\cblas_test_tpmv.o .\Release\mingw\cblas\cblas_test_tpsv.o .\Release\mingw\cblas\cblas_test_trmm.o .\Release\mingw\cblas\cblas_test_trmv.o .\Release\mingw\cblas\cblas_test_trsm.o .\Release\mingw\cblas\cblas_test_trsv.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_cblas_dll.exe .\Release\mingw\cblas\cblas_test.o .\Release\mingw\cblas\cblas_test_amax.o .\Release\mingw\cblas\cblas_test_asum.o .\Release\mingw\cblas\cblas_test_axpy.o .\Release\mingw\cblas\cblas_test_copy.o .\Release\mingw\cblas\cblas_test_dot.o .\Release\mingw\cblas\cblas_test_gbmv.o .\Release\mingw\cblas\cblas_test_gemm.o .\Release\mingw\cblas\cblas_test_gemv.o .\Release\mingw\cblas\cblas_test_ger.o .\Release\mingw\cblas\cblas_test_hbmv.o .\Release\mingw\cblas\cblas_test_hemm.o .\Release\mingw\cblas\cblas_test_hemv.o .\Release\mingw\cblas\cblas_test_her.o .\Release\mingw\cblas\cblas_test_her2.o .\Release\mingw\cblas\cblas_test_her2k.o .\Release\mingw\cblas\cblas_test_herk.o .\Release\mingw\cblas\cblas_test_hpmv.o .\Release\mingw\cblas\cblas_test_hpr.o .\Release\mingw\cblas\cblas_test_hpr2.o .\Release\mingw\cblas\cblas_test_nrm2.o .\Release\mingw\cblas\cblas_test_rot.o .\Release\mingw\cblas\cblas_test_rotg.o .\Release\mingw\cblas\cblas_test_rotm.o .\Release\mingw\cblas\cblas_test_rotmg.o .\Release\mingw\cblas\cblas_test_sbmv.o .\Release\mingw\cblas\cblas_test_scal.o .\Release\mingw\cblas\cblas_test_spmv.o .\Release\mingw\cblas\cblas_test_spr.o .\Release\mingw\cblas\cblas_test_spr2.o .\Release\mingw\cblas\cblas_test_swap.o .\Release\mingw\cblas\cblas_test_symm.o .\Release\mingw\cblas\cblas_test_symv.o .\Release\mingw\cblas\cblas_test_syr.o .\Release\mingw\cblas\cblas_test_syr2.o .\Release\mingw\cblas\cblas_test_syr2k.o .\Release\mingw\cblas\cblas_test_syrk.o .\Release\mingw\cblas\cblas_test_tbmv.o .\Release\mingw\cblas\cblas_test_tbsv.o .\Release\mingw\cblas\cblas_test_tpmv.o .\Release\mingw\cblas\cblas_test_tpsv.o .\Release\mingw\cblas\cblas_test_trmm.o .\Release\mingw\cblas\cblas_test_trmv.o .\Release\mingw\cblas\cblas_test_trsm.o .\Release\mingw\cblas\cblas_test_trsv.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

REM Make libgsl test (Release) executables
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\block_test.o ..\block\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_block.exe .\Release\mingw\temp\block_test.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_block_dll.exe .\Release\mingw\temp\block_test.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cdf_test.o ..\cdf\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_cdf.exe .\Release\mingw\temp\cdf_test.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_cdf_dll.exe .\Release\mingw\temp\cdf_test.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\cheb_test.o ..\cheb\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_cheb.exe .\Release\mingw\temp\cheb_test.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_cheb_dll.exe .\Release\mingw\temp\cheb_test.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\combination_test.o ..\combination\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_combination.exe .\Release\mingw\temp\combination_test.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_combination_dll.exe .\Release\mingw\temp\combination_test.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\complex_test.o ..\complex\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_complex.exe .\Release\mingw\temp\complex_test.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_complex_dll.exe .\Release\mingw\temp\complex_test.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\const_test.o ..\const\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_const.exe .\Release\mingw\temp\const_test.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_const_dll.exe .\Release\mingw\temp\const_test.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\deriv_test.o ..\deriv\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_deriv.exe .\Release\mingw\temp\deriv_test.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_deriv_dll.exe .\Release\mingw\temp\deriv_test.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\dht_test.o ..\dht\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_dht.exe .\Release\mingw\temp\dht_test.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_dht_dll.exe .\Release\mingw\temp\dht_test.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\diff_test.o ..\diff\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_diff.exe .\Release\mingw\temp\diff_test.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_diff_dll.exe .\Release\mingw\temp\diff_test.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\eigen_test.o ..\eigen\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_eigen.exe .\Release\mingw\temp\eigen_test.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_eigen_dll.exe .\Release\mingw\temp\eigen_test.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\fft_test.o ..\fft\test.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\fft_signals.o ..\fft\signals.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_fft.exe .\Release\mingw\temp\fft_test.o .\Release\mingw\temp\fft_signals.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_fft_dll.exe .\Release\mingw\temp\fft_test.o .\Release\mingw\temp\fft_signals.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\fit_test.o ..\fit\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_fit.exe .\Release\mingw\temp\fit_test.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_fit_dll.exe .\Release\mingw\temp\fit_test.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_test.o ..\histogram\test.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_test1d.o ..\histogram\test1d.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_test2d.o ..\histogram\test2d.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_test1d_resample.o ..\histogram\test1d_resample.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_test2d_resample.o ..\histogram\test2d_resample.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_test1d_trap.o ..\histogram\test1d_trap.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\histogram_test2d_trap.o ..\histogram\test2d_trap.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_histogram.exe .\Release\mingw\temp\histogram_test.o .\Release\mingw\temp\histogram_test1d.o .\Release\mingw\temp\histogram_test2d.o .\Release\mingw\temp\histogram_test1d_resample.o .\Release\mingw\temp\histogram_test2d_resample.o .\Release\mingw\temp\histogram_test1d_trap.o .\Release\mingw\temp\histogram_test2d_trap.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_histogram_dll.exe .\Release\mingw\temp\histogram_test.o .\Release\mingw\temp\histogram_test1d.o .\Release\mingw\temp\histogram_test2d.o .\Release\mingw\temp\histogram_test1d_resample.o .\Release\mingw\temp\histogram_test2d_resample.o .\Release\mingw\temp\histogram_test1d_trap.o .\Release\mingw\temp\histogram_test2d_trap.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ieee-utils_test.o ..\ieee-utils\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_ieee-utils.exe .\Release\mingw\temp\ieee-utils_test.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_ieee-utils_dll.exe .\Release\mingw\temp\ieee-utils_test.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\integration_test.o ..\integration\test.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\integration_tests.o ..\integration\tests.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_integration.exe .\Release\mingw\temp\integration_test.o .\Release\mingw\temp\integration_tests.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_integration_dll.exe .\Release\mingw\temp\integration_test.o .\Release\mingw\temp\integration_tests.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\interpolation_test.o ..\interpolation\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_interpolation.exe .\Release\mingw\temp\interpolation_test.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_interpolation_dll.exe .\Release\mingw\temp\interpolation_test.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\linalg_test.o ..\linalg\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_linalg.exe .\Release\mingw\temp\linalg_test.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_linalg_dll.exe .\Release\mingw\temp\linalg_test.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\matrix_test.o ..\matrix\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_matrix.exe .\Release\mingw\temp\matrix_test.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_matrix_dll.exe .\Release\mingw\temp\matrix_test.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\min_test.o ..\min\test.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\min_test_funcs.o ..\min\test_funcs.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_min.exe .\Release\mingw\temp\min_test.o .\Release\mingw\temp\min_test_funcs.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_min_dll.exe .\Release\mingw\temp\min_test.o .\Release\mingw\temp\min_test_funcs.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\monte_test.o ..\monte\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_monte.exe .\Release\mingw\temp\monte_test.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_monte_dll.exe .\Release\mingw\temp\monte_test.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multifit_test.o ..\multifit\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_multifit.exe .\Release\mingw\temp\multifit_test.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_multifit_dll.exe .\Release\mingw\temp\multifit_test.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multimin_test.o ..\multimin\test.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multimin_test_funcs.o ..\multimin\test_funcs.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_multimin.exe .\Release\mingw\temp\multimin_test.o .\Release\mingw\temp\multimin_test_funcs.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_multimin_dll.exe .\Release\mingw\temp\multimin_test.o .\Release\mingw\temp\multimin_test_funcs.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multiroots_test.o ..\multiroots\test.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\multiroots_test_funcs.o ..\multiroots\test_funcs.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_multiroots.exe .\Release\mingw\temp\multiroots_test.o .\Release\mingw\temp\multiroots_test_funcs.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_multiroots_dll.exe .\Release\mingw\temp\multiroots_test.o .\Release\mingw\temp\multiroots_test_funcs.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ntuple_test.o ..\ntuple\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_ntuple.exe .\Release\mingw\temp\ntuple_test.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_ntuple_dll.exe .\Release\mingw\temp\ntuple_test.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ode-initval_test.o ..\ode-initval\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_ode-initval.exe .\Release\mingw\temp\ode-initval_test.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_ode-initval_dll.exe .\Release\mingw\temp\ode-initval_test.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\permutation_test.o ..\permutation\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_permutation.exe .\Release\mingw\temp\permutation_test.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_permutation_dll.exe .\Release\mingw\temp\permutation_test.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\poly_test.o ..\poly\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_poly.exe .\Release\mingw\temp\poly_test.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_poly_dll.exe .\Release\mingw\temp\poly_test.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\qrng_test.o ..\qrng\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_qrng.exe .\Release\mingw\temp\qrng_test.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_qrng_dll.exe .\Release\mingw\temp\qrng_test.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\randist_test.o ..\randist\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_randist.exe .\Release\mingw\temp\randist_test.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_randist_dll.exe .\Release\mingw\temp\randist_test.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\rng_test.o ..\rng\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_rng.exe .\Release\mingw\temp\rng_test.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_rng_dll.exe .\Release\mingw\temp\rng_test.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\roots_test.o ..\roots\test.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\roots_test_funcs.o ..\roots\test_funcs.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_roots.exe .\Release\mingw\temp\roots_test.o .\Release\mingw\temp\roots_test_funcs.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_roots_dll.exe .\Release\mingw\temp\roots_test.o .\Release\mingw\temp\roots_test_funcs.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\siman_test.o ..\siman\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_siman.exe .\Release\mingw\temp\siman_test.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_siman_dll.exe .\Release\mingw\temp\siman_test.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\sort_test.o ..\sort\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_sort.exe .\Release\mingw\temp\sort_test.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_sort_dll.exe .\Release\mingw\temp\sort_test.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_test_sf.o ..\specfunc\test_sf.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_test_airy.o ..\specfunc\test_airy.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_test_bessel.o ..\specfunc\test_bessel.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_test_coulomb.o ..\specfunc\test_coulomb.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_test_dilog.o ..\specfunc\test_dilog.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_test_gamma.o ..\specfunc\test_gamma.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_test_hyperg.o ..\specfunc\test_hyperg.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\specfunc_test_legendre.o ..\specfunc\test_legendre.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_specfunc.exe .\Release\mingw\temp\specfunc_test_sf.o .\Release\mingw\temp\specfunc_test_airy.o .\Release\mingw\temp\specfunc_test_bessel.o .\Release\mingw\temp\specfunc_test_coulomb.o .\Release\mingw\temp\specfunc_test_dilog.o .\Release\mingw\temp\specfunc_test_gamma.o .\Release\mingw\temp\specfunc_test_hyperg.o .\Release\mingw\temp\specfunc_test_legendre.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_specfunc_dll.exe .\Release\mingw\temp\specfunc_test_sf.o .\Release\mingw\temp\specfunc_test_airy.o .\Release\mingw\temp\specfunc_test_bessel.o .\Release\mingw\temp\specfunc_test_coulomb.o .\Release\mingw\temp\specfunc_test_dilog.o .\Release\mingw\temp\specfunc_test_gamma.o .\Release\mingw\temp\specfunc_test_hyperg.o .\Release\mingw\temp\specfunc_test_legendre.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\statistics_test.o ..\statistics\test.c
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\statistics_test_nist.o ..\statistics\test_nist.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_statistics.exe .\Release\mingw\temp\statistics_test.o .\Release\mingw\temp\statistics_test_nist.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_statistics_dll.exe .\Release\mingw\temp\statistics_test.o .\Release\mingw\temp\statistics_test_nist.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\sum_test.o ..\sum\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_sum.exe .\Release\mingw\temp\sum_test.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_sum_dll.exe .\Release\mingw\temp\sum_test.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\sys_test.o ..\sys\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_sys.exe .\Release\mingw\temp\sys_test.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_sys_dll.exe .\Release\mingw\temp\sys_test.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\vector_test.o ..\vector\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_vector.exe .\Release\mingw\temp\vector_test.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_vector_dll.exe .\Release\mingw\temp\vector_test.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\wavelet_test.o ..\wavelet\test.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_wavelet.exe .\Release\mingw\temp\wavelet_test.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\test_wavelet_dll.exe .\Release\mingw\temp\wavelet_test.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

REM Make special (Release) executables
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\gsl-randist.o ..\gsl-randist.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\gsl-randist.exe .\Release\mingw\temp\gsl-randist.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\gsl-histogram.o ..\gsl-histogram.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\gsl-histogram.exe .\Release\mingw\temp\gsl-histogram.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a

REM Make example (Release) executables
%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_blas.o ..\doc\examples\blas.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_blas.exe .\Release\mingw\temp\ex_blas.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_blas_dll.exe .\Release\mingw\temp\ex_blas.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_block.o ..\doc\examples\block.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_block.exe .\Release\mingw\temp\ex_block.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_block_dll.exe .\Release\mingw\temp\ex_block.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_cblas.o ..\doc\examples\cblas.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_cblas.exe .\Release\mingw\temp\ex_cblas.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_cblas_dll.exe .\Release\mingw\temp\ex_cblas.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_cdf.o ..\doc\examples\cdf.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_cdf.exe .\Release\mingw\temp\ex_cdf.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_cdf_dll.exe .\Release\mingw\temp\ex_cdf.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_cheb.o ..\doc\examples\cheb.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_cheb.exe .\Release\mingw\temp\ex_cheb.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_cheb_dll.exe .\Release\mingw\temp\ex_cheb.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_combination.o ..\doc\examples\combination.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_combination.exe .\Release\mingw\temp\ex_combination.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_combination_dll.exe .\Release\mingw\temp\ex_combination.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_const.o ..\doc\examples\const.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_const.exe .\Release\mingw\temp\ex_const.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_const_dll.exe .\Release\mingw\temp\ex_const.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_diff.o ..\doc\examples\diff.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_diff.exe .\Release\mingw\temp\ex_diff.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_diff_dll.exe .\Release\mingw\temp\ex_diff.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_dwt.o ..\doc\examples\dwt.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_dwt.exe .\Release\mingw\temp\ex_dwt.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_dwt_dll.exe .\Release\mingw\temp\ex_dwt.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_eigen.o ..\doc\examples\eigen.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_eigen.exe .\Release\mingw\temp\ex_eigen.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_eigen_dll.exe .\Release\mingw\temp\ex_eigen.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_fft.o ..\doc\examples\fft.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_fft.exe .\Release\mingw\temp\ex_fft.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_fft_dll.exe .\Release\mingw\temp\ex_fft.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_fftmr.o ..\doc\examples\fftmr.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_fftmr.exe .\Release\mingw\temp\ex_fftmr.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_fftmr_dll.exe .\Release\mingw\temp\ex_fftmr.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_fftreal.o ..\doc\examples\fftreal.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_fftreal.exe .\Release\mingw\temp\ex_fftreal.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_fftreal_dll.exe .\Release\mingw\temp\ex_fftreal.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_fitting.o ..\doc\examples\fitting.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_fitting.exe .\Release\mingw\temp\ex_fitting.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_fitting_dll.exe .\Release\mingw\temp\ex_fitting.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_fitting2.o ..\doc\examples\fitting2.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_fitting2.exe .\Release\mingw\temp\ex_fitting2.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_fitting2_dll.exe .\Release\mingw\temp\ex_fitting2.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_fitting3.o ..\doc\examples\fitting3.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_fitting3.exe .\Release\mingw\temp\ex_fitting3.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_fitting3_dll.exe .\Release\mingw\temp\ex_fitting3.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_histogram.o ..\doc\examples\histogram.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_histogram.exe .\Release\mingw\temp\ex_histogram.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_histogram_dll.exe .\Release\mingw\temp\ex_histogram.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_histogram2d.o ..\doc\examples\histogram2d.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_histogram2d.exe .\Release\mingw\temp\ex_histogram2d.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_histogram2d_dll.exe .\Release\mingw\temp\ex_histogram2d.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_ieee.o ..\doc\examples\ieee.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_ieee.exe .\Release\mingw\temp\ex_ieee.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_ieee_dll.exe .\Release\mingw\temp\ex_ieee.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_ieeeround.o ..\doc\examples\ieeeround.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_ieeeround.exe .\Release\mingw\temp\ex_ieeeround.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_ieeeround_dll.exe .\Release\mingw\temp\ex_ieeeround.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_integration.o ..\doc\examples\integration.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_integration.exe .\Release\mingw\temp\ex_integration.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_integration_dll.exe .\Release\mingw\temp\ex_integration.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_interp.o ..\doc\examples\interp.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_interp.exe .\Release\mingw\temp\ex_interp.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_interp_dll.exe .\Release\mingw\temp\ex_interp.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_interpp.o ..\doc\examples\interpp.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_interpp.exe .\Release\mingw\temp\ex_interpp.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_interpp_dll.exe .\Release\mingw\temp\ex_interpp.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_intro.o ..\doc\examples\intro.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_intro.exe .\Release\mingw\temp\ex_intro.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_intro_dll.exe .\Release\mingw\temp\ex_intro.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_linalglu.o ..\doc\examples\linalglu.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_linalglu.exe .\Release\mingw\temp\ex_linalglu.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_linalglu_dll.exe .\Release\mingw\temp\ex_linalglu.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_matrix.o ..\doc\examples\matrix.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_matrix.exe .\Release\mingw\temp\ex_matrix.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_matrix_dll.exe .\Release\mingw\temp\ex_matrix.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_matrixw.o ..\doc\examples\matrixw.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_matrixw.exe .\Release\mingw\temp\ex_matrixw.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_matrixw_dll.exe .\Release\mingw\temp\ex_matrixw.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_min.o ..\doc\examples\min.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_min.exe .\Release\mingw\temp\ex_min.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_min_dll.exe .\Release\mingw\temp\ex_min.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_monte.o ..\doc\examples\monte.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_monte.exe .\Release\mingw\temp\ex_monte.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_monte_dll.exe .\Release\mingw\temp\ex_monte.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_nlfit.o ..\doc\examples\nlfit.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_nlfit.exe .\Release\mingw\temp\ex_nlfit.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_nlfit_dll.exe .\Release\mingw\temp\ex_nlfit.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_ntupler.o ..\doc\examples\ntupler.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_ntupler.exe .\Release\mingw\temp\ex_ntupler.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_ntupler_dll.exe .\Release\mingw\temp\ex_ntupler.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_ntuplew.o ..\doc\examples\ntuplew.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_ntuplew.exe .\Release\mingw\temp\ex_ntuplew.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_ntuplew_dll.exe .\Release\mingw\temp\ex_ntuplew.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_ode-initval.o ..\doc\examples\ode-initval.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_ode-initval.exe .\Release\mingw\temp\ex_ode-initval.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_ode-initval_dll.exe .\Release\mingw\temp\ex_ode-initval.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

REM odefixed.c is not functional at this time (4-Ju;-2006)
REM %_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_odefixed.o ..\doc\examples\odefixed.c
REM %_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_odefixed.exe .\Release\mingw\temp\ex_odefixed.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
REM %_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_odefixed_dll.exe .\Release\mingw\temp\ex_odefixed.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_permseq.o ..\doc\examples\permseq.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_permseq.exe .\Release\mingw\temp\ex_permseq.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_permseq_dll.exe .\Release\mingw\temp\ex_permseq.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_permshuffle.o ..\doc\examples\permshuffle.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_permshuffle.exe .\Release\mingw\temp\ex_permshuffle.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_permshuffle_dll.exe .\Release\mingw\temp\ex_permshuffle.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_polyroots.o ..\doc\examples\polyroots.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_polyroots.exe .\Release\mingw\temp\ex_polyroots.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_polyroots_dll.exe .\Release\mingw\temp\ex_polyroots.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_qrng.o ..\doc\examples\qrng.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_qrng.exe .\Release\mingw\temp\ex_qrng.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_qrng_dll.exe .\Release\mingw\temp\ex_qrng.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_randpoisson.o ..\doc\examples\randpoisson.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_randpoisson.exe .\Release\mingw\temp\ex_randpoisson.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_randpoisson_dll.exe .\Release\mingw\temp\ex_randpoisson.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_randwalk.o ..\doc\examples\randwalk.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_randwalk.exe .\Release\mingw\temp\ex_randwalk.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_randwalk_dll.exe .\Release\mingw\temp\ex_randwalk.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_rng.o ..\doc\examples\rng.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_rng.exe .\Release\mingw\temp\ex_rng.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_rng_dll.exe .\Release\mingw\temp\ex_rng.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_rngunif.o ..\doc\examples\rngunif.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_rngunif.exe .\Release\mingw\temp\ex_rngunif.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_rngunif_dll.exe .\Release\mingw\temp\ex_rngunif.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_rootnewt.o ..\doc\examples\rootnewt.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_rootnewt.exe .\Release\mingw\temp\ex_rootnewt.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_rootnewt_dll.exe .\Release\mingw\temp\ex_rootnewt.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_roots.o ..\doc\examples\roots.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_roots.exe .\Release\mingw\temp\ex_roots.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_roots_dll.exe .\Release\mingw\temp\ex_roots.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_siman.o ..\doc\examples\siman.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_siman.exe .\Release\mingw\temp\ex_siman.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_siman_dll.exe .\Release\mingw\temp\ex_siman.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_sortsmall.o ..\doc\examples\sortsmall.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_sortsmall.exe .\Release\mingw\temp\ex_sortsmall.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_sortsmall_dll.exe .\Release\mingw\temp\ex_sortsmall.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_specfun.o ..\doc\examples\specfun.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_specfun.exe .\Release\mingw\temp\ex_specfun.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_specfun_dll.exe .\Release\mingw\temp\ex_specfun.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_specfun_e.o ..\doc\examples\specfun_e.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_specfun_e.exe .\Release\mingw\temp\ex_specfun_e.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_specfun_e_dll.exe .\Release\mingw\temp\ex_specfun_e.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_stat.o ..\doc\examples\stat.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_stat.exe .\Release\mingw\temp\ex_stat.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_stat_dll.exe .\Release\mingw\temp\ex_stat.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_statsort.o ..\doc\examples\statsort.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_statsort.exe .\Release\mingw\temp\ex_statsort.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_statsort_dll.exe .\Release\mingw\temp\ex_statsort.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_sum.o ..\doc\examples\sum.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_sum.exe .\Release\mingw\temp\ex_sum.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_sum_dll.exe .\Release\mingw\temp\ex_sum.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_vector.o ..\doc\examples\vector.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_vector.exe .\Release\mingw\temp\ex_vector.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_vector_dll.exe .\Release\mingw\temp\ex_vector.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_vectorr.o ..\doc\examples\vectorr.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_vectorr.exe .\Release\mingw\temp\ex_vectorr.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_vectorr_dll.exe .\Release\mingw\temp\ex_vectorr.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_vectorview.o ..\doc\examples\vectorview.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_vectorview.exe .\Release\mingw\temp\ex_vectorview.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_vectorview_dll.exe .\Release\mingw\temp\ex_vectorview.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

%_COMPILE% %_OPT_RELEASE% %_COMP_OUTPUT_FLAG% .\Release\mingw\temp\ex_vectorw.o ..\doc\examples\vectorw.c
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_vectorw.exe .\Release\mingw\temp\ex_vectorw.o .\Release\mingw\libgsl.a .\Release\mingw\cblas\libgslcblas.a
%_COMPILE% %_COMP_OUTPUT_FLAG% .\Release\mingw\ex_vectorw_dll.exe .\Release\mingw\temp\ex_vectorw.o .\Release\mingw\libgsl_dll.a .\Release\mingw\libgslcblas_dll.a

REM Installation
%_MKDIR% %_PATH_INSTALL%

%_MKDIR% %_PATH_INSTALL%\%_VERSION_STRING%-lib

%_MKDIR% %_PATH_INSTALL%\%_VERSION_STRING%-lib\bin
%_COPY% .\Release\mingw\libgsl.dll %_PATH_INSTALL%\%_VERSION_STRING%-lib\bin\libgsl.dll
%_COPY% .\Release\mingw\libgslcblas.dll %_PATH_INSTALL%\%_VERSION_STRING%-lib\bin\libgslcblas.dll
%_COPY% .\Release\mingw\gsl-randist.exe %_PATH_INSTALL%\%_VERSION_STRING%-lib\bin\gsl-randist.exe
%_COPY% .\Release\mingw\gsl-histogram.exe %_PATH_INSTALL%\%_VERSION_STRING%-lib\bin\gsl-histogram.exe
%_COPY% .\Release\mingw\gsl-randist.exe %_PATH_INSTALL%\%_VERSION_STRING%-lib\bin\gsl-randist.exe

%_MKDIR% %_PATH_INSTALL%\%_VERSION_STRING%-lib\contrib
%_MKDIR% %_PATH_INSTALL%\%_VERSION_STRING%-lib\contrib\gsl-1.8
%_COPY% ..\AUTHORS %_PATH_INSTALL%\%_VERSION_STRING%-lib\contrib\gsl-1.8\*
%_COPY% ..\BUGS %_PATH_INSTALL%\%_VERSION_STRING%-lib\contrib\gsl-1.8\*
%_COPY% ..\ChangeLog %_PATH_INSTALL%\%_VERSION_STRING%-lib\contrib\gsl-1.8\*
%_COPY% ..\COPYING %_PATH_INSTALL%\%_VERSION_STRING%-lib\contrib\gsl-1.8\*
%_COPY% ..\INSTALL %_PATH_INSTALL%\%_VERSION_STRING%-lib\contrib\gsl-1.8\*
%_COPY% ..\NEWS %_PATH_INSTALL%\%_VERSION_STRING%-lib\contrib\gsl-1.8\*
%_COPY% ..\README %_PATH_INSTALL%\%_VERSION_STRING%-lib\contrib\gsl-1.8\*
%_COPY% ..\Readme_GnuWin32.txt %_PATH_INSTALL%\%_VERSION_STRING%-lib\contrib\gsl-1.8\*
%_COPY% ..\SUPPORT %_PATH_INSTALL%\%_VERSION_STRING%-lib\contrib\gsl-1.8\*
%_COPY% ..\THANKS %_PATH_INSTALL%\%_VERSION_STRING%-lib\contrib\gsl-1.8\*
%_COPY% ..\TODO %_PATH_INSTALL%\%_VERSION_STRING%-lib\contrib\gsl-1.8\*

%_MKDIR% %_PATH_INSTALL%\%_VERSION_STRING%-lib\info
%_COPY% ..\doc\gsl-ref.info %_PATH_INSTALL%\%_VERSION_STRING%-lib\info\gsl-ref.info
%_COPY% ..\doc\gsl-ref.info-1 %_PATH_INSTALL%\%_VERSION_STRING%-lib\info\gsl-ref.info-1
%_COPY% ..\doc\gsl-ref.info-2 %_PATH_INSTALL%\%_VERSION_STRING%-lib\info\gsl-ref.info-2
%_COPY% ..\doc\gsl-ref.info-3 %_PATH_INSTALL%\%_VERSION_STRING%-lib\info\gsl-ref.info-3
%_COPY% ..\doc\gsl-ref.info-4 %_PATH_INSTALL%\%_VERSION_STRING%-lib\info\gsl-ref.info-4

%_MKDIR% %_PATH_INSTALL%\%_VERSION_STRING%-lib\man3
%_COPY% ..\doc\gsl.3 %_PATH_INSTALL%\%_VERSION_STRING%-lib\man3\gsl.3

%_MKDIR% %_PATH_INSTALL%\%_VERSION_STRING%-lib\man1
%_COPY% ..\doc\gsl-config.1 %_PATH_INSTALL%\%_VERSION_STRING%-lib\man1\gsl-config.1
%_COPY% ..\doc\gsl-histogram.1 %_PATH_INSTALL%\%_VERSION_STRING%-lib\man1\gsl-histogram.1
%_COPY% ..\doc\gsl-randist.1 %_PATH_INSTALL%\%_VERSION_STRING%-lib\man1\gsl-randist.1

%_MKDIR% %_PATH_INSTALL%\%_VERSION_STRING%-lib
%_MKDIR% %_PATH_INSTALL%\%_VERSION_STRING%-lib\lib
%_COPY% .\Release\mingw\libgsl.a %_PATH_INSTALL%\%_VERSION_STRING%-lib\lib\libgsl.a
%_COPY% .\Release\mingw\cblas\libgslcblas.a %_PATH_INSTALL%\%_VERSION_STRING%-lib\lib\libgslcblas.a
%_COPY% .\Release\mingw\libgsl_dll.a %_PATH_INSTALL%\%_VERSION_STRING%-lib\lib\libgsl_dll.a
%_COPY% .\Release\mingw\libgslcblas_dll.a %_PATH_INSTALL%\%_VERSION_STRING%-lib\lib\libgslcblas_dll.a
%_COPY% .\libgsl.def %_PATH_INSTALL%\%_VERSION_STRING%-lib\lib\libgsl.def
%_COPY% .\libgslcblas.def %_PATH_INSTALL%\%_VERSION_STRING%-lib\lib\libgslcblas.def

%_MKDIR% %_PATH_INSTALL%\%_VERSION_STRING%-lib\include
%_MKDIR% %_PATH_INSTALL%\%_VERSION_STRING%-lib\include\gsl
%_COPY% ..\gsl\gsl_*.h %_PATH_INSTALL%\%_VERSION_STRING%-lib\include\gsl\*
%_COPY% ..\config.h %_PATH_INSTALL%\%_VERSION_STRING%-lib\include\gsl\config.h

%_MKDIR% %_PATH_INSTALL%\%_VERSION_STRING%-libdbg

%_MKDIR% %_PATH_INSTALL%\%_VERSION_STRING%-libdbg\bin
%_COPY% .\Debug\mingw\libgsl_d.dll %_PATH_INSTALL%\%_VERSION_STRING%-libdbg\bin\libgsl_d.dll
%_COPY% .\Debug\mingw\libgslcblas_d.dll %_PATH_INSTALL%\%_VERSION_STRING%-libdbg\bin\libgslcblas_d.dll

%_MKDIR% %_PATH_INSTALL%\%_VERSION_STRING%-libdbg\lib
%_COPY% .\Debug\mingw\libgsl_d.a %_PATH_INSTALL%\%_VERSION_STRING%-libdbg\lib\libgsl_d.a
%_COPY% .\Debug\mingw\cblas\libgslcblas_d.a %_PATH_INSTALL%\%_VERSION_STRING%-libdbg\lib\libgslcblas_d.a
%_COPY% .\Debug\mingw\libgsl_d_dll.a %_PATH_INSTALL%\%_VERSION_STRING%-libdbg\lib\libgsl_d_dll.a
%_COPY% .\Debug\mingw\libgslcblas_d_dll.a %_PATH_INSTALL%\%_VERSION_STRING%-libdbg\lib\libgslcblas_d_dll.a

SET _COMPILE=
SET _COMP_OUTPUT_FLAG=
SET _OPT_DEBUG=
SET _OPT_RELEASE=
SET _OPT_DLL=
SET _DLL_LINK_FLAG=
SET _ARC=
SET _ARC_OPTS=
SET _MKDIR=
SET _COPY=
SET _PATH_INSTALL=
SET _VERSION_STRING=
