/* $Revision: 1.2.6.4 $ $Date: 2006/10/14 11:48:22 $ */
/*=========================================================
 * utdu_slv.c
 * example for illustrating how to use LAPACK within a C
 * MEX-file on Windows or HP-UX.  This differs from the
 * other platforms in that the LAPACK symbols are not
 * exported with underscores e.g., dsysvx instead of dsysvx_
 *
 * UTDU_SLV Solves the symmetric indefinite system of linear 
 * equations A*X=B for X.
 * X = UTDU_SLV(A,B) computes a symmetric (Hermitian) indefinite 
 * factorization of A and returns the result X such that A*X is B. 
 * B must have as many rows as A.
 *
 * This is a MEX-file for MATLAB.
 * Copyright 1984-2006 The MathWorks, Inc.
 *=======================================================*/

#if !defined(_WIN32)
#define zhesvx zhesvx_
#define dsysvx dsysvx_
#endif

#include "mex.h"
#include "fort.h"

extern void zhesvx(
    char   *fact,
    char   *uplo,
    int    *n,
    int    *nrhs,
    double *a,
    int    *lda,
    double *af,
    int    *ldaf,
    int    *ipiv,
    double *b,
    int    *ldb,
    double *x,
    int    *ldx,
    double *rcond,
    double *ferr,
    double *berr,
    double *work,
    int    *lwork,
    double *rwork,
    int    *info
);

extern void dsysvx(
    char   *fact,
    char   *uplo,
    int    *n,
    int    *nrhs,
    double *a,
    int    *lda,
    double *af,
    int    *ldaf,
    int    *ipiv,
    double *b,
    int    *ldb,
    double *x,
    int    *ldx,
    double *rcond,
    double *ferr,
    double *berr,
    double *work,
    int    *lwork,
    int    *iwork,
    int    *info
);

void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] )
{

	/* mex interface to LAPACK functions dsysvx and zhesvx */

    char fact[2] = {'N','\0'}, uplo[2] = {'U','\0'};
    char msg[101];
    int cplx, info, n, nrhsb, lda, ldaf, ldb, ldx, lwork;
    int *ipiv, *iwork=NULL;
    double *A, *AF, *b, *x, rcond, *ferr, *berr, *work1, *work, *rwork=NULL;
	
    if ((nlhs > 1) || (nrhs != 2)) {
      mexErrMsgTxt("Expect 2 input arguments and return 1 output argument");
    }

    /*
     * FORTRAN/LAPACK uses 32-bit integers at present
     */
    mxAssert(mxGetM(prhs[0])<INT_MAX, "Matrix is too large for 32-bit LAPACK");
    mxAssert(mxGetN(prhs[0])<INT_MAX, "Matrix is too large for 32-bit LAPACK");
    mxAssert(mxGetM(prhs[1])<INT_MAX, "Matrix is too large for 32-bit LAPACK");
    mxAssert(mxGetN(prhs[1])<INT_MAX, "Matrix is too large for 32-bit LAPACK");

    n = (int)mxGetN(prhs[0]);
    nrhsb = (int)mxGetN(prhs[1]);
    lda = (int)mxGetM(prhs[0]);
    if (lda != n) {
      mexErrMsgTxt("Matrix must be square and symmetric");
    }
    cplx = (mxGetPi(prhs[0]) || mxGetPi(prhs[1]));
    if (cplx) {
      A = mat2fort(prhs[0],lda,n);
      AF = (double *)mxCalloc(2*lda*n,sizeof(double));
    } else {
      A = mxGetPr(prhs[0]);
      AF = (double *)mxCalloc(lda*n,sizeof(double));
    }
    ldaf = lda;
    ipiv = (int *)mxCalloc(n,sizeof(int));
    ldb = (int)mxGetM(prhs[1]);
    if (lda != ldb) {
      mexErrMsgTxt("A and b must have the same number of rows");
    }
    ldx = ldb;
    ferr = (double *)mxCalloc(nrhsb,sizeof(double));
    berr = (double *)mxCalloc(nrhsb,sizeof(double));
    lwork = -1;
    info = 0;
    if (cplx) {
      b = mat2fort(prhs[1],ldb,nrhsb);
      x = (double *)mxCalloc(2*ldb*nrhsb,sizeof(double));
      work1 = (double *)mxCalloc(2,sizeof(double));
      rwork = (double *)mxCalloc(n,sizeof(double));
      /* Query zhesvx on the value of lwork */
      zhesvx ( fact, uplo, &n, &nrhsb, A, &lda, AF, &ldaf, ipiv, b, &ldb,
        x, &ldx, &rcond, ferr, berr, work1, &lwork, rwork, &info );
        if (info < 0) {
          sprintf(msg, "Input %d to zhesvx had an illegal value",-info);
          mexErrMsgTxt(msg);
        }
      lwork = (int)(work1[0]);
      work = (double *)mxCalloc(2*lwork,sizeof(double));
        zhesvx ( fact, uplo, &n, &nrhsb, A, &lda, AF, &ldaf, ipiv, b, &ldb,
          x, &ldx, &rcond, ferr, berr, work, &lwork, rwork, &info );
        if (info < 0) {
          sprintf(msg, "Input %d to zhesvx had an illegal value",-info);
          mexErrMsgTxt(msg);
        }
    } else {
      b = mxGetPr(prhs[1]);
      x = (double *)mxCalloc(ldb*nrhsb,sizeof(double));
      work1 = (double *)mxCalloc(1,sizeof(double));
      iwork = (int *)mxCalloc(n,sizeof(int));
      /* Query dsysvx on the value of lwork */
      dsysvx ( fact, uplo, &n, &nrhsb, A, &lda, AF, &ldaf, ipiv, b, &ldb,
        x, &ldx, &rcond, ferr, berr, work1, &lwork, iwork, &info );
        if (info < 0) {
          sprintf(msg, "Input %d to dsysvx had an illegal value",-info);
          mexErrMsgTxt(msg);
        }
      lwork = (int)(work1[0]);
      work = (double *)mxCalloc(lwork,sizeof(double));
        dsysvx ( fact, uplo, &n, &nrhsb, A, &lda, AF, &ldaf, ipiv, b, &ldb,
          x, &ldx, &rcond, ferr, berr, work, &lwork, iwork, &info );
        if (info < 0) {
          sprintf(msg, "Input %d to dsysvx had an illegal value",-info);
          mexErrMsgTxt(msg);
        }
    }

    if (rcond == 0) {
      sprintf(msg,"Matrix is singular to working precision.");
      mexErrMsgTxt(msg);
    } else if (rcond < mxGetEps()) {
      sprintf(msg,"Matrix is close to singular or badly scaled.\n"
        "         Results may be inaccurate. RCOND = %g",rcond);
      mexWarnMsgTxt(msg);
    }

    if (cplx) {
      plhs[0] = fort2mat(x,ldx,ldx,nrhsb);
      mxFree(A);
      mxFree(b);
      mxFree(rwork);
    } else {
      plhs[0] = mxCreateDoubleMatrix(ldx,nrhsb,0);
      mxSetPr(plhs[0],x);
      mxFree(iwork);
    }

    mxFree(AF);
    mxFree(ipiv);
    mxFree(ferr);
    mxFree(berr);
    mxFree(work1);
    mxFree(work);
}
