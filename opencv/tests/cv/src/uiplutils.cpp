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
#include <math.h>
#include <assert.h>
#include <float.h>

#define  clip(x,a,b)  ((x)<(a) ? (a) : (x) > (b) ? (b) : (x))

void  atsGetImageInfo( IplImage* img, void** pData, int* pStep,
                       CvSize*  pSz, int*  pDepth, int* pChannels,
                       int* pBtPix )
{
    if( !img )
    {
        assert(0);
    }
    else
    {
        int channels = img->nChannels;
        int depth    = img->depth;
        int step     = img->widthStep;
        int bt_pix;

        if( img->origin != IPL_ORIGIN_TL ||
            img->dataOrder != IPL_DATA_ORDER_PIXEL )
        {
            assert(0);
            return;
        }

        bt_pix = ((depth & 255) >> 3) * channels;

        if( pDepth )    *pDepth    = depth;
        if( pChannels ) *pChannels = channels;
        if( pStep )     *pStep     = step;
        if( pBtPix )    *pBtPix    = bt_pix;

        if( pSz )
        {
            pSz->width = img->roi ? img->roi->width : img->width;
            pSz->height= img->roi ? img->roi->height : img->height;
        }

        if( pData )
        {
            *pData = img->imageData + (!img->roi ? 0 :
                     img->roi->yOffset*step + img->roi->xOffset*bt_pix );
        }
    }
}


/*
   Fills the whole image or selected ROI by random numbers.
   Supports only 8u, 8s and 32f formats.
*/
void atsFillRandomImage( IplImage* img, double low, double high )
{
    int      depth, channels, step;
    CvSize  sz;
    void*    data;

    atsGetImageInfo( img, (void**)&data, &step, &sz, &depth, &channels, 0 );
    sz.width *= channels;

    switch( depth )
    {
    case IPL_DEPTH_32F:
    {
        float *fdata = (float*)data;
        int    x, y;

        step /= sizeof(float);
        high = (high-low)/RAND_MAX;
        for( y = 0; y < sz.height; y++, fdata += step )
            for( x = 0; x < sz.width; x++ )
            {
                fdata[x] = (float)(rand()*high + low);
            }
        break;
    }
    case IPL_DEPTH_8U:
    case IPL_DEPTH_8S:
    {
        int l = (int)(low + (low > 0 ? .5 : low == 0 ? 0 : -.5));
        int h = (int)floor(high+(high > 0 ? .5 : high == 0 ? 0 : -.5));
        int x, y;
        uchar *udata = (uchar*)data;

        if( img->depth == IPL_DEPTH_8U )
        {
            l = clip( l, 0, 255 );
            h = clip( h, 0, 255 );
        }
        else
        {
            l = clip( l, -128, 127 );
            h = clip( h, -128, 127 );
        }
        if( l > h ) x = l, l = h, h = x;
        h -= l - 1;

        if( h == 256 ) /* speedup */
        {
            int w1 = sz.width&1;
            for( y = 0; y < sz.height; y++, udata += step )
            {
                for( x = 0; x+1 < sz.width; x += 2 )
                {
                    *((short*)(udata + x)) = (short)rand();
                }
                if( w1 ) udata[sz.width-1] = (uchar)(rand()&255);
            }
        }
        else
        {
            for( y = 0; y < sz.height; y++, udata += step )
                for( x = 0; x < sz.width; x++ )
                {
                    udata[x] = (uchar)(rand()%h + l);
                }
        }
        break;
    }
    default: assert(0);
    }
}


/*
   Fills the whole image or selected ROI by random numbers using 32-bit RNG.
   Supports only 8u, 8s and 32f formats.
*/
void atsFillRandomImageEx( IplImage* img, AtsRandState* state )
{
    int      depth, channels, step;
    CvSize  sz;
    void*    _data;

    atsGetImageInfo( img, (void**)&_data, &step, &sz, &depth, &channels, 0 );
    sz.width *= channels;

    switch( depth )
    {
    case IPL_DEPTH_32F:
    {
        float *data = (float*)_data;
        int    y;

        step /= sizeof(data[0]);

        for( y = 0; y < sz.height; y++, data += step )
        {
            atsbRand32f( state, data, sz.width );
        }
        break;
    }
    case IPL_DEPTH_8U:
    case IPL_DEPTH_8S:
    {
        uchar *data = (uchar*)_data;
        int    y;

        step /= sizeof(data[0]);

        for( y = 0; y < sz.height; y++, data += step )
        {
            atsbRand8u( state, data, sz.width );
        }
        break;
    }
    case IPL_DEPTH_16S:
    {
        short *data = (short*)_data;
        int    y;

        step /= sizeof(data[0]);

        for( y = 0; y < sz.height; y++, data += step )
        {
            atsbRand16s( state, data, sz.width );
        }
        break;
    }
    case IPL_DEPTH_32S:
    {
        int  *data = (int*)_data;
        int   y;

        step /= sizeof(data[0]);

        for( y = 0; y < sz.height; y++, data += step )
        {
            atsbRand32s( state, data, sz.width );
        }
        break;
    }
    default: assert(0);
    }
}


/* Allocates the IPL image and (may be) clears it */
IplImage*  atsCreateImage( int w, int h, int depth, int nch, int clear_flag )
{
    IplImage *img = iplCreateImageHeader
        ( nch, 0, depth, "", "", IPL_DATA_ORDER_PIXEL,
          IPL_ORIGIN_TL, 8, w, h, 0, 0, 0, 0 );

    if( depth == IPL_DEPTH_32F )
    {
        iplAllocateImageFP( img, clear_flag, 0 );
    }
    else
    {
        iplAllocateImage( img, clear_flag, 0 );
    }
    return img;
}


void atsReleaseImage( IplImage* img )
{
    assert( img->roi == 0 && img->maskROI == 0 );
    iplDeallocate( img, IPL_IMAGE_ALL );
}


/* extracts ROI data from the image and writes it in a single row */
void atsGetDataFromImage( IplImage* img, void* data )
{
    char*    src;
    char*    dst = (char*)data;
    int      bt_pix, step;
    CvSize  sz;
    int      y;

    atsGetImageInfo( img, (void**)&src, &step, &sz, 0, 0, &bt_pix );
    sz.width *= bt_pix;

    for( y = 0; y < sz.height; y++, src += step, dst += sz.width )
    {
        memcpy( dst, src, sz.width );
    }
}

/* writes linear data to the image ROI */
void atsPutDataToImage( IplImage *img, void *data )
{
    char    *src = (char*)data, *dst;
    int      bt_pix, step;
    CvSize  sz;
    int      y;

    atsGetImageInfo( img, (void**)&dst, &step, &sz, 0, 0, &bt_pix );
    sz.width *= bt_pix;

    for( y = 0; y < sz.height; y++, dst += step, src += sz.width )
    {
        memcpy( dst, src, sz.width );
    }
}


void atsConvert( IplImage* src, IplImage* dst )
{
    char* src_data = 0;
    char* dst_data = 0;
    int   src_step = 0, dst_step = 0;
    int   src_depth = 0, dst_depth = 0;
    int   src_channels = 0, dst_channels = 0;
    CvSize sz, sz2;

    atsGetImageInfo( src, (void**)&src_data, &src_step, &sz, &src_depth,
                     &src_channels, 0 );
    atsGetImageInfo( dst, (void**)&dst_data, &dst_step, &sz2,
                     &dst_depth, &dst_channels, 0 );

    assert( src_channels == dst_channels );

    if( src_depth == dst_depth )
        iplCopy( src, dst );
    else if( src_depth != IPL_DEPTH_32F && dst_depth != IPL_DEPTH_32F )
        iplConvert( src, dst );
    else
    {
        int i, j;
        sz.width  = (MIN( sz.width, sz2.width ))*src_channels;
        sz.height = MIN( sz.height, sz2.height );

        if( dst_depth == IPL_DEPTH_32F )
        {
            switch( src_depth )
            {
            case IPL_DEPTH_8U:
                for( i = 0; i < sz.height; i++, src_data += src_step, dst_data += dst_step )
                    for( j = 0; j < sz.width; j++ )
                        ((float*)dst_data)[j] = ((uchar*)src_data)[j];
                break;
            case IPL_DEPTH_8S:
                for( i = 0; i < sz.height; i++, src_data += src_step, dst_data += dst_step )
                    for( j = 0; j < sz.width; j++ )
                        ((float*)dst_data)[j] = src_data[j];
                break;
            case IPL_DEPTH_16S:
                for( i = 0; i < sz.height; i++, src_data += src_step, dst_data += dst_step )
                    for( j = 0; j < sz.width; j++ )
                        ((float*)dst_data)[j] = ((short*)src_data)[j];
                break;
            case IPL_DEPTH_32S:
                for( i = 0; i < sz.height; i++, src_data += src_step, dst_data += dst_step )
                    for( j = 0; j < sz.width; j++ )
                        ((float*)dst_data)[j] = (float)((int*)src_data)[j];
                break;
            }
        }
        else
        {
            switch( dst_depth )
            {
            case IPL_DEPTH_8U:
                for( i = 0; i < sz.height; i++, src_data += src_step, dst_data += dst_step )
                    for( j = 0; j < sz.width; j++ )
                    {
                        int t = cvRound(((float*)src_data)[j]);
                        ((uchar*)dst_data)[j] = (uchar)(!(t & ~255) ? t : t < 0 ? 0 : 255);
                    }
                break;
            case IPL_DEPTH_8S:
                for( i = 0; i < sz.height; i++, src_data += src_step, dst_data += dst_step )
                    for( j = 0; j < sz.width; j++ )
                    {
                        int t = cvRound(((float*)src_data)[j]);
                        ((char*)dst_data)[j] = (char)(!((t + 128) & ~255) ? t : t < 0 ? -128 : 127);
                    }
                break;
            case IPL_DEPTH_16S:
                for( i = 0; i < sz.height; i++, src_data += src_step, dst_data += dst_step )
                    for( j = 0; j < sz.width; j++ )
                    {
                        int t = cvRound(((float*)src_data)[j]);
                        ((short*)dst_data)[j] = (short)(!((t + 32768) & ~65535) ? t :
                                                         t < 0 ? -32768 : 32767);
                    }
                break;
            case IPL_DEPTH_32S:
                for( i = 0; i < sz.height; i++, src_data += src_step, dst_data += dst_step )
                    for( j = 0; j < sz.width; j++ )
                        ((int*)dst_data)[j] = (int)cvRound(((float*)src_data)[j]);
                break;
            }
        }
    }
}


