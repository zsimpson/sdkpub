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
//M*/#include <stdlib.h>
#include <varargs.h>
#include <limits.h>
#include "eic.h"
#include <ipl.h>
#include "eicdllwrap.h"

#pragma warning (disable:4700) /*warning C4700: local variable 'v' used without having been initialized*/

static val_t eic_iplGetAffineTransform(void)
{
	val_t v;

	iplGetAffineTransform(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplGetAffineQuad(void)
{
	val_t v;

	iplGetAffineQuad(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplNot(void)
{
	val_t v;

	iplNot(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplSet(void)
{
	val_t v;

	iplSet(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),int));

	return v;
}

static val_t eic_iplDecimate(void)
{
	val_t v;

	iplDecimate(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int),
		arg(4,getargs(),int),
		arg(5,getargs(),int),
		arg(6,getargs(),int));

	return v;
}

static val_t eic_iplLUV2RGB(void)
{
	val_t v;

	iplLUV2RGB(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplBitonalToGray(void)
{
	val_t v;

	iplBitonalToGray(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int));

	return v;
}

static val_t eic_iplGetBilinearQuad(void)
{
	val_t v;

	iplGetBilinearQuad(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplGetPerspectiveBound(void)
{
	val_t v;

	iplGetPerspectiveBound(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplNorm(void)
{
	val_t v;

	v.dval = iplNorm(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int));

	return v;
}

static val_t eic_iplRGB2XYZ(void)
{
	val_t v;

	iplRGB2XYZ(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplAddS(void)
{
	val_t v;

	iplAddS(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int));

	return v;
}

static val_t eic_iplMoments(void)
{
	val_t v;

	iplMoments(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplThreshold(void)
{
	val_t v;

	iplThreshold(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int));

	return v;
}

static val_t eic_iplMultiplySScale(void)
{
	val_t v;

	iplMultiplySScale(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int));

	return v;
}

static val_t eic_iplCreateROI(void)
{
	val_t v;

	v.p.ep = v.p.sp = v.p.p = iplCreateROI(arg(0,getargs(),int),
		arg(1,getargs(),int),
		arg(2,getargs(),int),
		arg(3,getargs(),int),
		arg(4,getargs(),int));

	return v;
}

static val_t eic_iplRealFft2D(void)
{
	val_t v;

	iplRealFft2D(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int));

	return v;
}

static val_t eic_iplFixedFilter(void)
{
	val_t v;

	v.ival = iplFixedFilter(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int));

	return v;
}

static val_t eic_iplRGB2HLS(void)
{
	val_t v;

	iplRGB2HLS(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplBlur(void)
{
	val_t v;

	iplBlur(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int),
		arg(4,getargs(),int),
		arg(5,getargs(),int));

	return v;
}

static val_t eic_iplSquare(void)
{
	val_t v;

	iplSquare(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplCloneImage(void)
{
	val_t v;

	v.p.ep = v.p.sp = v.p.p = iplCloneImage(arg(0,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplWarpBilinear(void)
{
	val_t v;

	iplWarpBilinear(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int),
		arg(4,getargs(),int));

	return v;
}

static val_t eic_iplMedianFilter(void)
{
	val_t v;

	iplMedianFilter(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int),
		arg(4,getargs(),int),
		arg(5,getargs(),int));

	return v;
}

static val_t eic_iplScaleFP(void)
{
	val_t v;

	v.ival = iplScaleFP(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),float),
		arg(3,getargs(),float));

	return v;
}

static val_t eic_iplClose(void)
{
	val_t v;

	iplClose(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int));

	return v;
}

static val_t eic_iplDeallocate(void)
{
	val_t v;

	iplDeallocate(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),int));

	return v;
}

static val_t eic_iplGetNormalizedSpatialMoment(void)
{
	val_t v;

	v.dval = iplGetNormalizedSpatialMoment(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),int),
		arg(2,getargs(),int));

	return v;
}

static val_t eic_iplGetConvKernelFP(void)
{
	val_t v;

	iplGetConvKernelFP(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),ptr_t).p,
		arg(4,getargs(),ptr_t).p,
		arg(5,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplAdd(void)
{
	val_t v;

	iplAdd(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplConvolveSep2DFP(void)
{
	val_t v;

	iplConvolveSep2DFP(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplGetAffineBound(void)
{
	val_t v;

	iplGetAffineBound(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplDeleteConvKernel(void)
{
	val_t v;

	iplDeleteConvKernel(arg(0,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplAllocateImageFP(void)
{
	val_t v;

	iplAllocateImageFP(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),int),
		arg(2,getargs(),float));

	return v;
}

static val_t eic_iplHLS2RGB(void)
{
	val_t v;

	iplHLS2RGB(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplMinFilter(void)
{
	val_t v;

	iplMinFilter(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int),
		arg(4,getargs(),int),
		arg(5,getargs(),int));

	return v;
}

static val_t eic_iplAlphaComposite(void)
{
	val_t v;

	iplAlphaComposite(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int),
		arg(4,getargs(),ptr_t).p,
		arg(5,getargs(),ptr_t).p,
		arg(6,getargs(),ptr_t).p,
		arg(7,getargs(),int),
		arg(8,getargs(),int));

	return v;
}

static val_t eic_iplPutPixel(void)
{
	val_t v;

	iplPutPixel(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),int),
		arg(2,getargs(),int),
		arg(3,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplGetBilinearBound(void)
{
	val_t v;

	iplGetBilinearBound(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplResize(void)
{
	val_t v;

	iplResize(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int),
		arg(4,getargs(),int),
		arg(5,getargs(),int),
		arg(6,getargs(),int));

	return v;
}

static val_t eic_iplSetFP(void)
{
	val_t v;

	iplSetFP(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),float));

	return v;
}

static val_t eic_iplPreMultiplyAlpha(void)
{
	val_t v;

	iplPreMultiplyAlpha(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),int));

	return v;
}

static val_t eic_iplMultiplySFP(void)
{
	val_t v;

	iplMultiplySFP(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),float));

	return v;
}

static val_t eic_iplGetConvKernelChar(void)
{
	val_t v;

	iplGetConvKernelChar(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),ptr_t).p,
		arg(4,getargs(),ptr_t).p,
		arg(5,getargs(),ptr_t).p,
		arg(6,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplAbs(void)
{
	val_t v;

	iplAbs(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplScale(void)
{
	val_t v;

	v.ival = iplScale(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplRShiftS(void)
{
	val_t v;

	iplRShiftS(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),unsigned));

	return v;
}

static val_t eic_iplYUV2RGB(void)
{
	val_t v;

	iplYUV2RGB(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplRGB2HSV(void)
{
	val_t v;

	iplRGB2HSV(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplCopy(void)
{
	val_t v;

	iplCopy(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplDeallocateImage(void)
{
	val_t v;

	iplDeallocateImage(arg(0,getargs(),ptr_t).p);

	return v;
}

static void * EiC_Cfunc_0 = NULL;
static void __stdcall MiddleOne_0(const IplImage *x0, int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_0, const IplImage* ,x0);
    setArg(1, EiC_Cfunc_0, int ,x1);
    setArg(2, EiC_Cfunc_0, int ,x2);
    setArg(3, EiC_Cfunc_0, int ,x3);

    EiC_callBack(EiC_Cfunc_0);
}

static void * EiC_Cfunc_1 = NULL;
static void  __stdcall MiddleOne_1(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_1, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_1, int ,x1);
    setArg(2, EiC_Cfunc_1, int ,x2);
    setArg(3, EiC_Cfunc_1, int ,x3);

    EiC_callBack(EiC_Cfunc_1);
}

static void * EiC_Cfunc_2 = NULL;
static void  __stdcall MiddleOne_2(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_2, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_2, int ,x1);
    setArg(2, EiC_Cfunc_2, int ,x2);
    setArg(3, EiC_Cfunc_2, int ,x3);

    EiC_callBack(EiC_Cfunc_2);
}

static void * EiC_Cfunc_3 = NULL;
static void  __stdcall MiddleOne_3(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_3, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_3, int ,x1);
    setArg(2, EiC_Cfunc_3, int ,x2);
    setArg(3, EiC_Cfunc_3, int ,x3);

    EiC_callBack(EiC_Cfunc_3);
}

static void * EiC_Cfunc_4 = NULL;
static void  __stdcall MiddleOne_4(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_4, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_4, int ,x1);
    setArg(2, EiC_Cfunc_4, int ,x2);
    setArg(3, EiC_Cfunc_4, int ,x3);

    EiC_callBack(EiC_Cfunc_4);
}

static void * EiC_Cfunc_5 = NULL;
static void  __stdcall MiddleOne_5(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_5, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_5, int ,x1);
    setArg(2, EiC_Cfunc_5, int ,x2);
    setArg(3, EiC_Cfunc_5, int ,x3);

    EiC_callBack(EiC_Cfunc_5);
}

static void * EiC_Cfunc_6 = NULL;
static void  __stdcall MiddleOne_6(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_6, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_6, int ,x1);
    setArg(2, EiC_Cfunc_6, int ,x2);
    setArg(3, EiC_Cfunc_6, int ,x3);

    EiC_callBack(EiC_Cfunc_6);
}

static void * EiC_Cfunc_7 = NULL;
static void  __stdcall MiddleOne_7(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_7, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_7, int ,x1);
    setArg(2, EiC_Cfunc_7, int ,x2);
    setArg(3, EiC_Cfunc_7, int ,x3);

    EiC_callBack(EiC_Cfunc_7);
}

static void * EiC_Cfunc_8 = NULL;
static void  __stdcall MiddleOne_8(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_8, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_8, int ,x1);
    setArg(2, EiC_Cfunc_8, int ,x2);
    setArg(3, EiC_Cfunc_8, int ,x3);

    EiC_callBack(EiC_Cfunc_8);
}

static void * EiC_Cfunc_9 = NULL;
static void  __stdcall MiddleOne_9(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_9, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_9, int ,x1);
    setArg(2, EiC_Cfunc_9, int ,x2);
    setArg(3, EiC_Cfunc_9, int ,x3);

    EiC_callBack(EiC_Cfunc_9);
}

static void * EiC_Cfunc_10 = NULL;
static void  __stdcall MiddleOne_10(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_10, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_10, int ,x1);
    setArg(2, EiC_Cfunc_10, int ,x2);
    setArg(3, EiC_Cfunc_10, int ,x3);

    EiC_callBack(EiC_Cfunc_10);
}

static void * EiC_Cfunc_11 = NULL;
static void  __stdcall MiddleOne_11(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_11, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_11, int ,x1);
    setArg(2, EiC_Cfunc_11, int ,x2);
    setArg(3, EiC_Cfunc_11, int ,x3);

    EiC_callBack(EiC_Cfunc_11);
}

static void * EiC_Cfunc_12 = NULL;
static void  __stdcall MiddleOne_12(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_12, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_12, int ,x1);
    setArg(2, EiC_Cfunc_12, int ,x2);
    setArg(3, EiC_Cfunc_12, int ,x3);

    EiC_callBack(EiC_Cfunc_12);
}

static void * EiC_Cfunc_13 = NULL;
static void  __stdcall MiddleOne_13(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_13, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_13, int ,x1);
    setArg(2, EiC_Cfunc_13, int ,x2);
    setArg(3, EiC_Cfunc_13, int ,x3);

    EiC_callBack(EiC_Cfunc_13);
}

static void * EiC_Cfunc_14 = NULL;
static void  __stdcall MiddleOne_14(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_14, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_14, int ,x1);
    setArg(2, EiC_Cfunc_14, int ,x2);
    setArg(3, EiC_Cfunc_14, int ,x3);

    EiC_callBack(EiC_Cfunc_14);
}

static void * EiC_Cfunc_15 = NULL;
static void  __stdcall MiddleOne_15(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_15, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_15, int ,x1);
    setArg(2, EiC_Cfunc_15, int ,x2);
    setArg(3, EiC_Cfunc_15, int ,x3);

    EiC_callBack(EiC_Cfunc_15);
}

