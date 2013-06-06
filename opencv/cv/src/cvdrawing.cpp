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
#include <limits.h>
#include "_cvwrap.h"
#include "_cvdatastructs.h"

#define  XY_SHIFT  16
#define  XY_ONE    (1 << XY_SHIFT)

typedef struct CvPolyEdge
{
    int x, dx;
    union
    {
        struct CvPolyEdge *next;
        int y0;
    };
    int y1;
}
CvPolyEdge;

static void
icvCollectPolyEdges( CvMat* img, CvSeq* v, CvContour* edges, const void* color );

static void
icvFillEdgeCollection( CvMat* img, CvContour* edges, const void* color );

static void
icvPolyLineAA( CvMat* img, CvPoint *v, int count, int closed,
               int scale, const void* color );

static void
icvPolyLine( CvMat* img, CvPoint *v, int count, int closed,
             int thickness, const void* color, int connectivity = 8 );

static void
icvFillConvexPoly( CvMat* img, CvPoint* v,
                   int npts, const void* color );

/****************************************************************************************\
*                                   Lines                                                *
\****************************************************************************************/

int icvClipLine( int right, int bottom, CvPoint* pt1, CvPoint* pt2 )
{
    int x1 = pt1->x, y1 = pt1->y, x2 = pt2->x, y2 = pt2->y;
    int c1 = (x1 < 0) + (x1 > right) * 2 + (y1 < 0) * 4 + (y1 > bottom) * 8;
    int c2 = (x2 < 0) + (x2 > right) * 2 + (y2 < 0) * 4 + (y2 > bottom) * 8;

    if( (c1 & c2) == 0 && (c1 | c2) != 0 )
    {
        int a;

        if( c1 & 12 )
        {
            a = c1 < 8 ? 0 : bottom;
            x1 += (int) (((int64) (a - y1)) * (x2 - x1) / (y2 - y1));
            y1 = a;
            c1 = (x1 < 0) + (x1 > right) * 2;
        }
        if( c2 & 12 )
        {
            a = c2 < 8 ? 0 : bottom;
            x2 += (int) (((int64) (a - y2)) * (x2 - x1) / (y2 - y1));
            y2 = a;
            c2 = (x2 < 0) + (x2 > right) * 2;
        }
        if( (c1 & c2) == 0 && (c1 | c2) != 0 )
        {
            if( c1 )
            {
                a = c1 == 1 ? 0 : right;
                y1 += (int) (((int64) (a - x1)) * (y2 - y1) / (x2 - x1));
                x1 = a;
                c1 = 0;
            }
            if( c2 )
            {
                a = c2 == 1 ? 0 : right;
                y2 += (int) (((int64) (a - x2)) * (y2 - y1) / (x2 - x1));
                x2 = a;
                c2 = 0;
            }
        }

        assert( (c1 & c2) != 0 || (x1 | y1 | x2 | y2) >= 0 );

        pt1->x = x1;
        pt1->y = y1;
        pt2->x = x2;
        pt2->y = y2;
    }

    return ( c1 | c2 ) == 0;
}

static void
icvLine( CvMat* mat, CvPoint pt1, CvPoint pt2,
         const void* color, int connectivity = 8 )
{
    if( icvClipLine( mat->width - 1, mat->height - 1, &pt1, &pt2 ))
    {
        CvLineIterator iterator;
        int i, count = icvInitLineIterator( mat, pt1, pt2, &iterator, connectivity, 1 );
        int pix_size = icvPixSize[CV_ARR_TYPE(mat->type)];

        for( i = 0; i < count; i++ )
        {
            memcpy( iterator.ptr, color, pix_size );
            CV_NEXT_LINE_POINT( iterator );
        }
    }
}


/* Correction table depended on slope */
static const uchar icvSlopeCorrTable[] = {
    181, 181, 181, 182, 182, 183, 184, 185, 187, 188, 190, 192, 194, 196, 198, 201,
    203, 206, 209, 211, 214, 218, 221, 224, 227, 231, 235, 238, 242, 246, 250, 254
};

/* Gaussian for antialiasing filter */
static const int icvFilterTable[] = {
    168, 177, 185, 194, 202, 210, 218, 224, 231, 236, 241, 246, 249, 252, 254, 254,
    254, 254, 252, 249, 246, 241, 236, 231, 224, 218, 210, 202, 194, 185, 177, 168,
    158, 149, 140, 131, 122, 114, 105, 97, 89, 82, 75, 68, 62, 56, 50, 45,
    40, 36, 32, 28, 25, 22, 19, 16, 14, 12, 11, 9, 8, 7, 5, 5
};


static void
icvLineAA( CvMat* img, CvPoint pt1, CvPoint pt2,
           const void* color )
{
    int dx, dy;
    int ecount, scount = 0;
    int slope;
    int ax, ay;
    int x_step, y_step;
    int i, j;
    int ep_table[9];
    int cb = ((uchar*)color)[0], cg = ((uchar*)color)[1], cr = ((uchar*)color)[2];
    int _cb, _cg, _cr;
    int nch = CV_ARR_CN( img->type );
    uchar* ptr = (uchar*)(img->data.ptr);
    int step = img->step;
    CvSize size = icvGetMatSize( img );

    assert( img && (nch == 1 || nch == 3) && CV_ARR_DEPTH(img->type) == CV_8U );

    size.width <<= XY_SHIFT;
    size.height <<= XY_SHIFT;

    if( !icvClipLine( size.width - XY_ONE, size.height - XY_ONE, &pt1, &pt2 ))
        return;

    dx = pt2.x - pt1.x;
    dy = pt2.y - pt1.y;

    j = dx < 0 ? -1 : 0;
    ax = (dx ^ j) - j;
    i = dy < 0 ? -1 : 0;
    ay = (dy ^ i) - i;

    if( ax > ay )
    {
        dx = ax;
        dy = (dy ^ j) - j;
        pt1.x ^= pt2.x & j;
        pt2.x ^= pt1.x & j;
        pt1.x ^= pt2.x & j;
        pt1.y ^= pt2.y & j;
        pt2.y ^= pt1.y & j;
        pt1.y ^= pt2.y & j;

        x_step = XY_ONE;
        y_step = (int) (((int64) dy << XY_SHIFT) / (ax | 1));
        pt2.x += XY_ONE;
        ecount = (pt2.x >> XY_SHIFT) - (pt1.x >> XY_SHIFT);
        j = -(pt1.x & (XY_ONE - 1));
        pt1.y += (int) ((((int64) y_step) * j) >> XY_SHIFT) + (XY_ONE >> 1);
        slope = (y_step >> (XY_SHIFT - 5)) & 0x3f;
        slope ^= (y_step < 0 ? 0x3f : 0);

        /* Get 4-bit fractions for end-point adjustments */
        i = (pt1.x >> (XY_SHIFT - 7)) & 0x78;
        j = (pt2.x >> (XY_SHIFT - 7)) & 0x78;
    }
    else
    {
        dy = ay;
        dx = (dx ^ i) - i;
        pt1.x ^= pt2.x & i;
        pt2.x ^= pt1.x & i;
        pt1.x ^= pt2.x & i;
        pt1.y ^= pt2.y & i;
        pt2.y ^= pt1.y & i;
        pt1.y ^= pt2.y & i;

        x_step = (int) (((int64) dx << XY_SHIFT) / (ay | 1));
        y_step = XY_ONE;
        pt2.y += XY_ONE;
        ecount = (pt2.y >> XY_SHIFT) - (pt1.y >> XY_SHIFT);
        j = -(pt1.y & (XY_ONE - 1));
        pt1.x += (int) ((((int64) x_step) * j) >> XY_SHIFT) + (XY_ONE >> 1);
        slope = (x_step >> (XY_SHIFT - 5)) & 0x3f;
        slope ^= (x_step < 0 ? 0x3f : 0);

        /* Get 4-bit fractions for end-point adjustments */
        i = (pt1.y >> (XY_SHIFT - 7)) & 0x78;
        j = (pt2.y >> (XY_SHIFT - 7)) & 0x78;
    }

    slope = (slope & 0x20) ? 0x100 : icvSlopeCorrTable[slope];

    /* Calc end point correction table */
    {
        int t0 = slope << 7;
        int t1 = ((0x78 - i) | 4) * slope;
        int t2 = (j | 4) * slope;

        ep_table[0] = 0;
        ep_table[8] = slope;
        ep_table[1] = ep_table[3] = ((((j - i) & 0x78) | 4) * slope >> 8) & 0x1ff;
        ep_table[2] = (t1 >> 8) & 0x1ff;
        ep_table[4] = ((((j - i) + 0x80) | 4) * slope >> 8) & 0x1ff;
        ep_table[5] = ((t1 + t0) >> 8) & 0x1ff;
        ep_table[6] = (t2 >> 8) & 0x1ff;
        ep_table[7] = ((t2 + t0) >> 8) & 0x1ff;
    }

    if( nch == 3 )
    {
        #define  ICV_PUT_POINT()            \
        {                                   \
            _cb = tptr[0];                  \
            _cb += (cb - _cb)*a >> 8;       \
            _cg = tptr[1];                  \
            _cg += (cg - _cg)*a >> 8;       \
            _cr = tptr[2];                  \
            _cr += (cr - _cr)*a >> 8;       \
            tptr[0] = (uchar)_cb;           \
            tptr[1] = (uchar)_cg;           \
            tptr[2] = (uchar)_cr;           \
        }
        if( ax > ay )
        {
            ptr += (pt1.x >> XY_SHIFT) * 3;

            while( ecount >= 0 )
            {
                uchar *tptr = ptr + ((pt1.y >> XY_SHIFT) - 1) * step;

                int ep_corr = ep_table[(((scount >= 2) + 1) & (scount | 2)) * 3 +
                                       (((ecount >= 2) + 1) & (ecount | 2))];
                int a, dist = (pt1.y >> (XY_SHIFT - 5)) & 31;

                a = (ep_corr * icvFilterTable[dist + 32] >> 8) & 0xff;
                ICV_PUT_POINT();

                tptr += step;
                a = (ep_corr * icvFilterTable[dist] >> 8) & 0xff;
                ICV_PUT_POINT();

                tptr += step;
                a = (ep_corr * icvFilterTable[63 - dist] >> 8) & 0xff;
                ICV_PUT_POINT();

                pt1.y += y_step;
                ptr += 3;
                scount++;
                ecount--;
            }
        }
        else
        {
            ptr += (pt1.y >> XY_SHIFT) * step;

            while( ecount >= 0 )
            {
                uchar *tptr = ptr + ((pt1.x >> XY_SHIFT) - 1) * 3;

                int ep_corr = ep_table[(((scount >= 2) + 1) & (scount | 2)) * 3 +
                                       (((ecount >= 2) + 1) & (ecount | 2))];
                int a, dist = (pt1.x >> (XY_SHIFT - 5)) & 31;

                a = (ep_corr * icvFilterTable[dist + 32] >> 8) & 0xff;
                ICV_PUT_POINT();

                tptr += 3;
                a = (ep_corr * icvFilterTable[dist] >> 8) & 0xff;
                ICV_PUT_POINT();

                tptr += 3;
                a = (ep_corr * icvFilterTable[63 - dist] >> 8) & 0xff;
                ICV_PUT_POINT();

                pt1.x += x_step;
                ptr += step;
                scount++;
                ecount--;
            }
        }
#undef ICV_PUT_POINT
    }
    else
    {
#define  ICV_PUT_POINT()       \
        {                                \
            _cb = tptr[0];               \
            _cb += (cb - _cb)*a >> 8;    \
            tptr[0] = (uchar)_cb;        \
        }

        if( ax > ay )
        {
            ptr += (pt1.x >> XY_SHIFT);

            while( ecount >= 0 )
            {
                uchar *tptr = ptr + ((pt1.y >> XY_SHIFT) - 1) * step;

                int ep_corr = ep_table[(((scount >= 2) + 1) & (scount | 2)) * 3 +
                                       (((ecount >= 2) + 1) & (ecount | 2))];
                int a, dist = (pt1.y >> (XY_SHIFT - 5)) & 31;

                a = (ep_corr * icvFilterTable[dist + 32] >> 8) & 0xff;
                ICV_PUT_POINT();

                tptr += step;
                a = (ep_corr * icvFilterTable[dist] >> 8) & 0xff;
                ICV_PUT_POINT();

                tptr += step;
                a = (ep_corr * icvFilterTable[63 - dist] >> 8) & 0xff;
                ICV_PUT_POINT();

                pt1.y += y_step;
                ptr++;
                scount++;
                ecount--;
            }
        }
        else
        {
            ptr += (pt1.y >> XY_SHIFT) * step;

            while( ecount >= 0 )
            {
                uchar *tptr = ptr + ((pt1.x >> XY_SHIFT) - 1);

                int ep_corr = ep_table[(((scount >= 2) + 1) & (scount | 2)) * 3 +
                                       (((ecount >= 2) + 1) & (ecount | 2))];
                int a, dist = (pt1.x >> (XY_SHIFT - 5)) & 31;

                a = (ep_corr * icvFilterTable[dist + 32] >> 8) & 0xff;
                ICV_PUT_POINT();

                tptr++;
                a = (ep_corr * icvFilterTable[dist] >> 8) & 0xff;
                ICV_PUT_POINT();

                tptr++;
                a = (ep_corr * icvFilterTable[63 - dist] >> 8) & 0xff;
                ICV_PUT_POINT();

                pt1.x += x_step;
                ptr += step;
                scount++;
                ecount--;
            }
        }
#undef ICV_PUT_POINT
    }
}