/*
   The function applies min filter using specified structuring element.
   float numbers are processed using integer arithmetics (IEEE 754 format is assumed)
*/
void atsMinFilterEx( IplImage* src, IplImage* dst, IplConvKernel* B )
{
    const    int  int_extr0   = 0x7fffffff;

    uchar*   srcData;
    uchar*   dstData;

    int      srcStep, dstStep;
    int      depth;
    int      ach; /* how many non-alpha channels and all the channels */
    CvSize  sz;

    int      cols    = B->nCols;
    int      rows    = B->nRows;
    int      anchorX = B->anchorX;
    int      anchorY = B->anchorY;
    int*     mask = B->values;

    int      x, y, c;

    atsGetImageInfo( src, (void**)&srcData, &srcStep, &sz, &depth, &ach, 0 );
    atsGetImageInfo( dst, (void**)&dstData, &dstStep, 0, 0, 0, 0 );

    switch( depth )
    {
    case IPL_DEPTH_8U:
        for( y = 0; y < sz.height; y++ )
            for( x = 0; x < sz.width; x++ )
                for( c = 0; c < ach; c++ )
                {
                    int val = int_extr0;
                    int  x1, y1 = y - anchorY;
                    int  i, j;

                    for( i = 0; i < rows; i++, y1++ )
                        for( j = 0, x1 = x - anchorX; j < cols; j++, x1++ )
                        {
                            int x2 = x1, y2 = y1;
                            if( x1 < 0 ) x2 = 0;
                            if( x1 >= sz.width ) x2 = sz.width - 1;
                            if( y1 < 0 ) y2 = 0;
                            if( y1 >= sz.height ) y2 = sz.height - 1;

                            /* unsigned comparsion helps to check for positivity */
                            if( mask[i*cols + j] != 0 )
                            {
                                int temp = srcData[y2*srcStep + x2*ach + c];
                                val = ATS_MIN( val, temp );
                            }
                        }

                    dstData[y*dstStep + x*ach + c] = (uchar)val;
                }
        break;

    case IPL_DEPTH_32F:
        {
        int *fltSrc = (int*)srcData;
        int *fltDst = (int*)dstData;

        srcStep /= sizeof(int);
        dstStep /= sizeof(int);

        for( y = 0; y < sz.height; y++ )
            for( x = 0; x < sz.width; x++ )
                for( c = 0; c < ach; c++ )
                {
                    int  val = int_extr0;
                    int  x1, y1 = y - anchorY;
                    int  i, j;

                    for( i = 0; i < rows; i++, y1++ )
                        for( j = 0, x1 = x - anchorX; j < cols; j++, x1++ )
                        {
                            int x2 = x1, y2 = y1;
                            if( x1 < 0 ) x2 = 0;
                            if( x1 >= sz.width ) x2 = sz.width - 1;
                            if( y1 < 0 ) y2 = 0;
                            if( y1 >= sz.height ) y2 = sz.height - 1;

                            /* unsigned comparsion helps to check for positivity */
                            if( mask[i*cols + j] != 0 )
                            {
                                int temp = fltSrc[y2*srcStep + x2*ach + c];
                                temp = ATS_TOGGLE_FLT( temp );
                                val = ATS_MIN( val, temp );
                            }
                        }

                    fltDst[y*dstStep + x*ach + c] = ATS_TOGGLE_FLT(val);
                }
        }
        break;
    default: assert(0);
    }
}


/*
   The function applies min filter using specified structuring element.
   float numbers are processed using integer arithmetics (IEEE 754 format is assumed)
*/
void atsMaxFilterEx( IplImage* src, IplImage* dst,
                     IplConvKernel* B )
{
    const    int  int_extr0   = 0x80000000;

    uchar*   srcData;
    uchar*   dstData;

    int      srcStep, dstStep;
    int      depth;
    int      ach; /* how many non-alpha channels and all the channels */
    CvSize  sz;

    int      cols    = B->nCols;
    int      rows    = B->nRows;
    int      anchorX = B->anchorX;
    int      anchorY = B->anchorY;
    int*     mask = B->values;

    int      x, y, c;

    atsGetImageInfo( src, (void**)&srcData, &srcStep, &sz, &depth, &ach, 0 );
    atsGetImageInfo( dst, (void**)&dstData, &dstStep, 0, 0, 0, 0 );

    switch( depth )
    {
    case IPL_DEPTH_8U:
        for( y = 0; y < sz.height; y++ )
            for( x = 0; x < sz.width; x++ )
                for( c = 0; c < ach; c++ )
                {
                    int val = int_extr0;
                    int  x1, y1 = y - anchorY;
                    int  i, j;

                    for( i = 0; i < rows; i++, y1++ )
                        for( j = 0, x1 = x - anchorX; j < cols; j++, x1++ )
                        {
                            int x2 = x1, y2 = y1;
                            if( x1 < 0 ) x2 = 0;
                            if( x1 >= sz.width ) x2 = sz.width - 1;
                            if( y1 < 0 ) y2 = 0;
                            if( y1 >= sz.height ) y2 = sz.height - 1;

                            /* unsigned comparsion helps to check for positivity */
                            if( mask[i*cols + j] != 0 )
                            {
                                int temp = srcData[y2*srcStep + x2*ach + c];
                                val = ATS_MAX( val, temp );
                            }
                        }

                    dstData[y*dstStep + x*ach + c] = (uchar)val;
                }
        break;

    case IPL_DEPTH_32F:
        {
        int *fltSrc = (int*)srcData;
        int *fltDst = (int*)dstData;

        srcStep /= sizeof(int);
        dstStep /= sizeof(int);

        for( y = 0; y < sz.height; y++ )
            for( x = 0; x < sz.width; x++ )
                for( c = 0; c < ach; c++ )
                {
                    int  val = int_extr0;
                    int  x1, y1 = y - anchorY;
                    int  i, j;

                    for( i = 0; i < rows; i++, y1++ )
                        for( j = 0, x1 = x - anchorX; j < cols; j++, x1++ )
                        {
                            int x2 = x1, y2 = y1;
                            if( x1 < 0 ) x2 = 0;
                            if( x1 >= sz.width ) x2 = sz.width - 1;
                            if( y1 < 0 ) y2 = 0;
                            if( y1 >= sz.height ) y2 = sz.height - 1;

                            /* unsigned comparsion helps to check for positivity */
                            if( mask[i*cols + j] != 0 )
                            {
                                int temp = fltSrc[y2*srcStep + x2*ach + c];
                                temp = ATS_TOGGLE_FLT( temp );
                                val = ATS_MAX( val, temp );
                            }
                        }

                    fltDst[y*dstStep + x*ach + c] = ATS_TOGGLE_FLT(val);
                }
        }
        break;
    default: assert(0);
    }
}



/*
   Replicates left and right ROI borders dx times,
   top and bottom ROI borders dy times.
*/
void atsReplicateBorders( IplImage* img, int dx, int dy )
{
    int      step;
    uchar*   data;
    int      bt_pix;
    int      x, y;
    int      x0, x1, y0, y1;
    int      count;
    int      copy_width;
    CvSize  sz;

    iplSetBorderMode( img, IPL_BORDER_REPLICATE, IPL_SIDE_ALL, 0 );

    if( !img->roi ) return;

    atsGetImageInfo( img, (void**)&data, &step, &sz, 0, 0, &bt_pix );

    x0 = img->roi->xOffset;
    y0 = img->roi->yOffset;

    x1 = x0 + sz.width - 1;
    y1 = y0 + sz.height - 1;

    copy_width = sz.width * bt_pix;

    /* left border */
    count = (x0 - dx >= 0 ? dx : x0)*bt_pix;
    copy_width += count;

    if( count > 0 )
    {
        for( y = 0; y < sz.height; y++, data += step )
            for( x = count; x > 0; x -= bt_pix ) memcpy( data - x, data, bt_pix );
        data -= sz.height*step;
    }

    /* right border */
    count = (x1 + dx < img->width ? dx : img->width - x1 - 1)*bt_pix;
    copy_width += count;

    if( count > 0 )
    {
        data += (sz.width - 1)*bt_pix;
        for( y = 0; y < sz.height; y++, data += step )
            for( x = count; x > 0; x -= bt_pix ) memcpy( data + x, data, bt_pix );
        data -= sz.height*step + (sz.width - 1)*bt_pix;
    }

    /* top border */
    count = (y0 - dy >= 0 ? dy : y0)*step;
    if( count > 0 )
    {
        for( y = count; y > 0; y -= step ) memcpy( data - y, data, copy_width );
    }

    /* bottom border */
    count = (y1 + dy < img->height ? dy : img->height - y1 - 1)*step;
    if( count > 0 )
    {
        data += (sz.height - 1)*step;
        for( y = count; y > 0; y -= step ) memcpy( data + y, data, copy_width );
    }
}


