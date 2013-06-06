# Microsoft Developer Studio Generated NMAKE File, Based on gsl18_vc6.dsp
!IF "$(CFG)" == ""
CFG=gsl18_vc6 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to gsl18_vc6 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "gsl18_vc6 - Win32 Release" && "$(CFG)" != "gsl18_vc6 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gsl18_vc6.mak" CFG="gsl18_vc6 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gsl18_vc6 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "gsl18_vc6 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\gsl18_vc6.dll"


CLEAN :
	-@erase "$(INTDIR)\blas\vc60.idb"
	-@erase "$(INTDIR)\block\vc60.idb"
	-@erase "$(INTDIR)\cblas\vc60.idb"
	-@erase "$(INTDIR)\complex\vc60.idb"
	-@erase "$(INTDIR)\err\vc60.idb"
	-@erase "$(INTDIR)\fft.obj"
	-@erase "$(INTDIR)\gsl18_vc6.obj"
	-@erase "$(INTDIR)\linalg\vc60.idb"
	-@erase "$(INTDIR)\matrix\vc60.idb"
	-@erase "$(INTDIR)\multifit\vc60.idb"
	-@erase "$(INTDIR)\ode-initval\vc60.idb"
	-@erase "$(INTDIR)\permutation\vc60.idb"
	-@erase "$(INTDIR)\randist\vc60.idb"
	-@erase "$(INTDIR)\rng\vc60.idb"
	-@erase "$(INTDIR)\specfunc\vc60.idb"
	-@erase "$(INTDIR)\sys\vc60.idb"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vector\vc60.idb"
	-@erase "$(OUTDIR)\gsl18_vc6.dll"
	-@erase "$(OUTDIR)\gsl18_vc6.exp"
	-@erase "$(OUTDIR)\gsl18_vc6.lib"
	-@erase ".\Release\blas\blas.obj"
	-@erase ".\Release\block\block.obj"
	-@erase ".\Release\block\file.obj"
	-@erase ".\Release\block\init.obj"
	-@erase ".\Release\cblas\caxpy.obj"
	-@erase ".\Release\cblas\ccopy.obj"
	-@erase ".\Release\cblas\cdotc_sub.obj"
	-@erase ".\Release\cblas\cdotu_sub.obj"
	-@erase ".\Release\cblas\cgbmv.obj"
	-@erase ".\Release\cblas\cgemm.obj"
	-@erase ".\Release\cblas\cgemv.obj"
	-@erase ".\Release\cblas\cgerc.obj"
	-@erase ".\Release\cblas\cgeru.obj"
	-@erase ".\Release\cblas\chbmv.obj"
	-@erase ".\Release\cblas\chemm.obj"
	-@erase ".\Release\cblas\chemv.obj"
	-@erase ".\Release\cblas\cher.obj"
	-@erase ".\Release\cblas\cher2.obj"
	-@erase ".\Release\cblas\cher2k.obj"
	-@erase ".\Release\cblas\cherk.obj"
	-@erase ".\Release\cblas\chpmv.obj"
	-@erase ".\Release\cblas\chpr.obj"
	-@erase ".\Release\cblas\chpr2.obj"
	-@erase ".\Release\cblas\cscal.obj"
	-@erase ".\Release\cblas\csscal.obj"
	-@erase ".\Release\cblas\cswap.obj"
	-@erase ".\Release\cblas\csymm.obj"
	-@erase ".\Release\cblas\csyr2k.obj"
	-@erase ".\Release\cblas\csyrk.obj"
	-@erase ".\Release\cblas\ctbmv.obj"
	-@erase ".\Release\cblas\ctbsv.obj"
	-@erase ".\Release\cblas\ctpmv.obj"
	-@erase ".\Release\cblas\ctpsv.obj"
	-@erase ".\Release\cblas\ctrmm.obj"
	-@erase ".\Release\cblas\ctrmv.obj"
	-@erase ".\Release\cblas\ctrsm.obj"
	-@erase ".\Release\cblas\ctrsv.obj"
	-@erase ".\Release\cblas\dasum.obj"
	-@erase ".\Release\cblas\daxpy.obj"
	-@erase ".\Release\cblas\dcopy.obj"
	-@erase ".\Release\cblas\ddot.obj"
	-@erase ".\Release\cblas\dgbmv.obj"
	-@erase ".\Release\cblas\dgemm.obj"
	-@erase ".\Release\cblas\dgemv.obj"
	-@erase ".\Release\cblas\dger.obj"
	-@erase ".\Release\cblas\dnrm2.obj"
	-@erase ".\Release\cblas\drot.obj"
	-@erase ".\Release\cblas\drotg.obj"
	-@erase ".\Release\cblas\drotm.obj"
	-@erase ".\Release\cblas\drotmg.obj"
	-@erase ".\Release\cblas\dsbmv.obj"
	-@erase ".\Release\cblas\dscal.obj"
	-@erase ".\Release\cblas\dsdot.obj"
	-@erase ".\Release\cblas\dspmv.obj"
	-@erase ".\Release\cblas\dspr.obj"
	-@erase ".\Release\cblas\dspr2.obj"
	-@erase ".\Release\cblas\dswap.obj"
	-@erase ".\Release\cblas\dsymm.obj"
	-@erase ".\Release\cblas\dsymv.obj"
	-@erase ".\Release\cblas\dsyr.obj"
	-@erase ".\Release\cblas\dsyr2.obj"
	-@erase ".\Release\cblas\dsyr2k.obj"
	-@erase ".\Release\cblas\dsyrk.obj"
	-@erase ".\Release\cblas\dtbmv.obj"
	-@erase ".\Release\cblas\dtbsv.obj"
	-@erase ".\Release\cblas\dtpmv.obj"
	-@erase ".\Release\cblas\dtpsv.obj"
	-@erase ".\Release\cblas\dtrmm.obj"
	-@erase ".\Release\cblas\dtrmv.obj"
	-@erase ".\Release\cblas\dtrsm.obj"
	-@erase ".\Release\cblas\dtrsv.obj"
	-@erase ".\Release\cblas\dzasum.obj"
	-@erase ".\Release\cblas\dznrm2.obj"
	-@erase ".\Release\cblas\hypot.obj"
	-@erase ".\Release\cblas\icamax.obj"
	-@erase ".\Release\cblas\idamax.obj"
	-@erase ".\Release\cblas\isamax.obj"
	-@erase ".\Release\cblas\izamax.obj"
	-@erase ".\Release\cblas\sasum.obj"
	-@erase ".\Release\cblas\saxpy.obj"
	-@erase ".\Release\cblas\scasum.obj"
	-@erase ".\Release\cblas\scnrm2.obj"
	-@erase ".\Release\cblas\scopy.obj"
	-@erase ".\Release\cblas\sdot.obj"
	-@erase ".\Release\cblas\sdsdot.obj"
	-@erase ".\Release\cblas\sgbmv.obj"
	-@erase ".\Release\cblas\sgemm.obj"
	-@erase ".\Release\cblas\sgemv.obj"
	-@erase ".\Release\cblas\sger.obj"
	-@erase ".\Release\cblas\snrm2.obj"
	-@erase ".\Release\cblas\srot.obj"
	-@erase ".\Release\cblas\srotg.obj"
	-@erase ".\Release\cblas\srotm.obj"
	-@erase ".\Release\cblas\srotmg.obj"
	-@erase ".\Release\cblas\ssbmv.obj"
	-@erase ".\Release\cblas\sscal.obj"
	-@erase ".\Release\cblas\sspmv.obj"
	-@erase ".\Release\cblas\sspr.obj"
	-@erase ".\Release\cblas\sspr2.obj"
	-@erase ".\Release\cblas\sswap.obj"
	-@erase ".\Release\cblas\ssymm.obj"
	-@erase ".\Release\cblas\ssymv.obj"
	-@erase ".\Release\cblas\ssyr.obj"
	-@erase ".\Release\cblas\ssyr2.obj"
	-@erase ".\Release\cblas\ssyr2k.obj"
	-@erase ".\Release\cblas\ssyrk.obj"
	-@erase ".\Release\cblas\stbmv.obj"
	-@erase ".\Release\cblas\stbsv.obj"
	-@erase ".\Release\cblas\stpmv.obj"
	-@erase ".\Release\cblas\stpsv.obj"
	-@erase ".\Release\cblas\strmm.obj"
	-@erase ".\Release\cblas\strmv.obj"
	-@erase ".\Release\cblas\strsm.obj"
	-@erase ".\Release\cblas\strsv.obj"
	-@erase ".\Release\cblas\xerbla.obj"
	-@erase ".\Release\cblas\zaxpy.obj"
	-@erase ".\Release\cblas\zcopy.obj"
	-@erase ".\Release\cblas\zdotc_sub.obj"
	-@erase ".\Release\cblas\zdotu_sub.obj"
	-@erase ".\Release\cblas\zdscal.obj"
	-@erase ".\Release\cblas\zgbmv.obj"
	-@erase ".\Release\cblas\zgemm.obj"
	-@erase ".\Release\cblas\zgemv.obj"
	-@erase ".\Release\cblas\zgerc.obj"
	-@erase ".\Release\cblas\zgeru.obj"
	-@erase ".\Release\cblas\zhbmv.obj"
	-@erase ".\Release\cblas\zhemm.obj"
	-@erase ".\Release\cblas\zhemv.obj"
	-@erase ".\Release\cblas\zher.obj"
	-@erase ".\Release\cblas\zher2.obj"
	-@erase ".\Release\cblas\zher2k.obj"
	-@erase ".\Release\cblas\zherk.obj"
	-@erase ".\Release\cblas\zhpmv.obj"
	-@erase ".\Release\cblas\zhpr.obj"
	-@erase ".\Release\cblas\zhpr2.obj"
	-@erase ".\Release\cblas\zscal.obj"
	-@erase ".\Release\cblas\zswap.obj"
	-@erase ".\Release\cblas\zsymm.obj"
	-@erase ".\Release\cblas\zsyr2k.obj"
	-@erase ".\Release\cblas\zsyrk.obj"
	-@erase ".\Release\cblas\ztbmv.obj"
	-@erase ".\Release\cblas\ztbsv.obj"
	-@erase ".\Release\cblas\ztpmv.obj"
	-@erase ".\Release\cblas\ztpsv.obj"
	-@erase ".\Release\cblas\ztrmm.obj"
	-@erase ".\Release\cblas\ztrmv.obj"
	-@erase ".\Release\cblas\ztrsm.obj"
	-@erase ".\Release\cblas\ztrsv.obj"
	-@erase ".\Release\complex\math.obj"
	-@erase ".\Release\err\error.obj"
	-@erase ".\Release\err\message.obj"
	-@erase ".\Release\err\stream.obj"
	-@erase ".\Release\err\strerror.obj"
	-@erase ".\Release\linalg\balance.obj"
	-@erase ".\Release\linalg\bidiag.obj"
	-@erase ".\Release\linalg\cholesky.obj"
	-@erase ".\Release\linalg\exponential.obj"
	-@erase ".\Release\linalg\hermtd.obj"
	-@erase ".\Release\linalg\hh.obj"
	-@erase ".\Release\linalg\householder.obj"
	-@erase ".\Release\linalg\householdercomplex.obj"
	-@erase ".\Release\linalg\lq.obj"
	-@erase ".\Release\linalg\lu.obj"
	-@erase ".\Release\linalg\luc.obj"
	-@erase ".\Release\linalg\multiply.obj"
	-@erase ".\Release\linalg\ptlq.obj"
	-@erase ".\Release\linalg\qr.obj"
	-@erase ".\Release\linalg\qrpt.obj"
	-@erase ".\Release\linalg\svd.obj"
	-@erase ".\Release\linalg\symmtd.obj"
	-@erase ".\Release\linalg\tridiag.obj"
	-@erase ".\Release\matrix\copy.obj"
	-@erase ".\Release\matrix\file.obj"
	-@erase ".\Release\matrix\getset.obj"
	-@erase ".\Release\matrix\init.obj"
	-@erase ".\Release\matrix\matrix.obj"
	-@erase ".\Release\matrix\minmax.obj"
	-@erase ".\Release\matrix\oper.obj"
	-@erase ".\Release\matrix\prop.obj"
	-@erase ".\Release\matrix\rowcol.obj"
	-@erase ".\Release\matrix\submatrix.obj"
	-@erase ".\Release\matrix\swap.obj"
	-@erase ".\Release\matrix\view.obj"
	-@erase ".\Release\multifit\convergence.obj"
	-@erase ".\Release\multifit\covar.obj"
	-@erase ".\Release\multifit\fdfsolver.obj"
	-@erase ".\Release\multifit\fsolver.obj"
	-@erase ".\Release\multifit\gradient.obj"
	-@erase ".\Release\multifit\lmder.obj"
	-@erase ".\Release\multifit\multilinear.obj"
	-@erase ".\Release\multifit\work.obj"
	-@erase ".\Release\ode-initval\bsimp.obj"
	-@erase ".\Release\ode-initval\control.obj"
	-@erase ".\Release\ode-initval\cscal.obj"
	-@erase ".\Release\ode-initval\cstd.obj"
	-@erase ".\Release\ode-initval\evolve.obj"
	-@erase ".\Release\ode-initval\gear1.obj"
	-@erase ".\Release\ode-initval\gear2.obj"
	-@erase ".\Release\ode-initval\rk2.obj"
	-@erase ".\Release\ode-initval\rk2imp.obj"
	-@erase ".\Release\ode-initval\rk2simp.obj"
	-@erase ".\Release\ode-initval\rk4.obj"
	-@erase ".\Release\ode-initval\rk4imp.obj"
	-@erase ".\Release\ode-initval\rk8pd.obj"
	-@erase ".\Release\ode-initval\rkck.obj"
	-@erase ".\Release\ode-initval\rkf45.obj"
	-@erase ".\Release\ode-initval\step.obj"
	-@erase ".\Release\permutation\canonical.obj"
	-@erase ".\Release\permutation\file.obj"
	-@erase ".\Release\permutation\init.obj"
	-@erase ".\Release\permutation\permutation.obj"
	-@erase ".\Release\permutation\permute.obj"
	-@erase ".\Release\randist\bernoulli.obj"
	-@erase ".\Release\randist\beta.obj"
	-@erase ".\Release\randist\bigauss.obj"
	-@erase ".\Release\randist\binomial.obj"
	-@erase ".\Release\randist\binomial_tpe.obj"
	-@erase ".\Release\randist\cauchy.obj"
	-@erase ".\Release\randist\chisq.obj"
	-@erase ".\Release\randist\dirichlet.obj"
	-@erase ".\Release\randist\discrete.obj"
	-@erase ".\Release\randist\erlang.obj"
	-@erase ".\Release\randist\exponential.obj"
	-@erase ".\Release\randist\exppow.obj"
	-@erase ".\Release\randist\fdist.obj"
	-@erase ".\Release\randist\flat.obj"
	-@erase ".\Release\randist\gamma.obj"
	-@erase ".\Release\randist\gauss.obj"
	-@erase ".\Release\randist\gausstail.obj"
	-@erase ".\Release\randist\gausszig.obj"
	-@erase ".\Release\randist\geometric.obj"
	-@erase ".\Release\randist\gumbel.obj"
	-@erase ".\Release\randist\hyperg.obj"
	-@erase ".\Release\randist\landau.obj"
	-@erase ".\Release\randist\laplace.obj"
	-@erase ".\Release\randist\levy.obj"
	-@erase ".\Release\randist\logarithmic.obj"
	-@erase ".\Release\randist\logistic.obj"
	-@erase ".\Release\randist\lognormal.obj"
	-@erase ".\Release\randist\multinomial.obj"
	-@erase ".\Release\randist\nbinomial.obj"
	-@erase ".\Release\randist\pareto.obj"
	-@erase ".\Release\randist\pascal.obj"
	-@erase ".\Release\randist\poisson.obj"
	-@erase ".\Release\randist\rayleigh.obj"
	-@erase ".\Release\randist\shuffle.obj"
	-@erase ".\Release\randist\sphere.obj"
	-@erase ".\Release\randist\tdist.obj"
	-@erase ".\Release\randist\weibull.obj"
	-@erase ".\Release\rng\borosh13.obj"
	-@erase ".\Release\rng\cmrg.obj"
	-@erase ".\Release\rng\coveyou.obj"
	-@erase ".\Release\rng\default.obj"
	-@erase ".\Release\rng\file.obj"
	-@erase ".\Release\rng\fishman18.obj"
	-@erase ".\Release\rng\fishman20.obj"
	-@erase ".\Release\rng\fishman2x.obj"
	-@erase ".\Release\rng\gfsr4.obj"
	-@erase ".\Release\rng\knuthran.obj"
	-@erase ".\Release\rng\knuthran2.obj"
	-@erase ".\Release\rng\lecuyer21.obj"
	-@erase ".\Release\rng\minstd.obj"
	-@erase ".\Release\rng\mrg.obj"
	-@erase ".\Release\rng\mt.obj"
	-@erase ".\Release\rng\r250.obj"
	-@erase ".\Release\rng\ran0.obj"
	-@erase ".\Release\rng\ran1.obj"
	-@erase ".\Release\rng\ran2.obj"
	-@erase ".\Release\rng\ran3.obj"
	-@erase ".\Release\rng\rand.obj"
	-@erase ".\Release\rng\rand48.obj"
	-@erase ".\Release\rng\random.obj"
	-@erase ".\Release\rng\randu.obj"
	-@erase ".\Release\rng\ranf.obj"
	-@erase ".\Release\rng\ranlux.obj"
	-@erase ".\Release\rng\ranlxd.obj"
	-@erase ".\Release\rng\ranlxs.obj"
	-@erase ".\Release\rng\ranmar.obj"
	-@erase ".\Release\rng\rng.obj"
	-@erase ".\Release\rng\slatec.obj"
	-@erase ".\Release\rng\taus.obj"
	-@erase ".\Release\rng\taus113.obj"
	-@erase ".\Release\rng\transputer.obj"
	-@erase ".\Release\rng\tt.obj"
	-@erase ".\Release\rng\types.obj"
	-@erase ".\Release\rng\uni.obj"
	-@erase ".\Release\rng\uni32.obj"
	-@erase ".\Release\rng\vax.obj"
	-@erase ".\Release\rng\waterman14.obj"
	-@erase ".\Release\rng\zuf.obj"
	-@erase ".\Release\specfunc\airy.obj"
	-@erase ".\Release\specfunc\airy_der.obj"
	-@erase ".\Release\specfunc\airy_zero.obj"
	-@erase ".\Release\specfunc\atanint.obj"
	-@erase ".\Release\specfunc\bessel.obj"
	-@erase ".\Release\specfunc\bessel_amp_phase.obj"
	-@erase ".\Release\specfunc\bessel_i.obj"
	-@erase ".\Release\specfunc\bessel_I0.obj"
	-@erase ".\Release\specfunc\bessel_I1.obj"
	-@erase ".\Release\specfunc\bessel_In.obj"
	-@erase ".\Release\specfunc\bessel_Inu.obj"
	-@erase ".\Release\specfunc\bessel_j.obj"
	-@erase ".\Release\specfunc\bessel_J0.obj"
	-@erase ".\Release\specfunc\bessel_J1.obj"
	-@erase ".\Release\specfunc\bessel_Jn.obj"
	-@erase ".\Release\specfunc\bessel_Jnu.obj"
	-@erase ".\Release\specfunc\bessel_k.obj"
	-@erase ".\Release\specfunc\bessel_K0.obj"
	-@erase ".\Release\specfunc\bessel_K1.obj"
	-@erase ".\Release\specfunc\bessel_Kn.obj"
	-@erase ".\Release\specfunc\bessel_Knu.obj"
	-@erase ".\Release\specfunc\bessel_olver.obj"
	-@erase ".\Release\specfunc\bessel_sequence.obj"
	-@erase ".\Release\specfunc\bessel_temme.obj"
	-@erase ".\Release\specfunc\bessel_y.obj"
	-@erase ".\Release\specfunc\bessel_Y0.obj"
	-@erase ".\Release\specfunc\bessel_Y1.obj"
	-@erase ".\Release\specfunc\bessel_Yn.obj"
	-@erase ".\Release\specfunc\bessel_Ynu.obj"
	-@erase ".\Release\specfunc\bessel_zero.obj"
	-@erase ".\Release\specfunc\beta.obj"
	-@erase ".\Release\specfunc\beta_inc.obj"
	-@erase ".\Release\specfunc\clausen.obj"
	-@erase ".\Release\specfunc\coulomb.obj"
	-@erase ".\Release\specfunc\coulomb_bound.obj"
	-@erase ".\Release\specfunc\coupling.obj"
	-@erase ".\Release\specfunc\dawson.obj"
	-@erase ".\Release\specfunc\debye.obj"
	-@erase ".\Release\specfunc\dilog.obj"
	-@erase ".\Release\specfunc\elementary.obj"
	-@erase ".\Release\specfunc\ellint.obj"
	-@erase ".\Release\specfunc\elljac.obj"
	-@erase ".\Release\specfunc\erfc.obj"
	-@erase ".\Release\specfunc\exp.obj"
	-@erase ".\Release\specfunc\expint.obj"
	-@erase ".\Release\specfunc\expint3.obj"
	-@erase ".\Release\specfunc\fermi_dirac.obj"
	-@erase ".\Release\specfunc\gamma.obj"
	-@erase ".\Release\specfunc\gamma_inc.obj"
	-@erase ".\Release\specfunc\gegenbauer.obj"
	-@erase ".\Release\specfunc\hyperg.obj"
	-@erase ".\Release\specfunc\hyperg_0F1.obj"
	-@erase ".\Release\specfunc\hyperg_1F1.obj"
	-@erase ".\Release\specfunc\hyperg_2F0.obj"
	-@erase ".\Release\specfunc\hyperg_2F1.obj"
	-@erase ".\Release\specfunc\hyperg_U.obj"
	-@erase ".\Release\specfunc\laguerre.obj"
	-@erase ".\Release\specfunc\lambert.obj"
	-@erase ".\Release\specfunc\legendre_con.obj"
	-@erase ".\Release\specfunc\legendre_H3d.obj"
	-@erase ".\Release\specfunc\legendre_poly.obj"
	-@erase ".\Release\specfunc\legendre_Qn.obj"
	-@erase ".\Release\specfunc\log.obj"
	-@erase ".\Release\specfunc\poch.obj"
	-@erase ".\Release\specfunc\pow_int.obj"
	-@erase ".\Release\specfunc\psi.obj"
	-@erase ".\Release\specfunc\result.obj"
	-@erase ".\Release\specfunc\shint.obj"
	-@erase ".\Release\specfunc\sinint.obj"
	-@erase ".\Release\specfunc\synchrotron.obj"
	-@erase ".\Release\specfunc\transport.obj"
	-@erase ".\Release\specfunc\trig.obj"
	-@erase ".\Release\specfunc\zeta.obj"
	-@erase ".\Release\sys\coerce.obj"
	-@erase ".\Release\sys\expm1.obj"
	-@erase ".\Release\sys\fcmp.obj"
	-@erase ".\Release\sys\fdiv.obj"
	-@erase ".\Release\sys\hypot.obj"
	-@erase ".\Release\sys\infnan.obj"
	-@erase ".\Release\sys\invhyp.obj"
	-@erase ".\Release\sys\ldfrexp.obj"
	-@erase ".\Release\sys\log1p.obj"
	-@erase ".\Release\sys\minmax.obj"
	-@erase ".\Release\sys\pow_int.obj"
	-@erase ".\Release\sys\prec.obj"
	-@erase ".\Release\vector\copy.obj"
	-@erase ".\Release\vector\file.obj"
	-@erase ".\Release\vector\init.obj"
	-@erase ".\Release\vector\minmax.obj"
	-@erase ".\Release\vector\oper.obj"
	-@erase ".\Release\vector\prop.obj"
	-@erase ".\Release\vector\reim.obj"
	-@erase ".\Release\vector\subvector.obj"
	-@erase ".\Release\vector\swap.obj"
	-@erase ".\Release\vector\vector.obj"
	-@erase ".\Release\vector\view.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\gsl18_vc6.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\gsl18_vc6.pdb" /machine:I386 /out:"$(OUTDIR)\gsl18_vc6.dll" /implib:"$(OUTDIR)\gsl18_vc6.lib" 