/****************************************************************************************\
*                   Antialiazed Elliptic Arcs through Antialiazed Lines                  *
\****************************************************************************************/

static const float icvSinTable[] =
    { 0.0000000f, 0.0174524f, 0.0348995f, 0.0523360f, 0.0697565f, 0.0871557f,
    0.1045285f, 0.1218693f, 0.1391731f, 0.1564345f, 0.1736482f, 0.1908090f,
    0.2079117f, 0.2249511f, 0.2419219f, 0.2588190f, 0.2756374f, 0.2923717f,
    0.3090170f, 0.3255682f, 0.3420201f, 0.3583679f, 0.3746066f, 0.3907311f,
    0.4067366f, 0.4226183f, 0.4383711f, 0.4539905f, 0.4694716f, 0.4848096f,
    0.5000000f, 0.5150381f, 0.5299193f, 0.5446390f, 0.5591929f, 0.5735764f,
    0.5877853f, 0.6018150f, 0.6156615f, 0.6293204f, 0.6427876f, 0.6560590f,
    0.6691306f, 0.6819984f, 0.6946584f, 0.7071068f, 0.7193398f, 0.7313537f,
    0.7431448f, 0.7547096f, 0.7660444f, 0.7771460f, 0.7880108f, 0.7986355f,
    0.8090170f, 0.8191520f, 0.8290376f, 0.8386706f, 0.8480481f, 0.8571673f,
    0.8660254f, 0.8746197f, 0.8829476f, 0.8910065f, 0.8987940f, 0.9063078f,
    0.9135455f, 0.9205049f, 0.9271839f, 0.9335804f, 0.9396926f, 0.9455186f,
    0.9510565f, 0.9563048f, 0.9612617f, 0.9659258f, 0.9702957f, 0.9743701f,
    0.9781476f, 0.9816272f, 0.9848078f, 0.9876883f, 0.9902681f, 0.9925462f,
    0.9945219f, 0.9961947f, 0.9975641f, 0.9986295f, 0.9993908f, 0.9998477f,
    1.0000000f, 0.9998477f, 0.9993908f, 0.9986295f, 0.9975641f, 0.9961947f,
    0.9945219f, 0.9925462f, 0.9902681f, 0.9876883f, 0.9848078f, 0.9816272f,
    0.9781476f, 0.9743701f, 0.9702957f, 0.9659258f, 0.9612617f, 0.9563048f,
    0.9510565f, 0.9455186f, 0.9396926f, 0.9335804f, 0.9271839f, 0.9205049f,
    0.9135455f, 0.9063078f, 0.8987940f, 0.8910065f, 0.8829476f, 0.8746197f,
    0.8660254f, 0.8571673f, 0.8480481f, 0.8386706f, 0.8290376f, 0.8191520f,
    0.8090170f, 0.7986355f, 0.7880108f, 0.7771460f, 0.7660444f, 0.7547096f,
    0.7431448f, 0.7313537f, 0.7193398f, 0.7071068f, 0.6946584f, 0.6819984f,
    0.6691306f, 0.6560590f, 0.6427876f, 0.6293204f, 0.6156615f, 0.6018150f,
    0.5877853f, 0.5735764f, 0.5591929f, 0.5446390f, 0.5299193f, 0.5150381f,
    0.5000000f, 0.4848096f, 0.4694716f, 0.4539905f, 0.4383711f, 0.4226183f,
    0.4067366f, 0.3907311f, 0.3746066f, 0.3583679f, 0.3420201f, 0.3255682f,
    0.3090170f, 0.2923717f, 0.2756374f, 0.2588190f, 0.2419219f, 0.2249511f,
    0.2079117f, 0.1908090f, 0.1736482f, 0.1564345f, 0.1391731f, 0.1218693f,
    0.1045285f, 0.0871557f, 0.0697565f, 0.0523360f, 0.0348995f, 0.0174524f,
    0.0000000f, -0.0174524f, -0.0348995f, -0.0523360f, -0.0697565f, -0.0871557f,
    -0.1045285f, -0.1218693f, -0.1391731f, -0.1564345f, -0.1736482f, -0.1908090f,
    -0.2079117f, -0.2249511f, -0.2419219f, -0.2588190f, -0.2756374f, -0.2923717f,
    -0.3090170f, -0.3255682f, -0.3420201f, -0.3583679f, -0.3746066f, -0.3907311f,
    -0.4067366f, -0.4226183f, -0.4383711f, -0.4539905f, -0.4694716f, -0.4848096f,
    -0.5000000f, -0.5150381f, -0.5299193f, -0.5446390f, -0.5591929f, -0.5735764f,
    -0.5877853f, -0.6018150f, -0.6156615f, -0.6293204f, -0.6427876f, -0.6560590f,
    -0.6691306f, -0.6819984f, -0.6946584f, -0.7071068f, -0.7193398f, -0.7313537f,
    -0.7431448f, -0.7547096f, -0.7660444f, -0.7771460f, -0.7880108f, -0.7986355f,
    -0.8090170f, -0.8191520f, -0.8290376f, -0.8386706f, -0.8480481f, -0.8571673f,
    -0.8660254f, -0.8746197f, -0.8829476f, -0.8910065f, -0.8987940f, -0.9063078f,
    -0.9135455f, -0.9205049f, -0.9271839f, -0.9335804f, -0.9396926f, -0.9455186f,
    -0.9510565f, -0.9563048f, -0.9612617f, -0.9659258f, -0.9702957f, -0.9743701f,
    -0.9781476f, -0.9816272f, -0.9848078f, -0.9876883f, -0.9902681f, -0.9925462f,
    -0.9945219f, -0.9961947f, -0.9975641f, -0.9986295f, -0.9993908f, -0.9998477f,
    -1.0000000f, -0.9998477f, -0.9993908f, -0.9986295f, -0.9975641f, -0.9961947f,
    -0.9945219f, -0.9925462f, -0.9902681f, -0.9876883f, -0.9848078f, -0.9816272f,
    -0.9781476f, -0.9743701f, -0.9702957f, -0.9659258f, -0.9612617f, -0.9563048f,
    -0.9510565f, -0.9455186f, -0.9396926f, -0.9335804f, -0.9271839f, -0.9205049f,
    -0.9135455f, -0.9063078f, -0.8987940f, -0.8910065f, -0.8829476f, -0.8746197f,
    -0.8660254f, -0.8571673f, -0.8480481f, -0.8386706f, -0.8290376f, -0.8191520f,
    -0.8090170f, -0.7986355f, -0.7880108f, -0.7771460f, -0.7660444f, -0.7547096f,
    -0.7431448f, -0.7313537f, -0.7193398f, -0.7071068f, -0.6946584f, -0.6819984f,
    -0.6691306f, -0.6560590f, -0.6427876f, -0.6293204f, -0.6156615f, -0.6018150f,
    -0.5877853f, -0.5735764f, -0.5591929f, -0.5446390f, -0.5299193f, -0.5150381f,
    -0.5000000f, -0.4848096f, -0.4694716f, -0.4539905f, -0.4383711f, -0.4226183f,
    -0.4067366f, -0.3907311f, -0.3746066f, -0.3583679f, -0.3420201f, -0.3255682f,
    -0.3090170f, -0.2923717f, -0.2756374f, -0.2588190f, -0.2419219f, -0.2249511f,
    -0.2079117f, -0.1908090f, -0.1736482f, -0.1564345f, -0.1391731f, -0.1218693f,
    -0.1045285f, -0.0871557f, -0.0697565f, -0.0523360f, -0.0348995f, -0.0174524f,
    -0.0000000f, 0.0174524f, 0.0348995f, 0.0523360f, 0.0697565f, 0.0871557f,
    0.1045285f, 0.1218693f, 0.1391731f, 0.1564345f, 0.1736482f, 0.1908090f,
    0.2079117f, 0.2249511f, 0.2419219f, 0.2588190f, 0.2756374f, 0.2923717f,
    0.3090170f, 0.3255682f, 0.3420201f, 0.3583679f, 0.3746066f, 0.3907311f,
    0.4067366f, 0.4226183f, 0.4383711f, 0.4539905f, 0.4694716f, 0.4848096f,
    0.5000000f, 0.5150381f, 0.5299193f, 0.5446390f, 0.5591929f, 0.5735764f,
    0.5877853f, 0.6018150f, 0.6156615f, 0.6293204f, 0.6427876f, 0.6560590f,
    0.6691306f, 0.6819984f, 0.6946584f, 0.7071068f, 0.7193398f, 0.7313537f,
    0.7431448f, 0.7547096f, 0.7660444f, 0.7771460f, 0.7880108f, 0.7986355f,
    0.8090170f, 0.8191520f, 0.8290376f, 0.8386706f, 0.8480481f, 0.8571673f,
    0.8660254f, 0.8746197f, 0.8829476f, 0.8910065f, 0.8987940f, 0.9063078f,
    0.9135455f, 0.9205049f, 0.9271839f, 0.9335804f, 0.9396926f, 0.9455186f,
    0.9510565f, 0.9563048f, 0.9612617f, 0.9659258f, 0.9702957f, 0.9743701f,
    0.9781476f, 0.9816272f, 0.9848078f, 0.9876883f, 0.9902681f, 0.9925462f,
    0.9945219f, 0.9961947f, 0.9975641f, 0.9986295f, 0.9993908f, 0.9998477f,
    1.0000000f
};

