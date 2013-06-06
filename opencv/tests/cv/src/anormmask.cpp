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
static char FuncName[] = "cvNormMask";
static char TestName[] = "Norm calculation functions test";
static char TestClass[] = "Algorithm";

static const double  EPS = 1.e-13;
static const double FEPS = 1.e-6;

static int Min_Image_Width, Max_Image_Width, Max_ROI_Offset;

#define TYPE_8U  0
#define TYPE_8S  1
#define TYPE_32F 2

#define MIN_VAL(type) type==IPL_DEPTH_8U ?   0 : type==IPL_DEPTH_8S ? -128 : type==IPL_DEPTH_32F ?  -1.f : 0
#define MAX_VAL(type) type==IPL_DEPTH_8U ? 255 : type==IPL_DEPTH_8S ?  127 : type==IPL_DEPTH_32F ?   1.f : 0

static const int cvlType[9]={_CV_C,_CV_L1,_CV_L2,_CV_DIFF_C,_CV_DIFF_L1,_CV_DIFF_L2,
                             _CV_RELATIVE_C,_CV_RELATIVE_L1,_CV_RELATIVE_L2};

/*------------------------------------------------ Test functions --------------------- */

double calcTestNormMask( double* a, double* b, uchar* m, int n, int type )
{
    int i;
    double n1=0, n2=0;

    switch( type )
    {
    case _CV_C:
        for( i=0; i<n; i++ ) if( m[i] )
        {
            double t = fabs( a[i] );
            if( n1<t ) n1=t;
        }
        break;
    case _CV_L1:
        for( i=0; i<n; i++ ) if( m[i] )
            n1 += fabs( a[i] );
        break;
    case _CV_L2:
        for( i=0; i<n; i++ ) if( m[i] )
        {
            double t = a[i];
            n1 += t*t;
        }
        n1 = sqrt( n1 );
        break;
    case _CV_DIFF_C:
        for( i=0; i<n; i++ ) if( m[i] )
        {
            double t = fabs( a[i] - b[i] );
            if( n1<t ) n1=t;
        }
        break;
    case _CV_DIFF_L1:
        for( i=0; i<n; i++ ) if( m[i] )
            n1 += fabs( a[i] - b[i] );
        break;
    case _CV_DIFF_L2:
        for( i=0; i<n; i++ ) if( m[i] )
        {
            double t = a[i] - b[i];
            n1 += t*t;
        }
        n1 = sqrt( n1 );
        break;
    case _CV_RELATIVE_C:
        for( i=0; i<n; i++ ) if( m[i] )
        {
            double bi = b[i];
            double t  = fabs( a[i] - bi );
            if( n1<t ) n1 = t;
            t = fabs( bi );
            if( n2<t ) n2 = t;
        }
        n1 = n2 ? n1/n2 : -20.0;
        break;
    case _CV_RELATIVE_L1:
        for( i=0; i<n; i++ ) if( m[i] )
        {
            double bi = b[i];
            n1 += fabs( a[i] - bi );
            n2 += fabs( bi );
        }
        n1 = n2 ? n1/n2 : -20.0;
        break;
    case _CV_RELATIVE_L2:
        for( i=0; i<n; i++ ) if( m[i] )
        {
            double bi = b[i];
            double t  = fabs( a[i] - bi );
            t  *= t;
            n1 += t;
            t   = fabs( bi );
            t  *= t;
            n2 += t;
        }
        n1 = n2 ? n1/n2 : -20.0;
        n1 = sqrt( n1 );
        break;
    default:
        n1 = -30.0;
    }

    return n1;
}
/*......................................................................................*/

