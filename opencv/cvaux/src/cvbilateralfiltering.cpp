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

#include "_cvaux.h"
#include <math.h>
#include "_cvutils.h"
#include "_cvwrap.h"

inline double weight(double x)
{
    return 1/(x*x + 1);
};

void icvBilateralFiltering8uC1(IplImage* in, IplImage* out, int thresh_space, int thresh_color);
void icvBilateralFiltering8uC3(IplImage* in, IplImage* out, int thresh_space, int thresh_color);
void icvBilateralFiltering16sC1(IplImage* in, IplImage* out, int thresh_space, int thresh_color);

CV_IMPL void icvBilateralFiltering(IplImage* in, IplImage* out, int thresh_space, int thresh_color)
{
    switch(in->depth)
    {
    case IPL_DEPTH_8U:
        switch(in->nChannels)
        {
            case 1:
                icvBilateralFiltering8uC1(in, out, thresh_space, thresh_color);
                break;

            case 3:
                icvBilateralFiltering8uC3(in, out, thresh_space, thresh_color);
                break;
        }
        break;

    case IPL_DEPTH_16S:
        icvBilateralFiltering16sC1(in, out, thresh_space, thresh_color);
        break;

    default:
        assert(0);
        return;
    }
}

#define CV_INIT_3X3_DELTAS( deltas, step, nch )             \
    ((deltas)[0] =  (nch),  (deltas)[1] = -(step) + (nch),  \
     (deltas)[2] = -(step), (deltas)[3] = -(step) - (nch),  \
     (deltas)[4] = -(nch),  (deltas)[5] =  (step) - (nch),  \
     (deltas)[6] =  (step), (deltas)[7] =  (step) + (nch))