/*
   The convolution function.
   Supports only 32fC1 images
*/
void atsConvolve( IplImage* src, IplImage* dst,
                  IplConvKernelFP* ker )
{
    float*   srcData;
    float*   dstData;

    int      srcStep, dstStep;
    CvSize  sz;

    int      cols     = ker->nCols;
    int      rows     = ker->nRows;
    int      anchorX  = ker->anchorX;
    int      anchorY  = ker->anchorY;
    float*   ker_data = ker->values;
    int      x, y;

    atsGetImageInfo( src, (void**)&srcData, &srcStep, &sz, 0, 0, 0 );
    atsGetImageInfo( dst, (void**)&dstData, &dstStep, 0, 0, 0, 0 );

    srcStep /= sizeof(int);
    dstStep /= sizeof(int);

    for( y = 0; y < sz.height; y++ )
        for( x = 0; x < sz.width; x++ )
        {
            double sum = 0;
            int   x1, y1 = y - anchorY;
            int  i, j;

            for( i = 0; i < rows; i++, y1++ )
                for( j = 0, x1 = x - anchorX; j < cols; j++, x1++ )
                {
                    /* unsigned comparsion helps to check for positivity */
                    if( (unsigned)x1 < (unsigned)sz.width  &&
                        (unsigned)y1 < (unsigned)sz.height )
                    {
                        sum += srcData[y1*srcStep + x1] * ker_data[i*rows + j];
                    }
                    else
                    {
                        int x2 = x1, y2 = y1;
                        if( x2 < 0 ) x2 = 0;
                        if( x2 >= sz.width ) x2 = sz.width - 1;
                        if( y2 < 0 ) y2 = 0;
                        if( y2 >= sz.height ) y2 = sz.height - 1;

                        sum += srcData[y2*srcStep + x2] * ker_data[i*rows + j];
                    }
                }

            dstData[y*dstStep + x] = (float)sum;
        }
}


/*
 Function caluclates miscellaneous statistics for the image:
 min & max with locations, number of non-zero pixels, sum of all pixels,
 mean value, standard deviation, c_norm( maximum of absolute values ),
 l1_norm ( sum of absolute values ), l2_norm (square root of sum of values squares)
*/
void  atsCalcImageStatistics(
        IplImage* img, IplImage* mask,
        double* _min_val, double* _max_val,
        CvPoint* _min_loc, CvPoint* _max_loc,
        int* _non_zero, double* _sum,
        double* _mean, double* _svd,
        double* _c_norm, double* _l1_norm, double* _l2_norm,
        int* _mask_pix )
{
    float*   img_data = 0;
    uchar*   mask_data = 0;
    int      img_step = 0, mask_step = 0;

    double   sum = 0, /* pixels sum */
             l1_norm = 0, /* sum of absolute values */
             l2_norm = 0; /* sum of squares (used in stddev and l2 norm) */
    int      non_zero = 0; /* number of non-zero pixels */
    int      mask_counter = 0; /* number of 1-pixels in mask */
    double   c_norm = 0, /* maximum of absolute value */
             min_val = DBL_MAX, /* minimum value */
             max_val = -DBL_MAX; /* maximum value */
    CvPoint min_loc = {0,0}, max_loc = {0,0}; /* current positions of minimum and maximum */
    double   inv_mask_counter = 0;
    int      i, j;
    CvSize  sz;
    int      coi = img->roi ? img->roi->coi : 0;
    int      depth = 0, ch = 0;

    atsGetImageInfo( img, (void**)&img_data, &img_step, &sz, &depth, &ch, 0 );
    assert( depth == IPL_DEPTH_32F && (ch == 1 || (ch == 3 && coi != 0)));

    if( mask )
    {
        atsGetImageInfo( mask, (void**)&mask_data, &mask_step, 0, 0, 0, 0 );
    }

    img_step /= 4;
    img_data += coi == 0 ? 0 : coi - 1;

    /* iterate through the image */
    for( i = 0; i < sz.height; i++, img_data += img_step, mask_data += mask_step )
    {
        for( j = 0; j < sz.width; j++ )
        {
            /* check mask pixel. if mask is absent - all pixels considered */
            if( !mask_data || mask_data[j] != 0 )
            {
                double val = img_data[j*ch];

                /* update minimum */
                if( val < min_val )
                {
                    min_val = val;
                    min_loc.x = j;
                    min_loc.y = i;
                }

                /* update maximum */
                if( val > max_val )
                {
                    max_val = val;
                    max_loc.x = j;
                    max_loc.y = i;
                }

                /* update non-zero */
                non_zero += val != 0;

                /* update sum */
                sum += val;
                val = fabs(val);

                /* update norms */
                if( val > c_norm ) c_norm = val;
                l1_norm += val;
                l2_norm += val*val;

                /* increase mask pixels counter */
                mask_counter++;
            }
        }
    }

    if( mask_counter != 0 )
    {
        inv_mask_counter = 1./mask_counter;
        if( _min_val ) *_min_val = min_val;
        if( _max_val ) *_max_val = max_val;
        if( _min_loc ) *_min_loc = min_loc;
        if( _max_loc ) *_max_loc = max_loc;
    }
    else
    {
        /* set to default if no pixel processed */
        min_loc.x = min_loc.y = 0;
        max_loc.x = max_loc.y = 0;
        min_val = max_val = 0.f;
    }

    if( _mask_pix ) *_mask_pix = mask_counter;
    if( _non_zero ) *_non_zero = non_zero;
    if( _c_norm  ) *_c_norm  = c_norm;
    if( _l1_norm ) *_l1_norm = l1_norm;
    if( _l2_norm ) *_l2_norm = sqrt(l2_norm);
    if( _sum )     *_sum = sum;
    sum *= inv_mask_counter;
    if( _mean )    *_mean = sum;
    if( _svd )     *_svd = sqrt(l2_norm*inv_mask_counter - sum*sum);
}


