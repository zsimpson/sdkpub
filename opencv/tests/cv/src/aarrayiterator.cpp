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
static char* testName  = "CvArrayIterator class";
static char* testClass = "Algorithm";

#define SIZE 10
#define NUM 2

#pragma warning(disable:4702) /* unreachable code */

template <class Val> static int foaCvArrayIterator()
{
    int Errors = 0;
    CvArrayIterator<Val>::value_type* array = new Val[SIZE];
    CvArrayIterator<Val>::value_type* array1 = new Val[SIZE];

    /* Filling array */
    for( CvArrayIterator<Val>::idx_type i = 0; i < SIZE; i++ )
        array[i] = (CvArrayIterator<Val>::value_type)i;


    /* Checking constructors */

    /* Check empty constructor */
    CvArrayIterator<Val> arrayEmpty;
    if( arrayEmpty.get_begin() != 0 )
        return trsResult( TRS_FAIL, "Bad empty constructor (wrong begin)" );
    if( arrayEmpty.get_current() != 0 )
        return trsResult( TRS_FAIL, "Bad empty constructor (wrong current)" );

    /* Check one-parameter constructor */
    CvArrayIterator<Val> arrayOne( array );
    if( arrayOne.get_begin() != array )
        return trsResult( TRS_FAIL, "Bad one-parameter constructor (wrong begin)" );
    if( arrayOne.get_current() != array )
        return trsResult( TRS_FAIL, "Bad one-parameter constructor (wrong current)" );

    /* Check two-parameter constructor */
    CvArrayIterator<Val> arrayTwo( array, array + NUM );
    if( arrayTwo.get_begin() != array )
        return trsResult( TRS_FAIL, "Bad two-parameter constructor (wrong begin)" );
    if( arrayTwo.get_current() != array + NUM )
        return trsResult( TRS_FAIL, "Bad two-parameter constructor (wrong current)" );

    /* Check copy constructor */
    CvArrayIterator<Val> arrayCopy( arrayTwo );
    if( arrayTwo.get_begin() != arrayCopy.get_begin() )
        return trsResult( TRS_FAIL, "Bad two-parameter constructor (wrong begin)" );
    if( arrayTwo.get_current() != arrayCopy.get_current() )
        return trsResult( TRS_FAIL, "Bad two-parameter constructor (wrong current)" );

    /* Check init() function */
    arrayTwo.init( array1, array1 + NUM );
    if( arrayTwo.get_begin() != array1 )
        return trsResult( TRS_FAIL, "Bad init() function (wrong begin)" );
    if( arrayTwo.get_current() != array1 + NUM )
        return trsResult( TRS_FAIL, "Bad init() function (wrong current)" );

    /* Check get_idx() function */
    if( arrayCopy.get_idx() != NUM )
        return trsResult( TRS_FAIL, "Bad get_idx() function" );

    /* Check operator* */
    if( *arrayCopy != NUM )
        return trsResult( TRS_FAIL, "Bad operator* (wrong value)" );

    /* Check operator== */
    arrayTwo = arrayCopy;
    if( !(arrayCopy == arrayTwo) )
        return trsResult( TRS_FAIL, "Bad operator==" );

    /* Check operator!= */
    if( arrayCopy != arrayTwo )
        return trsResult( TRS_FAIL, "Bad operator!=" );

    /* Check operator++(int) */
    if( *(arrayCopy++) != array[NUM] )
        return trsResult( TRS_FAIL, "Bad operator++ (not postfix)" );
    if( arrayCopy.get_current() != array + NUM + 1 )
        return trsResult( TRS_FAIL, "Bad operator++ (wrong increment)" );

    /* Check operator++ */
    if( (++arrayTwo).get_current() != array + NUM + 1 )
        return trsResult( TRS_FAIL, "Bad operator++ (not postfix)" );
    if( arrayCopy.get_current() != array + NUM + 1 )
        return trsResult( TRS_FAIL, "Bad operator++ (wrong increment)" );

    delete array;
    delete array1;

    return Errors == 0 ? TRS_OK : trsResult( TRS_FAIL, "Fixed %d errors", Errors );
}


#define INT   0
#define FLOAT 1
#define SHORT 2

static int foaCvArrayIteratorType( void* param )
{
    int Param = (int)param;
    switch (Param)
    {
    case INT:
        return foaCvArrayIterator<int>();
    case FLOAT:
        return foaCvArrayIterator<float>();
    case SHORT:
        return foaCvArrayIterator<short>();
    default:
        return trsResult( TRS_FAIL, "Wrong parameter" );
    }
}

void InitAArrayIterator()
{
    trsRegArg( funcName, testName, testClass, foaCvArrayIteratorType, INT   );
    trsRegArg( funcName, testName, testClass, foaCvArrayIteratorType, FLOAT );
    trsRegArg( funcName, testName, testClass, foaCvArrayIteratorType, SHORT );
    return;
}

#else
void InitAArrayIterator()
{
}
#endif /* WIN32 */

/* End of file. */