void
icvSinCos( int angle, float *cosval, float *sinval )
{
    angle += (angle < 0 ? 360 : 0);
    *sinval = icvSinTable[angle];
    *cosval = icvSinTable[450 - angle];
}

/* 
   constructs polygon that represents elliptic arc.
*/
static int
icvEllipse2Poly( CvPoint center, CvSize axes,
                 int angle, int arc_start, int arc_end, CvPoint * pts, int delta )
{
    float alpha, beta;
    float size_a = (float) axes.width, size_b = (float) axes.height;
    float arc_al, arc_be;
    float da, db;
    float cx, cy;
    CvPoint *pts_origin = pts;
    int i;

    cx = (float) center.x;
    cy = (float) center.y;

    while( angle < 0 )
        angle += 360;
    while( angle > 360 )
        angle -= 360;

    if( arc_start > arc_end )
    {
        i = arc_start;
        arc_start = arc_end;
        arc_end = i;
    }
    while( arc_start < 0 )
    {
        arc_start += 360;
        arc_end += 360;
    }
    while( arc_end > 360 )
    {
        arc_end -= 360;
        arc_start -= 360;
    }
    if( arc_end - arc_start > 360 )
    {
        arc_start = 0;
        arc_end = 360;
    }

    icvSinCos( angle, &alpha, &beta );

    icvSinCos( arc_start, &arc_al, &arc_be );
    icvSinCos( delta, &da, &db );

    for( i = arc_start; i < arc_end + delta; i += delta, pts++ )
    {
        float x, y;

        if( i > arc_end )
        {
            icvSinCos( arc_end, &arc_al, &arc_be );
        }

        x = size_a * arc_al;
        y = size_b * arc_be;
        pts->x = cvRound( cx + x * alpha - y * beta );
        pts->y = cvRound( cy - x * beta - y * alpha );

        x = arc_al * da - arc_be * db;
        arc_be = arc_al * db + arc_be * da;
        arc_al = x;
    }

    return pts - pts_origin;
}


typedef enum CvEllipseKind
{
    Ellipse_Antialiazed = -1,
    Ellipse_Filled = 0,
    Ellipse_Simple = 1
} CvEllipseKind;


static void
icvEllipseEx( CvMat* mat, CvPoint center, CvSize axes,
              int angle, int arc_start, int arc_end,
              CvEllipseKind kind, int scale,
              int thickness, const void* color )
{
    CvMemStorage* st = 0;

    CV_FUNCNAME( "icvEllipseEx" );
    
    __BEGIN__;

    CvPoint pts[1 << 8];
    int npts;

    if( (axes.width | axes.height) < 0 )
        CV_ERROR( CV_StsBadSize, "" );
    if( (unsigned)scale > XY_SHIFT )
        CV_ERROR( CV_StsBadFlag, "" );
    if( thickness < 0 )
        CV_ERROR( CV_StsBadFlag, "" );

    assert( kind == Ellipse_Antialiazed || scale == 0 );

    npts = icvEllipse2Poly( center, axes, angle, arc_start, arc_end,
                            pts, kind == Ellipse_Filled ? 2 : 2 );

    switch (kind)
    {
    case Ellipse_Simple:
        CV_CALL( icvPolyLine( mat, pts, npts, 0, thickness, color ));
        break;
    case Ellipse_Filled:
        if( arc_end - arc_start >= 360 )
        {
            CV_CALL( icvFillConvexPoly( mat, pts, npts, color ));
        }
        else
        {
            CvContour* edges;
            CvSeq vtx;
            CvSeqBlock block;
            
            CV_CALL( st = cvCreateMemStorage( (1<<12) - 128 ));
            CV_CALL( edges = (CvContour*)cvCreateSeq( 0, sizeof(CvContour),
                                                      sizeof(CvPolyEdge), st ));

            pts[npts++] = center;

            CV_CALL( cvMakeSeqHeaderForArray( 0, sizeof(CvSeq), sizeof(CvPoint),
                                              pts, npts, &vtx, &block ));

            CV_CALL( icvCollectPolyEdges( mat, &vtx, edges, color ));
            CV_CALL( icvFillEdgeCollection( mat, edges, color ));
        }
        break;
    case Ellipse_Antialiazed:
        CV_CALL( icvPolyLineAA( mat, pts, npts, 0, scale, color ));
        break;
    default:
        CV_ERROR( CV_StsBadFlag, "" );
    }

    __END__;

    if( st )
        cvReleaseMemStorage( &st );
}