/*
  Function calculates spatial and central moments up to third order.
  <binary> mode means that pixels values treated as 1 if they are non zero and 0 if zero.
*/
void    atsCalcMoments( IplImage* img, AtsMomentState* state, int binary )
{
    int      x, y;
    uchar*   img_data;
    int      img_step;
    CvSize  sz;
    int      coi = img->roi ? img->roi->coi : 0;
    int      depth = 0, ch = 0;
    double   cx = 0, cy = 0;
    AtsMomentState s;

    memset( &s, 0, sizeof(s));

    atsGetImageInfo( img, (void**)&img_data, &img_step, &sz, &depth, &ch, 0 );
    assert( depth == IPL_DEPTH_32F || depth == IPL_DEPTH_8U || depth == IPL_DEPTH_8S );
    assert( ch == 1 || (ch == 3 && coi != 0));
    assert( sz.width <= 2048 && sz.height <= 2048 );

    img_data += (coi == 0 ? 0 : coi - 1)*((depth & 255) >> 3);

    if( depth == IPL_DEPTH_8U || depth == IPL_DEPTH_8S ||
        (depth == IPL_DEPTH_32F && binary)) /* integer-value spatial moments */
    {
        int64  m00 = 0,
                 m10 = 0, m01 = 0,
                 m20 = 0, m11 = 0, m02 = 0,
                 m30 = 0, m21 = 0, m12 = 0, m03 = 0;

        int x2, y2; /* x^2 & y^2 */
        uchar* data = (uchar*)img_data;

        if( binary != 0 && depth == IPL_DEPTH_8S ) depth = IPL_DEPTH_8U;

        /* calc spatial moments */
        for( y = 0, y2 = 0; y < sz.height; y2 += 2*y + 1, y++, data += img_step )
        {
            int tm0 = 0, tm1 = 0;
            int64 tm2 = 0, tm3 = 0;

            for( x = 0, x2 = 0; x < sz.width; x2 += 2*x + 1, x++ )
            {
                int p, xp;

                if( depth == IPL_DEPTH_8U )
                {
                    p = data[x*ch];
                    if( binary ) p = p != 0;
                }
                else if( depth == IPL_DEPTH_8S )
                {
                    p = ((char*)data)[x*ch];
                }
                else
                {
                    p = ((int*)data)[x*ch]*2 != 0;
                }
                xp = x*p;
                tm0 += p;
                tm1 += xp;
                tm2 += ((int64)x2)*p;
                tm3 += ((int64)x2)*xp;
            }

            m00 += tm0;
            m10 += tm1;
            m01 += tm0*y;
            m20 += tm2;
            m11 += ((int64)tm1)*y;
            m02 += ((int64)tm0)*y2;
            m30 += tm3;
            m21 += tm2*y;
            m12 += ((int64)tm1)*y2;
            m03 += (((int64)tm0)*y2)*y;
        }

        if( m00 != 0 )
        {
            cx = ((double)m10)/m00;
            cy = ((double)m01)/m00;
        }

        s.m00 = (double)m00;
        s.m10 = (double)m10;
        s.m01 = (double)m01;
        s.m20 = (double)m20;
        s.m11 = (double)m11;
        s.m02 = (double)m02;
        s.m30 = (double)m30;
        s.m21 = (double)m21;
        s.m12 = (double)m12;
        s.m03 = (double)m03;
    }
    else /* floating-point spatial moments */
    {
        int x2, y2; /* x^2 & y^2 */
        float* data = (float*)img_data;

        assert( (img_step&3) == 0 );
        img_step /= 4;

        /* calc spatial moments */
        for( y = 0, y2 = 0; y < sz.height; y2 += 2*y + 1, y++, data += img_step )
        {
            double tm0 = 0, tm1 = 0, tm2 = 0, tm3 = 0;

            for( x = 0, x2 = 0; x < sz.width; x2 += 2*x + 1, x++ )
            {
                double p = data[x*ch], xp = x*p;
                tm0 += p;
                tm1 += xp;
                tm2 += x2*p;
                tm3 += x2*xp;
            }

            s.m00 += tm0;
            s.m10 += tm1;
            s.m01 += tm0*y;
            s.m20 += tm2;
            s.m11 += tm1*y;
            s.m02 += tm0*y2;
            s.m30 += tm3;
            s.m21 += tm2*y;
            s.m12 += tm1*y2;
            s.m03 += (tm0*y2)*y;
        }

        if( s.m00 != 0 )
        {
            cx = s.m10/s.m00;
            cy = s.m01/s.m00;
        }
        img_step *= 4;
    }

    /* calc central moments */
    for( y = 0; y < sz.height; y++, img_data += img_step )
    {
        double  tm0 = 0;
        double  tm1 = 0, tm2 = 0, tm3 = 0;
        double  yc = y - cy;
        double  yc2 = yc*yc;

        for( x = 0; x < sz.width; x++ )
        {
            double p;
            double xc = x - cx;
            double xc2 = xc*xc;
            double xcp;

            if( depth == IPL_DEPTH_8U )
            {
                p = binary ? img_data[x*ch] != 0 : img_data[x*ch];
            }
            else if( depth == IPL_DEPTH_8S )
            {
                p = ((char*)img_data)[x*ch];
            }
            else
            {
                p = binary ? ((int*)img_data)[x*ch]*2 != 0 : ((float*)img_data)[x*ch];
            }

            xcp = xc*p;
            tm0 += p;
            tm1 += xcp;
            tm2 += xc2*p;
            tm3 += xc2*xcp;
        }

        s.mu20 += tm2;
        s.mu11 += tm1*yc;
        s.mu02 += tm0*yc2;
        s.mu30 += tm3;
        s.mu21 += tm2*yc;
        s.mu12 += tm1*yc2;
        s.mu03 += tm0*yc2*yc;
    }

    /* calc normalized moments */
    {
        double inv_m00 = s.m00 == 0 ? 0 : 1./s.m00;
        double s2 = inv_m00*inv_m00; /* 1./(m00 ^ (2/2 + 1)) */
        double s3 = s2*sqrt(inv_m00); /* 1./(m00 ^ (3/2 + 1)) */

        s.nu20 = s.mu20 * s2;
        s.nu11 = s.mu11 * s2;
        s.nu02 = s.mu02 * s2;

        s.nu30 = s.mu30 * s3;
        s.nu21 = s.mu21 * s3;
        s.nu12 = s.mu12 * s3;
        s.nu03 = s.mu03 * s3;
    }

    *state = s;
}


/* The function draws line in 8uC1/C3 image */
void  atsDrawLine( IplImage* img, float x1, float y1, float x2, float y2, int color )
{
    float    dx = x2 - x1;
    float    dy = y2 - y1;
    float    adx = (float)fabs(dx);
    float    ady = (float)fabs(dy);
    float    steps = 0;
    uchar*   img_data;
    int      img_step;
    CvSize  sz;
    int      depth = 0, ch = 0, bt_pix = 0;

    uchar    b = (uchar)(color & 0xff);
    uchar    g = (uchar)((color >> 8) & 0xff);
    uchar    r = (uchar)((color >> 16) & 0xff);

    atsGetImageInfo( img, (void**)&img_data, &img_step, &sz, &depth, &ch, &bt_pix );

    assert( depth == IPL_DEPTH_8U );
    assert( ch == 1 || ch == 3);

    if( adx > ady )
    {
        dy /= adx;
        dx = dx > 0 ? 1.f : -1.f;
        steps = adx;
    }
    else if( ady != 0 )
    {
        dx /= ady;
        dy = dy > 0 ? 1.f : -1.f;
        steps = ady;
    }
    else
    {
        dx = dy = 0;
    }

    do
    {
        int x = cvRound(x1);
        int y = cvRound(y1);

        if( (unsigned)x < (unsigned)sz.width &&
            (unsigned)y < (unsigned)sz.height )
        {
            uchar* data = img_data + y*img_step + x*bt_pix;
            data[0] = b;
            if( ch == 3 )
            {
                data[1] = g;
                data[2] = r;
            }
        }

        x1 += dx;
        y1 += dy;
        steps--;
    }
    while( steps >= 0 );
}


/* The function draws ellipse arc in 8uC1/C3 image */
void  atsDrawEllipse( IplImage* img, float xc, float yc, float a, float b,
                      float angle, float arc0, float arc1, int color )
{
    assert( a >= b );
    if( a == 0 ) a = 0.1f;
    if( b == 0 ) b = 0.1f;
    {
    double  ba = b/a;
    double  e = sqrt( 1. - ba*ba);
    double  mag = b*ba;
    double  alpha, beta;
    double  c = a*e;
    double  x, y;
    double  a0 = arc0, a1 = arc1;
    double  ang;
    int     is_pt = arc0 == arc1;

    ang  = IPLsDegToRad(angle);
    alpha = cos(ang);
    beta  = sin(ang);

    if( a0 > a1 )
    {
        double temp = a0;
        a0 = a1;
        a1 = temp;
    }

    if( a1 - a0 >= 360 )
    {
        a0 = a1 = 0;
    }

    a0 = IPL_DegToRad(a0);
    a1 = IPL_DegToRad(a1);

    x = c + a*cos(a0);
    y = b*sin(a0);
    a0 = atan2( y, x )*180/IPL_PI;
    if( a0 < 0 ) a0 += 360.;

    if( is_pt )
        a0 = a1;
    else
    {
        x = c + a*cos(a1);
        y = b*sin(a1);
        a1 = atan2( y, x )*180/IPL_PI;
        if( a1 < 0 ) a1 += 360.f;
        if( a0 > a1 - 0.1 ) a0 -= 360;
    }

    xc = (float)( xc - c*alpha);
    yc = (float)( yc + c*beta);

    atsDrawConic( img, xc, yc, (float)mag, (float)e, angle, (float)a0, (float)a1, color );
    }
}


/* The function draws conic arc in 8uC1/C3 image */
void  atsDrawConic( IplImage* img, float xc, float yc, float mag, float e,
                    float angle, float arc0, float arc1, int color )
{
    int delta = 1;
    double  dang = IPL_PI*delta/180;
    double  alpha, beta;
    double  da = cos(dang), db = sin(dang);
    double  a, b;
    float   x1 = 0.f, y1 = 0.f;
    int     i, n, fl = 0;

    assert( mag > 0 && e >= 0 );

    angle = IPLsDegToRad(angle);
    alpha = cos(angle);
    beta  = sin(angle);

    if( arc0 > arc1 )
    {
        float temp = arc0;
        arc0 = arc1;
        arc1 = temp;
    }

    n = cvRound( arc1 - arc0 );
    if( n > 360 ) n = 360;

    arc0 = IPLsDegToRad(arc0);

    a = cos( arc0 );
    b = sin( arc0 );

    for( i = 0; i < n + delta; i += delta )
    {
        double d;

        if( i > n )
        {
            arc1 = IPLsDegToRad(arc1);
            a = cos(arc1);
            b = sin(arc1);
        }

        d = 1 - e*a;
        if( d != 0 )
        {
            double r = mag/d;
            double x = r*a;
            double y = r*b;
            float  x2 = (float)(xc + x*alpha - y*beta);
            float  y2 = (float)(yc - x*beta - y*alpha);
            if( fl ) atsDrawLine( img, x1, y1, x2, y2, color );
            x1 = x2;
            y1 = y2;
            fl = 1;
        }
        else
        {
            fl = 0;
        }
        d = a*da - b*db;
        b = a*db + b*da;
        a = d;
    }
}