static void * EiC_Cfunc_16 = NULL;
static void  __stdcall MiddleOne_16(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_16, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_16, int ,x1);
    setArg(2, EiC_Cfunc_16, int ,x2);
    setArg(3, EiC_Cfunc_16, int ,x3);

    EiC_callBack(EiC_Cfunc_16);
}

static void * EiC_Cfunc_17 = NULL;
static void  __stdcall MiddleOne_17(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_17, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_17, int ,x1);
    setArg(2, EiC_Cfunc_17, int ,x2);
    setArg(3, EiC_Cfunc_17, int ,x3);

    EiC_callBack(EiC_Cfunc_17);
}

static void * EiC_Cfunc_18 = NULL;
static void  __stdcall MiddleOne_18(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_18, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_18, int ,x1);
    setArg(2, EiC_Cfunc_18, int ,x2);
    setArg(3, EiC_Cfunc_18, int ,x3);

    EiC_callBack(EiC_Cfunc_18);
}

static void * EiC_Cfunc_19 = NULL;
static void  __stdcall MiddleOne_19(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_19, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_19, int ,x1);
    setArg(2, EiC_Cfunc_19, int ,x2);
    setArg(3, EiC_Cfunc_19, int ,x3);

    EiC_callBack(EiC_Cfunc_19);
}

