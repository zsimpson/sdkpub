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
#include "cvtest.hpp"

#ifdef WIN32
#include <process.h>
#else
#include <pthread.h>
#endif


/* Testing parameters */
static char* FuncName = "Error Handling Test";

static char TestName[]    = "Checking Error Handling";
static char TestClass[]   = "Algorithm";
    
/* here is own error checking function */
CVStatus CV_CDECL err_func( CVStatus status, const char *func,
                          const char *context, const char *file,int line) 
{
    return status;
};

#ifndef WIN32
void* ThreadFunction( void* result )
#else
void CV_CDECL ThreadFunction(void* result)
#endif
{
    long Errors = 0;

    /* Some variables */
    cvSetErrMode( CV_ErrModeLeaf );
    Errors+= (cvGetErrMode() != CV_ErrModeLeaf);

    cvSetErrMode( CV_ErrModeParent );
    Errors+= (cvGetErrMode() != CV_ErrModeParent);

    cvSetErrMode( CV_ErrModeSilent );
    Errors+= (cvGetErrMode() != CV_ErrModeSilent);
    
    cvRedirectError( err_func );
    Errors += ( cvRedirectError( cvStdErrReport ) != err_func ); 
    Errors += ( cvRedirectError( cvGuiBoxReport ) != cvStdErrReport ); 

    Errors += ( cvRedirectError( err_func ) != cvGuiBoxReport ); 

    *((int*)result) = Errors;

    //if ( Errors )
      //  trsResult( TRS_FAIL, "Fixed %d errors", Errors );
} 

static int fmaErrHandleTest( void )
{
    long errors = 0;
    int Result1 = 0;
    int Result2 = 0;

    ThreadFunction(&Result1);
#ifdef WIN32
    _beginthread( ThreadFunction, 0, &Result2 );  
#else
    pthread_t thread;
    pthread_create( &thread, 0, ThreadFunction, &Result2 );
#endif
    
    errors = Result1 + Result2;
    return (errors == 0) ? TRS_OK : trsResult( TRS_FAIL, "Fixed %d errors", errors );

} 

void InitAErrHandle()
{
    trsReg( FuncName, TestName, TestClass, fmaErrHandleTest );
}

/* End of file. */
