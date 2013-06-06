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
static char* testName  = "CvBackProject function";
static char* testClass = "Algorithm";

template<class Storage, class SrcType, class ThreshType, class DstType> static int
    foaCvBackProject(Storage, SrcType, ThreshType, DstType)
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

    DstType* measure = new DstType[roi.width * roi.height];

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
    CvBackProject<CVHistogram<Storage>, SrcType, ThreshType, DstType>
        ( hist, src, roi, step, thresh, measure, roi.width * sizeof(DstType), 0 );

    for( i = 0; i < roi.width; i++ )
        if( measure[roi.width + i] != roi.width / 5 * (1 + (i%5 == 0) + (i%5 == 1)))
    {
        trsWrite( ATS_CON | ATS_LST, "Wrong destination value\n" );
        Errors++;
        break;
    }
    for( int y = 0; y < roi.height; y++ )
        for( int x = 0; x < roi.width; x++ )
            if( y != 1 && measure[roi.width * y + x] != 0 )
            {
                trsWrite( ATS_CON | ATS_LST, "Wrong destination value (non zero)\n" );
                Errors++;
                goto _exit;
            }
_exit:;
    delete src[0];
    delete src[1];
    delete src[2];
    delete measure;

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

static int foaCvBackProjectType( void* param )
{
    int Param = (int)param;
    switch(Param)
    {
    case ARRAY_INT:
        return foaCvBackProject(CvArray<int>(),int(), int(), int());
    case ARRAY_FLOAT:
        return foaCvBackProject(CvArray<float>(),float(), float(), int());
    case ARRAY_SHORT:
        return foaCvBackProject(CvArray<short>(),short(), short(), int());
    case TREE_INT:
        return foaCvBackProject(CvTree<int>(),int(), int(), int());
    case TREE_FLOAT:
        return foaCvBackProject(CvTree<float>(),float(), float(), int());
    case TREE_SHORT:
        return foaCvBackProject(CvTree<short>(),short(), short(), int());
    default:
        assert( 0 );
        return trsResult( TRS_UNDEF, "Wrong parameter" );
    }
}

void InitABackProject( void )
{
    trsRegArg( funcName, testName, testClass, foaCvBackProjectType, ARRAY_INT );
    trsRegArg( funcName, testName, testClass, foaCvBackProjectType, ARRAY_FLOAT );
    trsRegArg( funcName, testName, testClass, foaCvBackProjectType, ARRAY_SHORT );
    trsRegArg( funcName, testName, testClass, foaCvBackProjectType, TREE_INT );
    trsRegArg( funcName, testName, testClass, foaCvBackProjectType, TREE_FLOAT );
    trsRegArg( funcName, testName, testClass, foaCvBackProjectType, TREE_SHORT );
}
#else
void InitABackProject( void )
{
}
#endif /* WIN32 */

/* End of file. */
