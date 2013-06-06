C ======================================================================
#if 0
C     
C     fill.F
C     .F file needs to be preprocessed to generate .for equivalent
C     
#endif
C     
C     fill.f
C     This is the subfunction called by sincall that fills the 
C     mxArray with data.  Your version of fill can load your data
C     however you would like.
C
C     This is a MEX-file for MATLAB.
C     Copyright 1984-2006 The MathWorks, Inc.
C     $Revision: 1.3.6.2 $
C ======================================================================
#include "fintrf.h"      

C     subroutine for filling up data

      subroutine fill(pr, m, n, max)
      
      real*8  pr(*)
      mwsize m, n, max
     
      m=max/2
      n=1
      do 10 i=1,m
 10      pr(i)=i*(4*3.1415926/max)

      return
      end