LINK32_OBJS= \
	"$(INTDIR)\gsl18_vc6.obj" \
	".\Release\multifit\convergence.obj" \
	".\Release\multifit\covar.obj" \
	".\Release\multifit\fdfsolver.obj" \
	".\Release\multifit\fsolver.obj" \
	".\Release\multifit\gradient.obj" \
	".\Release\multifit\lmder.obj" \
	".\Release\multifit\multilinear.obj" \
	".\Release\multifit\work.obj" \
	".\Release\err\error.obj" \
	".\Release\err\message.obj" \
	".\Release\err\stream.obj" \
	".\Release\err\strerror.obj" \
	".\Release\vector\copy.obj" \
	".\Release\vector\file.obj" \
	".\Release\vector\init.obj" \
	".\Release\vector\minmax.obj" \
	".\Release\vector\oper.obj" \
	".\Release\vector\prop.obj" \
	".\Release\vector\reim.obj" \
	".\Release\vector\subvector.obj" \
	".\Release\vector\swap.obj" \
	".\Release\vector\vector.obj" \
	".\Release\vector\view.obj" \
	".\Release\permutation\canonical.obj" \
	".\Release\permutation\file.obj" \
	".\Release\permutation\init.obj" \
	".\Release\permutation\permutation.obj" \
	".\Release\permutation\permute.obj" \
	".\Release\matrix\copy.obj" \
	".\Release\matrix\file.obj" \
	".\Release\matrix\getset.obj" \
	".\Release\matrix\init.obj" \
	".\Release\matrix\matrix.obj" \
	".\Release\matrix\minmax.obj" \
	".\Release\matrix\oper.obj" \
	".\Release\matrix\prop.obj" \
	".\Release\matrix\rowcol.obj" \
	".\Release\matrix\submatrix.obj" \
	".\Release\matrix\swap.obj" \
	".\Release\matrix\view.obj" \
	".\Release\linalg\balance.obj" \
	".\Release\linalg\bidiag.obj" \
	".\Release\linalg\cholesky.obj" \
	".\Release\linalg\exponential.obj" \
	".\Release\linalg\hermtd.obj" \
	".\Release\linalg\hh.obj" \
	".\Release\linalg\householder.obj" \
	".\Release\linalg\householdercomplex.obj" \
	".\Release\linalg\lq.obj" \
	".\Release\linalg\lu.obj" \
	".\Release\linalg\luc.obj" \
	".\Release\linalg\multiply.obj" \
	".\Release\linalg\ptlq.obj" \
	".\Release\linalg\qr.obj" \
	".\Release\linalg\qrpt.obj" \
	".\Release\linalg\svd.obj" \
	".\Release\linalg\symmtd.obj" \
	".\Release\linalg\tridiag.obj" \
	".\Release\block\block.obj" \
	".\Release\block\file.obj" \
	".\Release\block\init.obj" \
	".\Release\blas\blas.obj" \
	".\Release\cblas\caxpy.obj" \
	".\Release\cblas\ccopy.obj" \
	".\Release\cblas\cdotc_sub.obj" \
	".\Release\cblas\cdotu_sub.obj" \
	".\Release\cblas\cgbmv.obj" \
	".\Release\cblas\cgemm.obj" \
	".\Release\cblas\cgemv.obj" \
	".\Release\cblas\cgerc.obj" \
	".\Release\cblas\cgeru.obj" \
	".\Release\cblas\chbmv.obj" \
	".\Release\cblas\chemm.obj" \
	".\Release\cblas\chemv.obj" \
	".\Release\cblas\cher.obj" \
	".\Release\cblas\cher2.obj" \
	".\Release\cblas\cher2k.obj" \
	".\Release\cblas\cherk.obj" \
	".\Release\cblas\chpmv.obj" \
	".\Release\cblas\chpr.obj" \
	".\Release\cblas\chpr2.obj" \
	".\Release\cblas\cscal.obj" \
	".\Release\cblas\csscal.obj" \
	".\Release\cblas\cswap.obj" \
	".\Release\cblas\csymm.obj" \
	".\Release\cblas\csyr2k.obj" \
	".\Release\cblas\csyrk.obj" \
	".\Release\cblas\ctbmv.obj" \
	".\Release\cblas\ctbsv.obj" \
	".\Release\cblas\ctpmv.obj" \
	".\Release\cblas\ctpsv.obj" \
	".\Release\cblas\ctrmm.obj" \
	".\Release\cblas\ctrmv.obj" \
	".\Release\cblas\ctrsm.obj" \
	".\Release\cblas\ctrsv.obj" \
	".\Release\cblas\dasum.obj" \
	".\Release\cblas\daxpy.obj" \
	".\Release\cblas\dcopy.obj" \
	".\Release\cblas\ddot.obj" \
	".\Release\cblas\dgbmv.obj" \
	".\Release\cblas\dgemm.obj" \
	".\Release\cblas\dgemv.obj" \
	".\Release\cblas\dger.obj" \
	".\Release\cblas\dnrm2.obj" \
	".\Release\cblas\drot.obj" \
	".\Release\cblas\drotg.obj" \
	".\Release\cblas\drotm.obj" \
	".\Release\cblas\drotmg.obj" \
	".\Release\cblas\dsbmv.obj" \
	".\Release\cblas\dscal.obj" \
	".\Release\cblas\dsdot.obj" \
	".\Release\cblas\dspmv.obj" \
	".\Release\cblas\dspr.obj" \
	".\Release\cblas\dspr2.obj" \
	".\Release\cblas\dswap.obj" \
	".\Release\cblas\dsymm.obj" \
	".\Release\cblas\dsymv.obj" \
	".\Release\cblas\dsyr.obj" \
	".\Release\cblas\dsyr2.obj" \
	".\Release\cblas\dsyr2k.obj" \
	".\Release\cblas\dsyrk.obj" \
	".\Release\cblas\dtbmv.obj" \
	".\Release\cblas\dtbsv.obj" \
	".\Release\cblas\dtpmv.obj" \
	".\Release\cblas\dtpsv.obj" \
	".\Release\cblas\dtrmm.obj" \
	".\Release\cblas\dtrmv.obj" \
	".\Release\cblas\dtrsm.obj" \
	".\Release\cblas\dtrsv.obj" \
	".\Release\cblas\dzasum.obj" \
	".\Release\cblas\dznrm2.obj" \
	".\Release\cblas\hypot.obj" \
	".\Release\cblas\icamax.obj" \
	".\Release\cblas\idamax.obj" \
	".\Release\cblas\isamax.obj" \
	".\Release\cblas\izamax.obj" \
	".\Release\cblas\sasum.obj" \
	".\Release\cblas\saxpy.obj" \
	".\Release\cblas\scasum.obj" \
	".\Release\cblas\scnrm2.obj" \
	".\Release\cblas\scopy.obj" \
	".\Release\cblas\sdot.obj" \
	".\Release\cblas\sdsdot.obj" \
	".\Release\cblas\sgbmv.obj" \
	".\Release\cblas\sgemm.obj" \
	".\Release\cblas\sgemv.obj" \
	".\Release\cblas\sger.obj" \
	".\Release\cblas\snrm2.obj" \
	".\Release\cblas\srot.obj" \
	".\Release\cblas\srotg.obj" \
	".\Release\cblas\srotm.obj" \
	".\Release\cblas\srotmg.obj" \
	".\Release\cblas\ssbmv.obj" \
	".\Release\cblas\sscal.obj" \
	".\Release\cblas\sspmv.obj" \
	".\Release\cblas\sspr.obj" \
	".\Release\cblas\sspr2.obj" \
	".\Release\cblas\sswap.obj" \
	".\Release\cblas\ssymm.obj" \
	".\Release\cblas\ssymv.obj" \
	".\Release\cblas\ssyr.obj" \
	".\Release\cblas\ssyr2.obj" \
	".\Release\cblas\ssyr2k.obj" \
	".\Release\cblas\ssyrk.obj" \
	".\Release\cblas\stbmv.obj" \
	".\Release\cblas\stbsv.obj" \
	".\Release\cblas\stpmv.obj" \
	".\Release\cblas\stpsv.obj" \
	".\Release\cblas\strmm.obj" \
	".\Release\cblas\strmv.obj" \
	".\Release\cblas\strsm.obj" \
	".\Release\cblas\strsv.obj" \
	".\Release\cblas\xerbla.obj" \
	".\Release\cblas\zaxpy.obj" \
	".\Release\cblas\zcopy.obj" \
	".\Release\cblas\zdotc_sub.obj" \
	".\Release\cblas\zdotu_sub.obj" \
	".\Release\cblas\zdscal.obj" \
	".\Release\cblas\zgbmv.obj" \
	".\Release\cblas\zgemm.obj" \
	".\Release\cblas\zgemv.obj" \
	".\Release\cblas\zgerc.obj" \
	".\Release\cblas\zgeru.obj" \
	".\Release\cblas\zhbmv.obj" \
	".\Release\cblas\zhemm.obj" \
	".\Release\cblas\zhemv.obj" \
	".\Release\cblas\zher.obj" \
	".\Release\cblas\zher2.obj" \
	".\Release\cblas\zher2k.obj" \
	".\Release\cblas\zherk.obj" \
	".\Release\cblas\zhpmv.obj" \
	".\Release\cblas\zhpr.obj" \
	".\Release\cblas\zhpr2.obj" \
	".\Release\cblas\zscal.obj" \
	".\Release\cblas\zswap.obj" \
	".\Release\cblas\zsymm.obj" \
	".\Release\cblas\zsyr2k.obj" \
	".\Release\cblas\zsyrk.obj" \
	".\Release\cblas\ztbmv.obj" \
	".\Release\cblas\ztbsv.obj" \
	".\Release\cblas\ztpmv.obj" \
	".\Release\cblas\ztpsv.obj" \
	".\Release\cblas\ztrmm.obj" \
	".\Release\cblas\ztrmv.obj" \
	".\Release\cblas\ztrsm.obj" \
	".\Release\cblas\ztrsv.obj" \
	".\Release\sys\coerce.obj" \
	".\Release\sys\expm1.obj" \
	".\Release\sys\fcmp.obj" \
	".\Release\sys\fdiv.obj" \
	".\Release\sys\hypot.obj" \
	".\Release\sys\infnan.obj" \
	".\Release\sys\invhyp.obj" \
	".\Release\sys\ldfrexp.obj" \
	".\Release\sys\log1p.obj" \
	".\Release\sys\minmax.obj" \
	".\Release\sys\pow_int.obj" \
	".\Release\sys\prec.obj" \
	".\Release\complex\math.obj" \
	".\Release\ode-initval\bsimp.obj" \
	".\Release\ode-initval\control.obj" \
	".\Release\ode-initval\cscal.obj" \
	".\Release\ode-initval\cstd.obj" \
	".\Release\ode-initval\evolve.obj" \
	".\Release\ode-initval\gear1.obj" \
	".\Release\ode-initval\gear2.obj" \
	".\Release\ode-initval\rk2.obj" \
	".\Release\ode-initval\rk2imp.obj" \
	".\Release\ode-initval\rk2simp.obj" \
	".\Release\ode-initval\rk4.obj" \
	".\Release\ode-initval\rk4imp.obj" \
	".\Release\ode-initval\rk8pd.obj" \
	".\Release\ode-initval\rkck.obj" \
	".\Release\ode-initval\rkf45.obj" \
	".\Release\ode-initval\step.obj" \
	".\Release\randist\bernoulli.obj" \
	".\Release\randist\beta.obj" \
	".\Release\randist\bigauss.obj" \
	".\Release\randist\binomial.obj" \
	".\Release\randist\binomial_tpe.obj" \
	".\Release\randist\cauchy.obj" \
	".\Release\randist\chisq.obj" \
	".\Release\randist\dirichlet.obj" \
	".\Release\randist\discrete.obj" \
	".\Release\randist\erlang.obj" \
	".\Release\randist\exponential.obj" \
	".\Release\randist\exppow.obj" \
	".\Release\randist\fdist.obj" \
	".\Release\randist\flat.obj" \
	".\Release\randist\gamma.obj" \
	".\Release\randist\gauss.obj" \
	".\Release\randist\gausstail.obj" \
	".\Release\randist\gausszig.obj" \
	".\Release\randist\geometric.obj" \
	".\Release\randist\gumbel.obj" \
	".\Release\randist\hyperg.obj" \
	".\Release\randist\landau.obj" \
	".\Release\randist\laplace.obj" \
	".\Release\randist\levy.obj" \
	".\Release\randist\logarithmic.obj" \
	".\Release\randist\logistic.obj" \
	".\Release\randist\lognormal.obj" \
	".\Release\randist\multinomial.obj" \
	".\Release\randist\nbinomial.obj" \
	".\Release\randist\pareto.obj" \
	".\Release\randist\pascal.obj" \
	".\Release\randist\poisson.obj" \
	".\Release\randist\rayleigh.obj" \
	".\Release\randist\shuffle.obj" \
	".\Release\randist\sphere.obj" \
	".\Release\randist\tdist.obj" \
	".\Release\randist\weibull.obj" \
	".\Release\specfunc\airy.obj" \
	".\Release\specfunc\airy_der.obj" \
	".\Release\specfunc\airy_zero.obj" \
	".\Release\specfunc\atanint.obj" \
	".\Release\specfunc\bessel.obj" \
	".\Release\specfunc\bessel_amp_phase.obj" \
	".\Release\specfunc\bessel_i.obj" \
	".\Release\specfunc\bessel_I0.obj" \
	".\Release\specfunc\bessel_I1.obj" \
	".\Release\specfunc\bessel_In.obj" \
	".\Release\specfunc\bessel_Inu.obj" \
	".\Release\specfunc\bessel_j.obj" \
	".\Release\specfunc\bessel_J0.obj" \
	".\Release\specfunc\bessel_J1.obj" \
	".\Release\specfunc\bessel_Jn.obj" \
	".\Release\specfunc\bessel_Jnu.obj" \
	".\Release\specfunc\bessel_k.obj" \
	".\Release\specfunc\bessel_K0.obj" \
	".\Release\specfunc\bessel_K1.obj" \
	".\Release\specfunc\bessel_Kn.obj" \
	".\Release\specfunc\bessel_Knu.obj" \
	".\Release\specfunc\bessel_olver.obj" \
	".\Release\specfunc\bessel_sequence.obj" \
	".\Release\specfunc\bessel_temme.obj" \
	".\Release\specfunc\bessel_y.obj" \
	".\Release\specfunc\bessel_Y0.obj" \
	".\Release\specfunc\bessel_Y1.obj" \
	".\Release\specfunc\bessel_Yn.obj" \
	".\Release\specfunc\bessel_Ynu.obj" \
	".\Release\specfunc\bessel_zero.obj" \
	".\Release\specfunc\beta.obj" \
	".\Release\specfunc\beta_inc.obj" \
	".\Release\specfunc\clausen.obj" \
	".\Release\specfunc\coulomb.obj" \
	".\Release\specfunc\coulomb_bound.obj" \
	".\Release\specfunc\coupling.obj" \
	".\Release\specfunc\dawson.obj" \
	".\Release\specfunc\debye.obj" \
	".\Release\specfunc\dilog.obj" \
	".\Release\specfunc\elementary.obj" \
	".\Release\specfunc\ellint.obj" \
	".\Release\specfunc\elljac.obj" \
	".\Release\specfunc\erfc.obj" \
	".\Release\specfunc\exp.obj" \
	".\Release\specfunc\expint.obj" \
	".\Release\specfunc\expint3.obj" \
	".\Release\specfunc\fermi_dirac.obj" \
	".\Release\specfunc\gamma.obj" \
	".\Release\specfunc\gamma_inc.obj" \
	".\Release\specfunc\gegenbauer.obj" \
	".\Release\specfunc\hyperg.obj" \
	".\Release\specfunc\hyperg_0F1.obj" \
	".\Release\specfunc\hyperg_1F1.obj" \
	".\Release\specfunc\hyperg_2F0.obj" \
	".\Release\specfunc\hyperg_2F1.obj" \
	".\Release\specfunc\hyperg_U.obj" \
	".\Release\specfunc\laguerre.obj" \
	".\Release\specfunc\lambert.obj" \
	".\Release\specfunc\legendre_con.obj" \
	".\Release\specfunc\legendre_H3d.obj" \
	".\Release\specfunc\legendre_poly.obj" \
	".\Release\specfunc\legendre_Qn.obj" \
	".\Release\specfunc\log.obj" \
	".\Release\specfunc\poch.obj" \
	".\Release\specfunc\pow_int.obj" \
	".\Release\specfunc\psi.obj" \
	".\Release\specfunc\result.obj" \
	".\Release\specfunc\shint.obj" \
	".\Release\specfunc\sinint.obj" \
	".\Release\specfunc\synchrotron.obj" \
	".\Release\specfunc\transport.obj" \
	".\Release\specfunc\trig.obj" \
	".\Release\specfunc\zeta.obj" \
	".\Release\rng\borosh13.obj" \
	".\Release\rng\cmrg.obj" \
	".\Release\rng\coveyou.obj" \
	".\Release\rng\default.obj" \
	".\Release\rng\file.obj" \
	".\Release\rng\fishman18.obj" \
	".\Release\rng\fishman20.obj" \
	".\Release\rng\fishman2x.obj" \
	".\Release\rng\gfsr4.obj" \
	".\Release\rng\knuthran.obj" \
	".\Release\rng\knuthran2.obj" \
	".\Release\rng\lecuyer21.obj" \
	".\Release\rng\minstd.obj" \
	".\Release\rng\mrg.obj" \
	".\Release\rng\mt.obj" \
	".\Release\rng\r250.obj" \
	".\Release\rng\ran0.obj" \
	".\Release\rng\ran1.obj" \
	".\Release\rng\ran2.obj" \
	".\Release\rng\ran3.obj" \
	".\Release\rng\rand.obj" \
	".\Release\rng\rand48.obj" \
	".\Release\rng\random.obj" \
	".\Release\rng\randu.obj" \
	".\Release\rng\ranf.obj" \
	".\Release\rng\ranlux.obj" \
	".\Release\rng\ranlxd.obj" \
	".\Release\rng\ranlxs.obj" \
	".\Release\rng\ranmar.obj" \
	".\Release\rng\rng.obj" \
	".\Release\rng\slatec.obj" \
	".\Release\rng\taus.obj" \
	".\Release\rng\taus113.obj" \
	".\Release\rng\transputer.obj" \
	".\Release\rng\tt.obj" \
	".\Release\rng\types.obj" \
	".\Release\rng\uni.obj" \
	".\Release\rng\uni32.obj" \
	".\Release\rng\vax.obj" \
	".\Release\rng\waterman14.obj" \
	".\Release\rng\zuf.obj" \
	"$(INTDIR)\fft.obj"

