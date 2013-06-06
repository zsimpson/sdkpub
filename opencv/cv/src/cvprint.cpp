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

#if 0

typedef struct CvPrintInfo
{
    FILE* strm;
    const char* fmt_str;
    const char* name;
    int flags;
}
CvPrintInfo;

#define CV_IMPL_PRINT_1D( funcname, type, def_fmt_str )                         \
static int funcname( type* arr, int len, CvPrintInfo* info )                    \
{                                                                               \
    int arrtype = info->flags;                                                  \
    const char* fmt_str = info && info->fmt_str ? info->fmt_str : def_fmt_str;  \
    FILE* strm = info && info->strm ? info->strm : stdout;                      \
    char fmt_buf[16];                                                           \
    int i;                                                                      \
    len *= CV_ARR_CN(arrtype);                                                  \
                                                                                \
    /* add comma and space after format string */                               \
    sprintf( fmt_buf, "%s, ", fmt_str );                                        \
                                                                                \
    if( info && info->name )                                                    \
        fprintf( strm, "%s = \n[ ", info->name );                               \
    else                                                                        \
        fprintf( strm, "\n[ ");                                                 \
                                                                                \
    for( i = 0; i < len; i++ )                                                  \
        fprintf( strm, fmt_str, arr[i] );                                       \
                                                                                \
    fprintf( strm, " ]\n");                                                     \
    return 0;                                                                   \
}


#define CV_IMPL_PRINT_2D( funcname, type, def_fmt_str )                         \
static int funcname( type* arr, int step, int width, int height, CvPrintInfo* info ) \
{                                                                               \
    int arrtype = info->flags;                                                  \
    const char* fmt_str = info && info->fmt_str ? info->fmt_str : def_fmt_str;  \
    FILE* strm = info && info->strm ? info->strm : stdout;                      \
    int i;                                                                      \
    char fmt_buf[16];                                                           \
                                                                                \
    width *= CV_ARR_CN(arrtype);                                                \
                                                                                \
    /* add comma and space after format string */                               \
    sprintf( fmt_buf, "%s, ", fmt_str );                                        \
                                                                                \
    if( info && info->name )                                                    \
        fprintf( strm, "%s = \n[", info->name );                                \
    else                                                                        \
        fprintf( strm, "\n[ ");                                                 \
                                                                                \
    for( ; height--; (char*&)arr += step )                                      \
    {                                                                           \
        for( i = 0; i < width; i++ )                                            \
            fprintf( strm, fmt_str, arr[i] );                                   \
        fprintf( strm, height >= 1 ? "\n " : " ]\n" );                          \
    }                                                                           \
                                                                                \
    return 0;                                                                   \
}

#define def_8u_fmt   "%3d"
#define def_8s_fmt   "%4d"
#define def_16s_fmt  "%6d"
#define def_32s_fmt  "%08x"
#define def_32f_fmt  "%7.3g"
#define def_64f_fmt  "%9.5g"

CV_IMPL_PRINT_1D( icvPrint_1D_8u,  uchar,  def_8u_fmt )
CV_IMPL_PRINT_1D( icvPrint_1D_8s,  char,   def_8s_fmt )
CV_IMPL_PRINT_1D( icvPrint_1D_16s, short,  def_16s_fmt )
CV_IMPL_PRINT_1D( icvPrint_1D_32s, int,    def_32s_fmt )
CV_IMPL_PRINT_1D( icvPrint_1D_32f, float,  def_32f_fmt )
CV_IMPL_PRINT_1D( icvPrint_1D_64f, double, def_64f_fmt )

CV_IMPL_PRINT_2D( icvPrint_2D_8u,  uchar,  def_8u_fmt )
CV_IMPL_PRINT_2D( icvPrint_2D_8s,  char,   def_8s_fmt )
CV_IMPL_PRINT_2D( icvPrint_2D_16s, short,  def_16s_fmt )
CV_IMPL_PRINT_2D( icvPrint_2D_32s, int,    def_32s_fmt )
CV_IMPL_PRINT_2D( icvPrint_2D_32f, float,  def_32f_fmt )
CV_IMPL_PRINT_2D( icvPrint_2D_64f, double, def_64f_fmt )

CV_IMPL_INIT_FUNC_TAB( 1, Print );

CV_IMPL void cvPrint( const CvMat* arr, const char* arrname, FILE* strm, const char* fmt )
{
    static CvFunc1Table print_tab;
    CvPrintInfo info;

    __BEGIN__;

    CvMat arrstub;

    if( !print_tab.fn_2d[5] )
    {
        icvInitPrintTable( &print_tab );
    }

    CV_CALL( arr = cvGetMat( arr, &arrstub ));

    info.name = arrname;
    info.fmt_str = fmt;
    info.strm = strm;
    info.flags = CV_ARR_TYPE( arr->type );

    if( arr->height == 1 )
    {
        IPCV_CALL( print_tab.fn_1d[CV_ARR_DEPTH(arr->type)]
                   ( arr->data, arr->height*arr->width, &info ));
    }
    else
    {
        IPCV_CALL( print_tab.fn_2d[CV_ARR_DEPTH(arr->type)]
                   ( arr->data, arr->step, arr->width, arr->height, &info ));
    }
    
    __END__;
}

#endif

/* End of file. */