void icvBilateralFiltering8uC1(IplImage* in, IplImage* out, int thresh_space, int thresh_color)
{
    uchar* idata;
    uchar* odata;
    uchar* _idata;
    uchar* _odata;
    int step;
    CvSize size;

    double sigma_color = thresh_color; 
    double sigma_space = thresh_space;

    double i2sigma_color = 1/(sigma_color*sigma_color);
    double i2sigma_space = 1/(sigma_space*sigma_space); 

    cvGetRawData(in, &_idata, &step, &size);
    cvGetRawData(out, &_odata, &step, &size);
    idata = _idata;
    odata = _odata;

    double mean1;
    double mean0;
    double w;
    int deltas[8];
    double weight_tab[8];

    int i, j;

#define INIT\
            color = idata[0]; \
            mean0 = 1; mean1 = color;

#define COLOR_DISTANCE(c1, c2)\
            fabs(c1 - c2)
#define KERNEL_ELEMENT(k)\
            temp_color = idata[deltas[k]];\
            w = weight_tab[k] + COLOR_DISTANCE(color, temp_color)*i2sigma_color;\
            w = 1./(w*w + 1); \
            mean0 += w;\
            mean1 += temp_color*w;

#define UPDATE_OUTPUT\
            odata[i] = (uchar)cvRound(mean1/mean0);

#define INIT_MAIN \
            color = idata[0];

#define KERNEL_ELEMENT_MAIN(k)\
            temp_color = idata[deltas[k]];\
            t = weight_tab[k] + COLOR_DISTANCE(color, temp_color)*i2sigma_color;\
            buf[k] = t*t + 1;

#define UPDATE_OUTPUT_MAIN     \
                               \
            a = buf[0]*buf[1]; \
            b = buf[2]*buf[3]; \
            t = 1./(a*b);      \
            a *= t;            \
            b *= t;            \
            t = buf[2]*a;      \
            buf[2] = buf[3]*a; \
            buf[3] = t;        \
            t = buf[0]*b;      \
            buf[0] = buf[1]*b; \
            buf[1] = t;        \
                               \
            a = buf[4]*buf[5]; \
            b = buf[6]*buf[7]; \
            t = 1./(a*b);      \
            a *= t;            \
            b *= t;            \
            t = buf[6]*a;      \
            buf[6] = buf[7]*a; \
            buf[7] = t;        \
            t = buf[4]*b;      \
            buf[4] = buf[5]*b; \
            buf[5] = t;        \
                               \
            mean0 = 1./(1 + buf[0] + buf[1] + buf[2] + buf[3] +\
                        buf[4] + buf[5] + buf[6] + buf[7]);\
            mean1 = idata[0] + idata[1]*buf[1] + idata[-step+1]*buf[1] +\
                    idata[-step]*buf[2] + idata[-step-1]*buf[3] +\
                    idata[-1]*buf[4] + idata[step-1]*buf[5] +\
                    idata[step]*buf[6] + idata[step+1]*buf[7];\
            it = cvRound(mean1*mean0); \
            odata[i] = (uchar)((it & ~255) == 0 ? it : it > 255 ? 255 : 0);

    int color, temp_color;

    CV_INIT_3X3_DELTAS( deltas, step, 3 );

    weight_tab[0] = weight_tab[2] = weight_tab[4] = weight_tab[6] = i2sigma_space;
    weight_tab[1] = weight_tab[3] = weight_tab[5] = weight_tab[7] = i2sigma_space*2;

    for( i = 0; i < size.width; i++, idata++ )
    {
        INIT;
        KERNEL_ELEMENT(6);
        if( i > 0 )
        {
            KERNEL_ELEMENT(5);
            KERNEL_ELEMENT(4);
        }
        if( i < size.width - 1 )
        {
            KERNEL_ELEMENT(7);
            KERNEL_ELEMENT(0);
        }
        UPDATE_OUTPUT;
    }
    
    idata = _idata + step;
    odata = _odata + step;

    for(j = 1; j < size.height - 1; j++, _idata += step, idata = _idata, _odata += step, odata = _odata)
    {
        // i = 0;
        INIT;
        KERNEL_ELEMENT(0);
        KERNEL_ELEMENT(1);
        KERNEL_ELEMENT(2);
        KERNEL_ELEMENT(6);
        KERNEL_ELEMENT(7);
        UPDATE_OUTPUT;

        for( i = 1; i < size.width - 1; i++, idata++ )
        {
            double a, b, t;
            double buf[8];
            int it;
            
            INIT_MAIN;
            KERNEL_ELEMENT_MAIN(0);
            KERNEL_ELEMENT_MAIN(1);
            KERNEL_ELEMENT_MAIN(2);
            KERNEL_ELEMENT_MAIN(3);
            KERNEL_ELEMENT_MAIN(4);
            KERNEL_ELEMENT_MAIN(5);
            KERNEL_ELEMENT_MAIN(6);
            KERNEL_ELEMENT_MAIN(7);
            UPDATE_OUTPUT_MAIN;
        }

        // i = size.width - 1;
        INIT;
        KERNEL_ELEMENT(2);
        KERNEL_ELEMENT(3);
        KERNEL_ELEMENT(4);
        KERNEL_ELEMENT(5);
        KERNEL_ELEMENT(6);
        UPDATE_OUTPUT;
    }

    for( i = 0; i < size.width; i++, idata++ )
    {
        INIT;
        KERNEL_ELEMENT(2);
        if( i > 0 )
        {
            KERNEL_ELEMENT(3);
            KERNEL_ELEMENT(4);
        }
        if( i < size.width - 1 )
        {
            KERNEL_ELEMENT(1);
            KERNEL_ELEMENT(0);
        }
        UPDATE_OUTPUT;
    }

#undef INIT
#undef KERNEL_ELEMENT
#undef UPDATE_OUTPUT
#undef INIT_MAIN
#undef KERNEL_ELEMENT_MAIN
#undef UPDATE_OUTPUT_MAIN
#undef COLOR_DISTANCE
}


