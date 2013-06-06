/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                        Intel License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2000, Intel Corporation, all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of Intel Corporation may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/

#include "ats.h"
#include <stdio.h>
/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    atsCompSingle
//    Purpose:                                                                  
//      Detailed Comparing two float values      
//    Context:                                                                  
//    Parameters:                                                               
//      flFirst - first value                                               
//      flSecond- second value                                             
//      dbAcc - accuracy                                     
//                                                 
//    Returns:                                                                  
//      1 if not equal 
//      0 if equal                                           
//    Notes:                                                                    
//F*/
long atsCompSingle(float flFirst,
                   float flSecond,
                   double dbAcc)
{
        if(fabs( flFirst-flSecond )>
            dbAcc * ( fabs(flFirst) + fabs(flSecond))+dbAcc)
            return 1;      
                   
        else return 0;
        
}
/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    atsCompSinglePrec
//    Purpose:                                                                  
//      Detailed Comparing two float arrays      
//    Context:                                                                  
//    Parameters:                                                               
//      flFirstArray - first array                                               
//      flSecondArray - second array                                             
//      lLen       - lenght of this arrays                                      
//                                                 
//    Returns:                                                                  
//      Number of nonequal elements                                           
//    Notes:                                                                    
//F*/
long atsCompSinglePrec(float* flFirstArray,
                       float* flSecondArray,
                       long lLen,
                       double dbAcc)
{
    long lErrors = 0;
    int i;
    for(i = 0; i < lLen; i++)
    {
        if(fabs( flFirstArray[i]-flSecondArray[i] )>
            dbAcc * ( fabs(flFirstArray[i]) + fabs(flSecondArray[i]))+dbAcc){
            lErrors++;
        }
        
    }
        return lErrors;
}

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    atsCompDoublePrec
//    Purpose:                                                                  
//      Detailed Comparing two double arrays      
//    Context:                                                                  
//    Parameters:                                                               
//      flFirstArray - first array                                               
//      flSecondArray - second array                                             
//      lLen       - lenght of this arrays                                      
//                                                 
//    Returns:                                                                  
//      Number of nonequal elements                                           
//    Notes:                                                                    
//F*/
long atsCompDoublePrec(double* flFirstArray,
                       double* flSecondArray,
                       long lLen,
                       double dbAcc)
{
    long lErrors = 0;
    int i;
    for(i = 0; i < lLen; i++)
    {
        if(fabs( flFirstArray[i]-flSecondArray[i] )>  
		   dbAcc * ( fabs(flFirstArray[i]) + fabs(flSecondArray[i]))+dbAcc)
           lErrors++;
		
      
    }
     return lErrors;
}

    

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    atsCompare1Dfl
//    Purpose:                                                                  
//      Comparing two 1D float array and writing results to SUM & LST files     
//    Context:                                                                  
//    Parameters:                                                               
//      flArrayAct - actual array                                               
//      flArrayExp - expected array                                             
//      lLen       - lenght of this arrays                                      
//      dbTol      - tolerable limit                                            
//    Returns:                                                                  
//      Number of differents elements                                           
//    Notes:                                                                    
//F*/

