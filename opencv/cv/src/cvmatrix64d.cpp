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
#include "_cvwrap.h"

static float
square_32f( float x )
{
    return x * x;
}

/*====================================================================================*/


IPCVAPI_IMPL( CvStatus, icvComplexMult_32f, (CvMatr32f srcMatr,
                                             CvMatr32f dstMatr, int width, int height) )
{
    CvVect32f tmpMatr;
    CvVect32f tmpMatr2;
    CvMatr32f srcTrans;

    float *pMatr;
    float sum;
    int i, j, k;
    float *ps;
    float *pt;
    float *pti;
    float *ptj;
    float *ptk;
    float d;
    float *srcBase;
    float *dstBase;
    float *ptkBase;
    float *begRow;
    float *dstBase_i;
    int colShift;
    float coef;
    int shift;
    int shift_i, shift_j;
    int di, dj;
    int delta;
    int matrSize;

    matrSize = width;

#ifdef TRACE_TO_FILE
    int t;
    FILE *file;

    file = fopen( "E:\\test_matrix\\comples_mult.txt", "w" );

    fprintf( file, "\nSource matrix\n" );
    for( t = 0; t < width * height; t++ )
    {
        fprintf( file, "srcMatr[%d] = %f\n", t, srcMatr[t] );

    }
#endif
    tmpMatr = icvCreateVector_32f( (matrSize * (matrSize + 1)) / 2 );
    tmpMatr2 = icvCreateVector_32f( (matrSize * (matrSize + 1)) / 2 );
    srcTrans = icvCreateMatrix_32f( MAX( height, width ), width );

    /* Compute (AtA)-1 * At */

    /* Compute AtA and store in low triangular matrix */

    icvTransposeMatrix_32f( srcMatr, width, height, srcTrans );

#ifdef TRACE_TO_FILE
    fprintf( file, "\nSource matrix\n" );
    for( t = 0; t < width * height; t++ )
    {
        fprintf( file, "srcMatr[%d] = %f\n", t, srcMatr[t] );

    }

    fprintf( file, "\ntranspose source matrix\n" );
    for( t = 0; t < width * height; t++ )
    {
        fprintf( file, "srcTrans[%d] = %f\n", t, srcTrans[t] );
    }
#endif

    sum = 0;

    pMatr = tmpMatr;

    for( i = 0; i < width; i++ )
    {
        for( j = 0; j < i + 1; j++ )
        {
            *pMatr++ = (float)icvDotProduct_32f( srcTrans + i * height,
                                        srcTrans + j * height, height );
        }
    }


#ifdef TRACE_TO_FILE
    fprintf( file, "\nMult matrix\n" );
    for( t = 0; t < (matrSize * (matrSize + 1)) / 2; t++ )
    {
        fprintf( file, "tmpMatr[%d] = %f\n", t, tmpMatr[t] );
    }
#endif
    /* Apply cholesky decomposition */


    ps = tmpMatr;
    pt = tmpMatr2;
    pti = pt;

    for( i = 0; i < matrSize; i++ )
    {

        ptj = pt;               /* Get begin of the matrix */

        for( j = 0; j < i; j++ )
        {                       /*  By all elements in line of source */
            ptk = pti;          /* ti - current element of the matrix */
            sum = 0.0;
            k = j;

            while( k-- )
            {
                sum += (*ptj++) * (*ptk++);
            }
            *ptk = ((*ps++) - sum) / (*ptj++);
        }

        sum = 0.0;
        k = i;
        while( k-- )
        {
            sum += square_32f( *pti++ );
        }
        d = (*ps++) - sum;
        *pti++ = (float) sqrt( d );
    }

#ifdef TRACE_TO_FILE
    fprintf( file, "\nCholesky matrix (tmpMatr2)\n" );
    for( t = 0; t < (matrSize * (matrSize + 1)) / 2; t++ )
    {
        fprintf( file, "tmpMatr2[%d] = %f\n", t, tmpMatr2[t] );
    }
#endif

    /*  Find inverse matrix for triangular tmpMatr2 and strore in tmpMatr */


    icvSetZero_32f( tmpMatr, 1, (matrSize * (matrSize + 1)) / 2 );

    dstBase = tmpMatr;
    shift = 2;

    for( i = 0; i < matrSize; i++ )
    {
        *dstBase = 1.0;
        dstBase += shift;
        shift++;
    }

#ifdef TRACE_TO_FILE
    fprintf( file, "\nIdentical matrix (tmpMatr)\n" );
    for( t = 0; t < (matrSize * (matrSize + 1)) / 2; t++ )
    {
        fprintf( file, "tmpMatr[%d] = %f\n", t, tmpMatr[t] );
    }
#endif

    srcBase = tmpMatr2;
    dstBase = tmpMatr;
    ptk = tmpMatr;
    ptkBase = tmpMatr;

    for( i = 0; i < matrSize; i++ )
    {                           /* For each row */

        ptj = tmpMatr;

        for( j = 0; j < i; j++ )
        {                       /* for each element in row */
            coef = *srcBase++;  /* Get current coefficient */
            k = j + 1;

            ptk = ptkBase;
            while( k-- )
            {                   /* Multiplacate elements and subtruct */
                *(ptk++) -= coef * (*ptj++);
            }
        }

        k = i + 1;
        coef = 1.0f / (*srcBase++);

        while( k-- )
        {
            *ptkBase++ *= coef;
        }
    }

#ifdef TRACE_TO_FILE
    fprintf( file, "\nInv Cholesky matrix (tmpMatr)\n" );
    for( t = 0; t < (matrSize * (matrSize + 1)) / 2; t++ )
    {
        fprintf( file, "tmpMatr[%d] = %f\n", t, tmpMatr[t] );
    }
#endif

    /* Transpose this matrix for suitable computation tmpMatr -> tmpMatr2 */


    dstBase = tmpMatr2;
    srcBase = tmpMatr;
    begRow = tmpMatr;           /* begin of row for each cycle */

    shift = 2;

    for( i = 0; i < matrSize; i++ )
    {

        colShift = i + 1;


        ptj = begRow;

        for( j = 0; j < matrSize - i; j++ )
        {

            *dstBase++ = *ptj;

            ptj += colShift;
            colShift++;
        }

        begRow += shift;
        shift++;
    }

#ifdef TRACE_TO_FILE
    fprintf( file, "\nTranspose Inv Cholesky matrix (tmpMatr2)\n" );
    for( t = 0; t < (matrSize * (matrSize + 1)) / 2; t++ )
    {
        fprintf( file, "tmpMatr2[%d] = %f\n", t, tmpMatr2[t] );
    }
#endif

    /* multiplacate to itself (quadr) matrix tmpMatr2  */
    /* and store result in the srcTrans (quadr) */

    dstBase_i = srcTrans;

    shift_i = matrSize;

    pti = tmpMatr2;

    for( i = 0; i < matrSize; i++ )
    {
        dstBase = dstBase_i;
        dstBase_i += matrSize;

        ptj = tmpMatr2;

        shift_j = matrSize;

        for( j = 0; j < i + 1; j++ )
        {

            if( j < i )
            {
                dj = i - j;
                di = 0;
                delta = i;
            }
            else
            {
                dj = 0;
                di = j - i;
                delta = j;
            }

            *dstBase++ = (float)icvDotProduct_32f( pti + di, ptj + dj, matrSize - delta );
            ptj += shift_j;
            shift_j--;
        }

        pti += shift_i;
        shift_i--;

    }

    /* copy elements to up the diagonal */

    for( i = 0; i < matrSize - 1; i++ )
    {
        for( j = i + 1; j < matrSize; j++ )
        {
            srcTrans[i * matrSize + j] = srcTrans[j * matrSize + i];
        }
    }

#ifdef TRACE_TO_FILE
    fprintf( file, "\nMultiplacate matix not diagonal(srcTrans)\n" );
    for( i = 0; i < matrSize; i++ )
    {
        for( j = 0; j < matrSize; j++ )
        {
            fprintf( file, "srcTrans[%d,%d] = %f\n", i, j, srcTrans[i * matrSize + j] );
        }
        fprintf( file, "\n" );
    }
#endif


    /* Multiplicate this triangular matrix and transpose source */
    /* for suitable use not transpose matrix srcMatr */

    dstBase = dstMatr;

    pti = srcTrans;

    for( i = 0; i < matrSize; i++ )
    {

        ptj = srcMatr;

        for( j = 0; j < height; j++ )
        {
            *dstBase++ = (float)icvDotProduct_32f( pti, ptj, matrSize );
            ptj += width;
        }

        pti += matrSize;
    }

#ifdef TRACE_TO_FILE
    fprintf( file, "\nResult matrix (dstMatr)\n" );
    for( i = 0; i < width; i++ )
    {
        for( j = 0; j < height; j++ )
        {
            fprintf( file, "dstMatr[%d,%d] = %f\n", i, j, dstMatr[i * height + j] );
        }
        fprintf( file, "\n" );
    }
#endif


    icvDeleteMatrix( tmpMatr );
    icvDeleteMatrix( tmpMatr2 );
    icvDeleteMatrix( srcTrans );



#ifdef TRACE_TO_FILE
    fclose( file );
#endif

    return CV_NO_ERR;
}