void icvBilateralFiltering8uC3(IplImage* in, IplImage* out, int thresh_space, int thresh_color)
{
    uchar* idata;
    uchar* odata;
    uchar* _idata;
    uchar* _odata;
    int step;
    CvSize size;

    double sigma_color = thresh_color; 
    double sigma_space = thresh_space;

    double i2sigma_color = 1/(sigma_color*sigma_color);
    double i2sigma_space = 1/(sigma_space*sigma_space); 

    cvGetRawData(in, &_idata, &step, &size);
    cvGetRawData(out, &_odata, &step, &size);
    idata = _idata;
    odata = _odata;

    double mean1[3] = {0, 0, 0};
    double mean0 = 0;
    double w;
    int deltas[8];
    double weight_tab[8];

    int i, j;

#define INIT\
            mean0 = 1; mean1[0] = idata[0];mean1[1] = idata[2];mean1[2] = idata[3];

#define COLOR_DISTANCE(c1, c2)\
            (fabs(c1[0] - c2[0]) + fabs(c1[1] - c2[1]) + fabs(c1[2] - c2[2]))
#define KERNEL_ELEMENT(k)\
            temp_color = idata + deltas[k];\
            w = weight_tab[k] + COLOR_DISTANCE(idata, temp_color)*i2sigma_color;\
            w = 1./(w*w + 1); \
            mean0 += w;\
            mean1[0] += temp_color[0]*w; \
            mean1[1] += temp_color[1]*w; \
            mean1[2] += temp_color[2]*w;

#define UPDATE_OUTPUT\
            mean0 = 1./mean0;\
            odata[0] = (uchar)cvRound(mean1[0]*mean0); \
            odata[1] = (uchar)cvRound(mean1[1]*mean0); \
            odata[2] = (uchar)cvRound(mean1[2]*mean0);

#define INIT_MAIN

#define KERNEL_ELEMENT_MAIN(k)\
            temp_color = idata + deltas[k];\
            t = weight_tab[k] + COLOR_DISTANCE(idata, temp_color)*i2sigma_color;\
            buf[k] = t*t + 1;

#define UPDATE_OUTPUT_MAIN     \
                               \
            a = buf[0]*buf[1]; \
            b = buf[2]*buf[3]; \
            t = 1./(a*b);      \
            a *= t;            \
            b *= t;            \
            t = buf[2]*a;      \
            buf[2] = buf[3]*a; \
            buf[3] = t;        \
            t = buf[0]*b;      \
            buf[0] = buf[1]*b; \
            buf[1] = t;        \
                               \
            a = buf[4]*buf[5]; \
            b = buf[6]*buf[7]; \
            d = 1./(a*b);      \
            a *= d;            \
            b *= d;            \
            t = buf[6]*a;      \
            buf[6] = buf[7]*a; \
            buf[7] = t;        \
            t = buf[4]*b;      \
            buf[4] = buf[5]*b; \
            buf[5] = t;        \
                               \
            mean0 = 1./(1 + buf[0] + buf[1] + buf[2] + buf[3] +\
                        buf[4] + buf[5] + buf[6] + buf[7]);\
            mean1[0] = idata[0] + idata[3]*buf[1] + idata[-step+3]*buf[1] +\
                       idata[-step]*buf[2] + idata[-step-3]*buf[3] +\
                       idata[-3]*buf[4] + idata[step-3]*buf[5] +\
                       idata[step]*buf[6] + idata[step+3]*buf[7];\
                                                                 \
            mean1[1] = idata[1] + idata[4]*buf[1] + idata[-step+4]*buf[1] +\
                       idata[-step+1]*buf[2] + idata[-step-2]*buf[3] +\
                       idata[-2]*buf[4] + idata[step-2]*buf[5] +\
                       idata[step+1]*buf[6] + idata[step+4]*buf[7];\
                                                                   \
            mean1[2] = idata[2] + idata[5]*buf[1] + idata[-step+5]*buf[1] +\
                       idata[-step+2]*buf[2] + idata[-step-1]*buf[3] +\
                       idata[-1]*buf[4] + idata[step-1]*buf[5] +\
                       idata[step+2]*buf[6] + idata[step+5]*buf[7];\
            it = cvRound(mean1[0]*mean0); \
            odata[0] = (uchar)((it & ~255) == 0 ? it : it > 255 ? 255 : 0); \
            it = cvRound(mean1[1]*mean0);                                   \
            odata[1] = (uchar)((it & ~255) == 0 ? it : it > 255 ? 255 : 0); \
            it = cvRound(mean1[2]*mean0);                                   \
            odata[2] = (uchar)((it & ~255) == 0 ? it : it > 255 ? 255 : 0);

    uchar* temp_color;

    CV_INIT_3X3_DELTAS( deltas, step, 3 );

    weight_tab[0] = weight_tab[2] = weight_tab[4] = weight_tab[6] = i2sigma_space;
    weight_tab[1] = weight_tab[3] = weight_tab[5] = weight_tab[7] = i2sigma_space*2;

    for( i = 0; i < size.width; i++, idata += 3, odata += 3)
    {
        INIT;
        KERNEL_ELEMENT(6);
        if( i > 0 )
        {
            KERNEL_ELEMENT(5);
            KERNEL_ELEMENT(4);
        }
        if( i < size.width - 1 )
        {
            KERNEL_ELEMENT(7);
            KERNEL_ELEMENT(0);
        }
        UPDATE_OUTPUT;
    }
    
    idata = _idata + step;
    odata = _odata + step;

    for(j = 1; j < size.height - 1; j++, _idata += step, idata = _idata, _odata += step, odata = _odata)
    {
        // i = 0;
        INIT;
        KERNEL_ELEMENT(0);
        KERNEL_ELEMENT(1);
        KERNEL_ELEMENT(2);
        KERNEL_ELEMENT(6);
        KERNEL_ELEMENT(7);
        UPDATE_OUTPUT;

        for( i = 1; i < size.width - 1; i++, idata += 3, odata += 3)
        {
            double a, b, d, t;
            double buf[8];
            int it;
            
            INIT_MAIN;
            KERNEL_ELEMENT_MAIN(0);
            KERNEL_ELEMENT_MAIN(1);
            KERNEL_ELEMENT_MAIN(2);
            KERNEL_ELEMENT_MAIN(3);
            KERNEL_ELEMENT_MAIN(4);
            KERNEL_ELEMENT_MAIN(5);
            KERNEL_ELEMENT_MAIN(6);
            KERNEL_ELEMENT_MAIN(7);
            UPDATE_OUTPUT_MAIN;
        }

        // i = size.width - 1;
        INIT;
        KERNEL_ELEMENT(2);
        KERNEL_ELEMENT(3);
        KERNEL_ELEMENT(4);
        KERNEL_ELEMENT(5);
        KERNEL_ELEMENT(6);
        UPDATE_OUTPUT;
    }

    for( i = 0; i < size.width; i++, idata += 3, odata += 3 )
    {
        INIT;
        KERNEL_ELEMENT(2);
        if( i > 0 )
        {
            KERNEL_ELEMENT(3);
            KERNEL_ELEMENT(4);
        }
        if( i < size.width - 1 )
        {
            KERNEL_ELEMENT(1);
            KERNEL_ELEMENT(0);
        }
        UPDATE_OUTPUT;
    }

#undef INIT
#undef KERNEL_ELEMENT
#undef UPDATE_OUTPUT
}