"$(OUTDIR)\gsl18_vc6.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\gsl18_vc6.dll"
   copy Release\*.dll ..\..\..\zlab
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\gsl18_vc6D.dll"


CLEAN :
	-@erase "$(INTDIR)\blas\vc60.idb"
	-@erase "$(INTDIR)\blas\vc60.pdb"
	-@erase "$(INTDIR)\block\vc60.idb"
	-@erase "$(INTDIR)\block\vc60.pdb"
	-@erase "$(INTDIR)\cblas\vc60.idb"
	-@erase "$(INTDIR)\cblas\vc60.pdb"
	-@erase "$(INTDIR)\complex\vc60.idb"
	-@erase "$(INTDIR)\complex\vc60.pdb"
	-@erase "$(INTDIR)\err\vc60.idb"
	-@erase "$(INTDIR)\err\vc60.pdb"
	-@erase "$(INTDIR)\fft.obj"
	-@erase "$(INTDIR)\gsl18_vc6.obj"
	-@erase "$(INTDIR)\linalg\vc60.idb"
	-@erase "$(INTDIR)\linalg\vc60.pdb"
	-@erase "$(INTDIR)\matrix\vc60.idb"
	-@erase "$(INTDIR)\matrix\vc60.pdb"
	-@erase "$(INTDIR)\multifit\vc60.idb"
	-@erase "$(INTDIR)\multifit\vc60.pdb"
	-@erase "$(INTDIR)\ode-initval\vc60.idb"
	-@erase "$(INTDIR)\ode-initval\vc60.pdb"
	-@erase "$(INTDIR)\permutation\vc60.idb"
	-@erase "$(INTDIR)\permutation\vc60.pdb"
	-@erase "$(INTDIR)\randist\vc60.idb"
	-@erase "$(INTDIR)\randist\vc60.pdb"
	-@erase "$(INTDIR)\rng\vc60.idb"
	-@erase "$(INTDIR)\rng\vc60.pdb"
	-@erase "$(INTDIR)\specfunc\vc60.idb"
	-@erase "$(INTDIR)\specfunc\vc60.pdb"
	-@erase "$(INTDIR)\sys\vc60.idb"
	-@erase "$(INTDIR)\sys\vc60.pdb"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vector\vc60.idb"
	-@erase "$(INTDIR)\vector\vc60.pdb"
	-@erase "$(OUTDIR)\gsl18_vc6D.dll"
	-@erase "$(OUTDIR)\gsl18_vc6D.exp"
	-@erase "$(OUTDIR)\gsl18_vc6D.ilk"
	-@erase "$(OUTDIR)\gsl18_vc6D.lib"
	-@erase "$(OUTDIR)\gsl18_vc6D.pdb"
	-@erase ".\Debug\blas\blas.obj"
	-@erase ".\Debug\block\block.obj"
	-@erase ".\Debug\block\file.obj"
	-@erase ".\Debug\block\init.obj"
	-@erase ".\Debug\cblas\caxpy.obj"
	-@erase ".\Debug\cblas\ccopy.obj"
	-@erase ".\Debug\cblas\cdotc_sub.obj"
	-@erase ".\Debug\cblas\cdotu_sub.obj"
	-@erase ".\Debug\cblas\cgbmv.obj"
	-@erase ".\Debug\cblas\cgemm.obj"
	-@erase ".\Debug\cblas\cgemv.obj"
	-@erase ".\Debug\cblas\cgerc.obj"
	-@erase ".\Debug\cblas\cgeru.obj"
	-@erase ".\Debug\cblas\chbmv.obj"
	-@erase ".\Debug\cblas\chemm.obj"
	-@erase ".\Debug\cblas\chemv.obj"
	-@erase ".\Debug\cblas\cher.obj"
	-@erase ".\Debug\cblas\cher2.obj"
	-@erase ".\Debug\cblas\cher2k.obj"
	-@erase ".\Debug\cblas\cherk.obj"
	-@erase ".\Debug\cblas\chpmv.obj"
	-@erase ".\Debug\cblas\chpr.obj"
	-@erase ".\Debug\cblas\chpr2.obj"
	-@erase ".\Debug\cblas\cscal.obj"
	-@erase ".\Debug\cblas\csscal.obj"
	-@erase ".\Debug\cblas\cswap.obj"
	-@erase ".\Debug\cblas\csymm.obj"
	-@erase ".\Debug\cblas\csyr2k.obj"
	-@erase ".\Debug\cblas\csyrk.obj"
	-@erase ".\Debug\cblas\ctbmv.obj"
	-@erase ".\Debug\cblas\ctbsv.obj"
	-@erase ".\Debug\cblas\ctpmv.obj"
	-@erase ".\Debug\cblas\ctpsv.obj"
	-@erase ".\Debug\cblas\ctrmm.obj"
	-@erase ".\Debug\cblas\ctrmv.obj"
	-@erase ".\Debug\cblas\ctrsm.obj"
	-@erase ".\Debug\cblas\ctrsv.obj"
	-@erase ".\Debug\cblas\dasum.obj"
	-@erase ".\Debug\cblas\daxpy.obj"
	-@erase ".\Debug\cblas\dcopy.obj"
	-@erase ".\Debug\cblas\ddot.obj"
	-@erase ".\Debug\cblas\dgbmv.obj"
	-@erase ".\Debug\cblas\dgemm.obj"
	-@erase ".\Debug\cblas\dgemv.obj"
	-@erase ".\Debug\cblas\dger.obj"
	-@erase ".\Debug\cblas\dnrm2.obj"
	-@erase ".\Debug\cblas\drot.obj"
	-@erase ".\Debug\cblas\drotg.obj"
	-@erase ".\Debug\cblas\drotm.obj"
	-@erase ".\Debug\cblas\drotmg.obj"
	-@erase ".\Debug\cblas\dsbmv.obj"
	-@erase ".\Debug\cblas\dscal.obj"
	-@erase ".\Debug\cblas\dsdot.obj"
	-@erase ".\Debug\cblas\dspmv.obj"
	-@erase ".\Debug\cblas\dspr.obj"
	-@erase ".\Debug\cblas\dspr2.obj"
	-@erase ".\Debug\cblas\dswap.obj"
	-@erase ".\Debug\cblas\dsymm.obj"
	-@erase ".\Debug\cblas\dsymv.obj"
	-@erase ".\Debug\cblas\dsyr.obj"
	-@erase ".\Debug\cblas\dsyr2.obj"
	-@erase ".\Debug\cblas\dsyr2k.obj"
	-@erase ".\Debug\cblas\dsyrk.obj"
	-@erase ".\Debug\cblas\dtbmv.obj"
	-@erase ".\Debug\cblas\dtbsv.obj"
	-@erase ".\Debug\cblas\dtpmv.obj"
	-@erase ".\Debug\cblas\dtpsv.obj"
	-@erase ".\Debug\cblas\dtrmm.obj"
	-@erase ".\Debug\cblas\dtrmv.obj"
	-@erase ".\Debug\cblas\dtrsm.obj"
	-@erase ".\Debug\cblas\dtrsv.obj"
	-@erase ".\Debug\cblas\dzasum.obj"
	-@erase ".\Debug\cblas\dznrm2.obj"
	-@erase ".\Debug\cblas\hypot.obj"
	-@erase ".\Debug\cblas\icamax.obj"
	-@erase ".\Debug\cblas\idamax.obj"
	-@erase ".\Debug\cblas\isamax.obj"
	-@erase ".\Debug\cblas\izamax.obj"
	-@erase ".\Debug\cblas\sasum.obj"
	-@erase ".\Debug\cblas\saxpy.obj"
	-@erase ".\Debug\cblas\scasum.obj"
	-@erase ".\Debug\cblas\scnrm2.obj"
	-@erase ".\Debug\cblas\scopy.obj"
	-@erase ".\Debug\cblas\sdot.obj"
	-@erase ".\Debug\cblas\sdsdot.obj"
	-@erase ".\Debug\cblas\sgbmv.obj"
	-@erase ".\Debug\cblas\sgemm.obj"
	-@erase ".\Debug\cblas\sgemv.obj"
	-@erase ".\Debug\cblas\sger.obj"
	-@erase ".\Debug\cblas\snrm2.obj"
	-@erase ".\Debug\cblas\srot.obj"
	-@erase ".\Debug\cblas\srotg.obj"
	-@erase ".\Debug\cblas\srotm.obj"
	-@erase ".\Debug\cblas\srotmg.obj"
	-@erase ".\Debug\cblas\ssbmv.obj"
	-@erase ".\Debug\cblas\sscal.obj"
	-@erase ".\Debug\cblas\sspmv.obj"
	-@erase ".\Debug\cblas\sspr.obj"
	-@erase ".\Debug\cblas\sspr2.obj"
	-@erase ".\Debug\cblas\sswap.obj"
	-@erase ".\Debug\cblas\ssymm.obj"
	-@erase ".\Debug\cblas\ssymv.obj"
	-@erase ".\Debug\cblas\ssyr.obj"
	-@erase ".\Debug\cblas\ssyr2.obj"
	-@erase ".\Debug\cblas\ssyr2k.obj"
	-@erase ".\Debug\cblas\ssyrk.obj"
	-@erase ".\Debug\cblas\stbmv.obj"
	-@erase ".\Debug\cblas\stbsv.obj"
	-@erase ".\Debug\cblas\stpmv.obj"
	-@erase ".\Debug\cblas\stpsv.obj"
	-@erase ".\Debug\cblas\strmm.obj"
	-@erase ".\Debug\cblas\strmv.obj"
	-@erase ".\Debug\cblas\strsm.obj"
	-@erase ".\Debug\cblas\strsv.obj"
	-@erase ".\Debug\cblas\xerbla.obj"
	-@erase ".\Debug\cblas\zaxpy.obj"
	-@erase ".\Debug\cblas\zcopy.obj"
	-@erase ".\Debug\cblas\zdotc_sub.obj"
	-@erase ".\Debug\cblas\zdotu_sub.obj"
	-@erase ".\Debug\cblas\zdscal.obj"
	-@erase ".\Debug\cblas\zgbmv.obj"
	-@erase ".\Debug\cblas\zgemm.obj"
	-@erase ".\Debug\cblas\zgemv.obj"
	-@erase ".\Debug\cblas\zgerc.obj"
	-@erase ".\Debug\cblas\zgeru.obj"
	-@erase ".\Debug\cblas\zhbmv.obj"
	-@erase ".\Debug\cblas\zhemm.obj"
	-@erase ".\Debug\cblas\zhemv.obj"
	-@erase ".\Debug\cblas\zher.obj"
	-@erase ".\Debug\cblas\zher2.obj"
	-@erase ".\Debug\cblas\zher2k.obj"
	-@erase ".\Debug\cblas\zherk.obj"
	-@erase ".\Debug\cblas\zhpmv.obj"
	-@erase ".\Debug\cblas\zhpr.obj"
	-@erase ".\Debug\cblas\zhpr2.obj"
	-@erase ".\Debug\cblas\zscal.obj"
	-@erase ".\Debug\cblas\zswap.obj"
	-@erase ".\Debug\cblas\zsymm.obj"
	-@erase ".\Debug\cblas\zsyr2k.obj"
	-@erase ".\Debug\cblas\zsyrk.obj"
	-@erase ".\Debug\cblas\ztbmv.obj"
	-@erase ".\Debug\cblas\ztbsv.obj"
	-@erase ".\Debug\cblas\ztpmv.obj"
	-@erase ".\Debug\cblas\ztpsv.obj"
	-@erase ".\Debug\cblas\ztrmm.obj"
	-@erase ".\Debug\cblas\ztrmv.obj"
	-@erase ".\Debug\cblas\ztrsm.obj"
	-@erase ".\Debug\cblas\ztrsv.obj"
	-@erase ".\Debug\complex\math.obj"
	-@erase ".\Debug\err\error.obj"
	-@erase ".\Debug\err\message.obj"
	-@erase ".\Debug\err\stream.obj"
	-@erase ".\Debug\err\strerror.obj"
	-@erase ".\Debug\linalg\balance.obj"
	-@erase ".\Debug\linalg\bidiag.obj"
	-@erase ".\Debug\linalg\cholesky.obj"
	-@erase ".\Debug\linalg\exponential.obj"
	-@erase ".\Debug\linalg\hermtd.obj"
	-@erase ".\Debug\linalg\hh.obj"
	-@erase ".\Debug\linalg\householder.obj"
	-@erase ".\Debug\linalg\householdercomplex.obj"
	-@erase ".\Debug\linalg\lq.obj"
	-@erase ".\Debug\linalg\lu.obj"
	-@erase ".\Debug\linalg\luc.obj"
	-@erase ".\Debug\linalg\multiply.obj"
	-@erase ".\Debug\linalg\ptlq.obj"
	-@erase ".\Debug\linalg\qr.obj"
	-@erase ".\Debug\linalg\qrpt.obj"
	-@erase ".\Debug\linalg\svd.obj"
	-@erase ".\Debug\linalg\symmtd.obj"
	-@erase ".\Debug\linalg\tridiag.obj"
	-@erase ".\Debug\matrix\copy.obj"
	-@erase ".\Debug\matrix\file.obj"
	-@erase ".\Debug\matrix\getset.obj"
	-@erase ".\Debug\matrix\init.obj"
	-@erase ".\Debug\matrix\matrix.obj"
	-@erase ".\Debug\matrix\minmax.obj"
	-@erase ".\Debug\matrix\oper.obj"
	-@erase ".\Debug\matrix\prop.obj"
	-@erase ".\Debug\matrix\rowcol.obj"
	-@erase ".\Debug\matrix\submatrix.obj"
	-@erase ".\Debug\matrix\swap.obj"
	-@erase ".\Debug\matrix\view.obj"
	-@erase ".\Debug\multifit\convergence.obj"
	-@erase ".\Debug\multifit\covar.obj"
	-@erase ".\Debug\multifit\fdfsolver.obj"
	-@erase ".\Debug\multifit\fsolver.obj"
	-@erase ".\Debug\multifit\gradient.obj"
	-@erase ".\Debug\multifit\lmder.obj"
	-@erase ".\Debug\multifit\multilinear.obj"
	-@erase ".\Debug\multifit\work.obj"
	-@erase ".\Debug\ode-initval\bsimp.obj"
	-@erase ".\Debug\ode-initval\control.obj"
	-@erase ".\Debug\ode-initval\cscal.obj"
	-@erase ".\Debug\ode-initval\cstd.obj"
	-@erase ".\Debug\ode-initval\evolve.obj"
	-@erase ".\Debug\ode-initval\gear1.obj"
	-@erase ".\Debug\ode-initval\gear2.obj"
	-@erase ".\Debug\ode-initval\rk2.obj"
	-@erase ".\Debug\ode-initval\rk2imp.obj"
	-@erase ".\Debug\ode-initval\rk2simp.obj"
	-@erase ".\Debug\ode-initval\rk4.obj"
	-@erase ".\Debug\ode-initval\rk4imp.obj"
	-@erase ".\Debug\ode-initval\rk8pd.obj"
	-@erase ".\Debug\ode-initval\rkck.obj"
	-@erase ".\Debug\ode-initval\rkf45.obj"
	-@erase ".\Debug\ode-initval\step.obj"
	-@erase ".\Debug\permutation\canonical.obj"
	-@erase ".\Debug\permutation\file.obj"
	-@erase ".\Debug\permutation\init.obj"
	-@erase ".\Debug\permutation\permutation.obj"
	-@erase ".\Debug\permutation\permute.obj"
	-@erase ".\Debug\randist\bernoulli.obj"
	-@erase ".\Debug\randist\beta.obj"
	-@erase ".\Debug\randist\bigauss.obj"
	-@erase ".\Debug\randist\binomial.obj"
	-@erase ".\Debug\randist\binomial_tpe.obj"
	-@erase ".\Debug\randist\cauchy.obj"
	-@erase ".\Debug\randist\chisq.obj"
	-@erase ".\Debug\randist\dirichlet.obj"
	-@erase ".\Debug\randist\discrete.obj"
	-@erase ".\Debug\randist\erlang.obj"
	-@erase ".\Debug\randist\exponential.obj"
	-@erase ".\Debug\randist\exppow.obj"
	-@erase ".\Debug\randist\fdist.obj"
	-@erase ".\Debug\randist\flat.obj"
	-@erase ".\Debug\randist\gamma.obj"
	-@erase ".\Debug\randist\gauss.obj"
	-@erase ".\Debug\randist\gausstail.obj"
	-@erase ".\Debug\randist\gausszig.obj"
	-@erase ".\Debug\randist\geometric.obj"
	-@erase ".\Debug\randist\gumbel.obj"
	-@erase ".\Debug\randist\hyperg.obj"
	-@erase ".\Debug\randist\landau.obj"
	-@erase ".\Debug\randist\laplace.obj"
	-@erase ".\Debug\randist\levy.obj"
	-@erase ".\Debug\randist\logarithmic.obj"
	-@erase ".\Debug\randist\logistic.obj"
	-@erase ".\Debug\randist\lognormal.obj"
	-@erase ".\Debug\randist\multinomial.obj"
	-@erase ".\Debug\randist\nbinomial.obj"
	-@erase ".\Debug\randist\pareto.obj"
	-@erase ".\Debug\randist\pascal.obj"
	-@erase ".\Debug\randist\poisson.obj"
	-@erase ".\Debug\randist\rayleigh.obj"
	-@erase ".\Debug\randist\shuffle.obj"
	-@erase ".\Debug\randist\sphere.obj"
	-@erase ".\Debug\randist\tdist.obj"
	-@erase ".\Debug\randist\weibull.obj"
	-@erase ".\Debug\rng\borosh13.obj"
	-@erase ".\Debug\rng\cmrg.obj"
	-@erase ".\Debug\rng\coveyou.obj"
	-@erase ".\Debug\rng\default.obj"
	-@erase ".\Debug\rng\file.obj"
	-@erase ".\Debug\rng\fishman18.obj"
	-@erase ".\Debug\rng\fishman20.obj"
	-@erase ".\Debug\rng\fishman2x.obj"
	-@erase ".\Debug\rng\gfsr4.obj"
	-@erase ".\Debug\rng\knuthran.obj"
	-@erase ".\Debug\rng\knuthran2.obj"
	-@erase ".\Debug\rng\lecuyer21.obj"
	-@erase ".\Debug\rng\minstd.obj"
	-@erase ".\Debug\rng\mrg.obj"
	-@erase ".\Debug\rng\mt.obj"
	-@erase ".\Debug\rng\r250.obj"
	-@erase ".\Debug\rng\ran0.obj"
	-@erase ".\Debug\rng\ran1.obj"
	-@erase ".\Debug\rng\ran2.obj"
	-@erase ".\Debug\rng\ran3.obj"
	-@erase ".\Debug\rng\rand.obj"
	-@erase ".\Debug\rng\rand48.obj"
	-@erase ".\Debug\rng\random.obj"
	-@erase ".\Debug\rng\randu.obj"
	-@erase ".\Debug\rng\ranf.obj"
	-@erase ".\Debug\rng\ranlux.obj"
	-@erase ".\Debug\rng\ranlxd.obj"
	-@erase ".\Debug\rng\ranlxs.obj"
	-@erase ".\Debug\rng\ranmar.obj"
	-@erase ".\Debug\rng\rng.obj"
	-@erase ".\Debug\rng\slatec.obj"
	-@erase ".\Debug\rng\taus.obj"
	-@erase ".\Debug\rng\taus113.obj"
	-@erase ".\Debug\rng\transputer.obj"
	-@erase ".\Debug\rng\tt.obj"
	-@erase ".\Debug\rng\types.obj"
	-@erase ".\Debug\rng\uni.obj"
	-@erase ".\Debug\rng\uni32.obj"
	-@erase ".\Debug\rng\vax.obj"
	-@erase ".\Debug\rng\waterman14.obj"
	-@erase ".\Debug\rng\zuf.obj"
	-@erase ".\Debug\specfunc\airy.obj"
	-@erase ".\Debug\specfunc\airy_der.obj"
	-@erase ".\Debug\specfunc\airy_zero.obj"
	-@erase ".\Debug\specfunc\atanint.obj"
	-@erase ".\Debug\specfunc\bessel.obj"
	-@erase ".\Debug\specfunc\bessel_amp_phase.obj"
	-@erase ".\Debug\specfunc\bessel_i.obj"
	-@erase ".\Debug\specfunc\bessel_I0.obj"
	-@erase ".\Debug\specfunc\bessel_I1.obj"
	-@erase ".\Debug\specfunc\bessel_In.obj"
	-@erase ".\Debug\specfunc\bessel_Inu.obj"
	-@erase ".\Debug\specfunc\bessel_j.obj"
	-@erase ".\Debug\specfunc\bessel_J0.obj"
	-@erase ".\Debug\specfunc\bessel_J1.obj"
	-@erase ".\Debug\specfunc\bessel_Jn.obj"
	-@erase ".\Debug\specfunc\bessel_Jnu.obj"
	-@erase ".\Debug\specfunc\bessel_k.obj"
	-@erase ".\Debug\specfunc\bessel_K0.obj"
	-@erase ".\Debug\specfunc\bessel_K1.obj"
	-@erase ".\Debug\specfunc\bessel_Kn.obj"
	-@erase ".\Debug\specfunc\bessel_Knu.obj"
	-@erase ".\Debug\specfunc\bessel_olver.obj"
	-@erase ".\Debug\specfunc\bessel_sequence.obj"
	-@erase ".\Debug\specfunc\bessel_temme.obj"
	-@erase ".\Debug\specfunc\bessel_y.obj"
	-@erase ".\Debug\specfunc\bessel_Y0.obj"
	-@erase ".\Debug\specfunc\bessel_Y1.obj"
	-@erase ".\Debug\specfunc\bessel_Yn.obj"
	-@erase ".\Debug\specfunc\bessel_Ynu.obj"
	-@erase ".\Debug\specfunc\bessel_zero.obj"
	-@erase ".\Debug\specfunc\beta.obj"
	-@erase ".\Debug\specfunc\beta_inc.obj"
	-@erase ".\Debug\specfunc\clausen.obj"
	-@erase ".\Debug\specfunc\coulomb.obj"
	-@erase ".\Debug\specfunc\coulomb_bound.obj"
	-@erase ".\Debug\specfunc\coupling.obj"
	-@erase ".\Debug\specfunc\dawson.obj"
	-@erase ".\Debug\specfunc\debye.obj"
	-@erase ".\Debug\specfunc\dilog.obj"
	-@erase ".\Debug\specfunc\elementary.obj"
	-@erase ".\Debug\specfunc\ellint.obj"
	-@erase ".\Debug\specfunc\elljac.obj"
	-@erase ".\Debug\specfunc\erfc.obj"
	-@erase ".\Debug\specfunc\exp.obj"
	-@erase ".\Debug\specfunc\expint.obj"
	-@erase ".\Debug\specfunc\expint3.obj"
	-@erase ".\Debug\specfunc\fermi_dirac.obj"
	-@erase ".\Debug\specfunc\gamma.obj"
	-@erase ".\Debug\specfunc\gamma_inc.obj"
	-@erase ".\Debug\specfunc\gegenbauer.obj"
	-@erase ".\Debug\specfunc\hyperg.obj"
	-@erase ".\Debug\specfunc\hyperg_0F1.obj"
	-@erase ".\Debug\specfunc\hyperg_1F1.obj"
	-@erase ".\Debug\specfunc\hyperg_2F0.obj"
	-@erase ".\Debug\specfunc\hyperg_2F1.obj"
	-@erase ".\Debug\specfunc\hyperg_U.obj"
	-@erase ".\Debug\specfunc\laguerre.obj"
	-@erase ".\Debug\specfunc\lambert.obj"
	-@erase ".\Debug\specfunc\legendre_con.obj"
	-@erase ".\Debug\specfunc\legendre_H3d.obj"
	-@erase ".\Debug\specfunc\legendre_poly.obj"
	-@erase ".\Debug\specfunc\legendre_Qn.obj"
	-@erase ".\Debug\specfunc\log.obj"
	-@erase ".\Debug\specfunc\poch.obj"
	-@erase ".\Debug\specfunc\pow_int.obj"
	-@erase ".\Debug\specfunc\psi.obj"
	-@erase ".\Debug\specfunc\result.obj"
	-@erase ".\Debug\specfunc\shint.obj"
	-@erase ".\Debug\specfunc\sinint.obj"
	-@erase ".\Debug\specfunc\synchrotron.obj"
	-@erase ".\Debug\specfunc\transport.obj"
	-@erase ".\Debug\specfunc\trig.obj"
	-@erase ".\Debug\specfunc\zeta.obj"
	-@erase ".\Debug\sys\coerce.obj"
	-@erase ".\Debug\sys\expm1.obj"
	-@erase ".\Debug\sys\fcmp.obj"
	-@erase ".\Debug\sys\fdiv.obj"
	-@erase ".\Debug\sys\hypot.obj"
	-@erase ".\Debug\sys\infnan.obj"
	-@erase ".\Debug\sys\invhyp.obj"
	-@erase ".\Debug\sys\ldfrexp.obj"
	-@erase ".\Debug\sys\log1p.obj"
	-@erase ".\Debug\sys\minmax.obj"
	-@erase ".\Debug\sys\pow_int.obj"
	-@erase ".\Debug\sys\prec.obj"
	-@erase ".\Debug\vector\copy.obj"
	-@erase ".\Debug\vector\file.obj"
	-@erase ".\Debug\vector\init.obj"
	-@erase ".\Debug\vector\minmax.obj"
	-@erase ".\Debug\vector\oper.obj"
	-@erase ".\Debug\vector\prop.obj"
	-@erase ".\Debug\vector\reim.obj"
	-@erase ".\Debug\vector\subvector.obj"
	-@erase ".\Debug\vector\swap.obj"
	-@erase ".\Debug\vector\vector.obj"
	-@erase ".\Debug\vector\view.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\gsl18_vc6.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\gsl18_vc6D.pdb" /debug /machine:I386 /out:"$(OUTDIR)\gsl18_vc6D.dll" /implib:"$(OUTDIR)\gsl18_vc6D.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\gsl18_vc6.obj" \
	".\Debug\multifit\convergence.obj" \
	".\Debug\multifit\covar.obj" \
	".\Debug\multifit\fdfsolver.obj" \
	".\Debug\multifit\fsolver.obj" \
	".\Debug\multifit\gradient.obj" \
	".\Debug\multifit\lmder.obj" \
	".\Debug\multifit\multilinear.obj" \
	".\Debug\multifit\work.obj" \
	".\Debug\err\error.obj" \
	".\Debug\err\message.obj" \
	".\Debug\err\stream.obj" \
	".\Debug\err\strerror.obj" \
	".\Debug\vector\copy.obj" \
	".\Debug\vector\file.obj" \
	".\Debug\vector\init.obj" \
	".\Debug\vector\minmax.obj" \
	".\Debug\vector\oper.obj" \
	".\Debug\vector\prop.obj" \
	".\Debug\vector\reim.obj" \
	".\Debug\vector\subvector.obj" \
	".\Debug\vector\swap.obj" \
	".\Debug\vector\vector.obj" \
	".\Debug\vector\view.obj" \
	".\Debug\permutation\canonical.obj" \
	".\Debug\permutation\file.obj" \
	".\Debug\permutation\init.obj" \
	".\Debug\permutation\permutation.obj" \
	".\Debug\permutation\permute.obj" \
	".\Debug\matrix\copy.obj" \
	".\Debug\matrix\file.obj" \
	".\Debug\matrix\getset.obj" \
	".\Debug\matrix\init.obj" \
	".\Debug\matrix\matrix.obj" \
	".\Debug\matrix\minmax.obj" \
	".\Debug\matrix\oper.obj" \
	".\Debug\matrix\prop.obj" \
	".\Debug\matrix\rowcol.obj" \
	".\Debug\matrix\submatrix.obj" \
	".\Debug\matrix\swap.obj" \
	".\Debug\matrix\view.obj" \
	".\Debug\linalg\balance.obj" \
	".\Debug\linalg\bidiag.obj" \
	".\Debug\linalg\cholesky.obj" \
	".\Debug\linalg\exponential.obj" \
	".\Debug\linalg\hermtd.obj" \
	".\Debug\linalg\hh.obj" \
	".\Debug\linalg\householder.obj" \
	".\Debug\linalg\householdercomplex.obj" \
	".\Debug\linalg\lq.obj" \
	".\Debug\linalg\lu.obj" \
	".\Debug\linalg\luc.obj" \
	".\Debug\linalg\multiply.obj" \
	".\Debug\linalg\ptlq.obj" \
	".\Debug\linalg\qr.obj" \
	".\Debug\linalg\qrpt.obj" \
	".\Debug\linalg\svd.obj" \
	".\Debug\linalg\symmtd.obj" \
	".\Debug\linalg\tridiag.obj" \
	".\Debug\block\block.obj" \
	".\Debug\block\file.obj" \
	".\Debug\block\init.obj" \
	".\Debug\blas\blas.obj" \
	".\Debug\cblas\caxpy.obj" \
	".\Debug\cblas\ccopy.obj" \
	".\Debug\cblas\cdotc_sub.obj" \
	".\Debug\cblas\cdotu_sub.obj" \
	".\Debug\cblas\cgbmv.obj" \
	".\Debug\cblas\cgemm.obj" \
	".\Debug\cblas\cgemv.obj" \
	".\Debug\cblas\cgerc.obj" \
	".\Debug\cblas\cgeru.obj" \
	".\Debug\cblas\chbmv.obj" \
	".\Debug\cblas\chemm.obj" \
	".\Debug\cblas\chemv.obj" \
	".\Debug\cblas\cher.obj" \
	".\Debug\cblas\cher2.obj" \
	".\Debug\cblas\cher2k.obj" \
	".\Debug\cblas\cherk.obj" \
	".\Debug\cblas\chpmv.obj" \
	".\Debug\cblas\chpr.obj" \
	".\Debug\cblas\chpr2.obj" \
	".\Debug\cblas\cscal.obj" \
	".\Debug\cblas\csscal.obj" \
	".\Debug\cblas\cswap.obj" \
	".\Debug\cblas\csymm.obj" \
	".\Debug\cblas\csyr2k.obj" \
	".\Debug\cblas\csyrk.obj" \
	".\Debug\cblas\ctbmv.obj" \
	".\Debug\cblas\ctbsv.obj" \
	".\Debug\cblas\ctpmv.obj" \
	".\Debug\cblas\ctpsv.obj" \
	".\Debug\cblas\ctrmm.obj" \
	".\Debug\cblas\ctrmv.obj" \
	".\Debug\cblas\ctrsm.obj" \
	".\Debug\cblas\ctrsv.obj" \
	".\Debug\cblas\dasum.obj" \
	".\Debug\cblas\daxpy.obj" \
	".\Debug\cblas\dcopy.obj" \
	".\Debug\cblas\ddot.obj" \
	".\Debug\cblas\dgbmv.obj" \
	".\Debug\cblas\dgemm.obj" \
	".\Debug\cblas\dgemv.obj" \
	".\Debug\cblas\dger.obj" \
	".\Debug\cblas\dnrm2.obj" \
	".\Debug\cblas\drot.obj" \
	".\Debug\cblas\drotg.obj" \
	".\Debug\cblas\drotm.obj" \
	".\Debug\cblas\drotmg.obj" \
	".\Debug\cblas\dsbmv.obj" \
	".\Debug\cblas\dscal.obj" \
	".\Debug\cblas\dsdot.obj" \
	".\Debug\cblas\dspmv.obj" \
	".\Debug\cblas\dspr.obj" \
	".\Debug\cblas\dspr2.obj" \
	".\Debug\cblas\dswap.obj" \
	".\Debug\cblas\dsymm.obj" \
	".\Debug\cblas\dsymv.obj" \
	".\Debug\cblas\dsyr.obj" \
	".\Debug\cblas\dsyr2.obj" \
	".\Debug\cblas\dsyr2k.obj" \
	".\Debug\cblas\dsyrk.obj" \
	".\Debug\cblas\dtbmv.obj" \
	".\Debug\cblas\dtbsv.obj" \
	".\Debug\cblas\dtpmv.obj" \
	".\Debug\cblas\dtpsv.obj" \
	".\Debug\cblas\dtrmm.obj" \
	".\Debug\cblas\dtrmv.obj" \
	".\Debug\cblas\dtrsm.obj" \
	".\Debug\cblas\dtrsv.obj" \
	".\Debug\cblas\dzasum.obj" \
	".\Debug\cblas\dznrm2.obj" \
	".\Debug\cblas\hypot.obj" \
	".\Debug\cblas\icamax.obj" \
	".\Debug\cblas\idamax.obj" \
	".\Debug\cblas\isamax.obj" \
	".\Debug\cblas\izamax.obj" \
	".\Debug\cblas\sasum.obj" \
	".\Debug\cblas\saxpy.obj" \
	".\Debug\cblas\scasum.obj" \
	".\Debug\cblas\scnrm2.obj" \
	".\Debug\cblas\scopy.obj" \
	".\Debug\cblas\sdot.obj" \
	".\Debug\cblas\sdsdot.obj" \
	".\Debug\cblas\sgbmv.obj" \
	".\Debug\cblas\sgemm.obj" \
	".\Debug\cblas\sgemv.obj" \
	".\Debug\cblas\sger.obj" \
	".\Debug\cblas\snrm2.obj" \
	".\Debug\cblas\srot.obj" \
	".\Debug\cblas\srotg.obj" \
	".\Debug\cblas\srotm.obj" \
	".\Debug\cblas\srotmg.obj" \
	".\Debug\cblas\ssbmv.obj" \
	".\Debug\cblas\sscal.obj" \
	".\Debug\cblas\sspmv.obj" \
	".\Debug\cblas\sspr.obj" \
	".\Debug\cblas\sspr2.obj" \
	".\Debug\cblas\sswap.obj" \
	".\Debug\cblas\ssymm.obj" \
	".\Debug\cblas\ssymv.obj" \
	".\Debug\cblas\ssyr.obj" \
	".\Debug\cblas\ssyr2.obj" \
	".\Debug\cblas\ssyr2k.obj" \
	".\Debug\cblas\ssyrk.obj" \
	".\Debug\cblas\stbmv.obj" \
	".\Debug\cblas\stbsv.obj" \
	".\Debug\cblas\stpmv.obj" \
	".\Debug\cblas\stpsv.obj" \
	".\Debug\cblas\strmm.obj" \
	".\Debug\cblas\strmv.obj" \
	".\Debug\cblas\strsm.obj" \
	".\Debug\cblas\strsv.obj" \
	".\Debug\cblas\xerbla.obj" \
	".\Debug\cblas\zaxpy.obj" \
	".\Debug\cblas\zcopy.obj" \
	".\Debug\cblas\zdotc_sub.obj" \
	".\Debug\cblas\zdotu_sub.obj" \
	".\Debug\cblas\zdscal.obj" \
	".\Debug\cblas\zgbmv.obj" \
	".\Debug\cblas\zgemm.obj" \
	".\Debug\cblas\zgemv.obj" \
	".\Debug\cblas\zgerc.obj" \
	".\Debug\cblas\zgeru.obj" \
	".\Debug\cblas\zhbmv.obj" \
	".\Debug\cblas\zhemm.obj" \
	".\Debug\cblas\zhemv.obj" \
	".\Debug\cblas\zher.obj" \
	".\Debug\cblas\zher2.obj" \
	".\Debug\cblas\zher2k.obj" \
	".\Debug\cblas\zherk.obj" \
	".\Debug\cblas\zhpmv.obj" \
	".\Debug\cblas\zhpr.obj" \
	".\Debug\cblas\zhpr2.obj" \
	".\Debug\cblas\zscal.obj" \
	".\Debug\cblas\zswap.obj" \
	".\Debug\cblas\zsymm.obj" \
	".\Debug\cblas\zsyr2k.obj" \
	".\Debug\cblas\zsyrk.obj" \
	".\Debug\cblas\ztbmv.obj" \
	".\Debug\cblas\ztbsv.obj" \
	".\Debug\cblas\ztpmv.obj" \
	".\Debug\cblas\ztpsv.obj" \
	".\Debug\cblas\ztrmm.obj" \
	".\Debug\cblas\ztrmv.obj" \
	".\Debug\cblas\ztrsm.obj" \
	".\Debug\cblas\ztrsv.obj" \
	".\Debug\sys\coerce.obj" \
	".\Debug\sys\expm1.obj" \
	".\Debug\sys\fcmp.obj" \
	".\Debug\sys\fdiv.obj" \
	".\Debug\sys\hypot.obj" \
	".\Debug\sys\infnan.obj" \
	".\Debug\sys\invhyp.obj" \
	".\Debug\sys\ldfrexp.obj" \
	".\Debug\sys\log1p.obj" \
	".\Debug\sys\minmax.obj" \
	".\Debug\sys\pow_int.obj" \
	".\Debug\sys\prec.obj" \
	".\Debug\complex\math.obj" \
	".\Debug\ode-initval\bsimp.obj" \
	".\Debug\ode-initval\control.obj" \
	".\Debug\ode-initval\cscal.obj" \
	".\Debug\ode-initval\cstd.obj" \
	".\Debug\ode-initval\evolve.obj" \
	".\Debug\ode-initval\gear1.obj" \
	".\Debug\ode-initval\gear2.obj" \
	".\Debug\ode-initval\rk2.obj" \
	".\Debug\ode-initval\rk2imp.obj" \
	".\Debug\ode-initval\rk2simp.obj" \
	".\Debug\ode-initval\rk4.obj" \
	".\Debug\ode-initval\rk4imp.obj" \
	".\Debug\ode-initval\rk8pd.obj" \
	".\Debug\ode-initval\rkck.obj" \
	".\Debug\ode-initval\rkf45.obj" \
	".\Debug\ode-initval\step.obj" \
	".\Debug\randist\bernoulli.obj" \
	".\Debug\randist\beta.obj" \
	".\Debug\randist\bigauss.obj" \
	".\Debug\randist\binomial.obj" \
	".\Debug\randist\binomial_tpe.obj" \
	".\Debug\randist\cauchy.obj" \
	".\Debug\randist\chisq.obj" \
	".\Debug\randist\dirichlet.obj" \
	".\Debug\randist\discrete.obj" \
	".\Debug\randist\erlang.obj" \
	".\Debug\randist\exponential.obj" \
	".\Debug\randist\exppow.obj" \
	".\Debug\randist\fdist.obj" \
	".\Debug\randist\flat.obj" \
	".\Debug\randist\gamma.obj" \
	".\Debug\randist\gauss.obj" \
	".\Debug\randist\gausstail.obj" \
	".\Debug\randist\gausszig.obj" \
	".\Debug\randist\geometric.obj" \
	".\Debug\randist\gumbel.obj" \
	".\Debug\randist\hyperg.obj" \
	".\Debug\randist\landau.obj" \
	".\Debug\randist\laplace.obj" \
	".\Debug\randist\levy.obj" \
	".\Debug\randist\logarithmic.obj" \
	".\Debug\randist\logistic.obj" \
	".\Debug\randist\lognormal.obj" \
	".\Debug\randist\multinomial.obj" \
	".\Debug\randist\nbinomial.obj" \
	".\Debug\randist\pareto.obj" \
	".\Debug\randist\pascal.obj" \
	".\Debug\randist\poisson.obj" \
	".\Debug\randist\rayleigh.obj" \
	".\Debug\randist\shuffle.obj" \
	".\Debug\randist\sphere.obj" \
	".\Debug\randist\tdist.obj" \
	".\Debug\randist\weibull.obj" \
	".\Debug\specfunc\airy.obj" \
	".\Debug\specfunc\airy_der.obj" \
	".\Debug\specfunc\airy_zero.obj" \
	".\Debug\specfunc\atanint.obj" \
	".\Debug\specfunc\bessel.obj" \
	".\Debug\specfunc\bessel_amp_phase.obj" \
	".\Debug\specfunc\bessel_i.obj" \
	".\Debug\specfunc\bessel_I0.obj" \
	".\Debug\specfunc\bessel_I1.obj" \
	".\Debug\specfunc\bessel_In.obj" \
	".\Debug\specfunc\bessel_Inu.obj" \
	".\Debug\specfunc\bessel_j.obj" \
	".\Debug\specfunc\bessel_J0.obj" \
	".\Debug\specfunc\bessel_J1.obj" \
	".\Debug\specfunc\bessel_Jn.obj" \
	".\Debug\specfunc\bessel_Jnu.obj" \
	".\Debug\specfunc\bessel_k.obj" \
	".\Debug\specfunc\bessel_K0.obj" \
	".\Debug\specfunc\bessel_K1.obj" \
	".\Debug\specfunc\bessel_Kn.obj" \
	".\Debug\specfunc\bessel_Knu.obj" \
	".\Debug\specfunc\bessel_olver.obj" \
	".\Debug\specfunc\bessel_sequence.obj" \
	".\Debug\specfunc\bessel_temme.obj" \
	".\Debug\specfunc\bessel_y.obj" \
	".\Debug\specfunc\bessel_Y0.obj" \
	".\Debug\specfunc\bessel_Y1.obj" \
	".\Debug\specfunc\bessel_Yn.obj" \
	".\Debug\specfunc\bessel_Ynu.obj" \
	".\Debug\specfunc\bessel_zero.obj" \
	".\Debug\specfunc\beta.obj" \
	".\Debug\specfunc\beta_inc.obj" \
	".\Debug\specfunc\clausen.obj" \
	".\Debug\specfunc\coulomb.obj" \
	".\Debug\specfunc\coulomb_bound.obj" \
	".\Debug\specfunc\coupling.obj" \
	".\Debug\specfunc\dawson.obj" \
	".\Debug\specfunc\debye.obj" \
	".\Debug\specfunc\dilog.obj" \
	".\Debug\specfunc\elementary.obj" \
	".\Debug\specfunc\ellint.obj" \
	".\Debug\specfunc\elljac.obj" \
	".\Debug\specfunc\erfc.obj" \
	".\Debug\specfunc\exp.obj" \
	".\Debug\specfunc\expint.obj" \
	".\Debug\specfunc\expint3.obj" \
	".\Debug\specfunc\fermi_dirac.obj" \
	".\Debug\specfunc\gamma.obj" \
	".\Debug\specfunc\gamma_inc.obj" \
	".\Debug\specfunc\gegenbauer.obj" \
	".\Debug\specfunc\hyperg.obj" \
	".\Debug\specfunc\hyperg_0F1.obj" \
	".\Debug\specfunc\hyperg_1F1.obj" \
	".\Debug\specfunc\hyperg_2F0.obj" \
	".\Debug\specfunc\hyperg_2F1.obj" \
	".\Debug\specfunc\hyperg_U.obj" \
	".\Debug\specfunc\laguerre.obj" \
	".\Debug\specfunc\lambert.obj" \
	".\Debug\specfunc\legendre_con.obj" \
	".\Debug\specfunc\legendre_H3d.obj" \
	".\Debug\specfunc\legendre_poly.obj" \
	".\Debug\specfunc\legendre_Qn.obj" \
	".\Debug\specfunc\log.obj" \
	".\Debug\specfunc\poch.obj" \
	".\Debug\specfunc\pow_int.obj" \
	".\Debug\specfunc\psi.obj" \
	".\Debug\specfunc\result.obj" \
	".\Debug\specfunc\shint.obj" \
	".\Debug\specfunc\sinint.obj" \
	".\Debug\specfunc\synchrotron.obj" \
	".\Debug\specfunc\transport.obj" \
	".\Debug\specfunc\trig.obj" \
	".\Debug\specfunc\zeta.obj" \
	".\Debug\rng\borosh13.obj" \
	".\Debug\rng\cmrg.obj" \
	".\Debug\rng\coveyou.obj" \
	".\Debug\rng\default.obj" \
	".\Debug\rng\file.obj" \
	".\Debug\rng\fishman18.obj" \
	".\Debug\rng\fishman20.obj" \
	".\Debug\rng\fishman2x.obj" \
	".\Debug\rng\gfsr4.obj" \
	".\Debug\rng\knuthran.obj" \
	".\Debug\rng\knuthran2.obj" \
	".\Debug\rng\lecuyer21.obj" \
	".\Debug\rng\minstd.obj" \
	".\Debug\rng\mrg.obj" \
	".\Debug\rng\mt.obj" \
	".\Debug\rng\r250.obj" \
	".\Debug\rng\ran0.obj" \
	".\Debug\rng\ran1.obj" \
	".\Debug\rng\ran2.obj" \
	".\Debug\rng\ran3.obj" \
	".\Debug\rng\rand.obj" \
	".\Debug\rng\rand48.obj" \
	".\Debug\rng\random.obj" \
	".\Debug\rng\randu.obj" \
	".\Debug\rng\ranf.obj" \
	".\Debug\rng\ranlux.obj" \
	".\Debug\rng\ranlxd.obj" \
	".\Debug\rng\ranlxs.obj" \
	".\Debug\rng\ranmar.obj" \
	".\Debug\rng\rng.obj" \
	".\Debug\rng\slatec.obj" \
	".\Debug\rng\taus.obj" \
	".\Debug\rng\taus113.obj" \
	".\Debug\rng\transputer.obj" \
	".\Debug\rng\tt.obj" \
	".\Debug\rng\types.obj" \
	".\Debug\rng\uni.obj" \
	".\Debug\rng\uni32.obj" \
	".\Debug\rng\vax.obj" \
	".\Debug\rng\waterman14.obj" \
	".\Debug\rng\zuf.obj" \
	"$(INTDIR)\fft.obj"

