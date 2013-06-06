C======================================================================
C
#if 0
C     
C     fulltosparse.F
C     .F file needs to be preprocessed to generate .for equivalent
C     
#endif
C     
C     fulltosparse.f
C     example for illustrating how to populate a sparse matrix.
C     For the purpose of this example, you must pass in a
C     non-sparse 2-dimensional argument of type real double.
C
C     NOTE: The subroutine loadsparse() is in the file called 
C     loadsparse.f. 
C     This is a MEX-file for MATLAB.
C     Copyright 1984-2006 The MathWorks, Inc.
C     $Revision: 1.6.6.4 $
C======================================================================
#include "fintrf.h"
     
         
C     The gateway routine.
      subroutine mexFunction(nlhs, plhs, nrhs, prhs)
      integer nlhs, nrhs
C-----------------------------------------------------------------------
C     (pointer) Replace integer by integer*8 on 64-bit platforms
C
      mwpointer plhs(*), prhs(*)
      mwpointer mxGetPr, mxCreateSparse, mxGetIr, mxGetJc
      mwpointer pr, sr, irs, jcs
C-----------------------------------------------------------------------
C
C     mwsize and mwindex are 4 bytes on 32-bit platforms
C     On 64-bit platforms, they are 4 bytes in 32-bit compatibility mode
C     Otherwise they are 8 bytes (required for sparse)
C
      mwsize m, n, nzmax
      mwsize mxGetM, mxGetN;

      integer mxIsComplex, mxIsDouble
      integer loadsparse

C     Check for proper number of arguments. 
      if (nrhs .ne. 1) then
         call mexErrMsgTxt('One input argument required.')
      endif
      if (nlhs .gt. 1) then
         call mexErrMsgTxt('Too many output arguments.')
      endif

C     Check data type of input argument
      if (mxIsDouble(prhs(1)) .eq. 0) then
         call mexErrMsgTxt('Input argument must be of type double.')
      endif
      if (mxIsComplex(prhs(1)) .eq. 1) then
         call mexErrMsgTxt('Input argument must be real only')
      endif

C     Get the size and pointers to input data
      m = mxGetM(prhs(1))
      n = mxGetN(prhs(1))
      pr = mxGetPr(prhs(1))

C     Allocate space
C     NOTE: Assume at most 20% of the data is sparse.
      nzmax = dble(m*n) *.20 + .5
C     NOTE: The maximum number of non-zero elements cannot be less
C     than the number of columns in the matrix
      if (n .gt. nzmax) then
         nzmax = n
      endif
      plhs(1) = mxCreateSparse(m,n,nzmax,0)
      sr = mxGetPr(plhs(1))
      irs = mxGetIr(plhs(1))
      jcs = mxGetJc(plhs(1))

C     Load the sparse data
      if (loadsparse(%VAL(pr),%VAL(sr),%VAL(irs),%VAL(jcs),m,n,nzmax)
     +     .eq. 1) then
         call mexPrintf('Truncating output, input is > 20%% sparse')
      endif
      return
      end