static void _atsCalcConicPoint( double xc, double yc,
                                double mag, double e, double alpha,
                                double beta, double ang, CvPoint* pt )
{
    double a = cos( ang );
    double b = sin( ang );

    double d = 1 - e*a;
    if( d == 0 )
    {
        pt->x = pt->y = -10000;
    }
    else
    {
        d = mag/d;
        a *= d;
        b *= d;
        pt->x = cvRound( xc + alpha*a - beta*b );
        pt->y = cvRound( yc - beta*a - alpha*b );
    }
}


int  atsCalcQuadricCoeffs( double xc, double yc, double mag, double e,
                           double angle, double arc0, double arc1,
                           double* _A, double* _B, double* _C, double* _D, double* _E,
                           CvPoint* pt1, CvPoint* pt2 )
{
    double ang = angle*IPL_PI/180;
    double alpha = cos( ang );
    double beta = sin( ang );
    double alal = alpha*alpha;
    double bebe = beta*beta;
    double albe = alpha*beta;
    double a = 0, c = 0;
    double A = 0, B = 0, C = 0, D = 0, E = 0;
    double dx;
    int    code = 0;
    double cf_max = 0;
    /*double arcm; */
    /*int    oct1, oct2; */
    /*CvPoint ptm; */

    assert( mag > 0 && e >= 0 );

    if( arc0 > arc1 )
    {
        double temp = arc0;
        arc0 = arc1;
        arc1 = temp;
    }

    if( arc1 - arc0 > 360 )
    {
        arc0 = 0;
        arc1 = 360;
    }

    if( e != 1 ) /* non-parabolic case */
    {
        a = mag/fabs(e*e - 1);
        c = sqrt( mag*a );
        dx = a*e;
        a = 1./(a*a);
        c = 1./(c*c);
        D = -2*dx*a;
        if( e > 1 )
        {
            c = -c;
            D = -D;
        }
    }
    else
    {
        c = 1;
        dx = mag*0.5;
        D = -mag*2;
    }

    E = -beta*D;
    D *= alpha;

    /* rotate matrix */
    A = alal*a + bebe*c;
    B = albe*(c - a)*2;
    C = bebe*a + alal*c;

    /* move to (xc, yc) */
    D -= (2*A*xc + B*yc);
    E -= (B*xc + 2*C*yc);

    arc0 *= IPL_PI/180;
    arc1 *= IPL_PI/180;

    _atsCalcConicPoint( xc, yc, mag, e, alpha, beta, arc0, pt1 );
    if( pt1->x == -10000 ) code--;

    _atsCalcConicPoint( xc, yc, mag, e, alpha, beta, arc1, pt2 );
    if( pt2->x == -10000 ) code--;

    if( pt1->x == pt2->x && pt1->y == pt2->y )
    {
        if( arc1 - arc0 < 1.f ) code--;
    }

    if( fabs(A) > cf_max ) cf_max = fabs(A);
    if( fabs(B) > cf_max ) cf_max = fabs(B);
    if( fabs(C) > cf_max ) cf_max = fabs(C);
    if( fabs(D) > cf_max ) cf_max = fabs(D);
    if( fabs(E) > cf_max ) cf_max = fabs(E);

    cf_max = (1 << 20)/cf_max;

    *_A = A*cf_max;
    *_B = B*cf_max;
    *_C = C*cf_max;
    *_D = D*cf_max;
    *_E = E*cf_max;

    return code;
}


double atsCrossCorr( IplImage* imgA, IplImage* imgB, double deltaA, double deltaB )
{
    uchar* dataA;
    uchar* dataB;

    int stepA, stepB;
    CvSize sz, szB;
    int  depth = 0, ch = 0;
    int  depthB = 0, chB = 0;
    int  x, y;
    double sum = 0;
    
    atsGetImageInfo( imgA, (void**)&dataA, &stepA, &sz, &depth, &ch, 0 );
    atsGetImageInfo( imgB, (void**)&dataB, &stepB, &szB, &depthB, &chB, 0 );

    assert( sz.width == szB.width && sz.height == szB.height &&
            depth == depthB && ch == chB && ch == 1 );

    for( y = 0; y < sz.height; y++, dataA += stepA, dataB += stepB )
    {
        switch( depth )
        {
        case IPL_DEPTH_8U:
            for( x = 0; x < sz.width; x++ )
            {
                sum += (dataA[x] - deltaA)*(dataB[x] - deltaB );
            }
            break;
        case IPL_DEPTH_8S:
            for( x = 0; x < sz.width; x++ )
            {
                sum += (((char*)dataA)[x] - deltaA)*(((char*)dataB)[x] - deltaB );
            }
            break;
        case IPL_DEPTH_16S:
            for( x = 0; x < sz.width; x++ )
            {
                sum += (((short*)dataA)[x] - deltaA)*(((short*)dataB)[x] - deltaB );
            }
            break;
        case IPL_DEPTH_32F:
            for( x = 0; x < sz.width; x++ )
            {
                sum += (((float*)dataA)[x] - deltaA)*(((float*)dataB)[x] - deltaB );
            }
            break;
        default:
            assert(0);
            return -DBL_MAX;
        }
    }

    return sum;
}


void  atsClearBorder( IplImage* img )
{
    uchar* data = 0;
    int    i, step = 0;
    CvSize size;
    
    assert( img->depth == IPL_DEPTH_8U && img->nChannels == 1 );
    atsGetImageInfo( img, (void**)&data, &step, &size, 0, 0, 0 );
    
    /* clear bounds */
    for( i = 0; i < size.width; i++ )
        data[i] = data[(size.height-1)*step + i] = 0;

    for( i = 0; i < size.height; i++ )
        data[i*step] = data[i*step + size.width - 1] = 0;
}


void  atsGenerateBlobImage( IplImage* img, int min_blob_size, int max_blob_size,
                            int blob_count, int min_brightness, int max_brightness,
                            AtsRandState* rng_state )
{
    uchar* data;
    int    i, step;
    CvSize size;

    assert( img->depth == IPL_DEPTH_8U && img->nChannels == 1 );
    atsGetImageInfo( img, (void**)&data, &step, &size, 0, 0, 0 );
    iplSet( img, 0 );

    for( i = 0; i < blob_count; i++ )
    {
        CvPoint center;
        CvSize  axes;
        int angle = atsRandPlain32s( rng_state ) % 180;
        int brightness = atsRandPlain32s( rng_state ) %
                         (max_brightness - min_brightness) + min_brightness;
        center.x = atsRandPlain32s( rng_state ) % size.width;
        center.y = atsRandPlain32s( rng_state ) % size.height;
        axes.width = (atsRandPlain32s( rng_state ) %
                     (max_blob_size - min_blob_size) + min_blob_size + 1)/2;
        axes.height = (atsRandPlain32s( rng_state ) %
                      (max_blob_size - min_blob_size) + min_blob_size + 1)/2;
        
        cvEllipse( img, center, axes, angle, 0, 360, brightness, CV_FILLED ); 
    }
}


void  atsGetMoments( CvMoments* istate, AtsMomentState* astate )
{
    double inv_m00, s2, s3;

    astate->m00 = cvGetSpatialMoment( istate, 0, 0 );
    astate->m10 = cvGetSpatialMoment( istate, 1, 0 );
    astate->m01 = cvGetSpatialMoment( istate, 0, 1 );
    astate->m20 = cvGetSpatialMoment( istate, 2, 0 );
    astate->m11 = cvGetSpatialMoment( istate, 1, 1 );
    astate->m02 = cvGetSpatialMoment( istate, 0, 2 );
    astate->m30 = cvGetSpatialMoment( istate, 3, 0 );
    astate->m21 = cvGetSpatialMoment( istate, 2, 1 );
    astate->m12 = cvGetSpatialMoment( istate, 1, 2 );
    astate->m03 = cvGetSpatialMoment( istate, 0, 3 );

    astate->mu20 = cvGetCentralMoment( istate, 2, 0 );
    astate->mu11 = cvGetCentralMoment( istate, 1, 1 );
    astate->mu02 = cvGetCentralMoment( istate, 0, 2 );
    astate->mu30 = cvGetCentralMoment( istate, 3, 0 );
    astate->mu21 = cvGetCentralMoment( istate, 2, 1 );
    astate->mu12 = cvGetCentralMoment( istate, 1, 2 );
    astate->mu03 = cvGetCentralMoment( istate, 0, 3 );

    inv_m00 = astate->m00 == 0 ? 0 : 1./astate->m00;
    s2 = inv_m00*inv_m00;
    s3 = s2*sqrt(inv_m00);

    astate->nu20 = astate->mu20*s2;
    astate->nu11 = astate->mu11*s2;
    astate->nu02 = astate->mu02*s2;
    astate->nu30 = astate->mu30*s3;
    astate->nu21 = astate->mu21*s3;
    astate->nu12 = astate->mu12*s3;
    astate->nu03 = astate->mu03*s3;
}



