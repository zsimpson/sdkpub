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


//this file dedicated to stereo correspondens problem

#include "_cvaux.h"
#include <assert.h>

#define LEFT 1
#define RIGHT 2

void icvDrawFilledSegments( CvSeq* seq, IplImage* img, int part )
{
    assert( img->nChannels == 3 );
    assert( img->depth == IPL_DEPTH_8U );
    assert( part == LEFT || part == RIGHT );

    //iterate through tree 
    CvSeq* current = seq;
    int number = 0;

    int level = 1;

    while( current )
    {
        number++; 
        assert( number < 256*16 );
        //number%=256;
        //draw current object with child level
        int color = (part == LEFT) ? number<<12 : number;

        CvSeq* tmp = current->h_next; //process only current contour and its children
        current->h_next = NULL;
        cvDrawContours( img, current, color, color, 2, CV_FILLED );
        current->h_next = tmp;

        if( current->v_next ) 
        {   
            //goto child
            current = current->v_next;
            level++;
        }
        else 
        {
            //go parent
            while( !current->h_next )
            {
                current = current->v_prev;
                level--;
                if( !level ) break;
            }
            
            if( current ) //go brother
                current = current->h_next;
        }
    }
}


#if 0
//function finds relations between all pairs of input contours 
//and builds graph of relations
CvGraph* cvRegionIntersection( CvSeq* first_seq, CvSeq* second_seq, IplImage* tmp_image, CvMemStorage* storage ) 
{
    //assumed that input contours are in form of tree

    CvSize img_size;
    img_size.width = tmp_image->width;
    img_size.height = tmp_image->height;
    
    //create future graph
    CvGraph* graph = cvCreateGraph( CV_SEQ_KIND_GRAPH|CV_GRAPH_FLAG_ORIENTED, 
                                    sizeof(CvGraph), sizeof(CvGraphVtx), 
                                    sizeof(CvGraphEdge), storage );

    IplImage* first_img = cvCreateImage( img_size, IPL_DEPTH_8U, 3 );
    IplImage* second_img = cvCreateImage( img_size, IPL_DEPTH_8U, 3 );
    IplImage* merge_img = cvCreateImage( img_size, IPL_DEPTH_8U, 3 );

    IplImage* image4 = cvCreateImage( img_size, IPL_DEPTH_8U, 4 );
    IplImage* image41 = cvCreateImage( img_size, IPL_DEPTH_8U, 4 );    
    IplImage* gray = cvCreateImage( img_size, IPL_DEPTH_8U, 4 );    

    iplSet( first_img, 0 );
    iplSet( second_img, 0 );
                            
    //draw first_seq segments
    icvDrawFilledSegments( first_seq, first_img, LEFT );
    icvDrawFilledSegments( second_seq, second_img, RIGHT );
    
    //create merged image
    iplOr(first_img, second_img, merge_img );
    
    //find all intersections
    iplSet( image4, 0 ); 
    
    IplROI roi;
    roi.xOffset = roi.yOffset = 0;
    roi.width = image4->width; 
    roi.height = image4->height;
    roi.coi = 0;

    merge_img->roi = &roi;
    image4->roi = &roi;

    roi.coi = 1;
    iplCopy( merge_img, image4 );
    roi.coi = 2;
    iplCopy( merge_img, image4 );
    roi.coi = 3;
    iplCopy( merge_img, image4 );

    merge_img->roi = 0;
    image4->roi = 0;


    image4->depth = image41->depth = /*image42->depth = */IPL_DEPTH_32S;
    image4->nChannels = image41->nChannels = /*image42->nChannels = */1;
    
    iplMaxFilter( image4, image41, 3,3,1,1 );
    iplSubtract( image41, image4, image41 );
    iplThreshold( image41, image41, 1 );
    iplConvert( image41, gray );
    iplNot( gray, gray );
    image4->depth = image41->depth = /*image42->depth = */IPL_DEPTH_8U;
    image4->nChannels = image41->nChannels = /*image42->nChannels = */4;

    //now gray image consists of white segments
    CvSeq* seq; 
    cvFindContours( gray, storage, &seq, sizeof(CvContour), CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );

    //create graph

    //1 








    
    



    return graph;
}    
#endif
#if 0
cvFindExtrinsicCameraParams2( int numPoints,
                              CvSize imageSize,
                              CvPoint2D64d* imagePoints,
                              CvPoint3D64d* objectPoints,
                              CvVect64d focalLength,
                              CvPoint2D64d principalPoint,
                              CvVect64d distortion,
                              CvVect64d rotVect,
                              CvVect64d transVect )
{
    /* Normalizate points  */
    CvPoint3D64d *resImagePoints;
    CvMatr64d matrY;
    CvMatr64d X_kk_trans;
    CvPoint2D64d *im2Pnt;
    CvPoint2D64d *ob2Pnt;
    CvMatr64d X_new;
    int t;
    double det;
    double r;
    double tmpf1, tmpf2;
    CvPoint2D64d *projectImagePoints;
    CvVect64d derivPointsRot;
    CvVect64d derivPointsTrans;
    CvVect64d derivPointsFocal;
    CvVect64d derivPointsPrincipal;
    CvVect64d derivPointsDistort;
    CvMatr64d matrJJ;
    CvMatr64d matrJJt;

    CvPoint2D64d *ex_points;
    int iter;
    double change;
    double norm1;
    double norm2;
    double sc;

    double matrYY[3 * 3];
    double matrU[3 * 3];
    double matrV[3 * 3];
    double matrS[3 * 3];
    double X_mean[3];
    double R_trans[3 * 3];
    double Homography[3 * 3];
    double rotMatr[3 * 3];
    double T_trans[3];
    double tmp3[3];
    double tmp3f1[3];
    double tmp3f2[3];
    double Jacobian[3 * 9];
    double omckk[3];
    double tmpRotMatr[3 * 3];
    double matrJJtJJ[6 * 6];
    double invmatrJJtJJ[6 * 6];
    double tmp6[6];
    double vectParam_innov[6];
    double vect_Param_up[6];
    double vect_Param[6];

    matrY = icvCreateMatrix_64d( numPoints, 3 );
    X_new = icvCreateMatrix_64d( numPoints, 3 );
    X_kk_trans = icvCreateMatrix_64d( numPoints, 3 );
    matrJJ = icvCreateMatrix_64d( 6, 2 * numPoints );
    matrJJt = icvCreateMatrix_64d( 2 * numPoints, 6 );
    derivPointsRot = icvCreateVector_64d( 3 * 2 * numPoints );
    derivPointsTrans = icvCreateVector_64d( 3 * 2 * numPoints );
    derivPointsFocal = icvCreateVector_64d( 2 * 2 * numPoints );
    derivPointsPrincipal = icvCreateVector_64d( 2 * 2 * numPoints );
    derivPointsDistort = icvCreateVector_64d( 4 * 2 * numPoints );
    im2Pnt = (CvPoint2D64d *) icvCreateVector_64d( numPoints * 2 );
    ob2Pnt = (CvPoint2D64d *) icvCreateVector_64d( numPoints * 2 );
    projectImagePoints = (CvPoint2D64d *) icvCreateVector_64d( numPoints * 2 );
    ex_points = (CvPoint2D64d *) icvCreateVector_64d( numPoints * 2 );
    resImagePoints = (CvPoint3D64d *) icvCreateVector_64d( numPoints * 3 );

    /*  compute trans matrix of points */
    icvTransposeMatrix_64d( (double *) objectPoints, 3, numPoints, X_kk_trans );



    icvNormalizeImagePoints( numPoints,
                             imagePoints,
                             focalLength, principalPoint, distortion, resImagePoints );


    ////////////////////////smoli/////////////////
    //          compute alpha
    CvPoint2D64d* alpha = (CvPoint2D64d*)icvAlloc( numPoints * sizeof(CvPoint2D64d) );
    CvPoint2D64d* beta  = (CvPoint2D64d*)icvAlloc( numPoints * sizeof(CvPoint2D64d) );

    double invF = 1/focalLength;

    for( int i = 0 ; i < numPoints; i++ )
    {
        alpha[i].x = imagePoints[i].x * invF;
        alpha[i].y = imagePoints[i].y * invF;
    }

    //we will use 2 first and 1 last point as basic points

    //compute 2 basic vectors (0->1) and (0->last )

    double V1[3];
    double V2[4];
    V1[0] = objectPoints[1].x













    
    /* check for planarity of the structure */
    /*  compute mean value */

    X_mean[0] = 0;
    X_mean[1] = 0;
    X_mean[2] = 0;

    for( t = 0; t < numPoints; t++ )
    {
        X_mean[0] += objectPoints[t].x;
        X_mean[1] += objectPoints[t].y;
        X_mean[2] += objectPoints[t].z;
    }

    X_mean[0] = X_mean[0] / numPoints;
    X_mean[1] = X_mean[1] / numPoints;
    X_mean[2] = X_mean[2] / numPoints;

    /*  fill matrix Y */
    for( t = 0; t < numPoints; t++ )
    {
        matrY[numPoints * 0 + t] = X_kk_trans[numPoints * 0 + t] - X_mean[0];
        matrY[numPoints * 1 + t] = X_kk_trans[numPoints * 1 + t] - X_mean[1];
        matrY[numPoints * 2 + t] = X_kk_trans[numPoints * 2 + t] - X_mean[2];
    }

    /* Compute matrix YY */

    icvMulTransMatrixL_64d( matrY, numPoints, 3, matrYY );

    /*  Compute SVD of YY only */

    icvCopyMatrix_64d( matrYY, 3, 3, matrU );

    icvSVDecomposition_64d( matrU, 3,  /* number of columns */
                             3, /* number of rows    */
                             matrS,     /*  size n x n */
                             matrV );   /*  size n x n */

    r = matrS[2 * 3 + 2] / matrS[1 * 3 + 1];

    if( r < 0.0001 )
    {                           /* Test for planarity */
        /* Transorm the plane to bring it in the Z=0 plane */

        icvTransposeMatrix_64d( matrV, 3, 3, R_trans );

        icvDetMatrix_64d( R_trans, 3, &det );

        if( det < 0 )
        {
            icvScaleMatrix_64d( R_trans, R_trans, 3, 3, -1 );

        }

        icvMulMatrix_64d( R_trans, 3, 3, X_mean, 1, 3, T_trans );
        icvScaleMatrix_64d( T_trans, T_trans, 1, 3, -1 );

        icvMulMatrix_64d( R_trans, 3, 3, X_kk_trans, numPoints, 3, X_new );

        for( t = 0; t < numPoints; t++ )
        {
            X_new[numPoints * 0 + t] += T_trans[0];
        }

        for( t = 0; t < numPoints; t++ )
        {
            X_new[numPoints * 1 + t] += T_trans[1];
        }

        for( t = 0; t < numPoints; t++ )
        {
            X_new[numPoints * 2 + t] += T_trans[2];
        }

        /* Compute the planar homography */
        for( t = 0; t < numPoints; t++ )
        {
            im2Pnt[t].x = resImagePoints[t].x;
            im2Pnt[t].y = resImagePoints[t].y;
            ob2Pnt[t].x = X_new[0 * numPoints + t];
            ob2Pnt[t].y = X_new[1 * numPoints + t];
        }

        icvFindHomography( numPoints, imageSize, im2Pnt, ob2Pnt, Homography );

        /* De-embed the motion parameters from the homography */
        for( t = 0; t < 3; t++ )
        {
            tmp3[t] = Homography[t * 3 + 0];
        }
        icvNormVector_64d( tmp3, 3, &tmpf1 );

        for( t = 0; t < 3; t++ )
        {
            tmp3[t] = Homography[t * 3 + 1];
        }
        icvNormVector_64d( tmp3, 3, &tmpf2 );

        sc = (tmpf1 + tmpf2) * 0.5f;

        icvScaleVector_64d( Homography, Homography, 9, 1.0f / sc );

        /* fill rotate matrix */
        icvCopyVector_64d( Homography, 9, rotMatr );

        tmp3f1[0] = Homography[0];
        tmp3f1[1] = Homography[3];
        tmp3f1[2] = Homography[6];

        tmp3f2[0] = Homography[1];
        tmp3f2[1] = Homography[4];
        tmp3f2[2] = Homography[7];

        icvCrossProduct2L_64d( tmp3f1, tmp3f2, tmp3 );

        rotMatr[0] = Homography[0];
        rotMatr[3] = Homography[3];
        rotMatr[6] = Homography[6];

        rotMatr[1] = Homography[1];
        rotMatr[4] = Homography[4];
        rotMatr[7] = Homography[7];

        rotMatr[2] = tmp3[0];
        rotMatr[5] = tmp3[1];
        rotMatr[8] = tmp3[2];

        icvRodrigues_64d( rotMatr, omckk, Jacobian, CV_RODRIGUES_M2V );

        icvRodrigues_64d( rotMatr, omckk, Jacobian, CV_RODRIGUES_V2M );

        transVect[0] = Homography[2];
        transVect[1] = Homography[5];
        transVect[2] = Homography[8];

        icvMulMatrix_64d( rotMatr, 3, 3, T_trans, 1, 3, tmp3 );

        icvAddVector_64d( transVect, tmp3, transVect, 3 );

        /* Compute rotation matrix */
        icvMulMatrix_64d( rotMatr, 3, 3, R_trans, 3, 3, tmpRotMatr );

        icvRodrigues_64d( tmpRotMatr, rotVect, Jacobian, CV_RODRIGUES_M2V );
    }

    /* Final optimazation (minimize the reprojection error in pixel) */
    /* through Gradient Descent */

    iter = 0;
    change = 1.0f;

    icvCopyVector_64d( rotVect, 3, vect_Param );
    icvCopyVector_64d( transVect, 3, vect_Param + 3 );

    while( (change > 0.0000001f) && (iter < 100) )
    {
        iter++;

        icvProjectPoints( numPoints, objectPoints, rotVect, transVect,
                          focalLength, principalPoint, distortion,
                          projectImagePoints,
                          derivPointsRot,       /* need     */
                          derivPointsTrans,     /* need     */
                          derivPointsFocal,     /* not need */
                          derivPointsPrincipal, /* not need */
                          derivPointsDistort ); /* not need */
        /* compute ex points */

        icvSubVector_64d( (double *) imagePoints, (double *) projectImagePoints,
                           (double *) ex_points, numPoints * 2 );
        /* create vector matrJJ */

        for( t = 0; t < numPoints * 2; t++ )
        {
            icvCopyVector_64d( derivPointsRot + t * 3, 3, matrJJ + t * 6 );
            icvCopyVector_64d( derivPointsTrans + t * 3, 3, matrJJ + t * 6 + 3 );
        }

        icvMulTransMatrixR_64d( matrJJ, 6, 2 * numPoints, matrJJtJJ );
        icvInvertMatrix_64d( matrJJtJJ, 6, invmatrJJtJJ );

        icvTransposeMatrix_64d( matrJJ, 6, 2 * numPoints, matrJJt );

        icvMulMatrix_64d( matrJJt, 2 * numPoints, 6,
                          (double *) ex_points, 1, 2 * numPoints,
                           tmp6 );
        icvMulMatrix_64d( invmatrJJtJJ, 6, 6, tmp6, 1, 6, vectParam_innov );

        icvAddVector_64d( vect_Param, vectParam_innov, vect_Param_up, 6 );
        icvNormVector_64d( vectParam_innov, 6, &norm1 );
        icvNormVector_64d( vect_Param_up, 6, &norm2 );

        change = norm1 / norm2;

        icvCopyVector_64d( vect_Param_up, 6, vect_Param );

        iter++;

        icvCopyVector_64d( vect_Param, 3, rotVect );
        icvCopyVector_64d( vect_Param + 3, 3, transVect );

    }

    /* Free allocated memory */
    icvDeleteMatrix( matrY );
    icvDeleteMatrix( X_new );
    icvDeleteMatrix( X_kk_trans );
    icvDeleteMatrix( matrJJ );
    icvDeleteMatrix( matrJJt );
    icvDeleteVector( derivPointsRot );
    icvDeleteVector( derivPointsTrans );
    icvDeleteVector( derivPointsFocal );
    icvDeleteVector( derivPointsPrincipal );
    icvDeleteVector( derivPointsDistort );
    icvDeleteVector( im2Pnt );
    icvDeleteVector( ob2Pnt );
    icvDeleteVector( projectImagePoints );
    icvDeleteVector( ex_points );
    icvDeleteVector( resImagePoints );

    return CV_NO_ERR;
}
#endif