/****************************************************************************************\
*                                Polygons filling                                        * 
\****************************************************************************************/

/* helper macros: filling horizontal row */
#define ICV_HLINE( ptr, xl, xr, color, pix_size )            \
{                                                            \
    uchar* hline_ptr = (uchar*)(ptr) + (xl)*(pix_size);      \
    uchar* hline_max_ptr = (uchar*)(ptr) + (xr)*(pix_size);  \
                                                             \
    for( ; hline_ptr <= hline_max_ptr; hline_ptr += (pix_size))\
    {                                                        \
        int hline_j;                                         \
        for( hline_j = 0; hline_j < (pix_size); hline_j++ )  \
        {                                                    \
            hline_ptr[hline_j] = ((uchar*)color)[hline_j];   \
        }                                                    \
    }                                                        \
}


/* filling convex polygon. v - array of vertices, ntps - number of points */
static void
icvFillConvexPoly( CvMat* img, CvPoint *v, int npts, const void* color )
{
    const int scale = 16;
    const int delta = 1 << (scale - 1);

    struct
    {
        int idx, di;
        int x, dx, ye;
    }
    edge[2];

    int i, y, imin = 0, left = 0, right = 1, x1, x2;
    int edges = npts;
    int xmin = SHRT_MAX, ymin = xmin, xmax = SHRT_MIN, ymax = xmax;
    uchar* ptr = img->data.ptr;
    CvSize size = icvGetMatSize( img );
    int pix_size = icvPixSize[CV_ARR_TYPE(img->type)];
    CvPoint p0;

    p0 = v[npts - 1];

    //icvPolyLine( img, v, npts, 0, 1, color );

    for( i = 0; i < npts; i++ )
    {
        CvPoint p = v[i];
        int mask = p.y < ymin ? -1 : 0;

        imin ^= (imin ^ i) & mask;
        ymin ^= (ymin ^ p.y) & mask;

        ymax = CV_MAX( ymax, p.y );
        xmax = CV_MAX( xmax, p.x );
        xmin = CV_MIN( xmin, p.x );

        icvLine( img, p0, p, color, 8 );

        p0 = p;
    }

    if( npts < 3 || (ymax | xmax) < 0 || ymin >= size.height || xmin >= size.width )
        return;

    ymax = CV_MIN( ymax, size.height - 1 );

    edge[0].idx = edge[1].idx = imin;

    y = v[imin].y;

    edge[0].ye = edge[1].ye = y;
    edge[0].di = 1;
    edge[1].di = npts - 1;

    ptr += img->step * y;

    do
    {
        for( i = 0; i < 2; i++ )
        {
            if( y == edge[i].ye )
            {
                int idx = edge[i].idx, di = edge[i].di;
                int xs = 0, xe, ye;

                while( y >= v[idx].y && edges > 0 )
                {
                    xs = v[idx].x;
                    idx += di;
                    idx -= ((idx < npts) - 1) & npts;   /* idx -= idx >= npts ? npts : 0 */
                    edges--;
                }

                ye = v[idx].y;
                xe = v[idx].x;

                /* no more edges */
                if( y >= ye )
                    return;

                edge[i].ye = ye;
                edge[i].dx = (((xe - xs) << (scale + 1)) + (ye - y)) / (2 * (ye - y));
                edge[i].x = xs << scale;
                edge[i].idx = idx;
            }
        }

        if( edge[left].x > edge[right].x )
        {
            left ^= 1;
            right ^= 1;
        }

        x1 = edge[left].x;
        x2 = edge[right].x;

        if( y >= 0 )
        {
            int xx1 = (x1 + delta) >> scale;
            int xx2 = (x2 + delta) >> scale;

            if( xx2 >= 0 && xx1 < size.width )
            {
                if( xx1 < 0 )
                    xx1 = 0;
                if( xx2 >= size.width )
                    xx2 = size.width - 1;
                ICV_HLINE( ptr, xx1, xx2, color, pix_size );
            }
        }

        x1 += edge[left].dx;
        x2 += edge[right].dx;

        edge[left].x = x1;
        edge[right].x = x2;
        ptr += img->step;
    }
    while( ++y <= ymax );
}


/******** Arbitrary polygon **********/

static void
icvCollectPolyEdges( CvMat* img, CvSeq* v, CvContour* edges, const void* color )
{
    int  i, count = v->total;
    CvRect bounds = edges->rect;

    CvSeqReader reader;
    CvSeqWriter writer;

    cvStartReadSeq( v, &reader );
    cvStartAppendToSeq( (CvSeq*)edges, &writer );

    for( i = 0; i < count; i++ )
    {
        CvPoint pt0, pt1;
        CvPolyEdge edge;
        
        CV_READ_EDGE( pt0, pt1, reader );

        icvLine( img, pt0, pt1, color );

        if( pt0.y == pt1.y )
            continue;

        if( pt0.y > pt1.y )
        {
            CvPoint t;
            CV_SWAP( pt0, pt1, t );
        }

        bounds.y = CV_MIN( bounds.y, pt0.y );
        bounds.height = CV_MAX( bounds.height, pt1.y );

        if( pt0.x < pt1.x )
        {
            bounds.x = CV_MIN( bounds.x, pt0.x );
            bounds.width = CV_MAX( bounds.width, pt1.x );
        }
        else
        {
            bounds.x = CV_MIN( bounds.x, pt1.x );
            bounds.width = CV_MAX( bounds.width, pt0.x );
        }

        edge.y0 = pt0.y;
        edge.y1 = pt1.y;
        edge.x = pt0.x << 16;
        edge.dx = ((pt1.x - pt0.x) << 16) / (pt1.y - pt0.y);

        CV_WRITE_SEQ_ELEM( edge, writer );
    }

    edges->rect = bounds;
    cvEndWriteSeq( &writer );
}


#define ICV_CMP_EDGES( e1, e2 ) \
    ((e1).y0 < (e2).y0 || (e1).y0 == (e2).y0 && \
    ((e1).x < (e2).x || (e1).x == (e2).x && (e1).dx <= (e2).dx))


static
CV_IMPLEMENT_SEQ_QSORT( icvSortPolyEdges, CvPolyEdge, ICV_CMP_EDGES );


static void
icvFillEdgeCollection( CvMat* img, CvContour* edges, const void* color )
{
    CvPolyEdge tmp;
    int i, y, total = edges->total;
    CvSeqReader reader;
    CvSize size = icvGetMatSize(img);
    CvPolyEdge* e;
    int y_max = INT_MIN;
    int pix_size = icvPixSize[CV_ARR_TYPE(img->type)];

    __BEGIN__;
    
    memset( &tmp, 0, sizeof(tmp));
    
    /* check parameters */
    if( edges->total < 2 || edges->rect.height < 0 || edges->rect.y >= size.height ||
        edges->rect.width < 0 || edges->rect.x >= size.width )
        EXIT;

    icvSortPolyEdges( (CvSeq*)edges, 0 );

    cvStartReadSeq( (CvSeq*)edges, &reader );

#ifdef _DEBUG
    e = &tmp;
    tmp.y0 = INT_MIN;
#endif

    for( i = 0; i < total; i++ )
    {
        CvPolyEdge* e1 = (CvPolyEdge*)(reader.ptr);

#ifdef _DEBUG
        assert( ICV_CMP_EDGES( *e, *e1 ) != 0 );
        e = e1;
#endif
        y_max = CV_MAX( y_max, e1->y1 );

        CV_NEXT_SEQ_ELEM( sizeof(CvPolyEdge), reader );
    }

    if( y_max >= size.height )
        y_max = size.height - 1;

    /* start drawing */
    tmp.y0 = INT_MAX;
    cvSeqPush( (CvSeq*)edges, &tmp );

    i = 0;
    tmp.next = 0;
    cvStartReadSeq( (CvSeq*)edges, &reader );
    e = (CvPolyEdge*)(reader.ptr);
    y = e->y0;

    do
    {
        CvPolyEdge *last, *prelast, *keep_prelast;
        int sort_flag = 0;
        int draw = 0;
        int clipline = y < 0;

        prelast = &tmp;
        last = tmp.next;
        while( last || e->y0 == y )
        {
            if( last && last->y1 == y )
            {
                /* exlude edge if y reachs its lower point */
                prelast->next = last->next;
                last = last->next;
                continue;
            }
            keep_prelast = prelast;
            if( last && (e->y0 > y || last->x < e->x) )
            {
                /* go to the next edge in active list */
                prelast = last;
                last = last->next;
            }
            else if( i < total )
            {
                /* insert new edge into active list if y reachs its upper point */
                prelast->next = e;
                e->next = last;
                prelast = e;
                CV_NEXT_SEQ_ELEM( edges->elem_size, reader );
                e = (CvPolyEdge*)(reader.ptr);
                i++;
            }
            else
                break;

            if( draw )
            {
                if( !clipline )
                {
                    /* convert x's from fixed-point to image coordinates */
                    uchar *timg = (uchar*)(img->data.ptr) + y * img->step;
                    int x1 = keep_prelast->x;
                    int x2 = prelast->x;

                    if( x1 > x2 )
                    {
                        int t = x1;

                        x1 = x2;
                        x2 = t;
                    }

                    x1 = (x1 + (1 << 15)) >> 16;
                    x2 = (x2 + (1 << 15)) >> 16;

                    /* clip and draw the line */
                    if( x1 < size.width && x2 >= 0 )
                    {
                        if( x1 < 0 )
                            x1 = 0;
                        if( x2 >= size.width )
                            x2 = size.width - 1;
                        ICV_HLINE( timg, x1, x2, color, pix_size );
                    }
                }
                keep_prelast->x += keep_prelast->dx;
                prelast->x += prelast->dx;
            }
            draw ^= 1;
        }

        /* sort edges (bubble sort on list) */
        keep_prelast = 0;

        do
        {
            prelast = &tmp;
            last = tmp.next;

            while( last != keep_prelast && last->next != 0 )
            {
                CvPolyEdge *te = last->next;

                /* swap edges */
                if( last->x > te->x )
                {
                    prelast->next = te;
                    last->next = te->next;
                    te->next = last;
                    prelast = te;
                    sort_flag = 1;
                }
                else
                {
                    prelast = last;
                    last = te;
                }
            }
            keep_prelast = prelast;
        }
        while( sort_flag && keep_prelast != tmp.next && keep_prelast != &tmp );
    }
    while( (++y) < y_max );

    __END__;
}


