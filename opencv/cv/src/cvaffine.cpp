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

/* ////////////////////////////////////////////////////////////////////
//
//  Geometrical transforms on images and matrices: rotation, zoom etc.
//
// */

#include "_cv.h"
#include "_cvwrap.h"
#include "_cvarr.h"


IPCVAPI_IMPL( CvStatus,
icvResize_NN_8u_C1R, ( const uchar* src, int srcstep, CvSize srcsize,
                     uchar* dst, int dststep, CvSize dstsize,
                     int pix_size ))
{
    int* x_ofs = (int*)alloca( dstsize.width * sizeof(x_ofs[0]) );
    
    int sw = srcsize.width - 1;
    int sh = srcsize.height - 1;
    int dw = dstsize.width - 1;
    int dh = dstsize.height - 1;

    int x, y;

    for( x = 0; x <= dw; x++ )
        x_ofs[x] = ((sw*x*2 + dw)/(dw*2))*pix_size;

    for( y = 0; y <= dh; y++, dst += dststep )
    {
        const uchar* tsrc = src + srcstep*((sh*y*2 + dh)/(dh*2));

        switch( pix_size )
        {
        case 1:
            for( x = 0; x <= dw - 1; x += 2 )
            {
                uchar t0 = tsrc[x_ofs[x]];
                uchar t1 = tsrc[x_ofs[x+1]];

                dst[x] = t0;
                dst[x+1] = t1;
            }

            for( ; x <= dw; x++ )
                dst[x] = tsrc[x_ofs[x]];
            break;
        case 3:
            for( x = 0; x <= dw; x++ )
                memcpy( dst + x*3, tsrc + x_ofs[x], 3 );
            break;
        case 4:
            for( x = 0; x <= dw; x++ )
                memcpy( dst + x*4, tsrc + x_ofs[x], 4 );
            break;
        case 2:
            for( x = 0; x <= dw; x++ )
                memcpy( dst + x*2, tsrc + x_ofs[x], 2 );
            break;
        default:
            for( x = 0; x <= dw; x++ )
                memcpy( dst + x*pix_size, tsrc + x_ofs[x], pix_size );
        }
    }

    return CV_OK;
}


#define prepare_alpha_8u( x, shift_val )  cvRound((x)*(1 << (shift_val)))
#define scale_macro_8u(x, shift_val) ((x) << (shift_val))
#define cast_macro_8u(x)  ((uchar)(x))

#define process_bilinear_c1( sx, dx, cn, worktype, scale_macro,         \
                             descale_macro, cast_macro, shift_val )     \
{                                                                       \
    worktype t0 = tsrc[sx], t1 = tsrc2[sx];                             \
                                                                        \
    t0 = scale_macro(t0,shift_val) + (tsrc[sx+cn] - t0)*alpha;          \
    t1 = scale_macro(t1,shift_val) + (tsrc2[sx+cn] - t1)*alpha;         \
                                                                        \
    t0 = descale_macro( scale_macro(t0,shift_val) +                     \
                        (t1 - t0)*y_alpha,shift_val*2);                 \
    dst[dx] = cast_macro(t0);                                           \
}


#define process_bilinear_c2( sx, dx, cn, worktype, scale_macro,         \
                             descale_macro, cast_macro, shift_val )     \
{                                                                       \
    process_bilinear_c1( sx, dx*2, cn, worktype, scale_macro,           \
                         descale_macro, cast_macro, shift_val )         \
    process_bilinear_c1( sx+1, dx*2+1, cn, worktype, scale_macro,       \
                         descale_macro, cast_macro, shift_val )         \
}

#define process_bilinear_c3( sx, dx, cn, worktype, scale_macro,         \
                             descale_macro, cast_macro, shift_val )     \
{                                                                       \
    process_bilinear_c1( sx, dx*3, cn, worktype, scale_macro,           \
                         descale_macro, cast_macro, shift_val )         \
    process_bilinear_c1( sx+1, dx*3+1, cn, worktype, scale_macro,       \
                         descale_macro, cast_macro, shift_val )         \
    process_bilinear_c1( sx+2, dx*3+2, cn, worktype, scale_macro,       \
                         descale_macro, cast_macro, shift_val )         \
}