"$(OUTDIR)\gsl18_vc6D.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\gsl18_vc6D.dll"
   copy Debug\*.dll ..\..\..\zlab
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("gsl18_vc6.dep")
!INCLUDE "gsl18_vc6.dep"
!ELSE 
!MESSAGE Warning: cannot find "gsl18_vc6.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "gsl18_vc6 - Win32 Release" || "$(CFG)" == "gsl18_vc6 - Win32 Debug"
SOURCE=.\gsl18_vc6.cpp

"$(INTDIR)\gsl18_vc6.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=..\multifit\convergence.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\multifit/" /Fd"Release\multifit/" /FD /c 

".\Release\multifit\convergence.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\multifit/" /Fd"Debug\multifit/" /FD /GZ /c 

".\Debug\multifit\convergence.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\multifit\covar.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\multifit/" /Fd"Release\multifit/" /FD /c 

".\Release\multifit\covar.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\multifit/" /Fd"Debug\multifit/" /FD /GZ /c 

".\Debug\multifit\covar.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\multifit\fdfsolver.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\multifit/" /Fd"Release\multifit/" /FD /c 

".\Release\multifit\fdfsolver.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\multifit/" /Fd"Debug\multifit/" /FD /GZ /c 

".\Debug\multifit\fdfsolver.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\multifit\fsolver.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\multifit/" /Fd"Release\multifit/" /FD /c 

