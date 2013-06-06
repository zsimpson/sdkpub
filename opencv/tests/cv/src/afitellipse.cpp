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

#include <assert.h>
//#include <conio.h>


static char* func_names[] = {"cvFitEllipse"};
static char* test_desc[] = { "Algorithm test for cvFitEllipse"};

int test_dt(void* arg);
int read_image_dims(void);
int read_gen_type(void);

//sort of regression test
//it depends on drawing functions
//so if it becomes to crash - check also drawing

int fmaFitEllipse(void)
{
    long lErrors = 0; 
    CvPoint points[1000];
    CvPoint2D32f fpoints[1000];
    CvBox2D box;
    
    CvMemStorage* storage = cvCreateMemStorage(0);
    CvContour* contour;
    CvSize axis;
    IplImage* img = cvCreateImage( cvSize(200,200), IPL_DEPTH_8U, 1 );
    
    for( int k = 0 ; k < 1000; k++ )
    {
    
        iplSet( img, 0 );

        CvPoint center = { 100, 100 };
    
        double angle = atsInitRandom( 0, 360 );
        axis.height = (int)atsInitRandom( 5, 50 );
        axis.width  = (int)atsInitRandom( 5, 50 );   

        cvEllipse( img, center, axis, angle, 0, 360, 255, -1 );
    
        cvFindContours( img, storage, (CvSeq**)&contour, sizeof(CvContour) );

        cvCvtSeqToArray( (CvSeq*)contour, points );
        for( int i = 0; i < contour->total; i++ )
        {
            fpoints[i].x = (float)points[i].x;
            fpoints[i].y = (float)points[i].y;
        }
    
        cvFitEllipse( fpoints, contour->total, &box );

        //compare boxes
        if( fabs( box.center.x - center.x) > 1 || fabs( box.center.y - center.y ) > 1 )
        {
            lErrors++;
        }             

        if( ( fabs( box.size.width  - (axis.width * 2 ) ) > 4 || 
              fabs( box.size.height - (axis.height * 2) ) > 4 ) &&
            ( fabs( box.size.height - (axis.width * 2 ) ) > 4 || 
              fabs( box.size.width - (axis.height * 2) ) > 4 ) )           
        {
            lErrors++;

            //graphic
            /*IplImage* rgb = cvCreateImage( cvSize(200,200), IPL_DEPTH_8U, 3 );
            iplSet( rgb, 0 );
                        
            cvEllipse( rgb, center, axis, angle, 0, 360, CV_RGB(255,0,0) , 1 );
            
            int window = atsCreateWindow( "proba", cvPoint(0,0), cvSize(200,200) );
            cvEllipse( rgb, center, cvSize( box.size.width/2, box.size.height/2) , -box.angle, 
                        0, 360, CV_RGB(0,255,0) , 1 );

            //draw center 
            cvEllipse( rgb, center, cvSize( 0, 0) , 0, 
                        0, 360, CV_RGB(255,255,255) , -1 );
            
            atsDisplayImage( rgb, window, cvPoint(0,0), cvSize(200,200) );
            
            getch();

            atsDestroyWindow( window );
            
            //one more
            cvFitEllipse( fpoints, contour->total, &box );
          */
        }
    }
    cvReleaseMemStorage( &storage );
    
    if( !lErrors) return trsResult(TRS_OK, "No errors");
    else
        return trsResult(TRS_FAIL, "Fixed %d errors", lErrors);
    
}

void InitAFitEllipse(void)
{
    /* Registering test functions */
    trsReg(func_names[0], test_desc[0], atsAlgoClass, fmaFitEllipse);
} /* InitAFitLine*/