double TestNormMask( IplImage* A, IplImage* B, IplImage* M, int type )
{
    uchar *A_data = 0, *B_data = 0, *M_data = 0, *m;
    int    A_step = 0,  B_step = 0,  M_step = 0;
    CvSize A_size,      B_size,      M_size;
    int i, j, j4, k, coi, channels, nx, ny, n;
    double *a=0, *b=0, norm;

    cvGetImageRawData( A, &A_data, &A_step, &A_size );
    coi = A->roi->coi;
    channels = A->nChannels;
    if( coi<0 || coi>3 ) return -1.0;
    if( coi > 0 && channels != 3 ) return -2.0;

    cvGetImageRawData( M, &M_data, &M_step, &M_size );

    if( B )
    {
        cvGetImageRawData( B, &B_data, &B_step, &B_size );
        if( A_step!=B_step )    return -3.0;
        if( A_size.height!=B_size.height || A_size.width!=B_size.width ) return -4.0;
        if( coi!=B->roi->coi ) return -5.0;
    }
    else
        if( type==_CV_RELATIVE_C || type==_CV_RELATIVE_L1 || type==_CV_RELATIVE_L2 ||
            type==_CV_DIFF_C || type==_CV_DIFF_L1 || type==_CV_DIFF_L2 ) return -10.0;

    nx = A_size.width;
    ny = A_size.height;
    n  = nx*ny;
    m  = (uchar*) icvAlloc( n*sizeof(uchar));
    a  = (double*)icvAlloc( n*sizeof(double));
    if(B) b  = (double*)icvAlloc( n*sizeof(double));

    k = 0;

    if( channels < 3 )
    {
        if( B )
        {
            if( A->depth == IPL_DEPTH_8U )
            {
                for( i=0; i<ny; i++, A_data+=A_step, B_data+=B_step, M_data+=M_step )
                    for( j=0; j<nx; j++, k++ )
                    {
                        a[k] = A_data[j];
                        b[k] = B_data[j];
                        m[k] = M_data[j];
                    }
            }

            if( A->depth == IPL_DEPTH_8S )
            {
                for( i=0; i<ny; i++, A_data+=A_step, B_data+=B_step, M_data+=M_step )
                    for( j=0; j<nx; j++, k++ )
                    {
                        a[k] = *(char*)(A_data+j);
                        b[k] = *(char*)(B_data+j);
                        m[k] = M_data[j];
                    }
            }

            if( A->depth == IPL_DEPTH_32F )
            {
                for( i=0; i<ny; i++, A_data+=A_step, B_data+=B_step, M_data+=M_step )
                    for( j=0, j4=0; j<nx; j++, j4+=4, k++ )
                    {
                        a[k] = *(float*)(A_data+j4);
                        b[k] = *(float*)(B_data+j4);
                        m[k] = M_data[j];
                    }
            }
        }
        else
        {
            if( A->depth == IPL_DEPTH_8U )
            {
                for( i=0; i<ny; i++, A_data+=A_step, M_data+=M_step )
                    for( j=0; j<nx; j++, k++ )
                    {
                        a[k] = A_data[j];
                        m[k] = M_data[j];
                    }
            }

            if( A->depth == IPL_DEPTH_8S )
            {
                for( i=0; i<ny; i++, A_data+=A_step, M_data+=M_step )
                    for( j=0; j<nx; j++, k++ )
                    {
                        a[k] = *(char*)(A_data+j);
                        m[k] = M_data[j];
                    }
            }

            if( A->depth == IPL_DEPTH_32F )
            {
                for( i=0; i<ny; i++, A_data+=A_step, M_data+=M_step )
                    for( j=0, j4=0; j<nx; j++, j4+=4, k++ )
                    {
                        a[k] = *(float*)(A_data+j4);
                        m[k] = M_data[j];
                    }
            }
        }
    }
    else  /* channels = 3 */
    {
        coi--;

        if( B )
        {
            if( A->depth == IPL_DEPTH_8U )
            {
                A_data += coi;
                B_data += coi;

                for( i=0; i<ny; i++, A_data+=A_step, B_data+=B_step, M_data+=M_step )
                    for( j=0, j4=0; j<nx; j++, j4+=3, k++ )
                    {
                        a[k] = A_data[j4];
                        b[k] = B_data[j4];
                        m[k] = M_data[j];
                    }
            }

            if( A->depth == IPL_DEPTH_8S )
            {
                A_data += coi;
                B_data += coi;

                for( i=0; i<ny; i++, A_data+=A_step, B_data+=B_step, M_data+=M_step )
                    for( j=0, j4=0; j<nx; j++, j4+=3, k++ )
                    {
                        a[k] = *(char*)(A_data+j4);
                        b[k] = *(char*)(B_data+j4);
                        m[k] = M_data[j];
                    }
            }

            if( A->depth == IPL_DEPTH_32F )
            {
                A_data += 4*coi;
                B_data += 4*coi;

                for( i=0; i<ny; i++, A_data+=A_step, B_data+=B_step, M_data+=M_step )
                    for( j=0, j4=0; j<nx; j++, j4+=12, k++ )
                    {
                        a[k] = *(float*)(A_data+j4);
                        b[k] = *(float*)(B_data+j4);
                        m[k] = M_data[j];
                    }
            }
        }
        else
        {
            if( A->depth == IPL_DEPTH_8U )
            {
                A_data += coi;

                for( i=0; i<ny; i++, A_data+=A_step, M_data+=M_step )
                    for( j=0, j4=0; j<nx; j++, j4+=3, k++ )
                    {
                        a[k] = A_data[j4];
                        m[k] = M_data[j];
                    }
            }

            if( A->depth == IPL_DEPTH_8S )
            {
                A_data += coi;

                for( i=0; i<ny; i++, A_data+=A_step, M_data+=M_step )
                    for( j=0, j4=0; j<nx; j++, j4+=3, k++ )
                    {
                        a[k] = *(char*)(A_data+j4);
                        m[k] = M_data[j];
                    }
            }

            if( A->depth == IPL_DEPTH_32F )
            {
                A_data += 4*coi;

                for( i=0; i<ny; i++, A_data+=A_step, M_data+=M_step )
                    for( j=0, j4=0; j<nx; j++, j4+=12, k++ )
                    {
                        a[k] = *(float*)(A_data+j4);
                        m[k] = M_data[j];
                    }
            }
        }
    }  /* channels */

    norm = calcTestNormMask( a, b, m, n, type );

    icvFree((void**)&a );
    icvFree((void**)&m );
    if(b) icvFree((void**)&b );

    return norm;
}

