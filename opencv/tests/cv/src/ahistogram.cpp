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

#include "cvtest.h"
#include "cv.hpp"

#ifdef WIN32

static char* funcName  = "Constructors/Destructors and all other functions";
static char* testName  = "CVHistogram class";
static char* testClass = "Algorithm";

class operation
{
    public:
        typedef double result_type;

        template <class Val> double operator () ( double s, const Val val1, const Val val2 )
            { return (Val)(s + val1 * val2); }
};

template<class Storage1, class Storage2> static int foaHistogram(Storage1, Storage2)
{
const int S1 = 3;
const int S2 = 3;
const int S3 = 3;

const int SIZE = S1;

    typedef Storage1::value_type Val;
    typedef Storage1::idx_type   Idx;

    CVHistogram<Storage1> hist1( S1, S2, S3 );
    CVHistogram<Storage2> hist2( S1, S2, S3 );
    int Errors = 0;

    Idx i1, i2, i3;

    /* Check access to elements of histogram */
    for( Idx i = 0; i < SIZE; i++ ) hist1(i,i,i) = (Val)(i + 1);
    for( i = 0; i < SIZE; i++ ) if( hist1(i,i,i) != i + 1 )
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Wrong access\n" );
        break;
    }

    hist1.clear();
    hist2.clear();

    /* Check operations between two histogramms */
    for( i1 = 0; i1 < S1; i1++ )
        for( i2 = 0; i2 < S2; i2++ )
            for( i3 = 0; i3 < S3; i3 += 3 )
            {
                hist1( i1, i2, i3 ) = 1;
                hist1( i1, i2, i3 + 2 ) = 3;
                hist2( i1, i2, i3 + 1 ) = 2;
                hist2( i1, i2, i3 + 2 ) = 3;
            }
    if( hist1.operate_with( hist2, operation() ) != S1 * S2 * S3 * 3)
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Wrong operate_with() function\n" );
    }

    if( hist2.operate_with( hist1, operation() ) != S1 * S2 * S3 * 3)
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Wrong operate_with() function\n" );
    }

    hist1.clear();
    hist2.clear();
    /* Check normalize function */
    for( i1 = 0; i1 < S1; i1++ )
        for( i2 = 0; i2 < S2; i2++ )
            for( i3 = 0; i3 < S3; i3 += 3 )
            {
                hist1( i1, i2, i3 ) = hist2( i1, i2, i3 ) = 1;
                hist1( i1, i2, i3 + 1 ) = hist2( i1, i2, i3 + 1 ) = 2;
                hist1( i1, i2, i3 + 2 ) = hist2( i1, i2, i3 + 2 ) = 3;
            }
    hist1.normalize();
    for( i1 = 0; i1 < S1; i1++ )
        for( i2 = 0; i2 < S2; i2++ )
            for( i3 = 0; i3 < S3; i3 += 3 )
                if( hist1( i1, i2, i3 ) != (Val)(1.0 / (S1 * S2 * S3 * 2))    ||
                    hist1( i1, i2, i3 + 1) != (Val)(2.0 / (S1 * S2 * S3 * 2)) ||
                    hist1( i1, i2, i3 + 2) != (Val)(3.0 / (S1 * S2 * S3 * 2)) )
                {
                    Errors++;
                    trsWrite( ATS_CON | ATS_LST, "Wrong normalize() function\n" );
                    goto _n1;
                }
_n1:;
    hist1.clear();
    hist2.normalize( hist1 );
    for( i1 = 0; i1 < S1; i1++ )
        for( i2 = 0; i2 < S2; i2++ )
            for( i3 = 0; i3 < S3; i3 += 3 )
                if( hist1( i1, i2, i3 ) != (Val)(1.0 / (S1 * S2 * S3 * 2))    ||
                    hist1( i1, i2, i3 + 1) != (Val)(2.0 / (S1 * S2 * S3 * 2)) ||
                    hist1( i1, i2, i3 + 2) != (Val)(3.0 / (S1 * S2 * S3 * 2)) )
                {
                    Errors++;
                    trsWrite( ATS_CON | ATS_LST, "Wrong normalize(result) function\n" );
                    goto _n2;
                }