/* Function Calculates separable symmetric kernels for Sobel and Gaussian operators */
void _atsCalcKer (char* Kernel,int order, int Size, int depth)
{
    /* Some Variables */
    
    int i,j;
    int oldsafe, newsafe;
    float oldval, newval;
    
    float* KerF = (float*)Kernel;
    
    
    if(depth!=IPL_DEPTH_32F)
    {
        int* KerI = (int*)Kernel;
        KerI[0] = 1;
        for(i = 1; i <= Size; i++)KerI[i] = 0;
        
        for(i = 0; i < Size-order-1; i++)
        {
            oldsafe = KerI[0];
            for(j = 1; j <= Size; j++)
            {
                newsafe = KerI[j]+KerI[j-1];
                KerI[j-1] = oldsafe;
                oldsafe = newsafe;
            }
        }
        for(i = 0; i < order; i++)
        {
            oldsafe = KerI[0];
            for(j = 1; j <= Size; j++)
            {
                newsafe = KerI[j]-KerI[j-1];
                KerI[j-1] = oldsafe;
                oldsafe = newsafe;
            }
        }
		if(Size==CV_SCHARR)
		{
			if(order==1)
			{
				KerI[0]=1;
				KerI[1]=0;
				KerI[2]=-1;
			}
			else if(order==0)
			{
				KerI[0]=KerI[2]=3;
				KerI[1]=10;
			}

		}
    }
    else
    {
        KerF[0] = 1;
        for(i = 1; i <= Size; i++)KerF[i] = 0;
        
        for(i = 0; i < Size-order-1; i++)
        {
            oldval = KerF[0];
            for(j = 1; j <= Size; j++)
            {
                newval = KerF[j]+KerF[j-1];
                KerF[j-1] = oldval;
                oldval = newval;
            }
        }
        for(i = 0; i < order; i++)
        {
            oldval = KerF[0];
            for(j = 1; j <= Size; j++)
            {
                newval = KerF[j]-KerF[j-1];
                KerF[j-1] = oldval;
                oldval = newval;
            }
        }
		if(Size==CV_SCHARR)
		{
			if(order==1)
			{
				KerF[0]=1;
				KerF[1]=0;
				KerF[2]=-1;
			}
			else if(order==0)
			{
				KerF[0]=KerF[2]=3;
				KerF[1]=10;
			}

		}
    }
    return;
}

void atsCalcKernel( int   datatype,
                    int   Xorder,
                    int   Yorder,
                    int   apertureSize,
                    char* KerX,
                    char* KerY,
                    CvSize* kerLens,
                    int origin)
{
    /* Some variables */
	int sizeX,sizeY,size;
	if(apertureSize == CV_SCHARR)
	{
		sizeX = 3;
		sizeY = 3;
		size = MAX(sizeX,sizeY);


		origin;

		_atsCalcKer(KerX,Xorder,CV_SCHARR,datatype);
		_atsCalcKer(KerY,Yorder,CV_SCHARR,datatype);
		kerLens->height = size;
		kerLens->width = size;

	}
	else
	{
		sizeX = (apertureSize>Xorder)?apertureSize:(((Xorder+1)/2)+3);
		sizeY = (apertureSize>Yorder)?apertureSize:(((Yorder+1)/2)+3);
		size = MAX(sizeX,sizeY);

		origin;

		_atsCalcKer(KerX,Xorder,size,datatype);
		_atsCalcKer(KerY,Yorder,size,datatype);

		kerLens->height = size;
		kerLens->width = size;
		
	}
	return ;
}



/*
   Create IplConvKernelFP for calclulating derivative
*/
IplConvKernelFP* atsCalcDervConvKernel( int Xorder, int Yorder, int apertureSize, int origin )
{
    float    horz[32], vert[32];
    float    values[1024];
    int      i, j, k;
    CvSize   kerSize;

    atsCalcKernel( 32, Xorder, Yorder, apertureSize,
                   (char*)horz, (char*)vert, &kerSize, origin );

    if( kerSize.width == 0 )
    {
        kerSize.width = 1;
        horz[0] = 1.f;
    }

    if( kerSize.height == 0 )
    {
        kerSize.height = 1;
        vert[0] = 1.f;
    }

    for( i = 0, k = 0; i < kerSize.height; i++ )
        for( j = 0; j < kerSize.width; j++, k++ )
        {
            values[k] = horz[j]*vert[i];
        }

    return iplCreateConvKernelFP( kerSize.width, kerSize.height,
                     kerSize.width/2, kerSize.height/2, values );
}


/* patch */
void* icvAlloc_( int lSize )
{
    long pPointer = (long)malloc( lSize + 64 + 4);
    
    if( pPointer == NULL ) return NULL;
    *(long*)(((pPointer + 32 + 4) & 0xffffffe0) - 4) = (long)pPointer;
    return (void*)((pPointer + 32 + 4) & 0xffffffe0);
} /* icvAlloc */


void  icvFree_( void** ppPointer )
{
    void* pPointer;
    
    /* Checking for bad pointer */
    if( ppPointer && *ppPointer )
    {
        pPointer = *ppPointer;
        *ppPointer = 0;

        /* Pointer must be align by 32 */
        assert( ((long)pPointer & 0x1f) == 0 );
    
        free( (void*)*(long*)((long)pPointer - 4) );
    }
}


CvPoint  atsFindFirstErr( IplImage* imgA, IplImage* imgB, double eps )
{
    uchar* imgA_data = 0;
    uchar* imgB_data = 0;
    int imgA_step = 0;
    int imgB_step = 0;
    CvSize imgA_size;
    CvSize imgB_size;
    int x = 0, y = 0;

    cvGetImageRawData( imgA, &imgA_data, &imgA_step, &imgA_size );
    cvGetImageRawData( imgB, &imgB_data, &imgB_step, &imgB_size );

    assert( imgA_size.width == imgB_size.width && imgA_size.height == imgB_size.height );
    assert( imgA->depth == imgB->depth && imgA->nChannels == imgB->nChannels );

    imgA_size.width *= imgA->nChannels;

    for( y = 0; y < imgA_size.height; y++, imgA_data += imgA_step, imgB_data += imgB_step )
    {
        switch( imgA->depth )
        {
        case IPL_DEPTH_8U:
            for( x = 0; x < imgA_size.width; x++ )
            {
                int t = imgA_data[x] - imgB_data[x];
                if( abs(t) > eps )
                    goto exit_func;
            }
            break;
        case IPL_DEPTH_8S:
            for( x = 0; x < imgA_size.width; x++ )
            {
                int t = ((char*)imgA_data)[x] - ((char*)imgB_data)[x];
                if( abs(t) > eps )
                    goto exit_func;
            }
            break;
        case IPL_DEPTH_16S:
            for( x = 0; x < imgA_size.width; x++ )
            {
                int t = ((short*)imgA_data)[x] - ((short*)imgB_data)[x];
                if( abs(t) > eps )
                    goto exit_func;
            }
            break;
        case IPL_DEPTH_32S:
            for( x = 0; x < imgA_size.width; x++ )
            {
                int t = ((int*)imgA_data)[x] - ((int*)imgB_data)[x];
                if( abs(t) > eps )
                    goto exit_func;
            }
            break;
        case IPL_DEPTH_32F:
            for( x = 0; x < imgA_size.width; x++ )
            {
                float t = ((float*)imgA_data)[x] - ((float*)imgB_data)[x];
                if( fabs(t) > eps )
                    goto exit_func;
            }
            break;
        default:
            assert(0);
        }
    }

exit_func:

    return x < imgA_size.width && y < imgA_size.height ?
           cvPoint( x / imgA->nChannels, y ) : cvPoint( -1, -1 );
}


void atsScaleAddImage( IplImage* src, IplImage* dst, double scale, double shift )
{
    char*  src_data = 0;
    char*  dst_data = 0;
    int    src_step = 0, dst_step = 0;
    CvSize sz, sz2;
    int    x, y;

    assert( dst->depth == IPL_DEPTH_32F );
    assert( src->nChannels == dst->nChannels );

    if( src->depth != IPL_DEPTH_32F )
    {
        atsConvert( src, dst );
        src = dst;
    }

    atsGetImageInfo( src, (void**)&src_data, &src_step, &sz, 0, 0, 0 );
    atsGetImageInfo( dst, (void**)&dst_data, &dst_step, &sz2, 0, 0, 0 );

    assert( sz.width == sz2.width && sz.height == sz2.height );

    sz.width *= src->nChannels;

    for( y = 0; y < sz.height; y++, src += src_step, dst += dst_step )
    {
        for( x = 0; x < sz.width; x++ )
        {
            ((float*)dst_data)[x] = (float)(((float*)src_data)[x]*scale + shift);
        }
    }
}

void atsScaleAddAbsImage( IplImage* src, IplImage* dst, double scale, double shift )
{
    char*  src_data = 0;
    char*  dst_data = 0;
    int    src_step = 0, dst_step = 0;
    CvSize sz, sz2;
    int    x, y;

    assert( dst->depth == IPL_DEPTH_32F );
    assert( src->nChannels == dst->nChannels );

    if( src->depth != IPL_DEPTH_32F )
    {
        atsConvert( src, dst );
        src = dst;
    }

    atsGetImageInfo( src, (void**)&src_data, &src_step, &sz, 0, 0, 0 );
    atsGetImageInfo( dst, (void**)&dst_data, &dst_step, &sz2, 0, 0, 0 );

    assert( sz.width == sz2.width && sz.height == sz2.height );

    sz.width *= src->nChannels;

    for( y = 0; y < sz.height; y++, src_data += src_step, dst_data += dst_step )
    {
        for( x = 0; x < sz.width; x++ )
        {
            ((float*)dst_data)[x] = (float)fabs((scale*((float*)src_data)[x] + shift));
        }
    }
}


