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
#include "_cvdatastructs.h"


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name: icvContourArea
//    Purpose:
//      Calculates area within the contour
//    Context:
//    Parameters:
//      contour - pointer to input contour object.
//      area    - pointer to the calculating area 
//
//F*/
static  CvStatus  icvContourArea( CvSeq *contour, double *area )
{
    CvPoint pt;                 /*  pointer to points  */
    CvSeqReader reader;         /*  points reader of contour */

    int lpt, flag;
    double a00;                 /* unnormalized moments  */
    double xi, yi, xi_1, yi_1, x0, y0, dxy;

    assert( contour );

    if( contour == NULL )
        return CV_NULLPTR_ERR;

    if( !CV_IS_SEQ_POLYGON( contour ))
        return CV_BADFLAG_ERR;

    if( contour->total )
    {
        lpt = contour->total;
        a00 = x0 = y0 = xi_1 = yi_1 = 0;
        flag = 0;

        cvStartReadSeq( contour, &reader, 0 );

        while( lpt-- > 0 )
        {
            CV_READ_SEQ_ELEM( pt, reader );
            if( flag == 0 )
            {
                xi_1 = (double) pt.x;
                yi_1 = (double) pt.y;
                x0 = xi_1;
                y0 = yi_1;
                flag = 1;
            }
            else
            {
                xi = (double) pt.x;
                yi = (double) pt.y;
                dxy = xi_1 * yi - xi * yi_1;
                a00 += dxy;

                xi_1 = xi;
                yi_1 = yi;
            }
        }

        xi = x0;
        yi = y0;
        dxy = xi_1 * yi - xi * yi_1;

        a00 += dxy;

        *area = a00 / 2.;

        return CV_OK;
    }
    else
        return CV_BADSIZE_ERR;
}


/****************************************************************************************\

 copy data from one buffer to other buffer 

\****************************************************************************************/