/* draws simple circle */
static void
icvCircle( CvMat* img, CvPoint center, int radius, const void* color )
{
    CvSize size = icvGetMatSize( img );
    int step = img->step;
    int pix_size = icvPixSize[CV_ARR_TYPE(img->type)];
    uchar* ptr = (uchar*)(img->data.ptr);
    int err = 0, dx = radius, dy = 0, plus = 1, minus = (radius << 1) - 1;
    int inside = center.x >= radius && center.x < size.width - radius &&
        center.y >= radius && center.y < size.height - radius;

    #define ICV_PUT_POINT( ptr, x )   \
        memcpy( (ptr) + (x)*pix_size, color, pix_size )

    while( dx >= dy )
    {
        int mask;
        int y11 = center.y - dy, y12 = center.y + dy, y21 = center.y - dx, y22 = center.y + dx;

        int x11 = center.x - dx, x12 = center.x + dx, x21 = center.x - dy, x22 = center.x + dy;

        if( inside )
        {
            uchar *tptr0 = ptr + y11 * step;
            uchar *tptr1 = ptr + y12 * step;

            ICV_PUT_POINT( tptr0, x11 );
            ICV_PUT_POINT( tptr1, x11 );
            ICV_PUT_POINT( tptr0, x12 );
            ICV_PUT_POINT( tptr1, x12 );

            tptr0 = ptr + y21 * step;
            tptr1 = ptr + y22 * step;

            ICV_PUT_POINT( tptr0, x21 );
            ICV_PUT_POINT( tptr1, x21 );
            ICV_PUT_POINT( tptr0, x22 );
            ICV_PUT_POINT( tptr1, x22 );
        }
        else if( x11 < size.width && x12 >= 0 && y21 < size.height && y22 >= 0 )
        {
            if( (unsigned) y11 < (unsigned) size.height )
            {
                uchar *tptr = ptr + y11 * step;

                if( x11 >= 0 )
                    ICV_PUT_POINT( tptr, x11 );
                if( x12 < size.width )
                    ICV_PUT_POINT( tptr, x12 );
            }

            if( (unsigned) y12 < (unsigned) size.height )
            {
                uchar *tptr = ptr + y12 * step;

                if( x11 >= 0 )
                    ICV_PUT_POINT( tptr, x11 );
                if( x12 < size.width )
                    ICV_PUT_POINT( tptr, x12 );
            }

            if( x21 < size.width && x22 >= 0 )
            {
                if( (unsigned) y21 < (unsigned) size.height )
                {
                    uchar *tptr = ptr + y21 * step;

                    if( x21 >= 0 )
                        ICV_PUT_POINT( tptr, x21 );
                    if( x22 < size.width )
                        ICV_PUT_POINT( tptr, x22 );
                }

                if( (unsigned) y22 < (unsigned) size.height )
                {
                    uchar *tptr = ptr + y22 * step;

                    if( x21 >= 0 )
                        ICV_PUT_POINT( tptr, x21 );
                    if( x22 < size.width )
                        ICV_PUT_POINT( tptr, x22 );
                }
            }
        }
        dy++;
        err += plus;
        plus += 2;

        mask = (err <= 0) - 1;

        err -= minus & mask;
        dx += mask;
        minus -= mask & 2;
    }

    #undef  ICV_PUT_POINT
}


/****************************************************************************************\
*                      Cicle drawing using direct Bresenham algorithm                    *
\****************************************************************************************/

/* draws filled circle */
static void
icvFillCircle( CvMat* img, CvPoint center, int radius, const void* color )
{
    CvSize size = icvGetMatSize( img );
    int step = img->step;
    int pix_size = icvPixSize[CV_ARR_TYPE(img->type)];
    uchar* ptr = (uchar*)(img->data.ptr);
    int err = 0, dx = radius, dy = 0, plus = 1, minus = (radius << 1) - 1;
    int inside = center.x >= radius && center.x < size.width - radius &&
        center.y >= radius && center.y < size.height - radius;

    while( dx >= dy )
    {
        int mask;
        int y11 = center.y - dy, y12 = center.y + dy, y21 = center.y - dx, y22 = center.y + dx;
        int x11 = center.x - dx, x12 = center.x + dx, x21 = center.x - dy, x22 = center.x + dy;

        if( inside )
        {
            uchar *tptr0 = ptr + y11 * step;
            uchar *tptr1 = ptr + y12 * step;

            ICV_HLINE( tptr0, x11, x12, color, pix_size );
            ICV_HLINE( tptr1, x11, x12, color, pix_size );

            tptr0 = ptr + y21 * step;
            tptr1 = ptr + y22 * step;

            ICV_HLINE( tptr0, x21, x22, color, pix_size );
            ICV_HLINE( tptr1, x21, x22, color, pix_size );
        }
        else if( x11 < size.width && x12 >= 0 && y21 < size.height && y22 >= 0 )
        {
            x11 = CV_MAX( x11, 0 );
            x12 = CV_MIN( x12, size.width - 1 );

            if( (unsigned) y11 < (unsigned) size.height )
            {
                uchar *tptr = ptr + y11 * step;
                ICV_HLINE( tptr, x11, x12, color, pix_size );
            }

            if( (unsigned) y12 < (unsigned) size.height )
            {
                uchar *tptr = ptr + y12 * step;
                ICV_HLINE( tptr, x11, x12, color, pix_size );
            }

            if( x21 < size.width && x22 >= 0 )
            {
                x21 = CV_MAX( x21, 0 );
                x22 = CV_MIN( x22, size.width - 1 );

                if( (unsigned) y21 < (unsigned) size.height )
                {
                    uchar *tptr = ptr + y21 * step;
                    ICV_HLINE( tptr, x21, x22, color, pix_size );
                }

                if( (unsigned) y22 < (unsigned) size.height )
                {
                    uchar *tptr = ptr + y22 * step;
                    ICV_HLINE( tptr, x21, x22, color, pix_size );
                }
            }
        }
        dy++;
        err += plus;
        plus += 2;

        mask = (err <= 0) - 1;

        err -= minus & mask;
        dx += mask;
        minus -= mask & 2;
    }
}


/* helper function for thick lines */
static CvPoint
icvCalcWPT( CvPoint p1, CvPoint p2, int lr )
{
    int dx = p1.x - p2.x, dy = p2.y - p1.y;
    double r = dx * dx + dy * dy;
    CvPoint dp = { 0, 0 };

    if( r )
    {
        r = lr * cvInvSqrt( (float) r );
        dp.x = cvRound( dy * r );
        dp.y = cvRound( dx * r );
    }
    return dp;
}


static void
icvThickLine( CvMat* img, CvPoint pt1, CvPoint pt2,
              int thickness, const void* color,
              int connectivity = 8 )
{
    thickness >>= 1;

    if( connectivity == 0 )
        connectivity = 8;

    if( thickness <= 0 )
    {
        icvLine( img, pt1, pt2, color, connectivity );
    }
    else
    {
        CvPoint pt[4];
        CvPoint dp = icvCalcWPT( pt1, pt2, thickness );

        pt[0].x = pt1.x + dp.x;
        pt[0].y = pt1.y + dp.y;
        pt[1].x = pt1.x - dp.x;
        pt[1].y = pt1.y - dp.y;
        pt[2].x = pt2.x - dp.x;
        pt[2].y = pt2.y - dp.y;
        pt[3].x = pt2.x + dp.x;
        pt[3].y = pt2.y + dp.y;

        icvFillConvexPoly( img, pt, 4, color );
        icvFillCircle( img, pt1, thickness, color );
        icvFillCircle( img, pt2, thickness, color );
    }
}