CvPoint atsRandPoint( AtsRandState* rng_state, CvSize size )
{
    CvPoint pt;

    pt.x = atsRandPlain32s( rng_state ) % size.width;
    pt.y = atsRandPlain32s( rng_state ) % size.height;

    return pt;
}


CvPoint2D32f atsRandPoint2D32f( AtsRandState* rng_state, CvSize size )
{
    CvPoint2D32f pt;

    pt.x = (float)(atsRandPlain32s( rng_state ) % size.width);
    pt.y = (float)(atsRandPlain32s( rng_state ) % size.height);

    return pt;
}

/* general-purpose saturation macros */ 
#define ATS_CAST_8U(t)    (uchar)( !((t) & ~255) ? (t) : (t) > 0 ? 255 : 0)
#define ATS_CAST_8S(t)    (char)( !(((t)+128) & ~255) ? (t) : (t) > 0 ? 127 : -128 )
#define ATS_CAST_16S(t)   (short)( !(((t)+32768) & ~65535) ? (t) : (t) > 0 ? 32767 : -32768 )
#define ATS_CAST_32S(t)   (int)(t)
#define ATS_CAST_64S(t)   (int64)(t)
#define ATS_CAST_32F(t)   (float)(t)
#define ATS_CAST_64F(t)   (double)(t)

void atsLinearFunc( const CvArr* src1arr, CvScalar alpha,
                    const CvArr* src2arr, CvScalar beta,
                    CvScalar gamma, CvArr* dstarr )
{
    CvMat stub1, *src1;
    CvMat stub, *dst;
    int coi1 = 0, coi = 0;
    int x, y, c;
    int height, width_cn;
    int depth, channels;
    uchar *dstptr, *src1ptr;

    if( !src1arr )
    {
        if( !src2arr )
        {
            cvSet( dstarr, gamma );
            return;
        }

        src1arr = src2arr;
        src2arr = 0;
    }

    dst = cvGetMat( dstarr, &stub, &coi );
    src1 = cvGetMat( src1arr, &stub1, &coi1 );
    assert( coi1 == 0 && coi == 0 );
    assert( CV_ARR_TYPE(src1->type) == CV_ARR_TYPE(dst->type));
    assert( src1->width == dst->width && src1->height == dst->height );

    depth = CV_ARR_DEPTH( dst->type );
    channels = CV_ARR_CN( dst->type );

    height = dst->height;
    width_cn = dst->width * channels;

    dstptr = dst->data.ptr;
    src1ptr = src1->data.ptr;

    if( !src2arr )
    {
        switch( depth )
        {
        case CV_8U:
            for( y = 0; y < height; y++, dstptr += dst->step, src1ptr += src1->step )
                for( x = 0; x < width_cn; x += channels )
                    for( c = 0; c < channels; c++ )
                    {
                        int t = cvRound( ((uchar*)src1ptr)[x + c]*alpha.val[c] + gamma.val[c] );
                        ((uchar*)dstptr)[x + c] = ATS_CAST_8U(t);
                    }
            break;
        case CV_8S:
            for( y = 0; y < height; y++, dstptr += dst->step, src1ptr += src1->step )
                for( x = 0; x < width_cn; x += channels )
                    for( c = 0; c < channels; c++ )
                    {
                        int t = cvRound( ((char*)src1ptr)[x + c]*alpha.val[c] + gamma.val[c] );
                        ((char*)dstptr)[x + c] = ATS_CAST_8S(t);
                    }
            break;
        case CV_16S:
            for( y = 0; y < height; y++, dstptr += dst->step, src1ptr += src1->step )
                for( x = 0; x < width_cn; x += channels )
                    for( c = 0; c < channels; c++ )
                    {
                        int t = cvRound( ((short*)src1ptr)[x + c]*alpha.val[c] + gamma.val[c] );
                        ((short*)dstptr)[x + c] = ATS_CAST_16S(t);
                    }
            break;
        case CV_32S:
            for( y = 0; y < height; y++, dstptr += dst->step, src1ptr += src1->step )
                for( x = 0; x < width_cn; x += channels )
                    for( c = 0; c < channels; c++ )
                    {
                        int t = cvRound( ((int*)src1ptr)[x + c]*alpha.val[c] + gamma.val[c] );
                        ((int*)dstptr)[x + c] = t;
                    }
            break;
        case CV_32F:
            for( y = 0; y < height; y++, dstptr += dst->step, src1ptr += src1->step )
                for( x = 0; x < width_cn; x += channels )
                    for( c = 0; c < channels; c++ )
                    {
                        double t = ((float*)src1ptr)[x + c]*alpha.val[c] + gamma.val[c];
                        ((float*)dstptr)[x + c] = ATS_CAST_32F(t);
                    }
            break;
        case CV_64F:
            for( y = 0; y < height; y++, dstptr += dst->step, src1ptr += src1->step )
                for( x = 0; x < width_cn; x += channels )
                    for( c = 0; c < channels; c++ )
                    {
                        double t = ((double*)src1ptr)[x + c]*alpha.val[c] + gamma.val[c];
                        ((double*)dstptr)[x + c] = ATS_CAST_64F(t);
                    }
            break;
        default:
            assert(0);
            return;
        }
    }
    else
    {
        CvMat stub2, *src2;
        int coi2 = 0;
        uchar* src2ptr;

        src2 = cvGetMat( src2arr, &stub2, &coi2 );
        assert( coi2 == 0 );
        assert( CV_ARR_TYPE(src2->type) == CV_ARR_TYPE(dst->type));
        assert( src2->width == dst->width && src2->height == dst->height );

        src2ptr = src2->data.ptr;

        switch( depth )
        {
        case CV_8U:
            for( y = 0; y < height; y++, dstptr += dst->step,
                                         src1ptr += src1->step,
                                         src2ptr += src2->step )
                for( x = 0; x < width_cn; x += channels )
                    for( c = 0; c < channels; c++ )
                    {
                        int t = cvRound( ((uchar*)src1ptr)[x + c]*alpha.val[c] +
                                         ((uchar*)src2ptr)[x + c]*beta.val[c] +
                                         gamma.val[c] );
                        ((uchar*)dstptr)[x + c] = ATS_CAST_8U(t);
                    }
            break;
        case CV_8S:
            for( y = 0; y < height; y++, dstptr += dst->step,
                                         src1ptr += src1->step,
                                         src2ptr += src2->step )
                for( x = 0; x < width_cn; x += channels )
                    for( c = 0; c < channels; c++ )
                    {
                        int t = cvRound( ((char*)src1ptr)[x + c]*alpha.val[c] +
                                         ((char*)src2ptr)[x + c]*beta.val[c] +
                                         gamma.val[c] );
                        ((char*)dstptr)[x + c] = ATS_CAST_8S(t);
                    }
            break;
        case CV_16S:
            for( y = 0; y < height; y++, dstptr += dst->step,
                                         src1ptr += src1->step,
                                         src2ptr += src2->step )
                for( x = 0; x < width_cn; x += channels )
                    for( c = 0; c < channels; c++ )
                    {
                        int t = cvRound( ((short*)src1ptr)[x + c]*alpha.val[c] +
                                         ((short*)src2ptr)[x + c]*beta.val[c] +
                                         gamma.val[c] );
                        ((short*)dstptr)[x + c] = ATS_CAST_16S(t);
                    }
            break;
        case CV_32S:
            for( y = 0; y < height; y++, dstptr += dst->step,
                                         src1ptr += src1->step,
                                         src2ptr += src2->step )
                for( x = 0; x < width_cn; x += channels )
                    for( c = 0; c < channels; c++ )
                    {
                        int t = cvRound( ((int*)src1ptr)[x + c]*alpha.val[c] +
                                         ((int*)src2ptr)[x + c]*beta.val[c] +
                                         gamma.val[c] );
                        ((int*)dstptr)[x + c] = t;
                    }
            break;
        case CV_32F:
            for( y = 0; y < height; y++, dstptr += dst->step,
                                         src1ptr += src1->step,
                                         src2ptr += src2->step )
                for( x = 0; x < width_cn; x += channels )
                    for( c = 0; c < channels; c++ )
                    {
                        double t = ((float*)src1ptr)[x + c]*alpha.val[c] +
                                   ((float*)src2ptr)[x + c]*beta.val[c] +
                                   gamma.val[c];
                        ((float*)dstptr)[x + c] = ATS_CAST_32F(t);
                    }
            break;
        case CV_64F:
            for( y = 0; y < height; y++, dstptr += dst->step,
                                         src1ptr += src1->step,
                                         src2ptr += src2->step )
                for( x = 0; x < width_cn; x += channels )
                    for( c = 0; c < channels; c++ )
                    {
                        double t = ((double*)src1ptr)[x + c]*alpha.val[c] +
                                   ((double*)src2ptr)[x + c]*beta.val[c] +
                                   gamma.val[c];
                        ((double*)dstptr)[x + c] = ATS_CAST_64F(t);
                    }
            break;
        default:
            assert(0);
            return;
        }
    }
}


