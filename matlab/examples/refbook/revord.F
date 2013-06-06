C======================================================================
C
#if 0
C     
C     revord.F
C     .F file needs to be preprocessed to generate .for equivalent
C     
#endif
C     
C     revord.f
C     example for illustrating how to copy the string data from 
C     MATLAB to a FORTRAN-style string and back again 
C
C     takes a row vector string and returns a string in reverse order. 
C
C     This is a MEX-file for MATLAB.
C     Copyright 1984-2006 The MathWorks, Inc.
C     $Revision: 1.14.6.4 $
C======================================================================
#include "fintrf.h"

      subroutine revord(input_buf, strlen, output_buf)
      character  input_buf(*), output_buf(*)
      mwsize    i, strlen     
      do 10 i=1,strlen
         output_buf(i) = input_buf(strlen-i+1)
 10   continue
      return
      end

C     The gateway routine.
      subroutine mexFunction(nlhs, plhs, nrhs, prhs)
      integer nlhs, nrhs
C-----------------------------------------------------------------------
C
      mwpointer plhs(*), prhs(*)
      mwpointer mxCreateString, mxGetString       
C-----------------------------------------------------------------------
C
      mwsize  mxGetM, mxGetN, strlen
      integer mxIsChar, status
      character*100 input_buf, output_buf

C     Check for proper number of arguments. 
      if (nrhs .ne. 1) then
         call mexErrMsgTxt('One input required.')
      elseif (nlhs .gt. 1) then
         call mexErrMsgTxt('Too many output arguments.')
C     The input  must be a string.
      elseif(mxIsChar(prhs(1)) .ne. 1) then
         call mexErrMsgTxt('Input must be a string.')
C     The input must be a row vector.
      elseif (mxGetM(prhs(1)) .ne. 1) then
         call mexErrMsgTxt('Input must be a row vector.')
      endif
    
C     Get the length of the input string.
      strlen = mxGetM(prhs(1))*mxGetN(prhs(1))

C     Get the string contents (dereference the input pointer).
      status = mxGetString(prhs(1), input_buf, 100)

C     Check if mxGetString is successful.
      if (status .ne. 0) then 
         call mexErrMsgTxt('String length must be less than 100.')
      endif

C     Initialize outbuf_buf to blanks. This is necessary on some compilers.

      output_buf = ' '

C     Call the computational subroutine.
      call revord(input_buf, strlen, output_buf)
    
C     set output_buf to MATLAB mexFunction output
      plhs(1) = mxCreateString(output_buf)

      return
      end
