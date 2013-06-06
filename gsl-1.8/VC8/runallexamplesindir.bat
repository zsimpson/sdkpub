REM Runs all gsl example programs in a given directory
REM
REM Parameters:
REM    1 Path to example program executables
REM    2 Path to example output files
REM    3 Suffix appended to program names (e.g. _d or _dll or _dll_d)
REM

if "%1"=="" goto EXIT_BAT

if exist %1\ex_blas%3.exe call runtestwithoutput %1\ex_blas%3.exe %2\blas.out
if exist %1\ex_block%3.exe call runtestwithoutput %1\ex_block%3.exe %2\block.out
if exist %1\ex_cblas%3.exe call runtestwithoutput %1\ex_cblas%3.exe %2\cblas.out
if exist %1\ex_cdf%3.exe call runtestwithoutput %1\ex_cdf%3.exe %2\cdf.out
if exist %1\ex_cheb%3.exe call runtest %1\ex_cheb%3.exe
if exist %1\ex_combination%3.exe call runtestwithoutput %1\ex_combination%3.exe %2\combination.out
if exist %1\ex_const%3.exe call runtestwithoutput %1\ex_const%3.exe %2\const.out
if exist %1\ex_diff%3.exe call runtestwithoutput %1\ex_diff%3.exe %2\diff.out
if exist %1\ex_dwt%3.exe call runtest %1\ex_dwt%3.exe %2\dwt.dat
if exist %1\ex_eigen%3.exe call runtest %1\ex_eigen%3.exe
if exist %1\ex_fft%3.exe call runtest %1\ex_fft%3.exe
if exist %1\ex_fftmr%3.exe call runtest %1\ex_fftmr%3.exe
if exist %1\ex_fftreal%3.exe call runtest %1\ex_fftreal%3.exe
if exist %1\ex_fitting%3.exe call runtest %1\ex_fitting%3.exe
if exist %1\ex_fitting2%3.exe call runtest %1\ex_fitting2%3.exe
if exist %1\ex_fitting3%3.exe call runtest %1\ex_fitting3%3.exe
if exist %1\ex_histogram%3.exe call runtest %1\ex_histogram%3.exe
if exist %1\ex_histogram2d%3.exe call runtest %1\ex_histogram2d%3.exe
if exist %1\ex_ieee%3.exe call runtest %1\ex_ieee%3.exe
if exist %1\ex_ieeeround%3.exe call runtest %1\ex_ieeeround%3.exe
if exist %1\ex_integration%3.exe call runtestwithoutput %1\ex_integration%3.exe %2\integration.out
if exist %1\ex_interp%3.exe call runtest %1\ex_interp%3.exe
if exist %1\ex_interpp%3.exe call runtest %1\ex_interpp%3.exe
if exist %1\ex_intro%3.exe call runtestwithoutput %1\ex_intro%3.exe %2\intro.out
if exist %1\ex_linalglu%3.exe call runtestwithoutput %1\ex_linalglu%3.exe %2\linalglu.out
if exist %1\ex_matrix%3.exe call runtestwithoutput %1\ex_matrix%3.exe %2\matrix.out
if exist %1\ex_matrixw%3.exe call runtestwithoutput %1\ex_matrixw%3.exe %2\matrixw.out
if exist %1\ex_min%3.exe call runtestwithoutput %1\ex_min%3.exe %2\min.out
if exist %1\ex_monte%3.exe call runtest %1\ex_monte%3.exe
if exist %1\ex_nlfit%3.exe call runtest %1\ex_nlfit%3.exe
if exist %1\ex_ntupler%3.exe call runtest %1\ex_ntupler%3.exe
if exist %1\ex_ntuplew%3.exe call runtest %1\ex_ntuplew%3.exe
if exist %1\ex_ode-initval%3.exe call runtest %1\ex_ode-initval%3.exe
if exist %1\ex_odefixed%3.exe call runtest %1\ex_odefixed%3.exe
if exist %1\ex_permseq%3.exe call runtest %1\ex_permseq%3.exe
if exist %1\ex_permshuffle%3.exe call runtest %1\ex_permshuffle%3.exe
if exist %1\ex_polyroots%3.exe call runtestwithoutput %1\ex_polyroots%3.exe %2\polyroots.out
if exist %1\ex_qrng%3.exe call runtest %1\ex_qrng%3.exe
if exist %1\ex_randpoisson%3.exe call runtestwithoutput %1\ex_randpoisson%3.exe %2\randpoisson.out
if exist %1\ex_randwalk%3.exe call runtest %1\ex_randwalk%3.exe
if exist %1\ex_rng%3.exe call runtestwithoutput %1\ex_rng%3.exe %2\rng.out
if exist %1\ex_rngunif%3.exe call runtestwithoutput %1\ex_rngunif%3.exe %2\rngunif.out
if exist %1\ex_rootnewt%3.exe call runtest %1\ex_rootnewt%3.exe
if exist %1\ex_roots%3.exe call runtest %1\ex_roots%3.exe
if exist %1\ex_siman%3.exe call runtest %1\ex_siman%3.exe
if exist %1\ex_sortsmall%3.exe call runtestwithoutput %1\ex_sortsmall%3.exe %2\sortsmall.out
if exist %1\ex_specfun%3.exe call runtestwithoutput %1\ex_specfun%3.exe %2\specfun.out
if exist %1\ex_specfun_e%3.exe call runtestwithoutput %1\ex_specfun_e%3.exe %2\specfun_e.out
if exist %1\ex_stat%3.exe call runtestwithoutput %1\ex_stat%3.exe %2\stat.out
if exist %1\ex_statsort%3.exe call runtestwithoutput %1\ex_statsort%3.exe %2\statsort.out
if exist %1\ex_sum%3.exe call runtestwithoutput %1\ex_sum%3.exe %2\sum.out
if exist %1\ex_vector%3.exe call runtest %1\ex_vector%3.exe
if exist %1\ex_vectorview%3.exe call runtestwithoutput %1\ex_vectorview%3.exe %2\vectorview.out
if exist %1\ex_vectorw%3.exe call runtest %1\ex_vectorw%3.exe
if exist %1\ex_vectorr%3.exe call runtest %1\ex_vectorr%3.exe

:EXIT_BAT

