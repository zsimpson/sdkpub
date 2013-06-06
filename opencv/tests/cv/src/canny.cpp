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

int follow(int i, int j, float low, CvSize roi, uchar* dst, int dstStep, float* mag)
{
    int pixel_counter = 1;
    int k,l;        /* counters */
    int i_plus_1,i_minus_1,j_plus_1,j_minus_1;
    long index,kindex;
    char break_flag;

    i_plus_1= i + 1;
    i_minus_1= i - 1;
    j_plus_1=j+1;
    j_minus_1=j-1;
    index = i * dstStep + j;
    if (j_plus_1>=roi.width) j_plus_1=roi.width-1;
    if (j_minus_1<0) j_minus_1=0;
    if (i_plus_1>=roi.height) i_plus_1=roi.height-1;
    if (i_minus_1<0) i_minus_1=0;

    if (!dst[index])
    {
        /* current point must be added to the list of tracked points */
        dst[index]=255;
        /* now we can check immediately adjacent points to see if
           they too could be added to the track */
        break_flag=0;
        for (k=i_minus_1;k<=i_plus_1;k++)
        {
            for(l=j_minus_1;l<=j_plus_1;l++)
            {
                kindex = k * roi.width + l;
                if (!(l==j && k==i) && (mag[kindex]>low ))
                {
                    pixel_counter+=follow(k,l,low, roi, dst, dstStep, mag);
                }
            }
        }
        return(pixel_counter);
    }
    else return(0);
}
/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    atsCannyStatistics
//    Purpose:
//      perform canny edge detection with statistic
//    Context:
//    Parameters:
//      zero_mag - number of elements with zero magnitude
//      under_low - number of elements under low threshold
//      above_high - number of elements above high threshold
//      edges_in_nms - above low threshold and has local maxima
//      in_edges - in detected edges
//      components - number of 8-connected components on edge image
//    Returns:
//      Number of nonequal elements
//    Notes:
//F*/
int atsCannyStatistics(uchar* src,
                             CvSize roi,
                             int srcStep,
                             uchar* dst,
                             int dstStep,
                             int Sobord,
                             float lowThreshold,
                             float highThreshold,
                             int* zero_mag,
                             int* under_low,
                             int* above_high,
                             int* edges_in_nms,
                             int* components,
                             int* in_edges)
{
    float pi = 3.1415926535f;
    int i,j;

    IplImage* _dX = cvCreateImage( roi, IPL_DEPTH_16S, 1 );
    IplImage* _dY = cvCreateImage( roi, IPL_DEPTH_16S, 1 );
    short* dX = (short*)(_dX->imageData);
    short* dY = (short*)(_dY->imageData);
	int stepx = _dX->widthStep/2;
	int stepy = _dY->widthStep/2;
    IplImage* img = cvCreateImageHeader( roi, IPL_DEPTH_8U, 1 );

    float* mag = (float*)icvAlloc(roi.width * roi.height * 4);
    float* nms = (float*)icvAlloc(roi.width * roi.height * 4);

    memset(dst, 0, roi.height*dstStep);

    if(zero_mag) (*zero_mag)=0;
    if(under_low) (*under_low)=0;
    if(above_high) (*above_high)=0;
    if(edges_in_nms) (*edges_in_nms)=0;
    if(components) (*components)=0;
    if(in_edges) (*in_edges)=0;

    cvSetImageData( img, src, srcStep );

    memset( _dX->imageData, 0, _dX->imageSize );
    memset( _dY->imageData, 0, _dY->imageSize );

    /* smooth and difference */
    cvSobel( img, _dX, 1, 0, Sobord );
    cvSobel( img, _dY, 0, 1, Sobord );

    /* estimate magnitude and angle */
    for ( i = 0; i < roi.height; i++ )
    {
        for ( j = 0; j < roi.width; j++ )
        {
            mag[i*roi.width+j] = (float)(abs(dX[i*stepx+j])+abs(dY[i*stepy+j]));

            if ( (!mag[i*roi.width+j]) && zero_mag)
                (*zero_mag)++;
            if ( (mag[i*roi.width+j] <= lowThreshold) && under_low)
                (*under_low)++;
            if ( mag[i*roi.width+j] > highThreshold && above_high) (*above_high)++;

        }
    }
    /* nonmaxima suppression */
    for ( i = 0; i < roi.height; i++ )
    {
        for ( j = 0; j < roi.width; j++ )
        {
            int i1=0,i2=0,j1=0,j2=0;
            float tg = (float)dY[i*roi.width+j]/(float)dX[i*roi.width+j];
            float max = 0;

            if ( (tg < tan( pi/8 )) && (tg > tan( -pi/8 ) ))
            {
                i1 = i2 = i; j1 = j + 1; j2 = j - 1;
            }
            if ( (tg <= tan( pi/4+pi/8 )) && (tg >= tan( pi/8 )))
            {
                i1 = i + 1; i2 = i - 1; j1 = j + 1; j2 = j - 1;
            }
            if ((tg <= tan( -pi/8 )) && (tg >= tan( -pi/4-pi/8 )))
            {
                i1 = i - 1; i2 = i + 1; j1 = j + 1; j2 = j - 1;
            }
            if ((tg > tan( pi/2 - pi/8 )) || (tg < tan( -pi/4-pi/8 ))
                || (dX[i*roi.width+j]==0) )
            {
                j1 = j2 = j; i1 = i + 1; i2 = i - 1;
            }

            if ( i1>=0 && i1 < roi.height && j1>=0 && j1 < roi.width )
            {
                max = MAX( mag[i*roi.width+j], mag[i1*roi.width+j1] );
            }
            if ( i2>=0 && i2 < roi.height && j2>=0 && j2 < roi.width )
            {
                max = MAX( max, mag[i2*roi.width+j2] );
            }

            if ( mag[i * roi.width + j] >= max )
            {
                nms[i * roi.width + j] = mag[i * roi.width + j];
                if (nms[i * roi.width + j]>lowThreshold && edges_in_nms)
                {
                    (*edges_in_nms)++;
                }
            }
            else
                nms[i * roi.width + j] = 0;

        }
    }

    /* hysteresis threshold */
    for ( i = 0; i < roi.height; i++ )
    {
        for ( j = 0; j < roi.width; j++ )
        {
            if ((nms[i*roi.width+j] > highThreshold) && ( !dst[i*dstStep+j] ))
            {
                int a = follow( i,j, lowThreshold, roi, dst, dstStep, nms);
                if (components) (*components)++;
                if (in_edges) (*in_edges)+=a;

            }
        }
    }
    cvReleaseImage(&_dX);
    cvReleaseImage(&_dY);
    cvReleaseImageHeader(&img);
    icvFree(&nms);
    icvFree(&mag);

    return (int)CV_OK;
}


