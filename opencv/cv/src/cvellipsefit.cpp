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

#include "_cv.h"
#include "_cvutils.h"
#include  <limits.h>
#include  <float.h>

IPCVAPI( CvStatus , icvFitEllipse_32f, ( CvPoint2D32f* points, int n, CvBox2D* box))

#if 1
/* for now this function works bad with singular cases
   You can see in the code, that when some troubles with
   matrices or some variables occur -
   box filled with zero values is returned.
   However in general function works fine.
*/
IPCVAPI_IMPL( CvStatus, icvFitEllipse_32f, (CvPoint2D32f * points, int n, CvBox2D32f * box) )
{
    CvStatus status = CV_OK;
    CvStatus status1;

    float u[6];

    CvMatr32f D = 0;
    float S[36];            /*  S = D' * D  */
    float C[36];

    float INVQ[36];

    /* transposed eigenvectors */
    float INVEIGV[36];

    /* auxulary matrices */
    float TMP1[36];
    float TMP2[36];

    int i, index = -1;
    float eigenvalues[6];
    float a, b, c, d, e, f;
    float offx, offy;
    float *matr;

    if( points == NULL || box == NULL )
        return CV_NULLPTR_ERR;
    if( n < 6 )
        return CV_BADSIZE_ERR;

    /* create matrix D of  input points */
    D = icvCreateMatrix_32f( 6, n );

    offx = offy = 0;
    /* shift all points to zero */
    for( i = 0; i < n; i++ )
    {
        offx += points[i].x;
        offy += points[i].y;
    }
    c = 1.f / n;
    offx *= c;
    offy *= c;

    /* fill matrix rows as (x*x, x*y, y*y, x, y, 1 ) */
    matr = D;
    for( i = 0; i < n; i++ )
    {
        float x = points[i].x - offx;
        float y = points[i].y - offy;

        matr[0] = x * x;
        matr[1] = x * y;
        matr[2] = y * y;
        matr[3] = x;
        matr[4] = y;
        matr[5] = 1.f;
        matr += 6;
    }

    /* compute S */
    status1 = icvMulTransMatrixR_32f( D, 6, n, S );
    assert( status1 == CV_OK );

    /* fill matrix C */
    icvSetZero_32f( C, 6, 6 );
    C[2] = 2.f;  //icvSetElement_32f( C, 6, 6, 0, 2, 2.f );
    C[7] = -1.f; //icvSetElement_32f( C, 6, 6, 1, 1, -1.f );
    C[12] = 2.f; //icvSetElement_32f( C, 6, 6, 2, 0, 2.f );
    
    /* find eigenvalues */
    status1 = icvJacobiEigens_32f( S, INVEIGV, eigenvalues, 6, 0.f );
    assert( status1 == CV_OK );

    //avoid troubles with small negative values
    for( i = 0; i < 6; i++ )
       eigenvalues[i] = (float)fabs( eigenvalues[i] ); 

    /* compute sqrt of every eigenvalue; they all must be positive */
    status1 = icvbSqrt_32f( eigenvalues, eigenvalues, 6 );
    assert( status1 == CV_OK );

    /* compute inverse of Q */
    status1 = icvbInvSqrt_32f( eigenvalues, eigenvalues, 6 );
    assert( status1 == CV_OK );

    for( i = 0; i < 6; i++ )
    {
        icvScaleVector_32f( &INVEIGV[i * 6], &INVEIGV[i * 6], 6, eigenvalues[i] );
    }

    // INVQ = transp(INVEIGV) * INVEIGV
    status1 = icvMulTransMatrixR_32f( INVEIGV, 6, 6, INVQ );
    assert( status1 == CV_OK );
    
    /* create matrix INVQ*C*INVQ */
    icvMulMatrix_32f( INVQ, 6, 6, C, 6, 6, TMP1 );
    icvMulMatrix_32f( TMP1, 6, 6, INVQ, 6, 6, TMP2 );

    /* find its eigenvalues and vectors */
    status1 = icvJacobiEigens_32f( TMP2, INVEIGV, eigenvalues, 6, 0.f );
    assert( status1 == CV_OK );
    /* search for positive eigenvalue */

    for( i = 0; i < 3; i++ )
    {
        if( eigenvalues[i] > 0 )
        {
            index = i;
            break;
        }
    }

    /* only 3 eigenvalues must be not zero 
       and only one of them must be positive 
       if it is not true - return zero result
    */
    if( index == -1 )
    {
        box->center.x = box->center.y = 
        box->size.width = box->size.height = 
        box->angle = 0.f;
        goto error;
    }

    /* now find truthful eigenvector */
    icvTransformVector_32f( INVQ, &INVEIGV[index * 6], u, 6, 6 );
    assert( status1 == CV_OK );
    /* extract vector components */
    a = u[0];
    b = u[1];
    c = u[2];
    d = u[3];
    e = u[4];
    f = u[5];
    {
        /* extract ellipse axes from above values */

        /* 
           1) find center of ellipse 
           it satisfy equation  
           | a     b/2 | *  | x0 | +  | d/2 | = |0 |
           | b/2    c  |    | y0 |    | e/2 |   |0 |

         */
        float x0, y0;
        float idet = 1.f / (a * c - b * b * 0.25f);

        /* we must normalize (a b c d e f ) to fit (4ac-b^2=1) */
        float scale = cvSqrt( 0.25f * idet );

        if (!scale) 
        {
            box->center.x = box->center.y = 
            box->size.width = box->size.height = 
            box->angle = 0.f;
            goto error;
        }
           
        a *= scale;
        b *= scale;
        c *= scale;
        d *= scale;
        e *= scale;
        f *= scale;

        //x0 = box->center.x = (-d * c * 0.5f + e * b * 0.25f) * 4.f;
        //y0 = box->center.y = (-a * e * 0.5f + d * b * 0.25f) * 4.f;
        x0 = box->center.x = (-d * c + e * b * 0.5f) * 2.f;
        y0 = box->center.y = (-a * e + d * b * 0.5f) * 2.f;

        /* offset ellipse to (x0,y0) */
        /* new f == F(x0,y0) */
        f += a * x0 * x0 + b * x0 * y0 + c * y0 * y0 + d * x0 + e * y0;

        if (!f) 
        {
            box->center.x = box->center.y = 
            box->size.width = box->size.height = 
            box->angle = 0.f;
            goto error;
        }

        scale = -1.f / f;
        /* normalize to f = 1 */
        a *= scale;
        b *= scale;
        c *= scale;
    }
    /* recover center */
    box->center.x += offx;
    box->center.y += offy;

    /* extract axis of ellipse */
    /* one more eigenvalue operation */
    TMP1[0] = a;
    TMP1[1] = TMP1[2] = b * 0.5f;
    TMP1[3] = c;

    status1 = icvJacobiEigens_32f( TMP1, INVEIGV, eigenvalues, 2, 0.f );
    assert( status1 == CV_OK );

    /* exteract axis length from eigenvectors */
    box->size.height = 2 * cvInvSqrt( eigenvalues[0] );
    box->size.width = 2 * cvInvSqrt( eigenvalues[1] );

    if ( !(box->size.height && box->size.width) )
    {
        assert(0);
    }

    /* calc angle */
    box->angle = icvFastArctan32f( INVEIGV[3], INVEIGV[2] );

error:

    if( D )
        icvDeleteMatrix( D );

    return status1 < 0 ? status1 : status;
}

