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

#ifndef _CVMTEST_H_
#define _CVMTEST_H_

#include "cv.hpp"
#include "ats.h"
//#include "_cvWrap.h"


#ifdef __cplusplus
extern "C"{
#endif
#include "cblas.h"
#define IPPI_CHECK( cvFun )                                                  \
  {                                                                          \
    CvStatus  result = cvFun;                                                \
    if( result != CV_NO_ERR )                                                 \
    {                                                                         \
      trsWrite(ATS_LST,                                                       \
               "The error code %d was returned by the function call\n"        \
               "%s\n"                                                         \
               "in file %s, line %d",                                         \
               result, #cvFun, __FILE__, __LINE__ );                          \
      return trsResult( TRS_FAIL,                                             \
                        "A function from OpenCV library returns error status" ); \
    }                                                                         \
  }

#define ATS_CHECK( atsFun )                                                   \
  {                                                                           \
    CvStatus  result = (CvStatus)atsFun;                                  \
    if( result != IPP_NO_ERR )                                                \
    {                                                                         \
      trsWrite(ATS_LST,                                                       \
               "The error code %d was returned by the function call\n"        \
               "%s\n"                                                         \
               "in file %s, line %d",                                         \
               result, #atsFun, __FILE__, __LINE__ );                         \
      return trsResult( TRS_FAIL,                                             \
                        "A function from ATS library returns error status" ); \
    }                                                                         \
  }


#ifndef ATS_TIC_MAX
#ifdef WIN32
#define ATS_TIC_MAX  0x7fffffffffffffffI64
#else
#define ATS_TIC_MAX  0x7fffffffffffffffLL
#endif
#endif

#define ATS_START_TIMING() int64 temp = atsGetTickCount();
#define ATS_END_TIMING()   temp = atsGetTickCount() - temp; tics = ATS_MIN( tics, temp );

#define ATS_MEASURE( act ) \
    ATS_START_TIMING()     \
    (act);                 \
    ATS_END_TIMING()



#ifdef __cplusplus
}
#endif

#endif /* _CVMTEST_H_ */

/* End of file. */
