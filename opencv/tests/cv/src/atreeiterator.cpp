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
static char* testName  = "CvTreeIterator class";
static char* testClass = "Algorithm";

#define SIZE 700
#define NUM 2

template <class Val, class Idx> static int foaCvTreeIterator()
{
    int Errors = 0;

    typedef CvTree<Val, Idx>::node_type node_type;
    CvTree<Val, Idx> tree;

    for( Idx i = 0; i < SIZE; i++ ) tree[i] = (Val)(i + 1);

    CvTreeIterator<node_type> iterator;

    iterator = tree.begin();
    if( *iterator != 1 )
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Wrong CvTree::begin() function\n" );
    }

    if( *(iterator++) != 1 )
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Wrong postfix operator++ (not postfix)\n" );
    }
    if( *iterator != 2 )
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Wrong postfix operator++ (not increment)\n" );
    }

    for( i = 2; i < SIZE; i++ ) if( *(++iterator) != (i + 1) )
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Wrong prefix operator++ (not increment)\n" );
        break;
    }

    if( *(++iterator) != SIZE )
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Wrong operator++ (increment out of date)\n" );
    }

    if( !(iterator == iterator) )
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Bad operator==" );
    }

    if( iterator != iterator )
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Bad operator!=" );
    }

    return Errors == 0 ? TRS_OK : trsResult( TRS_FAIL, "Fixed %d errors", Errors );
}


#define INT   0
#define FLOAT 1
#define SHORT 2

static int foaCvTreeIteratorType( void* param )
{
    int Param = (int)param;
    switch (Param)
    {
    case INT:
        return foaCvTreeIterator<int, int>();
    case FLOAT:
        return foaCvTreeIterator<float, int>();
    case SHORT:
        return foaCvTreeIterator<short, int>();
    default:
        return trsResult( TRS_FAIL, "Wrong parameter" );
    }
}

void InitATreeIterator()
{
    trsRegArg( funcName, testName, testClass, foaCvTreeIteratorType, INT   );
    trsRegArg( funcName, testName, testClass, foaCvTreeIteratorType, FLOAT );
    trsRegArg( funcName, testName, testClass, foaCvTreeIteratorType, SHORT );
    return;
}
#else
void InitATreeIterator()
{
}
#endif

/* End of file. */
