C=====================================================================
#if 0
C     
C     passstr.F
C     .F file needs to be preprocessed to generate .for equivalent
C     
#endif
C     
C     passstr.f
C     example for illustrating passing a character matrix from FORTRAN
C     to MATLAB
C 
C     passes a string array/character matrix into MATLAB as output
C     arguments rather than placing it directly into the workspace 
C      
C     This is a MEX-file for MATLAB.
C     Copyright 1984-2006 The MathWorks, Inc.
C     $Revision: 1.11.6.5 $
C=====================================================================
#include "fintrf.h"

      subroutine mexFunction(nlhs, plhs, nrhs, prhs)
C-----------------------------------------------------------------------
C
      mwpointer plhs(*), prhs(*)
      mwpointer p_str, mxCreateString
C-----------------------------------------------------------------------
C
      integer nlhs, nrhs
      mwsize i, m, n
      character*75 thestring
      character*15 string(5)

C     create the string to be passed into MATLAB.
      string(1) = 'MATLAB         '
      string(2) = 'The Scientific '
      string(3) = 'Computing      '
      string(4) = 'Environment    '
      string(5) = '   by TMW, Inc.'
      
C     concatenate the set of 5 strings into a long string
      thestring = string(1)
      do 10 i=2,5
         thestring = thestring(:((i-1)*15)) // string(i)
 10   continue
      
C     create the string matrix to be passed into MATLAB 
C     set the matrix size to be M=15 and N=5
      p_str = mxcreatestring(thestring)
      m = 15
      call mxSetM(p_str, m)
      n = 5
      call mxSetN(p_str, n)
      
C     transpose the resulting matrix in MATLAB
      call mexCallMATLAB(1, plhs, 1, p_str, 'transpose')

      return
      end
