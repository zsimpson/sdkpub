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

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    atsInitRandom
//    Purpose:
//      Initialazing by randomize value
//    Context:
//    Parameters:
//      Min - minimal bound
//      Max - maximum bound
//    Returns:
//    Notes:
//F*/
double atsInitRandom( double Min, double Max )
{
  static int flag = 0;
  if( flag == 0 )
  {
    srand( (unsigned)time( NULL ) );
    flag = 1;
  } /* if */

  return (double)rand() / RAND_MAX * (Max - Min) + Min;
} /* atsInitRandom */


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    ats1bInitRandom
//    Purpose:
//      Initialazing unsigned char array by randomize value
//    Context:
//    Parameters:
//      Min  - minimal bound
//      Max  - maximum bound
//      pDst - destination array
//      lLen - size of array
//    Returns:
//    Notes:
//F*/
void ats1bInitRandom( double Min, double Max, unsigned char* pDst, long lLen )
{
  /* Some variables */
  int i;

  assert( pDst != NULL );
  assert( lLen > 0 );
  /* Init */
  for( i = 0; i < lLen; i++ ) pDst[i] = (unsigned char)atsInitRandom( Min,Max );

} /* ats1bInitRandom */


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    ats1cInitRandom
//    Purpose:
//      Initialazing unsigned char array by randomize value
//    Context:
//    Parameters:
//      Min  - minimal bound
//      Max  - maximum bound
//      pDst - destination array
//      lLen - size of array
//    Returns:
//    Notes:
//F*/
void ats1cInitRandom( double Min, double Max, char* pDst, long lLen )
{
  /* Some variables */
  int i;

  assert( pDst != NULL );
  assert( lLen > 0 );
  /* Init */
  for( i = 0; i < lLen; i++ ) pDst[i] = (unsigned char)atsInitRandom( Min,Max );

} /* ats1cInitRandom */


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    ats1iInitRandom
//    Purpose:
//      Initialazing unsigned char array by randomize value
//    Context:
//    Parameters:
//      Min  - minimal bound
//      Max  - maximum bound
//      pDst - destination array
//      lLen - size of array
//    Returns:
//    Notes:
//F*/
void ats1iInitRandom( double Min, double Max, int* pDst, long lLen )
{
  /* Some variables */
  int i;

  assert( pDst != NULL );
  assert( lLen > 0 );
  /* Init */
  for( i = 0; i < lLen; i++ ) pDst[i] = (int)atsInitRandom( Min,Max );

} /* ats1iInitRandom */


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    ats1flInitRandom
//    Purpose:
//      Initialazing unsigned char array by randomize value
//    Context:
//    Parameters:
//      Min  - minimal bound
//      Max  - maximum bound
//      pDst - destination array
//      lLen - size of array
//    Returns:
//    Notes:
//F*/
void ats1flInitRandom( double Min, double Max, float* pDst, long lLen )
{
  /* Some variables */
  int   i;

  assert( pDst != NULL );
  assert( lLen > 1 );

  /* Init */
  for( i = 0; i < lLen; i++ )
  {
    pDst[i] = (float)atsInitRandom( Min, Max );
  } /* for */

} /* ats1flInitGradRandom */

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    ats1flInitGradRandom
//    Purpose:
//      Initialazing unsigned char array by randomize value
//    Context:
//    Parameters:
//      Min  - minimal bound
//      Max  - maximum bound
//      pDst - destination array
//      lLen - size of array
//    Returns:
//    Notes:
//F*/
void ats1flInitGradRandom( double Min, double Max, float* pDst, long lLen )
{
  /* Some variables */
  int   i;
  float flStep;

  assert( pDst != NULL );
  assert( lLen > 1 );

  flStep = (float)(Max - Min) / (lLen - 1);

  /* Init */
  pDst[0] = (float)Min;
  pDst[lLen - 1] = (float)Max;
  for( i = 1; i < lLen - 1; i++ )
  {
    pDst[i] = (float)atsInitRandom( pDst[i - 1] + 0.1 * flStep,
                             flStep * (i + 1) - 0.1 * flStep );
    assert( pDst[i] > pDst[i - 1] );
  } /* for */

} /* ats1flInitGradRandom */

/* End of file. */