static val_t eic_iplCreateTileInfo(void)
{
	val_t v;
	static int nb = 0;

	switch(nb)
	{
	case 0 :
	EiC_Cfunc_0 = arg(0,getargs(),ptr_t).p;
	v.p.ep = v.p.sp = v.p.p = iplCreateTileInfo(MiddleOne_0,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int));
	break;
	case 1 :
	EiC_Cfunc_1 = arg(0,getargs(),ptr_t).p;
	v.p.ep = v.p.sp = v.p.p = iplCreateTileInfo(MiddleOne_1,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int));
	break;
	case 2 :
	EiC_Cfunc_2 = arg(0,getargs(),ptr_t).p;
	v.p.ep = v.p.sp = v.p.p = iplCreateTileInfo(MiddleOne_2,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int));
	break;
	case 3 :
	EiC_Cfunc_3 = arg(0,getargs(),ptr_t).p;
	v.p.ep = v.p.sp = v.p.p = iplCreateTileInfo(MiddleOne_3,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int));
	break;
	case 4 :
	EiC_Cfunc_4 = arg(0,getargs(),ptr_t).p;
	v.p.ep = v.p.sp = v.p.p = iplCreateTileInfo(MiddleOne_4,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int));
	break;
	case 5 :
	EiC_Cfunc_5 = arg(0,getargs(),ptr_t).p;
	v.p.ep = v.p.sp = v.p.p = iplCreateTileInfo(MiddleOne_5,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int));
	break;
	case 6 :
	EiC_Cfunc_6 = arg(0,getargs(),ptr_t).p;
	v.p.ep = v.p.sp = v.p.p = iplCreateTileInfo(MiddleOne_6,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int));
	break;
	case 7 :
	EiC_Cfunc_7 = arg(0,getargs(),ptr_t).p;
	v.p.ep = v.p.sp = v.p.p = iplCreateTileInfo(MiddleOne_7,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int));
	break;
	case 8 :
	EiC_Cfunc_8 = arg(0,getargs(),ptr_t).p;
	v.p.ep = v.p.sp = v.p.p = iplCreateTileInfo(MiddleOne_8,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int));
	break;
	case 9 :
	EiC_Cfunc_9 = arg(0,getargs(),ptr_t).p;
	v.p.ep = v.p.sp = v.p.p = iplCreateTileInfo(MiddleOne_9,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int));
	break;
	case 10 :
	EiC_Cfunc_10 = arg(0,getargs(),ptr_t).p;
	v.p.ep = v.p.sp = v.p.p = iplCreateTileInfo(MiddleOne_10,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int));
	break;
	case 11 :
	EiC_Cfunc_11 = arg(0,getargs(),ptr_t).p;
	v.p.ep = v.p.sp = v.p.p = iplCreateTileInfo(MiddleOne_11,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int));
	break;
	case 12 :
	EiC_Cfunc_12 = arg(0,getargs(),ptr_t).p;
	v.p.ep = v.p.sp = v.p.p = iplCreateTileInfo(MiddleOne_12,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int));
	break;
	case 13 :
	EiC_Cfunc_13 = arg(0,getargs(),ptr_t).p;
	v.p.ep = v.p.sp = v.p.p = iplCreateTileInfo(MiddleOne_13,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int));
	break;
	case 14 :
	EiC_Cfunc_14 = arg(0,getargs(),ptr_t).p;
	v.p.ep = v.p.sp = v.p.p = iplCreateTileInfo(MiddleOne_14,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int));
	break;
	case 15 :
	EiC_Cfunc_15 = arg(0,getargs(),ptr_t).p;
	v.p.ep = v.p.sp = v.p.p = iplCreateTileInfo(MiddleOne_15,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int));
	break;
	case 16 :
	EiC_Cfunc_16 = arg(0,getargs(),ptr_t).p;
	v.p.ep = v.p.sp = v.p.p = iplCreateTileInfo(MiddleOne_16,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int));
	break;
	case 17 :
	EiC_Cfunc_17 = arg(0,getargs(),ptr_t).p;
	v.p.ep = v.p.sp = v.p.p = iplCreateTileInfo(MiddleOne_17,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int));
	break;
	case 18 :
	EiC_Cfunc_18 = arg(0,getargs(),ptr_t).p;
	v.p.ep = v.p.sp = v.p.p = iplCreateTileInfo(MiddleOne_18,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int));
	break;
	case 19 :
	EiC_Cfunc_19 = arg(0,getargs(),ptr_t).p;
	v.p.ep = v.p.sp = v.p.p = iplCreateTileInfo(MiddleOne_19,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int));
	break;
	}
	++nb;
	nb %= 20;

	return v;
}

static val_t eic_iplSetBorderMode(void)
{
	val_t v;

	iplSetBorderMode(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),int),
		arg(2,getargs(),int),
		arg(3,getargs(),int));

	return v;
}

static val_t eic_iplAnd(void)
{
	val_t v;

	iplAnd(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplDCT2D(void)
{
	val_t v;

	iplDCT2D(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int));

	return v;
}

static val_t eic_iplDecimateExt(void)
{
	val_t v;

	iplDecimateExt(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int),
		arg(4,getargs(),int),
		arg(5,getargs(),int),
		arg(6,getargs(),int),
		arg(7,getargs(),int),
		arg(8,getargs(),int));

	return v;
}

static val_t eic_iplAddSFP(void)
{
	val_t v;

	iplAddSFP(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),float));

	return v;
}

static val_t eic_iplEqualS(void)
{
	val_t v;

	v.ival = iplEqualS(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),int),
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplMaxFilter(void)
{
	val_t v;

	iplMaxFilter(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int),
		arg(4,getargs(),int),
		arg(5,getargs(),int));

	return v;
}

static val_t eic_iplCreateConvKernelChar(void)
{
	val_t v;

	v.p.ep = v.p.sp = v.p.p = iplCreateConvKernelChar(arg(0,getargs(),int),
		arg(1,getargs(),int),
		arg(2,getargs(),int),
		arg(3,getargs(),int),
		arg(4,getargs(),ptr_t).p,
		arg(5,getargs(),int));

	return v;
}

