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

static char* funcName  = "Calculation histogram functions";
static char* testName  = "CvCalculation function";
static char* testClass = "Algorithm";

template<class Storage, class SrcType, class ThreshType> static int
    foaCvCalculate(Storage, SrcType, ThreshType)
{
    const S1 = 4;
    const S2 = 4;
    const S3 = 4;

    CvSize roi = {100, 100};
    int step = roi.width * sizeof( SrcType );

    SrcType* src[3];
    src[0] = new SrcType[roi.width * roi.height];
    src[1] = new SrcType[roi.width * roi.height];
    src[2] = new SrcType[roi.width * roi.height];

    ThreshType _thresh[3][5] = {{1, 2, 3, 4, 5},
                                {2, 3, 4, 5, 6},
                                {5, 6, 7, 9, 10}};
    ThreshType* thresh[3] = { _thresh[0], _thresh[1], _thresh[2] };

    int Errors = 0;

    for( int i = 0; i < roi.width * roi.height; i++ )
        src[0][i] = src[1][i] = src[2][i] = 0;

    for( i = 0; i < roi.width; i++ )
        for( int j = 0; j < 3; j++ )
            src[j][roi.width + i] = (SrcType)thresh[j][i%5];

    CVHistogram<Storage> hist( S1, S2, S3 );

    CvCalculateC1( hist, src, roi, step, thresh );

    for( int i1 = 0; i1 < S1; i1++ )
        for( int i2 = 0; i2 < S2; i2++ )
            for( int i3 = 0; i3 < S3; i3++ )
                if( (i1 != i2 || i1 != i3 || i2 != i3) && hist(i1, i2, i3) != 0 )
                {
                    Errors++;
                    trsWrite( ATS_CON | ATS_LST, "Wrong calculation (not zero)\n" );
                    goto _exit;
                }
                else if( i1 == i2 && i1 == i3 && i2 == i3 )
                {
                    if( i1 == 0 && hist(i1, i2, i3) != roi.width * 2 / 5 )
                    {
                        Errors++;
                        trsWrite( ATS_CON | ATS_LST, "Wrong calculation (wrong value)\n" );
                        goto _exit;
                    }
                    else if( i1 != 0 && hist(i1, i2, i3) != roi.width / 5 )
                    {
                        Errors++;
                        trsWrite( ATS_CON | ATS_LST, "Wrong calculation (wrong value)\n" );
                        goto _exit;
                    }
                }
_exit:
    delete src[0];
    delete src[1];
    delete src[2];

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

static int foaCvCalculateType( void* param )
{
    int Param = (int)param;
    switch(Param)
    {
    case ARRAY_INT:
        return foaCvCalculate(CvArray<int>(),int(), int());
    case ARRAY_FLOAT:
        return foaCvCalculate(CvArray<float>(),float(), float());
    case ARRAY_SHORT:
        return foaCvCalculate(CvArray<short>(),short(), short());
    case TREE_INT:
        return foaCvCalculate(CvTree<int>(),int(), int());
    case TREE_FLOAT:
        return foaCvCalculate(CvTree<float>(),float(), float());
    case TREE_SHORT:
        return foaCvCalculate(CvTree<short>(),short(), short());
    default:
        assert( 0 );
        return trsResult( TRS_UNDEF, "Wrong parameter" );
    }
}

void InitACvCalculate( void )
{
    trsRegArg( funcName, testName, testClass, foaCvCalculateType, ARRAY_INT );
    trsRegArg( funcName, testName, testClass, foaCvCalculateType, ARRAY_FLOAT );
    trsRegArg( funcName, testName, testClass, foaCvCalculateType, ARRAY_SHORT );
    trsRegArg( funcName, testName, testClass, foaCvCalculateType, TREE_INT );
    trsRegArg( funcName, testName, testClass, foaCvCalculateType, TREE_FLOAT );
    trsRegArg( funcName, testName, testClass, foaCvCalculateType, TREE_SHORT );
}
#else
void InitACvCalculate( void )
{
}
#endif

/* End of file. */
