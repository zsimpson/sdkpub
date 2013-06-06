#include "fintrf.h"
C
#if 0
C     
C     timestwo.F
C     .F file needs to be preprocessed to generate .for equivalent
C     
#endif
C     
C     timestwo.f
C
C     multiple the input argument by 2
      
C     This is a MEX-file for MATLAB.
C     Copyright 1984-2006 The MathWorks, Inc.
C     $Revision: 1.12.2.3 $
      
      subroutine mexFunction(nlhs, plhs, nrhs, prhs)
C-----------------------------------------------------------------------
C
      mwpointer plhs(*), prhs(*)
      mwpointer mxGetPr, mxCreateDoubleMatrix
      mwpointer x_pr, y_pr
C-----------------------------------------------------------------------
C

      integer nlhs, nrhs, mxIsNumeric
      mwsize mxGetM, mxGetN
      mwsize m, n, size
      real*8  x, y

C     Check for proper number of arguments. 
      if(nrhs .ne. 1) then
         call mexErrMsgTxt('One input required.')
      elseif(nlhs .ne. 1) then
         call mexErrMsgTxt('One output required.')
      endif

C     Get the size of the input array.
      m = mxGetM(prhs(1))
      n = mxGetN(prhs(1))
      size = m*n

C     Check to insure the input is a number.
      if(mxIsNumeric(prhs(1)) .eq. 0) then
         call mexErrMsgTxt('Input must be a number.')
      endif

C     Create matrix for the return argument.
      plhs(1) = mxCreateDoubleMatrix(m,n,0)
      x_pr = mxGetPr(prhs(1))
      y_pr = mxGetPr(plhs(1))
      call mxCopyPtrToReal8(x_pr,x,size)

C     Call the computational subroutine.
      call timestwo(y, x)

C     Load the data into y_pr, which is the output to MATLAB
      call mxCopyReal8ToPtr(y,y_pr,size)     

      return
      end

      subroutine timestwo(y, x)
      real*8 x, y
C     
      y = 2.0 * x
      return
      end