static val_t eic_iplXor(void)
{
	val_t v;

	iplXor(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplDeleteColorTwist(void)
{
	val_t v;

	iplDeleteColorTwist(arg(0,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplDilate(void)
{
	val_t v;

	iplDilate(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int));

	return v;
}

static val_t eic_iplCreateConvKernelFP(void)
{
	val_t v;

	v.p.ep = v.p.sp = v.p.p = iplCreateConvKernelFP(arg(0,getargs(),int),
		arg(1,getargs(),int),
		arg(2,getargs(),int),
		arg(3,getargs(),int),
		arg(4,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplRotate(void)
{
	val_t v;
    double d2 = arg(2,getargs(),double);
    double d3 = arg(3,getargs(),double);
    double d4 = arg(4,getargs(),double);

	iplRotate(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),double),
		arg(3,getargs(),double),
		arg(4,getargs(),double),
		arg(5,getargs(),int));

	return v;
}

static val_t eic_iplApplyColorTwist(void)
{
	val_t v;

	iplApplyColorTwist(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int));

	return v;
}

static val_t eic_iplSubtractS(void)
{
	val_t v;

	iplSubtractS(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int));

	return v;
}

static val_t eic_iplMirror(void)
{
	val_t v;

	iplMirror(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int));

	return v;
}

static val_t eic_iplMpyRCPack2D(void)
{
	val_t v;

	iplMpyRCPack2D(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplAndS(void)
{
	val_t v;

	iplAndS(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),unsigned));

	return v;
}

static val_t eic_iplLShiftS(void)
{
	val_t v;

	iplLShiftS(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),unsigned));

	return v;
}

static val_t eic_iplConvertToDIBSep(void)
{
	val_t v;

	v.ival = iplConvertToDIBSep(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int),
		arg(4,getargs(),int));

	return v;
}

static val_t eic_iplContrastStretch(void)
{
	val_t v;

	iplContrastStretch(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplRGB2LUV(void)
{
	val_t v;

	iplRGB2LUV(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplGetCentralMoment(void)
{
	val_t v;

	v.dval = iplGetCentralMoment(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),int),
		arg(2,getargs(),int));

	return v;
}

static val_t eic_iplMultiply(void)
{
	val_t v;

	iplMultiply(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplExchange(void)
{
	val_t v;

	iplExchange(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p);

	return v;
}

static void * EiC_Cfunc_20 = NULL;
static void  __stdcall MiddleOne_20(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_20, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_20, int ,x1);
    setArg(2, EiC_Cfunc_20, int ,x2);
    setArg(3, EiC_Cfunc_20, int ,x3);

    EiC_callBack(EiC_Cfunc_20);
}

static void * EiC_Cfunc_21 = NULL;
static void  __stdcall MiddleOne_21(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_21, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_21, int ,x1);
    setArg(2, EiC_Cfunc_21, int ,x2);
    setArg(3, EiC_Cfunc_21, int ,x3);

    EiC_callBack(EiC_Cfunc_21);
}

static void * EiC_Cfunc_22 = NULL;
static void  __stdcall MiddleOne_22(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_22, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_22, int ,x1);
    setArg(2, EiC_Cfunc_22, int ,x2);
    setArg(3, EiC_Cfunc_22, int ,x3);

    EiC_callBack(EiC_Cfunc_22);
}

static void * EiC_Cfunc_23 = NULL;
static void  __stdcall MiddleOne_23(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_23, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_23, int ,x1);
    setArg(2, EiC_Cfunc_23, int ,x2);
    setArg(3, EiC_Cfunc_23, int ,x3);

    EiC_callBack(EiC_Cfunc_23);
}

static void * EiC_Cfunc_24 = NULL;
static void  __stdcall MiddleOne_24(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_24, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_24, int ,x1);
    setArg(2, EiC_Cfunc_24, int ,x2);
    setArg(3, EiC_Cfunc_24, int ,x3);

    EiC_callBack(EiC_Cfunc_24);
}

static void * EiC_Cfunc_25 = NULL;
static void  __stdcall MiddleOne_25(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_25, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_25, int ,x1);
    setArg(2, EiC_Cfunc_25, int ,x2);
    setArg(3, EiC_Cfunc_25, int ,x3);

    EiC_callBack(EiC_Cfunc_25);
}

static void * EiC_Cfunc_26 = NULL;
static void  __stdcall MiddleOne_26(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_26, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_26, int ,x1);
    setArg(2, EiC_Cfunc_26, int ,x2);
    setArg(3, EiC_Cfunc_26, int ,x3);

    EiC_callBack(EiC_Cfunc_26);
}

static void * EiC_Cfunc_27 = NULL;
static void  __stdcall MiddleOne_27(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_27, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_27, int ,x1);
    setArg(2, EiC_Cfunc_27, int ,x2);
    setArg(3, EiC_Cfunc_27, int ,x3);

    EiC_callBack(EiC_Cfunc_27);
}

static void * EiC_Cfunc_28 = NULL;
static void  __stdcall MiddleOne_28(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_28, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_28, int ,x1);
    setArg(2, EiC_Cfunc_28, int ,x2);
    setArg(3, EiC_Cfunc_28, int ,x3);

    EiC_callBack(EiC_Cfunc_28);
}

static void * EiC_Cfunc_29 = NULL;
static void  __stdcall MiddleOne_29(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_29, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_29, int ,x1);
    setArg(2, EiC_Cfunc_29, int ,x2);
    setArg(3, EiC_Cfunc_29, int ,x3);

    EiC_callBack(EiC_Cfunc_29);
}

static void * EiC_Cfunc_30 = NULL;
static void  __stdcall MiddleOne_30(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_30, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_30, int ,x1);
    setArg(2, EiC_Cfunc_30, int ,x2);
    setArg(3, EiC_Cfunc_30, int ,x3);

    EiC_callBack(EiC_Cfunc_30);
}

static void * EiC_Cfunc_31 = NULL;
static void  __stdcall MiddleOne_31(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_31, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_31, int ,x1);
    setArg(2, EiC_Cfunc_31, int ,x2);
    setArg(3, EiC_Cfunc_31, int ,x3);

    EiC_callBack(EiC_Cfunc_31);
}

static void * EiC_Cfunc_32 = NULL;
static void  __stdcall MiddleOne_32(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_32, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_32, int ,x1);
    setArg(2, EiC_Cfunc_32, int ,x2);
    setArg(3, EiC_Cfunc_32, int ,x3);

    EiC_callBack(EiC_Cfunc_32);
}

static void * EiC_Cfunc_33 = NULL;
static void  __stdcall MiddleOne_33(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_33, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_33, int ,x1);
    setArg(2, EiC_Cfunc_33, int ,x2);
    setArg(3, EiC_Cfunc_33, int ,x3);

    EiC_callBack(EiC_Cfunc_33);
}

static void * EiC_Cfunc_34 = NULL;
static void __stdcall __stdcall MiddleOne_34(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_34, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_34, int ,x1);
    setArg(2, EiC_Cfunc_34, int ,x2);
    setArg(3, EiC_Cfunc_34, int ,x3);

    EiC_callBack(EiC_Cfunc_34);
}

static void * EiC_Cfunc_35 = NULL;
static void  __stdcall MiddleOne_35(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_35, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_35, int ,x1);
    setArg(2, EiC_Cfunc_35, int ,x2);
    setArg(3, EiC_Cfunc_35, int ,x3);

    EiC_callBack(EiC_Cfunc_35);
}

