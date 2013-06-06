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
static char* testName  = "CvArray class";
static char* testClass = "Algorithm";

#define SIZE 10
#define CAPACITY 20

#pragma warning(disable:4702) /* unreachable code */

template <class Val> static int foaCvArray()
{
    int Errors = 0;

    /* Checking constructors */

    /* Check empty constructor */
    CvArray<Val> arrayEmpty;
    if( arrayEmpty.get_capacity() != 0 )
        return trsResult( TRS_FAIL, "Bad empty constructor (wrong capacity)" );
    if( arrayEmpty.get_size() != 0 )
        return trsResult( TRS_FAIL, "Bad empty constructor (wrong size)" );
    if( arrayEmpty.get_array() != 0 )
        return trsResult( TRS_FAIL, "Bad empty constructor (wrong array)" );

    /* Check one-parameter constructor */
    CvArray<Val> arrayOne( SIZE );
    if( arrayOne.get_size() != SIZE )
        return trsResult( TRS_FAIL, "Bad one-parameter constructor (wrong size)" );
    if( arrayOne.get_capacity() != SIZE )
        return trsResult( TRS_FAIL, "Bad one-parameter constructor (wrong capacity)" );
    if( arrayOne.get_array() == 0 )
        return trsResult( TRS_FAIL, "Bad one-parameter constructor (wrong array)" );

    /* Check two-parameter constructor */
    CvArray<Val> arrayTwo( SIZE, CAPACITY );
    if( arrayTwo.get_size() != SIZE )
        return trsResult( TRS_FAIL, "Bad two-parameter constructor (wrong size)" );
    if( arrayTwo.get_capacity() != CAPACITY )
        return trsResult( TRS_FAIL, "Bad two-parameter constructor (wrong capacity)" );
    if( arrayTwo.get_array() == 0 )
        return trsResult( TRS_FAIL, "Bad two-parameter constructor (wrong array)" );

    /* Filling array */
    CvArray<Val>::value_type* array0 = arrayTwo.get_array();
    for( CvArray<Val>::idx_type i = 0; i < SIZE; i++ )
        array0[i] = (CvArray<Val>::value_type)i;

    /* Check copy constructor */
    CvArray<Val> arrayCopy( arrayTwo );
    if( arrayTwo.get_size() != arrayCopy.get_size() )
        return trsResult( TRS_FAIL, "Bad two-parameter constructor (wrong size)" );
    if( arrayTwo.get_capacity() != arrayCopy.get_capacity() )
        return trsResult( TRS_FAIL, "Bad two-parameter constructor (wrong capacity)" );
    CvArray<Val>::value_type* array1 = arrayCopy.get_array();
    for( i = 0; i < SIZE; i++ ) if( array0[i] != array1[i] )
        return trsResult( TRS_FAIL, "Bad two-parameter constructor (wrong array)" );

    /* Check begin & raw_begin functions */
    CvArray<Val>::iterator iter = arrayCopy.begin();
    CvArray<Val>::iterator iterRaw = arrayCopy.raw_begin();
    if( iter.get_begin() != array1 )
    {
        Errors++;
        trsWrite( ATS_LST | ATS_CON, "Error: begin() function (wrong begin)\n" );
    }
    if( iter.get_current() != array1 )
    {
        Errors++;
        trsWrite( ATS_LST | ATS_CON, "Error: begin() function (wrong current)\n" );
    }
    if( iterRaw.get_begin() != array1 )
    {
        Errors++;
        trsWrite( ATS_LST | ATS_CON, "Error: raw_begin() function (wrong begin)\n" );
    }
    if( iterRaw.get_current() != array1 )
    {
        Errors++;
        trsWrite( ATS_LST | ATS_CON, "Error: raw_begin() function (wrong current)\n" );
    }

    /* Check end & raw_end functions */
    iter = arrayCopy.end();
    iterRaw = arrayCopy.raw_end();
    if( iter.get_begin() != array1 )
    {
        Errors++;
        trsWrite( ATS_LST | ATS_CON, "Error: end() function (wrong begin)\n" );
    }
    if( iter.get_current() != &array1[arrayCopy.get_size() - 1] )
    {
        Errors++;
        trsWrite( ATS_LST | ATS_CON, "Error: end() function (wrong current)\n" );
    }
    if( iterRaw.get_begin() != array1 )
    {
        Errors++;
        trsWrite( ATS_LST | ATS_CON, "Error: raw_end() function (wrong begin)\n" );
    }
    if( iterRaw.get_current() != &array1[arrayCopy.get_size() - 1] )
    {
        Errors++;
        trsWrite( ATS_LST | ATS_CON, "Error: raw_end() function (wrong current)\n" );
    }

    /* Check operator= */
    arrayEmpty = arrayCopy;
    if( arrayEmpty.get_size() != arrayCopy.get_size() )
    {
        Errors++;
        trsWrite( ATS_LST | ATS_CON, "Error: operator= (wrong size)\n" );
    }
    if( arrayEmpty.get_capacity() != arrayCopy.get_capacity() )
    {
        Errors++;
        trsWrite( ATS_LST | ATS_CON, "Error: operator= (wrong capacity)\n" );
    }
    array0 = arrayEmpty.get_array();
    for( i = 0; i < arrayCopy.get_size(); i++ ) if( array0[i] != array1[i] )
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Error: operator= (wrong array)" );
        break;
    }

    /* Check operator[] */
    array0 = arrayTwo.get_array();
    for( i = 0; i < arrayCopy.get_size(); i++ ) if( array0[i] != arrayCopy[i] )
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Error: operator[] (wrong array)" );
        break;
    }

    /* Check query() function */
    for( i = 0; i < arrayCopy.get_size(); i++ ) if( array0[i] != arrayCopy.query(i) )
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Error: query() function (wrong array)" );
        break;
    }

    /* Check remove() function */
    arrayTwo.remove( SIZE / 2 );
    if( array0[SIZE / 2] != 0 )
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Error: remove() function (wrong array)" );
    }

    /* Check clear() function */
    arrayTwo.clear();
    for( i = 0; i < arrayTwo.get_size(); i++ ) if( array0[i] != 0 )
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Error: clear() function (wrong array)" );
        break;
    }

    /* Check set_size() function */
    /* Check case, when new size < capacity */
    arrayTwo = arrayCopy;
    arrayCopy.set_size( SIZE + 1 );
    if( arrayCopy.get_size() != SIZE + 1 )
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Error: set_size() function (wrong size)\n" );
    }
    if( arrayCopy.get_capacity() != CAPACITY )
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Error: set_size() function (wrong capasity)\n" );
    }
    for( i = 0; i < arrayTwo.get_size(); i++ ) if( arrayTwo[i] != arrayCopy[i] )
    {
        Errors++;
        trsWrite( ATS_LST | ATS_CON, "Error: set_size() function (old data changed)\n" );
        break;
    }
    for( i = arrayTwo.get_size();i < arrayCopy.get_size(); i++ )
        if( arrayCopy[i] != 0 )
        {
            Errors++;
            trsWrite( ATS_LST | ATS_CON,
                      "Error: set_size() function (new data not empty)\n" );
            break;
        }
    /* Check case, when new size > capacity */
    arrayCopy = arrayTwo;
    arrayCopy.set_size( CAPACITY + 10 );
    if( arrayCopy.get_size() != CAPACITY + 10 )
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Error: set_size() function (wrong size)\n" );
    }
    if( arrayCopy.get_capacity() != CAPACITY + 10 )
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Error: set_size() function (wrong capasity)\n" );
    }
    for( i = 0; i < arrayTwo.get_size(); i++ ) if( arrayTwo[i] != arrayCopy[i] )
    {
        Errors++;
        trsWrite( ATS_LST | ATS_CON, "Error: set_size() function (old data changed)\n" );
        break;
    }
    for( i = arrayTwo.get_size(); i < arrayCopy.get_size(); i++ )
        if( arrayCopy[i] != 0 )
        {
            Errors++;
            trsWrite( ATS_LST | ATS_CON,
                      "Error: set_size() function (new data not empty)\n" );
            break;
        }

    /* Check set_capacity() function */
    arrayCopy = arrayTwo;
    arrayCopy.set_capacity( CAPACITY + 1 );
    if( arrayCopy.get_size() != SIZE )
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Error: set_capacity() function (wrong size)\n" );
    }
    if( arrayCopy.get_capacity() != CAPACITY + 1 )
    {
        Errors++;
        trsWrite( ATS_CON | ATS_LST, "Error: set_capacity() function (wrong capasity)\n" );
    }
    for( i = 0; i < arrayCopy.get_size(); i++ ) if( arrayTwo[i] != arrayCopy[i] )
    {
        Errors++;
        trsWrite( ATS_LST | ATS_CON, "Error: set_capacity() function (data changed)\n" );
        break;
    }

    return Errors == 0 ? TRS_OK : trsResult( TRS_FAIL, "Fixed %d errors", Errors );
}


#define INT   0
#define FLOAT 1
#define SHORT 2

static int foaCvArrayType( void* param )
{
    int Param = (int)param;
    switch (Param)
    {
    case INT:
        return foaCvArray<int>();
    case FLOAT:
        return foaCvArray<float>();
    case SHORT:
        return foaCvArray<short>();
    default:
        return trsResult( TRS_FAIL, "Wrong parameter" );
    }
}


void InitAStorageArray()
{
    trsRegArg( funcName, testName, testClass, foaCvArrayType, INT   );
    trsRegArg( funcName, testName, testClass, foaCvArrayType, FLOAT );
    trsRegArg( funcName, testName, testClass, foaCvArrayType, SHORT );
    return;
}
#else
void InitAStorageArray()
{
}
#endif /* WIN32 */

/* End of file. */