static void
icvPolyLine( CvMat* img, CvPoint *v, int count, int closed,
             int thickness, const void* color, int connectivity )
{
    CV_FUNCNAME("icvPolyLine");

    __BEGIN__;
    
    int i0 = closed ? count - 1 : 0, i;

    assert( img && thickness >= 0 ); 
    assert( v && count >= 0 );

    if( !v )
        CV_ERROR( CV_StsNullPtr, "" );

    if( count > 0 )
    {
        for( i = !closed; i < count; i0 = i, i++ )
        {
            icvThickLine( img, v[i0], v[i], thickness, color, connectivity );
        }
    }

    __END__;
}


static void
icvPolyLineAA( CvMat* img, CvPoint *v, int count, int closed,
               int scale, const void* color )
{
    CV_FUNCNAME("icvPolyLineAA");

    __BEGIN__;
    
    CvMat mat = *img;
    int i0 = closed ? count - 1 : 0, i;

    assert( img && (unsigned) scale <= XY_SHIFT ); 

    if( !v )
        CV_ERROR( CV_StsNullPtr, "" );

    if( CV_ARR_DEPTH( img->type ) != CV_8U )
        CV_ERROR( CV_BadDepth, icvUnsupportedFormat );

    if( CV_ARR_CN( img->type ) != 1 && CV_ARR_CN( img->type ) != 3 )
        CV_ERROR( CV_BadNumChannels, icvUnsupportedFormat );

    mat.width -= 4;
    mat.height -= 4;

    if( mat.width > 0 && mat.height > 0 )
    {
        mat.data.ptr += (mat.step + CV_ARR_CN(mat.type)) * 2;

        for( i = !closed; i < count; i0 = i, i++ )
        {
            icvLineAA( &mat,
                       cvPoint( (v[i0].x << (XY_SHIFT - scale)) - 2 * XY_ONE,
                                (v[i0].y << (XY_SHIFT - scale)) - 2 * XY_ONE ),
                       cvPoint( (v[i].x << (XY_SHIFT - scale)) - 2 * XY_ONE,
                                (v[i].y << (XY_SHIFT - scale)) - 2 * XY_ONE ), color );
        }
    }

    __END__;
}


/****************************************************************************************\
*                              External functions                                        *
\****************************************************************************************/

static void
icvExtractColor( double color, int type, void* buffer )
{
    CV_FUNCNAME( "icvExtractColor" );

    __BEGIN__;

    if( CV_ARR_DEPTH( type ) <= CV_8S )
    {
        int icolor = cvRound( color );
        
        ((uchar*)buffer)[0] = (uchar)icolor;
        ((uchar*)buffer)[1] = (uchar)(icolor >> 8);
        ((uchar*)buffer)[2] = (uchar)(icolor >> 16);
        ((uchar*)buffer)[3] = (uchar)(icolor >> 24);
    }
    else
    {
        if( CV_ARR_CN( type ) > 1 )
            CV_ERROR( CV_BadNumChannels,
            "Multi-channel images with depth different from 8bit "
            "are not supported by drawing functions" );

        switch( CV_ARR_DEPTH( type ))
        {
        case CV_16S:
            ((short*)buffer)[0] = (short)cvRound( color );
            break;
        case CV_32S:
            ((int*)buffer)[0] = cvRound( color );
            break;
        case CV_32F:
            ((float*)buffer)[0] = (float)color;
            break;
        case CV_64F:
            ((double*)buffer)[0] = (double)color;
            break;
        default:
            assert(0);
            CV_ERROR( CV_BadDepth, "" );
        }
    }

    __END__;
}


CV_IMPL void
cvLine( void* img, CvPoint pt1, CvPoint pt2, double color,
        int thickness, int connectivity )
{
    CV_FUNCNAME( "cvLine" );

    __BEGIN__;

    int coi = 0;
    CvMat stub, *mat = (CvMat*)img;
    double buf[4];

    CV_CALL( mat = cvGetMat( img, &stub, &coi ));

    if( coi != 0 )
        CV_ERROR( CV_BadCOI, icvUnsupportedFormat );

    if( (unsigned)thickness > 255  )
        CV_ERROR_FROM_STATUS( CV_BADRANGE_ERR );

    CV_CALL( icvExtractColor( color, mat->type, buf ));
    icvThickLine( mat, pt1, pt2, thickness, buf, connectivity );

    __END__;
}



CV_IMPL void
cvLineAA( void *img, CvPoint pt1, CvPoint pt2, double color, int scale )
{
    CV_FUNCNAME( "cvLineAA" );

    __BEGIN__;

    int coi = 0, cn;
    CvMat stub, *mat = (CvMat*)img;
    double buf[4];

    CV_CALL( mat = cvGetMat( mat, &stub, &coi ));

    if( mat != &stub )
    {
        stub = *mat;
        mat = &stub;
    }

    if( coi != 0 )
        CV_ERROR( CV_BadCOI, icvUnsupportedFormat );

    if( scale < 0 || scale > XY_SHIFT )
        CV_ERROR_FROM_STATUS( CV_BADRANGE_ERR );

    CV_CALL( icvExtractColor( color, mat->type, buf ));

    cn = CV_ARR_CN( mat->type );

    if( CV_ARR_DEPTH( mat->type) != CV_8U )
        CV_ERROR( CV_BadDepth, icvUnsupportedFormat );

    if( cn != 1 && cn != 3 )
        CV_ERROR( CV_BadNumChannels, icvUnsupportedFormat );

    /* shrink window because antialiased line is 3-pixel width */
    mat->width -= 4;
    mat->height -= 4;
    mat->data.ptr += (mat->step + cn)*2;

    if( mat->width > 0 && mat->height > 0 )
    {
        pt1.x = (pt1.x << (XY_SHIFT - scale)) - 2 * XY_ONE;
        pt1.y = (pt1.y << (XY_SHIFT - scale)) - 2 * XY_ONE;
        pt2.x = (pt2.x << (XY_SHIFT - scale)) - 2 * XY_ONE;
        pt2.y = (pt2.y << (XY_SHIFT - scale)) - 2 * XY_ONE;

        icvLineAA( mat, pt1, pt2, buf );
    }

    __END__;
}


CV_IMPL void
cvRectangle( void* img, CvPoint pt1, CvPoint pt2,
             double color, int thickness )
{
    CvPoint pt_arr[4];
    CvPoint *pt = pt_arr;
    int count = 4;

    CV_FUNCNAME("cvRectangle");

    __BEGIN__;

    if( thickness < -1 || thickness > 255 )
        CV_ERROR_FROM_STATUS( CV_BADRANGE_ERR );

    pt_arr[0] = pt1;
    pt_arr[1].x = pt2.x;
    pt_arr[1].y = pt1.y;
    pt_arr[2] = pt2;
    pt_arr[3].x = pt1.x;
    pt_arr[3].y = pt2.y;

    if( thickness >= 0 )
    {
        cvPolyLine( img, &pt, &count, 1, 1, color, thickness );
    }
    else
    {
        cvFillConvexPoly( img, pt, count, color );
    }

    __END__;
}


CV_IMPL void
cvCircle( void *img, CvPoint center, int radius, double color, int thickness )
{
    CV_FUNCNAME( "cvCircle" );

    __BEGIN__;

    int coi = 0;
    CvMat stub, *mat = (CvMat*)img;
    double buf[4];

    CV_CALL( mat = cvGetMat( mat, &stub, &coi ));

    if( coi != 0 )
        CV_ERROR( CV_BadCOI, icvUnsupportedFormat );

    if( radius < 0 )
        CV_ERROR_FROM_STATUS( CV_BADRANGE_ERR );

    if( thickness < -1 || thickness > 255 )
        CV_ERROR_FROM_STATUS( CV_BADRANGE_ERR );

    CV_CALL( icvExtractColor( color, mat->type, buf ));

    if( thickness > 1 )
    {
        icvEllipseEx( mat, center, cvSize( radius, radius ), 0, 0, 360,
                      Ellipse_Simple, 0, thickness, buf );
    }
    else if( thickness >= 0 )
    {
        icvCircle( mat, center, radius, buf );
    }
    else
    {
        icvFillCircle( mat, center, radius, buf );
    }

    __END__;
}



CV_IMPL void
cvCircleAA( void *img, CvPoint center, int radius,
            double color, int scale )
{
    CV_FUNCNAME( "cvCircleAA" );

    __BEGIN__;

    int coi = 0;
    CvMat stub, *mat = (CvMat*)img;
    double buf[4];

    CV_CALL( mat = cvGetMat( mat, &stub, &coi ));

    if( coi != 0 )
        CV_ERROR( CV_BadCOI, icvUnsupportedFormat );

    if( radius < 0 )
        CV_ERROR_FROM_STATUS( CV_BADRANGE_ERR );

    CV_CALL( icvExtractColor( color, mat->type, buf ));

    if( radius < 0 )
        CV_ERROR_FROM_STATUS( CV_BADRANGE_ERR );

    if( scale < 0 || scale > XY_SHIFT )
        CV_ERROR_FROM_STATUS( CV_BADRANGE_ERR );

    CV_CALL( icvEllipseEx( mat, center, cvSize( radius , radius ),
                           0, 0, 360, Ellipse_Antialiazed, scale,
                           1, buf ));

    __END__;
}