static void * EiC_Cfunc_36 = NULL;
static void  __stdcall MiddleOne_36(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_36, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_36, int ,x1);
    setArg(2, EiC_Cfunc_36, int ,x2);
    setArg(3, EiC_Cfunc_36, int ,x3);

    EiC_callBack(EiC_Cfunc_36);
}

static void * EiC_Cfunc_37 = NULL;
static void  __stdcall MiddleOne_37(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_37, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_37, int ,x1);
    setArg(2, EiC_Cfunc_37, int ,x2);
    setArg(3, EiC_Cfunc_37, int ,x3);

    EiC_callBack(EiC_Cfunc_37);
}

static void * EiC_Cfunc_38 = NULL;
static void  __stdcall MiddleOne_38(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_38, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_38, int ,x1);
    setArg(2, EiC_Cfunc_38, int ,x2);
    setArg(3, EiC_Cfunc_38, int ,x3);

    EiC_callBack(EiC_Cfunc_38);
}

static void * EiC_Cfunc_39 = NULL;
static void  __stdcall MiddleOne_39(const IplImage *x0,  int x1, int x2, int x3 )
{
    setArg(0, EiC_Cfunc_39, const IplImage * ,x0);
    setArg(1, EiC_Cfunc_39, int ,x1);
    setArg(2, EiC_Cfunc_39, int ,x2);
    setArg(3, EiC_Cfunc_39, int ,x3);

    EiC_callBack(EiC_Cfunc_39);
}

static val_t eic_iplSetTileInfo(void)
{
	val_t v;
	static int nb = 0;

	switch(nb)
	{
	case 0 :
	EiC_Cfunc_20 = arg(1,getargs(),ptr_t).p;
	iplSetTileInfo(arg(0,getargs(),ptr_t).p,
		MiddleOne_20,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int),
		arg(4,getargs(),int));
	break;
	case 1 :
	EiC_Cfunc_21 = arg(1,getargs(),ptr_t).p;
	iplSetTileInfo(arg(0,getargs(),ptr_t).p,
		MiddleOne_21,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int),
		arg(4,getargs(),int));
	break;
	case 2 :
	EiC_Cfunc_22 = arg(1,getargs(),ptr_t).p;
	iplSetTileInfo(arg(0,getargs(),ptr_t).p,
		MiddleOne_22,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int),
		arg(4,getargs(),int));
	break;
	case 3 :
	EiC_Cfunc_23 = arg(1,getargs(),ptr_t).p;
	iplSetTileInfo(arg(0,getargs(),ptr_t).p,
		MiddleOne_23,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int),
		arg(4,getargs(),int));
	break;
	case 4 :
	EiC_Cfunc_24 = arg(1,getargs(),ptr_t).p;
	iplSetTileInfo(arg(0,getargs(),ptr_t).p,
		MiddleOne_24,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int),
		arg(4,getargs(),int));
	break;
	case 5 :
	EiC_Cfunc_25 = arg(1,getargs(),ptr_t).p;
	iplSetTileInfo(arg(0,getargs(),ptr_t).p,
		MiddleOne_25,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int),
		arg(4,getargs(),int));
	break;
	case 6 :
	EiC_Cfunc_26 = arg(1,getargs(),ptr_t).p;
	iplSetTileInfo(arg(0,getargs(),ptr_t).p,
		MiddleOne_26,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int),
		arg(4,getargs(),int));
	break;
	case 7 :
	EiC_Cfunc_27 = arg(1,getargs(),ptr_t).p;
	iplSetTileInfo(arg(0,getargs(),ptr_t).p,
		MiddleOne_27,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int),
		arg(4,getargs(),int));
	break;
	case 8 :
	EiC_Cfunc_28 = arg(1,getargs(),ptr_t).p;
	iplSetTileInfo(arg(0,getargs(),ptr_t).p,
		MiddleOne_28,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int),
		arg(4,getargs(),int));
	break;
	case 9 :
	EiC_Cfunc_29 = arg(1,getargs(),ptr_t).p;
	iplSetTileInfo(arg(0,getargs(),ptr_t).p,
		MiddleOne_29,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int),
		arg(4,getargs(),int));
	break;
	case 10 :
	EiC_Cfunc_30 = arg(1,getargs(),ptr_t).p;
	iplSetTileInfo(arg(0,getargs(),ptr_t).p,
		MiddleOne_30,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int),
		arg(4,getargs(),int));
	break;
	case 11 :
	EiC_Cfunc_31 = arg(1,getargs(),ptr_t).p;
	iplSetTileInfo(arg(0,getargs(),ptr_t).p,
		MiddleOne_31,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int),
		arg(4,getargs(),int));
	break;
	case 12 :
	EiC_Cfunc_32 = arg(1,getargs(),ptr_t).p;
	iplSetTileInfo(arg(0,getargs(),ptr_t).p,
		MiddleOne_32,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int),
		arg(4,getargs(),int));
	break;
	case 13 :
	EiC_Cfunc_33 = arg(1,getargs(),ptr_t).p;
	iplSetTileInfo(arg(0,getargs(),ptr_t).p,
		MiddleOne_33,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int),
		arg(4,getargs(),int));
	break;
	case 14 :
	EiC_Cfunc_34 = arg(1,getargs(),ptr_t).p;
	iplSetTileInfo(arg(0,getargs(),ptr_t).p,
		MiddleOne_34,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int),
		arg(4,getargs(),int));
	break;
	case 15 :
	EiC_Cfunc_35 = arg(1,getargs(),ptr_t).p;
	iplSetTileInfo(arg(0,getargs(),ptr_t).p,
		MiddleOne_35,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int),
		arg(4,getargs(),int));
	break;
	case 16 :
	EiC_Cfunc_36 = arg(1,getargs(),ptr_t).p;
	iplSetTileInfo(arg(0,getargs(),ptr_t).p,
		MiddleOne_36,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int),
		arg(4,getargs(),int));
	break;
	case 17 :
	EiC_Cfunc_37 = arg(1,getargs(),ptr_t).p;
	iplSetTileInfo(arg(0,getargs(),ptr_t).p,
		MiddleOne_37,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int),
		arg(4,getargs(),int));
	break;
	case 18 :
	EiC_Cfunc_38 = arg(1,getargs(),ptr_t).p;
	iplSetTileInfo(arg(0,getargs(),ptr_t).p,
		MiddleOne_38,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int),
		arg(4,getargs(),int));
	break;
	case 19 :
	EiC_Cfunc_39 = arg(1,getargs(),ptr_t).p;
	iplSetTileInfo(arg(0,getargs(),ptr_t).p,
		MiddleOne_39,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int),
		arg(4,getargs(),int));
	break;
	}
	++nb;
	nb %= 20;

	return v;
}

