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

#define F1 -1.0f
#define F2  1.0f
#define MAXDIFF 3
#define MAXPERCENT 1

/* Testing parameters */
static char  FuncName[] = "cvUnDistort";
static char  TestName[] = "Image undistortion function test";
static char TestClass[] = "Algorithm";

static int img_width, img_height, roi_step;

//----------------------------------------------------------------------------------------
void  UnDistortTest_C1 ( uchar* srcImage,
                         uchar* dstImage,
                         int    step,
                         CvSize size,
                         float* intrMatrix,
                         float* distCoeffs,
                         int    interToggle )
{
    const double a1 = 1.f/intrMatrix[0], b1 = 1.f/intrMatrix[4],
                 u0 = intrMatrix[2],     v0 = intrMatrix[5],
                 k1 = distCoeffs[0],     k2 = distCoeffs[1],
                 p1 = distCoeffs[2],     p2 = distCoeffs[3];
    int u, v;

    if( !interToggle )
        for( v=0; v<size.height; v++, dstImage+=step )
        {
            double dv = v-v0;
            double  y = b1*dv;
            double y2 = y*y;
            for( u=0; u<size.width; u++ )
            {
                double   du = u-u0;
                double    x = a1*du;
                double   x2 = x*x;
                double   r2 = x2 + y2;
                double  dst = r2*k1 + r2*r2*k2;
                double dstx = dst + 2.f*p1*y + p2*( r2/x + 2.f*x );
                double dsty = dst + 2.f*p2*x + p1*( r2/y + 2.f*y );
                int      ud = u + cvRound( du*dstx );
                int      vd = v + cvRound( dv*dsty );
                if( ud<0 || ud>=size.width || vd<0 || vd>=size.height )
                    dstImage[u] = 0;
                else 
                    dstImage[u] = srcImage[vd*step + ud];
            }
        }
    else
    {
        int sizex = size.width - 2,  sizey = size.height - 2;
        for( v=0; v<size.height; v++, dstImage+=step )
        {
            double dv = v-v0;
            double  y = b1*dv;
            double y2 = y*y;
            for( u=0; u<size.width; u++ )
            {
                double   du = u-u0;
                double    x = a1*du;
                double   x2 = x*x;
                double   r2 = x2 + y2;
                double  dst = r2*k1 + r2*r2*k2;
                double dstx = dst + 2.f*p1*y + p2*( r2/x + 2.f*x );
                double dsty = dst + 2.f*p2*x + p1*( r2/y + 2.f*y );
                double   eu = du*dstx;
                double   ev = dv*dsty;
                int      ud = cvFloor( eu );
                int      vd = cvFloor( ev );
                eu -= (double)ud;
                ev -= (double)vd;
                ud += u;
                vd += v;

                if( ud<0 || ud>sizex || vd<0 || vd>sizey )
                    dstImage[u] = 0;
                else
                {
                    int    uv = vd*step + ud;
                    double a0 = (double)srcImage[uv];
                    double  a = (double)srcImage[uv+1]      - a0;
                    double  b = (double)srcImage[uv+step]   - a0;
                    double  c = (double)srcImage[uv+step+1] - a0 - a - b;
                    dstImage[u] = (uchar)cvRound( a0 + a*eu + ev*(b + c*eu) );
                }
            }
        }
    }
}
//........................................................................................
void  UnDistortTest_C3 ( uchar* srcImage,
                         uchar* dstImage,
                         int    step,
                         CvSize size,
                         float* intrMatrix,
                         float* distCoeffs,
                         int    interToggle )
{
    const double a1 = 1.f/intrMatrix[0], b1 = 1.f/intrMatrix[4],
                 u0 = intrMatrix[2],     v0 = intrMatrix[5],
                 k1 = distCoeffs[0],     k2 = distCoeffs[1],
                 p1 = distCoeffs[2],     p2 = distCoeffs[3];
    int u, v;

    if( !interToggle )
        for( v=0; v<size.height; v++, dstImage+=step )
        {
            double dv = v-v0;
            double  y = b1*dv;
            double y2 = y*y;
            for( u=0; u<size.width; u++ )
            {
                double   du = u-u0;
                double    x = a1*du;
                double   x2 = x*x;
                double   r2 = x2 + y2;
                double  dst = r2*k1 + r2*r2*k2;
                double dstx = dst + 2.f*p1*y + p2*( r2/x + 2.f*x );
                double dsty = dst + 2.f*p2*x + p1*( r2/y + 2.f*y );
                int     ud = u + cvRound( du*dstx );
                int     vd = v + cvRound( dv*dsty );
                int     u3 = 3*u;
                if( ud<0 || ud>=size.width || vd<0 || vd>=size.height )
                    dstImage[u3] = dstImage[u3+1] = dstImage[u3+2] = 0;
                else
                {
                    int uv = vd*step + 3*ud;
                    dstImage[u3  ] = srcImage[uv  ];
                    dstImage[u3+1] = srcImage[uv+1];
                    dstImage[u3+2] = srcImage[uv+2];
                }
            }
        }
    else
    {
        int sizex = size.width - 2,  sizey = size.height - 2;
        for( v=0; v<size.height; v++, dstImage+=step )
        {
            double dv = v-v0;
            double  y = b1*dv;
            double y2 = y*y;
            for( u=0; u<size.width; u++ )
            {
                double   du = u-u0;
                double    x = a1*du;
                double   x2 = x*x;
                double   r2 = x2 + y2;
                double  dst = r2*k1 + r2*r2*k2;
                double dstx = dst + 2.f*p1*y + p2*( r2/x + 2.f*x );
                double dsty = dst + 2.f*p2*x + p1*( r2/y + 2.f*y );
                double   eu = du*dstx;
                double   ev = dv*dsty;
                int     ud = cvFloor( eu );
                int     vd = cvFloor( ev ), u3 = 3*u;
                eu -= (double)ud;
                ev -= (double)vd;
                ud += u;
                vd += v;

                if( ud<0 || ud>sizex || vd<0 || vd>sizey )
                    dstImage[u3] = dstImage[u3+1] = dstImage[u3+2] = 0;
                else
                {
                    int    uv = vd*step + 3*ud;
                    double a0 = (double)srcImage[uv];
                    double  a = (double)srcImage[uv+3]      - a0;
                    double  b = (double)srcImage[uv+step]   - a0;
                    double  c = (double)srcImage[uv+step+3] - a0 - a - b;
                    dstImage[u3] = (uchar)cvRound( a0 + a*eu + ev*(b + c*eu) );

                    uv++;
                    a0 = (double)srcImage[uv];
                    a  = (double)srcImage[uv+3]      - a0;
                    b  = (double)srcImage[uv+step]   - a0;
                    c  = (double)srcImage[uv+step+3] - a0 - a - b;
                    dstImage[u3+1] = (uchar)cvRound( a0 + a*eu + ev*(b + c*eu) );

                    uv++;
                    a0 = (double)srcImage[uv];
                    a  = (double)srcImage[uv+3]      - a0;
                    b  = (double)srcImage[uv+step]   - a0;
                    c  = (double)srcImage[uv+step+3] - a0 - a - b;
                    dstImage[u3+2] = (uchar)cvRound( a0 + a*eu + ev*(b + c*eu) );
                }
            }
        }
    }
}
//--------------------------------------------------- Test body --------------------------
static int fmaUnDistort( void )
{
    int i, itest, io=0, num_test, err1=0, err2=0, err3=0, err4=0,
        err10=0, err20=0, err30=0, err40=0, err=0, err5, pass=1;
    int n, n3, step, step3;
    int* data;
    IplImage* undistMap = 0;
    uchar *srcImg, *dstImg, *tstImg, *srcImg3, *dstImg3, *tstImg3;
    IplImage *src, *dst, *tst, *src3, *dst3, *tst3;
    float *a, *k, p = 0.f;
    AtsRandState state;
    CvSize size;
    double norm, norm1;

    /* Reading test parameters */
    trsiRead( &img_width,  "320", "width of image" );
    trsiRead( &img_height, "240", "height of image" );
    trsiRead( &roi_step,     "0", "ROI step" );

    n = img_width * img_height;
    size.height = img_height;  size.width = img_width;

    a      = (float*)cvAlloc( sizeof(float) * 9 );
    k      = (float*)cvAlloc( sizeof(float) * 4 );
    //data   = (int*)   icvAlloc(   3*n*sizeof(int) );
    
    src  = cvCreateImage( size, IPL_DEPTH_8U, 1 );
    cvSetImageROI( src, cvRect(0, 0, src->width, src->height) );
    dst  = cvCreateImage( size, IPL_DEPTH_8U, 1 );
    cvSetImageROI( dst, cvRect(0, 0, dst->width, dst->height) );
    tst  = cvCreateImage( size, IPL_DEPTH_8U, 1 );
    cvSetImageROI( tst, cvRect(0, 0, tst->width, tst->height) );
    src3 = cvCreateImage( size, IPL_DEPTH_8U, 3 );
    cvSetImageROI( src3, cvRect(0, 0, src3->width, src3->height) );
    dst3 = cvCreateImage( size, IPL_DEPTH_8U, 3 );
    cvSetImageROI( dst3, cvRect(0, 0, dst3->width, dst3->height) );
    tst3 = cvCreateImage( size, IPL_DEPTH_8U, 3 );
    cvSetImageROI( tst3, cvRect(0, 0, tst3->width, tst3->height) );
    undistMap = cvCreateImage( size, IPL_DEPTH_32S, 3 );

    srcImg  = (uchar*)src->imageData;
    dstImg  = (uchar*)dst->imageData;
    tstImg  = (uchar*)tst->imageData;
    srcImg3 = (uchar*)src3->imageData;
    dstImg3 = (uchar*)dst3->imageData;
    tstImg3 = (uchar*)tst3->imageData;
    data = (int*)undistMap->imageData;

    step = src->widthStep;  step3 = src3->widthStep;
    n = step*img_height;  n3 = step3*img_height;

    atsRandInit( &state, 0, 255, 13 );
    atsbRand8u ( &state, srcImg,  n  );
    atsbRand8u ( &state, srcImg3, n3 );

    a[0] = img_width/3.f;
    a[4] = img_height/2.f;
    a[2] = img_width/2.f;
    a[5] = img_height/2.f;
    k[0] = -0.04f;
    k[1] = 0.004f;
    k[2] = 0.f;
    k[3] = 0.f;

    if(roi_step)
    {
        num_test = (img_width/2 - 3)/roi_step;
        if( num_test > (img_height/2)/roi_step ) num_test = (img_height/2)/roi_step;
    }
    else num_test = 1;
    if( num_test < 1 )  num_test = 1;

begin:
    trsWrite(TW_RUN|TW_CON, "\n  %d pass of 4 :\n", pass);
    for(itest=0; itest<num_test; itest++)
    {
        int ii = (itest*10)/num_test;
        int roi_offset  = roi_step*itest;
        int img_offset  = roi_offset*(step  + 1);
        int img_offset3 = roi_offset*(step3 + 3);
        size.width = img_width - 2*roi_offset;  size.height = img_height - 2*roi_offset;

        src->roi->xOffset  = src->roi->yOffset = roi_offset;
        src->roi->height   = size.height;  src->roi->width = size.width;
        dst->roi->xOffset  = dst->roi->yOffset = roi_offset;
        dst->roi->height   = size.height;  dst->roi->width = size.width;
        tst->roi->xOffset  = tst->roi->yOffset = roi_offset;
        tst->roi->height   = size.height;  tst->roi->width = size.width;
        src3->roi->xOffset = src3->roi->yOffset = roi_offset;
        src3->roi->height  = size.height;  src3->roi->width = size.width;
        dst3->roi->xOffset = dst3->roi->yOffset = roi_offset;
        dst3->roi->height  = size.height;  dst3->roi->width = size.width;
        tst3->roi->xOffset = tst3->roi->yOffset = roi_offset;
        tst3->roi->height  = size.height;  tst3->roi->width = size.width;

/*  8uC1 flavor test without interpolation */
        for(i=0; i<n; i++) dstImg[i] = tstImg[i] = 0;

        cvUnDistortInit ( src, undistMap, a, k, 0 );
        cvUnDistort     ( src, dst, undistMap, 0 );
        UnDistortTest_C1( srcImg + img_offset, tstImg + img_offset, step, size, a, k, 0 );

        if( !img_offset )
        {
            norm = norm1 = 0.0;
            for(i=0; i<n; i++)
            {
                norm  += fabs( dstImg[i] - tstImg[i] );
                norm1 += fabs( tstImg[i] );
            }
            norm /= norm1;
            printf( " 8u C1 without interpolation:  %g\n", norm );
        }

        for(i=0; i<n; i++)
        {
            int d = dstImg[i] - tstImg[i];
            if( d > MAXDIFF || d < -MAXDIFF ) err1++;
        }

        for(i=0; i<n; i++) dstImg[i] = 0;
        cvUnDistortOnce ( src, dst, a, k, 0 );
        //for(i=0; i<n; i++)printf(" %d", dstImg[i]); getchar();

        if( !img_offset )
        {
            norm = norm1 = 0.0;
            for(i=0; i<n; i++)
            {
                norm  += fabs( dstImg[i] - tstImg[i] );
                norm1 += fabs( tstImg[i] );
            }
            norm /= norm1;
            printf( "                               %g\n", norm );
        }

        for(i=0; i<n; i++)
        {
            int d = dstImg[i] - tstImg[i];
            if( d > MAXDIFF || d < -MAXDIFF ) err10++;
        }

/*  8uC1 flavor test with interpolation */
        for(i=0; i<n; i++) dstImg[i] = tstImg[i] = 0;

        cvUnDistortInit ( src, undistMap, a, k, 1 );
        cvUnDistort     ( src, dst, undistMap, 1 );
        UnDistortTest_C1( srcImg + img_offset, tstImg + img_offset, step, size, a, k, 1 );

        if( !img_offset )
        {
            norm = norm1 = 0.0;
            for(i=0; i<n; i++)
            {
                norm  += fabs( dstImg[i] - tstImg[i] );
                norm1 += fabs( tstImg[i] );
            }
            norm /= norm1;
            printf( " 8u C1 with    interpolation:  %g\n", norm );
        }

        for(i=0; i<n; i++)
        {
            int d = dstImg[i] - tstImg[i];
            if( d > MAXDIFF || d < -MAXDIFF ) err2++;
        }

        for(i=0; i<n; i++) dstImg[i] = 0;

        cvUnDistortOnce ( src, dst, a, k, 1 );

        if( !img_offset )
        {
            norm = norm1 = 0.0;
            for(i=0; i<n; i++)
            {
                norm  += fabs( dstImg[i] - tstImg[i] );
                norm1 += fabs( tstImg[i] );
            }
            norm /= norm1;
            printf( "                               %g\n", norm );
        }

        for(i=0; i<n; i++)
        {
            int d = dstImg[i] - tstImg[i];
            if( d > MAXDIFF || d < -MAXDIFF ) err20++;
        }

/*  8uC3 flavor test without interpolation */
        for(i=0; i<n3; i++) dstImg3[i] = tstImg3[i] = 0;

        cvUnDistortInit ( src3, undistMap, a, k, 0 );
        cvUnDistort     ( src3, dst3, undistMap, 0 );
        UnDistortTest_C3( srcImg3+img_offset3, tstImg3+img_offset3, step3, size, a, k, 0 );

        for(i=0; i<n3; i++)
        {
            int d = dstImg3[i] - tstImg3[i];
            if( d > MAXDIFF || d < -MAXDIFF ) err3++;
        }

        if( !img_offset )
        {
            norm = norm1 = 0.0;
            for(i=0; i<n3; i++)
            {
                norm  += fabs( dstImg3[i] - tstImg3[i] );
                norm1 += fabs( tstImg3[i] );
            }
            norm /= norm1;
            printf( " 8u C3 without interpolation:  %g\n", norm );
        }

        for(i=0; i<n3; i++) dstImg3[i] = 0;

        cvUnDistortOnce ( src3, dst3, a, k, 0 );

        if( !img_offset )
        {
            norm = norm1 = 0.0;
            for(i=0; i<n3; i++)
            {
                norm  += fabs( dstImg3[i] - tstImg3[i] );
                norm1 += fabs( tstImg3[i] );
            }
            norm /= norm1;
            printf( "                               %g\n", norm );
        }

        for(i=0; i<n3; i++)
        {
            int d = dstImg3[i] - tstImg3[i];
            if( d > MAXDIFF || d < -MAXDIFF ) err30++;
        }

/*  8uC3 flavor test with interpolation */
        for(i=0; i<n3; i++) dstImg3[i] = tstImg3[i] = 0;

        cvUnDistortInit ( src3, undistMap, a, k, 1 );
        cvUnDistort     ( src3, dst3, undistMap, 1 );
        UnDistortTest_C3( srcImg3+img_offset3, tstImg3+img_offset3, step3, size, a, k, 1 );

        for(i=0; i<n3; i++)
        {
            int d = dstImg3[i] - tstImg3[i];
            if( d > MAXDIFF || d < -MAXDIFF ) err4++;
        }

        if( !img_offset )
        {
            norm = norm1 = 0.0;
            for(i=0; i<n3; i++)
            {
                norm  += fabs( dstImg3[i] - tstImg3[i] );
                norm1 += fabs( tstImg3[i] );
            }
            norm /= norm1;
            printf( " 8u C3 with    interpolation:  %g\n", norm );
        }

        for(i=0; i<n3; i++) dstImg3[i] = 0;

        cvUnDistortOnce ( src3, dst3, a, k, 1 );

        if( !img_offset )
        {
            norm = norm1 = 0.0;
            for(i=0; i<n3; i++)
            {
                norm  += fabs( dstImg3[i] - tstImg3[i] );
                norm1 += fabs( tstImg3[i] );
            }
            norm /= norm1;
            printf( "                               %g\n", norm );
        }

        for(i=0; i<n3; i++)
        {
            int d = dstImg3[i] - tstImg3[i];
            if( d > MAXDIFF || d < -MAXDIFF ) err40++;
        }

        if(ii>io) { trsWrite(TW_RUN|TW_CON, " %d%% ", 10*ii); io=ii; }
    }

    err5 = err1 + err2 + err3 + err4 + err10 + err20 + err30 + err40;
    err += err5;

    if( p < err1*100.f / (float)(n*num_test)   ) p = err1*100.f / (float)(n*num_test);
    if( p < err2*100.f / (float)(n*num_test)   ) p = err2*100.f / (float)(n*num_test);
    if( p < err3*100.f / (float)(3*n*num_test) ) p = err3*100.f / (float)(3*n*num_test);
    if( p < err4*100.f / (float)(3*n*num_test) ) p = err4*100.f / (float)(3*n*num_test);

    if( p < err10*100.f / (float)(n*num_test)   ) p = err10*100.f / (float)(n*num_test);
    if( p < err20*100.f / (float)(n*num_test)   ) p = err20*100.f / (float)(n*num_test);
    if( p < err30*100.f / (float)(3*n*num_test) ) p = err30*100.f / (float)(3*n*num_test);
    if( p < err40*100.f / (float)(3*n*num_test) ) p = err40*100.f / (float)(3*n*num_test);

//printf("\n  %d   %d   %d   %d\n  %d   %d   %d   %d      %7.3f%% errors\n",
//       err1, err2, err3, err4, err10, err20, err30, err40, p);

    switch( pass )
    {
    case 1:
        k[0] = -k[0];
        io = 0;
        err1 = err2 = err3 = err4 = err10 = err20 = err30 = err40 = 0;
        pass++;
        goto begin;
        break;
    case 2:
        k[0] = -k[0];
        k[2] = k[3] = 0.02f;
        io = 0;
        err1 = err2 = err3 = err4 = err10 = err20 = err30 = err40 = 0;
        pass++;
        goto begin;
        break;
    case 3:
        k[0] = -k[0];
        io = 0;
        err1 = err2 = err3 = err4 = err10 = err20 = err30 = err40 = 0;
        pass++;
        goto begin;
        break;
    }

    if( p < MAXPERCENT ) err = 0;

    cvReleaseImage( &src  );
    cvReleaseImage( &dst  );
    cvReleaseImage( &tst  );
    cvReleaseImage( &src3 );
    cvReleaseImage( &dst3 );
    cvReleaseImage( &tst3 );
    cvReleaseImage( &undistMap );
    cvFree( (void**)&a      );
    cvFree( (void**)&k      );

    if( err == 0 ) return trsResult( TRS_OK, "No errors fixed by this test" );
    else return trsResult( TRS_FAIL, "Total fixed %d errors", err );
    
} /*fma*/
/*------------------------------------------- Initialize function ------------------------ */
void InitAUnDistort( void )
{
   /* Registering test function */
    trsReg( FuncName, TestName, TestClass, fmaUnDistort );
} /* InitTEigenObjects */

/*  End of file  */