#define process_bilinear_c4( sx, dx, cn, worktype, scale_macro,         \
                             descale_macro, cast_macro, shift_val )     \
{                                                                       \
    process_bilinear_c1( sx, dx*4, cn, worktype, scale_macro,           \
                         descale_macro, cast_macro, shift_val )         \
    process_bilinear_c1( sx+1, dx*4+1, cn, worktype, scale_macro,       \
                         descale_macro, cast_macro, shift_val )         \
    process_bilinear_c1( sx+2, dx*4+2, cn, worktype, scale_macro,       \
                         descale_macro, cast_macro, shift_val )         \
    process_bilinear_c1( sx+3, dx*4+3, cn, worktype, scale_macro,       \
                         descale_macro, cast_macro, shift_val )         \
}

#define process_bilinear_vert_c1( worktype, arrtype, scale_macro,       \
                                  descale_macro, cast_macro, shift_val) \
{                                                                       \
    int sx = x_ofs[x];                                                  \
    worktype t0 = tsrc[sx];                                             \
    arrtype t1;                                                         \
                                                                        \
    t0 = descale_macro( scale_macro(t0,shift_val) +                     \
                        (tsrc2[sx] - t0)*y_alpha,shift_val);            \
    t1 = cast_macro(t0);                                                \
                                                                        \
    for( ; x <= dw; x++ )                                               \
        dst[x] = t1;                                                    \
}

#define process_bilinear_vert_c2( worktype, arrtype, scale_macro,       \
                                  descale_macro, cast_macro, shift_val) \
{                                                                       \
    int sx = x_ofs[x];                                                  \
    worktype t0;                                                        \
    arrtype t1, t2;                                                     \
                                                                        \
    t0 = tsrc[sx];                                                      \
    t0 = descale_macro( scale_macro(t0,shift_val) +                     \
                        (tsrc2[sx] - t0)*y_alpha,shift_val);            \
    t1 = cast_macro(t0);                                                \
                                                                        \
    t0 = tsrc[sx+1];                                                    \
    t0 = descale_macro( scale_macro(t0,shift_val) +                     \
                        (tsrc2[sx+1] - t0)*y_alpha,shift_val);          \
    t2 = cast_macro(t0);                                                \
                                                                        \
    for( ; x <= dw; x++ )                                               \
    {                                                                   \
        dst[x*2] = t1;                                                  \
        dst[x*2+1] = t2;                                                \
    }                                                                   \
}

#define process_bilinear_vert_c3( worktype, arrtype, scale_macro,       \
                                  descale_macro, cast_macro, shift_val) \
{                                                                       \
    int sx = x_ofs[x];                                                  \
    worktype t0;                                                        \
    arrtype t1, t2, t3;                                                 \
                                                                        \
    t0 = tsrc[sx];                                                      \
    t0 = descale_macro( scale_macro(t0,shift_val) +                     \
                        (tsrc2[sx] - t0)*y_alpha,shift_val);            \
    t1 = cast_macro(t0);                                                \
                                                                        \
    t0 = tsrc[sx+1];                                                    \
    t0 = descale_macro( scale_macro(t0,shift_val) +                     \
                        (tsrc2[sx+1] - t0)*y_alpha,shift_val);          \
    t2 = cast_macro(t0);                                                \
                                                                        \
    t0 = tsrc[sx+2];                                                    \
    t0 = descale_macro( scale_macro(t0,shift_val) +                     \
                        (tsrc2[sx+2] - t0)*y_alpha,shift_val);          \
    t3 = cast_macro(t0);                                                \
                                                                        \
    for( ; x <= dw; x++ )                                               \
    {                                                                   \
        dst[x*3] = t1;                                                  \
        dst[x*3+1] = t2;                                                \
        dst[x*3+2] = t3;                                                \
    }                                                                   \
}