#else
IPCVAPI_IMPL( CvStatus, icvFitEllipse_32f, (CvPoint2D32f * points, int n, CvBox2D32f * box) )
{
    CvStatus status = CV_OK;
    CvStatus status1;

    float u[6];

    CvMatr32f D = 0;
    float S[36];            /*  S = D' * D  */
    float C[36];
    double S64[36]; /* 64d copy of S */
    

    float INVQ[36];

    /* transposed eigenvectors */
    float INVEIGV[36];

    /* auxulary matrices */
    float TMP1[36];
    float TMP2[36];

    int i, index = -1;
    float eigenvalues[6];
    float a, b, c, d, e, f;
    float offx, offy;
    float *matr;

    if( points == NULL || box == NULL )
        return CV_NULLPTR_ERR;
    if( n < 6 )
        return CV_BADSIZE_ERR;

    /* create matrix D of  input points */
    D = icvCreateMatrix_32f( 6, n );
    
    if( D == NULL )
    {
        status = CV_OUTOFMEM_ERR;
        goto error;
    }

    offx = offy = 0;
    /* shift all points to zero */
    for( i = 0; i < n; i++ )
    {
        offx += points[i].x;
        offy += points[i].y;
    }
    c = 1.f / n;
    offx *= c;
    offy *= c;

    /* fill matrix rows as (x*x, x*y, y*y, x, y, 1 ) */
    matr = D;
    for( i = 0; i < n; i++ )
    {
        float x = points[i].x - offx;
        float y = points[i].y - offy;

        matr[0] = x * x;
        matr[1] = x * y;
        matr[2] = y * y;
        matr[3] = x;
        matr[4] = y;
        matr[5] = 1.f;
        matr += 6;
    }

    /* compute S */
    status1 = icvMulTransMatrixR_32f( D, 6, n, S );
    assert( status1 == CV_OK );

    /* fill matrix C */
    status1 = icvSetZero_32f( C, 6, 6 );
    assert( status1 == CV_OK );
    C[2] = 2.f;  
    C[7] = -1.f; 
    C[12] = 2.f; 
    
    icvCvt_32f_64d( S, S64, 36 );
    
    double temp_buffer[128];
    icvPseudoInverse_64f( 6, 6, S64, 6, FLT_EPSILON, temp_buffer );
    
    icvCvtTo_32f_C1R( S64, S, 36, CV_64FC1 );
    status1 = icvMulMatrix6x6_32f( S, C, TMP2 );
    
    /* find its eigenvalues and vectors */
    status1 = icvJacobiEigens_32f( TMP2, INVEIGV, eigenvalues, 6, 0.f );
    assert( status1 == CV_OK );
    /* search for positive eigenvalue */
    index = -1;
    for( i = 0; i < 3; i++ )
    {
        if( eigenvalues[i] > 0 )
        {
            index = i;
            break;
        }
    }

    /* only 3 eigenvalues must be not zero 
       and only one of them must be positive 
       if it is not true - return zero result
    */
    if ( index == -1 )
    {
        box->center.x = box->center.y = 
        box->size.width = box->size.height = 
        box->angle = 0.f;
        goto error;
    }

    /* now find truthful eigenvector */
    //status1 = icvTransformVector_32f( INVQ, &INVEIGV[index * 6], u, 6, 6 );
    //assert( status1 == CV_OK );
    /* extract vector components */
    a = INVEIGV[index * 6];
    b = INVEIGV[index * 6 + 1];
    c = INVEIGV[index * 6 + 2];
    d = INVEIGV[index * 6 + 3];
    e = INVEIGV[index * 6 + 4];
    f = INVEIGV[index * 6 + 5];
    {
        /* extract ellipse axes from above values */

        /* 
           1) find center of ellipse 
           it satisfy equation  
           | a     b/2 | *  | x0 | +  | d/2 | = |0 |
           | b/2    c  |    | y0 |    | e/2 |   |0 |

         */
        float x0, y0;
        float idet = 1.f / (a * c - b * b * 0.25f);

        /* we must normalize (a b c d e f ) to fit (4ac-b^2=1) */
        float scale = cvSqrt( 0.25f * idet );

        a *= scale;
        b *= scale;
        c *= scale;
        d *= scale;
        e *= scale;
        f *= scale;

        //x0 = box->center.x = (-d * c * 0.5f + e * b * 0.25f) * 4.f;
        //y0 = box->center.y = (-a * e * 0.5f + d * b * 0.25f) * 4.f;
        x0 = box->center.x = (-d * c + e * b * 0.5f) * 2.f;
        y0 = box->center.y = (-a * e + d * b * 0.5f) * 2.f;

        /* offset ellipse to (x0,y0) */
        /* new f == F(x0,y0) */
        f += a * x0 * x0 + b * x0 * y0 + c * y0 * y0 + d * x0 + e * y0;

        if (!f) 
        {
            box->center.x = box->center.y = 
            box->size.width = box->size.height = 
            box->angle = 0.f;
            goto error;
        }

        scale = -1.f / f;
        /* normalize to f = 1 */
        a *= scale;
        b *= scale;
        c *= scale;
    }
    /* recover center */
    box->center.x += offx;
    box->center.y += offy;

    /* extract axis of ellipse */
    /* one more eigenvalue operation */
    TMP1[0] = a;
    TMP1[1] = TMP1[2] = b * 0.5f;
    TMP1[3] = c;

    status1 = icvJacobiEigens_32f( TMP1, INVEIGV, eigenvalues, 2, 0.f );
    assert( status1 == CV_OK );

    /* exteract axis length from eigenvectors */
    box->size.height = 2 * cvInvSqrt( eigenvalues[0] );
    box->size.width = 2 * cvInvSqrt( eigenvalues[1] );

    /* calc angle */
    box->angle = icvFastArctan32f( INVEIGV[3], INVEIGV[2] );

error:

    if( D )
        icvDeleteMatrix( D );

    return status;
}
#endif


//external 
CV_IMPL void
cvFitEllipse( CvPoint2D32f * points, int n, CvBox2D32f * box )
{
    CV_FUNCNAME( "cvFitEllipse" );

    __BEGIN__;

    IPPI_CALL( icvFitEllipse_32f( points, n, box ));

    __CLEANUP__;
    __END__;
}

/* End of file. */