static val_t eic_iplOr(void)
{
	val_t v;

	iplOr(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplConvolveSep2D(void)
{
	val_t v;

	iplConvolveSep2D(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplWarpPerspective(void)
{
	val_t v;

	iplWarpPerspective(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int),
		arg(4,getargs(),int));

	return v;
}

static val_t eic_iplConvertToDIB(void)
{
	val_t v;

	iplConvertToDIB(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int));

	return v;
}

static val_t eic_iplXYZ2RGB(void)
{
	val_t v;

	iplXYZ2RGB(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplCreateImageJaehne(void)
{
	val_t v;

	v.p.ep = v.p.sp = v.p.p = iplCreateImageJaehne(arg(0,getargs(),int),
		arg(1,getargs(),int),
		arg(2,getargs(),int));

	return v;
}

static val_t eic_iplYCC2RGB(void)
{
	val_t v;

	iplYCC2RGB(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplSetROI(void)
{
	val_t v;

	iplSetROI(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),int),
		arg(2,getargs(),int),
		arg(3,getargs(),int),
		arg(4,getargs(),int),
		arg(5,getargs(),int));

	return v;
}

static val_t eic_iplGreater(void)
{
	val_t v;

	v.ival = iplGreater(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplCreateConvKernel(void)
{
	val_t v;

	v.p.ep = v.p.sp = v.p.p = iplCreateConvKernel(arg(0,getargs(),int),
		arg(1,getargs(),int),
		arg(2,getargs(),int),
		arg(3,getargs(),int),
		arg(4,getargs(),ptr_t).p,
		arg(5,getargs(),int));

	return v;
}

static val_t eic_iplEqualSFP(void)
{
	val_t v;

	v.ival = iplEqualSFP(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),float),
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplLess(void)
{
	val_t v;

	v.ival = iplLess(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplColorToGray(void)
{
	val_t v;

	iplColorToGray(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplCcsFft2D(void)
{
	val_t v;

	iplCcsFft2D(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int));

	return v;
}

static val_t eic_iplXorS(void)
{
	val_t v;

	iplXorS(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),unsigned));

	return v;
}

static val_t eic_iplCentralMoment(void)
{
	val_t v;

	v.dval = iplCentralMoment(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),int),
		arg(2,getargs(),int));

	return v;
}

static val_t eic_iplRemap(void)
{
	val_t v;

	iplRemap(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),ptr_t).p,
		arg(4,getargs(),int));

	return v;
}

static val_t eic_iplErode(void)
{
	val_t v;

	iplErode(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int));

	return v;
}

static val_t eic_iplEqualSFPEps(void)
{
	val_t v;

	v.ival = iplEqualSFPEps(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),float),
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),float));

	return v;
}

