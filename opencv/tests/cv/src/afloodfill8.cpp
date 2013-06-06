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

/* Testing parameters */
static char FuncName[] = "cvFloodFill8";
static char TestName[] = "Flood Fill 8-connected function test";
static char TestClass[] = "Algorithm";

typedef struct
{
    int    nx0;
    ushort nx1;
    ushort ny1;
    uchar  q1;
    uchar  q2;
    uchar  unv;
    uchar* b;
    uchar* I;
} consts;

int Counter8=0;
static int X1=0, X2=0, Y1=0, Y2=0;

/*---------------------- Test function (the most slowly algorithm) ----------------------- */
CvStatus  _cvFloodFill8uC1R_slow8 ( uchar*   pImage,
                                    int      step,
                                    CvSize  imgSize,
                                    CvPoint initPoint,
                                    int      nv,
                                    int      d1,
                                    int      d2 )
{
    int i, j, k, ij, ijb, ij1, nx, ny, n, nx1, ny1, mNew, ov, nxj, nxjb;
    uchar *b = 0, b0, q1, q2, q10, q20;

    nx = imgSize.width;  ny = imgSize.height;
    ij = initPoint.x + nx*initPoint.y;
    ov = pImage[ij];
    n = nx*ny;
    nx1 = nx-1;  ny1 = ny-1;
    b0=1;
    q10=(uchar)d1; q20=(uchar)d2;
    if( (b=(uchar*)icvAlloc(n*sizeof(uchar))) == NULL) return CV_OUTOFMEM_ERR;
    for(k=0; k<n; k++) b[k]=0;
    b[ij]=1;

    do
    {
        mNew = 0;
        for(j=0; j<ny; j++)
        {
            nxj = step*j;
            nxjb= nx *j;
            for(i=0; i<nx; i++)
            {
                ij = i + nxj;
                ijb= i + nxjb;
                if(b[ijb]!=b0)continue;

                b[ijb]++;
                q1 = (uchar)((pImage[ij]>q10) ? pImage[ij]-q10 : (uchar)0);
                q2 = (uchar)(((int)pImage[ij]+(int)q20<255)?pImage[ij]+q20:(uchar)255);
                pImage[ij] = (uchar)nv;
                Counter8++;
                if(X1>i) X1=i;  if(X2<i) X2=i;  if(Y1>j) Y1=j;  if(Y2<j) Y2=j;
                /*------------------------- */
                ij1=ij-1;
                if((i>0) && (!b[ijb-1]) && (pImage[ij1]>=q1) && (pImage[ij1]<=q2))
                {
                    mNew++;
                    b[ijb-1]++;
                }
                ij1=ij+1;
                if((i<nx1) && (!b[ijb+1]) && (pImage[ij1]>=q1) && (pImage[ij1]<=q2))
                {
                    mNew++;
                    b[ijb+1]++;
                }
                ij1=ij-step;
                if((j>0) && (!b[ijb-nx]) && (pImage[ij1]>=q1) && (pImage[ij1]<=q2))
                {
                    mNew++;
                    b[ijb-nx]++;
                }
                ij1=ij+step;
                if((j<ny1) && (!b[ijb+nx]) && (pImage[ij1]>=q1) && (pImage[ij1]<=q2))
                {
                    mNew++;
                    b[ijb+nx]++;
                }
                /*------------------------- */
                ij1=ij-step-1;
                if((i>0)&&(j>0))
                    if((!b[ijb-nx-1])&&(pImage[ij1]>=q1)&&(pImage[ij1]<=q2))
                {
                    mNew++;
                    b[ijb-nx-1]++;
                }
                ij1=ij-step+1;
                if((i<nx1)&&(j>0))
                    if((!b[ijb-nx+1])&&(pImage[ij1]>=q1)&&(pImage[ij1]<=q2))
                {
                    mNew++;
                    b[ijb-nx+1]++;
                }
                ij1=ij+step-1;
                if((i>0)&&(j<ny1))
                    if((!b[ijb+nx-1])&&(pImage[ij1]>=q1)&&(pImage[ij1]<=q2))
                {
                    mNew++;
                    b[ijb+nx-1]++;
                }
                ij1=ij+step+1;
                if((i<nx1)&&(j<ny1))
                    if((!b[ijb+nx+1])&&(pImage[ij1]>=q1)&&(pImage[ij1]<=q2))
                {
                    mNew++;
                    b[ijb+nx+1]++;
                }
                /*------------------------- */
            }     /* i */
        }         /* j */
    } while(mNew);

    icvFree((void**)&b);
    return CV_NO_ERR;
} /*  _ipcvFloodFill8uC1R_slow8 */
/*--------------------------------------------------------------------------------------*/
CvStatus  _cvFloodFill32fC1R_slow8 ( float* pImage,
                                     int     step,
                                     CvSize  imgSize,
                                     CvPoint initPoint,
                                     float   nv,
                                     float   d1,
                                     float   d2 )
{
    int i, j, k, ij, ij1, ijb, nx, ny, n, nx1, ny1, mNew, nxj, nxjb;
    float ov, q1, q2;
    uchar *b, b0;

    step /= 4;
    nx = imgSize.width;  ny = imgSize.height;  n = nx * ny;
    ij = initPoint.x + step*initPoint.y;
    ov = pImage[ij];
    nx1 = nx-1;  ny1 = ny-1;
    b0=1;
    if( (b=(uchar*)icvAlloc(n*sizeof(uchar))) == NULL) return CV_OUTOFMEM_ERR;
    for(k=0; k<n; k++) b[k]=0;
    ij = initPoint.x + nx*initPoint.y;
    b[ij]=b0;
    Counter8 = 0;

    do
    {
        mNew = 0;
        for(j=0; j<ny; j++)
        {
            nxj = step*j;
            nxjb= nx *j;
            for(i=0; i<nx; i++)
            {
                ij = i + nxj;
                ijb= i + nxjb;
                if(b[ijb]!=b0)continue;

                b[ijb]++;
                q1 = pImage[ij] - d1;  q2 = pImage[ij] + d2;
                pImage[ij] = nv;
                Counter8++;
                if(X1>i) X1=i;  if(X2<i) X2=i;  if(Y1>j) Y1=j;  if(Y2<j) Y2=j;

                /*------------------------- */
                ij1=ij-1;
                if((i>0) && (!b[ijb-1]) && (pImage[ij1]>=q1) && (pImage[ij1]<=q2))
                {
                    mNew++;
                    b[ijb-1]++;
                }
                ij1=ij+1;
                if((i<nx1) && (!b[ijb+1]) && (pImage[ij1]>=q1) && (pImage[ij1]<=q2))
                {
                    mNew++;
                    b[ijb+1]++;
                }
                ij1=ij-step;
                if((j>0) && (!b[ijb-nx]) && (pImage[ij1]>=q1) && (pImage[ij1]<=q2))
                {
                    mNew++;
                    b[ijb-nx]++;
                }
                ij1=ij+step;
                if((j<ny1) && (!b[ijb+nx]) && (pImage[ij1]>=q1) && (pImage[ij1]<=q2))
                {
                    mNew++;
                    b[ijb+nx]++;
                }
                /*------------------------- */
                ij1=ij-step-1;
                if((i>0)&&(j>0))
                    if((!b[ijb-nx-1])&&(pImage[ij1]>=q1)&&(pImage[ij1]<=q2))
                {
                    mNew++;
                    b[ijb-nx-1]++;
                }
                ij1=ij-step+1;
                if((i<nx1)&&(j>0))
                    if((!b[ijb-nx+1])&&(pImage[ij1]>=q1)&&(pImage[ij1]<=q2))
                {
                    mNew++;
                    b[ijb-nx+1]++;
                }
                ij1=ij+step-1;
                if((i>0)&&(j<ny1))
                    if((!b[ijb+nx-1])&&(pImage[ij1]>=q1)&&(pImage[ij1]<=q2))
                {
                    mNew++;
                    b[ijb+nx-1]++;
                }
                ij1=ij+step+1;
                if((i<nx1)&&(j<ny1))
                    if((!b[ijb+nx+1])&&(pImage[ij1]>=q1)&&(pImage[ij1]<=q2))
                {
                    mNew++;
                    b[ijb+nx+1]++;
                }
                /*------------------------- */
            }     /* i */
        }         /* j */
    } while(mNew);

    icvFree((void**)&b);
    return CV_NO_ERR;
} /*  _ipcvFloodFill32fC1R_slow8 */