CV_IMPL void
cvEllipse( void *img, CvPoint center, CvSize axes,
           double angle, double startAngle, double endAngle,
           double color, int thickness )
{
    CV_FUNCNAME( "cvEllipse" );

    __BEGIN__;

    int coi = 0;
    CvMat stub, *mat = (CvMat*)img;
    double buf[4];

    CV_CALL( mat = cvGetMat( mat, &stub, &coi ));

    if( coi != 0 )
        CV_ERROR( CV_BadCOI, icvUnsupportedFormat );

    if( axes.width < 0 || axes.height < 0 )
        CV_ERROR_FROM_STATUS( CV_BADRANGE_ERR );

    if( thickness < -1 || thickness > 255 )
        CV_ERROR_FROM_STATUS( CV_BADRANGE_ERR );

    CV_CALL( icvExtractColor( color, mat->type, buf ));

    {
        CvEllipseKind kind = Ellipse_Simple;
        if( thickness < 0 )
        {
            kind = Ellipse_Filled;
            thickness = 1;
        }

        CV_CALL( icvEllipseEx( mat, center, axes, cvRound( angle ),
                               cvRound( startAngle ), cvRound( endAngle ),
                               kind, 0, thickness, buf ));
    }

    __END__;
}


CV_IMPL void
cvEllipseAA( void *img, CvPoint center, CvSize axes,
             double angle, double startAngle, double endAngle,
             double color, int scale )
{
    CV_FUNCNAME( "cvEllipseAA" );

    __BEGIN__;

    int coi = 0;
    CvMat stub, *mat = (CvMat*)img;
    double buf[4];

    CV_CALL( mat = cvGetMat( mat, &stub, &coi ));

    if( coi != 0 )
        CV_ERROR( CV_BadCOI, icvUnsupportedFormat );

    if( scale < 0 || scale > XY_SHIFT )
        CV_ERROR_FROM_STATUS( CV_BADRANGE_ERR );

    if( axes.width < 0 || axes.height < 0 )
        CV_ERROR_FROM_STATUS( CV_BADRANGE_ERR );

    CV_CALL( icvExtractColor( color, mat->type, buf ));

    CV_CALL( icvEllipseEx( mat, center, axes, cvRound( angle ),
                           cvRound( startAngle ), cvRound( endAngle ),
                           Ellipse_Antialiazed, scale, 1, buf ));

    __END__;
}


CV_IMPL void
cvFillConvexPoly( void *img, CvPoint *pts, int npts, double color )
{
    CV_FUNCNAME( "cvFillConvexPoly" );

    __BEGIN__;

    int coi = 0;
    CvMat stub, *mat = (CvMat*)img;
    double buf[4];

    CV_CALL( mat = cvGetMat( mat, &stub, &coi ));

    if( coi != 0 )
        CV_ERROR( CV_BadCOI, icvUnsupportedFormat );

    if( !pts )
        CV_ERROR_FROM_STATUS( CV_NULLPTR_ERR );

    if( npts <= 0 )
        CV_ERROR_FROM_STATUS( CV_BADRANGE_ERR );

    CV_CALL( icvExtractColor( color, mat->type, buf ));

    icvFillConvexPoly( mat, pts, npts, buf );

    __END__;
}


CV_IMPL void
cvFillPoly( void *img, CvPoint **pts, int *npts, int contours, double color )
{
    CvMemStorage* st = 0;
    
    CV_FUNCNAME( "cvFillPoly" );

    __BEGIN__;

    int coi = 0;
    CvMat stub, *mat = (CvMat*)img;
    double buf[4];

    CV_CALL( mat = cvGetMat( mat, &stub, &coi ));

    if( coi != 0 )
        CV_ERROR( CV_BadCOI, icvUnsupportedFormat );

    if( contours <= 0 )
        CV_ERROR( CV_StsBadArg, "" );

    if( !pts )
        CV_ERROR( CV_StsNullPtr, "" );

    if( npts <= 0 )
        CV_ERROR( CV_StsNullPtr, "" );

    CV_CALL( icvExtractColor( color, mat->type, buf ));

    {
        CvContour* edges = 0;
        CvSeq vtx;
        CvSeqBlock block;

        CV_CALL( st = cvCreateMemStorage( (1<<12) - 128 ));
        CV_CALL( edges = (CvContour*)cvCreateSeq( 0, sizeof(CvContour),
                                                  sizeof(CvPolyEdge), st ));

        for( int i = 0; i < contours; i++ )
        {
            if( !pts[i] )
                CV_ERROR_FROM_STATUS( CV_NULLPTR_ERR );

            if( npts[i] < 0 )
                CV_ERROR_FROM_STATUS( CV_BADRANGE_ERR );
            
            cvMakeSeqHeaderForArray( 0, sizeof(CvSeq), sizeof(CvPoint),
                                     pts[i], npts[i], &vtx, &block );

            CV_CALL( icvCollectPolyEdges( mat, &vtx, edges, buf ));
        }

        CV_CALL( icvFillEdgeCollection( mat, edges, buf ));
    }

    __END__;

    cvReleaseMemStorage( &st );
}



CV_IMPL void
cvPolyLine( void *img, CvPoint **pts, int *npts,
            int contours, int closed, double color,
            int thickness, int connectivity )
{
    CV_FUNCNAME( "cvPolyLine" );

    __BEGIN__;

    int coi = 0, i;
    CvMat stub, *mat = (CvMat*)img;
    double buf[4];

    CV_CALL( mat = cvGetMat( mat, &stub, &coi ));

    if( coi != 0 )
        CV_ERROR( CV_BadCOI, icvUnsupportedFormat );

    if( contours <= 0 )
        CV_ERROR( CV_StsBadArg, "" );

    if( thickness < -1 || thickness > 255 )
        CV_ERROR( CV_StsBadArg, "" );

    if( !pts )
        CV_ERROR( CV_StsNullPtr, "" );

    if( npts <= 0 )
        CV_ERROR( CV_StsNullPtr, "" );

    CV_CALL( icvExtractColor( color, mat->type, buf ));

    for( i = 0; i < contours; i++ )
    {
        CV_CALL( icvPolyLine( mat, pts[i], npts[i], closed, thickness,
                              buf, connectivity ));
    }

    __END__;
}


CV_IMPL void
cvPolyLineAA( void * img, CvPoint **pts, int *npts,
              int contours, int closed, double color, int scale )
{
    CV_FUNCNAME( "cvPolyLineAA" );

    __BEGIN__;

    int coi = 0, i;
    CvMat stub, *mat = (CvMat*)img;
    double buf[4];

    CV_CALL( mat = cvGetMat( mat, &stub, &coi ));

    if( coi != 0 )
        CV_ERROR( CV_BadCOI, icvUnsupportedFormat );

    if( contours <= 0 )
        CV_ERROR( CV_StsBadArg, "" );

    if( scale < 0 || scale > XY_SHIFT )
        CV_ERROR_FROM_STATUS( CV_BADRANGE_ERR );

    if( !pts )
        CV_ERROR( CV_StsNullPtr, "" );

    if( npts <= 0 )
        CV_ERROR( CV_StsNullPtr, "" );

    CV_CALL( icvExtractColor( color, mat->type, buf ));

    for( i = 0; i < contours; i++ )
    {
        CV_CALL( icvPolyLineAA( mat, pts[i], npts[i], closed, scale, buf ));
    }

    __END__;
}


CV_IMPL void
cvPutText( void *img, const char *text, CvPoint org, CvFont *font, double color )
{
    CV_FUNCNAME( "cvPutText" );

    __BEGIN__;

    int coi = 0;
    int top_bottom = 0;
    CvMat stub, *mat = (CvMat*)img;
    double buf[4];

    const int shift = CV_TXT_FONT_SHIFT + CV_TXT_SIZE_SHIFT;
    const int delta = 1 << (shift - 1);

    int i, font_height, max_code;
    const short *faces;

    CV_CALL( mat = cvGetMat( mat, &stub, &coi ));

    if( coi != 0 )
        CV_ERROR( CV_BadCOI, icvUnsupportedFormat );

    if( _CV_IS_IMAGE(img) && ((IplImage*)img)->origin )
        top_bottom = 1;

    if( !text || !font || !font->data )
        CV_ERROR( CV_StsNullPtr, "" );

    if( !font->data[2] && !font->data[3] )
        CV_ERROR( CV_StsNullPtr, "" );

    CV_CALL( icvExtractColor( color, mat->type, buf ));

    faces = (const short *)(((ulong)font->data[3] << sizeof(int)*8*
                             (sizeof(long)>sizeof(int))) + (ulong)font->data[2]);
    max_code = font->data[4];

    font_height = font->size.height;

    if( top_bottom )
    {
        org.y -= (font->data[1] * font_height + delta) >> shift;
        font_height = -font_height;
    }

    for( i = 0; text[i] != '\0'; i++ )
    {
        int idx = ((uchar)text[i]) * 4;
        int w;
        const short *letter;
        CvPoint pt0 = org;

        if( idx >= max_code * 4 || font->data[idx + CV_FONT_HDR_SIZE] < 0 )
            idx = 127 * 4;
        idx += CV_FONT_HDR_SIZE;
        letter = faces + font->data[idx];

        w = (font->data[idx + 1] * font->size.width + delta) >> shift;

        for( ;; )
        {
            CvPoint pt;
            int new_fl, end_fl;

            pt.x = letter[0];
            pt.y = letter[1];
            new_fl = (pt.x & 1);
            end_fl = (pt.y & 1);
            letter += 2;

            if( pt.x == SHRT_MIN )
                break;

            pt.x = org.x + ((pt.x * font->size.width +
                             pt.y * font->italic_scale + delta) >> shift);
            pt.y = org.y - ((pt.y * font_height + delta) >> shift);

            if( !new_fl )
            {
                icvThickLine( mat, pt0, pt, font->thickness, buf );
            }
            pt0 = pt;
            if( end_fl )
                break;
        }

        org.x += w + font->dx;
    }

    __END__;
}


