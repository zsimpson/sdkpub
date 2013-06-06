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

#define DOT     0
#define CROSS   1
#define TRACE   2
#define MT      3
#define PP      4
#define EV      5
#define DET     6

#include "cvmtest.h"
#include <float.h>
#define PI  3.141593f
#define FEPS 1.0e-5
#define DEPS 1.0e-10

/* Testing parameters */
static char* func_names[] =
{
    "cvmDotProduct",
    "cvmCrossProduct",
    "cvmTrace",
    "cvmMulTransposed",
    "cvmPerspectiveProject",
	"cvmEigenVV",
	"cvmDet"
};

static char* test_desc = "Matrix - Matrix operations (2)";
static int max_length, length1, length2, ntests;
static int step;
static int read_param = 0;
static int test_type=6;

#include "amatrix.inc"

static int fcaMatrMatr2( void* prm )
{
    int i, j, it;
    const int nh = 20;
    int        Errors = 0;
    long lParam = (long)prm;
    double result, result0;
    CvMat fSrc1, fSrc2, fDst1, fDst2, dSrc1, dSrc2, dDst1, dDst2, dDst1a, dDst2a;
    CvMatArray fSrc, dSrc, fDst, dDst;
    AtsRandState state, stt;
      
    /* Initialization global parameters */
    if( !read_param )
    {
        /* Determine which tests are needed to run */
        trsCaseRead( &test_type, "/D/C/T/M/P/E/DET/a", "a",
        "a - all, D - dot product, C - cross product, T - trace, M - multiply transpose, "
        "P - perspective projection, E - eigen values and vectors, DET - determinant" );
        
        /* Reading test-parameters */
        trsiRead( &ntests,     "25", " number of tests" );
        trsiRead( &max_length, "32", " maximal size of matrices" );
        read_param = 1;
    }
    if((test_type!=7)&&(test_type!=lParam)) return TRS_UNDEF;

    atsRandInit( &state, -256.0, 256.0, 10 );
    atsRandInit( &stt, 1.001, max_length+0.999, 13 );

    for( it=0; it<ntests; it++ )
    {

        switch( lParam )
        {
		case DOT:
                length1 = atsRand32s( &stt );

                fSrc1 = cvMat(length1, 1, CV_MAT32F, NULL);
                fSrc2 = cvMat(length1, 1, CV_MAT32F, NULL);
                dSrc1 = cvMat(length1, 1, CV_MAT64D, NULL);
                dSrc2 = cvMat(length1, 1, CV_MAT64D, NULL);
            	cvmAlloc(&fSrc1);
            	cvmAlloc(&fSrc2);
            	cvmAlloc(&dSrc1);
            	cvmAlloc(&dSrc2);

                atsbRand32f( &state, fSrc1.data.fl, length1 );
                atsbRand32f( &state, fSrc2.data.fl, length1 );
                __fl2db( fSrc1.data.fl, dSrc1.data.db, length1 );
                __fl2db( fSrc2.data.fl, dSrc2.data.db, length1 );
                result  = cvmDotProduct( &fSrc1, &fSrc2 );
                result0 =  __DotProduct( dSrc1.data.db, dSrc2.data.db, length1 );
                if( fabs( ( result - result0 )/result0 ) > FEPS ) Errors++;
        
                atsbRand64d( &state, dSrc1.data.db, length1 );
                atsbRand64d( &state, dSrc2.data.db, length1 );
                result  = cvmDotProduct( &dSrc1, &dSrc2 );
                result0 =  __DotProduct( dSrc1.data.db, dSrc2.data.db, length1 );
                if( fabs( ( result - result0 )/result0 ) > DEPS ) Errors++;

                cvmFree(&fSrc1);
                cvmFree(&fSrc2);
                cvmFree(&dSrc1);
                cvmFree(&dSrc2);
            break;

		case CROSS:
                fSrc1 = cvMat(3, 1, CV_MAT3x1_32F, NULL);
                fSrc2 = cvMat(3, 1, CV_MAT3x1_32F, NULL);
                dSrc1 = cvMat(3, 1, CV_MAT3x1_64D, NULL);
                dSrc2 = cvMat(3, 1, CV_MAT3x1_64D, NULL);
                fDst1 = cvMat(3, 1, CV_MAT3x1_32F, NULL);
                fDst2 = cvMat(3, 1, CV_MAT3x1_32F, NULL);
                dDst1 = cvMat(3, 1, CV_MAT3x1_64D, NULL);
                dDst2 = cvMat(3, 1, CV_MAT3x1_64D, NULL);
            	cvmAlloc(&fSrc1);
            	cvmAlloc(&fSrc2);
            	cvmAlloc(&dSrc1);
            	cvmAlloc(&dSrc2);
            	cvmAlloc(&fDst1);
            	cvmAlloc(&fDst2);
            	cvmAlloc(&dDst1);
            	cvmAlloc(&dDst2);

                atsbRand32f( &state, fSrc1.data.fl, 3 );
                atsbRand32f( &state, fSrc2.data.fl, 3 );
                __fl2db( fSrc1.data.fl, dSrc1.data.db, 3 );
                __fl2db( fSrc2.data.fl, dSrc2.data.db, 3 );
                __CrossProduct( dSrc1.data.db, dSrc2.data.db, dDst2.data.db );
                cvmCrossProduct( &fSrc1, &fSrc2, &fDst1 );
                __fl2db( fDst1.data.fl, dDst1.data.db, 3 );
                Errors += atsCompDoublePrec( dDst1.data.db ,dDst2.data.db, 3, FEPS );
        
                cvmFree(&fSrc1);
                cvmFree(&fSrc2);
                cvmFree(&dSrc1);
                cvmFree(&dSrc2);
                cvmFree(&fDst1);
                cvmFree(&fDst2);
                cvmFree(&dDst1);
                cvmFree(&dDst2);
            break;

        case TRACE:
                length1 = atsRand32s( &stt );
                length2 = atsRand32s( &stt );

                fSrc1 = cvMat(length1, length2, CV_MAT32F, NULL);
                dSrc1 = cvMat(length1, length2, CV_MAT64D, NULL);
            	cvmAlloc(&fSrc1);
            	cvmAlloc(&dSrc1);

                atsbRand32f( &state, fSrc1.data.fl, length1*length2 );
                __fl2db( fSrc1.data.fl, dSrc1.data.db, length1*length2 );
                result  = cvmTrace( &fSrc1 );
                result0 =  __Trace( dSrc1.data.db, length1, length2 );
                if( fabs( ( result - result0 )/result0 ) > FEPS ) Errors++;
        
                atsbRand64d( &state, dSrc1.data.db, length1*length2 );
                result  = cvmTrace( &dSrc1 );
                result0 =  __Trace( dSrc1.data.db, length1, length2 );
                if( fabs( ( result - result0 )/result0 ) > DEPS ) Errors++;

                cvmFree(&fSrc1);
                cvmFree(&dSrc1);
            break;

        case MT:
                length1 = atsRand32s( &stt );
                length2 = atsRand32s( &stt );

                fSrc1 = cvMat(length1, length2, CV_MAT32F, NULL);
                fDst1 = cvMat(length1, length1, CV_MAT32F, NULL);
                fDst2 = cvMat(length2, length2, CV_MAT32F, NULL);
                dSrc1 = cvMat(length1, length2, CV_MAT64D, NULL);
                dDst1 = cvMat(length1, length1, CV_MAT64D, NULL);
                dDst2 = cvMat(length2, length2, CV_MAT64D, NULL);
                dDst1a= cvMat(length1, length1, CV_MAT64D, NULL);
                dDst2a= cvMat(length2, length2, CV_MAT64D, NULL);
            	cvmAlloc(&fSrc1);
            	cvmAlloc(&dSrc1);
            	cvmAlloc(&fDst1);
            	cvmAlloc(&fDst2);
            	cvmAlloc(&dDst1);
            	cvmAlloc(&dDst2);
            	cvmAlloc(&dDst1a);
            	cvmAlloc(&dDst2a);

                atsbRand32f( &state, fSrc1.data.fl, length1*length2 );
                __fl2db( fSrc1.data.fl, dSrc1.data.db, length1*length2 );
                cvmMulTransposed( &fSrc1, &fDst1, 0 );
                __MulTrans( dSrc1.data.db, dDst1.data.db, length1, length2, 0 );
                for( i=0; i<length1*length1; i++ )
                {
                    double r1 = (double)fDst1.data.fl[i];
                    double r2 =         dDst1.data.db[i];
                    if( fabs( ( r1 - r2 )/r2 ) > 50.0*FEPS ) { Errors++;/* printf( " fl., var. 1:  %g  %g  err = %g\n", r1, r2, fabs( ( r1 - r2 )/r2 ) );*/ }
                }
        
                cvmMulTransposed( &fSrc1, &fDst2, 1 );
                __MulTrans( dSrc1.data.db, dDst2.data.db, length1, length2, 1 );
                for( i=0; i<length2*length2; i++ )
                {
                    double r1 = (double)fDst2.data.fl[i];
                    double r2 =         dDst2.data.db[i];
                    if( fabs( ( r1 - r2 )/r2 ) > 50.0*FEPS ) { Errors++;/* printf( " fl., var. 2:  %g  %g  err = %g\n", r1, r2, fabs( ( r1 - r2 )/r2 ) );*/ }
                }
        
                atsbRand64d( &state, dSrc1.data.db, length1*length2 );
                cvmMulTransposed( &dSrc1, &dDst1a, 0 );
                __MulTrans( dSrc1.data.db, dDst1.data.db, length1, length2, 0 );
                for( i=0; i<length1*length1; i++ )
                {
                    double r1 = dDst1a.data.db[i];
                    double r2 =  dDst1.data.db[i];
                    if( fabs( ( r1 - r2 )/r2 ) > DEPS ) { Errors++;/* printf( " db., var. 1:  %g  %g  err = %g\n", r1, r2, fabs( ( r1 - r2 )/r2 ) ); */}
                }
        
                cvmMulTransposed( &dSrc1, &dDst2a, 1 );
                __MulTrans( dSrc1.data.db, dDst2.data.db, length1, length2, 1 );
                for( i=0; i<length2*length2; i++ )
                {
                    double r1 = dDst2a.data.db[i];
                    double r2 =  dDst2.data.db[i];
                    if( fabs( ( r1 - r2 )/r2 ) > DEPS ) { Errors++;/* printf( " db., var. 2:  %g  %g  err = %g\n", r1, r2, fabs( ( r1 - r2 )/r2 ) ); */}
                }

                cvmFree(&fSrc1);
                cvmFree(&dSrc1);
                cvmFree(&fDst1);
                cvmFree(&dDst1);
                cvmFree(&fDst2);
                cvmFree(&dDst2);
                cvmFree(&dDst1a);
                cvmFree(&dDst2a);
            break;

        case EV:
                length1 = atsRand32s( &stt );

                fSrc1 = cvMat(length1, length1, CV_MAT32F, NULL);
                fSrc2 = cvMat(length1, length1, CV_MAT32F, NULL);
                fDst1 = cvMat(length1, length1, CV_MAT32F, NULL);
                fDst2 = cvMat(length1, 1,       CV_MAT32F, NULL);
                dSrc1 = cvMat(length1, length1, CV_MAT64D, NULL);
                dSrc2 = cvMat(length1, length1, CV_MAT64D, NULL);
                dDst1 = cvMat(length1, length1, CV_MAT64D, NULL);
                dDst2 = cvMat(length1, 1,       CV_MAT64D, NULL);
            	cvmAlloc(&fSrc1);
            	cvmAlloc(&fSrc2);
            	cvmAlloc(&dSrc1);
            	cvmAlloc(&dSrc2);
            	cvmAlloc(&fDst1);
            	cvmAlloc(&fDst2);
            	cvmAlloc(&dDst1);
            	cvmAlloc(&dDst2);

                atsbRand32f( &state, fSrc1.data.fl, length1*length1 );
                atsbRand64d( &state, dSrc1.data.db, length1*length1 );

                /* Symmetrize */
                for( i=1; i<length1; i++ )
                {
                    int in = i*length1;
                    for( j=0; j<i; j++ )
                    {
                        int jn = j*length1;
                        fSrc1.data.fl[in+j] = fSrc1.data.fl[jn+i];
                        dSrc1.data.db[in+j] = dSrc1.data.db[jn+i];
                    }
                }

                /* Clone */
                cvmCopy( &fSrc1, &fSrc2 );
                cvmCopy( &dSrc1, &dSrc2 );

                /* Library function call */
                cvmEigenVV( &fSrc1, &fDst1, &fDst2, 1.0e-7  );
                cvmEigenVV( &dSrc1, &dDst1, &dDst2, 1.0e-15 );

                /* Check */
                for( i=0; i<length1; i++ )
                {
                    int in = i*length1;
                    double eps = 1.0e1*FEPS, deps = DEPS, fN1, fN2, dN1, dN2;

                    if( length1 > 24 ) { eps = 1.0e-4; deps = 1.0e-9; }
                    if( length1 > 48 ) { eps = 2.0e-3; deps = 1.0e-8; }
                    fN1 = fN2 = dN1 = dN2 = 0;

                    for( j=0; j<length1; j++ )
                    {
                        int jn = j*length1, l;
                        double fn1 = 0, fn2, dn1 = 0, dn2;

                        for( l=0; l<length1; l++ )
                        {
                            fn1 += (double)(fSrc2.data.fl[jn+l]) * (double)(fDst1.data.fl[in+l]);
                            dn1 += dSrc2.data.db[jn+l] * dDst1.data.db[in+l];
                        }

                        fn2  = (double)(fDst2.data.fl[i]) * (double)(fDst1.data.fl[in+j]);
                        dn2  = dDst2.data.db[i] * dDst1.data.db[in+j];
                        fN1 += fn1*fn1;
                        fN2 += fn2*fn2;
                        dN1 += dn1*dn1;
                        dN2 += dn2*dn2;
                    }

                    fN1 = sqrt( fN1 );
                    fN2 = sqrt( fN2 );
                    dN1 = sqrt( dN1 );
                    dN2 = sqrt( dN2 );
                    if( fabs( ( fN1 - fN2 )/fN1 ) > eps  ) { Errors++;/* printf( " n = %d   %g  %g   err = %g\n", length1, fN1, fN2, fabs( ( fN1 - fN2 )/fN1 ) );*/ }
                    if( fabs( ( dN1 - dN2 )/dN1 ) > deps ) Errors++;
                }

                cvmFree(&fSrc1);
                cvmFree(&fSrc2);
                cvmFree(&dSrc1);
                cvmFree(&dSrc2);
                cvmFree(&fDst1);
                cvmFree(&dDst1);
                cvmFree(&fDst2);
                cvmFree(&dDst2);
            break;

        case PP:
            {
                double* buf;
                buf = (double*)malloc( 4*sizeof(double) );

                length1 = atsRand32s( &stt );

                fSrc1 = cvMat(4, 4, CV_MAT4x4_32F, NULL);
                dSrc1 = cvMat(4, 4, CV_MAT4x4_64D, NULL);
                fSrc  = cvMatArray( 3, 1, CV_MAT3x1_32F, length1, NULL );
                dSrc  = cvMatArray( 3, 1, CV_MAT3x1_64D, length1, NULL );
                fDst  = cvMatArray( 3, 1, CV_MAT3x1_32F, length1, NULL );
                dDst  = cvMatArray( 3, 1, CV_MAT3x1_64D, length1, NULL );
            	cvmAlloc(&fSrc1);
            	cvmAlloc(&dSrc1);
            	cvmAllocArray(&fSrc);
            	cvmAllocArray(&dSrc);
            	cvmAllocArray(&fDst);
            	cvmAllocArray(&dDst);

                atsbRand32f( &state, fSrc1.data.fl, 16 );
                atsbRand64d( &state, dSrc1.data.db, 16 );
                atsbRand32f( &state, fSrc.data.fl, 3*length1 );
                atsbRand64d( &state, dSrc.data.db, 3*length1 );
                atsbRand32f( &state, fDst.data.fl, 3*length1 );
                atsbRand64d( &state, dDst.data.db, 3*length1 );

                cvmPerspectiveProject( &fSrc1, &fSrc, &fDst );

                for( i=0; i<length1; i++ )
                {
                    int in = 3*i;
                    for( j=0; j<4; j++ )
                    {
                        int jn = 4*j;
                        buf[j] = (double)fSrc1.data.fl[jn]  *(double)fSrc.data.fl[in]   + 
                                 (double)fSrc1.data.fl[jn+1]*(double)fSrc.data.fl[in+1] +
                                 (double)fSrc1.data.fl[jn+2]*(double)fSrc.data.fl[in+2] +
                                 (double)fSrc1.data.fl[jn+3];
                    }
                    if( !buf[3] ) buf[3] = 1.0;
                    buf[0] /= buf[3];
                    buf[1] /= buf[3];
                    buf[2] /= buf[3];

                    /* comparison */
                    for( j=0; j<3; j++ )
                    {
                        double w = (double)fDst.data.fl[in+j];
                        if( fabs( (buf[j]-w)/buf[j] ) > FEPS  ) Errors++;
                    }
                }

                cvmFree(&fSrc1);
                cvmFree(&dSrc1);
                cvmFreeArray(&fSrc);
                cvmFreeArray(&dSrc);
                cvmFreeArray(&fDst);
                cvmFreeArray(&dDst);
                free(buf);
                break;
            }

        case DET:
                length1 = atsRand32s( &stt );

                fSrc1 = cvMat(length1, length1, CV_MAT32F, NULL);
                dSrc1 = cvMat(length1, length1, CV_MAT64D, NULL);
                dSrc2 = cvMat(length1, length1, CV_MAT64D, NULL);
            	cvmAlloc(&fSrc1);
            	cvmAlloc(&dSrc1);
            	cvmAlloc(&dSrc2);

                atsbRand32f( &state, fSrc1.data.fl, length1*length1 );
                atsbRand64d( &state, dSrc1.data.db, length1*length1 );
                __fl2db( fSrc1.data.fl, dSrc2.data.db, length1*length1 );

                result = 0.0;

                result  = cvmDet( &fSrc1 );
                result0 =  __Det( dSrc2.data.db, length1 );
                if( fabs( ( result - result0 )/result0 ) > 10.0*FEPS )
                {
                    Errors++;
                  /*  printf( " Nt = %2d   float:  n = %3d   D = %12.5g   Do = %12.5g     rel.err. = %12.5g\n",
                    it, length1, result, result0, fabs( ( result - result0 )/result0 ) );*/
                }
        
                result  = cvmDet( &dSrc1 );
                result0 =  __Det( dSrc1.data.db, length1 );
                if( fabs( ( result - result0 )/result0 ) > DEPS )
                {
                    Errors++;
                  /*  printf( " Nt = %2d  double:  n = %3d   D = %12.5g   Do = %12.5g     rel.err. = %12.5g\n",
                    it, length1, result, result0, fabs( ( result - result0 )/result0 ) ); */
                }

                cvmFree(&fSrc1);
                cvmFree(&dSrc1);
                cvmFree(&dSrc2);

                /*  Test on the Hilbert matrices  */

                if( it >= 2 && it <= nh )
                {
                    static double hdet[nh-1] = { 8.333333333333333e-002,  // Values calculated with MatLab
                                          4.629629629629615e-004,
                                          1.653439153439300e-007,
                                          3.749295132515225e-012,
                                          5.367299886816844e-018,
                                          4.835802608198560e-025,
                                          2.737050135446322e-033,
                                          9.720265326886592e-043,
                                          2.164405264621389e-053,
                                          3.027279056572940e-065,
                                          2.858071296533713e-078,
                                          4.448044215086200e-092,
                                         -3.921999626288328e-107,
                                         -2.190299969119358e-120,
                                          2.424034479836854e-135,
                                          6.262835142564319e-150,
                                         -5.631269053071585e-166,
                                         -2.231620266630412e-180,
                                         -1.100432794334090e-195 };
                    length1 = it;

                    dSrc1 = cvMat(length1, length1, CV_MAT64D, NULL);
            	 	cvmAlloc(&dSrc1);

                     for( i=0; i<length1; i++ )
                         for( j=0; j<length1; j++ )
                             dSrc1.data.db[i*length1 + j] = 1.0e0/(double)(i+j+1);

                     result0 = hdet[it-2];

                     result = cvmDet( &dSrc1 );
                   /*result =  __Det( dSrc1.data.db, length1 );*/
                     if( fabs( ( result - result0 )/result0 ) > DEPS )
                     {
                         Errors++;
                   /*    printf( "  Nt = %d   Hilbert: n = %d   %g  %g    rel.err. = %g\n",
                         it, length1, result, result0, fabs( ( result - result0 )/result0 ) );*/
                     }

                  /*   if(it == 2 ) printf( "\n Test on the Hilbert matrices :\n\n" );
                     printf( " n = %2d :    D = %23.15e    Do = %23.15e    err = %9.3g\n",
                         it, result, result0, fabs( ( result - result0 )/result0 ) );*/

                     cvmFree(&dSrc1);
                }

            break;

        default:
            return trsResult( TRS_FAIL, "Incorrect test type: ", lParam );

        }

    } /* test number */
	    
    
    if( Errors == 0 ) return trsResult( TRS_OK, "No errors fixed for this test" );
    else return trsResult( TRS_FAIL, "Total fixed %d errors", Errors );
}


void InitAMatr2( void )
{
    /* Registering test functions */
	trsRegArg( func_names[0], test_desc, atsAlgoClass, fcaMatrMatr2, DOT   );
	trsRegArg( func_names[1], test_desc, atsAlgoClass, fcaMatrMatr2, CROSS );
    trsRegArg( func_names[2], test_desc, atsAlgoClass, fcaMatrMatr2, TRACE );
    trsRegArg( func_names[3], test_desc, atsAlgoClass, fcaMatrMatr2, MT    );
    trsRegArg( func_names[4], test_desc, atsAlgoClass, fcaMatrMatr2, PP    );
    trsRegArg( func_names[5], test_desc, atsAlgoClass, fcaMatrMatr2, EV    );
    trsRegArg( func_names[6], test_desc, atsAlgoClass, fcaMatrMatr2, DET   );
} /* InitAMatrMatr */
/* End of File */