void icvBilateralFiltering16sC1(IplImage* in, IplImage* out, int thresh_space, int thresh_color)
{
    short* idata;
    short* odata;
    uchar* _idata;
    uchar* _odata;
    int step;
    CvSize size;

    double sigma_color = thresh_color; 
    double sigma_space = thresh_space;

    double i2sigma_color = 1/(sigma_color*sigma_color);
    double i2sigma_space = 1/(sigma_space*sigma_space); 

    cvGetImageRawData(in, &_idata, &step, &size);
    cvGetImageRawData(out, &_odata, &step, &size);
    idata = (short*)_idata;
    odata = (short*)_odata;

    double mean1 = 0;
    double mean0 = 0;
    double w;

    int i, j;

#define INIT\
            color = idata[0];\
            mean0 = 0;mean1 = 0;

#define KERNEL_ELEMENT(m, n)\
            temp_color = idata[(m)*step + (n)];\
            w = (double)weight(-((m)*(m) + (n)*(n))*i2sigma_space - (temp_color - color)*(temp_color - color)*i2sigma_color);\
            mean0 += w;\
            mean1 += idata[(m)*step + (n)]*w;\

#define UPDATE_OUTPUT\
            *odata = (short)floor(mean1/mean0);

    int color, temp_color;

    // j = 0, i = 0;
    INIT;
    KERNEL_ELEMENT(0, 0);
    KERNEL_ELEMENT(0, 1);
    KERNEL_ELEMENT(1, 0);
    UPDATE_OUTPUT;
    idata++;
    odata++;

    for(i = 1; i < size.width - 1; i++, idata += 1, odata += 1)
    {
        INIT;
        KERNEL_ELEMENT(0, 0);
        KERNEL_ELEMENT(0, 1);
        KERNEL_ELEMENT(0, -1);
        KERNEL_ELEMENT(1, 0);
        KERNEL_ELEMENT(1, 1);
        KERNEL_ELEMENT(1, -1);
        UPDATE_OUTPUT;
    }


    // j = 0, i = size.width - 1
    INIT;
    KERNEL_ELEMENT(0, 0);
    KERNEL_ELEMENT(0, -1);
    KERNEL_ELEMENT(1, 0);
    UPDATE_OUTPUT;
    idata = (short*)(_idata + step);
    odata = (short*)(_odata + step);

    for(j = 1; j < size.height - 1; j++, _idata += step, idata = (short*)_idata, _odata += step, odata = (short*)_odata)
    {
        // i = 0;
        INIT;
        KERNEL_ELEMENT(0, 0);
        KERNEL_ELEMENT(0, 1);
        KERNEL_ELEMENT(-1, 0);
        KERNEL_ELEMENT(-1, 1);
        KERNEL_ELEMENT(1, 0);
        KERNEL_ELEMENT(1, 1);
        UPDATE_OUTPUT;

        for(int i = 1; i < size.width - 1; i++, idata += 1, odata += 1)
        {
            INIT;
            KERNEL_ELEMENT(0, 0);
            KERNEL_ELEMENT(1, 0);
            KERNEL_ELEMENT(-1, 0);
            KERNEL_ELEMENT(-1, 1);
            KERNEL_ELEMENT(0, 1);
            KERNEL_ELEMENT(1, 1);
            KERNEL_ELEMENT(-1, -1);
            KERNEL_ELEMENT(0, -1);
            KERNEL_ELEMENT(1, -1);
            UPDATE_OUTPUT;
        }

        // i = size.width - 1;
        INIT;
        KERNEL_ELEMENT(0, 0);
        KERNEL_ELEMENT(0, -1);
        KERNEL_ELEMENT(-1, 0);
        KERNEL_ELEMENT(-1, -1);
        KERNEL_ELEMENT(1, 0);
        KERNEL_ELEMENT(1, -1);
        UPDATE_OUTPUT;
    }

    // j = size.height - 1, i = 0;
    INIT;
    KERNEL_ELEMENT(0, 0);
    KERNEL_ELEMENT(0, 1);
    KERNEL_ELEMENT(-1, 0);
    UPDATE_OUTPUT;
    idata++;
    odata++;

    for(i = 1; i < size.width - 1; i++, idata += 1, odata += 1)
    {
        INIT;
        KERNEL_ELEMENT(0, 0);
        KERNEL_ELEMENT(0, 1);
        KERNEL_ELEMENT(0, -1);
        KERNEL_ELEMENT(-1, 0);
        KERNEL_ELEMENT(-1, 1);
        KERNEL_ELEMENT(-1, -1);
        UPDATE_OUTPUT;
    }
    // j = size.height - 1, i = size.width - 1
    INIT;
    KERNEL_ELEMENT(0, 0);
    KERNEL_ELEMENT(0, -1);
    KERNEL_ELEMENT(1, 0);
    UPDATE_OUTPUT;

#undef INIT
#undef KERNEL_ELEMENT
#undef UPDATE_OUTPUT
    
}

