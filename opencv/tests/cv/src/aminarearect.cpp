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
#include "float.h"

CvSeq* atsCvtHullToContour( CvSeq* hull, CvMemStorage* storage )
{
    CvSeqWriter writer;
    CvSeqReader hull_reader;
    cvStartWriteSeq( CV_SEQ_POLYGON, sizeof(CvSeq), sizeof(CvPoint), storage, &writer );
    cvStartReadSeq( hull, &hull_reader, 0 );

    CvPoint* hull_elem;
    int i = 0;
    for( i = 0; i < hull->total; i++ )
    {           
        CV_READ_SEQ_ELEM( hull_elem, hull_reader );
        CV_WRITE_SEQ_ELEM( hull_elem[0], writer )        
    }

    return cvEndWriteSeq( &writer );
}

int atsCheckMinAreaRect( CvPoint* points, int n, CvPoint2D32f anchor, 
                     CvPoint2D32f vect1, CvPoint2D32f vect2 )
{
    float acc = 1.f;
    CvPoint2D32f Anchor = cvPoint2D32f(0,0);
    CvPoint2D32f Vect1 = cvPoint2D32f(0,0);
    CvPoint2D32f Vect2 = cvPoint2D32f(0,0);
    float minarea = FLT_MAX;

    //consequently get 2 points
    for( int i = 0; i < n; i++ )
    {
        CvPoint p1 = points[i];
        CvPoint p2 = points[(i+1)%n];

        CvPoint2D32f main_vect;
        main_vect.x = (float)(p2.x - p1.x);
        main_vect.y = (float)(p2.y - p1.y);

        //project all points to this vector
        int right = -1, left = -1, top = -1;
        float right_val = -FLT_MAX, left_val = FLT_MAX, top_val = -FLT_MAX;
               
        for( int j = 0; j < n; j++ )
        {
            CvPoint2D32f tmp_vect;
            tmp_vect.x = (float)(points[j].x - p1.x);
            tmp_vect.y = (float)(points[j].y - p1.y);

            //compute dot product and find min & max
            float prod = main_vect.x*tmp_vect.x + main_vect.y * tmp_vect.y;
            if( prod > right_val )
            {
                right_val = prod;
                right = j;
            }
            if( prod < left_val )
            {
                left_val = prod;
                left = j;
            }

            //compute perpendicular
            prod = -main_vect.y * tmp_vect.x + main_vect.x * tmp_vect.y;
            if( prod > top_val )
            {
                top_val = prod;
                top = j;
            }
        }

        /*compute area  */

        //1. find main vector norm
        float norm = (float)sqrt( main_vect.x*main_vect.x + main_vect.y * main_vect.y );
        
        main_vect.x /= norm;
        main_vect.y /= norm;

        CvPoint2D32f co;
        co.x = (float)(points[right].x - points[left].x);
        co.y = (float)(points[right].y - points[left].y);

        float width = main_vect.x* co.x + main_vect.y * co.y;

        CvPoint2D32f per;
        per.x = (float)(points[top].x - p1.x);
        per.y = (float)(points[top].y - p1.y);

        float height = -main_vect.y* per.x + main_vect.x * per.y;

        float area = height * width;

        if( area < minarea )
        {
            minarea  = area;
            CvPoint2D32f ico;
            ico.x = (float)(points[left].x - p1.x);
            ico.y = (float)(points[left].y - p1.y);


            //fill output
            float ret = main_vect.x* ico.x + main_vect.y * ico.y;

            //compute anchor
            Anchor.x = p1.x + main_vect.x * ret;
            Anchor.y = p1.y + main_vect.y * ret;

            //compute output vecs
            Vect1.x = main_vect.x * width;
            Vect1.y = main_vect.y * width;

            Vect2.x = -main_vect.y * height;
            Vect2.y = main_vect.x * height;
        } 
    }

    //compare computed & input
    
    //calc all vertices
    CvPoint2D32f v[4];
    CvPoint2D32f V[4];

    v[0] = anchor;
    v[1] = cvPoint2D32f( anchor.x + vect1.x, anchor.y + vect1.y );
    v[2] = cvPoint2D32f( v[1].x + vect2.x, v[1].y + vect2.y );
    v[3] = cvPoint2D32f( anchor.x + vect2.x, anchor.y + vect2.y );

    V[0] = Anchor;
    V[1] = cvPoint2D32f( Anchor.x + Vect1.x, Anchor.y + Vect1.y );
    V[2] = cvPoint2D32f( V[1].x + Vect2.x, V[1].y + Vect2.y );
    V[3] = cvPoint2D32f( Anchor.x + Vect2.x, Anchor.y + Vect2.y );


    //return (atsCompSinglePrec( &(anchor.x), &(Anchor.x), 2, acc ) +
    //       atsCompSinglePrec( &(vect1.x), &(Vect1.x), 2, acc ) +
    //       atsCompSinglePrec( &(vect2.x), &(Vect2.x), 2, acc ));
        
    //compare vertices
    int err = 1;
    for( int j = 0; j < 4; j++ )
    {
        int e  = atsCompSinglePrec( &(v[0].x), &(V[j].x), 2, acc );
            e += atsCompSinglePrec( &(v[1].x), &(V[(j+1)%4].x), 2, acc );
            e += atsCompSinglePrec( &(v[2].x), &(V[(j+2)%4].x), 2, acc );
            e += atsCompSinglePrec( &(v[3].x), &(V[(j+3)%4].x), 2, acc );

        if( !e ) 
        {
            err = 0;
            break;
        }
    }

    return err;
}