static val_t eic_iplGetPixel(void)
{
	val_t v;

	iplGetPixel(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),int),
		arg(2,getargs(),int),
		arg(3,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplGetBilinearTransform(void)
{
	val_t v;

	iplGetBilinearTransform(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplSetColorTwist(void)
{
	val_t v;

	iplSetColorTwist(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int));

	return v;
}

static val_t eic_iplTranslateDIB(void)
{
	val_t v;

	v.p.ep = v.p.sp = v.p.p = iplTranslateDIB(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplDeleteTileInfo(void)
{
	val_t v;

	iplDeleteTileInfo(arg(0,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplColorTwistFP(void)
{
	val_t v;

	v.ival = iplColorTwistFP(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplNormalizedCentralMoment(void)
{
	val_t v;

	v.dval = iplNormalizedCentralMoment(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),int),
		arg(2,getargs(),int));

	return v;
}

static val_t eic_iplShear(void)
{
	val_t v;

	iplShear(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),double),
		arg(3,getargs(),double),
		arg(4,getargs(),double),
		arg(5,getargs(),double),
		arg(6,getargs(),int));

	return v;
}

static val_t eic_iplConvolve2D(void)
{
	val_t v;

	iplConvolve2D(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int),
		arg(4,getargs(),int));

	return v;
}

static val_t eic_iplDeleteConvKernelFP(void)
{
	val_t v;

	iplDeleteConvKernelFP(arg(0,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplGetConvKernel(void)
{
	val_t v;

	iplGetConvKernel(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),ptr_t).p,
		arg(4,getargs(),ptr_t).p,
		arg(5,getargs(),ptr_t).p,
		arg(6,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplGetPerspectiveTransform(void)
{
	val_t v;

	iplGetPerspectiveTransform(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplWarpAffine(void)
{
	val_t v;

	iplWarpAffine(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int));

	return v;
}

static val_t eic_iplMultiplyS(void)
{
	val_t v;

	iplMultiplyS(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int));

	return v;
}

static val_t eic_iplEqual(void)
{
	val_t v;

	v.ival = iplEqual(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplGetSpatialMoment(void)
{
	val_t v;

	v.dval = iplGetSpatialMoment(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),int),
		arg(2,getargs(),int));

	return v;
}

static val_t eic_iplOrS(void)
{
	val_t v;

	iplOrS(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),unsigned));

	return v;
}

static val_t eic_iplWarpPerspectiveQ(void)
{
	val_t v;

	iplWarpPerspectiveQ(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int),
		arg(4,getargs(),int));

	return v;
}

static val_t eic_iplSubtract(void)
{
	val_t v;

	iplSubtract(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplGetNormalizedCentralMoment(void)
{
	val_t v;

	v.dval = iplGetNormalizedCentralMoment(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),int),
		arg(2,getargs(),int));

	return v;
}

static val_t eic_iplComputeHisto(void)
{
	val_t v;

	iplComputeHisto(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplCreateColorTwist(void)
{
	val_t v;

	v.p.ep = v.p.sp = v.p.p = iplCreateColorTwist(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),int));

	return v;
}

static val_t eic_iplSubtractSFP(void)
{
	val_t v;

	iplSubtractSFP(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),float),
		arg(3,getargs(),int));

	return v;
}

static val_t eic_iplGreaterSFP(void)
{
	val_t v;

	v.ival = iplGreaterSFP(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),float),
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplRGB2YCrCb(void)
{
	val_t v;

	iplRGB2YCrCb(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplDeleteROI(void)
{
	val_t v;

	iplDeleteROI(arg(0,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplGrayToColor(void)
{
	val_t v;

	iplGrayToColor(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),float),
		arg(3,getargs(),float),
		arg(4,getargs(),float));

	return v;
}

static val_t eic_iplConvert(void)
{
	val_t v;

	iplConvert(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplMinMaxFP(void)
{
	val_t v;

	v.ival = iplMinMaxFP(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplHSV2RGB(void)
{
	val_t v;

	iplHSV2RGB(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplMultiplyScale(void)
{
	val_t v;

	iplMultiplyScale(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplHistoEqualize(void)
{
	val_t v;

	iplHistoEqualize(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplYCrCb2RGB(void)
{
	val_t v;

	iplYCrCb2RGB(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplSpatialMoment(void)
{
	val_t v;

	v.dval = iplSpatialMoment(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),int),
		arg(2,getargs(),int));

	return v;
}

static val_t eic_iplGreaterS(void)
{
	val_t v;

	v.ival = iplGreaterS(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),int),
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplEqualFPEps(void)
{
	val_t v;

	v.ival = iplEqualFPEps(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),float));

	return v;
}

static val_t eic_iplOpen(void)
{
	val_t v;

	iplOpen(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int));

	return v;
}

static val_t eic_iplGetRotateShift(void)
{
	val_t v;

	iplGetRotateShift(arg(0,getargs(),double),
		arg(1,getargs(),double),
		arg(2,getargs(),double),
		arg(3,getargs(),ptr_t).p,
		arg(4,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplConvertFromDIBSep(void)
{
	val_t v;

	v.ival = iplConvertFromDIBSep(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplDeallocateHeader(void)
{
	val_t v;

	iplDeallocateHeader(arg(0,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplZoom(void)
{
	val_t v;

	iplZoom(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int),
		arg(4,getargs(),int),
		arg(5,getargs(),int),
		arg(6,getargs(),int));

	return v;
}

static val_t eic_iplConvertFromDIB(void)
{
	val_t v;

	iplConvertFromDIB(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplLessS(void)
{
	val_t v;

	v.ival = iplLessS(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),int),
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplGetPerspectiveQuad(void)
{
	val_t v;

	iplGetPerspectiveQuad(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplConvolve2DFP(void)
{
	val_t v;

	iplConvolve2DFP(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int),
		arg(4,getargs(),int));

	return v;
}

static val_t eic_iplRGB2YUV(void)
{
	val_t v;

	iplRGB2YUV(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplAlphaCompositeC(void)
{
	val_t v;

	iplAlphaCompositeC(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int),
		arg(4,getargs(),int),
		arg(5,getargs(),int),
		arg(6,getargs(),int),
		arg(7,getargs(),int));

	return v;
}

static val_t eic_iplLessSFP(void)
{
	val_t v;

	v.ival = iplLessSFP(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),float),
		arg(2,getargs(),ptr_t).p);

	return v;
}

static val_t eic_iplWarpBilinearQ(void)
{
	val_t v;

	iplWarpBilinearQ(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),ptr_t).p,
		arg(3,getargs(),int),
		arg(4,getargs(),int));

	return v;
}

static val_t eic_iplReduceBits(void)
{
	val_t v;

	iplReduceBits(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p,
		arg(2,getargs(),int),
		arg(3,getargs(),int),
		arg(4,getargs(),int));

	return v;
}

static val_t eic_iplNormalizedSpatialMoment(void)
{
	val_t v;

	v.dval = iplNormalizedSpatialMoment(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),int),
		arg(2,getargs(),int));

	return v;
}

static val_t eic_iplAllocateImage(void)
{
	val_t v;

	iplAllocateImage(arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),int),
		arg(2,getargs(),int));

	return v;
}

static val_t eic_iplCreateImageHeader(void)
{
	val_t v;

	v.p.ep = v.p.sp = v.p.p = iplCreateImageHeader(arg(0,getargs(),int),
		arg(1,getargs(),int),
		arg(2,getargs(),int),
		arg(3,getargs(),ptr_t).p,
		arg(4,getargs(),ptr_t).p,
		arg(5,getargs(),int),
		arg(6,getargs(),int),
		arg(7,getargs(),int),
		arg(8,getargs(),int),
		arg(9,getargs(),int),
		arg(10,getargs(),ptr_t).p,
		arg(11,getargs(),ptr_t).p,
		arg(12,getargs(),ptr_t).p,
		arg(13,getargs(),ptr_t).p);

	return v;
}

/**********************************/

void module_ipl()
{
}

/**********************************/

char* eic_function_names[] = {
    "iplCreateImageHeader", "iplAllocateImage", "iplNormalizedSpatialMoment", "iplReduceBits", "iplWarpBilinearQ", 
    "iplLessSFP", "iplAlphaCompositeC", "iplRGB2YUV", "iplConvolve2DFP", "iplGetPerspectiveQuad", 
    "iplLessS", "iplConvertFromDIB", "iplZoom", "iplDeallocateHeader", "iplConvertFromDIBSep", 
    "iplGetRotateShift", "iplOpen", "iplEqualFPEps", "iplGreaterS", "iplSpatialMoment", 
    "iplYCrCb2RGB", "iplHistoEqualize", "iplMultiplyScale", "iplHSV2RGB", "iplMinMaxFP", 
    "iplConvert", "iplGrayToColor", "iplDeleteROI", "iplRGB2YCrCb", "iplGreaterSFP", 
    "iplSubtractSFP", "iplCreateColorTwist", "iplComputeHisto", "iplGetNormalizedCentralMoment", "iplSubtract", 
    "iplWarpPerspectiveQ", "iplOrS", "iplGetSpatialMoment", "iplEqual", "iplMultiplyS", 
    "iplWarpAffine", "iplGetPerspectiveTransform", "iplGetConvKernel", "iplDeleteConvKernelFP", "iplConvolve2D", 
    "iplShear", "iplNormalizedCentralMoment", "iplColorTwistFP", "iplDeleteTileInfo", "iplTranslateDIB", 
    "iplSetColorTwist", "iplGetBilinearTransform", "iplGetPixel", "iplEqualSFPEps", "iplErode", 
    "iplRemap", "iplCentralMoment", "iplXorS", "iplCcsFft2D", "iplColorToGray", 
    "iplLess", "iplEqualSFP", "iplCreateConvKernel", "iplGreater", "iplSetROI", 
    "iplYCC2RGB", "iplCreateImageJaehne", "iplXYZ2RGB", "iplConvertToDIB", "iplWarpPerspective", 
    "iplConvolveSep2D", "iplOr", "iplSetTileInfo", "iplExchange", "iplMultiply", 
    "iplGetCentralMoment", "iplRGB2LUV", "iplContrastStretch", "iplConvertToDIBSep", "iplLShiftS", 
    "iplAndS", "iplMpyRCPack2D", "iplMirror", "iplSubtractS", "iplApplyColorTwist", 
    "iplRotate", "iplCreateConvKernelFP", "iplDilate", "iplDeleteColorTwist", "iplXor", 
    "iplCreateConvKernelChar", "iplMaxFilter", "iplEqualS", "iplAddSFP", "iplDecimateExt", 
    "iplDCT2D", "iplAnd", "iplSetBorderMode", "iplCreateTileInfo", "iplDeallocateImage", 
    "iplCopy", "iplRGB2HSV", "iplYUV2RGB", "iplRShiftS", "iplScale", 
    "iplAbs", "iplGetConvKernelChar", "iplMultiplySFP", "iplPreMultiplyAlpha", "iplSetFP", 
    "iplResize", "iplGetBilinearBound", "iplPutPixel", "iplAlphaComposite", "iplMinFilter", 
    "iplHLS2RGB", "iplAllocateImageFP", "iplDeleteConvKernel", "iplGetAffineBound", "iplConvolveSep2DFP", 
    "iplAdd", "iplGetConvKernelFP", "iplGetNormalizedSpatialMoment", "iplDeallocate", "iplClose", 
    "iplScaleFP", "iplMedianFilter", "iplWarpBilinear", "iplCloneImage", "iplSquare", 
    "iplBlur", "iplRGB2HLS", "iplFixedFilter", "iplRealFft2D", "iplCreateROI", 
    "iplMultiplySScale", "iplThreshold", "iplMoments", "iplAddS", "iplRGB2XYZ", 
    "iplNorm", "iplGetPerspectiveBound", "iplGetBilinearQuad", "iplBitonalToGray", "iplLUV2RGB", 
    "iplDecimate", "iplSet", "iplNot", "iplGetAffineQuad", "iplGetAffineTransform"};

val_t (*eic_functions[])(void) = {    
    eic_iplCreateImageHeader, eic_iplAllocateImage, eic_iplNormalizedSpatialMoment, eic_iplReduceBits, eic_iplWarpBilinearQ, 
    eic_iplLessSFP, eic_iplAlphaCompositeC, eic_iplRGB2YUV, eic_iplConvolve2DFP, eic_iplGetPerspectiveQuad, 
    eic_iplLessS, eic_iplConvertFromDIB, eic_iplZoom, eic_iplDeallocateHeader, eic_iplConvertFromDIBSep, 
    eic_iplGetRotateShift, eic_iplOpen, eic_iplEqualFPEps, eic_iplGreaterS, eic_iplSpatialMoment, 
    eic_iplYCrCb2RGB, eic_iplHistoEqualize, eic_iplMultiplyScale, eic_iplHSV2RGB, eic_iplMinMaxFP, 
    eic_iplConvert, eic_iplGrayToColor, eic_iplDeleteROI, eic_iplRGB2YCrCb, eic_iplGreaterSFP, 
    eic_iplSubtractSFP, eic_iplCreateColorTwist, eic_iplComputeHisto, eic_iplGetNormalizedCentralMoment, eic_iplSubtract, 
    eic_iplWarpPerspectiveQ, eic_iplOrS, eic_iplGetSpatialMoment, eic_iplEqual, eic_iplMultiplyS, 
    eic_iplWarpAffine, eic_iplGetPerspectiveTransform, eic_iplGetConvKernel, eic_iplDeleteConvKernelFP, eic_iplConvolve2D, 
    eic_iplShear, eic_iplNormalizedCentralMoment, eic_iplColorTwistFP, eic_iplDeleteTileInfo, eic_iplTranslateDIB, 
    eic_iplSetColorTwist, eic_iplGetBilinearTransform, eic_iplGetPixel, eic_iplEqualSFPEps, eic_iplErode, 
    eic_iplRemap, eic_iplCentralMoment, eic_iplXorS, eic_iplCcsFft2D, eic_iplColorToGray, 
    eic_iplLess, eic_iplEqualSFP, eic_iplCreateConvKernel, eic_iplGreater, eic_iplSetROI, 
    eic_iplYCC2RGB, eic_iplCreateImageJaehne, eic_iplXYZ2RGB, eic_iplConvertToDIB, eic_iplWarpPerspective, 
    eic_iplConvolveSep2D, eic_iplOr, eic_iplSetTileInfo, eic_iplExchange, eic_iplMultiply, 
    eic_iplGetCentralMoment, eic_iplRGB2LUV, eic_iplContrastStretch, eic_iplConvertToDIBSep, eic_iplLShiftS, 
    eic_iplAndS, eic_iplMpyRCPack2D, eic_iplMirror, eic_iplSubtractS, eic_iplApplyColorTwist, 
    eic_iplRotate, eic_iplCreateConvKernelFP, eic_iplDilate, eic_iplDeleteColorTwist, eic_iplXor, 
    eic_iplCreateConvKernelChar, eic_iplMaxFilter, eic_iplEqualS, eic_iplAddSFP, eic_iplDecimateExt, 
    eic_iplDCT2D, eic_iplAnd, eic_iplSetBorderMode, eic_iplCreateTileInfo, eic_iplDeallocateImage, 
    eic_iplCopy, eic_iplRGB2HSV, eic_iplYUV2RGB, eic_iplRShiftS, eic_iplScale, 
    eic_iplAbs, eic_iplGetConvKernelChar, eic_iplMultiplySFP, eic_iplPreMultiplyAlpha, eic_iplSetFP, 
    eic_iplResize, eic_iplGetBilinearBound, eic_iplPutPixel, eic_iplAlphaComposite, eic_iplMinFilter, 
    eic_iplHLS2RGB, eic_iplAllocateImageFP, eic_iplDeleteConvKernel, eic_iplGetAffineBound, eic_iplConvolveSep2DFP, 
    eic_iplAdd, eic_iplGetConvKernelFP, eic_iplGetNormalizedSpatialMoment, eic_iplDeallocate, eic_iplClose, 
    eic_iplScaleFP, eic_iplMedianFilter, eic_iplWarpBilinear, eic_iplCloneImage, eic_iplSquare, 
    eic_iplBlur, eic_iplRGB2HLS, eic_iplFixedFilter, eic_iplRealFft2D, eic_iplCreateROI, 
    eic_iplMultiplySScale, eic_iplThreshold, eic_iplMoments, eic_iplAddS, eic_iplRGB2XYZ, 
    eic_iplNorm, eic_iplGetPerspectiveBound, eic_iplGetBilinearQuad, eic_iplBitonalToGray, eic_iplLUV2RGB, 
    eic_iplDecimate, eic_iplSet, eic_iplNot, eic_iplGetAffineQuad, eic_iplGetAffineTransform};

void GetFunctions(char*** func_names, val_t (***funcs)(void), int* funcs_count)
{
    *func_names = eic_function_names;
    *funcs = eic_functions;
    *funcs_count = sizeof(eic_functions)/sizeof(eic_functions[0]);
}

void PluginGetInfo(plugin_info* info)
{
    strcpy(info->name, "IPL 2.1");
    strcpy(info->library_path, "ipl.dll");
    info->type = PLUG_WRAPPERS;
}
