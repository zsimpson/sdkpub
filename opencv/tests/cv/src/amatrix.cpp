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

#ifdef WIN32

#define ADD     0
#define SUB     1
#define SCALE   2
#define MULT    3
#define TRANSP  4
#define INVERT  5
#define MAHAL   6

#include "cvmtest.h"
#include <float.h>
#define PI  3.1415f
#define FEPS 0.001f

/* Testing parameters */
static char* func_names[] =
{
    "cvmAdd",
    "cvmSub",
    "cvmScale",
    "cvmMul",
    "cvmTranspose",
	"cvmInvert",
	"cvmMahalanobis"
};

static char* test_desc = "Matrix - Matrix operations";
static int max_length;
static int step;
static int read_param = 0;
static int test_type=6;

static int fcaMatrMatr( void* prm )
{
    double success_error_level = 1e-3;
    int i,j, iter;
    long    lParam = (long)prm;
    unsigned seed = (unsigned)-1; //atsGetSeed();
    double  max_err = 0;
	
    AtsRandState state;

    static int  read_param = 0;
    /* Initialization global parameters */
    if( !read_param )
    {
        /* Determine which tests are needed to run */
        trsCaseRead( &test_type, "/A/S/SC/M/T/I/a", "a",
        "a - all, A - add, S - sub, SC - scale, M - multiply, T-Transpose,I - Invert" );
        
        /* Reading test-parameters */
        trsiRead( &max_length, "30", " size of matrices" );
        read_param = 1;
    }
    if((test_type!=6)&&(test_type!=lParam)) return TRS_UNDEF;

    atsRandInit( &state, -10, 10, seed );

    for( iter = 0; iter < 100; iter++ )
    {
        double  error = 0;
        int length = atsRandPlain32s( &state ) % max_length + 1;

	    CvMat flSrcV1 = cvMat(length,1,CV_MAT32F,NULL);
	    CvMat flSrcV2 = cvMat(length,1,CV_MAT32F,NULL);
        CvMat flsrc1 = cvMat(length, length,CV_MAT32F,NULL);
	    CvMat flsrc2 = cvMat(length, length,CV_MAT32F,NULL);
	    CvMat fldst = cvMat(length, length,CV_MAT32F,NULL);
	    CvMat flmklDest = cvMat(length, length,CV_MAT32F,NULL);
	    CvMat flmklZero = cvMat(length, length,CV_MAT32F,NULL);
	    CvMat flmklUnit = cvMat(length, length,CV_MAT32F,NULL);
	    CvMat dbsrc1 = cvMat(length, length,CV_MAT64D,NULL);
	    CvMat dbsrc2 = cvMat(length, length,CV_MAT64D,NULL);
	    CvMat dbdst = cvMat(length, length,CV_MAT64D,NULL);
	    CvMat dbmklDest = cvMat(length, length,CV_MAT64D,NULL);
	    CvMat dbmklZero = cvMat(length, length,CV_MAT64D,NULL);
	    CvMat dbmklUnit = cvMat(length, length,CV_MAT64D,NULL);

	    cvmAlloc(&flSrcV1);
	    cvmAlloc(&flSrcV2);
	    cvmAlloc(&flsrc1);
	    cvmAlloc(&flsrc2);
	    cvmAlloc(&fldst);
	    cvmAlloc(&flmklZero);
	    cvmAlloc(&flmklUnit);
	    cvmAlloc(&flmklDest);
	    cvmAlloc(&dbsrc1);
	    cvmAlloc(&dbsrc2);
	    cvmAlloc(&dbdst);
	    cvmAlloc(&dbmklZero);
	    cvmAlloc(&dbmklUnit);
	    cvmAlloc(&dbmklDest);
	    
        atsbRand32f( &state, flSrcV1.data.fl, length );
        atsbRand32f( &state, flSrcV2.data.fl, length );
	    atsbRand32f( &state, flsrc1.data.fl, length*length );
        atsbRand32f( &state, flsrc2.data.fl, length*length );
	    atsbRand64d( &state, dbsrc1.data.db, length*length );
	    atsbRand64d( &state, dbsrc2.data.db, length*length );

        cvmSetZero(&flmklZero);
        cvmSetIdentity(&flmklUnit);
	    cvmSetZero(&dbmklZero);
        cvmSetIdentity(&dbmklUnit);

        switch( lParam )
        {
            case ADD:
                 cvmAdd( &flsrc1,&flsrc2,&fldst);
			     cvmCopy(&flsrc2,&flmklDest);
                 /* mkl check */
                 cblas_sgemm( CblasRowMajor, CblasNoTrans, CblasNoTrans,
                             length, length, length, 1,flsrc1.data.fl,length,
                             flmklUnit.data.fl,length,1,flmklDest.data.fl,length);
                /* check */
                 error = atsCompSinglePrec( flmklDest.data.fl ,fldst.data.fl, length*length, FEPS );
                 max_err = MAX( max_err, error );

			     cvmAdd(&dbsrc1,&dbsrc2,&dbdst);
			     cvmCopy(&dbsrc2,&dbmklDest);
                 /* mkl check */
                 cblas_dgemm( CblasRowMajor, CblasNoTrans, CblasNoTrans,
                             length, length, length, 1,dbsrc1.data.db,length,
                             dbmklUnit.data.db,length,1,dbmklDest.data.db,length);
                /* check */
                 error = atsCompDoublePrec( dbmklDest.data.db ,dbdst.data.db, length*length, FEPS );
                 max_err = MAX( max_err, error );
			     
			     
                break;
            case SUB:
                 cvmSub( &flsrc1,&flsrc2,&fldst);
			     cvmCopy(&flsrc2,&flmklDest);
                 /* mkl check */
                 cblas_sgemm( CblasRowMajor, CblasNoTrans, CblasNoTrans,
                             length, length, length, 1,flsrc1.data.fl,length,
                             flmklUnit.data.fl,length,-1,flmklDest.data.fl,length);
                /* check */
                 error = atsCompSinglePrec( flmklDest.data.fl ,fldst.data.fl, length*length, FEPS );
                 max_err = MAX( max_err, error );

			     cvmSub(&dbsrc1,&dbsrc2,&dbdst);
			     cvmCopy(&dbsrc2,&dbmklDest);
                 /* mkl check */
                 cblas_dgemm( CblasRowMajor, CblasNoTrans, CblasNoTrans,
                             length, length, length, 1,dbsrc1.data.db,length,
                             dbmklUnit.data.db,length,-1,dbmklDest.data.db,length);
                /* check */
                 error = atsCompDoublePrec( dbmklDest.data.db ,dbdst.data.db, length*length, FEPS );
                 max_err = MAX( max_err, error );

			     break;
		    case SCALE:
                 cvmScale(&flsrc2,&fldst,PI);
                 cvmCopy(&flsrc2,&flmklDest);
			     /* mkl check */
                 cblas_sgemm( CblasRowMajor, CblasNoTrans, CblasNoTrans,
                             length, length, length, 1,flmklZero.data.fl,length,
                             flmklZero.data.fl,length,PI,flmklDest.data.fl,length);
                 /* check */
                 error = atsCompSinglePrec( flmklDest.data.fl ,fldst.data.fl, length*length, FEPS );
                 max_err = MAX( max_err, error );

			     cvmScale(&dbsrc2,&dbdst,PI);
                 cvmCopy(&dbsrc2,&dbmklDest);
			     /* mkl check */
                 cblas_dgemm( CblasRowMajor, CblasNoTrans, CblasNoTrans,
                             length, length, length, 1,dbmklZero.data.db,length,
                             dbmklZero.data.db,length,PI,dbmklDest.data.db,length);
                 /* check */
                 error = atsCompDoublePrec( dbmklDest.data.db ,dbdst.data.db, length*length, FEPS );
                 max_err = MAX( max_err, error );

            break;
            case MULT:
                 cvmMul(&flsrc1,&flsrc2,&fldst) ;
                           
                 /* mkl check */
                 cblas_sgemm( CblasRowMajor, CblasNoTrans, CblasNoTrans,
                             length, length, length, 1, flsrc1.data.fl, length,
                             flsrc2.data.fl,length,0,flmklZero.data.fl,length);
                 error = atsCompSinglePrec( flmklZero.data.fl ,fldst.data.fl, length*length, FEPS );      
                 max_err = MAX( max_err, error );

			     cvmMul(&dbsrc1,&dbsrc2,&dbdst);
                           
                 /* mkl check */
                 cblas_dgemm( CblasRowMajor, CblasNoTrans, CblasNoTrans,
                             length, length, length, 1, dbsrc1.data.db, length,
                             dbsrc2.data.db,length,0,dbmklZero.data.db,length);
                 error = atsCompDoublePrec( dbmklZero.data.db ,dbdst.data.db, length*length, FEPS );
                 max_err = MAX( max_err, error );

            break;
            case TRANSP:
                 cvmTranspose(&flsrc1,&fldst);
    
                 /* get data to simple mode */
                 for(i = 0; i < length; i++)
                     for(j = 0; j < length; j++)
                     {
                         if(cvmGet(&flsrc1,i,j)!=cvmGet(&fldst,j,i))
					     error++;
                     }
			     cvmTranspose(&dbsrc1,&dbdst);
    
                 /* get data to simple mode */
                 for(i = 0; i < length; i++)
                     for(j = 0; j < length; j++)
                     {
                         if(cvmGet(&dbsrc1,i,j)!=cvmGet(&dbdst,j,i))
					        error++;
                     }
                 max_err = MAX( max_err, error );                     
            break;
		    case INVERT:
                 cvmInvert(&flsrc1,&flsrc2);
			     cvmMul(&flsrc1,&flsrc2,&fldst);
			     error = atsCompSinglePrec( flmklUnit.data.fl ,fldst.data.fl, length*length, FEPS );
                 max_err = MAX( max_err, error );

			     cvmInvert(&dbsrc1,&dbsrc2);
			     cvmMul(&dbsrc1,&dbsrc2,&dbdst);
			     error = atsCompDoublePrec( dbmklUnit.data.db ,dbdst.data.db, length*length, FEPS );
                 max_err = MAX( max_err, error );

            break;
		    case MAHAL:
			    
                cvMulTransposed( &flsrc1, &flsrc2, 0 );
                cvCopy( &flsrc2, &flsrc1 );

			    double testval =  cvmMahalanobis(&flSrcV1,&flSrcV2,&flsrc1);
			    cblas_saxpy(length,-1,flSrcV2.data.fl,1,flSrcV1.data.fl,1);
			    cblas_sgemv( CblasRowMajor,CblasNoTrans,length, length, 1, flsrc1.data.fl,length,flSrcV1.data.fl, 1,0,
                             flSrcV2.data.fl,1);
			    double val = sqrt(cblas_sdot(length,flSrcV1.data.fl,1,flSrcV2.data.fl,1));
			    error = fabs(val-testval);
                max_err = MAX( max_err, error );
        }

        cvmFree(&flSrcV1);
	    cvmFree(&flSrcV2);
        cvmFree(&flsrc1);
	    cvmFree(&flsrc2);
	    cvmFree(&fldst);
	    cvmFree(&flmklZero);
	    cvmFree(&flmklUnit);
	    cvmFree(&flmklDest);
	    cvmFree(&dbsrc1);
	    cvmFree(&dbsrc2);
	    cvmFree(&dbdst);
	    cvmFree(&dbmklZero);
	    cvmFree(&dbmklUnit);
	    cvmFree(&dbmklDest);

        if( max_err > success_error_level )
            goto test_exit;
    }
        
test_exit:
    if( max_err < success_error_level )
        return trsResult( TRS_OK, "No errors fixed for this text" );
    else
        return trsResult( TRS_FAIL, "Maximal error is %g at iter = %d, seed = %08x",
                          max_err, iter, seed );
}


void InitAMatr( void )
{
    /* Registering test functions */
    trsRegArg( func_names[0], test_desc, atsAlgoClass, fcaMatrMatr, ADD );
    trsRegArg( func_names[1], test_desc, atsAlgoClass, fcaMatrMatr, SUB );
    trsRegArg( func_names[2], test_desc, atsAlgoClass, fcaMatrMatr, SCALE );
    trsRegArg( func_names[3], test_desc, atsAlgoClass, fcaMatrMatr, MULT );
    trsRegArg( func_names[4], test_desc, atsAlgoClass, fcaMatrMatr, TRANSP );
	trsRegArg( func_names[5], test_desc, atsAlgoClass, fcaMatrMatr, INVERT );
	trsRegArg( func_names[6], test_desc, atsAlgoClass, fcaMatrMatr, MAHAL );
} /* InitAMatrMatr */

#else
void InitAMatr( void )
{
}
#endif /* WIN32 */

/* End of File */