".\Release\multifit\fsolver.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\multifit/" /Fd"Debug\multifit/" /FD /GZ /c 

".\Debug\multifit\fsolver.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\multifit\gradient.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\multifit/" /Fd"Release\multifit/" /FD /c 

".\Release\multifit\gradient.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\multifit/" /Fd"Debug\multifit/" /FD /GZ /c 

".\Debug\multifit\gradient.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\multifit\lmder.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\multifit/" /Fd"Release\multifit/" /FD /c 

".\Release\multifit\lmder.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\multifit/" /Fd"Debug\multifit/" /FD /GZ /c 

".\Debug\multifit\lmder.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\multifit\lmiterate.c
SOURCE=..\multifit\lmpar.c
SOURCE=..\multifit\lmset.c
SOURCE=..\multifit\lmutil.c
SOURCE=..\multifit\multilinear.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\multifit/" /Fd"Release\multifit/" /FD /c 

".\Release\multifit\multilinear.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\multifit/" /Fd"Debug\multifit/" /FD /GZ /c 

".\Debug\multifit\multilinear.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\multifit\qrsolv.c
SOURCE=..\multifit\work.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\multifit/" /Fd"Release\multifit/" /FD /c 

".\Release\multifit\work.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\multifit/" /Fd"Debug\multifit/" /FD /GZ /c 