/*=================================================== Test body ========================== */
static int fmaNormMask(void)
{
    /* Some Variables */
    int nx, ny, n, n4, it, ir, nr, nerr=0, coi, step, step4;
    int xoff, yoff, roiw, roih, nerrt[9];
    CvSize size;
    AtsRandState state1, state2, state3, state4;
    IplImage *A_8uC1, *A_8sC1, *A_32fC1, *B_8uC1, *B_8sC1, *B_32fC1;
    IplImage *A_8uC3, *A_8sC3, *A_32fC3, *B_8uC3, *B_8sC3, *B_32fC3;
    IplImage *mask;
    IplROI   r, rm;
    double norm, testnorm, err;
    double Mask_density, d1, d2;

    trsiRead( &Min_Image_Width,  "1", "Minimal image width" );
    trsiRead( &Max_Image_Width, "32", "Maximal image width" );
    trsiRead( &Max_ROI_Offset,   "8", "Maximal ROI offset" );
    trsdRead( &Mask_density,   "0.5", "Mask density (0 - 1)" );

    if( Min_Image_Width < 1 )               Min_Image_Width = 1;
    if( Max_Image_Width < Min_Image_Width ) Max_Image_Width = Min_Image_Width;
    if( Max_ROI_Offset  < 0 )               Max_ROI_Offset  = 0;
    if( Mask_density    < 0.0 )             Mask_density    = 0.0;

    if( Mask_density >= 1.0 ) { d1 = 2.0; d2 = 4.0; }
    else                      { d1 = 0.0; d2 = 1.0/(1.0-Mask_density); }
    if(d2>256.0) d2=256.0;

    atsRandInit( &state1, MIN_VAL(IPL_DEPTH_8U),  MAX_VAL(IPL_DEPTH_8U),  13 );
    atsRandInit( &state2, MIN_VAL(IPL_DEPTH_8S),  MAX_VAL(IPL_DEPTH_8S),  14 );
    atsRandInit( &state3, MIN_VAL(IPL_DEPTH_32F), MAX_VAL(IPL_DEPTH_32F), 15 );
    atsRandInit( &state4, d1, d2, 16 );

    for( it=0; it<9; it++ ) nerrt[it] = 0;

/*  Image size cycle starts ________________________ */
    for( nx = Min_Image_Width; nx<=Max_Image_Width; nx++ )
    {
        ny = nx;
        /*if(nx>1)ny=(int)(0.7*nx);           // Non-square images test */
        size.width  = nx;  size.height = ny;

        /* Initial images allocating & random filling */
        A_8uC1  = cvCreateImage( size, IPL_DEPTH_8U,  1 );
        A_8sC1  = cvCreateImage( size, IPL_DEPTH_8S,  1 );
        A_32fC1 = cvCreateImage( size, IPL_DEPTH_32F, 1 );

        B_8uC1  = cvCreateImage( size, IPL_DEPTH_8U,  1 );
        B_8sC1  = cvCreateImage( size, IPL_DEPTH_8S,  1 );
        B_32fC1 = cvCreateImage( size, IPL_DEPTH_32F, 1 );

        A_8uC3  = cvCreateImage( size, IPL_DEPTH_8U,  3 );
        A_8sC3  = cvCreateImage( size, IPL_DEPTH_8S,  3 );
        A_32fC3 = cvCreateImage( size, IPL_DEPTH_32F, 3 );

        B_8uC3  = cvCreateImage( size, IPL_DEPTH_8U,  3 );
        B_8sC3  = cvCreateImage( size, IPL_DEPTH_8S,  3 );
        B_32fC3 = cvCreateImage( size, IPL_DEPTH_32F, 3 );

        mask  = cvCreateImage( size, IPL_DEPTH_8U,  1 );

        step = A_8uC1->widthStep;  step4 = (A_32fC1->widthStep)/4;
        n = ny*step;  n4 = ny*step4;

        atsbRand8u ( &state1, (uchar*)A_8uC1->imageData,  n );
        atsbRand8s ( &state2, A_8sC1->imageData,  n );
        atsbRand32f( &state3, (float*)A_32fC1->imageData, n4);

        atsbRand8u ( &state1, (uchar*)B_8uC1->imageData,  n );
        atsbRand8s ( &state2, B_8sC1->imageData,  n );
        atsbRand32f( &state3, (float*)B_32fC1->imageData, n4);

        atsbRand8u ( &state4, (uchar*)mask->imageData,  n );
        for(ir=0; ir<n; ir++) if((mask->imageData)[ir]>1) (mask->imageData)[ir]=1;
        (mask->imageData)[0] = 1;

        step = A_8uC3->widthStep;  step4 = (A_32fC3->widthStep)/4;
        n = ny*step;  n4 = ny*step4;

        atsbRand8u ( &state1, (uchar*)A_8uC3->imageData,  n );
        atsbRand8s ( &state2, A_8sC3->imageData,  n );
        atsbRand32f( &state3, (float*)A_32fC3->imageData, n4);

        atsbRand8u ( &state1, (uchar*)B_8uC3->imageData,  n );
        atsbRand8s ( &state2, B_8sC3->imageData,  n );
        atsbRand32f( &state3, (float*)B_32fC3->imageData, n4);

        nr = (ny-1)/2>Max_ROI_Offset ? Max_ROI_Offset : (ny-1)/2;

        A_8uC1->roi = A_8sC1->roi = A_32fC1->roi = 
        A_8uC3->roi = A_8sC3->roi = A_32fC3->roi = 
        B_8uC1->roi = B_8sC1->roi = B_32fC1->roi = 
        B_8uC3->roi = B_8sC3->roi = B_32fC3->roi = &r;

        for( ir = 0; ir<=nr; ir++) /* ROI size cycle starts ----------------- */
        {
            /* IPL ROI structures filling */
            xoff = ir/11;
            yoff = ir;
            roiw = nx - (int)(1.2*xoff);
            roih = ny - (int)(1.5*yoff);
            r.xOffset = xoff;
            r.yOffset = yoff;
            r.width   = roiw;
            r.height  = roih;

            rm = r;
            rm.coi = 0;
            mask->roi = &rm;

/*  T E S T I N G  */
            for(it = 0; it<9; it++)
            {
                IplImage* B;

                r.coi = 0;

                //if( it >= 3 )
                //    continue;

                B = it<3 ? NULL : B_8uC1;
                A_8uC1->maskROI = B_8uC1->maskROI = NULL;
                norm     =   cvNormMask( A_8uC1, B, mask, cvlType[it] );
                testnorm = TestNormMask( A_8uC1, B, mask, cvlType[it] );
                err = fabs((norm-testnorm)/testnorm);
                if( err > EPS )
                {
                    nerrt[it]++;
                    printf(" 8uC1  %d norm fail:  %f  %f\n", it+1, norm, testnorm);
                }

                B = it<3 ? NULL : B_8sC1;
                A_8sC1->maskROI = B_8sC1->maskROI = NULL;
                norm     =   cvNormMask( A_8sC1, B, mask, cvlType[it] );
                testnorm = TestNormMask( A_8sC1, B, mask, cvlType[it] );
                err = fabs((norm-testnorm)/testnorm);
                if( err > EPS )
                {
                    nerrt[it]++;
                    printf(" 8sC1  %d norm fail:  %f  %f\n", it+1, norm, testnorm);
                }

                B = it<3 ? NULL : B_32fC1;
                A_32fC1->maskROI = B_32fC1->maskROI = NULL;
                norm     =   cvNormMask( A_32fC1, B, mask, cvlType[it] );
                testnorm = TestNormMask( A_32fC1, B, mask, cvlType[it] );
                err = fabs((norm-testnorm)/testnorm);
                if( err > FEPS )
                {
                    nerrt[it]++;
                    printf(" 32fC1 %d norm fail:  %f  %f\n", it+1, norm, testnorm);
                }

                    B = it<3 ? NULL : B_8uC3;
                    for( coi=1; coi<4; coi++ )
                    {
                        r.coi   = coi;
                        A_8uC3->maskROI = B_8uC3->maskROI = NULL;
                        norm     =   cvNormMask( A_8uC3, B, mask, cvlType[it] );
                        testnorm = TestNormMask( A_8uC3, B, mask, cvlType[it] );
                        err     = fabs((norm-testnorm)/testnorm);
                        if( err > EPS )
                        {
                            nerrt[it]++;
                            printf(" 8uC3  %d norm fail:  %f  %f,  coi = %d\n", it+1, norm, testnorm, coi);
                        }
                    }

                    B = it<3 ? NULL : B_8sC3;
                    for( coi=1; coi<4; coi++ )
                    {
                        r.coi = coi;
                        A_8sC3->maskROI = B_8sC3->maskROI = NULL;
                        norm     =   cvNormMask( A_8sC3, B, mask, cvlType[it] );
                        testnorm = TestNormMask( A_8sC3, B, mask, cvlType[it] );
                        err = fabs((norm-testnorm)/testnorm);
                        if( err > EPS )
                        {
                            nerrt[it]++;
                            printf(" 8sC3  %d norm fail:  %f  %f,  coi = %d\n", it+1, norm, testnorm, coi);
                        }
                    }

                    B = it<3 ? NULL : B_32fC3;
                    for( coi=1; coi<4; coi++ )
                    {
                        r.coi = coi;
                        A_32fC3->maskROI = B_32fC3->maskROI = NULL;
                        norm     =   cvNormMask( A_32fC3, B, mask, cvlType[it] );
                        testnorm = TestNormMask( A_32fC3, B, mask, cvlType[it] );
                        err = fabs((norm-testnorm)/testnorm);
                        if( err > FEPS )
                        {
                            nerrt[it]++;
                            printf(" 32fC3 %d norm fail:  %f  %f,  coi = %d\n", it+1, norm, testnorm, coi);
                        }
                    }
            } /* norm type */

            for( it=0; it<9; it++ ) nerr += nerrt[it];
        } /* ROI */

        A_8uC1->roi = A_8sC1->roi = A_32fC1->roi = 
        A_8uC3->roi = A_8sC3->roi = A_32fC3->roi = 
        B_8uC1->roi = B_8sC1->roi = B_32fC1->roi = 
        B_8uC3->roi = B_8sC3->roi = B_32fC3->roi = 0;

        mask->roi = 0;

        A_8uC1->maskROI = A_8sC1->maskROI = A_32fC1->maskROI = 
        A_8uC3->maskROI = A_8sC3->maskROI = A_32fC3->maskROI = 
        B_8uC1->maskROI = B_8sC1->maskROI = B_32fC1->maskROI = 
        B_8uC3->maskROI = B_8sC3->maskROI = B_32fC3->maskROI = 0;

        mask->maskROI = 0;

        cvReleaseImage( &A_8uC1  );
        cvReleaseImage( &A_8sC1  );
        cvReleaseImage( &A_32fC1 );
        cvReleaseImage( &B_8uC1  );
        cvReleaseImage( &B_8sC1  );
        cvReleaseImage( &B_32fC1 );
        cvReleaseImage( &A_8uC3  );
        cvReleaseImage( &A_8sC3  );
        cvReleaseImage( &A_32fC3 );
        cvReleaseImage( &B_8uC3  );
        cvReleaseImage( &B_8sC3  );
        cvReleaseImage( &B_32fC3 );
        cvReleaseImage( &mask    );
    } /* Nx */

/*trsWrite (TW_RUN|TW_CON|TW_SUM," %d norm  %s%s flavor  fail:  %g %g\n",
          it+1, f1, f2, norm, testnorm);*/

    if(nerr) return trsResult( TRS_FAIL, "Algorithm test has passed. %d errors.", nerr );
    else    return trsResult( TRS_OK, "Algorithm test has passed successfully" );

} /* fmaNorm */
/*------------------------------------------------ Initialize function ------------------- */
void InitANormMask( void )
{
    trsReg( FuncName, TestName, TestClass, fmaNormMask );
} /* InitANorm */

/* End of file. */