#if 0
/*======================================================================================*/
IPCVAPI_IMPL( CvStatus, icvComplexMult_64d, (CvMatr64d srcMatr,
                                             CvMatr64d dstMatr, int width, int height) )
{
    double *tmpMatr;
    double *tmpMatr2;
    double *srcTrans;

    double *pMatr;
    double sum;
    int i, j, k;
    double *ps;
    double *pt;
    double *pti;
    double *ptj;
    double *ptk;
    double d;
    double *srcBase;
    double *dstBase;
    double *ptkBase;
    double *begRow;
    double *dstBase_i;
    int colShift;
    double coef;
    int shift;

/*    int         t; */
    int shift_i, shift_j;
    int di, dj;
    int delta;
    int matrSize;

#ifdef TRACE_TO_FILE
    FILE *file;
#endif
    matrSize = width;
/*
    file = fopen("E:\\test_matrix\\comples_mult.txt","w");

    fprintf(file,"\nSource matrix\n");
    for (t = 0; t < (matrSize * (matrSize )) ; t++) {
        fprintf(file,"srcMatr[%d] = %f\n",t,srcMatr[t]);
        
    }
*/

    tmpMatr = (double *) icvAlloc( (matrSize * (matrSize + 1)) / 2 * sizeof( double ));
    tmpMatr2 = (double *) icvAlloc( (matrSize * (matrSize + 1)) / 2 * sizeof( double ));
    srcTrans = (double *) icvAlloc( MAX( height, width ) * width * sizeof( double ));
    memset( tmpMatr, 0, (matrSize * (matrSize + 1)) / 2 * sizeof( double ));
    memset( tmpMatr2, 0, (matrSize * (matrSize + 1)) / 2 * sizeof( double ));
    memset( srcTrans, 0, MAX( height, width ) * width * sizeof( double ));

    /* Compute (AtA)-1 * At */

    /* Compute AtA and store in low triangular matrix */

    icvTransposeMatrix_64d( srcMatr, width, height, srcTrans );
/*
    fprintf(file,"\ntranspose source matrix\n");
    for (t = 0; t < width * height  ; t++) {
        fprintf(file,"srcTrans[%d] = %f\n",t,srcTrans[t]);
    }
*/
    sum = 0;

    pMatr = tmpMatr;

    for( i = 0; i < width; i++ )
    {
        for( j = 0; j < i + 1; j++ )
        {
            *pMatr++ = icvDotProduct_64d( srcTrans + i * height,
                                   srcTrans + j * height, height );
        }
    }

/*
    fprintf(file,"\nMult matrix\n");
    for (t = 0; t < (matrSize * (matrSize + 1)) / 2; t++) {
        fprintf(file,"tmpMatr[%d] = %f\n",t,tmpMatr[t]);
    }
*/
    /* Apply cholesky decomposition */


    ps = tmpMatr;
    pt = tmpMatr2;
    pti = pt;

    for( i = 0; i < matrSize; i++ )
    {

        ptj = pt;               /* Get begin of the matrix */

        for( j = 0; j < i; j++ )
        {                       /*  By all elements in line of source */
            ptk = pti;          /* ti - current element of the matrix */
            sum = 0.0;
            k = j;

            while( k-- )
            {
                sum += (*ptj++) * (*ptk++);
            }
            *ptk = ((*ps++) - sum) / (*ptj++);
        }

        sum = 0.0;
        k = i;
        while( k-- )
        {
            sum += ((*pti) * (*pti));
            pti++;
        }
        d = (*ps++) - sum;
/*
        if (d <= 0.0) {
            return CV_BADCOEF_ERR;
        }
*/
        *pti++ = sqrt( d );
    }

/*  
    fprintf(file,"\nCholesky matrix (tmpMatr2)\n");
    for (t = 0; t < (matrSize * (matrSize + 1)) / 2; t++) {
        fprintf(file,"tmpMatr2[%d] = %f\n",t,tmpMatr2[t]);
    }
*/

    /*  Find inverse matrix for triangular tmpMatr2 and strore in tmpMatr */


    icvSetZero_64d( tmpMatr, 1, (matrSize * (matrSize + 1)) / 2 );

    dstBase = tmpMatr;
    shift = 2;

    for( i = 0; i < matrSize; i++ )
    {
        *dstBase = 1.0;
        dstBase += shift;
        shift++;
    }
/*
    fprintf(file,"\nIdentical matrix (tmpMatr)\n");
    for (t = 0; t < (matrSize * (matrSize + 1)) / 2; t++) {
        fprintf(file,"tmpMatr[%d] = %f\n",t,tmpMatr[t]);
    }
*/
    srcBase = tmpMatr2;
    dstBase = tmpMatr;
    ptk = tmpMatr;
    ptkBase = tmpMatr;

    for( i = 0; i < matrSize; i++ )
    {                           /* For each row */

        ptj = tmpMatr;

        for( j = 0; j < i; j++ )
        {                       /* for each element in row */
            coef = *srcBase++;  /* Get current coefficient */
            k = j + 1;

            ptk = ptkBase;
            while( k-- )
            {                   /* Multiplacate elements and subtruct */
                *(ptk++) -= coef * (*ptj++);
            }
        }

        k = i + 1;
        coef = 1.0 / (*srcBase++);

        while( k-- )
        {
            *ptkBase++ *= coef;
        }
    }
/*
    fprintf(file,"\nInv Cholesky matrix (tmpMatr)\n");
    for (t = 0; t < (matrSize * (matrSize + 1)) / 2; t++) {
        fprintf(file,"tmpMatr[%d] = %f\n",t,tmpMatr[t]);
    }
*/

    /* Transpose this matrix for suitable computation tmpMatr -> tmpMatr2 */


    dstBase = tmpMatr2;
    srcBase = tmpMatr;
    begRow = tmpMatr;           /* begin of row for each cycle */

    shift = 2;

    for( i = 0; i < matrSize; i++ )
    {

        colShift = i + 1;


        ptj = begRow;

        for( j = 0; j < matrSize - i; j++ )
        {

            *dstBase++ = *ptj;

            ptj += colShift;
            colShift++;
        }

        begRow += shift;
        shift++;
    }
/*
    fprintf(file,"\nTranspose Inv Cholesky matrix (tmpMatr2)\n");
    for (t = 0; t < (matrSize * (matrSize + 1)) / 2; t++) {
        fprintf(file,"tmpMatr2[%d] = %f\n",t,tmpMatr2[t]);
    }
*/
    /* multiplacate to itself (quadr) matrix tmpMatr2  */
    /* and store result in the srcTrans (quadr) */

    dstBase_i = srcTrans;

    shift_i = matrSize;

    pti = tmpMatr2;

    for( i = 0; i < matrSize; i++ )
    {

        dstBase = dstBase_i;
        dstBase_i += matrSize;

        ptj = tmpMatr2;

        shift_j = matrSize;

        for( j = 0; j < i + 1; j++ )
        {

            if( j < i )
            {
                dj = i - j;
                di = 0;
                delta = i;
            }
            else
            {
                dj = 0;
                di = j - i;
                delta = j;
            }

            *dstBase++ = icvDotProduct_64d( pti + di, ptj + dj, matrSize - delta );
            ptj += shift_j;
            shift_j--;
        }

        pti += shift_i;
        shift_i--;

    }

    /* copy elements to up the diagonal */

    for( i = 0; i < matrSize - 1; i++ )
    {
        for( j = i + 1; j < matrSize; j++ )
        {
            srcTrans[i * matrSize + j] = srcTrans[j * matrSize + i];
        }
    }

/*
    fprintf(file,"\nMultiplacate matix not diagonal(srcTrans)\n");
    for(i = 0; i < matrSize; i++) {
        for (j = 0; j < matrSize; j++) {
            fprintf(file,"srcTrans[%d,%d] = %f\n",i,j,srcTrans[i * matrSize + j]);
        }
        fprintf(file,"\n");
    }
*/


    /* Multiplicate this triangular matrix and transpose source */
    /* for suitable use not transpose matrix srcMatr */

    dstBase = dstMatr;

    pti = srcTrans;

    for( i = 0; i < matrSize; i++ )
    {

        ptj = srcMatr;

        for( j = 0; j < height; j++ )
        {
            *dstBase++ = icvDotProduct_64d( pti, ptj, matrSize );
            ptj += width;
        }

        pti += matrSize;
    }

/*
    fprintf(file,"\nResult matrix (dstMatr)\n");
    for(i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            fprintf(file,"dstMatr[%d,%d] = %f\n",i,j,dstMatr[i * height + j]);
        }
        fprintf(file,"\n");
    }
*/

    icvFree( &tmpMatr );
    icvFree( &tmpMatr2 );
    icvFree( &srcTrans );

/*    fclose(file); */
    return CV_NO_ERR;
}
#else
IPCVAPI_IMPL( CvStatus, icvComplexMult_64d, (CvMatr64d srcMatr,
                                             CvMatr64d dstMatr, int width, int height) )
{
    CvMat src = cvMat( height, width, CV_64FC1, srcMatr );
    CvMat dst = cvMat( width, height, CV_64FC1, dstMatr );

    CvMat* at = cvCreateMat( width, height, CV_64FC1 );
    CvMat* ata = cvCreateMat( width, width, CV_64FC1 );
    CvMat* inv_ata = cvCreateMat( width, width, CV_64FC1 );

    cvMulTransposed( &src, ata, 1 );
    cvPseudoInv( ata, inv_ata/*, CV_SVD_MODIFY_A*/ );

#if 0
    {
        CvMat* t = cvCreateMat( width, width, CV_64FC1 );
        CvMat* eye = cvCreateMat( width, width, CV_64FC1 );
        cvSetIdentity( eye );
        cvMatMul( ata, inv_ata, t );
        double norm = cvNorm( eye, t, CV_L1 );
        cvReleaseMat( &t );
        cvReleaseMat( &eye );
    }
#endif

    cvT( &src, at );
    cvMatMul( inv_ata, at, &dst );

    cvReleaseMat( &at );
    cvReleaseMat( &ata );
    cvReleaseMat( &inv_ata );

    return CV_OK;
}
#endif