_n2:;
    hist1.clear();
    hist2.clear();
    /* Check mean function */
    for( i1 = 0; i1 < S1; i1++ )
        for( i2 = 0; i2 < S2; i2++ )
            for( i3 = 0; i3 < S3; i3 += 3 )
            {
                hist1( i1, i2, i3 ) = 1;
                hist1( i1, i2, i3 + 1 ) = 2;
                hist1( i1, i2, i3 + 2 ) = 3;
            }
    if( hist1.mean() != 2 )
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Wrong mean() function\n" );
    }
    /* Check threshold function */
    hist2 = hist1;
    hist1.threshold( 3 );
    for( i1 = 0; i1 < S1; i1++ )
        for( i2 = 0; i2 < S2; i2++ )
            for( i3 = 0; i3 < S3; i3 += 3 )
                if( hist1( i1, i2, i3 )    != 0 ||
                    hist1( i1, i2, i3 + 1) != 0 ||
                    hist1( i1, i2, i3 + 2) != 3 )
                {
                    Errors++;
                    trsWrite( ATS_CON | ATS_LST, "Wrong threshold() function\n" );
                    goto _n3;
                }
_n3:;
    hist2.threshold( 2, hist1 );
    for( i1 = 0; i1 < S1; i1++ )
        for( i2 = 0; i2 < S2; i2++ )
            for( i3 = 0; i3 < S3; i3 += 3 )
                if( hist1( i1, i2, i3 )    != 0 ||
                    hist1( i1, i2, i3 + 1) != 2 ||
                    hist1( i1, i2, i3 + 2) != 3 )
                {
                    Errors++;
                    trsWrite( ATS_CON | ATS_LST, "Wrong threshold(result) function\n" );
                    goto _n4;
                }
_n4:;
    /* Check -= operator */
    for( i1 = 0; i1 < S1; i1++ )
        for( i2 = 0; i2 < S2; i2++ )
            for( i3 = 0; i3 < S3; i3 ++ ) hist1( i1, i2, i3 ) = (Val)(i3 + 10);
    hist1 -= 1;
    for( i1 = 0; i1 < S1; i1++ )
        for( i2 = 0; i2 < S2; i2++ )
            for( i3 = 0; i3 < S3; i3 ++ )
                if( hist1( i1, i2, i3 ) != i3 + 9 )
                {
                    Errors++;
                    trsWrite( ATS_CON | ATS_LST, "Wrong operator -= operator\n" );
                    goto _n4;
                }

    /* Check *= operator */
    for( i1 = 0; i1 < S1; i1++ )
        for( i2 = 0; i2 < S2; i2++ )
            for( i3 = 0; i3 < S3; i3 ++ ) hist1( i1, i2, i3 ) = (Val)(i3);
    hist1 *= 2;
    for( i1 = 0; i1 < S1; i1++ )
        for( i2 = 0; i2 < S2; i2++ )
            for( i3 = 0; i3 < S3; i3 ++ )
                if( hist1( i1, i2, i3 ) != i3 * 2 )
                {
                    Errors++;
                    trsWrite( ATS_CON | ATS_LST, "Wrong operator *= operator\n" );
                    goto _n4;
                }

    return Errors == 0 ? TRS_OK : trsResult( TRS_FAIL, "Fixed %d errors", Errors );
}

#define INT   0
#define FLOAT 1
#define SHORT 2

#define ARRAY 0
#define TREE  1

#define ARRAY_INT   (ARRAY << 4) + INT
#define ARRAY_FLOAT (ARRAY << 4) + FLOAT
#define ARRAY_SHORT (ARRAY << 4) + SHORT
#define TREE_INT    (TREE << 4)  + INT
#define TREE_FLOAT  (TREE << 4)  + FLOAT
#define TREE_SHORT  (TREE << 4)  + SHORT

static int foaCVHistogramType( void* param )
{
    int type = (int)param;

    switch( type )
    {
    case ARRAY_INT:
        return foaHistogram(CvArray<int>(),CvArray<int>());
    case ARRAY_FLOAT:
        return foaHistogram(CvArray<float>(), CvArray<float>());
    case ARRAY_SHORT:
        return foaHistogram(CvArray<short>(), CvArray<short>());
    case TREE_INT:
        return foaHistogram(CvTree<int>(), CvTree<int>());
    case TREE_FLOAT:
        return foaHistogram(CvTree<float>(), CvTree<float>());
    case TREE_SHORT:
        return foaHistogram(CvTree<short>(), CvTree<short>());
    default:
        return TRS_UNDEF;
    }
}

void InitAHistogram( void )
{
    trsRegArg( funcName, testName, testClass, foaCVHistogramType, ARRAY_INT   );
    trsRegArg( funcName, testName, testClass, foaCVHistogramType, ARRAY_FLOAT );
    trsRegArg( funcName, testName, testClass, foaCVHistogramType, ARRAY_SHORT );
    trsRegArg( funcName, testName, testClass, foaCVHistogramType, TREE_INT   );
    trsRegArg( funcName, testName, testClass, foaCVHistogramType, TREE_FLOAT );
    trsRegArg( funcName, testName, testClass, foaCVHistogramType, TREE_SHORT );
}

#else
void InitAHistogram( void )
{
}
#endif /* WIN32 */

/* End of file. */
