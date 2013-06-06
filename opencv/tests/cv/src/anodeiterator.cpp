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
static char* testName  = "CvNodeIterator class";
static char* testClass = "Algorithm";

#define SIZE 10
#define NUM 2

template <class Node> static int foaCvNodeIterator()
{
    int Errors = 0;

    _CvNodeBlock<Node> block;

    for( _CvNodeBlock<Node>::node_type::idx_type i = 0; i < SIZE; i++ )
        block[i].idx = (_CvNodeBlock<Node>::node_type::idx_type)(i + 1);

    CvNodeIterator<Node> iterator_one( &block );
    if( iterator_one.get_idx() != 1 )
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Wrong one parameter constructor (wrong index)\n" );
    }

    CvNodeIterator<Node> iterator_two( &block, NUM );
    if( iterator_two.get_idx() != NUM + 1 )
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Wrong two parameters constructor (wrong index)\n" );
    }

    if( (++iterator_one).get_idx() != 2 )
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Wrong prefix operator++ (wrong index)\n" );
    }

    if( (iterator_two++).get_idx() != NUM + 1 )
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Wrong postfix operator++ (not postfix)\n" );
    }

    if( iterator_two.get_idx() != NUM + 2 )
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Wrong postfix operator++ (not increment)\n" );
    }

    iterator_one = iterator_two;

    if( !(iterator_one == iterator_two) )
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Wrong operator==\n" );
    }

    if( iterator_one != iterator_two )
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Wrong operator!=\n" );
    }

    return Errors == 0 ? TRS_OK : trsResult( TRS_FAIL, "Fixed %d errors", Errors );
}


#define INT   0
#define FLOAT 1
#define SHORT 2

static int foaCvNodeIteratorType( void* param )
{
    int Param = (int)param;
    switch (Param)
    {
    case INT:
        {
            typedef _CvTreeNode<int,int> int_node;
            return foaCvNodeIterator<int_node>();
        }
    case FLOAT:
        {
            typedef _CvTreeNode<float,int> float_node;
            return foaCvNodeIterator<float_node>();
        }
    case SHORT:
        {
            typedef _CvTreeNode<short,int> short_node;
            return foaCvNodeIterator<short_node>();
        }
    default:
        return trsResult( TRS_FAIL, "Wrong parameter" );
    }
}

void InitANodeIterator()
{
    trsRegArg( funcName, testName, testClass, foaCvNodeIteratorType, INT   );
    trsRegArg( funcName, testName, testClass, foaCvNodeIteratorType, FLOAT );
    trsRegArg( funcName, testName, testClass, foaCvNodeIteratorType, SHORT );
    return;
}
#else
void InitANodeIterator()
{
}
#endif /*WIN32 */

/* End of file. */