/* Testing parameters */
static char test_desc[] = "MinAreaRect";
static char TestClass[] = "Algorithm";
static char* func_name = "cvMinAreaRect";

static int lScreenSize;
static long lLoopsProp;
static long lNumPoints;   

static int fmaMinAreaRect(void)
{ 
    long lErrors = 0;     
    
    static int  read_param = 0;
    int j;
    
    CvPoint* points;
    CvContour* contour;
    CvSeq* hull = NULL;
    CvMemStorage* storage;

    if(!read_param)
    {
        read_param=1;
        
        /* Reading test-parameters */
        trslRead( &lNumPoints, "50", "number of points" ); 
        trslRead( &lLoopsProp, "50", "Loops" ); 
    }

    storage = cvCreateMemStorage(0);
    points = (CvPoint*)icvAlloc( lNumPoints * sizeof(CvPoint) );
    
    for( j = 0; j < lLoopsProp; j++ )
    {
        int numpts;
        ats1iInitRandom( 5, 1024, &lScreenSize, 1 );
        ats1iInitRandom( 5, lNumPoints, &numpts, 1 );
        ats1iInitRandom( 0, lScreenSize, (int*)points, 2*numpts ) ;
       /* numpts = 7;
        points[0] = cvPoint( 4, 33);
        points[1] = cvPoint( 5, 34);
        points[2] = cvPoint( 34, 33);
        points[3] = cvPoint( 34, 2);
        points[4] = cvPoint( 14, 0);
        points[5] = cvPoint( 8, 8);
        points[6] = cvPoint( 5, 22);
       */ 
        contour = (CvContour*)cvCreateSeq( CV_SEQ_SIMPLE_POLYGON, sizeof(CvContour),
                               sizeof(CvPoint), storage);  
 
        cvSeqPushMulti( (CvSeq*)contour, points, numpts );
        hull = cvContourConvexHull( (CvSeq*)contour, CV_COUNTER_CLOCKWISE, storage );   
        
        if( hull->total < 3 ) continue;
        //convert hull
        CvContour* contour2 = (CvContour*)atsCvtHullToContour( hull, storage );
        /* check errors */
        
        cvCvtSeqToArray( (CvSeq*)contour2, points ); 
        CvPoint2D32f anchor;
        CvPoint2D32f vect1, vect2;
        cvMinAreaRect( points, contour2->total, -1, -1, -1, -1, &anchor, &vect1, &vect2 );
        
        lErrors += atsCheckMinAreaRect( points , contour2->total, anchor, vect1, vect2 );
               
        cvClearMemStorage( storage );
    } /* for */

    icvFree(&points);
    cvReleaseMemStorage(&storage);
    
   if( lErrors == 0 ) return trsResult( TRS_OK, "No errors fixed for this test" );
   else return trsResult( TRS_FAIL, "Total fixed %d errors", lErrors );

}        

void InitAMinAreaRect(void)
{
    /* Register test function */    
    trsReg( func_name, test_desc, atsAlgoClass, fmaMinAreaRect );
    
} /* InitAMinAreaRect */