".\Debug\multifit\work.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\err\error.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\err/" /Fd"Release\err/" /FD /c 

".\Release\err\error.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\err/" /Fd"Debug\err/" /FD /GZ /c 

".\Debug\err\error.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\err\message.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\err/" /Fd"Release\err/" /FD /c 

".\Release\err\message.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\err/" /Fd"Debug\err/" /FD /GZ /c 

".\Debug\err\message.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\err\stream.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\err/" /Fd"Release\err/" /FD /c 

".\Release\err\stream.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\err/" /Fd"Debug\err/" /FD /GZ /c 

".\Debug\err\stream.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\err\strerror.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\err/" /Fd"Release\err/" /FD /c 

".\Release\err\strerror.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\err/" /Fd"Debug\err/" /FD /GZ /c 

".\Debug\err\strerror.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\err\test.c
SOURCE=..\vector\copy.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\vector/" /Fd"Release\vector/" /FD /c 

".\Release\vector\copy.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\vector/" /Fd"Debug\vector/" /FD /GZ /c 

".\Debug\vector\copy.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\vector\copy_source.c
SOURCE=..\vector\file.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\vector/" /Fd"Release\vector/" /FD /c 

".\Release\vector\file.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\vector/" /Fd"Debug\vector/" /FD /GZ /c 

".\Debug\vector\file.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\vector\file_source.c
SOURCE=..\vector\init.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\vector/" /Fd"Release\vector/" /FD /c 

".\Release\vector\init.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\vector/" /Fd"Debug\vector/" /FD /GZ /c 

".\Debug\vector\init.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\vector\init_source.c
SOURCE=..\vector\minmax.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\vector/" /Fd"Release\vector/" /FD /c 

".\Release\vector\minmax.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\vector/" /Fd"Debug\vector/" /FD /GZ /c 

".\Debug\vector\minmax.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\vector\minmax_source.c
SOURCE=..\vector\oper.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\vector/" /Fd"Release\vector/" /FD /c 

".\Release\vector\oper.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\vector/" /Fd"Debug\vector/" /FD /GZ /c 

".\Debug\vector\oper.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\vector\oper_source.c
SOURCE=..\vector\prop.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\vector/" /Fd"Release\vector/" /FD /c 

".\Release\vector\prop.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\vector/" /Fd"Debug\vector/" /FD /GZ /c 

".\Debug\vector\prop.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\vector\prop_source.c
SOURCE=..\vector\reim.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\vector/" /Fd"Release\vector/" /FD /c 

".\Release\vector\reim.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\vector/" /Fd"Debug\vector/" /FD /GZ /c 

".\Debug\vector\reim.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\vector\reim_source.c
SOURCE=..\vector\subvector.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\vector/" /Fd"Release\vector/" /FD /c 

".\Release\vector\subvector.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\vector/" /Fd"Debug\vector/" /FD /GZ /c 

".\Debug\vector\subvector.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\vector\subvector_source.c
SOURCE=..\vector\swap.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\vector/" /Fd"Release\vector/" /FD /c 

".\Release\vector\swap.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\vector/" /Fd"Debug\vector/" /FD /GZ /c 

".\Debug\vector\swap.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\vector\swap_source.c
SOURCE=..\vector\test.c
SOURCE=..\vector\test_complex_source.c
SOURCE=..\vector\test_source.c
SOURCE=..\vector\test_static.c
SOURCE=..\vector\vector.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\vector/" /Fd"Release\vector/" /FD /c 

".\Release\vector\vector.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\vector/" /Fd"Debug\vector/" /FD /GZ /c 

".\Debug\vector\vector.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\vector\vector_source.c
SOURCE=..\vector\view.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\vector/" /Fd"Release\vector/" /FD /c 

".\Release\vector\view.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\vector/" /Fd"Debug\vector/" /FD /GZ /c 

".\Debug\vector\view.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\vector\view_source.c
SOURCE=..\permutation\canonical.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\permutation/" /Fd"Release\permutation/" /FD /c 

".\Release\permutation\canonical.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\permutation/" /Fd"Debug\permutation/" /FD /GZ /c 

".\Debug\permutation\canonical.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\permutation\file.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\permutation/" /Fd"Release\permutation/" /FD /c 

".\Release\permutation\file.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\permutation/" /Fd"Debug\permutation/" /FD /GZ /c 

".\Debug\permutation\file.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\permutation\init.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\permutation/" /Fd"Release\permutation/" /FD /c 

".\Release\permutation\init.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\permutation/" /Fd"Debug\permutation/" /FD /GZ /c 

".\Debug\permutation\init.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\permutation\permutation.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\permutation/" /Fd"Release\permutation/" /FD /c 

".\Release\permutation\permutation.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\permutation/" /Fd"Debug\permutation/" /FD /GZ /c 

".\Debug\permutation\permutation.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\permutation\permute.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\permutation/" /Fd"Release\permutation/" /FD /c 

".\Release\permutation\permute.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\permutation/" /Fd"Debug\permutation/" /FD /GZ /c 

".\Debug\permutation\permute.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\permutation\permute_source.c
SOURCE=..\permutation\test.c
SOURCE=..\matrix\copy.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\matrix/" /Fd"Release\matrix/" /FD /c 

".\Release\matrix\copy.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\matrix/" /Fd"Debug\matrix/" /FD /GZ /c 

".\Debug\matrix\copy.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\matrix\copy_source.c
SOURCE=..\matrix\file.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\matrix/" /Fd"Release\matrix/" /FD /c 

".\Release\matrix\file.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\matrix/" /Fd"Debug\matrix/" /FD /GZ /c 

".\Debug\matrix\file.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\matrix\file_source.c
SOURCE=..\matrix\getset.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\matrix/" /Fd"Release\matrix/" /FD /c 

".\Release\matrix\getset.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\matrix/" /Fd"Debug\matrix/" /FD /GZ /c 

".\Debug\matrix\getset.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\matrix\getset_source.c
SOURCE=..\matrix\init.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\matrix/" /Fd"Release\matrix/" /FD /c 

".\Release\matrix\init.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\matrix/" /Fd"Debug\matrix/" /FD /GZ /c 

".\Debug\matrix\init.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\matrix\init_source.c
SOURCE=..\matrix\matrix.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\matrix/" /Fd"Release\matrix/" /FD /c 

".\Release\matrix\matrix.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\matrix/" /Fd"Debug\matrix/" /FD /GZ /c 

".\Debug\matrix\matrix.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\matrix\matrix_source.c
SOURCE=..\matrix\minmax.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\matrix/" /Fd"Release\matrix/" /FD /c 

".\Release\matrix\minmax.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\matrix/" /Fd"Debug\matrix/" /FD /GZ /c 

".\Debug\matrix\minmax.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\matrix\minmax_source.c
SOURCE=..\matrix\oper.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\matrix/" /Fd"Release\matrix/" /FD /c 

".\Release\matrix\oper.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\matrix/" /Fd"Debug\matrix/" /FD /GZ /c 

".\Debug\matrix\oper.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\matrix\oper_complex_source.c
SOURCE=..\matrix\oper_source.c
SOURCE=..\matrix\prop.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\matrix/" /Fd"Release\matrix/" /FD /c 

".\Release\matrix\prop.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\matrix/" /Fd"Debug\matrix/" /FD /GZ /c 

".\Debug\matrix\prop.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\matrix\prop_source.c
SOURCE=..\matrix\rowcol.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\matrix/" /Fd"Release\matrix/" /FD /c 

".\Release\matrix\rowcol.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\matrix/" /Fd"Debug\matrix/" /FD /GZ /c 