#define process_bilinear_vert_c4( worktype, arrtype, scale_macro,       \
                                  descale_macro, cast_macro, shift_val) \
{                                                                       \
    int sx = x_ofs[x];                                                  \
    worktype t0;                                                        \
    arrtype t1, t2, t3, t4;                                             \
                                                                        \
    t0 = tsrc[sx];                                                      \
    t0 = descale_macro( scale_macro(t0,shift_val) +                     \
                        (tsrc2[sx] - t0)*y_alpha,shift_val);            \
    t1 = cast_macro(t0);                                                \
                                                                        \
    t0 = tsrc[sx+1];                                                    \
    t0 = descale_macro( scale_macro(t0,shift_val) +                     \
                        (tsrc2[sx+1] - t0)*y_alpha,shift_val);          \
    t2 = cast_macro(t0);                                                \
                                                                        \
    t0 = tsrc[sx+2];                                                    \
    t0 = descale_macro( scale_macro(t0,shift_val) +                     \
                        (tsrc2[sx+2] - t0)*y_alpha,shift_val);          \
    t3 = cast_macro(t0);                                                \
                                                                        \
    t0 = tsrc[sx+3];                                                    \
    t0 = descale_macro( scale_macro(t0,shift_val) +                     \
                        (tsrc2[sx+3] - t0)*y_alpha,shift_val);          \
    t4 = cast_macro(t0);                                                \
                                                                        \
    for( ; x <= dw; x++ )                                               \
    {                                                                   \
        dst[x*4] = t1;                                                  \
        dst[x*4+1] = t2;                                                \
        dst[x*4+2] = t3;                                                \
        dst[x*4+3] = t4;                                                \
    }                                                                   \
}


#define  ICV_DEF_RESIZE_BILINEAR_FUNC( flavor, cn, arrtype, worktype, prepare_alpha,    \
                                      scale_macro, descale_macro, cast_macro, shift_val)\
IPCVAPI_IMPL( CvStatus,                                                                 \
icvResize_Bilinear_##flavor##_C##cn##R, ( const uchar* src, int srcstep, CvSize srcsize,\
                                          uchar* dst, int dststep, CvSize dstsize ))    \
{                                                                                       \
    int* x_ofs = (int*)alloca( dstsize.width * sizeof(x_ofs[0]) );                      \
    worktype* x_alpha = (worktype*)alloca( dstsize.width * sizeof(x_alpha[0]) );        \
                                                                                        \
    int sw = srcsize.width - 1;                                                         \
    int sh = srcsize.height - 1;                                                        \
    int dw = dstsize.width - 1;                                                         \
    int dh = dstsize.height - 1;                                                        \
    int x, y, xmax = dw+1;                                                              \
                                                                                        \
    for( x = 0; x <= dw; x++ )                                                          \
    {                                                                                   \
        float fx = (float)sw*x/(dw + (dw==0));                                          \
        int ix = cvFloor(fx);                                                           \
        x_ofs[x] = ix*cn;                                                               \
        if( ix >= sw && xmax > dw )                                                     \
            xmax = x;                                                                   \
        x_alpha[x] = prepare_alpha(fx - ix, shift_val );                                \
    }                                                                                   \
                                                                                        \
    for( y = 0; y <= dh; y++, (char*&)dst += dststep )                                  \
    {                                                                                   \
        float fy = (float)sh*y/(dh + (dh==0));                                          \
        int iy = cvFloor(fy);                                                           \
        int y_alpha = prepare_alpha( fy - iy, shift_val );                              \
                                                                                        \
        const arrtype* tsrc = (const arrtype*)((uchar*)src + iy*srcstep);               \
        const arrtype* tsrc2 = iy < sh ? (const arrtype*)((uchar*)tsrc+srcstep) : tsrc; \
                                                                                        \
        for( x = 0; x < xmax; x++ )                                                     \
        {                                                                               \
            int sx = x_ofs[x];                                                          \
            worktype alpha = x_alpha[x];                                                \
                                                                                        \
            process_bilinear_c##cn( sx, x, cn, worktype, scale_macro,                   \
                                    descale_macro, cast_macro, shift_val );             \
        }                                                                               \
                                                                                        \
        process_bilinear_vert_c##cn( worktype, arrtype, scale_macro,                    \
                                     descale_macro, cast_macro, shift_val);             \
    }                                                                                   \
                                                                                        \
    return CV_OK;                                                                       \
}


