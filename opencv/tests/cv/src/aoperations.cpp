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

template<class Storage1, class Storage2> static int foaOperations(Storage1, Storage2)
{
const int SIZE = 720;

    typedef Storage1::value_type Val;
    typedef Storage1::idx_type   Idx;

    CVHistogram<Storage1> hist1( SIZE );
    CVHistogram<Storage2> hist2( SIZE );

    int Errors = 0;

    for( Idx i = 0; i < SIZE; i++ )
    {
        hist1[i] = (Val)(i % 10);
        hist2[i] = (Val)(9 - hist1[i]);
    }

    if( calc_histogram_intersection( hist1, hist2 ) != SIZE * 2 )
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Error Intersection function\n" );
    }

    double res;
    if( (res = fabs(calc_histogram_chi_square( hist1, hist2 ) - SIZE * 330 / 90)) > 0.0001 )
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Error ChiSqr function\n" );
    }

    for( i = 0; i < SIZE; i++ )
    {
        hist1[i] = (Val)(i % 9);
        hist2[i] = (Val)(8 - hist1[i]);
    }

    if( fabs(calc_histogram_correlation( hist1, hist2 ) + 1 ) >= 0.0001 )
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Error Correl function\n" );
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

static int foaCvOperationsType( void* param )
{
    int type = (int)param;

    switch( type )
    {
    case ARRAY_INT:
        return foaOperations(CvArray<int>(),CvArray<int>());
    case ARRAY_FLOAT:
        return foaOperations(CvArray<double>(), CvArray<double>());
    case ARRAY_SHORT:
        return foaOperations(CvArray<short>(), CvArray<short>());
    case TREE_INT:
        return foaOperations(CvTree<int>(), CvTree<int>());
    case TREE_FLOAT:
        return foaOperations(CvTree<float>(), CvTree<float>());
    case TREE_SHORT:
        return foaOperations(CvTree<short>(), CvTree<short>());
    default:
        return TRS_UNDEF;
    }
}

void InitAHistogramOperations( void )
{
    trsRegArg( funcName, testName, testClass, foaCvOperationsType, ARRAY_INT   );
    trsRegArg( funcName, testName, testClass, foaCvOperationsType, ARRAY_FLOAT );
    trsRegArg( funcName, testName, testClass, foaCvOperationsType, ARRAY_SHORT );
    trsRegArg( funcName, testName, testClass, foaCvOperationsType, TREE_INT   );
    trsRegArg( funcName, testName, testClass, foaCvOperationsType, TREE_FLOAT );
    trsRegArg( funcName, testName, testClass, foaCvOperationsType, TREE_SHORT );
}
#else
void InitAHistogramOperations( void )
{
}
#endif /* WIN32 */

/* End of file. */
