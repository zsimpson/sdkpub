/*=================================================================
 * mexevalstring.c
 *
 * mexevalstring takes no input arguments. It uses mexEvalString to
 * turn warnings off in MATLAB. It then calls mexEvalString to
 * evaluate 0/0, which would cause a Divide By Zero warning to be
 * displayed if warnings were not turned off.
 *
 * NOTE: The call to mexEvalString to evaluate a divide by zero is for
 * illustration purposes only, and may be replaced with a call to
 * mexCallMATLAB to evaluate a MATLAB function that would cause a
 * warning.
 *
 * Copyright 1984-2006 The MathWorks, Inc.
 *================================================================*/

/* $Revision: 1.8.6.2 $ */
#include "mex.h"

void
mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
    (void) plhs;      /* unused parameters */
    (void) prhs;

    /* Check for proper number of input and output arguments */    
    if (nrhs != 0) {
        mexErrMsgTxt("No input arguments required.");
    } 
    if(nlhs > 1){
        mexErrMsgTxt("Too many output arguments.");
    } 

    /* Issue a division by 0 to show warning is displayed. */
    mexEvalString("a=0/0");
   
    /* Turn divideByZero warning off */
    mexEvalString("warnState = warning('off','MATLAB:divideByZero');");
    
    /* Issue a division by 0 to show no warning is displayed. */
    mexEvalString("b=0/0");
    
    /* Leave MATLAB in the same state it was in before the MEX-file
       executed. */
    mexEvalString("warning(warnState);");

}