static CvStatus
icvMemCopy( double **buf1, double **buf2, double **buf3, int *b_max )
{
    int bb;

    if( *buf1 == NULL && *buf2 == NULL || *buf3 == NULL )
        return CV_NULLPTR_ERR;

    bb = *b_max;
    if( *buf2 == NULL )
    {
        *b_max = 2 * (*b_max);
        *buf2 = (double *) icvAlloc( (*b_max) * sizeof( double ));

        if( *buf2 == NULL )
            return CV_OUTOFMEM_ERR;

        memcpy( *buf2, *buf3, bb * sizeof( double ));

        *buf3 = *buf2;
        icvFree( &(*buf1) );
        *buf1 = NULL;
    }
    else
    {
        *b_max = 2 * (*b_max);
        *buf1 = (double *) icvAlloc( (*b_max) * sizeof( double ));

        if( *buf1 == NULL )
            return CV_OUTOFMEM_ERR;

        memcpy( *buf1, *buf3, bb * sizeof( double ));

        *buf3 = *buf1;
        icvFree( &(*buf2) );
        *buf2 = NULL;
    }
    return CV_OK;
}


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name: icvContourSecArea
//    Purpose:
//      Calculates area of the section within the contour from one point to other
//    Context:
//    Parameters:
//      contour - pointer to input contour object.
//      n1, n2 - numbers of the first and last contour's points 
//      area    - pointer to the calculating area 
//
//F*/
static CvStatus icvContourSecArea( CvSeq * contour, CvSlice slice, double *area )
{
    CvPoint pt;                 /*  pointer to points   */
    CvPoint pt_s, pt_e;         /*  first and last points  */
    CvSeqReader reader;         /*  points reader of contour   */

    int p_max = 2, p_ind;
    int lpt, flag, i;
    double a00;                 /* unnormalized moments m00    */
    double xi, yi, xi_1, yi_1, x0, y0, dxy, sk, sk1, t;
    double x_s, y_s, nx, ny, dx, dy, du, dv;
    double eps = 1.e-5;
    double *p_are1, *p_are2, *p_are;

    assert( contour != NULL );

    if( contour == NULL )
        return CV_NULLPTR_ERR;

    if( !CV_IS_SEQ_POLYGON( contour ))
        return CV_BADFLAG_ERR;

    lpt = icvSliceLength( slice, contour );
    /*if( n2 >= n1 )
        lpt = n2 - n1 + 1;
    else
        lpt = contour->total - n1 + n2 + 1;*/

    if( contour->total && lpt > 2 )
    {
        a00 = x0 = y0 = xi_1 = yi_1 = 0;
        sk1 = 0;
        flag = 0;
        dxy = 0;
        p_are1 = (double *) icvAlloc( p_max * sizeof( double ));

        if( p_are1 == NULL )
            return CV_OUTOFMEM_ERR;

        p_are = p_are1;
        p_are2 = NULL;

        cvStartReadSeq( contour, &reader, 0 );
        cvSetSeqReaderPos( &reader, slice.startIndex );
        CV_READ_SEQ_ELEM( pt_s, reader );
        p_ind = 0;
        cvSetSeqReaderPos( &reader, slice.endIndex );
        CV_READ_SEQ_ELEM( pt_e, reader );

/*    normal coefficients    */
        nx = pt_s.y - pt_e.y;
        ny = pt_e.x - pt_s.x;
        cvSetSeqReaderPos( &reader, slice.startIndex );

        while( lpt-- > 0 )
        {
            CV_READ_SEQ_ELEM( pt, reader );

            if( flag == 0 )
            {
                xi_1 = (double) pt.x;
                yi_1 = (double) pt.y;
                x0 = xi_1;
                y0 = yi_1;
                sk1 = 0;
                flag = 1;
            }
            else
            {
                xi = (double) pt.x;
                yi = (double) pt.y;

/****************   edges intersaction examination   **************************/
                sk = nx * (xi - pt_s.x) + ny * (yi - pt_s.y);
                if( fabs( sk ) < eps && lpt > 0 || sk * sk1 < -eps )
                {
                    if( fabs( sk ) < eps )
                    {
                        dxy = xi_1 * yi - xi * yi_1;
                        a00 = a00 + dxy;
                        dxy = xi * y0 - x0 * yi;
                        a00 = a00 + dxy;

                        if( p_ind >= p_max )
                            icvMemCopy( &p_are1, &p_are2, &p_are, &p_max );

                        p_are[p_ind] = a00 / 2.;
                        p_ind++;
                        a00 = 0;
                        sk1 = 0;
                        x0 = xi;
                        y0 = yi;
                        dxy = 0;
                    }
                    else
                    {
/*  define intersection point    */
                        dv = yi - yi_1;
                        du = xi - xi_1;
                        dx = ny;
                        dy = -nx;
                        if( fabs( du ) > eps )
                            t = ((yi_1 - pt_s.y) * du + dv * (pt_s.x - xi_1)) /
                                (du * dy - dx * dv);
                        else
                            t = (xi_1 - pt_s.x) / dx;
                        if( t > eps && t < 1 - eps )
                        {
                            x_s = pt_s.x + t * dx;
                            y_s = pt_s.y + t * dy;
                            dxy = xi_1 * y_s - x_s * yi_1;
                            a00 += dxy;
                            dxy = x_s * y0 - x0 * y_s;
                            a00 += dxy;
                            if( p_ind >= p_max )
                                icvMemCopy( &p_are1, &p_are2, &p_are, &p_max );

                            p_are[p_ind] = a00 / 2.;
                            p_ind++;

                            a00 = 0;
                            sk1 = 0;
                            x0 = x_s;
                            y0 = y_s;
                            dxy = x_s * yi - xi * y_s;
                        }
                    }
                }
                else
                    dxy = xi_1 * yi - xi * yi_1;

                a00 += dxy;
                xi_1 = xi;
                yi_1 = yi;
                sk1 = sk;

            }
        }

        xi = x0;
        yi = y0;
        dxy = xi_1 * yi - xi * yi_1;

        a00 += dxy;

        if( p_ind >= p_max )
            icvMemCopy( &p_are1, &p_are2, &p_are, &p_max );

        p_are[p_ind] = a00 / 2.;
        p_ind++;

/*     common area calculation    */
        *area = 0;
        for( i = 0; i < p_ind; i++ )
            (*area) += fabs( p_are[i] );

        if( p_are1 != NULL )
            icvFree( &p_are1 );
        else if( p_are2 != NULL )
            icvFree( &p_are2 );

        return CV_OK;
    }
    else
        return CV_BADSIZE_ERR;
}


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name: cvContourArea
//    Purpose:
//      Calculates area within the contour
//    Context:
//    Parameters:
//      contour - pointer to input contour object.
//      area    - pointer to the calculating area 
//
//F*/
CV_IMPL double
cvContourArea( CvSeq *contour, CvSlice slice )
{
    int length;
    double area = 0;
    
    CV_FUNCNAME( "cvContourArea" );
    __BEGIN__;

    if( !contour )
        CV_ERROR_FROM_STATUS( CV_NULLPTR_ERR );

    length = icvSliceLength( slice, contour );

    if( length == contour->total )
    {
        IPPI_CALL( icvContourArea( contour, &area ));
    }
    else
    {
        IPPI_CALL( icvContourSecArea( contour, slice, &area ));
    }

    __CLEANUP__;
    __END__;

    return area;
}


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    cvContourBoundingRect
//    Purpose:
//      Update bounding box for the given contour 
//    Context:
//    Parameters:
//      contour          - pointer to the source contour
//      update           - attribute of contour bounding box updating
//                         (if update = 0 the bounding box isn't updated
//
//    Returns:
//F*/  
CV_IMPL  CvRect  cvContourBoundingRect( CvSeq* contour, int update )
{
    CvPoint pt;                 /*  pointer to points  */
    CvSeqReader reader;         /*  points reader of contour  */
    CvRect  rect = { 0, 0, 0, 0 };

    int  xmin, ymin, xmax, ymax, lpt;

    CV_FUNCNAME("cvUpdateContourRect");

    __BEGIN__

    if( !contour )
        CV_ERROR_FROM_STATUS( CV_NULLPTR_ERR );

    if( !CV_IS_SEQ_POINT_SET( contour ))
        CV_ERROR_FROM_STATUS( CV_BADFLAG_ERR );

    if( contour->header_size < (int)sizeof( CvContour ) )
        CV_ERROR_FROM_STATUS( CV_BADSIZE_ERR );

    if( update )
    {
        if( contour->total )
        {   
            cvStartReadSeq( contour, &reader, 0 );

            /* init values */
            CV_READ_SEQ_ELEM( pt, reader );
            xmin = xmax = pt.x;
            ymin = ymax = pt.y;
    
            for( lpt = 1; lpt < contour->total; lpt++ )
            {            
                CV_READ_SEQ_ELEM( pt, reader );
            
                if( xmin > pt.x )
                    xmin = pt.x;
            
                if( xmax < pt.x )
                    xmax = pt.x;

                if( ymin > pt.y )
                    ymin = pt.y;

                if( ymax < pt.y )
                    ymax = pt.y;
            }

            rect.x = xmin;
            rect.y = ymin;
            rect.width = xmax - xmin + 1;
            rect.height = ymax - ymin + 1;
        }

        ((CvContour*)contour)->rect = rect;
    }
    else
    {
        rect = ((CvContour*)contour)->rect;
    }

    __CLEANUP__
    __END__

    return rect;
}

/* End of file. */
