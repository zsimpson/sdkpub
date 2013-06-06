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

const int SIZE_X     = 200;
const int SIZE_Y     = 250;
const int PLANS      = 3;

const int BEGIN_X    = 20;
const int BEGIN_Y    = 40;

const int SECOND_X   = 30;
const int SECOND_Y   = 25;

static char* funcName  = "PixelAccess";
static char* testName  = "PixelAccess Algorithm Test";
static char* testClass = "Algorithm";


#define TEST_TYPE CvPixelPosition8u
#define DATA_TYPE uchar
static int foaPixelAccessUCHAR(void)
{
#include "apixelaccess.inc"
}
#undef TEST_TYPE
#undef DATA_TYPE

#define TEST_TYPE CvPixelPosition8s
#define DATA_TYPE char
static int foaPixelAccessCHAR(void)
{
#include "apixelaccess.inc"
}
#undef TEST_TYPE
#undef DATA_TYPE

#define TEST_TYPE CvPixelPosition32f
#define DATA_TYPE float
static int foaPixelAccessFLOAT(void)
{
#include "apixelaccess.inc"
}
#undef TEST_TYPE
#undef DATA_TYPE


void InitAPixelAccess()
{
    trsReg( funcName, testName, testClass, foaPixelAccessUCHAR );
    trsReg( funcName, testName, testClass, foaPixelAccessCHAR );
    trsReg( funcName, testName, testClass, foaPixelAccessFLOAT );
}