CV_IMPL void
cvInitFont( CvFont *font, CvFontFace font_face,
            double hscale, double vscale, double italic_scale, int thickness )
{
    CV_FUNCNAME( "cvInitFont" );

    __BEGIN__;

    const int shift = CV_TXT_FONT_SHIFT + CV_TXT_SIZE_SHIFT;
    const int delta = 1 << (shift - 1);

    if( !font )
        CV_ERROR_FROM_STATUS( CV_NULLPTR_ERR );
    if( font_face != CV_FONT_VECTOR0 || hscale <= 0 || vscale <= 0 || thickness < 0 )
        CV_ERROR_FROM_STATUS( CV_BADRANGE_ERR );

    font->data = icvTextHdrsFn0;
    font->size.width = cvRound( hscale * (1 << CV_TXT_SIZE_SHIFT) );
    font->size.height = cvRound( vscale * (1 << CV_TXT_SIZE_SHIFT) );
    font->italic_scale = cvRound( italic_scale * vscale * (1 << CV_TXT_SIZE_SHIFT) );
    font->thickness = thickness;
    font->dx = ((font->size.width * font->data[0] + delta * 4) >>
                (shift + 2)) + font->thickness;

    __END__;
}


CV_IMPL void
cvGetTextSize( const char *text_string, CvFont *font, CvSize *text_size, int *_ymin )
{
    const int shift = CV_TXT_FONT_SHIFT + CV_TXT_SIZE_SHIFT;
    const int delta = 1 << (shift - 1);

    int i, max_code, width = 0, height = 0, ymin = 0;

    CV_FUNCNAME( "cvGetTextSize" );

    __BEGIN__;

    if( !font || !font->data || !text_string || !text_size || !_ymin )
        CV_ERROR_FROM_STATUS( CV_NULLPTR_ERR );

    max_code = font->data[3];

    for( i = 0; text_string[i] != '\0'; i++ )
    {
        int idx = ((uchar) text_string[i]) * 4;
        int yplus, yminus;

        if( idx >= max_code * 4 || font->data[idx + CV_FONT_HDR_SIZE] < 0 )
            idx = 127 * 4;
        idx += CV_FONT_HDR_SIZE;

        width += font->dx + ((font->data[idx + 1] * font->size.width + delta) >> shift);
        yplus = (font->data[idx + 2] * font->size.height + delta) >> shift;
        yminus = (font->data[idx + 3] * font->size.height + delta) >> shift;

        height = CV_IMAX( height, yplus );
        ymin = CV_IMIN( ymin, yminus );
    }

    text_size->width = width;
    text_size->height = height;
    *_ymin = ymin;

    __END__;
}



/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name: cvDrawContours
//    Purpose:
//      Draws one or more contours on the image
//    Context:
//    Parameters:
//      img      - destination three-channel image
//      step     - its full width in bytes
//      size     - width and height of the image in pixels
//      contour  - pointer to drawn contour(s).
//      external_color - color to draw external contours with
//      hole_color - color to draw hole contours with
//      max_level  - max level of the tree (starting from contour pointer) to draw.
//                   if it is 0, draw single contour, if 1 - draw the contour and
//                   other contours at the same level, 2 - draw two levels etc.
//    Returns:
//      CV_OK or error code
//    Notes:
//F*/
CV_IMPL void
cvDrawContours( void*  img,  CvSeq*  contour,
                double externalColor, double holeColor, 
                int  maxLevel, int thickness, int connectivity )
{
    int level = 1;
    CvSeq* limit;
    CvSeq* h_next = 0;
    CvMemStorage* st = 0;
    CvSeq* tseq = 0;
    CvContour* edges = 0;
    CvSeqWriter writer;
    int k = 0;

    CV_FUNCNAME( "cvDrawContours" );

    __BEGIN__;

    int coi = 0;
    CvMat stub, *mat = (CvMat*)img;
    double ext_buf[4], hole_buf[4];

    CV_CALL( mat = cvGetMat( mat, &stub, &coi ));

    if( coi != 0 )
        CV_ERROR( CV_BadCOI, icvUnsupportedFormat );

    if( thickness < -1 || thickness > 255 )
        CV_ERROR_FROM_STATUS( CV_BADRANGE_ERR );

    CV_CALL( icvExtractColor( externalColor, mat->type, ext_buf ));
    CV_CALL( icvExtractColor( holeColor, mat->type, hole_buf ));

    limit = contour->v_prev;

    if( maxLevel < 0 )
    {
        h_next = contour->h_next;
        contour->h_next = 0;
        maxLevel = -maxLevel;
    }

    if( thickness < 0 )
    {
        if( contour->storage )
            st = cvCreateChildMemStorage( contour->storage );
        else
            st = cvCreateMemStorage();
        tseq = cvCreateSeq( 0, sizeof(CvContour), sizeof(CvPoint), st );
        edges = (CvContour*)cvCreateSeq( 0, sizeof(CvContour), sizeof(CvPolyEdge), st );
    }

    memset( &writer, 0, sizeof(writer));

    while( contour != 0 )
    {        
        CvSeqReader reader;
        int i, count = contour->total;
        void* clr = (contour->flags & CV_SEQ_FLAG_HOLE) == 0 ? ext_buf : hole_buf;

        cvStartReadSeq( contour, &reader, 0 );

        if( CV_IS_SEQ_CHAIN_CONTOUR( contour ))
        {
            CvPoint pt = ((CvChain*)contour)->origin;
            CvPoint prev_pt = pt;
            char prev_code = reader.ptr ? reader.ptr[0] : '\0';

            if( thickness < 0 )
            {
                cvClearSeq( tseq );
                cvStartAppendToSeq( tseq, &writer );
                CV_WRITE_SEQ_ELEM( pt, writer );
            }

            for( i = 0; i < count; i++ )
            {
                char code;
                CV_READ_SEQ_ELEM( code, reader );

                assert( (code & ~7) == 0 );

                if( code != prev_code )
                {
                    prev_code = code;
                    if( thickness >= 0 )
                    {
                        icvThickLine( mat, prev_pt, pt, thickness, clr, connectivity );
                    }
                    else
                    {
                        CV_WRITE_SEQ_ELEM( pt, writer );
                    }
                    prev_pt = pt;
                }
            
                pt.x += icvCodeDeltas[code].x;
                pt.y += icvCodeDeltas[code].y;
            }

            if( thickness >= 0 )
            {
                icvThickLine( mat, prev_pt, ((CvChain*)contour)->origin,
                              thickness, clr, connectivity );
            }
            else
            {
                CV_WRITE_SEQ_ELEM( pt, writer );
                cvEndWriteSeq( &writer );
                CV_CALL( icvCollectPolyEdges( mat, tseq, edges, ext_buf ));
            }
        }
        else if( CV_IS_SEQ_POLYLINE( contour ))
        {
            if( thickness >= 0 )
            {
                CvPoint pt1, pt2;
                CV_ADJUST_EDGE_COUNT( count, contour );

                /* scroll the reader by 1 point */
                CV_READ_EDGE( pt1, pt2, reader );

                for( i = 0; i < count; i++ )
                {
                    CV_READ_EDGE( pt1, pt2, reader );

                    /*assert( pt1.x != 0 && pt1.y != 0 && pt2.x != 0 && pt2.y != 0 );*/

                    icvThickLine( mat, pt1, pt2, thickness, clr, connectivity );
                }
            }
            else
            {
                CV_CALL( icvCollectPolyEdges( mat, contour, edges, ext_buf ));
            }
        }

        if( maxLevel == 0 )
            break;

        if( contour->v_next && level < maxLevel )
        {
            contour = contour->v_next;
            level++;
        }
        else
        {
            while( contour->h_next == 0 )
            {
                contour = contour->v_prev;
                if( contour == limit )
                    break;
                level--;
            }
            if( contour == limit )
                break;
            if( contour )
                contour = contour->h_next;
        }

        k++;
    }

    if( thickness < 0 )
    {
        CV_CALL( icvFillEdgeCollection( mat, edges, ext_buf ));
    }

    __END__;

    if( h_next && contour )
        contour->h_next = h_next;

    cvReleaseMemStorage( &st );
}

/* End of file. */