/*=================================================== Test body ========================== */
static int fmaFloodFill8( void )
{
    /* Some Variables */
    int nx, ny, stepX, stepY, numTest, ROI_offset, mp=0, mp4=0;
    int i, j, k, ij, it, n, n4, ov, d1, d2, ntest2, nerr=0;
    int step, step4;
    uchar *pI0, *pI1, *pI2;
    float* pI3, *pI4;
    IplImage *I0, *I1, *I2, *I3, *I4;
    CvSize  size;
    CvPoint seed;
    CvConnectedComp Comp;
    CvStatus r;

    /* Reading test parameters */
    trsiRead( &nx,        "64", "Image width" );
    trsiRead( &stepX,     "16", "Seed point horizontal step" );
    trsiRead( &numTest,   "32", "Number of each seed point tests" );
    trsiRead( &ROI_offset, "0", "ROI offset" );

    ny = nx;
    stepY = stepX;
    n = nx*ny;
    ntest2 = numTest/2;
    size.width  = nx;
    size.height = ny;

    I0  = cvCreateImage( size, IPL_DEPTH_8U, 1 );
    I1  = cvCreateImage( size, IPL_DEPTH_8U, 1 );
    I2  = cvCreateImage( size, IPL_DEPTH_8U, 1 );
    I3  = cvCreateImage( size, IPL_DEPTH_32F,1 );
    I4  = cvCreateImage( size, IPL_DEPTH_32F,1 );

    pI0 = (uchar*)I0->imageData;
    pI1 = (uchar*)I1->imageData;
    pI2 = (uchar*)I2->imageData;
    pI3 = (float*)I3->imageData;
    pI4 = (float*)I4->imageData;

    step = I1->widthStep;  step4 = I3->widthStep;
    n = step*ny;  n4 = (step4/4)*ny;

    if(ROI_offset)
    {
        mp = ROI_offset + ROI_offset*step;
        mp4= ROI_offset + ROI_offset*step4;
        size.width  = nx - 2*ROI_offset;
        size.height = ny - 2*ROI_offset;
        I1->roi->xOffset = I1->roi->yOffset = ROI_offset;
        I1->roi->height  = size.height;  I1->roi->width = size.width;
        I3->roi->xOffset = I3->roi->yOffset = ROI_offset;
        I3->roi->height = size.height;  I3->roi->width = size.width;
    }

    /*  T E S T I N G  */

/* Zero interval */
    d1 = d2 = 0;
    ats1bInitRandom ( 0, 1.5, pI0, n );
        /*for(i=0;i<n;i++)printf(" %d",pI0[i]);getchar(); */
    for(j=0; j<size.height; j=j+stepY)
    {
        seed.y = j;
        for(i=0; i<size.width; i=i+stepX)
        {
            seed.x = i;
            for(k=0; k<n;  k++) pI1[k]=pI2[k]=pI0[k];
            for(k=0; k<n4; k++) pI3[k]=pI4[k]=(float)pI0[k];
     /* 8U */
            Counter8 = 0;   X1 = X2 = i;    Y1 = Y2 = j;
            /* Run CVL function */
            cvFloodFill ( I1, seed, 10.0, (double)d1, (double)d2, &Comp, 8 );
            /* Run test function */
            r = _cvFloodFill8uC1R_slow8 (pI2+mp, step, size, seed, 10, d1, d2 );
            /* Comparison */
                for(k=0; k<n; k++) if( (pI1[k]-pI2[k]) ) nerr++;
                if( Comp.area!=Counter8 ) nerr++;
            if(X1!=Comp.rect.x) nerr++;
            if(Y1!=Comp.rect.y) nerr++;
            if((X2-X1+1)!=Comp.rect.width) nerr++;
            if((Y2-Y1+1)!=Comp.rect.height) nerr++;
     /* 32F */
            Counter8 = 0;   X1 = X2 = i;    Y1 = Y2 = j;
            /* Run CVL function */
            cvFloodFill ( I3, seed, 10.0, (double)d1, (double)d2, &Comp, 8 );
            /* Run test function */
            r = _cvFloodFill32fC1R_slow8 (pI4+mp4, step4, size, seed, 10.0, (float)d1, (float)d2 );
            /* Comparison */
                for(k=0; k<n4; k++) if( (pI3[k]-pI4[k]) ) nerr++;
                if( Comp.area!=Counter8 ) nerr++;
            if(X1!=Comp.rect.x) nerr++;
            if(Y1!=Comp.rect.y) nerr++;
            if((X2-X1+1)!=Comp.rect.width) nerr++;
            if((Y2-Y1+1)!=Comp.rect.height) nerr++;

            if( nerr != 0 )
                break;
        }
    }

/* Non-zero interval */
    ats1bInitRandom ( 0, 254.99, pI0, n );
    for(j=1; j<size.height; j=j+stepY)
    {
        seed.y = j;
        for(i=1; i<size.width; i=i+stepX)
        {
            ij=i+step*j;   ov=pI0[ij+mp];
            seed.x = i;
            for(it=0; it<numTest; it++)
            {
                for(k=0; k<n;  k++) pI1[k]=pI2[k]=pI0[k];
                for(k=0; k<n4; k++) pI3[k]=pI4[k]=(float)pI0[k];
                if(it<ntest2)  /* sequential increase interval */
                { d1=(ov*(it+1))/ntest2;  d2=((255-ov)*(it+1))/ntest2; }
                else           /* random interval */
                {
                    d1 = (int)atsInitRandom(1.0, 127);
                    d2 = (int)atsInitRandom(1.0, 127);
                    if(it>(3*numTest)/4){d1/=2; d2/=2;}
                }
     /* 8U */
                Counter8 = 0; X1 = X2 = i;    Y1 = Y2 = j;
                /* Run CVL function */
                cvFloodFill ( I1, seed, 255.0, (double)d1, (double)d2, &Comp, 8 );
                /* Run test function */
                r = _cvFloodFill8uC1R_slow8 (pI2+mp, step, size, seed, 255, d1, d2 );
                /* Comparison */
                    for(k=0; k<n; k++) if( (pI1[k]-pI2[k]) ) nerr++;
                    if( Comp.area!=Counter8 ) nerr++;
                if(X1!=Comp.rect.x) nerr++;
                if(Y1!=Comp.rect.y) nerr++;
                if((X2-X1+1)!=Comp.rect.width) nerr++;
                if((Y2-Y1+1)!=Comp.rect.height) nerr++;
     /* 32F */
                Counter8 = 0; X1 = X2 = i;    Y1 = Y2 = j;
                /* Run CVL function */
                cvFloodFill ( I3, seed, 255.0, (double)d1, (double)d2, &Comp, 8 );
                /* Run test function */
                r = _cvFloodFill32fC1R_slow8 (pI4+mp4, step4, size, seed, 255.0, (float)d1, (float)d2 );
                /* Comparison */
                    for(k=0; k<n4; k++) if( (pI3[k]-pI4[k]) ) nerr++;
                    if( Comp.area!=Counter8 ) nerr++;
                if(X1!=Comp.rect.x) nerr++;
                if(Y1!=Comp.rect.y) nerr++;
                if((X2-X1+1)!=Comp.rect.width) nerr++;
                if((Y2-Y1+1)!=Comp.rect.height) nerr++;

                if( nerr != 0 )
                    break;
            }
        }
        trsWrite(TW_RUN|TW_CON, " %d%% ", ((j+stepY)*100)/size.height);
    }
    cvReleaseImage( &I0 );
    cvReleaseImage( &I1 );
    cvReleaseImage( &I2 );
    cvReleaseImage( &I3 );
    cvReleaseImage( &I4 );
    trsWrite(TW_RUN|TW_CON|TW_SUM, "    Nerr = %d\n", nerr);
    if( nerr == 0 ) return trsResult( TRS_OK, "No errors fixed by this test" );
    else return trsResult( TRS_FAIL, "Total fixed %d errors", nerr );
} /*fma*/
/*------------------------------------------------ Initialize function ------------------- */
void InitAFloodFill8( void )
{
    trsReg( FuncName, TestName, TestClass, fmaFloodFill8 );
} /* InitAFloodFill8 */

/* End of file. */
