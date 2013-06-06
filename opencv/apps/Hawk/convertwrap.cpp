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
//M*/#include "stdafx.h"
#include <stdlib.h>
#include <varargs.h>
#include <limits.h>

extern "C"
{
#include "CVEiCL\EiC\src\eic.h"
#include "CVEiCL\EiC\src\typemod.h"
//#include "CVEiCL\EiC\src\datastruct.h"
#include "CVEiCL\EiC\src\global.h"
#include "CVEiCL\EiC\src\func.h"

#include "wrap.h"

#ifdef WIN32
#undef WIN32
#include "convert.h"
#define WIN32
#else
#include "convert.h"
#endif
#include "cv.h"

symentry_t * EiC_lookup(char nspace, char *id);
}

#ifdef malloc /* This macros is defined in eic.h */
#undef malloc
#endif /* malloc */
#ifdef realloc
#undef realloc
#endif /* realloc */
#ifdef free
#undef free
#endif /* free */


#include "hawkwrap.h"

static jmp_buf* hawk_mark = NULL;
static errlevel_t hawk_errlevel = unsafe;


static void (*avi_callback)(IPLIMAGE) = NULL;
static void eic_avi_play_callback(void* image)
{
    if(!avi_callback)
    {
        return;
    }
    
    setArg(0, (code_t*)avi_callback, void*, image);
    EiC_callBack(avi_callback);
}

static val_t eic_play_avi(void)
{
	val_t v;

    avi_callback = (void(*)(IPLIMAGE))arg(2,getargs(),ptr_t).p;
	v.ival = play_avi((char*)arg(0,getargs(),ptr_t).p,
        (char*)arg(1,getargs(),ptr_t).p,
        (void(*)(IPLIMAGE))eic_avi_play_callback);
    avi_callback = NULL;

	return v;
}

static void (*ds_callback)(IPLIMAGE) = NULL;
static void eic_ds_play_callback(void* image)
{
    if(!ds_callback)
    {
        return;
    }
    
    setArg(0, (code_t*)ds_callback, void*, image);
    EiC_callBack(ds_callback);
}

static val_t eic_play_ds(void)
{
	val_t v;

    ds_callback = (void(*)(IPLIMAGE))arg(0,getargs(),ptr_t).p;
    v.ival = play_ds((void(*)(IPLIMAGE))(ds_callback ? eic_ds_play_callback : NULL));
    ds_callback = NULL;

	return v;
}

/**********************************/
void set_hawk_mark(jmp_buf* mark)
{
    hawk_mark = mark;
}

void set_hawk_errlevel(errlevel_t level)
{
    hawk_errlevel = level;
}

/**********************************/

val_t eic_universal_wrapper()
{
    val_t v;
    v.ival = 0;

    int pcount = int(arg(2, getargs(), ptr_t).p);
    uni_wrap((stub_f)arg(0, getargs(), ptr_t).p, 
        (int*)arg(1, getargs(), ptr_t).p,
        (char*)(getargs()- 10 - pcount), (int*)arg(3, getargs(), ptr_t).p,
        arg(4, getargs(), ptr_t).p);

    return v;
}

static void (*eic_calc_weights)(float*, int, float*);
void eic_cvFitLine_Weight(float* r, int count, float* w)
{
    setArg(0, (code_t*)eic_calc_weights, float*, r);
    setArg(1, (code_t*)eic_calc_weights, int, count);
    setArg(2, (code_t*)eic_calc_weights, float*, w);
    EiC_callBack(eic_calc_weights);
}

static val_t eic_cvFitLine2D(void)
{
	val_t v;
    v.ival = 0;
    void *p;

    eic_calc_weights = (void (*)(float*, int, float*))arg(3, getargs(), ptr_t).p;
    if(arg(2, getargs(), int) == CV_DIST_USER && eic_calc_weights != NULL)
    {
        p = eic_cvFitLine_Weight;
    }
    else
    {
        p = eic_calc_weights;
    }
    cvFitLine2D((CvPoint2D32f*)arg(0,getargs(),ptr_t).p, 
                arg(1,getargs(),int),
                (CvDisType)arg(2, getargs(),int),
                p,
                arg(4, getargs(),float),
                arg(5, getargs(), float),
                (float*)arg(6,getargs(),ptr_t).p);
    return v;
}

static val_t eic_cvFitLine3D(void)
{
	val_t v;
    v.ival = 0;
    void *p;

    eic_calc_weights = (void (*)(float*, int, float*))arg(3, getargs(), ptr_t).p;
    if(arg(2, getargs(), int) == CV_DIST_USER && eic_calc_weights != NULL)
    {
        p = eic_cvFitLine_Weight;
    }
    else
    {
        p = eic_calc_weights;
    }
    
    cvFitLine3D((CvPoint3D32f*)arg(0,getargs(),ptr_t).p, 
                         arg(1,getargs(),int),
                         (CvDisType)arg(2, getargs(),int),
                         p,
                         arg(4, getargs(),float),
                         arg(5, getargs(), float),
                         (float*)arg(6,getargs(),ptr_t).p);
    return v;
}

static void* eic_cvCalcEMD_Pointer = 0;
float eic_cvCalcEMD_Callback(const float* f1, const float* f2, void* user_param)
{
    setArg(0, (code_t*)eic_cvCalcEMD_Pointer, const float*, f1);
    setArg(1, (code_t*)eic_cvCalcEMD_Pointer, const float*, f2);
    setArg(2, (code_t*)eic_cvCalcEMD_Pointer, void*, user_param);
    EiC_callBack(eic_cvCalcEMD_Pointer);
    return EiC_ReturnValue(float);
}

static val_t eic_cvCalcEMD()
{
    val_t v;
    eic_cvCalcEMD_Pointer = arg(6, getargs(), ptr_t).p;
    v.dval = cvCalcEMD((float*)arg(0, getargs(), ptr_t).p,
        arg(1, getargs(), int),
        (float*)arg(2, getargs(), ptr_t).p,
        arg(3, getargs(), int),
        arg(4, getargs(), int),
        (CvDisType)arg(5, getargs(), int),
        eic_cvCalcEMD_Callback,
        (float*)arg(7, getargs(), ptr_t).p,
        arg(8, getargs(), ptr_t).p);

    return v;
}

void module_convertwrap()
{
    EiC_add_builtinfunc("_Hawk_uniwrap", eic_universal_wrapper);
	EiC_add_builtinfunc("play_avi",eic_play_avi);
    EiC_add_builtinfunc("play_ds", eic_play_ds);
    EiC_add_builtinfunc("cvFitLine2D", eic_cvFitLine2D);
    EiC_add_builtinfunc("cvFitLine3D", eic_cvFitLine3D);
    EiC_add_builtinfunc("cvCalcEMD", eic_cvCalcEMD);
}

/**********************************/