void atsMul( const CvArr* src1arr, const CvArr* src2arr, CvArr* dstarr )
{
    CvMat stub1, *src1;
    CvMat stub2, *src2;
    CvMat stub, *dst;
    int coi1 = 0, coi2 = 0, coi = 0;
    int x, y;
    int height, width_cn;
    int depth, channels;
    uchar *dstptr, *src1ptr, *src2ptr;

    dst = cvGetMat( dstarr, &stub, &coi );
    src1 = cvGetMat( src1arr, &stub1, &coi1 );
    src2 = cvGetMat( src2arr, &stub2, &coi2 );
    assert( coi1 == 0 && coi2 == 0 && coi == 0 );
    assert( CV_ARR_TYPE(src1->type) == CV_ARR_TYPE(dst->type));
    assert( src1->width == dst->width && src1->height == dst->height );
    assert( CV_ARR_TYPE(src2->type) == CV_ARR_TYPE(dst->type));
    assert( src2->width == dst->width && src2->height == dst->height );

    depth = CV_ARR_DEPTH( dst->type );
    channels = CV_ARR_CN( dst->type );

    height = dst->height;
    width_cn = dst->width * channels;

    dstptr = dst->data.ptr;
    src1ptr = src1->data.ptr;
    src2ptr = src2->data.ptr;

    switch( depth )
    {
    case CV_8U:
        for( y = 0; y < height; y++, dstptr += dst->step,
                                     src1ptr += src1->step,
                                     src2ptr += src2->step )
            for( x = 0; x < width_cn; x++ )
            {
                int t = ((uchar*)src1ptr)[x]*((uchar*)src2ptr)[x];
                ((uchar*)dstptr)[x] = ATS_CAST_8U(t);
            }
        break;
    case CV_8S:
        for( y = 0; y < height; y++, dstptr += dst->step,
                                     src1ptr += src1->step,
                                     src2ptr += src2->step )
            for( x = 0; x < width_cn; x++ )
            {
                int t = ((char*)src1ptr)[x]*((char*)src2ptr)[x];
                ((char*)dstptr)[x] = ATS_CAST_8S(t);
            }
        break;
    case CV_16S:
        for( y = 0; y < height; y++, dstptr += dst->step,
                                     src1ptr += src1->step,
                                     src2ptr += src2->step )
            for( x = 0; x < width_cn; x++ )
            {
                int t = ((short*)src1ptr)[x]*((short*)src2ptr)[x];
                ((short*)dstptr)[x] = ATS_CAST_16S(t);
            }
        break;
    case CV_32S:
        for( y = 0; y < height; y++, dstptr += dst->step,
                                     src1ptr += src1->step,
                                     src2ptr += src2->step )
            for( x = 0; x < width_cn; x++ )
            {
                int t = ((int*)src1ptr)[x]*((int*)src2ptr)[x];
                ((int*)dstptr)[x] = ATS_CAST_32S(t);
            }
        break;
    case CV_32F:
        for( y = 0; y < height; y++, dstptr += dst->step,
                                     src1ptr += src1->step,
                                     src2ptr += src2->step )
            for( x = 0; x < width_cn; x++ )
            {
                float t = ((float*)src1ptr)[x]*((float*)src2ptr)[x];
                ((float*)dstptr)[x] = ATS_CAST_32F(t);
            }
        break;
    case CV_64F:
        for( y = 0; y < height; y++, dstptr += dst->step,
                                     src1ptr += src1->step,
                                     src2ptr += src2->step )
            for( x = 0; x < width_cn; x++ )
            {
                double t = ((double*)src1ptr)[x]*((double*)src2ptr)[x];
                ((double*)dstptr)[x] = ATS_CAST_64F(t);
            }
        break;
    default:
        assert(0);
        return;
    }
}


#define ATS_LOGIC_AND  0
#define ATS_LOGIC_OR   1
#define ATS_LOGIC_XOR  2

void atsLogic( const CvArr* src1arr, const CvArr* src2arr, CvArr* dstarr, int op )
{
    CvMat stub1, *src1;
    CvMat stub2, *src2;
    CvMat stub, *dst;
    int coi1 = 0, coi2 = 0, coi = 0;
    int x, y;
    int height, width_cn;
    int pix_size;
    uchar *dstptr, *src1ptr, *src2ptr;

    dst = cvGetMat( dstarr, &stub, &coi );
    src1 = cvGetMat( src1arr, &stub1, &coi1 );
    src2 = cvGetMat( src2arr, &stub2, &coi2 );
    assert( coi1 == 0 && coi2 == 0 && coi == 0 );
    assert( CV_ARR_TYPE(src1->type) == CV_ARR_TYPE(dst->type));
    assert( src1->width == dst->width && src1->height == dst->height );
    assert( CV_ARR_TYPE(src2->type) == CV_ARR_TYPE(dst->type));
    assert( src2->width == dst->width && src2->height == dst->height );

    height = dst->height;
    pix_size = cvPixSize( dst->type );
    width_cn = dst->width * pix_size;

    dstptr = dst->data.ptr;
    src1ptr = src1->data.ptr;
    src2ptr = src2->data.ptr;

    switch( op )
    {
    case ATS_LOGIC_AND:
        for( y = 0; y < height; y++, dstptr += dst->step,
                                     src1ptr += src1->step,
                                     src2ptr += src2->step )
            for( x = 0; x < width_cn; x++ )
            {
                int t = ((uchar*)src1ptr)[x] & ((uchar*)src2ptr)[x];
                ((uchar*)dstptr)[x] = (uchar)t;
            }
        break;
    case ATS_LOGIC_OR:
        for( y = 0; y < height; y++, dstptr += dst->step,
                                     src1ptr += src1->step,
                                     src2ptr += src2->step )
            for( x = 0; x < width_cn; x++ )
            {
                int t = ((uchar*)src1ptr)[x] | ((uchar*)src2ptr)[x];
                ((uchar*)dstptr)[x] = (uchar)t;
            }
        break;
    case ATS_LOGIC_XOR:
        for( y = 0; y < height; y++, dstptr += dst->step,
                                     src1ptr += src1->step,
                                     src2ptr += src2->step )
            for( x = 0; x < width_cn; x++ )
            {
                int t = ((uchar*)src1ptr)[x] ^ ((uchar*)src2ptr)[x];
                ((uchar*)dstptr)[x] = (uchar)t;
            }
        break;
    default:
        assert(0);
    }
}



void atsLogicS( const CvArr* src1arr, CvScalar scalar, CvArr* dstarr, int op )
{
    double buf[4];
    CvMat stub1, *src1;
    CvMat stub2, *src2 = &stub2;
    CvMat stub, *dst;
    int coi1 = 0, coi = 0;
    int x, y, c;
    int height, width_cn;
    int pix_size;
    uchar *dstptr, *src1ptr, *src2ptr;

    dst = cvGetMat( dstarr, &stub, &coi );
    src1 = cvGetMat( src1arr, &stub1, &coi1 );
    assert( coi1 == 0 && coi == 0 );
    assert( CV_ARR_TYPE(src1->type) == CV_ARR_TYPE(dst->type));
    assert( src1->width == dst->width && src1->height == dst->height );

    height = dst->height;
    pix_size = cvPixSize( dst->type );
    width_cn = dst->width * pix_size;

    dstptr = dst->data.ptr;
    src1ptr = src1->data.ptr;
    
    cvInitMatHeader( src2, 1, 1, dst->type, buf );
    cvSetAt( src2, scalar, 0, 0 );
    src2ptr = src2->data.ptr;

    switch( op )
    {
    case ATS_LOGIC_AND:
        for( y = 0; y < height; y++, dstptr += dst->step,
                                     src1ptr += src1->step,
                                     src2ptr += src2->step )
            for( x = 0; x < width_cn; x += pix_size )
                for( c = 0; c < pix_size; c++ )
                {
                    int t = ((uchar*)src1ptr)[x + c] & ((uchar*)src2ptr)[c];
                    ((uchar*)dstptr)[x + c] = (uchar)t;
                }
        break;
    case ATS_LOGIC_OR:
        for( y = 0; y < height; y++, dstptr += dst->step,
                                     src1ptr += src1->step,
                                     src2ptr += src2->step )
            for( x = 0; x < width_cn; x += pix_size )
                for( c = 0; c < pix_size; c++ )
                {
                    int t = ((uchar*)src1ptr)[x + c] | ((uchar*)src2ptr)[c];
                    ((uchar*)dstptr)[x + c] = (uchar)t;
                }
        break;
    case ATS_LOGIC_XOR:
        for( y = 0; y < height; y++, dstptr += dst->step,
                                     src1ptr += src1->step,
                                     src2ptr += src2->step )
            for( x = 0; x < width_cn; x += pix_size )
                for( c = 0; c < pix_size; c++ )
                {
                    int t = ((uchar*)src1ptr)[x + c] ^ ((uchar*)src2ptr)[c];
                    ((uchar*)dstptr)[x + c] = (uchar)t;
                }
        break;
    default:
        assert(0);
    }
}


/* End of file. */