".\Debug\matrix\rowcol.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\matrix\rowcol_source.c
SOURCE=..\matrix\submatrix.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\matrix/" /Fd"Release\matrix/" /FD /c 

".\Release\matrix\submatrix.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\matrix/" /Fd"Debug\matrix/" /FD /GZ /c 

".\Debug\matrix\submatrix.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\matrix\submatrix_source.c
SOURCE=..\matrix\swap.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\matrix/" /Fd"Release\matrix/" /FD /c 

".\Release\matrix\swap.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\matrix/" /Fd"Debug\matrix/" /FD /GZ /c 

".\Debug\matrix\swap.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\matrix\swap_source.c
SOURCE=..\matrix\test.c
SOURCE=..\matrix\test_complex_source.c
SOURCE=..\matrix\test_source.c
SOURCE=..\matrix\test_static.c
SOURCE=..\matrix\view.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\matrix/" /Fd"Release\matrix/" /FD /c 

".\Release\matrix\view.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\matrix/" /Fd"Debug\matrix/" /FD /GZ /c 

".\Debug\matrix\view.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\matrix\view_source.c
SOURCE=..\linalg\apply_givens.c
SOURCE=..\linalg\balance.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\linalg/" /Fd"Release\linalg/" /FD /c 

".\Release\linalg\balance.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\linalg/" /Fd"Debug\linalg/" /FD /GZ /c 

".\Debug\linalg\balance.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\linalg\bidiag.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\linalg/" /Fd"Release\linalg/" /FD /c 

".\Release\linalg\bidiag.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\linalg/" /Fd"Debug\linalg/" /FD /GZ /c 

".\Debug\linalg\bidiag.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\linalg\cholesky.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\linalg/" /Fd"Release\linalg/" /FD /c 

".\Release\linalg\cholesky.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\linalg/" /Fd"Debug\linalg/" /FD /GZ /c 

".\Debug\linalg\cholesky.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\linalg\exponential.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\linalg/" /Fd"Release\linalg/" /FD /c 

".\Release\linalg\exponential.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\linalg/" /Fd"Debug\linalg/" /FD /GZ /c 

".\Debug\linalg\exponential.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\linalg\givens.c
SOURCE=..\linalg\hermtd.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\linalg/" /Fd"Release\linalg/" /FD /c 

".\Release\linalg\hermtd.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\linalg/" /Fd"Debug\linalg/" /FD /GZ /c 

".\Debug\linalg\hermtd.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\linalg\hh.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\linalg/" /Fd"Release\linalg/" /FD /c 

".\Release\linalg\hh.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\linalg/" /Fd"Debug\linalg/" /FD /GZ /c 

".\Debug\linalg\hh.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\linalg\householder.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\linalg/" /Fd"Release\linalg/" /FD /c 

".\Release\linalg\householder.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\linalg/" /Fd"Debug\linalg/" /FD /GZ /c 

".\Debug\linalg\householder.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\linalg\householdercomplex.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\linalg/" /Fd"Release\linalg/" /FD /c 

".\Release\linalg\householdercomplex.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\linalg/" /Fd"Debug\linalg/" /FD /GZ /c 

".\Debug\linalg\householdercomplex.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\linalg\lq.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\linalg/" /Fd"Release\linalg/" /FD /c 

".\Release\linalg\lq.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\linalg/" /Fd"Debug\linalg/" /FD /GZ /c 

".\Debug\linalg\lq.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\linalg\lu.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\linalg/" /Fd"Release\linalg/" /FD /c 

".\Release\linalg\lu.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\linalg/" /Fd"Debug\linalg/" /FD /GZ /c 

".\Debug\linalg\lu.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\linalg\luc.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\linalg/" /Fd"Release\linalg/" /FD /c 

".\Release\linalg\luc.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\linalg/" /Fd"Debug\linalg/" /FD /GZ /c 

".\Debug\linalg\luc.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\linalg\multiply.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\linalg/" /Fd"Release\linalg/" /FD /c 

".\Release\linalg\multiply.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\linalg/" /Fd"Debug\linalg/" /FD /GZ /c 

".\Debug\linalg\multiply.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\linalg\ptlq.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\linalg/" /Fd"Release\linalg/" /FD /c 

".\Release\linalg\ptlq.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\linalg/" /Fd"Debug\linalg/" /FD /GZ /c 

".\Debug\linalg\ptlq.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\linalg\qr.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\linalg/" /Fd"Release\linalg/" /FD /c 

".\Release\linalg\qr.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\linalg/" /Fd"Debug\linalg/" /FD /GZ /c 

".\Debug\linalg\qr.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\linalg\qrpt.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\linalg/" /Fd"Release\linalg/" /FD /c 

".\Release\linalg\qrpt.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\linalg/" /Fd"Debug\linalg/" /FD /GZ /c 

".\Debug\linalg\qrpt.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\linalg\svd.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\linalg/" /Fd"Release\linalg/" /FD /c 

".\Release\linalg\svd.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\linalg/" /Fd"Debug\linalg/" /FD /GZ /c 

".\Debug\linalg\svd.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\linalg\svdstep.c
SOURCE=..\linalg\symmtd.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\linalg/" /Fd"Release\linalg/" /FD /c 

".\Release\linalg\symmtd.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\linalg/" /Fd"Debug\linalg/" /FD /GZ /c 

".\Debug\linalg\symmtd.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\linalg\test.c
SOURCE=..\linalg\tridiag.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\linalg/" /Fd"Release\linalg/" /FD /c 

".\Release\linalg\tridiag.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\linalg/" /Fd"Debug\linalg/" /FD /GZ /c 

".\Debug\linalg\tridiag.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\block\block.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\block/" /Fd"Release\block/" /FD /c 

".\Release\block\block.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\block/" /Fd"Debug\block/" /FD /GZ /c 

".\Debug\block\block.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\block\block_source.c
SOURCE=..\block\file.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\block/" /Fd"Release\block/" /FD /c 

".\Release\block\file.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\block/" /Fd"Debug\block/" /FD /GZ /c 

".\Debug\block\file.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\block\fprintf_source.c
SOURCE=..\block\fwrite_source.c
SOURCE=..\block\init.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\block/" /Fd"Release\block/" /FD /c 

".\Release\block\init.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\block/" /Fd"Debug\block/" /FD /GZ /c 

".\Debug\block\init.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\block\init_source.c
SOURCE=..\block\test.c
SOURCE=..\block\test_complex_io.c
SOURCE=..\block\test_complex_source.c
SOURCE=..\block\test_io.c
SOURCE=..\block\test_source.c
SOURCE=..\blas\blas.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\blas/" /Fd"Release\blas/" /FD /c 

".\Release\blas\blas.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\blas/" /Fd"Debug\blas/" /FD /GZ /c 

".\Debug\blas\blas.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\caxpy.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\caxpy.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\caxpy.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\ccopy.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\ccopy.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\ccopy.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\cdotc_sub.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\cdotc_sub.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\cdotc_sub.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\cdotu_sub.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\cdotu_sub.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\cdotu_sub.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\cgbmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\cgbmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\cgbmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\cgemm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\cgemm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\cgemm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\cgemv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\cgemv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\cgemv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\cgerc.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\cgerc.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\cgerc.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\cgeru.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\cgeru.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\cgeru.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\chbmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\chbmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\chbmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\chemm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\chemm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\chemm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\chemv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\chemv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\chemv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\cher.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\cher.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\cher.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\cher2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\cher2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\cher2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\cher2k.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\cher2k.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\cher2k.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\cherk.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\cherk.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\cherk.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\chpmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\chpmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\chpmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\chpr.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\chpr.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\chpr.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\chpr2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\chpr2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\chpr2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\cscal.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\cscal.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\cscal.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\csscal.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\csscal.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\csscal.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\cswap.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\cswap.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\cswap.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\csymm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\csymm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\csymm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\csyr2k.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\csyr2k.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\csyr2k.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\csyrk.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\csyrk.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\csyrk.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\ctbmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\ctbmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\ctbmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\ctbsv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\ctbsv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\ctbsv.obj" : $(SOURCE) "..\cblas\hypot.c"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\ctpmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\ctpmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\ctpmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\ctpsv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\ctpsv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\ctpsv.obj" : $(SOURCE) "..\cblas\hypot.c"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\ctrmm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\ctrmm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\ctrmm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\ctrmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\ctrmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\ctrmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\ctrsm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\ctrsm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\ctrsm.obj" : $(SOURCE) "..\cblas\hypot.c"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\ctrsv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\ctrsv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\ctrsv.obj" : $(SOURCE) "..\cblas\hypot.c"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\dasum.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\dasum.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\dasum.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\daxpy.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\daxpy.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\daxpy.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\dcopy.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\dcopy.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\dcopy.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\ddot.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\ddot.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\ddot.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\dgbmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\dgbmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\dgbmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\dgemm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\dgemm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\dgemm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\dgemv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\dgemv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\dgemv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\dger.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\dger.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\dger.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\dnrm2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\dnrm2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\dnrm2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\drot.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\drot.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\drot.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\drotg.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\drotg.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\drotg.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\drotm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\drotm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\drotm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\drotmg.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\drotmg.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\drotmg.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\dsbmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\dsbmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\dsbmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\dscal.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\dscal.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\dscal.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\dsdot.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\dsdot.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\dsdot.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\dspmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\dspmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\dspmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\dspr.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\dspr.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\dspr.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\dspr2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\dspr2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\dspr2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\dswap.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\dswap.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\dswap.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\dsymm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\dsymm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\dsymm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\dsymv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\dsymv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\dsymv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\dsyr.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\dsyr.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\dsyr.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\dsyr2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\dsyr2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\dsyr2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\dsyr2k.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\dsyr2k.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\dsyr2k.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\dsyrk.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\dsyrk.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\dsyrk.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\dtbmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\dtbmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\dtbmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\dtbsv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\dtbsv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\dtbsv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\dtpmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\dtpmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\dtpmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\dtpsv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\dtpsv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\dtpsv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\dtrmm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\dtrmm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\dtrmm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\dtrmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\dtrmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\dtrmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\dtrsm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\dtrsm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\dtrsm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\dtrsv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\dtrsv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\dtrsv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\dzasum.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\dzasum.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\dzasum.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\dznrm2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\dznrm2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\dznrm2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\hypot.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\hypot.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\hypot.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\icamax.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\icamax.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\icamax.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\idamax.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\idamax.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\idamax.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\isamax.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\isamax.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\isamax.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\izamax.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\izamax.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\izamax.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\sasum.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\sasum.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\sasum.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\saxpy.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\saxpy.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\saxpy.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\scasum.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\scasum.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\scasum.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\scnrm2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\scnrm2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\scnrm2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\scopy.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\scopy.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\scopy.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\sdot.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\sdot.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\sdot.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\sdsdot.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\sdsdot.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\sdsdot.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\sgbmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\sgbmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\sgbmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\sgemm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\sgemm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\sgemm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\sgemv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\sgemv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\sgemv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\sger.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\sger.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\sger.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\snrm2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\snrm2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\snrm2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\srot.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\srot.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\srot.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\srotg.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\srotg.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\srotg.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\srotm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\srotm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\srotm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\srotmg.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\srotmg.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\srotmg.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\ssbmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\ssbmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\ssbmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\sscal.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\sscal.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\sscal.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\sspmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\sspmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\sspmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\sspr.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\sspr.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\sspr.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\sspr2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\sspr2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\sspr2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\sswap.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\sswap.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\sswap.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\ssymm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\ssymm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\ssymm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\ssymv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\ssymv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\ssymv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\ssyr.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\ssyr.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\ssyr.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\ssyr2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\ssyr2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\ssyr2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\ssyr2k.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\ssyr2k.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\ssyr2k.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\ssyrk.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\ssyrk.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\ssyrk.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\stbmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\stbmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\stbmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\stbsv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\stbsv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\stbsv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\stpmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\stpmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\stpmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\stpsv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\stpsv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\stpsv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\strmm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\strmm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\strmm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\strmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\strmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\strmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\strsm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\strsm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\strsm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\strsv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\strsv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\strsv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\test.c
SOURCE=..\cblas\test_amax.c
SOURCE=..\cblas\test_asum.c
SOURCE=..\cblas\test_axpy.c
SOURCE=..\cblas\test_copy.c
SOURCE=..\cblas\test_dot.c
SOURCE=..\cblas\test_gbmv.c
SOURCE=..\cblas\test_gemm.c
SOURCE=..\cblas\test_gemv.c
SOURCE=..\cblas\test_ger.c
SOURCE=..\cblas\test_hbmv.c
SOURCE=..\cblas\test_hemm.c
SOURCE=..\cblas\test_hemv.c
SOURCE=..\cblas\test_her.c
SOURCE=..\cblas\test_her2.c
SOURCE=..\cblas\test_her2k.c
SOURCE=..\cblas\test_herk.c
SOURCE=..\cblas\test_hpmv.c
SOURCE=..\cblas\test_hpr.c
SOURCE=..\cblas\test_hpr2.c
SOURCE=..\cblas\test_nrm2.c
SOURCE=..\cblas\test_rot.c
SOURCE=..\cblas\test_rotg.c
SOURCE=..\cblas\test_rotm.c
SOURCE=..\cblas\test_rotmg.c
SOURCE=..\cblas\test_sbmv.c
SOURCE=..\cblas\test_scal.c
SOURCE=..\cblas\test_spmv.c
SOURCE=..\cblas\test_spr.c
SOURCE=..\cblas\test_spr2.c
SOURCE=..\cblas\test_swap.c
SOURCE=..\cblas\test_symm.c
SOURCE=..\cblas\test_symv.c
SOURCE=..\cblas\test_syr.c
SOURCE=..\cblas\test_syr2.c
SOURCE=..\cblas\test_syr2k.c
SOURCE=..\cblas\test_syrk.c
SOURCE=..\cblas\test_tbmv.c
SOURCE=..\cblas\test_tbsv.c
SOURCE=..\cblas\test_tpmv.c
SOURCE=..\cblas\test_tpsv.c
SOURCE=..\cblas\test_trmm.c
SOURCE=..\cblas\test_trmv.c
SOURCE=..\cblas\test_trsm.c
SOURCE=..\cblas\test_trsv.c
SOURCE=..\cblas\tests.c
SOURCE=..\cblas\xerbla.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\xerbla.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\xerbla.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\zaxpy.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\zaxpy.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\zaxpy.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\zcopy.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\zcopy.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\zcopy.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\zdotc_sub.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\zdotc_sub.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\zdotc_sub.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\zdotu_sub.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\zdotu_sub.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\zdotu_sub.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\zdscal.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\zdscal.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\zdscal.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\zgbmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\zgbmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\zgbmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\zgemm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\zgemm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\zgemm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\zgemv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\zgemv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\zgemv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\zgerc.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\zgerc.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\zgerc.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\zgeru.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\zgeru.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\zgeru.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\zhbmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\zhbmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\zhbmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\zhemm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\zhemm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\zhemm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\zhemv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\zhemv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\zhemv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\zher.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\zher.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\zher.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\zher2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\zher2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\zher2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\zher2k.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\zher2k.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\zher2k.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\zherk.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\zherk.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\zherk.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\zhpmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\zhpmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\zhpmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\zhpr.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\zhpr.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\zhpr.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\zhpr2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\zhpr2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\zhpr2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\zscal.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\zscal.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\zscal.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\zswap.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\zswap.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\zswap.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\zsymm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\zsymm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\zsymm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\zsyr2k.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\zsyr2k.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\zsyr2k.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\zsyrk.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\zsyrk.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\zsyrk.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\ztbmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\ztbmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\ztbmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\ztbsv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\ztbsv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\ztbsv.obj" : $(SOURCE) "..\cblas\hypot.c"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\ztpmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\ztpmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\ztpmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\ztpsv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\ztpsv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\ztpsv.obj" : $(SOURCE) "..\cblas\hypot.c"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\ztrmm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\ztrmm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\ztrmm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\ztrmv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\ztrmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\ztrmv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\ztrsm.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\ztrsm.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\ztrsm.obj" : $(SOURCE) "..\cblas\hypot.c"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\cblas\ztrsv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\cblas/" /Fd"Release\cblas/" /FD /c 

".\Release\cblas\ztrsv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\cblas/" /Fd"Debug\cblas/" /FD /GZ /c 

".\Debug\cblas\ztrsv.obj" : $(SOURCE) "..\cblas\hypot.c"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\sys\coerce.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\sys/" /Fd"Release\sys/" /FD /c 

".\Release\sys\coerce.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\sys/" /Fd"Debug\sys/" /FD /GZ /c 

