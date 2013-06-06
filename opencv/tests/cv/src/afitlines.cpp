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

#include <stdlib.h>
#include <math.h>
#include <float.h>

static const int LF_FITLINE2D = 1;
static const int LF_FITLINE3D = 2;
static const int LF_PROJECT = 3;

static char* func_names[] = {"cvFitLine2D", "cvFitLine3D", "cvProject3D"};
static char* test_desc[] = { "Run the line fitting and projection functions"};

int test_dt(void* arg);
int read_image_dims(void);
int read_gen_type(void);

int test_lf(void* arg)
{
    int npoints = 10;
    CvPoint3D32f* points3D = new CvPoint3D32f[npoints];
    CvPoint2D32f* points2D = new CvPoint2D32f[npoints];
    CvDisType distType = CV_DIST_L12;
    float reps = 0.0f, aeps = 0.0f;
    float line[6];
    int ret = 1;
    int type = int(arg);

    /* Initialize the data */
    int i;
    for(i = 0; i < npoints; i++)
    {
        points2D[i].x = float(i);
        points2D[i].y = 0;

        points3D[i].x = float(i);
        points3D[i].y = 0;
        points3D[i].z = 0;
    }

    switch(type)
    {
    case LF_FITLINE2D:
        /* Run the distance transformation function */
        cvFitLine2D(points2D, npoints, distType, 0, reps, aeps, line);
        if(line[0] == 0 || fabs(line[1]/line[0]) > 0.01)
            ret = 0;
        break;

    case LF_FITLINE3D:
        cvFitLine3D(points3D, npoints, distType, 0, reps, aeps, line);
        if(fabs(line[0] - 1.0f) > 0.01f) /* very weak condition */
            ret = 0;
        break;

    case LF_PROJECT:
        cvProject3D(points3D, npoints, points2D, 2, 0);
        for(i = 0; i < npoints; i++)
            if(points3D[i].z != points2D[i].x || points3D[i].x != points2D[i].y)
                ret = 0;
        break;

    default:
        delete points2D;
        delete points3D;
        trsResult(TRS_FAIL, "No such function");
    }
    delete points2D;
    delete points3D;
    if(iplGetErrStatus() < 0)
    {
        return trsResult(TRS_FAIL, "Function returned 'bad argument'");
    }
    else if(!ret)
    {
        return trsResult(TRS_FAIL, "Test check failed!");
    }
    else
    {
        return trsResult(TRS_OK, "No errors");
    }
}

void InitAFitLine(void)
{
    /* Registering test functions */
    trsRegArg(func_names[0], test_desc[0], atsAlgoClass, test_lf, LF_FITLINE2D);
    trsRegArg(func_names[1], test_desc[0], atsAlgoClass, test_lf, LF_FITLINE3D);
    trsRegArg(func_names[2], test_desc[0], atsAlgoClass, test_lf, LF_PROJECT);
} /* InitAFitLine*/