#define ICV_DEF_RESIZE_BILINEAR_FUNC_8U( cn )                                           \
    ICV_DEF_RESIZE_BILINEAR_FUNC( 8u, cn, uchar, int, prepare_alpha_8u,                 \
                                  scale_macro_8u, CV_DESCALE, cast_macro_8u, 8 )


ICV_DEF_RESIZE_BILINEAR_FUNC_8U( 1 )
ICV_DEF_RESIZE_BILINEAR_FUNC_8U( 2 )
ICV_DEF_RESIZE_BILINEAR_FUNC_8U( 3 )
ICV_DEF_RESIZE_BILINEAR_FUNC_8U( 4 )


#define ICV_DEF_INIT_GEOM_TABLE( FUNCNAME )                 \
static void                                                 \
icvInit##FUNCNAME##RTable( CvBigFuncTable* table )          \
{                                                           \
    table->fn_2d[CV_8UC1] = (void*)icv##FUNCNAME##_8u_C1R;  \
    table->fn_2d[CV_8UC2] = (void*)icv##FUNCNAME##_8u_C2R;  \
    table->fn_2d[CV_8UC3] = (void*)icv##FUNCNAME##_8u_C3R;  \
    table->fn_2d[CV_8UC4] = (void*)icv##FUNCNAME##_8u_C4R;  \
}

ICV_DEF_INIT_GEOM_TABLE( Resize_Bilinear )

typedef CvStatus (CV_STDCALL * CvGeomTransformFunc)
                            ( const void* src, int srcstep, CvSize srcsize,
                              void* dst, int dststep, CvSize dstsize );

CV_IMPL void
cvResize( const CvArr* srcarr, CvArr* dstarr, int method )
{
    static CvBigFuncTable bilintab;
    static int inittab = 0;

    CV_FUNCNAME( "cvResize" );

    __BEGIN__;
    
    CvMat srcstub, *src = (CvMat*)srcarr;
    CvMat dststub, *dst = (CvMat*)dstarr;
    CvSize srcsize, dstsize;
    
    CV_CALL( src = cvGetMat( srcarr, &srcstub ));
    CV_CALL( dst = cvGetMat( dstarr, &dststub ));
    
    if( !inittab )
    {
        icvInitResize_BilinearRTable( &bilintab );
        inittab = 1;
    }

    if( !CV_ARE_TYPES_EQ( src, dst ))
        CV_ERROR( CV_StsUnmatchedFormats, "" );

    srcsize = icvGetMatSize( src );
    dstsize = icvGetMatSize( dst );

    if( (unsigned)method > CV_INTER_LINEAR )
        CV_ERROR( CV_StsBadFlag, "Bad interpolation method value" );

    if( CV_ARE_SIZES_EQ( src, dst ))
        CV_CALL( cvCopy( src, dst ));

    if( method == CV_INTER_NN )
    {
        IPPI_CALL( icvResize_NN_8u_C1R( src->data.ptr, src->step, srcsize,
                                        dst->data.ptr, dst->step, dstsize,
                                        icvPixSize[CV_ARR_TYPE(src->type)]));
    }
    else
    {
        CvGeomTransformFunc func = (CvGeomTransformFunc)
            (bilintab.fn_2d[CV_ARR_TYPE(src->type)]);

        if( !func )
            CV_ERROR( CV_StsUnsupportedFormat, "" );

        IPPI_CALL( func( src->data.ptr, src->step, srcsize,
                         dst->data.ptr, dst->step, dstsize ));
    }

    __END__;
}

/* End of file. */