".\Debug\sys\coerce.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\sys\expm1.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\sys/" /Fd"Release\sys/" /FD /c 

".\Release\sys\expm1.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\sys/" /Fd"Debug\sys/" /FD /GZ /c 

".\Debug\sys\expm1.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\sys\fcmp.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\sys/" /Fd"Release\sys/" /FD /c 

".\Release\sys\fcmp.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\sys/" /Fd"Debug\sys/" /FD /GZ /c 

".\Debug\sys\fcmp.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\sys\fdiv.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\sys/" /Fd"Release\sys/" /FD /c 

".\Release\sys\fdiv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\sys/" /Fd"Debug\sys/" /FD /GZ /c 

".\Debug\sys\fdiv.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\sys\hypot.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\sys/" /Fd"Release\sys/" /FD /c 

".\Release\sys\hypot.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\sys/" /Fd"Debug\sys/" /FD /GZ /c 

".\Debug\sys\hypot.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\sys\infnan.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\sys/" /Fd"Release\sys/" /FD /c 

".\Release\sys\infnan.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\sys/" /Fd"Debug\sys/" /FD /GZ /c 

".\Debug\sys\infnan.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\sys\invhyp.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\sys/" /Fd"Release\sys/" /FD /c 

".\Release\sys\invhyp.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\sys/" /Fd"Debug\sys/" /FD /GZ /c 

".\Debug\sys\invhyp.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\sys\ldfrexp.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\sys/" /Fd"Release\sys/" /FD /c 

".\Release\sys\ldfrexp.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\sys/" /Fd"Debug\sys/" /FD /GZ /c 

".\Debug\sys\ldfrexp.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\sys\log1p.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\sys/" /Fd"Release\sys/" /FD /c 

".\Release\sys\log1p.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\sys/" /Fd"Debug\sys/" /FD /GZ /c 

".\Debug\sys\log1p.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\sys\minmax.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\sys/" /Fd"Release\sys/" /FD /c 

".\Release\sys\minmax.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\sys/" /Fd"Debug\sys/" /FD /GZ /c 

".\Debug\sys\minmax.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\sys\pow_int.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\sys/" /Fd"Release\sys/" /FD /c 

".\Release\sys\pow_int.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\sys/" /Fd"Debug\sys/" /FD /GZ /c 

".\Debug\sys\pow_int.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\sys\prec.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\sys/" /Fd"Release\sys/" /FD /c 

".\Release\sys\prec.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\sys/" /Fd"Debug\sys/" /FD /GZ /c 

".\Debug\sys\prec.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\sys\test.c
SOURCE=..\complex\math.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\complex/" /Fd"Release\complex/" /FD /c 

".\Release\complex\math.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\complex/" /Fd"Debug\complex/" /FD /GZ /c 

".\Debug\complex\math.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\complex\test.c
SOURCE="..\ode-initval\bsimp.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\ode-initval/" /Fd"Release\ode-initval/" /FD /c 

".\Release\ode-initval\bsimp.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\ode-initval/" /Fd"Debug\ode-initval/" /FD /GZ /c 

".\Debug\ode-initval\bsimp.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE="..\ode-initval\control.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\ode-initval/" /Fd"Release\ode-initval/" /FD /c 

".\Release\ode-initval\control.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\ode-initval/" /Fd"Debug\ode-initval/" /FD /GZ /c 

".\Debug\ode-initval\control.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE="..\ode-initval\cscal.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\ode-initval/" /Fd"Release\ode-initval/" /FD /c 

".\Release\ode-initval\cscal.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\ode-initval/" /Fd"Debug\ode-initval/" /FD /GZ /c 

".\Debug\ode-initval\cscal.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE="..\ode-initval\cstd.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\ode-initval/" /Fd"Release\ode-initval/" /FD /c 

".\Release\ode-initval\cstd.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\ode-initval/" /Fd"Debug\ode-initval/" /FD /GZ /c 

".\Debug\ode-initval\cstd.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE="..\ode-initval\evolve.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\ode-initval/" /Fd"Release\ode-initval/" /FD /c 

".\Release\ode-initval\evolve.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\ode-initval/" /Fd"Debug\ode-initval/" /FD /GZ /c 

".\Debug\ode-initval\evolve.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE="..\ode-initval\gear1.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\ode-initval/" /Fd"Release\ode-initval/" /FD /c 

".\Release\ode-initval\gear1.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\ode-initval/" /Fd"Debug\ode-initval/" /FD /GZ /c 

".\Debug\ode-initval\gear1.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE="..\ode-initval\gear2.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\ode-initval/" /Fd"Release\ode-initval/" /FD /c 

".\Release\ode-initval\gear2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\ode-initval/" /Fd"Debug\ode-initval/" /FD /GZ /c 

".\Debug\ode-initval\gear2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE="..\ode-initval\rk2.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\ode-initval/" /Fd"Release\ode-initval/" /FD /c 

".\Release\ode-initval\rk2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\ode-initval/" /Fd"Debug\ode-initval/" /FD /GZ /c 

".\Debug\ode-initval\rk2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE="..\ode-initval\rk2imp.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\ode-initval/" /Fd"Release\ode-initval/" /FD /c 

".\Release\ode-initval\rk2imp.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\ode-initval/" /Fd"Debug\ode-initval/" /FD /GZ /c 

".\Debug\ode-initval\rk2imp.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE="..\ode-initval\rk2simp.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\ode-initval/" /Fd"Release\ode-initval/" /FD /c 

".\Release\ode-initval\rk2simp.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\ode-initval/" /Fd"Debug\ode-initval/" /FD /GZ /c 

".\Debug\ode-initval\rk2simp.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE="..\ode-initval\rk4.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\ode-initval/" /Fd"Release\ode-initval/" /FD /c 

".\Release\ode-initval\rk4.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\ode-initval/" /Fd"Debug\ode-initval/" /FD /GZ /c 

".\Debug\ode-initval\rk4.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE="..\ode-initval\rk4imp.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\ode-initval/" /Fd"Release\ode-initval/" /FD /c 

".\Release\ode-initval\rk4imp.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\ode-initval/" /Fd"Debug\ode-initval/" /FD /GZ /c 

".\Debug\ode-initval\rk4imp.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE="..\ode-initval\rk8pd.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\ode-initval/" /Fd"Release\ode-initval/" /FD /c 

".\Release\ode-initval\rk8pd.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\ode-initval/" /Fd"Debug\ode-initval/" /FD /GZ /c 

".\Debug\ode-initval\rk8pd.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE="..\ode-initval\rkck.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\ode-initval/" /Fd"Release\ode-initval/" /FD /c 

".\Release\ode-initval\rkck.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\ode-initval/" /Fd"Debug\ode-initval/" /FD /GZ /c 

".\Debug\ode-initval\rkck.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE="..\ode-initval\rkf45.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\ode-initval/" /Fd"Release\ode-initval/" /FD /c 

".\Release\ode-initval\rkf45.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\ode-initval/" /Fd"Debug\ode-initval/" /FD /GZ /c 

".\Debug\ode-initval\rkf45.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE="..\ode-initval\step.c"

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\ode-initval/" /Fd"Release\ode-initval/" /FD /c 

".\Release\ode-initval\step.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\ode-initval/" /Fd"Debug\ode-initval/" /FD /GZ /c 

".\Debug\ode-initval\step.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE="..\ode-initval\test.c"
SOURCE=..\randist\bernoulli.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\bernoulli.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\bernoulli.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\beta.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\beta.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\beta.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\bigauss.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\bigauss.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\bigauss.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\binomial.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\binomial.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\binomial.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\binomial_tpe.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\binomial_tpe.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\binomial_tpe.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\cauchy.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\cauchy.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\cauchy.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\chisq.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\chisq.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\chisq.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\dirichlet.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\dirichlet.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\dirichlet.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\discrete.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\discrete.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\discrete.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\erlang.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\erlang.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\erlang.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\exponential.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\exponential.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\exponential.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\exppow.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\exppow.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\exppow.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\fdist.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\fdist.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\fdist.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\flat.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\flat.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\flat.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\gamma.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\gamma.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\gamma.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\gauss.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\gauss.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\gauss.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\gausstail.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\gausstail.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\gausstail.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\gausszig.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\gausszig.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\gausszig.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\geometric.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\geometric.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\geometric.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\gumbel.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\gumbel.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\gumbel.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\hyperg.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\hyperg.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\hyperg.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\landau.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\landau.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\landau.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\laplace.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\laplace.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\laplace.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\levy.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\levy.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\levy.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\logarithmic.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\logarithmic.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\logarithmic.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\logistic.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\logistic.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\logistic.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\lognormal.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\lognormal.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\lognormal.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\multinomial.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\multinomial.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\multinomial.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\nbinomial.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\nbinomial.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\nbinomial.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\pareto.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\pareto.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\pareto.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\pascal.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\pascal.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\pascal.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\poisson.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\poisson.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\poisson.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\rayleigh.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\rayleigh.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\rayleigh.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\shuffle.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\shuffle.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\shuffle.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\sphere.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\sphere.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\sphere.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\tdist.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\tdist.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\tdist.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\randist\test.c
SOURCE=..\randist\weibull.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\randist/" /Fd"Release\randist/" /FD /c 

".\Release\randist\weibull.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\randist/" /Fd"Debug\randist/" /FD /GZ /c 

".\Debug\randist\weibull.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\airy.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\airy.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\airy.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\airy_der.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\airy_der.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\airy_der.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\airy_zero.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\airy_zero.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\airy_zero.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\atanint.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\atanint.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\atanint.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\bessel.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\bessel.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\bessel.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\bessel_amp_phase.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\bessel_amp_phase.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\bessel_amp_phase.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\bessel_i.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\bessel_i.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\bessel_i.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\bessel_I0.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\bessel_I0.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\bessel_I0.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\bessel_I1.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\bessel_I1.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\bessel_I1.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\bessel_In.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\bessel_In.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\bessel_In.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\bessel_Inu.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\bessel_Inu.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\bessel_Inu.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\bessel_j.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\bessel_j.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\bessel_j.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\bessel_J0.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\bessel_J0.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\bessel_J0.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\bessel_J1.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\bessel_J1.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\bessel_J1.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\bessel_Jn.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\bessel_Jn.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\bessel_Jn.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\bessel_Jnu.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\bessel_Jnu.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\bessel_Jnu.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\bessel_k.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\bessel_k.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\bessel_k.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\bessel_K0.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\bessel_K0.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\bessel_K0.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\bessel_K1.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\bessel_K1.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\bessel_K1.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\bessel_Kn.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\bessel_Kn.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\bessel_Kn.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\bessel_Knu.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\bessel_Knu.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\bessel_Knu.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\bessel_olver.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\bessel_olver.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\bessel_olver.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\bessel_sequence.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\bessel_sequence.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\bessel_sequence.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\bessel_temme.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\bessel_temme.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\bessel_temme.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\bessel_y.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\bessel_y.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\bessel_y.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\bessel_Y0.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\bessel_Y0.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\bessel_Y0.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\bessel_Y1.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\bessel_Y1.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\bessel_Y1.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\bessel_Yn.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\bessel_Yn.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\bessel_Yn.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\bessel_Ynu.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\bessel_Ynu.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\bessel_Ynu.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\bessel_zero.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\bessel_zero.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\bessel_zero.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\beta.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\beta.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\beta.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\beta_inc.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\beta_inc.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\beta_inc.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\cheb_eval.c
SOURCE=..\specfunc\cheb_eval_mode.c
SOURCE=..\specfunc\clausen.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\clausen.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\clausen.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\coulomb.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\coulomb.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\coulomb.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\coulomb_bound.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\coulomb_bound.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\coulomb_bound.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\coupling.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\coupling.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\coupling.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\dawson.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\dawson.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\dawson.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\debye.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\debye.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\debye.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\dilog.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\dilog.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\dilog.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\elementary.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\elementary.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\elementary.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\ellint.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\ellint.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\ellint.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\elljac.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\elljac.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\elljac.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\erfc.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\erfc.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\erfc.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\exp.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\exp.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\exp.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\expint.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\expint.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\expint.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\expint3.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\expint3.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\expint3.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\fermi_dirac.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\fermi_dirac.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\fermi_dirac.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\gamma.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\gamma.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\gamma.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\gamma_inc.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\gamma_inc.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\gamma_inc.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\gegenbauer.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\gegenbauer.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\gegenbauer.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\hyperg.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\hyperg.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\hyperg.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\hyperg_0F1.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\hyperg_0F1.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\hyperg_0F1.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\hyperg_1F1.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\hyperg_1F1.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\hyperg_1F1.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\hyperg_2F0.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\hyperg_2F0.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\hyperg_2F0.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\hyperg_2F1.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\hyperg_2F1.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\hyperg_2F1.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\hyperg_U.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\hyperg_U.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\hyperg_U.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\laguerre.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\laguerre.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\laguerre.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\lambert.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\lambert.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\lambert.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\legendre_con.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\legendre_con.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\legendre_con.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\legendre_H3d.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\legendre_H3d.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\legendre_H3d.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\legendre_poly.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\legendre_poly.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\legendre_poly.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\legendre_Qn.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\legendre_Qn.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\legendre_Qn.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\log.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\log.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\log.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\poch.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\poch.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\poch.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\pow_int.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\pow_int.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\pow_int.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\psi.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\psi.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\psi.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\result.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\result.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\result.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\shint.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\shint.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\shint.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\sinint.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\sinint.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\sinint.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\synchrotron.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\synchrotron.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\synchrotron.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\test_airy.c
SOURCE=..\specfunc\test_bessel.c
SOURCE=..\specfunc\test_coulomb.c
SOURCE=..\specfunc\test_dilog.c
SOURCE=..\specfunc\test_gamma.c
SOURCE=..\specfunc\test_hyperg.c
SOURCE=..\specfunc\test_legendre.c
SOURCE=..\specfunc\test_sf.c
SOURCE=..\specfunc\transport.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\transport.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\transport.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\trig.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\trig.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\trig.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\specfunc\zeta.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\specfunc/" /Fd"Release\specfunc/" /FD /c 

".\Release\specfunc\zeta.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\specfunc/" /Fd"Debug\specfunc/" /FD /GZ /c 

".\Debug\specfunc\zeta.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\borosh13.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\borosh13.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\borosh13.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\cmrg.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\cmrg.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\cmrg.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\coveyou.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\coveyou.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\coveyou.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\default.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\default.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\default.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\file.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\file.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\file.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\fishman18.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\fishman18.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\fishman18.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\fishman20.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\fishman20.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\fishman20.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\fishman2x.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\fishman2x.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\fishman2x.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\gfsr4.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\gfsr4.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\gfsr4.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\knuthran.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\knuthran.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\knuthran.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\knuthran2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\knuthran2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\knuthran2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\lecuyer21.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\lecuyer21.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\lecuyer21.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\minstd.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\minstd.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\minstd.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\mrg.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\mrg.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\mrg.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\mt.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\mt.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\mt.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\r250.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\r250.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\r250.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\ran0.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\ran0.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\ran0.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\ran1.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\ran1.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\ran1.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\ran2.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\ran2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\ran2.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\ran3.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\ran3.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\ran3.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\rand.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\rand.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\rand.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\rand48.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\rand48.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\rand48.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\random.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\random.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\random.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\randu.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\randu.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\randu.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\ranf.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\ranf.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\ranf.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\ranlux.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\ranlux.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\ranlux.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\ranlxd.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\ranlxd.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\ranlxd.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\ranlxs.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\ranlxs.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\ranlxs.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\ranmar.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\ranmar.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\ranmar.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\rng.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\rng.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\rng.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\schrage.c
SOURCE=..\rng\slatec.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\slatec.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\slatec.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\taus.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\taus.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\taus.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\taus113.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\taus113.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\taus113.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\test.c
SOURCE=..\rng\transputer.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\transputer.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\transputer.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\tt.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\tt.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\tt.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\types.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\types.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\types.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\uni.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\uni.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\uni.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\uni32.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\uni32.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\uni32.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\vax.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\vax.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\vax.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\waterman14.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\waterman14.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\waterman14.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\rng\zuf.c

!IF  "$(CFG)" == "gsl18_vc6 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\include\gsl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Release\rng/" /Fd"Release\rng/" /FD /c 

".\Release\rng\zuf.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gsl18_vc6 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\gsl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GSL18_VC6_EXPORTS" /D "GSL_DLL" /D "DLL_EXPORT" /Fo"Debug\rng/" /Fd"Debug\rng/" /FD /GZ /c 

".\Debug\rng\zuf.obj" : $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\fft\fft.c

"$(INTDIR)\fft.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