long atsCompare1Dfl( float* flArrayAct, float* flArrayExp, long lLen, double dbTol )
{
    int   i;
    long  lErrors = 0;
    
    for( i = 0; i < lLen; i++ )
    {
        if( fabs( flArrayAct[i] - flArrayExp[i] ) > dbTol )
        {
            lErrors++;
            trsWrite( ATS_LST,
                "Error: x = %d   act  %f    exp %f\n",
                i,
                flArrayAct[i],
                flArrayExp[i] );
        } /* if */
    } /* for */
    
    if( lErrors == NULL ) trsWrite( ATS_LST,
        "No errors detected for this test\n" );
    else trsWrite( ATS_SUM | ATS_LST, "Total fixed %d errors :(\n", lErrors );
    return lErrors;
} /* atsCompare1Dfl */


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    atsCompare2Dfl
//    Purpose:                                                                  
//      Comparing two array and writing results to SUM & LST files     
//    Context:                                                                  
//    Parameters:                                                               
//    Returns:                                                                  
//      Number of differents elements                                           
//    Notes:                                                                    
//F*/
long atsCompare2Dfl( float* ArrayAct, float* ArrayExp, CvSize size, int stride, double Tol )
{
    int   x, y;
    long  lErrors = 0;
    
    for( y = 0; y < size.height; y++, ArrayAct = (float*)((long)ArrayAct + stride), 
                                      ArrayExp = (float*)((long)ArrayExp + stride) )
        for( x = 0; x < size.width; x++ )
            if( fabs( ArrayAct[x] - ArrayExp[x] ) > Tol )
            {
                lErrors++;
                trsWrite( ATS_LST,
                    "Error: x=%d  y=%d   act  %f    exp %f\n",
                    x, y,
                    (float)ArrayAct[x],
                    (float)ArrayExp[x] );
            } /* if */
            
            if( lErrors == NULL ) trsWrite( ATS_LST,
                "No errors detected for this test\n" );
            else trsWrite( ATS_SUM | ATS_LST, "Total fixed %d errors :(\n", lErrors );
            return lErrors;
} /* atsCompare1Db */


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    atsCompare1Db
//    Purpose:                                                                  
//      Comparing two 1D array and writing results to SUM & LST files     
//    Context:                                                                  
//    Parameters:                                                               
//      ArrayAct - actual array                                               
//      ArrayExp - expected array                                             
//      lLen     - lenght of this arrays                                      
//      Tol      - tolerable limit                                            
//    Returns:                                                                  
//      Number of differents elements                                           
//    Notes:                                                                    
//F*/
long atsCompare1Db( uchar* ArrayAct, uchar* ArrayExp, long lLen, int Tol )
{
    int   i;
    long  lErrors = 0;
    
    for( i = 0; i < lLen; i++ )
    {
        if( abs( ArrayAct[i] - ArrayExp[i] ) > Tol )
        {
            lErrors++;
            trsWrite( ATS_LST,
                "Error: x = %d   act  %d    exp %d\n",
                i,
                (int)ArrayAct[i],
                (int)ArrayExp[i] );
        } /* if */
    } /* for */
    
    if( lErrors == NULL ) trsWrite( ATS_LST,
        "No errors detected for this test\n" );
    else trsWrite( ATS_SUM | ATS_LST, "Total fixed %d errors :(\n", lErrors );
    return lErrors;
} /* atsCompare1Db */


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    atsCompare2Db
//    Purpose:                                                                  
//      Comparing two array and writing results to SUM & LST files     
//    Context:                                                                  
//    Parameters:                                                               
//    Returns:                                                                  
//      Number of differents elements                                           
//    Notes:                                                                    
//F*/
long atsCompare2Db( uchar* ArrayAct, uchar* ArrayExp, CvSize size, int stride, int Tol )
{
    int   x, y;
    long  lErrors = 0;
    
    for( y = 0; y < size.height; y++, ArrayAct += stride, ArrayExp += stride )
        for( x = 0; x < size.width; x++ )
            if( abs( ArrayAct[x] - ArrayExp[x] ) > Tol )
            {
                lErrors++;
                trsWrite( ATS_LST,
                    "Error: x=%d  y=%d   act  %d    exp %d\n",
                    x, y,
                    (int)ArrayAct[x],
                    (int)ArrayExp[x] );
            } /* if */
    
    if( lErrors ) trsWrite( ATS_SUM | ATS_LST, "Total fixed %d errors :(\n", lErrors );
    return lErrors;
}


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    atsCompare1Dc
//    Purpose:                                                                  
//      Comparing two 1D array and writing results to SUM & LST files     
//    Context:                                                                  
//    Parameters:                                                               
//      ArrayAct - actual array                                               
//      ArrayExp - expected array                                             
//      lLen     - lenght of this arrays                                      
//      Tol      - tolerable limit                                            
//    Returns:                                                                  
//      Number of differents elements                                           
//    Notes:                                                                    
//F*/
long atsCompare1Dc( char* ArrayAct, char* ArrayExp, long lLen, int Tol )
{
    int   i;
    long  lErrors = 0;
    
    for( i = 0; i < lLen; i++ )
    {
        if( abs( ArrayAct[i] - ArrayExp[i] ) > Tol )
        {
            lErrors++;
            trsWrite( ATS_LST,
                "Error: x = %d   act  %d    exp %d\n",
                i,
                (int)ArrayAct[i],
                (int)ArrayExp[i] );
        } /* if */
    } /* for */
    
    if( lErrors ) trsWrite( ATS_SUM | ATS_LST, "Total fixed %d errors :(\n", lErrors );
    return lErrors;
} /* atsCompare1Dc */


  /*F///////////////////////////////////////////////////////////////////////////////////////
  //    Name:    atsCompare2Db
  //    Purpose:                                                                  
  //      Comparing two array and writing results to SUM & LST files     
  //    Context:                                                                  
  //    Parameters:                                                               
  //    Returns:                                                                  
  //      Number of differents elements                                           
  //    Notes:                                                                    
//F*/
long atsCompare2Dc( char* ArrayAct, char* ArrayExp, CvSize size, int stride, int Tol )
{
    int   x, y;
    long  lErrors = 0;
    
    for( y = 0; y < size.height; y++, ArrayAct += stride, ArrayExp += stride )
        for( x = 0; x < size.width; x++ )
            if( abs( ArrayAct[x] - ArrayExp[x] ) > Tol )
            {
                lErrors++;
                trsWrite( ATS_LST,
                    "Error: x=%d  y=%d   act  %d    exp %d\n",
                    x, y,
                    (int)ArrayAct[x],
                    (int)ArrayExp[x] );
            } /* if */
            
            if( lErrors ) trsWrite( ATS_SUM | ATS_LST, "Total fixed %d errors :(\n", lErrors );
            return lErrors;
}


/* End of file. */
